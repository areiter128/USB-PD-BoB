/*LICENSE ********************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 * ***************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "ZeusStackConfig.h"
#include "stdinc.h"
#include "hook_functions.h"
#include "thermal_power_management.h"
//#include "buck.h"

#include "debug_uart.h"
//#include "system_log.h"
#include "cfg_globals.h"
#include "int_globals.h"
#include <libpic30.h>

thermal_mgmt_state_t thermal_mgmt_state = THERM_ST_INIT;
power_substate_t thermal_mgmt_substate = SUBSTATE_IDLE;
uint8_t thermal_shutdown_active = false;

uint8_t port_pdo_update_required[CONFIG_PD_PORT_COUNT];

uint32_t port_max_power[CONFIG_PD_PORT_COUNT];

uint16_t thermal_rollback_threshold = THERMAL_ROLLBACK_DEFAULT_LEVEL;
uint16_t thermal_5v_only_threshold = THERMAL_5V_ONLY_DEFAULT_LEVEL;
uint16_t thermal_shutdown_threshold = THERMAL_SHUTDOWN_DEFAULT_LEVEL;

uint32_t power_budget_watts = POWER_BUDGET_DEFAULT_WATTS;

uint8_t check_power_budget(uint8_t port_num, uint16_t max_current_requested, uint8_t pdo_requested)
{
    uint8_t power_budget_met = 0;
    uint8_t index;
    uint32_t used_power_mw = 0;
    uint32_t requested_port_power_mw;
    uint32_t remaining_power_mw;
    uint32_t pdo_calculated_current;
    
    for (index = 0; index < CONFIG_PD_PORT_COUNT; index++)
    {
        if (index != port_num)
        {
            used_power_mw += port_max_power[index];
        }
    }
    
    requested_port_power_mw = ((uint32_t)DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasPortConfigurationData[port_num].u32PDO[pdo_requested-1]) *
                           (uint32_t) max_current_requested) / 100;
    LOG_PRINT2(LOG_DEBUG, "CHECK_POWER: Port %d requested %ld mW\r\n", port_num, requested_port_power_mw);
            
    if ((used_power_mw + requested_port_power_mw) > (power_budget_watts * 1000))
    {
        /* This will put us over the power budget.  Update the PDOs for this port and 
         * mark the request invalid
         */
        remaining_power_mw = (power_budget_watts * 1000) - used_power_mw;
        LOG_PRINT2(LOG_DEBUG, "CHECK_POWER: Port %d Remaining %ld mW\r\n", port_num, remaining_power_mw);
        for (index = 0; index < gasPortConfigurationData[port_num].u8PDOCnt; index++)
        {
            if ((((uint32_t)DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasPortConfigurationData[port_num].u32PDO[index])) * 
                 ((uint32_t)DPM_GET_CURRENT_FROM_PDO_MILLI_A(gasPortConfigurationData[port_num].u32PDO[index]))) >
                remaining_power_mw)
            {
                /* The power for this PDO is greater than the remaining power in the budget.  Reduce the 
                 * current to the level required to fit in the budget 
                 */
                LOG_PRINT1(LOG_DEBUG, "CHECK_POWER: V %ld mV\r\n", ((uint32_t)DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasPortConfigurationData[port_num].u32PDO[index])));
        
                pdo_calculated_current = (remaining_power_mw * 1000) / ((uint32_t)DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasPortConfigurationData[port_num].u32PDO[index]));
                LOG_PRINT2(LOG_DEBUG, "CHECK_POWER: Port %d new current is %ld mA\r\n", port_num, pdo_calculated_current);
               
                gasPortConfigurationData[port_num].u32PDO[index] = 
                        (gasPortConfigurationData[port_num].u32PDO[index] & ~(DPM_PDO_CURRENT_MASK << DPM_PDO_CURRENT_POS)) |
                        (((pdo_calculated_current / DPM_PDO_CURRENT_UNIT) & DPM_PDO_CURRENT_MASK) << DPM_PDO_CURRENT_POS);
                LOG_PRINT1(LOG_DEBUG, "CHECK_POWER: new A %ld mA\r\n", ((uint32_t)DPM_GET_CURRENT_FROM_PDO_MILLI_A(gasPortConfigurationData[port_num].u32PDO[index])));
            }
        }
    }
    else
    {
        /* The power budget has been met */
        LOG_PRINT1(LOG_DEBUG, "CHECK_POWER: Port %d within budget\r\n", port_num);
        power_budget_met = 1;
        port_max_power[port_num] = requested_port_power_mw;
    }

    return (power_budget_met);
}

