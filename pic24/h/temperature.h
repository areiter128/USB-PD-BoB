
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

#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "adc1.h"

#define MCP9700
//#define MCP9701

#define VREF  3.3  //  ADC reference

#ifdef MCP9700
#define VOLTS_OVER_DEG 0.01 // 10mV per Celsius degree
#define VOFFSET 0.5         // 500 mV at 0 degrees 
#endif //MCP9700

#ifdef MCP9701
#define VOLTS_OVER_DEG 0.0195 // 19.5mV per Celsius degree
#define VOFFSET 0.4         // 400 mV at 0 degrees 
#endif //MCP9701

    
#define TemperatureInit()   ADC1_Initialize()

// Celsius degrees
#define THERMAL_WARNING       55
#define THERMAL_SHUTDOWN      75
#define THERMAL_HYSTERESIS     5
    
typedef enum {
    THERM_NO_CHANGE,
    THERM_ALERT,
    THERM_SAFE,
    THERM_WARNING
} therm_event_t;

    
therm_event_t TemperatureCheck(uint8_t * pTemperature);

#ifdef	__cplusplus
}
#endif

#endif	/* TEMPERATURE_H */

