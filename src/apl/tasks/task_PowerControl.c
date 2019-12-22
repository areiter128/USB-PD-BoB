/*
 * File:   task_PowerControl.c
 * Author: M91406
 *
 * Created on May 27, 2019, 3:11 PM
 */

 //selects which channel RC2 is assigned to for ISR timing
#define CH2   

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "apl/tasks/task_PowerControl.h"
#include "apl/resources/c4swbb_control.h"   // 4-Switch Buck/Boost Power Control State Machine Header

// Declare two 4-Switch Buck/Boost DC/DC converter objects
volatile C4SWBB_PWRCTRL_t c4swbb_1;    // USB PD Port A
volatile C4SWBB_PWRCTRL_t c4swbb_2;    // USB PD Port B

// PRIVATE FUNCTION PROTOTYPES
volatile uint16_t init_USBport_1(void);
volatile uint16_t init_USBport_2(void);

volatile uint16_t init_ISR_USBport_1(void);
volatile uint16_t init_ISR_USBport_2(void);

// Private variables for current sense feedback offset calibration
#ifdef __00173_USB_PD_BOB_R21__
volatile uint16_t iavg_buf_1 = 0;
volatile uint16_t iavg_cnt_1 = 0;
volatile uint16_t iavg_buf_2 = 0;
volatile uint16_t iavg_cnt_2 = 0;
#endif


