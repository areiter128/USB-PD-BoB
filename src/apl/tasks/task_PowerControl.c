/*
 * File:   task_PowerControl.c
 * Author: M91406
 *
 * Created on May 27, 2019, 3:11 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "apl/tasks/task_PowerControl.h"

// Declare two 4-Switch Buck/Boost DC/DC converter objects
volatile C4SWBB_PWRCTRL_t c4swbb_1;    // USB PD Port A
volatile C4SWBB_PWRCTRL_t c4swbb_2;    // USB PD Port B

// PRIVATE FUNCTION PROTOTYPES
volatile uint16_t init_USBport_1(void);
volatile uint16_t init_USBport_2(void);

volatile uint16_t init_ISR_USBport_1(void);
volatile uint16_t init_ISR_USBport_2(void);

/*!exec_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t exec_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    fres &= exec_4SWBB_PowerController(&c4swbb_1);  // Execute 4-Switch Buck/Boost Converter #1 State Machine
    fres &= exec_4SWBB_PowerController(&c4swbb_2);  // Execute 4-Switch Buck/Boost Converter #2 State Machine
    
    return (fres);
}

/*!init_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;

    // Initialize the 4-switch buck/boost power controller objects for USB port A and B
    fres &= init_USBport_1(); // Initialize complete configuration of USB Port 1 power controller
    fres &= init_USBport_2(); // Initialize complete configuration of USB Port 2 power controller
    
    // Initialize PWM module base registers:
    // =====================================
    // This only needs to be called once at startup and applies to both USB PD ports.
    // The only setting of the data structure used in this routine is the 
    // PWM period, which is written into the master time base period register MPER
    fres &= c4swbb_pwm_module_initialize(&c4swbb_1);
    
    // Load PWM configurations for PWM generators for both ports
    fres &= c4swbb_pwm_generators_initialize(&c4swbb_1); // Initialize PWM generators of USB Port A
    fres &= c4swbb_pwm_generators_initialize(&c4swbb_2); // Initialize PWM generators of USB Port B

    // ADC core configuration
    fres &= c4swbb_adc_module_initialize();
    
//    // Initialize all ADC input channels of one power controller
    fres &= c4swbb_adc_inputs_initialize(&c4swbb_1);
    fres &= c4swbb_adc_inputs_initialize(&c4swbb_2);

    // Initialize analog inputs and analog input interrupts
    fres &= init_ISR_USBport_1();
    fres &= init_ISR_USBport_2();

    // Enable ADC module and all ADC cores used
    fres &= c4swbb_adc_enable();
    
    // Enable PWM module starting to trigger the ADC while outputs are 
    // still disabled
    fres &= c4swbb_pwm_hold(&c4swbb_1);
    fres &= c4swbb_pwm_hold(&c4swbb_2);
    
    fres &= c4swbb_pwm_enable(&c4swbb_1);
    fres &= c4swbb_pwm_enable(&c4swbb_2);
    
    // return Success/Failure
    return (fres);
}

/*!reset_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t reset_PowerControl(void) {
    
    volatile uint16_t fres = 0;
    
    fres &= c4SWBB_shut_down(&c4swbb_1);  // Shut Down 4-Switch Buck/Boost Converter #1 State Machine
    fres &= c4SWBB_shut_down(&c4swbb_2);  // Shut Down 4-Switch Buck/Boost Converter #2 State Machine
    
    return(fres);
}

/*!init_ISR_USBport_1
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t init_ISR_USBport_1(void) {

    volatile uint16_t fres = 1;
    volatile uint16_t dummy_read=0;

    // Configure ADC input pins and interrupts
    FB_VOUT1_INIT_ANALOG; // Output voltage converter #1 feedback pin
    FB_VOUT1_ADC_IP = c4swbb_1.feedback.ad_vout.interrupt_priority; // Set interrupt priority
    dummy_read = FB_VOUT1_ADCBUF; // Dummy-read the ADC buffer
    FB_VOUT1_ADC_IF = 0; // Clear interrupt flag bit
    FB_VOUT1_ADC_IE = c4swbb_1.feedback.ad_vout.interrupt_enable; // Enable/Disable interrupt service routine

    // Configure ADC input pin and interrupt
    FB_IOUT1_INIT_ANALOG; // Output current converter #1 feedback pin
    FB_IOUT1_ADC_IP = c4swbb_1.feedback.ad_iout.interrupt_priority; // Set interrupt priority
    dummy_read = FB_IOUT1_ADCBUF; // Dummy-read the ADC buffer
    FB_IOUT1_ADC_IF = 0; // Clear interrupt flag bit
    FB_IOUT1_ADC_IE = c4swbb_1.feedback.ad_iout.interrupt_enable; // Enable/Disable interrupt service routine

    // Configure ADC input pin and interrupt
    FB_TEMP1_INIT_ANALOG; // Temperature converter #1 feedback pin
    FB_TEMP1_ADC_IP = c4swbb_1.feedback.ad_temp.interrupt_priority; // Set interrupt priority
    dummy_read = FB_TEMP1_ADCBUF; // Dummy-read the ADC buffer
    FB_TEMP1_ADC_IF = 0; // Clear interrupt flag bit
    FB_TEMP1_ADC_IE = c4swbb_1.feedback.ad_temp.interrupt_enable; // Enable/Disable interrupt service routine

    FB_VBAT_INIT_ANALOG; // Input voltage feedback pin
    FB_VBAT_ADC_IP = c4swbb_1.feedback.ad_vin.interrupt_priority; // Set interrupt priority
    dummy_read = FB_VBAT_ADCBUF; // Dummy-read the ADC buffer
    FB_VBAT_ADC_IF = 0;  // Clear interrupt flag bit
    FB_VBAT_ADC_IE = c4swbb_1.feedback.ad_vin.interrupt_enable; // Enable/Disable interrupt service routine

    return(fres);
}

/*!init_ISR_USBport_2
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t init_ISR_USBport_2(void) {

    volatile uint16_t fres = 1;
    volatile uint16_t dummy_read=0;

    // Configure ADC input pins and interrupts
    FB_VOUT2_INIT_ANALOG; // Output voltage converter #1 feedback pin
    FB_VOUT2_ADC_IP = c4swbb_2.feedback.ad_vout.interrupt_priority; // Set interrupt priority
    dummy_read = FB_VOUT2_ADCBUF; // Dummy-read the ADC buffer
    FB_VOUT2_ADC_IF = 0; // Clear interrupt flag bit
    FB_VOUT2_ADC_IE = c4swbb_2.feedback.ad_vout.interrupt_enable; // Enable/Disable interrupt service routine

    // Configure ADC input pin and interrupt
    FB_IOUT2_INIT_ANALOG; // Output current converter #1 feedback pin
    FB_IOUT2_ADC_IP = c4swbb_2.feedback.ad_iout.interrupt_priority; // Set interrupt priority
    dummy_read = FB_IOUT2_ADCBUF; // Dummy-read the ADC buffer
    FB_IOUT2_ADC_IF = 0; // Clear interrupt flag bit
    FB_IOUT2_ADC_IE = c4swbb_2.feedback.ad_iout.interrupt_enable; // Enable/Disable interrupt service routine

    // Configure ADC input pin and interrupt
    FB_TEMP2_INIT_ANALOG; // Temperature converter #1 feedback pin
    FB_TEMP2_ADC_IP = c4swbb_2.feedback.ad_temp.interrupt_priority; // Set interrupt priority
    dummy_read = FB_TEMP2_ADCBUF; // Dummy-read the ADC buffer
    FB_TEMP2_ADC_IF = 0; // Clear interrupt flag bit
    FB_TEMP2_ADC_IE = c4swbb_2.feedback.ad_temp.interrupt_enable; // Enable/Disable interrupt service routine

    // Initialization of this shared signal is covered by converter #1
//    FB_VBAT_INIT_ANALOG; // Input voltage feedback pin
//    FB_VBAT_ADC_IP = c4swbb_2.feedback.ad_vin.interrupt_priority; // Set interrupt priority
//    dummy_read = FB_VBAT_ADCBUF; // Dummy-read the ADC buffer
//    FB_VBAT_ADC_IF = 0;  // Clear interrupt flag bit
//    FB_VBAT_ADC_IE = c4swbb_2.feedback.ad_vin.interrupt_enable; // Enable/Disable interrupt service routine
    
    
    return(fres);
}

/*!init_USBport_1
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t init_USBport_1(void) {

    volatile uint16_t fres=1;

    
    /* Initializing 4SW-BB DC/DC converter at USB port A */
    fres &= reset_4SWBB_PowerController(&c4swbb_1);  // Initialize power controller of USB port 1
    
    // Load PWM settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_1.buck_leg.pwm_instance = BUCKH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.buck_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_1.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.buck_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_1.buck_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_1.buck_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_1.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_1.buck_leg.pwm_swap = false; // PWMxH and PWMxL are not swapped for buck converter operation
    c4swbb_1.buck_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW

    c4swbb_1.boost_leg.pwm_instance = BOOSTH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.boost_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_1.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.boost_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_1.boost_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_1.boost_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_1.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_1.boost_leg.pwm_swap = true; // PWMxH and PWMxL are swapped for boost converter operation
    c4swbb_1.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    
    // Load ADC settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_1.feedback.ad_vout.enable = true;
    c4swbb_1.feedback.ad_vout.adin_no = FB_VOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vout.adc_core = FB_VOUT1_ADCCORE;
    c4swbb_1.feedback.ad_vout.ptrADBUF = &FB_VOUT1_ADCBUF;
    c4swbb_1.feedback.ad_vout.early_interrupt_enable = true;
    c4swbb_1.feedback.ad_vout.interrupt_enable = true;
    c4swbb_1.feedback.ad_vout.interrupt_priority = FB_VOUT1_ISR_PRIORITY;
    c4swbb_1.feedback.ad_vout.trigger_source = BUCKH1_ADC_TRGSRC_1;
    
    c4swbb_1.feedback.ad_iout.enable = true;
    c4swbb_1.feedback.ad_iout.adin_no = FB_IOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_iout.adc_core = FB_IOUT1_ADCCORE;
    c4swbb_1.feedback.ad_iout.ptrADBUF = &FB_IOUT1_ADCBUF;
    c4swbb_1.feedback.ad_iout.trigger_source = BUCKH1_ADC_TRGSRC_2;
    c4swbb_1.feedback.ad_iout.early_interrupt_enable = true;
    c4swbb_1.feedback.ad_iout.interrupt_enable = true;
    c4swbb_1.feedback.ad_iout.interrupt_priority = FB_IOUT1_ISR_PRIORITY;
    
    c4swbb_1.feedback.ad_vin.enable = true;
    c4swbb_1.feedback.ad_vin.adin_no = FB_VBAT_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vin.adc_core = FB_VBAT_ADCCORE;
    c4swbb_1.feedback.ad_vin.ptrADBUF = &FB_VBAT_ADCBUF;
    c4swbb_1.feedback.ad_vin.trigger_source = BUCKH1_ADC_TRGSRC_2;
    c4swbb_1.feedback.ad_vin.early_interrupt_enable = true;
    c4swbb_1.feedback.ad_vin.interrupt_enable = false;
    c4swbb_1.feedback.ad_vin.interrupt_priority = FB_VBAT_ISR_PRIORITY;
    
    c4swbb_1.feedback.ad_temp.enable = true;
    c4swbb_1.feedback.ad_temp.adin_no = FB_TEMP1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_temp.adc_core = FB_TEMP1_ADCCORE;
    c4swbb_1.feedback.ad_temp.ptrADBUF = &FB_TEMP1_ADCBUF;
    c4swbb_1.feedback.ad_temp.trigger_source = BUCKH1_ADC_TRGSRC_2;
    c4swbb_1.feedback.ad_temp.early_interrupt_enable = true;
    c4swbb_1.feedback.ad_temp.interrupt_enable = false;
    c4swbb_1.feedback.ad_temp.interrupt_priority = FB_TEMP1_ISR_PRIORITY;

    // Initialize converter #1 voltage loop controller settings

    // Initialize basic controller settings of voltage loop object
    fres &= cha_vloop_Init(&cha_vloop);

    // Hardware-specific voltage loop controller settings
    c4swbb_1.v_loop.minimum = IOUT_LCL_CLAMP;   // Minimum output value of voltage loop is absolute current limit
    c4swbb_1.v_loop.maximum = IOUT_OCL_TRIP;    // Maximum output value of voltage loop is absolute current limit
    c4swbb_1.v_loop.feedback_offset = C4SWBB_VOUT_OFFSET;   // Voltage feedback signal offset
    c4swbb_1.v_loop.reference = C4SWBB_VOUT_REF; // Voltage loop reference value
    c4swbb_1.v_loop.trigger_offset = ADC_TRIG_OFFSET_VOUT; // Voltage sample ADC trigger offset (offset from 50% on-time)
    
    // Assign voltage loop object to 4-switch buck/boost converter instance
    c4swbb_1.v_loop.controller = &cha_vloop;        // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_1.v_loop.controller->ptrSource = &FB_VOUT1_ADCBUF; // Load pointer to user data input source
    c4swbb_1.v_loop.controller->ptrTarget = &c4swbb_1.i_loop.reference; // Load pointer to user data output target
    c4swbb_1.v_loop.controller->ptrControlReference = &c4swbb_1.v_loop.reference; // Set pointer to user reference
    c4swbb_1.v_loop.controller->MinOutput = c4swbb_1.v_loop.minimum; // Load user minimum value
    c4swbb_1.v_loop.controller->MaxOutput = c4swbb_1.v_loop.maximum; // Load user maximum value
    c4swbb_1.v_loop.controller->InputOffset = c4swbb_1.v_loop.feedback_offset; // Load user feedback offset value
    c4swbb_1.v_loop.controller->ADCTriggerOffset = c4swbb_1.v_loop.trigger_offset; // Load user trigger offset value
    c4swbb_1.v_loop.controller->ptrADCTriggerRegister = &BOOSTH1_PGxTRIGA; // Load pointer to ADC trigger register
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.v_loop.ctrl_Init = &cha_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.v_loop.ctrl_Update = &cha_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.v_loop.ctrl_Precharge = &cha_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.v_loop.ctrl_Reset = &cha_vloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_1.v_loop.ctrl_Reset(&cha_vloop); // Call RESET routine of voltage loop controller

    // Initialize converter #1 current loop settings
    fres &= cha_iloop_Init(&cha_iloop);
    
    c4swbb_1.i_loop.minimum = DUTY_RATIO_MIN_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.maximum = DUTY_RATIO_MAX_REG;   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_1.i_loop.reference = IOUT_LCL_CLAMP; // Current loop reference value
    c4swbb_1.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)
    
    c4swbb_1.i_loop.controller = &cha_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_1.i_loop.controller->ptrSource = &FB_IOUT1_ADCBUF; // Set pointer to data input source
    c4swbb_1.i_loop.controller->ptrTarget = &BUCKH1_PGx_DC; // Set pointer to data output target
    c4swbb_1.i_loop.controller->ptrControlReference = &c4swbb_1.i_loop.reference; // Set pointer to user reference
    c4swbb_1.i_loop.controller->MinOutput = c4swbb_1.i_loop.minimum; // Load user minimum value
    c4swbb_1.i_loop.controller->MaxOutput = c4swbb_1.i_loop.maximum; // Load user maximum value
    c4swbb_1.i_loop.controller->InputOffset = c4swbb_1.i_loop.feedback_offset; // Load user feedback offset value
    c4swbb_1.i_loop.controller->ADCTriggerOffset = c4swbb_1.i_loop.trigger_offset; // Load user trigger offset value
    c4swbb_1.i_loop.controller->ptrADCTriggerRegister = &BUCKH1_PGxTRIGA; // Load pointer to ADC trigger register
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.i_loop.ctrl_Init = &cha_iloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.i_loop.ctrl_Update = &cha_iloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.i_loop.ctrl_Precharge = &cha_iloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.i_loop.ctrl_Reset = &cha_iloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_1.i_loop.ctrl_Reset(&cha_iloop); // Call RESET routine of voltage loop controller
    
    // Initialize USB Port #1 Soft Start Settings
    c4swbb_1.soft_start.pwr_on_delay = C4SWBB_PODLY;    // Power-On Delay
    c4swbb_1.soft_start.ramp_period = C4SWBB_RPER;      // Ramp-Up Period
    c4swbb_1.soft_start.pwr_good_delay = C4SWBB_PGDLY;  // Power-Good Delay
    c4swbb_1.soft_start.ramp_v_ref_increment = C4SWBB_VREF_STEP; // Voltage reference tick increment to meet ramp period setting
    c4swbb_1.soft_start.ramp_i_ref_increment = C4SWBB_IREF_STEP; // Current reference tick increment to meet ramp period setting
    c4swbb_1.soft_start.inrush_limit = IOUT_INRUSH_CLAMP; // Set soft-start inrush current limit

    
    // Reset runtime data output of USB port #1
    c4swbb_1.data.v_in = 0;     // Reset input current value
    c4swbb_1.data.i_out = 0;    // Reset output current value
    c4swbb_1.data.v_out = 0;    // Reset output voltage value
    c4swbb_1.data.temp = 0;     // Reset converter temperature value
    
    return(fres);
    
}