void update_all_port_pdos(void)
{
    uint8_t port_num;

    switch(thermal_mgmt_state)
    {
        case THERM_ST_NORMAL:
            memcpy(gasPortConfigurationData, gasPortNormalConfigurationData, sizeof(gasPortConfigurationData));
        break;

        case THERM_ST_ROLLBACK:
            memcpy(gasPortConfigurationData, gasPortRollbackConfigurationData, sizeof(gasPortConfigurationData));
        break;

        case THERM_ST_5V_ONLY:
            /* Only enable the first PDO for 5V */
            for (port_num = 0; port_num < CONFIG_PD_PORT_COUNT; port_num++)
            {
                gasPortConfigurationData[port_num].u8PDOCnt = 1;
            }
        break;

        case THERM_ST_SHUTDOWN:
            
        break;
    }

    /* Set the flag to tell the state machine to update all ports */
    for (port_num = 0; port_num < CONFIG_PD_PORT_COUNT; port_num++)
    {
        if (thermal_shutdown_active)
        {
            port_pdo_update_required[port_num] = PDO_UPDATE_CAPS_RESET;
            thermal_shutdown_active = false;
        }
        else
        {
            port_pdo_update_required[port_num] = PDO_UPDATE_CAPABILITIES;
        }
    }

}

void reset_port_pdos(uint8_t port_num)
{
    uint8_t index;
    
    for (index = 0; index < gasPortConfigurationData[port_num].u8PDOCnt; index++)
    {
        switch(thermal_mgmt_state)
        {
            case THERM_ST_NORMAL:
                gasPortConfigurationData[port_num].u32PDO[index] = gasPortNormalConfigurationData[port_num].u32PDO[index];
            break;

            case THERM_ST_ROLLBACK:
                gasPortConfigurationData[port_num].u32PDO[index] = gasPortRollbackConfigurationData[port_num].u32PDO[index];
            break;

            case THERM_ST_5V_ONLY:
                gasPortConfigurationData[port_num].u32PDO[index] = gasPortRollbackConfigurationData[port_num].u32PDO[index];
            break;

            case THERM_ST_SHUTDOWN:

            break;
        }
    }
}

void update_single_port_pdos(uint8_t port_num)
{

    switch(thermal_mgmt_state)
    {
        case THERM_ST_NORMAL:
            memcpy(gasPortConfigurationData, gasPortNormalConfigurationData, sizeof(gasPortConfigurationData));
        break;

        case THERM_ST_ROLLBACK:
            memcpy(gasPortConfigurationData, gasPortRollbackConfigurationData, sizeof(gasPortConfigurationData));
        break;

        case THERM_ST_5V_ONLY:
            /* Only enable the first PDO for 5V */
            for (port_num = 0; port_num < CONFIG_PD_PORT_COUNT; port_num++)
            {
                gasPortConfigurationData[port_num].u8PDOCnt = 1;
            }
        break;

        case THERM_ST_SHUTDOWN:
            
        break;
    }

    /* Set the flag to tell the state machine to update all ports */
    for (port_num = 0; port_num < CONFIG_PD_PORT_COUNT; port_num++)
    {
        if (thermal_shutdown_active)
        {
            port_pdo_update_required[port_num] = PDO_UPDATE_CAPS_RESET;
            thermal_shutdown_active = false;
        }
        else
        {
            port_pdo_update_required[port_num] = PDO_UPDATE_CAPABILITIES;
        }
    }

}

