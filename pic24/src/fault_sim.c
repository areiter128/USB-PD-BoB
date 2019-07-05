
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

#include "delay.h"
#include "tmr1.h"
#include <stdlib.h>

#define TIME_LIMIT_MIN   5000  // milliseconds
#define TIME_LIMIT_MAX   (5000 + TIME_LIMIT_MIN)

#define FLT_BUCK_OVP     LATCbits.LATC7
#define FLT_BUCK_OCP     LATCbits.LATC6
#define FLT_BOOST_OVP    LATBbits.LATB9
#define FLT_BOOST_OCP    LATCbits.LATC9

#define CLR_BUCK_OVP     LATBbits.LATB11
#define CLR_BUCK_OCP     LATBbits.LATB10
#define CLR_BOOST_OVP    LATBbits.LATB13
#define CLR_BOOST_OCP    LATBbits.LATB12

static void _FaultSimTrigger(uint8_t select)
{
    switch(select & 3)
    {
        case 0: FLT_BUCK_OVP = 1;  break;
        case 1: FLT_BUCK_OCP = 1;  break;
        case 2: FLT_BOOST_OVP = 1; break;
        case 3: FLT_BOOST_OCP = 1; break;
        default: break;
    }
}

void _FaultSim_BCK_C(void)
{
    FLT_BUCK_OCP = 0;
}

void _FaultSim_BCK_V(void)
{
    FLT_BUCK_OVP = 0;
}

void _FaultSim_BST_C(void)
{
    FLT_BOOST_OCP = 0;
}

void _FaultSim_BST_V(void)
{
    FLT_BOOST_OVP = 0;
}

void _FaultSimRun(void)
{
    static int time_limit = TIME_LIMIT_MIN;
    // the sw timer gets incremented at every 1ms
    if(TMR1_SoftwareCounterGet() > time_limit)
    {
        TMR1_SoftwareCounterClear();
        // returns a random number between TIME_LIMIT_MIN and TIME_LIMIT_MAX milliseconds
        time_limit = TIME_LIMIT_MIN + (int)rand() % (TIME_LIMIT_MAX - TIME_LIMIT_MIN);
        _FaultSimTrigger((uint8_t)time_limit);
    }
}