/*!exec_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t exec_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    // Both converters are supplied by the same power input and c4swbb_1 is the 
    // instance sampling the input voltage. Once this voltage is within the nominal
    // operating range, the POWER_SOURCE_DETECTED flag is set
    // 
    // Please note:
    // This test is for startup only. There is no hysteresis and no shut-down event
    // is triggered. This flag only provides an immediate indication. Power Supply
    // Over/Under Voltage Lock Out are taken care of by the fault handler.
    
    if((C4SWBB_VIN_UVLO < c4swbb_1.data.v_in) && (c4swbb_1.data.v_in < C4SWBB_VIN_OVLO)) {
        c4swbb_1.status.bits.power_source_detected = true;
        c4swbb_2.status.bits.power_source_detected = true;
    }
    else {
        c4swbb_1.status.bits.power_source_detected = false;
        c4swbb_2.status.bits.power_source_detected = false;
    }

    // The power supply fault flag is only reset if ALL fault objects have been cleared
    // 
    // Please note:
    // Output Over Current conditions are allowed and will result in a hard limitation
    // of the output current at the defined level. Thus over current conditions will NOT 
    // lead to an automatic shut down of the converter.
    
    // ToDo: RegulationError is very sensitive to changes to VREF. 
    //       Further testing is required to enable this feature.
    
    fltobj_RegulationError_USBPort_1.status.bits.fltchken = (volatile bool)(c4swbb_1.status.bits.op_status == CONVERTER_STATE_COMPLETE);
    if (!fltobj_RegulationError_USBPort_1.status.bits.fltchken) fltobj_RegulationError_USBPort_1.status.bits.fltstat = false;
    
    fltobj_RegulationError_USBPort_2.status.bits.fltchken = (volatile bool)(c4swbb_2.status.bits.op_status == CONVERTER_STATE_COMPLETE);
    if (!fltobj_RegulationError_USBPort_2.status.bits.fltchken) fltobj_RegulationError_USBPort_1.status.bits.fltstat = false;
    
    c4swbb_1.status.bits.fault_active = (volatile bool)(
                fltobj_UnderVoltageLockOut.status.bits.fltstat | 
                fltobj_OverVoltageLockOut.status.bits.fltstat |
                fltobj_OverVoltageProtection_USBPort_1.status.bits.fltstat |
                fltobj_RegulationError_USBPort_1.status.bits.fltstat
            );

    c4swbb_2.status.bits.fault_active = (volatile bool)(
                fltobj_UnderVoltageLockOut.status.bits.fltstat | 
                fltobj_OverVoltageLockOut.status.bits.fltstat |
                fltobj_OverVoltageProtection_USBPort_2.status.bits.fltstat |
                fltobj_RegulationError_USBPort_2.status.bits.fltstat
            );


    // -----------------------------------------------------
    // "Quick and Dirty" output current averaging
    // -----------------------------------------------------
    // 
    // ToDo: utilize averaging filter of ADC to generate average values of voltage and current in
    // hardware. This set is only required for current sense feedback offset calibration during
    // development and needs to be removed once a better solution is available.
    
    #ifdef __00173_USB_PD_BOB_R21__
    // ONLY VALID FOR HARDWARE VERSION R2.1
    // ====================================
    // If board is equipped with INA181A2 current sense amplifiers, 
    // the current feedback offset can be calibrated at startup...
    
    if (c4swbb_1.status.bits.adc_active) {
        
        iavg_buf_1 += c4swbb_1.data.i_out;
        if(!(++iavg_cnt_1 & 0x000F))
        { 
            c4swbb_1.data.i_out_avg = (iavg_buf_1 >> 4);
            iavg_buf_1 = 0;
            
            if ( (c4swbb_1.status.bits.op_status == CONVERTER_STATE_STANDBY) && 
                 (!c4swbb_1.status.bits.cs_calib_complete) )
            {
                c4swbb_1.i_loop.feedback_offset = c4swbb_1.data.i_out_avg;
                c4swbb_1.v_loop.maximum = (IOUT_OC_CLAMP + c4swbb_1.i_loop.feedback_offset);
                c4swbb_1.status.bits.cs_calib_complete = true;
            }
        }
        
    }

    if (c4swbb_2.status.bits.adc_active) {
        
        iavg_buf_2 += c4swbb_2.data.i_out;
        if(!(++iavg_cnt_2 & 0x000F))
        { 
            c4swbb_2.data.i_out_avg = (iavg_buf_2 >> 4);
            iavg_buf_2 = 0;
            
            if ( (c4swbb_2.status.bits.op_status == CONVERTER_STATE_STANDBY) && 
                 (!c4swbb_2.status.bits.cs_calib_complete) )
            {
                c4swbb_2.i_loop.feedback_offset = c4swbb_2.data.i_out_avg;
                c4swbb_2.v_loop.maximum = (IOUT_OC_CLAMP + c4swbb_2.i_loop.feedback_offset);
                c4swbb_2.status.bits.cs_calib_complete = true;
            }
        }
        
    }

    #else
    // ONLY VALID FOR HARDWARE VERSION R2.0
    // ====================================

    // If board is equipped with MCP6C02 current sense amplifiers, 
    // the current feedback offset is set in syscfg_scaling.h header

    c4swbb_1.status.bits.cs_calib_complete = c4swbb_1.status.bits.adc_active;
    c4swbb_2.status.bits.cs_calib_complete = c4swbb_2.status.bits.adc_active;

    #endif

    
    // Execute the state machines of converter 1 and 2
    fres &= exec_4SWBB_PowerController(&c4swbb_1);  // Execute 4-Switch Buck/Boost Converter #1 State Machine
    fres &= exec_4SWBB_PowerController(&c4swbb_2);  // Execute 4-Switch Buck/Boost Converter #2 State Machine
    
    Nop();
    Nop();
    Nop();
    
    
    return (fres);
}

/*!init_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;

#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP39_INIT_OUTPUT;
    ECP44_INIT_OUTPUT;
#endif

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

    // ----------------------------------------------------
    // ToDo: Move these settings into normal initialization
    //       NO DEDICATED REGISTER WRITES IN USER CODE !!!
    
    
    //Custom setup for c4swbb_2 to use PCI to sync c2 buck leg to ch 1 buck leg
    PG1LEBH = C4SWBB_2_PG1LEBH;     // PG5 available to PCI logic
    PG1CONH = C4SWBB_2_PGxCONH;     // Trigger is via PCI logic from PG5 
    PG1SPCIL = 0b1001000000000001;  // Termination of latched PCI occurs immediately / Auto-Terminate / 
                                    // Internally connected to the output of PWMPCI<2:0> MUX
    PG1SPCIH = 0x0000;              
    
    //Custom setup for c4swbb_2 to use PCI to sync c2 boost leg to ch 1 buck leg
    PG2LEBH = C4SWBB_2_PG1LEBH;             // PG5 available to PCI logic
    PG2CONH = C4SWBB_BOOSTLEG_2_PGxCONH;    // Trigger is via PCI logic from PG5 
    PG2SPCIL = 0b1001000000000001;  // Termination of latched PCI occurs immediately / Auto-Terminate / 
                                    // Internally connected to the output of PWMPCI<2:0> MUX
    PG2SPCIH = 0x0000;
    
    PG2PHASE = 0;
    PG7PHASE = 0;

    // ----------------------------------------------------
    // ----------------------------------------------------
    
    // ADC core configuration
    fres &= c4swbb_adc_module_initialize();
    
    // Initialize all ADC input channels of one power controller
    fres &= c4swbb_adc_inputs_initialize(&c4swbb_1);
    fres &= c4swbb_adc_inputs_initialize(&c4swbb_2);

    // Initialize analog inputs and analog input interrupts
    fres &= init_ISR_USBport_1();
    fres &= init_ISR_USBport_2();

    // Enable ADC module and all ADC cores used
    fres &= c4swbb_adc_enable();
    
    // Enable PWM module starting to trigger the ADC while outputs are 
    // still disabled
  
    
    fres &= c4swbb_pwm_enable(&c4swbb_1);
    fres &= c4swbb_pwm_enable(&c4swbb_2);

            
    c4swbb_1.status.bits.enable = false;
    c4swbb_2.status.bits.enable = false;
    
    //fres &= c4swbb_pwm_release(&c4swbb_1);
    //fres &= c4swbb_pwm_release(&c4swbb_2);
    
    // ----------------------------------------------------
    // ToDo: Move these settings into normal initialization
    //       NO DEDICATED REGISTER WRITES IN USER CODE !!!
    
    TRISCbits.TRISC2 = 0;  // used for debug // ToDo: Remove when done
    
    //Max 1428 for 350kHz
    // PG1TRIGA = 200; => replaced by following line
    BUCKH2_PGxTRIGA = 200;
    //PG7TRIGA = 20;
    //PG2TRIGA = 20;
    
    // PG5TRIGA = 200; => replaced by following line
    BUCKH1_PGxTRIGA = 200;
    
    //PG7TRIGA = 20;
    Nop();
    
    PG1STATbits.UPDREQ = 1;
    PG2STATbits.UPDREQ = 1;
    PG5STATbits.UPDREQ = 1;
    PG7STATbits.UPDREQ = 1;
   
    
   c4swbb_1.data.v_ref = C4SWBB_VOUT_REF_15V ;    // Set reference to 5V
   c4swbb_2.data.v_ref = C4SWBB_VOUT_REF_15V ;    // Set reference to 5V
   
   c4swbb_1.status.bits.autorun = 1;
   c4swbb_2.status.bits.autorun = 1;  
    Nop();
    
    // return Success/Failure
    return (fres);
}

/*!reset_PowerControl
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t reset_PowerControl(void) {
    
    volatile uint16_t fres = 0;

    c4swbb_1.status.bits.fault_active = true; // Set FAULT flag
    c4swbb_2.status.bits.fault_active = true; // Set FAULT flag
    
    fres &= c4SWBB_shut_down(&c4swbb_1);  // Shut Down 4-Switch Buck/Boost Converter #1 State Machine
    fres &= c4SWBB_shut_down(&c4swbb_2);  // Shut Down 4-Switch Buck/Boost Converter #2 State Machine
    
    fltobj_RegulationError_USBPort_1.status.bits.fltactive = false;
    fltobj_RegulationError_USBPort_1.status.bits.fltstat = false;
    fltobj_RegulationError_USBPort_1.status.bits.fltchken = false;
    
    fltobj_RegulationError_USBPort_2.status.bits.fltactive = false;
    fltobj_RegulationError_USBPort_2.status.bits.fltstat = false;
    fltobj_RegulationError_USBPort_2.status.bits.fltchken = false;

    return(fres);
}

/*!init_ISR_USBport_1
 * ******************************************************************************************************
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t init_ISR_USBport_1(void) {

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

volatile uint16_t init_ISR_USBport_2(void) {

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

volatile uint16_t init_USBport_1(void) {

    volatile uint16_t fres=1;

    
    /* Initializing 4SW-BB DC/DC converter at USB port A */
    fres &= reset_4SWBB_PowerController(&c4swbb_1);  // Initialize power controller of USB port 1
    
    // Load PWM settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_1.buck_leg.pwm_instance = BUCKH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.buck_leg.phase = 0; // Phase shift of converter #1 is ZERO
    c4swbb_1.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.buck_leg.duty_ratio_init = DUTY_RATIO_INIT_BUCK_REG; // reset initial duty cycle
    c4swbb_1.buck_leg.duty_ratio_min = DUTY_RATIO_MIN_BUCK_REG; // set minimum duty cycle
    c4swbb_1.buck_leg.duty_ratio_max = DUTY_RATIO_MAX_BUCK_REG; // set maximum duty cycle
    c4swbb_1.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_1.buck_leg.pwm_swap = false; // PWMxH and PWMxL are not swapped for buck converter operation
    c4swbb_1.buck_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    c4swbb_1.buck_leg.adtr1_source = BUCKH1_PGxEVT_ADTR1EN; // ADC trigger 1 source is PGxTRIGA/B/C register compare event
    c4swbb_1.buck_leg.adtr2_source = BUCKH1_PGxEVT_ADTR2EN; // ADC trigger 2 source is PGxTRIGA/B/C register compare event
    c4swbb_1.buck_leg.adtr1_scale = BUCKH1_PGxEVT_ADTR1PS;  // ADC Trigger 1 Post-Scaler Selection
    c4swbb_1.buck_leg.adtr1_offset = BUCKH1_PGxEVT_ADTR1OFS; // ADC Trigger 1 Offset Selection
    
    c4swbb_1.boost_leg.pwm_instance = BOOSTH1_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.boost_leg.phase = 0; // Phase shift of converter #1 is ZERO 
    c4swbb_1.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.boost_leg.duty_ratio_init = DUTY_RATIO_INIT_BOOST_REG; // reset initial duty cycle
    c4swbb_1.boost_leg.duty_ratio_min = DUTY_RATIO_MIN_BOOST_REG; // set minimum duty cycle
    c4swbb_1.boost_leg.duty_ratio_max = DUTY_RATIO_MAX_BOOST_REG; // set maximum duty cycle
    c4swbb_1.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_1.boost_leg.pwm_swap = true; // PWMxH and PWMxL are swapped for boost converter operation
    c4swbb_1.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    c4swbb_1.boost_leg.adtr1_source = BOOSTH1_PGxEVT_ADTR1EN; // ADC trigger 1 source is PGxTRIGA/B/C register compare event
    c4swbb_1.boost_leg.adtr2_source = BOOSTH1_PGxEVT_ADTR2EN; // ADC trigger 2 source is PGxTRIGA/B/C register compare event
    c4swbb_1.boost_leg.adtr1_scale = BOOSTH1_PGxEVT_ADTR1PS;  // ADC Trigger 1 Post-Scaler Selection
    c4swbb_1.boost_leg.adtr1_offset = BOOSTH1_PGxEVT_ADTR1OFS; // ADC Trigger 1 Offset Selection
    
    // Load ADC settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_1.feedback.ad_vout.enable = FB_VOUT1_ENABLE;
    c4swbb_1.feedback.ad_vout.adin_no = FB_VOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vout.adc_core = FB_VOUT1_ADCCORE;
    c4swbb_1.feedback.ad_vout.ptrADBUF = &FB_VOUT1_ADCBUF;
    c4swbb_1.feedback.ad_vout.trigger_source = FB_VOUT1_TRGSRC;
    c4swbb_1.feedback.ad_vout.early_interrupt_enable = FB_VOUT1_EIE_ENABLE;
    c4swbb_1.feedback.ad_vout.interrupt_enable = FB_VOUT1_ISR_ENABLE;
    c4swbb_1.feedback.ad_vout.interrupt_priority = FB_VOUT1_ISR_PRIORITY;
    
    c4swbb_1.feedback.ad_iout.enable = FB_IOUT1_ENABLE;
    c4swbb_1.feedback.ad_iout.adin_no = FB_IOUT1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_iout.adc_core = FB_IOUT1_ADCCORE;
    c4swbb_1.feedback.ad_iout.ptrADBUF = &FB_IOUT1_ADCBUF;
    c4swbb_1.feedback.ad_iout.trigger_source = FB_IOUT1_TRGSRC;
    c4swbb_1.feedback.ad_iout.early_interrupt_enable = FB_IOUT1_EIE_ENABLE;
    c4swbb_1.feedback.ad_iout.interrupt_enable = FB_IOUT1_ISR_ENABLE;
    c4swbb_1.feedback.ad_iout.interrupt_priority = FB_IOUT1_ISR_PRIORITY;
    
    c4swbb_1.feedback.ad_vin.enable = FB_VBAT_ENABLE;
    c4swbb_1.feedback.ad_vin.adin_no = FB_VBAT_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_vin.adc_core = FB_VBAT_ADCCORE;
    c4swbb_1.feedback.ad_vin.ptrADBUF = &FB_VBAT_ADCBUF;
    c4swbb_1.feedback.ad_vin.trigger_source = FB_VBAT_TRGSRC;
    c4swbb_1.feedback.ad_vin.early_interrupt_enable = FB_VBAT_EIE_ENABLE;
    c4swbb_1.feedback.ad_vin.interrupt_enable = FB_VBAT_ISR_ENABLE;
    c4swbb_1.feedback.ad_vin.interrupt_priority = FB_VBAT_ISR_PRIORITY;
    
    c4swbb_1.feedback.ad_temp.enable = FB_TEMP1_ENABLE;
    c4swbb_1.feedback.ad_temp.adin_no = FB_TEMP1_ADC_AN_INPUT;
    c4swbb_1.feedback.ad_temp.adc_core = FB_TEMP1_ADCCORE;
    c4swbb_1.feedback.ad_temp.ptrADBUF = &FB_TEMP1_ADCBUF;
    c4swbb_1.feedback.ad_temp.trigger_source = FB_TEMP1_TRGSRC;
    c4swbb_1.feedback.ad_temp.early_interrupt_enable = FB_TEMP1_EIE_ENABLE;
    c4swbb_1.feedback.ad_temp.interrupt_enable = FB_TEMP1_ISR_ENABLE;
    c4swbb_1.feedback.ad_temp.interrupt_priority = FB_TEMP1_ISR_PRIORITY;

    // Initialize converter #1 voltage loop controller settings

    // Initialize basic controller settings of voltage loop object
    fres &= cha_vloop_Init(&cha_vloop);

    // Hardware-specific voltage loop controller settings
    c4swbb_1.v_loop.minimum = (IOUT_LCL_CLAMP + C4SWBB_IOUT_FEEDBACK_OFFSET);   // Minimum output value of voltage loop is absolute current limit
    c4swbb_1.v_loop.maximum = (IOUT_OCL_TRIP + C4SWBB_IOUT_FEEDBACK_OFFSET);    // Maximum output value of voltage loop is absolute current limit
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
    c4swbb_1.v_loop.controller->ptrDataProviderControlInput = &c4swbb_1.data.v_out; // Setting pointer to output voltage variable for automatic update
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.v_loop.ctrl_Init = &cha_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.v_loop.ctrl_Update = &cha_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.v_loop.ctrl_Precharge = &cha_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.v_loop.ctrl_Reset = &cha_vloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_1.v_loop.ctrl_Reset(&cha_vloop); // Call RESET routine of voltage loop controller

    // Initialize converter #1 current loop settings
    fres &= cha_iloop_Init(&cha_iloop);
    c4swbb_1.i_loop.minimum = DUTY_RATIO_MIN_BUCK_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.maximum = (DUTY_RATIO_MAX_BUCK_REG + DUTY_RATIO_MAX_BOOST_REG);   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_1.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_1.i_loop.reference = (IOUT_LCL_CLAMP + C4SWBB_IOUT_FEEDBACK_OFFSET); // Current loop reference value
    c4swbb_1.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)

    c4swbb_1.i_loop.controller = &cha_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_1.i_loop.controller->ptrSource = &FB_IOUT1_ADCBUF; // Set pointer to data input source
    c4swbb_1.i_loop.controller->ptrTarget = &c4swbb_1.i_loop.control_output; // &BUCKH1_PGx_DC; // Set pointer to data output target
    c4swbb_1.i_loop.controller->ptrControlReference = &c4swbb_1.i_loop.reference; // Set pointer to user reference
    c4swbb_1.i_loop.controller->MinOutput = c4swbb_1.i_loop.minimum; // Load user minimum value
    c4swbb_1.i_loop.controller->MaxOutput = c4swbb_1.i_loop.maximum; // Load user maximum value
    c4swbb_1.i_loop.controller->InputOffset = c4swbb_1.i_loop.feedback_offset; // Load user feedback offset value
    c4swbb_1.i_loop.controller->ptrDataProviderControlInput = &c4swbb_1.data.i_out; // Setting pointer to output current variable for automatic update
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_1.i_loop.ctrl_Init = &cha_iloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_1.i_loop.ctrl_Update = &cha_iloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_1.i_loop.ctrl_Precharge = &cha_iloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_1.i_loop.ctrl_Reset = &cha_iloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_1.i_loop.ctrl_Reset(&cha_iloop); // Call RESET routine of current loop controller

    // Initializing the 4-Switch Buck/Boost PWM distribution module data structure
    c4swbb_1.pwm_dist.ptr_source = &c4swbb_1.i_loop.control_output; // Set pointer to controller output value buffer2.i_loop.control_output; // Set pointer to controller output value buffer
    c4swbb_1.pwm_dist.ptr_targetA = &BUCKH1_PGx_DC;         // Target A for PWM distribution is buck-leg PWM output HIGH
    c4swbb_1.pwm_dist.ptr_targetB = &BOOSTH1_PGx_DC;        // Target B for PWM distribution is boost-leg PWM output HIGH
    c4swbb_1.pwm_dist.limitA_min = DUTY_RATIO_MIN_BUCK_REG; // Min clamping threshold of buck PWM
    c4swbb_1.pwm_dist.limitA_max = DUTY_RATIO_MAX_BUCK_REG; // Max clamping threshold of buck PWM
    c4swbb_1.pwm_dist.limitB_min = DUTY_RATIO_MIN_BOOST_REG; // Min clamping threshold of boost PWM
    c4swbb_1.pwm_dist.limitB_max = DUTY_RATIO_MAX_BOOST_REG; // Max clamping threshold of boost PWM
    c4swbb_1.pwm_dist.ptr_adc_trigA = &FB_IOUT1_PGxTRIGy;    // Load pointer to ADC trigger A register (current trigger)
    c4swbb_1.pwm_dist.adc_trigA_offset = c4swbb_1.i_loop.trigger_offset;    // Set ADC trigger A offset value (current trigger)
    c4swbb_1.pwm_dist.ptr_adc_trigB = &FB_VOUT1_PGxTRIGy;   // Load pointer to ADC trigger B register (voltage trigger)
    c4swbb_1.pwm_dist.adc_trigB_offset = c4swbb_1.v_loop.trigger_offset;   // Set ADC trigger B offset value (voltage trigger)
    c4swbb_1.pwm_dist.status.bits.trigA_placement_enable = false; // Allow the PWM distribution module to auto-position the rigger of buck leg
    c4swbb_1.pwm_dist.status.bits.trigB_placement_enable = false; // Allow the PWM distribution module to auto-position the rigger of boost leg
    c4swbb_1.pwm_dist.ssm_bit_mask = SSM_MOD_RANGE_MASK;   // Define bit-mask to limit Spread Spectrum Modulation range
    c4swbb_1.pwm_dist.status.bits.ssm_enable = false;   // Spread Spectrum Modulation disabled
    
    //Added this to enable PWM distribution routine
    c4swbb_1.pwm_dist.status.bits.enable = true;
    
    
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

