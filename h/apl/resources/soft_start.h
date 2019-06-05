/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
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
 */

/* 
 * File:   soft_start.h
 * Author: M91406
 * Comments: Dedicated DC/DC battery charger soft-start state engine for bi-directional buck converters
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APL_RESOURCES_SOFT_START_H_
#define	_APL_RESOURCES_SOFT_START_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "hal/config/syscfg_scaling.h"
#include "hal/config/syscfg_limits.h"

/* Controller Settings */
#define SOFT_START_V_REF_STEP_SIZE  7 // (uint16_t)((float)VOUT_FB_REF_ADC / (float)RAMP_UP_PERIOD_TICKS)     // Step-Granulatiry of soft-start ramp
#define SOFT_START_I_REF_STEP_SIZE  1 // (uint16_t)((float)VOUT_FB_REF_ADC / (float)RAMP_UP_PERIOD_TICKS)     // Step-Granulatiry of soft-start ramp
#define SOFT_START_INIT_REFERENCE   100   // Minimum voltage feedback refrence
#define SOFT_START_POWER_ON_DELAY   POWER_ON_DELAY_TICKS  // Delay in [Number of System Ticks] until the output voltage is ramped up
#define SOFT_START_POWER_GOOD_DELAY POWER_GOOD_DELAY_TICKS    // Delay in [Number of System Ticks] until the POWER GOOD flag is set
/* ToDo: Ramp Up Timing is not defined yet and will depend on reference step size and execution interval
 *       syscfg_startup contains a define POWER_UP_RAMP_PERIOD_TICKS whic hcan be used to create a new conversion macro to determine 
 *       the required reference value steps size to meet the user-given ramp up/down time */ 
#define SOFT_START_PRECHARGE_TICKS  10    // Number of bootstrap precharge pulses before ramp up
#define SOFT_START_PCRG_PULSE_DUTY  asm volatile ( "REPEAT #6 \n NOP \n" ) // pulse width ~100ns



/* Soft Start Sequence Definitions */
/*
#define SOFT_START_STEP_INITIALIZE     0   // soft-start phase #0: initialize variables and hijack controller reference
#define SOFT_START_STEP_POWER_ON_DELAY 1   // soft-start phase #1: power on delay (no action)
#define SOFT_START_STEP_PRECHARGE      2   // soft-start phase #2: precharge bootstrap capacitor to ensure proper function of half-bridge switch node
#define SOFT_START_STEP_LAUNCH_V_RAMP  3   // soft-start phase #3: turn on PWM outputs and enable controller
#define SOFT_START_STEP_V_RAMP_UP      4   // soft-start phase #4: perform output voltage ramp up based on parameters and system response 
#define SOFT_START_STEP_I_RAMP_UP      5   // soft-start phase #5: perform output current ramp up based on parameters and system response (average current mode only)
#define SOFT_START_WAIT_FOR_PWRGOOD    6   // soft-start phase #6: Output reached regulation point but waits until things have settled
#define SOFT_START_STEP_COMPLETE       7   // soft-start phase #7: Output in regulation and power is OK
*/
typedef enum {
    SOFT_START_STEP_INITIALIZE     = 0b000,   // soft-start phase #0: initialize variables and hijack controller reference
    SOFT_START_STEP_POWER_ON_DELAY = 0b001,   // soft-start phase #1: power on delay (no action)
    SOFT_START_STEP_PRECHARGE      = 0b010,   // soft-start phase #2: precharge bootstrap capacitor to ensure proper function of half-bridge switch node
    SOFT_START_STEP_LAUNCH_V_RAMP  = 0b011,   // soft-start phase #3: turn on PWM outputs and enable controller
    SOFT_START_STEP_V_RAMP_UP      = 0b100,   // soft-start phase #4: perform output voltage ramp up based on parameters and system response 
    SOFT_START_STEP_I_RAMP_UP      = 0b101,   // soft-start phase #5: perform output current ramp up based on parameters and system response (average current mode only)
    SOFT_START_WAIT_FOR_PWRGOOD    = 0b110,   // soft-start phase #6: Output reached regulation point but waits until things have settled
    SOFT_START_STEP_COMPLETE       = 0b111    // soft-start phase #7: Output in regulation and power is OK
}SOFT_START_PHASE_e;

typedef enum {
    SOFT_START_RAMPDIR_UP     = 0b1,   // soft-start ramp direction #1: output is ramping up
    SOFT_START_RAMPDIR_DOWN   = 0b0    // soft-start ramp direction #0: output is ramping down
}SOFT_START_RAMP_DIRECTION_e;

typedef enum {
    SOFT_START_RAMP_OFF        = 0b00,   // soft-start ramp status #0: ramping in not progress, converter off
    SOFT_START_RAMP_PRECHARGE  = 0b01,   // soft-start ramp status #1: ramping progress is at pre-charge
    SOFT_START_RAMP_ACTIVE     = 0b10,   // soft-start ramp status #2: ramping in progress
    SOFT_START_RAMP_COMPLETE   = 0b11    // soft-start ramp status #3: ramping complete
}SOFT_START_RAMP_STATUS_e;

typedef struct {
    volatile uint16_t v_reference; // Voltage reference dummy for during soft-start control
    volatile uint16_t i_reference; // Current reference dummy for during soft-start control
    volatile uint16_t interval;    // Soft-start step interval in state-machine ticks
    struct {
    volatile SOFT_START_PHASE_e step : 3;               // Bit <0:2>: Most recent soft-start step
    volatile SOFT_START_RAMP_DIRECTION_e direction :1;  // Bit <3>: 0 = RAMP DOWN, 1 = RAMP UP 
    volatile unsigned :10;                              // Bit <4:13>: (reserved)
    volatile SOFT_START_RAMP_STATUS_e ramp_status  :2;  // Bit <14:15>: Flag indicating if the startup ramp has been completed
    };
} CONTROL_SOFT_START_t; // Settings required by the soft-start driver while the converter is ramped up

/* Prototypes */
extern volatile uint16_t init_SoftStart(void);
extern volatile uint16_t exec_SoftStart(void);


#endif	/* _APL_RESOURCES_SOFT_START_H_ */

