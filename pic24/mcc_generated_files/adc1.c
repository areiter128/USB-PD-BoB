
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : 1.55
        Device            :  PIC24FJ64GA004
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.34
        MPLAB 	          :  MPLAB X v4.15
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc1.h"
//manually added code, do not remove or overwrite
#include <stdbool.h>
#include "interrupt_manager.h"

//manually added code, do not remove or overwrite
#define AVG_SIZE   2048

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/

//manually added code, do not remove or overwrite
static uint32_t adc_average = 0;
static volatile uint32_t adc_value = 0;
static volatile bool adc_ready = 0;

void ADC1_Initialize (void)
{
    // ASAM enabled; ADSIDL disabled; DONE disabled; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; ADON enabled; 

   AD1CON1 = 0x80E4;

    // CSCNA enabled; VCFG0 AVDD; VCFG1 AVSS; ALTS disabled; BUFM disabled; SMPI Generates interrupt after completion of every sample/conversion operation; 

   AD1CON2 = 0x0404;

    // SAMC 20; ADRC FOSC/2; ADCS 49; 

   AD1CON3 = 0x1431;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

   AD1CHS = 0x0000;

    // CSSL9 disabled; CSSL8 disabled; CSSL7 disabled; CSSL6 disabled; CSSL5 disabled; CSSL4 enabled; CSSL3 disabled; CSSL2 disabled; CSSL15 disabled; CSSL1 disabled; CSSL0 disabled; CSSL12 disabled; CSSL11 disabled; CSSL10 disabled; 

   AD1CSSL = 0x0010;


   adc1_obj.intSample = AD1CON2bits.SMPI;
   
   // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;
}

void ADC1_Start(void)
{
   AD1CON1bits.SAMP = 1;
}
void ADC1_Stop(void)
{
   AD1CON1bits.SAMP = 0;
}
uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<=adc1_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}
uint16_t ADC1_ConversionResultGet(void)
{
    return ADC1BUF0;
}
bool ADC1_IsConversionComplete( void )
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}
void ADC1_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}

//enters here at every 200us
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADC1Interrupt ( void )
{
    //manually added code, do not remove or overwrite
    static uint16_t adc_counter = 0;
    adc_average += ADC1BUF0;
    adc_counter++;
    if(adc_counter == AVG_SIZE)
    {
        adc_counter = 0;
        adc_value = adc_average;
        adc_average = 0;
        adc_ready = 1;
    }
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}

//manually added code, do not remove or overwrite
uint16_t ADC1_ReadAvg(void)
{
    static uint16_t retval = 0;
    uint32_t tempval;
    if(adc_ready)
    {
        NoInterrupts();
        tempval = adc_value;
        adc_ready = 0;
        Interrupts();
        retval = (uint16_t)(tempval/AVG_SIZE);
    }
    return retval;
}
        
/**
  End of File
*/