/*!init_USBport_2
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

inline volatile uint16_t init_USBport_2(void) {

    volatile uint16_t fres=1;
    
    /* Initializing 4SW-BB DC/DC converter at USB port B */
    fres &= reset_4SWBB_PowerController(&c4swbb_2);  // Initialize power controller of USB port 1
    
    // Load PWM settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_2.buck_leg.pwm_instance = BUCKH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.buck_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_2.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.buck_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_2.buck_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_2.buck_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_2.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_2.buck_leg.pwm_swap = 0; // PWMxH and PWMxL are not swapped for buck converter operation
    c4swbb_2.buck_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW

    c4swbb_2.boost_leg.pwm_instance = BOOSTH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.boost_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_2.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.boost_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_2.boost_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_2.boost_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_2.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_2.boost_leg.pwm_swap = 1; // PWMxH and PWMxL are swapped for boost converter operation
    c4swbb_2.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    
    // Load ADC settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_2.feedback.ad_vout.enable = true;
    c4swbb_2.feedback.ad_vout.adin_no = FB_VOUT2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_vout.adc_core = FB_VOUT2_ADCCORE;
    c4swbb_2.feedback.ad_vout.ptrADBUF = &FB_VOUT2_ADCBUF;
    c4swbb_2.feedback.ad_vout.trigger_source = BUCKH2_ADC_TRGSRC_1;
    c4swbb_2.feedback.ad_vout.early_interrupt_enable = true;
    c4swbb_2.feedback.ad_vout.interrupt_enable = true;
    c4swbb_2.feedback.ad_vout.interrupt_priority = FB_VOUT2_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_iout.enable = true;
    c4swbb_2.feedback.ad_iout.adin_no = FB_IOUT2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_iout.adc_core = FB_IOUT2_ADCCORE;
    c4swbb_2.feedback.ad_iout.ptrADBUF = &FB_IOUT2_ADCBUF;
    c4swbb_2.feedback.ad_iout.trigger_source = BUCKH2_ADC_TRGSRC_2;
    c4swbb_2.feedback.ad_iout.early_interrupt_enable = true;
    c4swbb_2.feedback.ad_iout.interrupt_enable = true;
    c4swbb_2.feedback.ad_iout.interrupt_priority = FB_IOUT2_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_vin.enable = false;
    c4swbb_2.feedback.ad_vin.adin_no = FB_VBAT_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_vin.adc_core = FB_VBAT_ADCCORE;
    c4swbb_2.feedback.ad_vin.ptrADBUF = &FB_VBAT_ADCBUF;
    c4swbb_2.feedback.ad_vin.trigger_source = BUCKH1_ADC_TRGSRC_2;
    c4swbb_2.feedback.ad_vin.early_interrupt_enable = true;
    c4swbb_2.feedback.ad_vin.interrupt_enable = false;
    c4swbb_2.feedback.ad_vin.interrupt_priority = FB_VBAT_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_temp.enable = true;
    c4swbb_2.feedback.ad_temp.adin_no = FB_TEMP2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_temp.adc_core = FB_TEMP2_ADCCORE;
    c4swbb_2.feedback.ad_temp.ptrADBUF = &FB_TEMP2_ADCBUF;
    c4swbb_2.feedback.ad_temp.trigger_source = BUCKH2_ADC_TRGSRC_2;
    c4swbb_2.feedback.ad_temp.early_interrupt_enable = true;
    c4swbb_2.feedback.ad_temp.interrupt_enable = false;
    c4swbb_2.feedback.ad_temp.interrupt_priority = FB_TEMP2_ISR_PRIORITY;

    // Initialize converter #1 voltage loop controller settings

    // Initialize basic controller settings of voltage loop object
    fres &= cha_vloop_Init(&chb_vloop);

    // Hardware-specific voltage loop controller settings
    c4swbb_2.v_loop.minimum = IOUT_LCL_CLAMP;   // Minimum output value of voltage loop is absolute current limit
    c4swbb_2.v_loop.maximum = IOUT_OCL_TRIP;    // Maximum output value of voltage loop is absolute current limit
    c4swbb_2.v_loop.feedback_offset = C4SWBB_VOUT_OFFSET;   // Voltage feedback signal offset
    c4swbb_2.v_loop.reference = C4SWBB_VOUT_REF; // Voltage loop reference value
    c4swbb_2.v_loop.trigger_offset = ADC_TRIG_OFFSET_VOUT; // Voltage sample ADC trigger offset (offset from 50% on-time)
    
    // Assign voltage loop object to 4-switch buck/boost converter instance
    c4swbb_2.v_loop.controller = &chb_vloop;        // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_2.v_loop.controller->ptrSource = &FB_VOUT2_ADCBUF; // Load pointer to user data input source
    c4swbb_2.v_loop.controller->ptrTarget = &c4swbb_2.i_loop.reference; // Load pointer to user data output target
    c4swbb_2.v_loop.controller->ptrControlReference = &c4swbb_2.v_loop.reference; // Set pointer to user reference
    c4swbb_2.v_loop.controller->MinOutput = c4swbb_2.v_loop.minimum; // Load user minimum value
    c4swbb_2.v_loop.controller->MaxOutput = c4swbb_2.v_loop.maximum; // Load user maximum value
    c4swbb_2.v_loop.controller->InputOffset = c4swbb_2.v_loop.feedback_offset; // Load user feedback offset value
    c4swbb_2.v_loop.controller->ADCTriggerOffset = c4swbb_2.v_loop.trigger_offset; // Load user trigger offset value
    c4swbb_2.v_loop.controller->ptrADCTriggerRegister = &BOOSTH2_PGxTRIGA; // Load pointer to ADC trigger register
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_2.v_loop.ctrl_Init = &chb_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_2.v_loop.ctrl_Update = &chb_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_2.v_loop.ctrl_Precharge = &chb_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_2.v_loop.ctrl_Reset = &chb_vloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_2.v_loop.ctrl_Reset(&chb_vloop); // Call RESET routine of voltage loop controller

    // Initialize converter #2 current loop settings
    fres &= cha_iloop_Init(&chb_iloop);

    c4swbb_2.i_loop.minimum = DUTY_RATIO_MIN_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.maximum = DUTY_RATIO_MAX_REG;   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_2.i_loop.reference = IOUT_LCL_CLAMP; // Current loop reference value
    c4swbb_2.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)
    
    c4swbb_2.i_loop.controller = &chb_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_2.i_loop.controller->ptrSource = &FB_IOUT2_ADCBUF; // Set pointer to data input source
    c4swbb_2.i_loop.controller->ptrTarget = &BUCKH2_PGx_DC; // Set pointer to data output target
    c4swbb_2.i_loop.controller->ptrControlReference = &c4swbb_2.i_loop.reference; // Set pointer to user reference
    c4swbb_2.i_loop.controller->MinOutput = c4swbb_2.i_loop.minimum; // Load user minimum value
    c4swbb_2.i_loop.controller->MaxOutput = c4swbb_2.i_loop.maximum; // Load user maximum value
    c4swbb_2.i_loop.controller->InputOffset = c4swbb_2.i_loop.feedback_offset; // Load user feedback offset value
    c4swbb_2.i_loop.controller->ADCTriggerOffset = c4swbb_2.i_loop.trigger_offset; // Load user trigger offset value
    c4swbb_2.i_loop.controller->ptrADCTriggerRegister = &BUCKH2_PGxTRIGA; // Load pointer to ADC trigger register
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_2.i_loop.ctrl_Init = &chb_iloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_2.i_loop.ctrl_Update = &chb_iloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_2.i_loop.ctrl_Precharge = &chb_iloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_2.i_loop.ctrl_Reset = &chb_iloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_2.i_loop.ctrl_Reset(&chb_iloop); // Call RESET routine of voltage loop controller
    
    // Initialize USB Port #1 Soft Start Settings
    c4swbb_2.soft_start.pwr_on_delay = C4SWBB_PODLY;    // Power-On Delay
    c4swbb_2.soft_start.ramp_period = C4SWBB_RPER;      // Ramp-Up Period
    c4swbb_2.soft_start.pwr_good_delay = C4SWBB_PGDLY;  // Power-Good Delay
    c4swbb_2.soft_start.ramp_v_ref_increment = C4SWBB_VREF_STEP; // Voltage reference tick increment to meet ramp period setting
    c4swbb_2.soft_start.ramp_i_ref_increment = C4SWBB_IREF_STEP; // Current reference tick increment to meet ramp period setting
    c4swbb_2.soft_start.inrush_limit = IOUT_INRUSH_CLAMP; // Set soft-start inrush current limit

    
    // Reset runtime data output of USB port #1
    c4swbb_2.data.v_in = 0;     // Reset input current value
    c4swbb_2.data.i_out = 0;    // Reset output current value
    c4swbb_2.data.v_out = 0;    // Reset output voltage value
    c4swbb_2.data.temp = 0;     // Reset converter temperature value
    
    return(fres);
    
}

