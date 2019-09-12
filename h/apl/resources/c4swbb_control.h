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

#include "apl/resources/c4swbb_pconfig.h"   // 4-Switch Buck/Boost Power Control Peripheral Configuration Header
#include "apl/resources/npnz16b.h"          // Generic nPnZ control loop header file

/* Controller Settings */

/* ToDo: Ramp Up Timing is not defined yet and will depend on reference step size and execution interval
 *       syscfg_startup contains a define POWER_UP_RAMP_PERIOD_TICKS which can be used to create a new 
 *       conversion macro to determine the required reference value steps size to meet the user-given 
 *       ramp up/down time */
#define SOFT_START_PRECHARGE_TICKS  10    // Number of bootstrap precharge pulses before ramp up
#define SOFT_START_PCRG_PULSE_DUTY  asm volatile ( "REPEAT #6 \n NOP \n" ) // pulse width ~100ns


/*!C4SWBB_STATUS_t
 * ***************************************************************************************************
 * Summary:
 * Generic data structure for major, publicly accessible controller status information
 * 
 * Description:
 * This data structure is holding common power controller state machine status information.
 * The upper three bits of the status word are used to enable/disable, start or stop the converter.
 * All other bits are read only and may get overridden by the power controller during operation.
 * 
 * *************************************************************************************************** */

/* Power Controller State Machine Status Definitions */
typedef enum {
    CONVERTER_STATE_INITIALIZE = 0b0000, // converter state machine step #0: initialize peripherals, variables and hijack controller reference
    CONVERTER_STATE_STANDBY = 0b0001, // converter state machine step #1: standby mode, power supply is disabled waiting for being enabled (no action)
    CONVERTER_STATE_POWER_ON_DELAY = 0b0010, // converter state machine step #2: power on delay (no action)
    CONVERTER_STATE_PRECHARGE = 0b0011, // converter state machine step #3: pre-charge bootstrap capacitor to ensure proper function of half-bridge switch node
    CONVERTER_STATE_LAUNCH_V_RAMP = 0b0100, // converter state machine step #4: turn on PWM outputs and enable controller
    CONVERTER_STATE_V_RAMP_UP = 0b0101, // converter state machine step #5: perform output voltage ramp up based on parameters and system response 
    CONVERTER_STATE_I_RAMP_UP = 0b0110, // converter state machine step #6: perform output current ramp up based on parameters and system response (average current mode only)
    CONVERTER_STATE_POWER_GOOD = 0b0111, // converter state machine step #7: Output reached regulation point but waits until things have settled
    CONVERTER_STATE_COMPLETE = 0b1000, // converter state machine step #8: Output in regulation and power is OK
    CONVERTER_STATE_RESET = 0b1001, // converter state machine step #9: State machine is pushed in default step causing it to reset to STANDBY (off)
    CONVERTER_STATE_FAULT = 0b1111 // converter state machine step #9: Some fault condition has been detected and the power supply is shut down
} C4SWBB_STATUS_LABEL_e; // Labels of converter state machine steps

/* 16-bit bit masks of converter status bits */
#define C4SWBB_CTRL_STAT_POWERSOURCE_DETECTED   0b0000000000010000
#define C4SWBB_CTRL_STAT_PWM_ACTIVE             0b0000000000100000
#define C4SWBB_CTRL_STAT_ADC_ACTIVE             0b0000000001000000
#define C4SWBB_CTRL_STAT_FAULT_ACTIVE           0b0000000010000000
#define C4SWBB_CTRL_STAT_BUSY                   0b0000000100000000
#define C4SWBB_CTRL_STAT_GO_ACTIVE              0b0010000000000000
#define C4SWBB_CTRL_STAT_AUTORUN_ENABLED        0b0100000000000000
#define C4SWBB_CTRL_STAT_ENABLED                0b1000000000000000

typedef enum {
    CONVERTER_RAMP_DIR_UP = 0b1, // soft-start ramp direction #1: output is ramping up
    CONVERTER_RAMP_DIR_DOWN = 0b0 // soft-start ramp direction #0: output is ramping down
} C4SWBB_RAMP_DIRECTION_e;

typedef struct {
    volatile C4SWBB_STATUS_LABEL_e op_status : 4; // Bit <0:3>: (read only) converter state machine operating status 
    volatile bool power_source_detected : 1; // Bit <4>:  (read only) Status bit indicating that a valid power source has been detected
    volatile bool pwm_active : 1; // Bit <5>:  (read only) Status bit indicating that the PWM outputs have been enabled
    volatile bool adc_active : 1; // Bit <6>: (read only) Status bit indicating that the ADC has been started and is sampling data
    volatile bool fault_active : 1; // Bit <7>: (read only) Status bit indicating that a critical fault condition has been detected
    volatile bool busy : 1; // Bit <9:11>: (read only) Status bit indicating that the state machine is in a ramp or delay phase
    volatile unsigned : 3; // Bit <9:11>: (reserved)
    volatile C4SWBB_RAMP_DIRECTION_e tune_dir : 1; // Bit <12>: (read only) flag indicating the direction of the tune-in ramp when the reference is changed (0=up or 1=down)
    volatile bool GO : 1; // Bit <13>: POWER SUPPLY START bit (will trigger startup procedure when set)
    volatile bool autorun : 1; // Bit <14>: Auto-Start will automatically enable the converter and set the GO bit when ready
    volatile bool enabled : 1; // Bit <15>: Enable-bit (when disabled, power supply will reset in STANDBY mode)
} __attribute__((packed))C4SWBB_STATUS_FLAGS_t;