volatile uint16_t init_USBport_2(void) {

    volatile uint16_t fres=1;
    
    /* Initializing 4SW-BB DC/DC converter at USB port B */
    fres &= reset_4SWBB_PowerController(&c4swbb_2);  // Initialize power controller of USB port 1
    
    // Load PWM settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_2.buck_leg.pwm_instance = BUCKH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.buck_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.buck_leg.phase = 0;//PWM_PHASE_SFT; // Phase shift of converter #2 is 180° (half of switching frequency)
    c4swbb_2.buck_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.buck_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.buck_leg.duty_ratio_init = DUTY_RATIO_INIT_BUCK_REG; // reset initial duty cycle
    c4swbb_2.buck_leg.duty_ratio_min = DUTY_RATIO_MIN_BUCK_REG; // set minimum duty cycle
    c4swbb_2.buck_leg.duty_ratio_max = DUTY_RATIO_MAX_BUCK_REG; // set maximum duty cycle
    c4swbb_2.buck_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_2.buck_leg.pwm_swap = 0; // PWMxH and PWMxL are not swapped for buck converter operation
    c4swbb_2.buck_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    c4swbb_2.buck_leg.adtr1_source = BUCKH2_PGxEVT_ADTR1EN; // ADC trigger 1 source is PGxTRIGA/B/C register compare event
    c4swbb_2.buck_leg.adtr2_source = BUCKH2_PGxEVT_ADTR2EN; // ADC trigger 2 source is PGxTRIGA/B/C register compare event
    c4swbb_2.buck_leg.adtr1_scale = BUCKH2_PGxEVT_ADTR1PS;  // ADC Trigger 1 Post-Scaler Selection
    c4swbb_2.buck_leg.adtr1_offset = BUCKH2_PGxEVT_ADTR1OFS; // ADC Trigger 1 Offset Selection

    c4swbb_2.boost_leg.pwm_instance = BOOSTH2_PGx_CHANNEL; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_2.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_2.boost_leg.phase = 0; //PWM_PHASE_SFT; // Phase shift of converter #2 is 180° (half of switching frequency
    c4swbb_2.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_2.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_2.boost_leg.duty_ratio_init = DUTY_RATIO_INIT_BOOST_REG; // reset initial duty cycle
    c4swbb_2.boost_leg.duty_ratio_min = DUTY_RATIO_MIN_BOOST_REG; // set minimum duty cycle
    c4swbb_2.boost_leg.duty_ratio_max = DUTY_RATIO_MAX_BOOST_REG; // set maximum duty cycle
    c4swbb_2.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    c4swbb_2.boost_leg.pwm_swap = 1; // PWMxH and PWMxL are swapped for boost converter operation
    c4swbb_2.boost_leg.pwm_ovrdat = 0; // PWMxH and PWMxL pin states in OFF mode are PWMxH=LOW, PWMxL=LOW
    c4swbb_2.boost_leg.adtr1_source = BOOSTH2_PGxEVT_ADTR1EN; // ADC trigger 1 source is PGxTRIGA/B/C register compare event
    c4swbb_2.boost_leg.adtr2_source = BOOSTH2_PGxEVT_ADTR2EN; // ADC trigger 2 source is PGxTRIGA/B/C register compare event
    c4swbb_2.boost_leg.adtr1_scale = BOOSTH2_PGxEVT_ADTR1PS;  // ADC Trigger 1 Post-Scaler Selection
    c4swbb_2.boost_leg.adtr1_offset = BOOSTH2_PGxEVT_ADTR1OFS; // ADC Trigger 1 Offset Selection
    
    // Load ADC settings from hardware and microcontroller abstraction layers (HAL and MCAL)
    c4swbb_2.feedback.ad_vout.enable = FB_VOUT2_ENABLE;
    c4swbb_2.feedback.ad_vout.adin_no = FB_VOUT2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_vout.adc_core = FB_VOUT2_ADCCORE;
    c4swbb_2.feedback.ad_vout.ptrADBUF = &FB_VOUT2_ADCBUF;
    c4swbb_2.feedback.ad_vout.trigger_source = FB_VOUT2_TRGSRC;
    c4swbb_2.feedback.ad_vout.early_interrupt_enable = FB_VOUT2_EIE_ENABLE;
    c4swbb_2.feedback.ad_vout.interrupt_enable = FB_VOUT2_ISR_ENABLE;
    c4swbb_2.feedback.ad_vout.interrupt_priority = FB_VOUT2_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_iout.enable = FB_IOUT2_ENABLE;
    c4swbb_2.feedback.ad_iout.adin_no = FB_IOUT2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_iout.adc_core = FB_IOUT2_ADCCORE;
    c4swbb_2.feedback.ad_iout.ptrADBUF = &FB_IOUT2_ADCBUF;
    c4swbb_2.feedback.ad_iout.trigger_source = FB_IOUT2_TRGSRC;
    c4swbb_2.feedback.ad_iout.early_interrupt_enable = FB_IOUT2_EIE_ENABLE;
    c4swbb_2.feedback.ad_iout.interrupt_enable = FB_IOUT2_ISR_ENABLE;
    c4swbb_2.feedback.ad_iout.interrupt_priority = FB_IOUT2_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_vin.enable = FB_VBAT_ENABLE;
    c4swbb_2.feedback.ad_vin.adin_no = FB_VBAT_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_vin.adc_core = FB_VBAT_ADCCORE;
    c4swbb_2.feedback.ad_vin.ptrADBUF = &FB_VBAT_ADCBUF;
    c4swbb_2.feedback.ad_vin.trigger_source = FB_VBAT_TRGSRC;
    c4swbb_2.feedback.ad_vin.early_interrupt_enable = FB_VBAT_EIE_ENABLE;
    c4swbb_2.feedback.ad_vin.interrupt_enable = FB_VBAT_ISR_ENABLE;
    c4swbb_2.feedback.ad_vin.interrupt_priority = FB_VBAT_ISR_PRIORITY;
    
    c4swbb_2.feedback.ad_temp.enable = FB_TEMP2_ENABLE;
    c4swbb_2.feedback.ad_temp.adin_no = FB_TEMP2_ADC_AN_INPUT;
    c4swbb_2.feedback.ad_temp.adc_core = FB_TEMP2_ADCCORE;
    c4swbb_2.feedback.ad_temp.ptrADBUF = &FB_TEMP2_ADCBUF;
    c4swbb_2.feedback.ad_temp.trigger_source = FB_TEMP2_TRGSRC;
    c4swbb_2.feedback.ad_temp.early_interrupt_enable = FB_TEMP2_EIE_ENABLE;
    c4swbb_2.feedback.ad_temp.interrupt_enable = FB_TEMP2_ISR_ENABLE;
    c4swbb_2.feedback.ad_temp.interrupt_priority = FB_TEMP2_ISR_PRIORITY;

    // Initialize converter #1 voltage loop controller settings

    // Initialize basic controller settings of voltage loop object
    fres &= chb_vloop_Init(&chb_vloop);

    // Hardware-specific voltage loop controller settings
    c4swbb_2.v_loop.minimum = (IOUT_LCL_CLAMP + C4SWBB_IOUT_FEEDBACK_OFFSET);   // Minimum output value of voltage loop is absolute current limit
    c4swbb_2.v_loop.maximum = (IOUT_OCL_TRIP + C4SWBB_IOUT_FEEDBACK_OFFSET);    // Maximum output value of voltage loop is absolute current limit
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
    c4swbb_2.v_loop.controller->ptrDataProviderControlInput = &c4swbb_2.data.v_out; // Setting pointer to output voltage variable for automatic update
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_2.v_loop.ctrl_Init = &chb_vloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_2.v_loop.ctrl_Update = &chb_vloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_2.v_loop.ctrl_Precharge = &chb_vloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_2.v_loop.ctrl_Reset = &chb_vloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_2.v_loop.ctrl_Reset(&chb_vloop); // Call RESET routine of voltage loop controller

    // Initialize converter #2 current loop settings
    fres &= chb_iloop_Init(&chb_iloop);

    c4swbb_2.i_loop.minimum = DUTY_RATIO_MIN_BUCK_REG;   // Minimum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.maximum = (DUTY_RATIO_MAX_BUCK_REG + DUTY_RATIO_MAX_BOOST_REG);   // Maximum duty ratio is absolute clamping limit of current loop
    c4swbb_2.i_loop.feedback_offset = C4SWBB_IOUT_FEEDBACK_OFFSET;   // Current feedback signal offset
    c4swbb_2.i_loop.reference = (IOUT_LCL_CLAMP + C4SWBB_IOUT_FEEDBACK_OFFSET); // Current loop reference value
    c4swbb_2.i_loop.trigger_offset = ADC_TRIG_OFFSET_IOUT; // Current sample ADC trigger offset (offset from 50% on-time)
    
    c4swbb_2.i_loop.controller = &chb_iloop;   // 4-Switch Buck/Boost converter voltage loop controller
    c4swbb_2.i_loop.controller->ptrSource = &FB_IOUT2_ADCBUF; // Set pointer to data input source
    c4swbb_2.i_loop.controller->ptrTarget = &c4swbb_2.i_loop.control_output; // &BUCKH2_PGx_DC; // Set pointer to data output target
    c4swbb_2.i_loop.controller->ptrControlReference = &c4swbb_2.i_loop.reference; // Set pointer to user reference
    c4swbb_2.i_loop.controller->MinOutput = c4swbb_2.i_loop.minimum; // Load user minimum value
    c4swbb_2.i_loop.controller->MaxOutput = c4swbb_2.i_loop.maximum; // Load user maximum value
    c4swbb_2.i_loop.controller->InputOffset = c4swbb_2.i_loop.feedback_offset; // Load user feedback offset value
    c4swbb_2.i_loop.controller->ptrDataProviderControlInput = &c4swbb_2.data.i_out; // Setting pointer to output current variable for automatic update
    
    // Assign control functions by loading function pointers into the data structure
    c4swbb_2.i_loop.ctrl_Init = &chb_iloop_Init;        // Function pointer to CONTROL INIT routine
    c4swbb_2.i_loop.ctrl_Update = &chb_iloop_Update;    // Function pointer to CONTROL UPDATE routine
    c4swbb_2.i_loop.ctrl_Precharge = &chb_iloop_Precharge; // Function pointer to CONTROL PRECHARGE routine
    c4swbb_2.i_loop.ctrl_Reset = &chb_iloop_Reset;     // Function pointer to CONTROL RESET routine
    
    c4swbb_2.i_loop.ctrl_Reset(&chb_iloop); // Call RESET routine of voltage loop controller

    // Initializing the 4-Switch Buck/Boost PWM distribution module data structure
    c4swbb_2.pwm_dist.ptr_source = &c4swbb_2.i_loop.control_output; // Set pointer to controller output value buffer
    c4swbb_2.pwm_dist.ptr_targetA = &BUCKH2_PGx_DC;         // Target A for PWM distribution is buck-leg PWM output HIGH
    c4swbb_2.pwm_dist.ptr_targetB = &BOOSTH2_PGx_DC;        // Target B for PWM distribution is boost-leg PWM output HIGH
    c4swbb_2.pwm_dist.limitA_min = DUTY_RATIO_MIN_BUCK_REG; // Min clamping threshold of buck PWM
    c4swbb_2.pwm_dist.limitA_max = DUTY_RATIO_MAX_BUCK_REG; // Max clamping threshold of buck PWM
    c4swbb_2.pwm_dist.limitB_min = DUTY_RATIO_MIN_BOOST_REG; // Min clamping threshold of boost PWM
    c4swbb_2.pwm_dist.limitB_max = DUTY_RATIO_MAX_BOOST_REG; // Max clamping threshold of boost PWM
    c4swbb_2.pwm_dist.ptr_adc_trigA = &FB_IOUT2_PGxTRIGy;    // Load pointer to ADC trigger A register (current trigger)
    c4swbb_2.pwm_dist.adc_trigA_offset = c4swbb_2.i_loop.trigger_offset;    // Set ADC trigger A offset value (current trigger)
    c4swbb_2.pwm_dist.ptr_adc_trigB = &FB_VOUT2_PGxTRIGy;   // Load pointer to ADC trigger B register (voltage trigger)
    c4swbb_2.pwm_dist.adc_trigB_offset = c4swbb_2.v_loop.trigger_offset;   // Set ADC trigger B offset value (voltage trigger)
    c4swbb_2.pwm_dist.status.bits.trigA_placement_enable = false; // Allow the PWM distribution module to auto-position the trigger of buck leg
    c4swbb_2.pwm_dist.status.bits.trigB_placement_enable = false; // Allow the PWM distribution module to auto-position the trigger of boost leg
    c4swbb_2.pwm_dist.ssm_bit_mask = SSM_MOD_RANGE_MASK;   // Define bit-mask to limit Spread Spectrum Modulation range
    c4swbb_2.pwm_dist.status.bits.ssm_enable = false;   // Spread Spectrum Modulation disabled
    
    // Added this to enable PWM distribution routine
    c4swbb_2.pwm_dist.status.bits.enable = true;        // Enable PWM distribution for buck and boost leg
    
    
    // Initialize USB Port #2 Soft Start Settings
    c4swbb_2.soft_start.pwr_on_delay = C4SWBB_PODLY;    // Power-On Delay
    c4swbb_2.soft_start.ramp_period = C4SWBB_RPER;      // Ramp-Up Period
    c4swbb_2.soft_start.pwr_good_delay = C4SWBB_PGDLY;  // Power-Good Delay
    c4swbb_2.soft_start.ramp_v_ref_increment = C4SWBB_VREF_STEP; // Voltage reference tick increment to meet ramp period setting
    c4swbb_2.soft_start.ramp_i_ref_increment = C4SWBB_IREF_STEP; // Current reference tick increment to meet ramp period setting
    c4swbb_2.soft_start.inrush_limit = IOUT_INRUSH_CLAMP; // Set soft-start inrush current limit

    
    // Reset runtime data output of USB port #2
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
short buffer[2000],cntbuff=0;
#if (FB_VOUT1_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_VOUT1_ADC_Interrupt(void)
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
ECP39_SET;
#endif

#if defined CH1|| defined ALL
//LATCbits.LATC2 = 1;
#endif

    // Call control loop update
    cha_vloop_Update(&cha_vloop);
    cha_iloop_Update(&cha_iloop);
    c4swbb_pwm_update(&c4swbb_1.pwm_dist);
      
    //PG5STATbits.UPDREQ = 1;
    //PG7STATbits.UPDREQ = 1;
    
    // Capture additional analog inputs
    c4swbb_1.status.bits.adc_active = true; // Set ADC_ACTIVE flag
    c4swbb_1.data.v_in = FB_VBAT_ADCBUF; // Capture most recent input voltage value 
    c4swbb_1.data.temp = FB_TEMP1_ADCBUF; // Capture most recent temperature value

    // Clear the interrupt flag 
    _ADCIF = 0;
    #if (FB_VOUT1_ENABLE)
    FB_VOUT1_ADC_IF = 0; 
    #endif
    #if (FB_IOUT1_ENABLE)
    //FB_IOUT1_ADC_IF = 0;
    #endif
    #if (FB_VBAT_ENABLE)
    //FB_VBAT_ADC_IF = 0;
    #endif
    #if (FB_TEMP1_ENABLE)
    //FB_TEMP1_ADC_IF = 0;
    #endif
    
    // Software trigger for VBAT,TEMP1 and TEMP2 - samples stored in next ISR
    ADCON3Lbits.SWCTRG = 1;
    
    
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP39_CLEAR;
#endif
#if defined CH1|| defined ALL
//LATCbits.LATC2 = 0;
#endif
}
#else
    #pragma message "WARNING: NO VOLTAGE FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #1"
