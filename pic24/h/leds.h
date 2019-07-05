
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

#ifndef LEDS_H
#define	LEDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "leds.h"


#define LED_BUCK_LOAD_1    0
#define LED_BOOST_LOAD_1   1
#define LED_BUCK_ERROR     2

#define LED_BUCK_LOAD_2    3
#define LED_BOOST_LOAD_2   4
#define LED_BOOST_ERROR    5

#define LED_BUCK_LOAD_3    6
#define LED_BOOST_LOAD_3   7
#define LED_THERMAL_ERROR  8

#define LED_MAX            9

void LedsInit(void);
void LedOn(uint8_t);
void LedOff(uint8_t);
void LedBlink(uint8_t);

extern void LedsMatrixTask(void);
extern void LedsBlinkTask(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LEDS_H */

