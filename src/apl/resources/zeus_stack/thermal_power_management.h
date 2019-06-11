/* 
 * File:   thermal_power_management.h
 * Author: C41076
 *
 * Created on January 30, 2019 9:57 AM
 */

#ifndef THERMAL_POWER_MANAGEMENT_H
#define	THERMAL_POWER_MANAGEMENT_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define POWER_BUDGET_WATTS    (uint32_t)60    
    
#define TEMP_HYSTERESIS             3

/* Define the temperature at which currents are rolled back to 50% */
#define TEMP_ROLLBACK_RISING_LEVEL  70
#define TEMP_ROLLBACK_FALLING_LEVEL (TEMP_ROLLBACK_RISING_LEVEL - TEMP_HYSTERESIS)

/* Define the temperature at which PDOs are reduced to 5V only */    
#define TEMP_5V_ONLY_RISING_LEVEL   80
#define TEMP_5V_ONLY_FALLING_LEVEL  (TEMP_5V_ONLY_RISING_LEVEL - TEMP_HYSTERESIS)

/* Define the temperature at which the supply will shut down.  When the temperature
 * returns to below the falling level the system will reset
 */    
#define TEMP_SHUTDOWN_RISING_LEVEL  85
#define TEMP_SHUTDOWN_FALLING_LEVEL (TEMP_ROLLBACK_RISING_LEVEL - TEMP_HYSTERESIS)


typedef enum
{
    THERM_ST_NORMAL = 0,
    THERM_ST_ROLLBACK,
    THERM_ST_5V_ONLY,
    THERM_ST_SHUTDOWN,
    THERM_ST_INIT        
}thermal_mgmt_state_t;

typedef enum
{
    SUBSTATE_ENTRY = 0,
    SUBSTATE_IDLE
}power_substate_t;

enum PDO_UPDATE_TYPE
{
    PDO_NO_UPDATE = 0,
    PDO_UPDATE_CAPABILITIES,
    PDO_UPDATE_CAPS_RESET
};


uint8_t check_power_budget(uint8_t port_num, uint16_t max_current_requested, uint8_t pdo_requested);
void reset_port_pdos(uint8_t port_num);
void power_management_state_machine(void);
    
extern thermal_mgmt_state_t thermal_mgmt_state;
extern power_substate_t thermal_mgmt_substate;
extern uint8_t port_pdo_update_required[CONFIG_PD_PORT_COUNT];
extern uint32_t port_max_power[CONFIG_PD_PORT_COUNT];
#ifdef	__cplusplus
}
#endif

#endif	/* THERMAL_POWER_MANAGEMENT_H */