#endif

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
#if ((FB_IOUT1_ENABLE) || (FB_IIN1_ENABLE))
#if (FB_IOUT1_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_IOUT1_ADC_Interrupt(void)
#elif (FB_IIN1_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_IIN2_ADC_Interrupt(void)
#else
    #pragma message "WARNING: NO CURRENT FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #1"
#endif
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP44_SET;
#endif
    
#if defined CH1|| defined ALL
//LATCbits.LATC2 = 1;
#endif

    // Call control loop update
    cha_iloop_Update(&cha_iloop);
    c4swbb_pwm_update(&c4swbb_1.pwm_dist);
    
    // Capture additional analog inputs
    c4swbb_1.status.bits.adc_active = true; // Set ADC_ACTIVE flag
//    c4swbb_1.data.i_out = FB_IOUT1_ADCBUF; // Capture most recent output current value
    c4swbb_1.data.temp = FB_TEMP1_ADCBUF; // Capture most recent temperature value
    
    // Clear the interrupt flag 
    FB_TEMP1_ADC_IF = 0;
    #if (FB_IOUT1_ENABLE)
    FB_IOUT1_ADC_IF = 0;  
    #elif (FB_IIN1_ENABLE)
    FB_IIN1_ADC_IF = 0;  
    #else
    #pragma message "WARNING: NO VOLTAGE FEEDBACK SIGNAL HAS BEEN SELECTED FOR USB PORT #2"
    #endif   