typedef union {
    volatile uint16_t value; // buffer for 16-bit word read/write operations
    volatile C4SWBB_STATUS_FLAGS_t flags; // data structure for single bit addressing operations
} C4SWBB_STATUS_t; // Power converter operation status bits

/*!C4SWBB_LOOP_SETTINGS_t
 * ***************************************************************************************************
 * Summary:
 * Generic data structure for major, publicly accessible controller remote control settings
 * 
 * Description:
 * This data structure is used to set, monitor or change controller settings from external
 * firmware modules. It covers the basic settings of a power supply control loop such as
 * its reference value, feedback tuning and ADC trigger placement offset, output clamping
 * minimum and maximum values.
 * This data structure may be used for one or multiple loops.
 * 
 * *************************************************************************************************** */
typedef struct {
    volatile cNPNZ16b_t* controller; // pointer to control loop object data structure
    volatile uint16_t (*ctrl_init)(volatile cNPNZ16b_t*); // Function pointer to INIT routine
    void (*ctrl_reset)(volatile cNPNZ16b_t*); // Function pointer to RESET routine
    void (*ctrl_precharge)(volatile cNPNZ16b_t*, volatile uint16_t, volatile uint16_t); // Function pointer to PRECHARGE routine
    void (*ctrl_Update)(volatile cNPNZ16b_t*); // Function pointer to UPDATE routine
    volatile uint16_t feedback_offset; // Feedback offset value for calibration or bidirectional feedback signals
    volatile uint16_t trigger_offset; // ADC trigger offset value for trigger fine-tuning
    volatile uint16_t reference; // Control loop reference variable
    volatile uint16_t minimum; // output voltage clamping value (minimum)
    volatile uint16_t maximum; // output voltage clamping value (maximum)
} __attribute__((packed)) C4SWBB_LOOP_SETTINGS_t; // User defined settings for control loops; 

/*!C4SWBB_STARTUP_SETTINGS_t
 * ***************************************************************************************************
 * Summary:
 * Generic power controller startup settings
 * 
 * Description:
 * This data structure is used to set the startup settings such as power on delay, power good delay
 * and ramp up time. It further covers private values like startup counters and reference values
 * for voltage and current, which are used internally by the controller (read only) but are still
 * accessible for external code modules for monitoring, diagnostics and fault handling purposes.
 * 
 * *************************************************************************************************** */

typedef struct {
    volatile uint16_t counter; // Soft-Start Execution Counter (read only)
    volatile uint16_t pwr_on_delay; // Soft-Start POwer On Delay
    volatile uint16_t precharge_delay; // Soft-Start Bootstrap Capacitor pre-charge delay
    volatile uint16_t ramp_period; // Soft-Start Ramp-Up Duration
    volatile uint16_t ramp_v_ref_increment; // Soft-Start Single Voltage Reference Increment per Step
    volatile uint16_t ramp_i_ref_increment; // Soft-Start Single Current Reference Increment per Step
    volatile uint16_t pwr_good_delay; // Soft-Start Power Good Delay
    volatile uint16_t v_reference; // Soft-Start target voltage loop reference value (read only)
    volatile uint16_t i_reference; // Soft-Start target current loop reference value (read only)
}  __attribute__((packed)) C4SWBB_STARTUP_SETTINGS_t; // Power converter soft-start settings and variables

/*!C4SWBB_SWITCH_NODE_SETTINGS_t
 * ***************************************************************************************************
 * Summary:
 * Generic data structure holding the switch node specification
 * 
 * Description:
 * This data structure is used to set, monitor or change the switch node specification of the
 * power supply, covering half bridge switch timing such as switching frequency, minimum and 
 * maximum on-time of the main switch and dead times between high- and low-side switch of a half-
 * bridge.
 * This data structure may be used for one or multiple half bridge legs.
 * 
 * *************************************************************************************************** */
