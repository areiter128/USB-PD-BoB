////////////////////////////////////////////////////////////////////////////////
// © 2015 Microchip Technology Inc.
//
// MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any
// derivatives created by any person or entity by or on your behalf, exclusively
// with Microchip's products.  Microchip and its licensors retain all ownership
// and intellectual property rights in the accompanying software and in all
// derivatives here to.
//
// This software and any accompanying information is for suggestion only.  It
// does not modify Microchip's standard warranty for its products.  You agree
// that you are solely responsible for testing the software and determining its
// suitability.  Microchip has no obligation to modify, test, certify, or
// support the software.
//
// THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
// EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
// WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
// PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS,
// COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
//
// IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT
// (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY,
// INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
// EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
// ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF
// MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
// TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
// CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
// FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
//
// MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
// TERMS.
////////////////////////////////////////////////////////////////////////////////
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "ZeusStackConfig.h"
#include "stdinc.h"
#include "thermal_power_management.h"
//#include "buck.h"

//#include "debug_uart.h"
//#include "system_log.h"
#include "cfg_globals.h"
#include "int_globals.h"
#include <libpic30.h>

/*===== DEMO_BOARD_TEST =====*/
#define LOG_PRINT(x,y) // define away LOG_PRINTs
#define Read_Temp() 30  // Set the temperature to 30C
/*===== DEMO_BOARD_TEST =====*/

thermal_mgmt_state_t thermal_mgmt_state = THERM_ST_INIT;
power_substate_t thermal_mgmt_substate = SUBSTATE_IDLE;
uint8_t thermal_shutdown_active = false;

uint8_t port_pdo_update_required[CONFIG_PD_PORT_COUNT];

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

void thermal_power_management_state_machine(void)
{
    uint8_t port_index;
    uint16_t temperature = Read_Temp();
    
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
                    if (temperature > TEMP_ROLLBACK_RISING_LEVEL)
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
                    if (temperature > TEMP_5V_ONLY_RISING_LEVEL)
                    {
                        /* Temperature has exceeded the rollback operating range.
                         * go to the 5V ONLY state.
                         */
                        LOG_PRINT(LOG_DEBUG, "ROLLBACK: Temp > Rollback hi level\r\n");
                        thermal_mgmt_state = THERM_ST_5V_ONLY;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    else if (temperature < TEMP_ROLLBACK_FALLING_LEVEL)
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
                    if (temperature > TEMP_SHUTDOWN_RISING_LEVEL)
                    {
                        /* Temperature has exceeded the 5V ONLY operating range.
                         * go to the SHUTDOWN state.
                         */
                        LOG_PRINT(LOG_DEBUG, "5V_ONLY: Temp > 5V Only Hi level\r\n");
                        thermal_mgmt_state = THERM_ST_SHUTDOWN;
                        thermal_mgmt_substate = SUBSTATE_ENTRY;
                    }
                    else if (temperature < TEMP_5V_ONLY_FALLING_LEVEL)
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
                    if (temperature < TEMP_SHUTDOWN_FALLING_LEVEL)
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