#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
ECP44_CLEAR;
#endif

#if defined CH1|| defined ALL
//LATCbits.LATC2 = 0;
#endif

}
#else
    #pragma message "WARNING: NO CURRENT FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #1"
#endif

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
#if (FB_VOUT2_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_VOUT2_ADC_Interrupt(void)
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP39_SET;
#endif
    
#if defined CH2|| defined ALL
LATCbits.LATC2 = 1;
#endif

    // Call control loop update 
    chb_vloop_Update(&chb_vloop);
    chb_iloop_Update(&chb_iloop);    
    c4swbb_pwm_update(&c4swbb_2.pwm_dist);

       
    // Capture additional analog inputs
    c4swbb_2.status.bits.adc_active = true; // Set ADC_ACTIVE flag
    c4swbb_2.data.v_in = FB_VBAT_ADCBUF; // Capture most recent input voltage value
    c4swbb_2.data.temp = FB_TEMP2_ADCBUF;
    
    //PG1STATbits.UPDREQ = 1;
    //PG2STATbits.UPDREQ = 1;
    
    // Clear the interrupt flag 
    _ADCIF = 0;
    #if (FB_VOUT2_ENABLE)
    FB_VOUT2_ADC_IF = 0; 
    #endif
    #if (FB_IOUT2_ENABLE)
    //FB_IOUT2_ADC_IF = 0;
    #endif
    #if (FB_VBAT_ENABLE)
    //FB_VBAT_ADC_IF = 0;
    #endif
    #if (FB_TEMP2_ENABLE)
    //FB_TEMP2_ADC_IF = 0;
    #endif
     
    // Software trigger for VBAT,TEMP1 - samples stored in next ISR
    ADCON3Lbits.SWCTRG = 1;
    LATCbits.LATC2 = 0;
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP39_CLEAR;
#endif
    