typedef struct {
    volatile uint16_t pwm_instance; // Instance of the PWM peripheral used (e.g. 1=PG1, 2=PG2, etc.)
    volatile uint16_t period; // Switching period
    volatile uint16_t phase; // Switching signal phase-shift
    volatile uint16_t duty_ratio_init; // Initial duty cycle when the PWM module is being turned on
    volatile uint16_t duty_ratio_min; // Absolute duty cycle minimum during normal operation
    volatile uint16_t duty_ratio_max; // Absolute duty cycle maximum during normal operation
    volatile uint16_t dead_time_rising; // Dead time setting at rising edge of a half-bridge drive
    volatile uint16_t dead_time_falling; // Dead time setting at falling edge of a half-bridge drive
    volatile uint16_t leb_period; // Leading Edge Blanking period 
}  __attribute__((packed)) C4SWBB_SWITCH_NODE_SETTINGS_t; // Switching signal timing settings

/*!C4SWBB_DATA_t
 * ***************************************************************************************************
 * Summary:
 * Data structure holding shadow copies of most recent ADC samples
 * 
 * Description:
 * This data structure holds shadow copies of most recent sample points as global access points 
 * to system operating values, such as input and output voltage, output currents and temperatures.
 * 
 * *************************************************************************************************** */

typedef struct {
    volatile uint16_t i_out; // Power converter output current
    volatile uint16_t v_in; // Power converter input voltage
    volatile uint16_t v_out; // Power converter output voltage
    volatile uint16_t v_ref; // Power converter output voltage reference (user setting)
    volatile uint16_t temp; // Power converter board temperature
}  __attribute__((packed)) C4SWBB_DATA_t; // Power converter runtime data

/*!C4SWBB_POWER_CONTROLLER_t
 * ***************************************************************************************************
 * Summary:
 * Data structure of 4-Switch Buck/Boost Power Controller
 * 
 * Description:
 * This data structure holds all defines, values and setting of a power controller state machine
 * object running a 4-switch buck boost converter DC/DC controller.
 * 
 * *************************************************************************************************** */

typedef struct {
    volatile C4SWBB_STATUS_t status; // Operating status information
    volatile C4SWBB_DATA_t data; // Data structure providing real-time operating data
    volatile C4SWBB_LOOP_SETTINGS_t i_loop; // Current loop control data structure
    volatile C4SWBB_LOOP_SETTINGS_t v_loop; // Voltage loop control data structure
    volatile C4SWBB_SWITCH_NODE_SETTINGS_t boost_leg; // Settings for 4-switch buck/boost converter boost leg
    volatile C4SWBB_SWITCH_NODE_SETTINGS_t buck_leg;  // Settings for 4-switch buck/boost converter buck leg
    volatile C4SWBB_STARTUP_SETTINGS_t soft_start; // Soft-Start settings
} __attribute__((packed)) C4SWBB_POWER_CONTROLLER_t; // Settings, status and operating data of the power controller

     
/* **********************************************************************************************
 *  Code example of how to start/control the power controller in your code
 * 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Hi James: search for your name to find this comment! :-)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *  Step 1: define a power controller somewhere in your project
 *
 *     volatile C4SWBB_POWER_CONTROLLER_t my_supply;
 * 
 *
 *  Step 2: Setting the output voltage reference
 * 
 *     The default output voltage level is +5V. This reference will be set automatically 
 *     during the self-configuration of the 4swbb power controller. Would you like to 
 *     change the reference to some other level, please follow these guidelines:
 * 
 *     a) Power Controller is NOT running yet:
 * 
 *          - write an appropriate 16 bit integer value to 'my_supply.data.v_ref'         
 *          - use the enable and GO bits in the status word to initiate the power up (see Step 3)
 * 
 *     b) Changing output voltage at runtime
 * 
 *          - write an appropriate 16 bit integer value to 'my_supply.data.v_ref'
 *          - when 'autorun' is enabled, the c4swbb power controller will start ramping 
 *            up/down the output voltage in the next state machine tick after this value has 
 *            been changed.
 *          - when 'autorun' is disabled, the c4swbb power controller will wait for the GO bit 
 *            to be set before ramping up/down the output voltage.
 * 
 *     The ramp-up/down period will end after the Power Good period has expired.
 * 
 * 
 *  Step 3: 
 *  
 *   for manual control use the status word of the C4SWBB_POWER_CONTROLLER_t data structure: 
 *
 *      - disable 'autorun'
 *      - set 'enabled = true'
 *        
 *   Now the power controller is in standby mode until you set the GO bit.
 * 
 *      - set 'GO = 1'
 * 
 * 
 *      my_supply.status.flags.autorun = false;
 *      my_supply.status.flags.enabled = true;
 *      my_supply.status.flags.GO = 1;
 * 
 *
 * **********************************************************************************************/

/* Public Function Prototypes */
extern volatile uint16_t reset_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance);
extern volatile uint16_t init_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance);
extern volatile uint16_t exec_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance);
extern volatile uint16_t c4SWBB_shut_down(volatile C4SWBB_POWER_CONTROLLER_t* pInstance);


#endif	/* _APL_RESOURCES_SOFT_START_H_ */