/*!_FB_VOUT1_ADC_Interrupt
 * ******************************************************************************************************
 * Summary: 
 * USB Port A Voltage Loop Control
 * 
 * Description:
 * Interrupt Service Routine (ISR) where the most recent output voltage sample of USB port A
 * is read and the outer voltage loop controller of 4-switch buck/boost converter #1 is called.
 * inside the ISR global flags for ADC_ACTIVE is set and the samples of input and output voltage
 * are read and published by copying their values into the c4swbb_1 global data structure of 
 * 4-switch buck/boost converter #1.
 * 
 * *****************************************************************************************************/

void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_VOUT1_ADC_Interrupt ( void )
{
    cha_vloop_Update(&cha_vloop);
    c4swbb_1.status.bits.adc_active = true;
    c4swbb_1.data.v_out = FB_VOUT1_ADCBUF;
    c4swbb_1.data.v_in = FB_VBAT_ADCBUF;
    FB_VOUT1_ADC_IF = 0;  // Clear the interrupt flag 
}

/*!_FB_IOUT1_ADC_Interrupt
 * ******************************************************************************************************
 * Summary: 
 * USB Port A Current Loop Control
 * 
 * Description:
 * Interrupt Service Routine (ISR) where the most recent output current sample of USB port A
 * is read and the inner current loop controller of 4-switch buck/boost converter #1 is called.
 * Inside the ISR global flags for ADC_ACTIVE is set and the samples of input voltage and temperature
 * are read and published by copying their values into the c4swbb_1 global data structure of 
 * 4-switch buck/boost converter #1.
 * 
 * *****************************************************************************************************/