#if defined CH2|| defined ALL
//LATCbits.LATC2 = 0;
#endif

}
#else
//    #pragma message "WARNING: NO VOLTAGE FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #2"
#endif

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
#if ((FB_IOUT2_ENABLE) || (FB_IIN2_ENABLE))
#if (FB_IOUT2_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_IOUT2_ADC_Interrupt(void)
#elif (FB_IIN2_ENABLE)
void __attribute__ ((__interrupt__, auto_psv, context)) _FB_IIN2_ADC_Interrupt(void)
#else
    #pragma message "WARNING: NO CURRENT FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #2"
#endif
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP44_SET;
#endif
    
#if defined CH2|| defined ALL
//LATCbits.LATC2 = 1;
#endif
    
    // Call control loop update
    chb_iloop_Update(&chb_iloop);    
    c4swbb_pwm_update(&c4swbb_2.pwm_dist);
    
    // Capture additional analog inputs
    c4swbb_2.status.bits.adc_active = true; // Set ADC_ACTIVE flag
//    c4swbb_2.data.i_out = FB_IOUT2_ADCBUF; // Capture most recent output current value
    c4swbb_2.data.temp = FB_TEMP2_ADCBUF; // Capture most recent temperature value
    
    // Clear the interrupt flag 
    FB_TEMP2_ADC_IF = 0;
    #if (FB_IOUT1_ENABLE)
    FB_IOUT2_ADC_IF = 0;  
    #elif (FB_IIN1_ENABLE)
    FB_IIN2_ADC_IF = 0;  
    #else
    #pragma message "WARNING: NO VOLTAGE FEEDBACK SIGNAL HAS BEEN SELECTED FOR USB PORT #2"
    #endif   

#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    ECP44_CLEAR;
#endif
    
#if defined CH2|| defined ALL
//LATCbits.LATC2 = 0;
#endif

}
#else
//    #pragma message "WARNING: NO CURRENT FEEDBACK SIGNAL HAS BEEN ENABLED FOR USB PORT #2"
#endif


// EOF
