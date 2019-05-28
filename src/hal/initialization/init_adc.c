/*
 * File:   adc.c
 * Author: M91281
 *
 * Created on April 15, 2019, 1:47 PM
 */



#include <xc.h>
#include "mcal/mcal.h"
#include "hal/hal.h"


// local defines
#define TRIGA1_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM1 & PWM2
#define TRIGA5_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM5 & PWM7

#define SAMPLING_TIME               10     // X*TAD sampling time for the shared core ADC

// local variables
volatile uint16_t UTH_ADCAN9_TRIPPED, LTH_ADCAN9_TRIPPED;
volatile uint16_t UTH_ADCAN18_TRIPPED, LTH_ADCAN18_TRIPPED;

#define ADCRDY_TIMEOUT      5000

volatile uint16_t initialize_adc(void) {
    
    volatile uint16_t timeout=0;
    
    volatile uint16_t fres = 0;
    volatile REGBLK_ADCON1_t adcon1;
    volatile REGBLK_ADCON2_t adcon2;
    volatile REGBLK_ADCON3_t adcon3;
    volatile REGBLK_ADCON4_t adcon4;
    volatile REGBLK_ADCON5_t adcon5;

    
    // Run basic initialization of ADC module features
    adcon1.ADCON1.ADON = ADCON1_ADON_DISABLED; // Make sure ADC module is off
    adcon1.ADCON1.ADSIDL = ADCON1_ADSIDL_RUN; // Run core in doze mode
    adcon1.ADCON1.SHRRES = ADCON1_SHRRES_12BIT; // ADC resolution = 12-bit (0...4095 ticks)
    adcon1.ADCON1.FORM = ADCON1_FORM_INTEGER; // Produce integer (right-aligned) numbers
    
    adcon2.ADCON2.SHRADCS = ADCON2_SHRADCS_DIV_MIN; // shared core clock divider = 2:1 (minimum)
    adcon2.ADCON2.SHRSAMC = ADCON2_SHRSAMC_0010; // 10x TAD sampling time 
    adcon2.ADCON2.REFCIE = ADCON2_REFCIE_OFF; // no error interrupt is triggered when Vref becomes available
    adcon2.ADCON2.REFERCIE = ADCON2_REFERCIE_OFF; // no error interrupt is triggered when Vref fails
    adcon2.ADCON2.REFERR = ADCON2_REFERR_OK; // reset error flag
    adcon2.ADCON2.REFRDY = ADCON2_REFRDY_NOT_READY; // reset bandgap status bit
    adcon2.ADCON2.EIEN = ADCON2_EIEN_ON; // enable early interrupts
    adcon2.ADCON2.SHREISEL = ADCON2_SHREISEL_8TAD; // ADC interrupts are triggered 8 TAD clocks ahead of completion
    
    adcon3.ADCON3.CLKSEL = ADCON3_CLKSEL_FOSC; //ADCON3_CLKSEL_AFVCODIV; // set ADC clock to auxiliary clock (common clock with PWM)
    adcon3.ADCON3.CLKDIV = ADCON3_CLKDIV_1; // set ADC input clock divider
    adcon3.ADCON3.SHREN = ADCON3_CxEN_ENABLED; // enable shared ADC core
    adcon3.ADCON3.CNVCHSEL = ADCON3_CNVCHSEL_AN0; // set AN0 to be target for software triggers (not used)
    adcon3.ADCON3.CNVRTCH = ADCON3_CNVRTCH_READY; // reset TRIGGER READY flag bit
    adcon3.ADCON3.REFSEL = ADCON3_REFSEL_AVDD_AVSS; // set ADC reference to AVDD-toAVSS
    adcon3.ADCON3.SHRSAMP = ADCON3_SHRSAMP_HWTRIG; // use hardware trigger
    adcon3.ADCON3.SUSPCIE = ADCON3_SUSPCIE_DISABLED; // disable ISR SUSPEND interrupt 
    adcon3.ADCON3.SUSPEND = ADCON3_SUSPEND_RUN; // disable SUSPEND MODE
    adcon3.ADCON3.SUSPRDY = ADCON3_SUSPRDY_RUNNING; // reset SUSPEND mode status flag bit
    adcon3.ADCON3.SWCTRG = ADCON3_SWCTRG_READY; // set software trigger to READY
    adcon3.ADCON3.SWLCTRG = ADCON3_SWLCTRG_LVLTRG_BY_HW; // set level sensitive triggers for hardware
    adcon3.ADCON3.CNVCHSEL = ADCON3_CNVCHSEL_AN0; // configure the ADC inputs used (not used))
    
    adcon4.value = 0;
    adcon4.ADCON4.C0CHS = ADCON4_C0CHS_S1AN0;
    adcon4.ADCON4.C1CHS = ADCON4_C1CHS_S1AN1;
    adcon4.ADCON4.SAMC0EN = ADCON4_SAMCxEN_DISABLED;
    adcon4.ADCON4.SAMC1EN = ADCON4_SAMCxEN_DISABLED;
//    adcon4.ADCON4.SYNCTRG0 = ADCON4_SYNCTRGx_SYNC_TO_SOURCE;
//    adcon4.ADCON4.SYNCTRG1 = ADCON4_SYNCTRGx_SYNC_TO_SOURCE;
    
    adcon5.ADCON5.SHRCIE = ADCON5L_CxCIE_DISABLED; // enable shared core to generate common interrupts
    adcon5.ADCON5.SHRPWR = ADCON5_CxPWR_OFF; // Power off Shared Core => will be turned on later
    adcon5.ADCON5.WARMTIME = ADCON5H_WARMTIME_CLK_32768;

    // Turn on ADC module power
    fres = hsadc_module_power_up();
    fres &= hsadc_module_disable();

    // Run initialization of ADC module features (no power on yet)
    fres &= hsadc_init_adc_module(adcon1, adcon2, adcon3, adcon4, adcon5);

    // Set ADC Interrupt Trigger for the ADC inputs
    
    // series of 3 conversion tied to ADC TRIGGER #1
//    fres &= hsadc_set_adc_input_trigger_source(VBATA_FB_ADC_AN_INPUT, REG_ADTRIGxL_TRGSRC_MSTR_PWM2_TRIG1); // set trigger source
//    fres &= hsadc_set_adc_input_interrupt(VBATA_FB_ADC_AN_INPUT, ADIE_ANx_ON, ADEIE_ANx_ON); // enable VSNS interrupt with early generation enabled
//
//    fres &= hsadc_set_adc_input_trigger_source(V_DCLINK_FB2_ADC_AN_INPUT, REG_ADTRIGxL_TRGSRC_MSTR_PWM2_TRIG1); // set trigger source
//    fres &= hsadc_set_adc_input_interrupt(V_DCLINK_FB2_ADC_AN_INPUT, ADIE_ANx_OFF, ADEIE_ANx_OFF); // disable V_DCLINK interrupt
//
//    // series of 3 conversion tied to ADC TRIGGER #2
//    fres &= hsadc_set_adc_input_trigger_source(IBATA_FB_ADC_AN_INPUT, REG_ADTRIGxL_TRGSRC_MSTR_PWM2_TRIG2); // set trigger source
//    fres &= hsadc_set_adc_input_interrupt(IBATA_FB_ADC_AN_INPUT, ADIE_ANx_ON, ADEIE_ANx_ON); // enable VSNS interrupt with early generation enabled
//
//    
//    // Set ADC interrupt
//    VBATA_FB_ADC_IP = 5; // interrupt priority needs to be in sync with the config bit setting <#pragma config CTXT1 = IPL5>
//    VBATA_FB_ADC_IF = 0; // reset VOUT feedback interrupt flag bit
//    VBATA_FB_ADC_IE = 1; // enable VOUT feedback interrupt
//
//    IBATA_FB_ADC_IP = 5; // interrupt priority needs to be in sync with the config bit setting <#pragma config CTXT1 = IPL5>
//    IBATA_FB_ADC_IF = 0; // reset VOUT feedback interrupt flag bit
//    IBATA_FB_ADC_IE = 1; // enable VOUT feedback interrupt
//
//    // Enable ADC Module
//    fres &= hsadc_module_enable();
//   
//    // power up ADC core (only one shared core available on RHEA)
//    fres &= hsadc_power_on_adc_core(VBATA_FB_ADCCORE);
//    fres &= hsadc_power_on_adc_core(IBATA_FB_ADCCORE);
//    fres &= hsadc_power_on_adc_core(V_DCLINK_FB2_ADCCORE);

// =======================================================================
// ISTVAN CODE    
    
    // Configure the I/O pins to be used as analog inputs.
    ANSELAbits.ANSELA2  = 1; TRISAbits.TRISA2  = 1; // AN9/RA2 connected the shared core
    ANSELDbits.ANSELD10 = 1; TRISDbits.TRISD10 = 1; // AN18/RD10 connected the shared core
    
    
    ADCON1Lbits.ADON    = 0;    // Disable ADC - Set the ADON bit only after the ADC module has been configured
    ADCON1Lbits.ADSIDL  = 0;    // Leave it as default - ADC operation is enabled in Idle mode  
    
    /* Select the common ADC clock source and configure the pre-scaler */
    ADCON3Hbits.CLKSEL  = 0b00; // Fp (Peripheral Clock) - The ADC input clock frequency, selected by the CLKSEL<1:0> bits, must not exceed 560 MHz
    ADCON3Hbits.CLKDIV  = 0x00; // 1 Source Clock Period - The ADC clock frequency, after the divider selected by the CLKDIV<5:0> bits, must not exceed 280 MHz        
    
    /* Select the clock period for the ADC core */
    ADCON2Lbits.SHRADCS     = 0x00; // Shared core clock divider = 2:1 (minimum)
    
    /* Configure the ADC reference sources */
    ADCON3Lbits.REFSEL  = 0b000;    // VrefH = AVDD, VrefL = AVSS
    
    /* Select the result resolution for the ADC core */
    ADCON1Hbits.SHRRES  = 0b11; // Shared ADC core resolution is set to 12-bit  
     
    /* Configure the data output format */
    ADCON1Hbits.FORM    = 0;    // Setting integer data output format
    
    /* Select single-ended or differential input configuration and output format for each input channel */
       ADMOD0Hbits.DIFF9   = 0;    // AN13 input channel is single ended
       ADMOD0Hbits.SIGN9   = 0;    // Output data for AN13 is unsigned
       ADMOD1Lbits.DIFF18  = 0;    // AN13 input channel is single ended
       ADMOD1Lbits.SIGN18  = 0;    // Output data for AN13 is unsigned
   
    /* If the shared ADC core is used, configure the Shared ADC Core Sample Time Selection bits */
     ADCON2Hbits.SHRSAMC     = SAMPLING_TIME-2; // Shared core sampling time (minimum 2*TAD)
     
    /* Configure and enable the ADC interrupts */ 
    ADCON2Lbits.EIEN     = 1;    // Early interrupts are enabled
    ADEIELbits.EIEN9     = 1;    // Enabling early interrupt for AN9
    ADEIEHbits.EIEN18    = 1;    // Enabling early interrupt for AN18
    ADCON2Lbits.SHREISEL = 0x7;  // Shared core ADC interrupts are triggered 8 TAD clock ahead of completion
    
    FB_IOUT2_ADC_IP = 5;    // Setting priority level to 5 
    FB_IOUT2_ADC_IF = 0;    // Clearing ADCAN9 interrupt flag.
    FB_IOUT2_ADC_IE = 1;    // Enabling interrupt for ADCAN9
    
    FB_IOUT1_ADC_IP = 5;    // Setting priority level to 5 
    FB_IOUT1_ADC_IF = 0;    // Clearing ADCAN18 interrupt flag
    FB_IOUT1_ADC_IE = 1;    // Enabling interrupt for ADCAN18
    
    /* Set the ADON bit in the ADCON1L register to enable the module and set the
     * WARMTIME<3:0> bits in the ADCON5H register to provide at least 10 us for the initialization  */ 
    ADCON1Lbits.ADON        = 1;    // Enabling ADC module
    ADCON5Hbits.WARMTIME    = 0xF;  // 32768 Core Source Clock Periods
    
    /* Turn on the module power: */
    ADCON5Lbits.SHRPWR      = 1;    // Enabling Shared ADC Core analog circuits power
    while ((!ADCON5Lbits.SHRRDY) && (timeout++<ADCRDY_TIMEOUT));  // Polling the Shared ADC analog circuit until it's ready
    if(timeout>=ADCRDY_TIMEOUT)
    { 
        return(0); 
    }
    else
    {
        ADCON3Hbits.SHREN       = 1;    // Enabling Shared ADC Core digital circuits
    }
    return(1); // ToDo: need function execution success validation
    
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
