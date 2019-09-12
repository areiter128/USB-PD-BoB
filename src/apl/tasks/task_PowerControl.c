/*
 * File:   task_PowerControl.c
 * Author: M91406
 *
 * Created on May 27, 2019, 3:11 PM
 */


#include <xc.h>
#include "apl/tasks/task_PowerControl.h"

// Declare two 4-Switch Buck/Boost DC/DC converter objects
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_1;    // USB PD Port A
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_2;    // USB PD Port B


volatile uint16_t exec_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    fres &= exec_4SWBB_PowerController(&c4swbb_1);  // Execute 4-Switch Buck/Boost Converter #1 State Machine
    fres &= exec_4SWBB_PowerController(&c4swbb_2);  // Execute 4-Switch Buck/Boost Converter #2 State Machine
    
    return (fres);
}

/*!init_PowerControl
 *  ******************************************************************************************************
 *
 * 
 * *****************************************************************************************************/

volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;

    // Run global/common, non-converter specific peripheral module configuration
//    fres &= initialize_adc();
//    fres &= c4swbb_pwm_initialize();
    
    c4swbb_pwm_module_initialize();
    
    //    c4swbb_2 = c4swbb_1;
    
//    init_4SWBB_PowerController(&c4swbb_2);  // Initialize power controller of USB port 2
    
    return (fres);
}

volatile uint16_t init_USBport_1(void) {

    volatile uint16_t fres=1;
    
    /* Initializing 4SW-BB DC/DC converter at USB port A */
    reset_4SWBB_PowerController(&c4swbb_1);  // Initialize power controller of USB port 1
    
    // Set PWM settings
    c4swbb_1.buck_leg.pwm_instance = BUCKH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.buck_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_1.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.buck_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_1.buck_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_1.buck_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_1.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period

    c4swbb_1.boost_leg.pwm_instance = BOOSTH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.boost_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_1.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.boost_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_1.boost_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_1.boost_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_1.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    
    // Initialize converter #1 voltage loop settings

    // Initializing the hardware-specific settings into data structure
    // Initialize basic controller settings of voltage loop object
    cha_vloop_Init(&cha_vloop);

    c4swbb_1.v_loop.minimum = IOUT_LCL_CLAMP;   // Minimum output value of voltage loop is absolute current limit
    c4swbb_1.v_loop.maximum = IOUT_OCL_TRIP;    // Maximum output value of voltage loop is absolute current limit
    c4swbb_1.v_loop.feedback_offset = C4SWBB_VOUT_OFFSET;   // Voltage feedback signal offset
    c4swbb_1.v_loop.reference = C4SWBB_VOUT_REF; // Voltage loop reference value
    c4swbb_1.v_loop.trigger_offset = ADC_TRIG_OFFSET_VOUT; // Voltage sample ADC trigger offset (offset from 50% on-time)

    
    // Assign voltage loop object to 4-switch buck/boost converter instance
    c4swbb_1.v_loop.controller = &cha_vloop;        // 4-Switch Buck/Boost converter voltage loop controller

    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.v_loop.ctrl_init = &cha_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.v_loop.ctrl_Update = &cha_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.v_loop.ctrl_precharge = &cha_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.v_loop.ctrl_reset = &cha_vloop_Reset;     // Function pointer to CONTROL RESET routine
    

    
    

    
    // Initialize converter #1 current loop settings
    cha_iloop_Init(&cha_iloop);
    
    c4swbb_1.i_loop.controller = &cha_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_1.i_loop.minimum = DUTY_RATIO_MIN_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.maximum = DUTY_RATIO_MAX_REG;   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_1.i_loop.reference = IOUT_LCL_CLAMP; // Current loop reference value
    c4swbb_1.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)
    
    // Initialize USB Port #1 Soft Start Settings
    c4swbb_1.soft_start.pwr_on_delay = C4SWBB_PODLY;    // Power-On Delay
    c4swbb_1.soft_start.ramp_period = C4SWBB_RPER;      // Ramp-Up Period
    c4swbb_1.soft_start.pwr_good_delay = C4SWBB_PGDLY;  // Power-Good Delay
    c4swbb_1.soft_start.ramp_v_ref_increment = C4SWBB_VREF_STEP; // Voltage reference tick increment to meet ramp period setting
    c4swbb_1.soft_start.ramp_i_ref_increment = C4SWBB_IREF_STEP; // Current reference tick increment to meet ramp period setting

    // Reset runtime data output of USB port #1
    c4swbb_1.data.v_in = 0;     // Reset input current value
    c4swbb_1.data.i_out = 0;    // Reset output current value
    c4swbb_1.data.v_out = 0;    // Reset output voltage value
    c4swbb_1.data.temp = 0;     // Reset converter temperature value
    
    return(fres);
    
}

volatile uint16_t init_USBport_2(void) {

    volatile uint16_t fres=1;
    
    /* Initializing 4SW-BB DC/DC converter at USB port B */
    init_4SWBB_PowerController(&c4swbb_2);  // Initialize power controller of USB port 2
    
    // Set PWM settings
    c4swbb_2.buck_leg.pwm_instance = BUCKH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.buck_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_2.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.buck_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_2.buck_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_2.buck_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_2.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period

    c4swbb_2.boost_leg.pwm_instance = BOOSTH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.boost_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_2.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.boost_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_2.boost_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_2.boost_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_2.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
   
    // Initialize converter #1 voltage loop settings
    chb_vloop_Init(&chb_vloop);
    
    c4swbb_2.v_loop.controller = &chb_vloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_2.v_loop.minimum = IOUT_LCL_CLAMP;   // Minimum output value of voltage loop is absolute current limit
    c4swbb_2.v_loop.maximum = IOUT_OCL_TRIP;    // Maximum output value of voltage loop is absolute current limit
    c4swbb_2.v_loop.feedback_offset = C4SWBB_VOUT_OFFSET;   // Voltage feedback signal offset
    c4swbb_2.v_loop.reference = C4SWBB_VOUT_REF; // Voltage loop reference value
    c4swbb_2.v_loop.trigger_offset = ADC_TRIG_OFFSET_VOUT; // Voltage sample ADC trigger offset (offset from 50% on-time)

    // Initialize converter #1 current loop settings
    chb_iloop_Init(&chb_iloop);
    
    c4swbb_2.i_loop.controller = &chb_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_2.i_loop.minimum = DUTY_RATIO_MIN_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.maximum = DUTY_RATIO_MAX_REG;   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_2.i_loop.reference = IOUT_LCL_CLAMP; // Current loop reference value
    c4swbb_2.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)
   
    // Initialize USB Port #1 Soft Start Settings
    c4swbb_2.soft_start.pwr_on_delay = C4SWBB_PODLY;    // Power-On Delay
    c4swbb_2.soft_start.ramp_period = C4SWBB_RPER;      // Ramp-Up Period
    c4swbb_2.soft_start.pwr_good_delay = C4SWBB_PGDLY;  // Power-Good Delay
    c4swbb_2.soft_start.ramp_v_ref_increment = C4SWBB_VREF_STEP; // Voltage reference tick increment to meet ramp period setting
    c4swbb_2.soft_start.ramp_i_ref_increment = C4SWBB_IREF_STEP; // Current reference tick increment to meet ramp period setting
    
    // Reset runtime data output of USB port #1
    c4swbb_2.data.v_in = 0;     // Reset input current value
    c4swbb_2.data.i_out = 0;    // Reset output current value
    c4swbb_2.data.v_out = 0;    // Reset output voltage value
    c4swbb_2.data.temp = 0;     // Reset converter temperature value
   
    return(fres);
    
}

