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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_TASK_POWER_CONTROL_H
#define	APL_TASK_POWER_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "hal/hal.h"
#include "mcal/mcal.h"

#include "apl/resources/soft_start.h"

#include "apl/resources/cvmc_cha.h"
#include "apl/resources/cacmc_cha.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typedef struct {
    volatile uint16_t reference; // Control loop reference variable
    volatile uint16_t feedback_offset; // Feedback offset value for calibration or bi-direction feedback signals
    volatile uint16_t trigger_offset; // ADC trigger offset value for trigger fine-tuning
    volatile uint16_t minimum; // output clamping value (minimum)
    volatile uint16_t maximum; // output clamping value (maximum)
} PWRCTRL_4SWBB_LOOP_SETTINGS_t; // User defined settings for control loops; 

typedef struct {
    volatile uint16_t period; // Switching period
    volatile uint16_t phase; // Switching signal phase-shift
    volatile uint16_t duty_ratio_init; // Initial duty cycle when the PWM module is being turned on
    volatile uint16_t duty_ratio_min; // Absolute duty cycle minimum during normal operation
    volatile uint16_t duty_ratio_max; // Absolute duty cycle maximum during normal operation
    volatile uint16_t dead_time_rising; // Dead time setting at rising edge of a half-bridge drive
    volatile uint16_t dead_time_falling; // Dead time setting at falling edge of a half-bridge drive
} PWRCTRL_4SWBB_SWITCHING_TIMING_SETTINGS_t; // Switching signal timing settings

typedef struct {
    volatile uint16_t v_in;  // power supply input voltage (template only)
    volatile uint16_t i_in;  // power supply input current (template only)
    volatile uint16_t v_out_cha;  // power supply output voltage (channel A)
    volatile uint16_t i_out_cha;  // power supply output current (channel A)
    volatile uint16_t temperature_a; // board temperature (template only)
    volatile uint16_t v_out_chb;  // power supply output voltage (channel A)
    volatile uint16_t i_out_chb;  // power supply output current (channel A)
    volatile uint16_t temperature_b; // board temperature (template only)
} APPLICATION_DATA_t; // Application real-time data value list (voltages, currents, etc.)

#define CTRL_STAT_POWERSOURCE_DETECTED  0b0000000000000001
#define CTRL_STAT_PWM_STARTED           0b0000000000000010
#define CTRL_STAT_ADC_ACTIVE            0b0000000000000100

#define CTRL_STAT_FORCED_SHUT_DOWN      0b0010000000000000
#define CTRL_STAT_SYSTEM_STARTUP        0b0100000000000010
#define CTRL_STAT_SYSTEM_READY          0b1000000000000000

typedef struct{

	volatile bool power_source_detected:1;	// Bit #0:  indicating that a valid power source was detected
	volatile bool pwm_started:1;	// Bit #1:  indicating that PWM has been started and ADC triggers are generated
	volatile bool adc_active:1;	    // Bit #2:  indicating that ADC has been started and samples are taken
	volatile unsigned :1;   // Bit #3: (reserved)
	volatile unsigned :1;	// Bit #4: (reserved)
	volatile unsigned :1;	// Bit #5:  (reserved)
	volatile unsigned :1;	// Bit #6:  (reserved)
	volatile unsigned :1;	// Bit #7:  (reserved)
    
	volatile unsigned :1;	// Bit #8:  (reserved)
	volatile unsigned :1;	// Bit #9:  (reserved)
	volatile unsigned :1;	// Bit #10: (reserved)
	volatile unsigned :1;	// Bit #11: (reserved)
	volatile unsigned :1;	// Bit #12: (reserved)
    volatile bool forced_shut_down :1; // Bit #13: Flag bit indicating system is in enforced shut down mode (usually due to a fault condition)
	volatile bool system_startup:1;	// Bit #14:  indicating a system startup procedure
	volatile bool system_ready:1;	// Bit #15:  indicating that system startup is complete
} PWRCTRL_4SWBB_STATUS_BIT_FIELD_t;

typedef union 
{
	volatile uint16_t value; // buffer for 16-bit word read/write operations
	volatile PWRCTRL_4SWBB_STATUS_BIT_FIELD_t flags; // data structure for single bit addressing operations
} PWRCTRL_4SWBB_STATUS_t;

    
typedef struct {
    volatile PWRCTRL_4SWBB_STATUS_t status; 
} __attribute__((packed))PWRCTRL_4SWBB_t;    
    
    


// Public function prototypes
extern volatile uint16_t init_PowerControl(void);
extern volatile uint16_t exec_PowerControl(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* APL_TASK_POWER_CONTROL_H */

