
/**
  TMR1 Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    tmr1.c

  @Summary
    This is the generated source file for the TMR1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for TMR1. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  dsPIC33EP128GS808
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB 	          :  MPLAB X 3.60
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
#include <stdbool.h>
#include <stdint.h>
#include "psf_stdinc.h"

/**
  Section: Data Type Definitions
*/

/** TMR Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintainence of the hardware instance.

  @Description
    This defines the object required for the maintainence of the hardware
    instance. This object exists once per hardware instance of the peripheral.

  Remarks:
    None.
*/


/**
  Section: Driver Interface
*/


uint8_t PD_TMR_Initialize (void)
{
#if 0    
    //TMR1 0; 
    TMR1 = 0x0;
    //Period = 0.0009999168 s; Frequency = 69093750 Hz; PR1 8636; 
    PR1 = 0x2BF2;//0x21BC; // (1ms) //0x21BC (100us);
    //TCKPS 1:8; TON enabled; TSIDL disabled; TCS FOSC/2; TSYNC disabled; TGATE disabled; 
    T1CON = 0x8010;

    IPC0bits.T1IP = 4;   // Set Interrupt Priority
    IFS0bits.T1IF = false;
    IEC0bits.T1IE = true;
    
    /*Enable the interrupt*/
    IEC0bits.T1IE = true;

    /* Start the Timer */
    T1CONbits.TON = 1;
#endif // 0
    // CCPON enabled; MOD 16-Bit/32-Bit Timer; CCSEL disabled; CCPSIDL disabled; TMR32 16 Bit; CCPSLP disabled; TMRPS 1:64; CLKSEL FOSC/2; TMRSYNC disabled; 
    CCP7CON1L = (0x80C0 & 0x7FFF); //Disabling CCPON bit
    //RTRGEN disabled; ALTSYNC disabled; ONESHOT disabled; TRIGEN disabled; IOPS Each Time Base Period Match; SYNC None; OPSRC Timer Interrupt Event; 
    CCP7CON1H = 0x00;
    //ASDGM disabled; SSDG disabled; ASDG 0; PWMRSEN disabled; 
    CCP7CON2L = 0x00;
    //ICGSM Level-Sensitive mode; ICSEL IC1; AUXOUT Disabled; OCAEN disabled; OENSYNC disabled; 
    CCP7CON2H = 0x00;
    //OETRIG disabled; OSCNT None; POLACE disabled; PSSACE Tri-state; 
    CCP7CON3H = 0x00;
    //ICDIS disabled; SCEVT disabled; TRSET disabled; ICOV disabled; ASEVT disabled; TRIG disabled; TRCLR disabled; 
    CCP7STATL = 0x00;
    //TMR 0; 
    CCP7TMRL = 0x00;
    //TMR 0; 
    CCP7TMRH = 0x00;
    //PR 1562; 
    CCP7PRL = 0x61A; //1ms
    //PR 0; 
    CCP7PRH = 0x00;
    //CMP 0; 
    CCP7RAL = 0x00;
    //CMP 0; 
    CCP7RBL = 0x00;
    //BUF 0; 
    CCP7BUFL = 0x00;
    //BUF 0; 
    CCP7BUFH = 0x00;

    CCP7CON1Lbits.CCPON = 0x1; //Enabling CCP

    IFS9bits.CCP7IF = 0;

    IFS9bits.CCT7IF = 0;
      
    IPC37bits.CCT7IP = 4;   // Set Interrupt Priority

    // Enabling SCCP1 interrupt.
    //IEC0bits.CCP1IE = 1;

    // Enabling SCCP1 interrupt.
    IEC9bits.CCT7IE = 1;
    
   /* Start the Timer */
    CCP7CON1Lbits.CCPON = true;


    return(1);
}

/* void PD_TMR_set (upd_timer_t *timer, uint32_t exp_value)
{
    timer->expired_flag = 0;
    timer->timer_count = 0;
    timer->timer_exp_value = exp_value;
    timer->enabled_flag = 1;
}

uint8_t PD_TMR_expired (upd_timer_t *timer)
{
    if (timer->expired_flag)
    {
        timer->expired_flag = 0;
        return (1);
    }
    else
    {
        return (0);
    }
}
 */

void __attribute__ ( ( interrupt, no_auto_psv ) ) _CCT7Interrupt ( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if(IFS9bits.CCT7IF)
    {         
    //    LATCbits.LATC5 ^= 1;
        
        //***User Area Begin
        // Call the PD Stack timer interrupt handler function
        PDTimer_InterruptHandler();
        //***User Area End
        IFS9bits.CCT7IF = 0;
    }
}


/**
 End of File
*/
