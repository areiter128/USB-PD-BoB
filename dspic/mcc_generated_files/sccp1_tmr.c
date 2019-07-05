/**
  SCCP1 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    sccp1.c

  @Summary
    This is the generated driver implementation file for the SCCP1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides implementations for driver APIs for SCCP1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  dsPIC33CK256MP505
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05
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
#include "sccp1_tmr.h"

/**
  Section: Data Type Definitions
*/

/**
  SCCP1 Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

*/
typedef struct _SCCP1_TMR_OBJ_STRUCT
{

    /* Timer Elapsed */
    bool                                                    primaryTimer16Elapsed;
    bool                                                    secondaryTimer16Elapsed;
    bool                                                    Timer32Elapsed;
} SCCP1_TMR_OBJ;

static SCCP1_TMR_OBJ sccp1_timer_obj;
void SCCP1_TMR_Initialize(void)
{
    // CCPON enabled; MOD 16-Bit/32-Bit Timer; CCSEL disabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:1; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP1CON1L = (0x8000 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; IOPS Each Time Base Period Match; SYNC None; OPSRC Timer Interrupt Event; 
    CCP1CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP1CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC1; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP1CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP1CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; TRCLR disabled; 
    CCP1STATL = 0x00;
    //TMR 0; 
    CCP1TMRL = 0x00;
    //TMR 0; 
    CCP1TMRH = 0x00;
    //PR 1000; 
    CCP1PRL = 0x3E8;
    //PR 0; 
    CCP1PRH = 0x00;
    //CMP 0; 
    CCP1RAL = 0x00;
    //CMP 0; 
    CCP1RBL = 0x00;
    //BUF 0; 
    CCP1BUFL = 0x00;
    //BUF 0; 
    CCP1BUFH = 0x00;

    CCP1CON1Lbits.CCPON = 0x1; //Enabling CCP

    IFS0bits.CCP1IF = 0;

    IFS0bits.CCT1IF = 0;
      
    // Enabling SCCP1 interrupt.
    IEC0bits.CCP1IE = 1;

    // Enabling SCCP1 interrupt.
    IEC0bits.CCT1IE = 1;

}

void SCCP1_TMR_Start( void )
{
    /* Reset the status information */
    sccp1_timer_obj.primaryTimer16Elapsed = false;
    sccp1_timer_obj.secondaryTimer16Elapsed = false;
    sccp1_timer_obj.Timer32Elapsed = false;

    /* Start the Timer */
    CCP1CON1Lbits.CCPON = true;
}
void SCCP1_TMR_Stop( void )
{
    /* Stop the Timer */
    CCP1CON1Lbits.CCPON = false;
}

void __attribute__ ( (interrupt, no_auto_psv , weak) ) _CCT1Interrupt ( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS0bits.CCT1IF)
    {         
        sccp1_timer_obj.primaryTimer16Elapsed = true;
        IFS0bits.CCT1IF = 0;
    }
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCP1Interrupt ( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS0bits.CCP1IF)
    {
        sccp1_timer_obj.secondaryTimer16Elapsed = true;
        IFS0bits.CCP1IF = 0;
    }
}

void SCCP1_TMR_Period16BitPrimarySet( uint16_t value )
{
    /* Update the counter values */
    CCP1PRL = value;

    /* Reset the status information */
    sccp1_timer_obj.primaryTimer16Elapsed = false;
}
void SCCP1_TMR_Period16BitSecondarySet( uint16_t value )
{
    /* Update the counter values */
    CCP1PRH = value;

    /* Reset the status information */
    sccp1_timer_obj.secondaryTimer16Elapsed = false;
}
uint16_t SCCP1_TMR_Period16BitPrimaryGet( void )
{
    return( CCP1PRL );
}
uint16_t SCCP1_TMR_Period16BitSecondaryGet( void )
{
    return( CCP1PRH );
}
void SCCP1_TMR_Counter16BitPrimarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP1PRL = value;
    /* Reset the status information */
    sccp1_timer_obj.primaryTimer16Elapsed = false;
}
void SCCP1_TMR_Counter16BitSecondarySet ( uint16_t value )
{
    /* Update the counter values */
    CCP1PRH = value;
    /* Reset the status information */
    sccp1_timer_obj.secondaryTimer16Elapsed = false;
}
uint16_t SCCP1_TMR_Counter16BitPrimaryGet( void )
{
    return( CCP1TMRL );
}

uint16_t SCCP1_TMR_Counter16BitSecondaryGet( void )
{
    return( CCP1TMRH );
}

bool SCCP1_TMR_PrimaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp1_timer_obj.primaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp1_timer_obj.primaryTimer16Elapsed = false;
    }
    return status;
}
bool SCCP1_TMR_SecondaryTimer16ElapsedThenClear(void)
{
    bool status;
    
    status = sccp1_timer_obj.secondaryTimer16Elapsed ;
    
    if(status == true)
    {
        sccp1_timer_obj.secondaryTimer16Elapsed = false;
    }
    return status;
}

/**
 End of File
*/