void power_management_state_machine(void)
{
    uint8_t port_index;
    uint16_t temperature = CONFIG_HOOK_FUNCTION_GET_TEMPERATURE_IN_C();
    
    switch (thermal_mgmt_state)
    {
        case THERM_ST_INIT:
            /* Initialization of State machine Variables */
            LOG_PRINT(LOG_DEBUG, "INIT: Initialize Thermal state machine vars\r\n");
            thermal_mgmt_state = THERM_ST_NORMAL;
            thermal_mgmt_substate = SUBSTATE_IDLE;
            for (port_index = 0; port_index < CONFIG_PD_PORT_COUNT; port_index++)
            {
                port_pdo_update_required[port_index] = PDO_NO_UPDATE;
                port_max_power[port_index] = 0;
            }
            break;
        case THERM_ST_NORMAL:
            /* Normal conditions.  Run at full current in all PDOs */
            switch (thermal_mgmt_substate)
            {
                case SUBSTATE_ENTRY:
                    /* Set up the system for normal mode */
                    LOG_PRINT(LOG_DEBUG, "Entering NORMAL Thermal State\r\n");
                    update_all_port_pdos();
                    thermal_mgmt_substate = SUBSTATE_IDLE;
                break;
                    
                case SUBSTATE_IDLE:
                    if (temperature > thermal_rollback_threshold)
                    {
                        /* Temperature has exceeded the normal operating range.
                         * go to the ROLLBACK state.
                         */
                        LOG_PRINT(LOG_DEBUG, "NORMAL: Temp > normal hi level\r\n");
                        thermal_mgmt_state = THERM_ST_ROLLBACK;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    break;
            }
            break;
            
        case THERM_ST_ROLLBACK:
            /* Current rollback conditions.  Run at half current in all PDOs */
            switch (thermal_mgmt_substate)
            {
                case SUBSTATE_ENTRY:
                    /* Set up the system for rollback mode */
                    LOG_PRINT(LOG_DEBUG, "ROLLBACK: Enter Rollback mode\r\n");
                    update_all_port_pdos();
                    thermal_mgmt_substate = SUBSTATE_IDLE;
                break;
                    
                case SUBSTATE_IDLE:
                    if (temperature > thermal_5v_only_threshold)
                    {
                        /* Temperature has exceeded the rollback operating range.
                         * go to the 5V ONLY state.
                         */
                        LOG_PRINT(LOG_DEBUG, "ROLLBACK: Temp > Rollback hi level\r\n");
                        thermal_mgmt_state = THERM_ST_5V_ONLY;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    else if (temperature < (thermal_rollback_threshold - THERMAL_HYSTERESIS))
                    {
                        /* Temperature has returned to the normal operating range.
                         * go to the NORMAL state.
                         */
                        LOG_PRINT(LOG_DEBUG, "ROLLBACK: Temp < rollback low level\r\n");
                        thermal_mgmt_state = THERM_ST_NORMAL;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    break;
            }
            break;
            
        case THERM_ST_5V_ONLY:
            /* 5V ONLY conditions.  Run with only a 5V PDO */
            switch (thermal_mgmt_substate)
            {
                case SUBSTATE_ENTRY:
                    /* Set up the system for 5V ONLY mode */
                    LOG_PRINT(LOG_DEBUG, "5V_ONLY: Enter 5V Only mode\r\n");
                    update_all_port_pdos();
                    thermal_mgmt_substate = SUBSTATE_IDLE;
                    break;
                    
                case SUBSTATE_IDLE:
                    if (temperature > thermal_shutdown_threshold)
                    {
                        /* Temperature has exceeded the 5V ONLY operating range.
                         * go to the SHUTDOWN state.
                         */
                        LOG_PRINT(LOG_DEBUG, "5V_ONLY: Temp > 5V Only Hi level\r\n");
                        thermal_mgmt_state = THERM_ST_SHUTDOWN;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    else if (temperature < (thermal_5v_only_threshold - THERMAL_HYSTERESIS))
                    {
                        /* Temperature has returned to the ROLLBACK operating range.
                         * go to the ROLLBACK state.
                         */
                        LOG_PRINT(LOG_DEBUG, "5V_ONLY: Temp < 5V Only Lo Level\r\n");
                        thermal_mgmt_state = THERM_ST_ROLLBACK;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    break;
            }
            break;
            
        case THERM_ST_SHUTDOWN:
            /* SHUTDOWN conditions.  Turn off the supply */
            switch (thermal_mgmt_substate)
            {
                case SUBSTATE_ENTRY:
                    /* Set up the system for shutdown mode */
                    LOG_PRINT(LOG_DEBUG, "SHUTDOWN: Enter Thermal Shutdown mode\r\n");
                    update_all_port_pdos();
                    // DEMO_BOARD_TEST
                    //buck_status.overtemp = 1;
                    thermal_shutdown_active = true;
                    for (port_index = 0; port_index < CONFIG_PD_PORT_COUNT; port_index++)
                    {
                        gau8PortDisable[port_index] = PORT_STATUS_DISABLED;
                    }
                    thermal_mgmt_substate = SUBSTATE_IDLE;
                    break;
                    
                case SUBSTATE_IDLE:
                    if (temperature < (thermal_shutdown_threshold - THERMAL_HYSTERESIS))
                    {
                        /* Temperature has returned to the 5V ONLY operating range.
                         * go to the 5V ONLY state.
                         */
                        LOG_PRINT(LOG_DEBUG, "SHUTDOWN: Temp < Shutdown Lo Level\r\n");
                        asm("RESET");
                    }
                    break;
            }
        break;
    }
    
    
}