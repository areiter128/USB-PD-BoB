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


volatile uint16_t initialize_adc(void) {
    
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
    while (ADCON5Lbits.SHRRDY !=1)  // Polling the Shared ADC analog circuit until it's ready
    ADCON3Hbits.SHREN       = 1;    // Enabling Shared ADC Core digital circuits
    
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
