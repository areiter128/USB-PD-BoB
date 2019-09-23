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

// PRIVATE FUNCTION PROTOTYPES
volatile uint16_t init_USBport_1(void);
volatile uint16_t init_USBport_2(void);


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

    volatile HSADC_MODULE_ADCORE_CONFIG_t adcore_cfg;
    
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
    
    // Initialize ADC Converter
    // ========================
    // The ADC channels configured here are covering sampling of input voltage, output voltage, 
    // output current and temperature of each converter. All other ADC configurations for other 
    // functions outside the power control scope need to be done elsewhere
    fres &= c4swbb_adc_module_initialize(&c4swbb_1);
    
    // Initialize all ADC input channels of one power controller
    fres &= c4swbb_adc_inputs_initialize(&c4swbb_1);
    
    // Initialize ADC cores
    
    // Dedicated ADC core #0
    adcore_cfg.ADCORE0.config.bits.ADCS = ADCORE_ADCS_DEFAULT;
    adcore_cfg.ADCORE0.config.bits.EISEL = ADCORE_EISEL_8TAD;
    adcore_cfg.ADCORE0.config.bits.RES = ADCORE_RES_12BIT;
    adcore_cfg.ADCORE0.config.bits.SAMC = ADCORE_SAMC_DEFAULT;

    fres &= hsadc_adc_core_initialize(adcore_cfg.ADCORE0);
    fres &= hsadc_adc_core_power_on(adcore_cfg.ADCORE0.index);
    
    // Dedicated ADC core #1
    adcore_cfg.ADCORE1.config.bits.ADCS = ADCORE_ADCS_DEFAULT;
    adcore_cfg.ADCORE1.config.bits.EISEL = ADCORE_EISEL_8TAD;
    adcore_cfg.ADCORE1.config.bits.RES = ADCORE_RES_12BIT;
    adcore_cfg.ADCORE1.config.bits.SAMC = ADCORE_SAMC_DEFAULT;

    fres &= hsadc_adc_core_initialize(adcore_cfg.ADCORE1);
    fres &= hsadc_adc_core_power_on(adcore_cfg.ADCORE1.index);

    // Shared ADC core
    adcore_cfg.SHRADCORE.index = (ADC_CORE_COUNT - 1);
    adcore_cfg.SHRADCORE.config.bits.ADCS = ADCORE_ADCS_DEFAULT;
    adcore_cfg.SHRADCORE.config.bits.EISEL = ADCORE_EISEL_8TAD;
    adcore_cfg.SHRADCORE.config.bits.RES = ADCORE_RES_12BIT;
    adcore_cfg.SHRADCORE.config.bits.SAMC = ADCORE_SAMC_0010;
    
    fres &= hsadc_adc_core_initialize(adcore_cfg.SHRADCORE);
    fres &= hsadc_adc_core_power_on(adcore_cfg.SHRADCORE.index);

    // Configure device pins
    FB_VOUT1_INIT_ANALOG; // Output voltage converter #1 feedback pin
    FB_VOUT1_ADC_IP = 5; // Set interrupt priority
    FB_VOUT1_ADC_IF = 0; // Clear interrupt flag bit
    FB_VOUT1_ADC_IE = 1; // Enable interrupt service routine
    
    FB_IOUT1_INIT_ANALOG; // Output current converter #1 feedback pin
    FB_IOUT1_ADC_IP = 5; // Set interrupt priority
    FB_IOUT1_ADC_IF = 0; // Clear interrupt flag bit
    FB_IOUT1_ADC_IE = 1; // Enable interrupt service routine

    FB_TEMP1_INIT_ANALOG; // Temperature converter #1 feedback pin
    FB_TEMP1_ADC_IP = 5; // Set interrupt priority
    FB_TEMP1_ADC_IF = 0; // Clear interrupt flag bit
    FB_TEMP1_ADC_IE = 0; // Disable interrupt service routine

    FB_VOUT2_INIT_ANALOG; // Output voltage converter #2 feedback pin
    FB_VOUT2_ADC_IP = 5; // Set interrupt priority
    FB_VOUT2_ADC_IF = 0; // Clear interrupt flag bit
    FB_VOUT2_ADC_IE = 1; // Enable interrupt service routine

    FB_IOUT2_INIT_ANALOG; // Output current converter #2 feedback pin
    FB_IOUT2_ADC_IP = 5; // Set interrupt priority
    FB_IOUT2_ADC_IF = 0; // Clear interrupt flag bit
    FB_IOUT2_ADC_IE = 1; // Enable interrupt service routine

    FB_TEMP2_INIT_ANALOG; // Temperature converter #2 feedback pin
    FB_TEMP2_ADC_IP = 5; // Set interrupt priority
    FB_TEMP2_ADC_IF = 0; // Clear interrupt flag bit
    FB_TEMP2_ADC_IE = 0; // Disable interrupt service routine

    FB_VBAT_INIT_ANALOG; // Input voltage feedback pin
    FB_VBAT_ADC_IP = 5;  // Set interrupt priority
    FB_VBAT_ADC_IF = 0;  // Clear interrupt flag bit
    FB_VBAT_ADC_IE = 0;  // Disable interrupt service routine
    
    // Enable ADC Interrupts in Interrupt Controller
    
    
    return (fres);
}

