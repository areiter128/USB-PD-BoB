
/**********************************************************************
Copyright(c) 2018 Microchip Technology Inc. and its subsidiaries.
Subject to your compliance with these terms, you may use Microchip
software and any derivatives exclusively with Microchip products. It
is your responsibility to comply with third party license terms
applicable to your use of third-party software (including open source
software) that may accompany Microchip software.
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
FOR A PARTICULAR PURPOSE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THIS SOFTWARE.
**********************************************************************/

#include <xc.h>
#include "fault.h"
#include "leds.h"
#include "delay.h"
#include "fault_sim.h"
#include "interrupt_manager.h"

#if FAULT_SIM
    #define FLT_BUCK_OVP     (PORTCbits.RC7 | LATCbits.LATC7)
    #define FLT_BUCK_OCP     (PORTCbits.RC6 | LATCbits.LATC6)
    #define FLT_BOOST_OVP    (PORTCbits.RC8 | LATCbits.LATC8)
    #define FLT_BOOST_OCP    (PORTCbits.RC9 | LATCbits.LATC9)
#else  // FAULT_SIM
    #define FLT_BUCK_OVP     PORTCbits.RC7
    #define FLT_BUCK_OCP     PORTCbits.RC6
    #define FLT_BOOST_OVP    PORTCbits.RC8 
    #define FLT_BOOST_OCP    PORTCbits.RC9
#endif // FAULT_SIM

#define CLR_BUCK_OVP     LATBbits.LATB11
#define CLR_BUCK_OCP     LATBbits.LATB10
#define CLR_BOOST_OVP    LATBbits.LATB13
#define CLR_BOOST_OCP    LATBbits.LATB12

#define CLR_DELAY    200 // 200 * 5ms = 1s
#define CLR_PULSE    50  // us

static volatile bool fault_flags[4];
static uint16_t fault_counters[4];

void   FaultInit(void)
{
    volatile uint8_t i;
    NoInterrupts();
    for(i = 0; i < 4; i++)
    {
        fault_flags[i] = 0;
        fault_counters[i] = 0;
    }

    // protection fault inputs
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC9 = 1;
    TRISBbits.TRISB9 = 1;
            
    // CLR signals off - 1 logic
    CLR_BUCK_OVP = 1;
    CLR_BUCK_OCP = 1;
    CLR_BOOST_OVP = 1;
    CLR_BOOST_OCP = 1;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    Interrupts();
}

uint8_t FaultCheck(void)
{
    volatile uint8_t faultStatus = 0, fault_id;
    FaultSimRun();
    
    for(fault_id = 0; fault_id < 4; fault_id++)
    {
        NoInterrupts();
        if(fault_flags[fault_id])
            faultStatus |= (1 << fault_id);
        Interrupts();
    }
    
    if(faultStatus & (1 << FAULT_BUCK_OCP))
        LedBlink(LED_BUCK_ERROR);
    else if(faultStatus & (1 << FAULT_BUCK_OVP))
        LedOn(LED_BUCK_ERROR);
    else
        LedOff(LED_BUCK_ERROR);

   if(faultStatus & (1 << FAULT_BOOST_OCP))
        LedBlink(LED_BOOST_ERROR);
    else if(faultStatus & (1 << FAULT_BOOST_OVP))
        LedOn(LED_BOOST_ERROR);
    else
        LedOff(LED_BOOST_ERROR);

   return faultStatus;
}

static bool FaultInput(uint8_t fault_id)
{
    switch(fault_id)
    {
        case FAULT_BUCK_OVP:  return (bool)(FLT_BUCK_OVP);
        case FAULT_BUCK_OCP:  return (bool)(FLT_BUCK_OCP);
        case FAULT_BOOST_OVP: return (bool)(FLT_BOOST_OVP);
        case FAULT_BOOST_OCP: return (bool)(FLT_BOOST_OCP);
        default: return 0;
    }
}

static void FaultClear(uint8_t fault_id)
{
    switch(fault_id)
    {
        case FAULT_BUCK_OVP:  
            CLR_BUCK_OVP = 0;  
            __delay_us(CLR_PULSE); 
            FaultSim_BCK_V(); 
            CLR_BUCK_OVP = 1;  
            break;
            
        case FAULT_BUCK_OCP:  
            CLR_BUCK_OCP = 0;  
            __delay_us(CLR_PULSE); 
            FaultSim_BCK_C(); 
            CLR_BUCK_OCP = 1;  
            break;
            
        case FAULT_BOOST_OVP: 
            CLR_BOOST_OVP = 0; 
            __delay_us(CLR_PULSE); 
            FaultSim_BST_V(); 
            CLR_BOOST_OVP = 1; 
            break;
            
        case FAULT_BOOST_OCP: 
            CLR_BOOST_OCP = 0; 
            __delay_us(CLR_PULSE); 
            FaultSim_BST_C(); 
            CLR_BOOST_OCP = 1; 
            break;
            
        default: break;
    }
}

//this is called at each 5 ms
void   FaultTask(void)
{
    volatile uint8_t i;
    
    for(i = 0; i < 4; i++)
    {
        // is fault protection triggered ?
        if(FaultInput(i)) //yes, it is triggered
        {
            // already started counting?
            if(fault_counters[i]) // yes, the protection fault triggered earlier
            {
                fault_counters[i]--; // decrease counter
                if(fault_counters[i] == 0) // until zero then...
                    FaultClear(i); // ...try to clear
            }
            else // no, just detected the fault protection
            {
                fault_counters[i] = CLR_DELAY;
                fault_flags[i] = 1;
            }
        }
        else // no, it isn't triggered
        {
            fault_flags[i] = 0;
        }
    }
}