void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_IOUT1_ADC_Interrupt ( void )
{
    cha_iloop_Update(&cha_iloop);
    c4swbb_1.status.bits.adc_active = true;
    c4swbb_1.data.i_out = FB_IOUT1_ADCBUF;
    c4swbb_1.data.temp = FB_TEMP1_ADCBUF;
    FB_IOUT1_ADC_IF = 0;  // Clear the interrupt flag 
}

/*!_FB_VOUT2_ADC_Interrupt
 * ******************************************************************************************************
 * Summary: 
 * USB Port B Voltage Loop Control
 * 
 * Description:
 * Interrupt Service Routine (ISR) where the most recent output voltage sample of USB port B
 * is read and the outer voltage loop controller of 4-switch buck/boost converter #2 is called.
 * Inside the ISR global flags for ADC_ACTIVE is set and the samples of input and output voltage
 * are read and published by copying their values into the c4swbb_2 global data structure of 
 * 4-switch buck/boost converter #2.
 * 
 * *****************************************************************************************************/

void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_VOUT2_ADC_Interrupt ( void )
{
    chb_vloop_Update(&chb_vloop);
    c4swbb_2.status.bits.adc_active = true;
    c4swbb_2.data.v_out = FB_VOUT2_ADCBUF;
    c4swbb_2.data.v_in = FB_VBAT_ADCBUF;
    FB_VOUT2_ADC_IF = 0;  // Clear the interrupt flag 
}

/*!_FB_IOUT2_ADC_Interrupt
 * ******************************************************************************************************
 * Summary: 
 * USB Port B Current Loop Control
 * 
 * Description:
 * Interrupt Service Routine (ISR) where the most recent output current sample of USB port B
 * is read and the inner current loop controller of 4-switch buck/boost converter #2 is called.
 * Inside the ISR global flags for ADC_ACTIVE is set and the samples of input voltage and temperature
 * are read and published by copying their values into the c4swbb_2 global data structure of 
 * 4-switch buck/boost converter #2.
 * 
 * *****************************************************************************************************/

void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_IOUT2_ADC_Interrupt ( void )
{
    chb_iloop_Update(&chb_iloop);
    c4swbb_2.status.bits.adc_active = true;
    c4swbb_2.data.i_out = FB_IOUT2_ADCBUF;
    c4swbb_2.data.temp = FB_TEMP2_ADCBUF;
    FB_IOUT2_ADC_IF = 0;  // Clear the interrupt flag 
}


// EOF