volatile uint16_t init_USBport_1(void) {

    volatile uint16_t fres=1;

    
    /* Initializing 4SW-BB DC/DC converter at USB port A */
    reset_4SWBB_PowerController(&c4swbb_1);  // Initialize power controller of USB port 1
    
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
    c4swbb_1.buck_leg.pwm_swap = 0; // PWMxH and PWMxL are not swapped for buck converter operation
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
    c4swbb_1.boost_leg.pwm_swap = 1; // PWMxH and PWMxL are swapped for boost converter operation
    c4swbb_1.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    
    // Load ADC settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_1.feedback.ad_vout.adin_no = FB_VOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vout.adc_core = FB_VOUT1_ADCCORE;
    c4swbb_1.feedback.ad_vout.ptrADBUF = &FB_VOUT1_ADCBUF;

    /* ToDo: trigger and interrupt configuration needs to be added*/
    c4swbb_1.feedback.ad_vout.trigger_source = BUCKH1_ADC_TRGSRC_1;
    c4swbb_1.feedback.ad_vout.interrupt_enable = true;
    c4swbb_1.feedback.ad_vout.interrupt_priority = FB_VOUT1_ISR_PRIORITY;
    c4swbb_1.feedback.ad_vout.early_interrupt_enable = true;
    c4swbb_1.feedback.ad_vout.early_interrupt_tad = ADCORE_EISEL_TAD;
    
    c4swbb_1.feedback.ad_iout.adin_no = FB_IOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_iout.adc_core = FB_IOUT1_ADCCORE;
    c4swbb_1.feedback.ad_iout.ptrADBUF = &FB_IOUT1_ADCBUF;
    
    c4swbb_1.feedback.ad_vin.adin_no = FB_VBAT_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vin.adc_core = FB_VBAT_ADCCORE;
    c4swbb_1.feedback.ad_vin.ptrADBUF = &FB_VBAT_ADCBUF;
    
    c4swbb_1.feedback.ad_temp.adin_no = FB_TEMP1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_temp.adc_core = FB_TEMP1_ADCCORE;
    c4swbb_1.feedback.ad_temp.ptrADBUF = &FB_TEMP1_ADCBUF;

    // Initialize converter #1 voltage loop settings

    // Initialize basic controller settings of voltage loop object
    cha_vloop_Init(&cha_vloop);

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
    c4swbb_1.v_loop.controller->ptrADCTriggerRegister = &BUCKH1_PGxTRIGA; // Load pointer to ADC trigger register
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.v_loop.ctrl_Init = &cha_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.v_loop.ctrl_Update = &cha_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.v_loop.ctrl_Precharge = &cha_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.v_loop.ctrl_Reset = &cha_vloop_Reset;     // Function pointer to CONTROL RESET routine
    

    // Initialize converter #1 current loop settings
    cha_iloop_Init(&cha_iloop);
    
    c4swbb_1.i_loop.controller = &cha_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_1.i_loop.controller->ptrSource = &FB_IOUT1_ADCBUF; // Set pointer to data input source
    c4swbb_1.i_loop.controller->ptrTarget = &BUCKH1_PGx_DC; // Set pointer to data output target
    
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
    c4swbb_1.soft_start.inrush_limit = IOUT_INRUSH_CLAMP; // Set soft-start inrush current limit

    
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
    c4swbb_2.boost_leg.pwm_swap = 0; // PWMxH and PWMxL are not swapped for buck converter operation
    c4swbb_2.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
   
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


void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_IOUT2_ADC_Interrupt ( void )
{
    static volatile uint16_t counter = 0;
    static volatile uint16_t accADCAN9 =0;
    volatile uint16_t valADCAN9, avgADCAN9;
    
    valADCAN9  = ADCBUF9;   // Read the ADC value from the ADCBUF (ADSTATLbits.AN9RDY is cleared at the same time)
    
    if(++counter == 8){
        
        accADCAN9 += valADCAN9;
        avgADCAN9  = accADCAN9 >> 3;
        
        if (avgADCAN9 >= IOUT_4SWBB_UTH_CONV1) {
            // Enable PWM2 
            hspwm_ovr_release(BOOSTH1_PGx_CHANNEL);
            
            PG2CONLbits.ON = 0b1;           // PWM2 Module is enabled
//            UTH_ADCAN9_TRIPPED  = 1; 
//            LTH_ADCAN9_TRIPPED  = 0;
        }
        if (avgADCAN9 <= IOUT_4SWBB_LTH_CONV1) {
            // Disable PWM2 
            PG2CONLbits.ON      = 0b0;     // PWM2 Module is disabled 
//            UTH_ADCAN9_TRIPPED  = 0; 
//            LTH_ADCAN9_TRIPPED  = 1;
        }
        counter = 0;
        accADCAN9 = 0;
    } 
    else {
        accADCAN9 += valADCAN9;
    }
    FB_IOUT2_ADC_IF = 0;  // Clear the ADCAN9 interrupt flag 
}

void __attribute__ ( ( __interrupt__ , auto_psv , context) ) _FB_IOUT1_ADC_Interrupt ( void )
{
    static volatile uint16_t counter = 0;
    static volatile uint16_t accADCAN18 =0;
    volatile uint16_t valADCAN18, avgADCAN18;
   
    valADCAN18  = ADCBUF18;   // Read the ADC value from the ADCBUF (ADSTATLbits.AN18RDY is cleared at the same time)
    
    if(++counter == 8){
        accADCAN18 += valADCAN18;
        avgADCAN18  = accADCAN18 >> 3;
        
        if (avgADCAN18 >= IOUT_4SWBB_UTH_CONV2) {
            // Enable PWM7 outputs
            hspwm_ovr_release(BOOSTH1_PGx_CHANNEL);
            
// Remove:            PG7CONLbits.ON = 0b1;           // PWM7 Module is enabled
// Remove:            UTH_ADCAN18_TRIPPED = 1; 
// Remove:            LTH_ADCAN18_TRIPPED = 0; 
        }
        if (avgADCAN18 <= IOUT_4SWBB_LTH_CONV2) {
            // Disable PWM7 outputs
            hspwm_ovr_hold(BOOSTH1_PGx_CHANNEL);

// Remove:            PG7CONLbits.ON      = 0b0;     // PWM7 Module is disabled 
// Remove:            UTH_ADCAN18_TRIPPED = 0; 
// Remove:            LTH_ADCAN18_TRIPPED = 1; 
        }
        
        counter = 0;
        accADCAN18 = 0;
    } 
    else {
        accADCAN18 += valADCAN18;
    }
    FB_IOUT1_ADC_IF = 0;  // Clear the ADCAN18 interrupt flag 
}


