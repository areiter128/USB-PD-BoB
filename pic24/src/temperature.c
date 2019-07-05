
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
#include "temperature.h"
#include "leds.h"

#define Voltage()           (double)(VREF*ADC1_ReadAvg()/1024.0)
#define TemperatureRead()   (uint8_t)((Voltage()-VOFFSET) / VOLTS_OVER_DEG)


therm_event_t TemperatureCheck(uint8_t * pTemperature)
{
    static bool stateThermalShutDown = false;
    static bool stateThermalWarning = false;
    therm_event_t ret = THERM_NO_CHANGE;
    uint8_t temperature = TemperatureRead();

    if(stateThermalShutDown)
    {
        if(temperature < (THERMAL_SHUTDOWN - THERMAL_HYSTERESIS))
        {
            stateThermalShutDown = false;
            stateThermalWarning = true;
            ret = THERM_WARNING;
        }
    }
    else
    {
        if(temperature >= (THERMAL_SHUTDOWN + THERMAL_HYSTERESIS))
        {
            stateThermalShutDown = true;
            ret = THERM_ALERT;
        }
        else
        {
            if(stateThermalWarning)
            {
                if(temperature < THERMAL_WARNING)
                {
                    stateThermalWarning = false;
                    ret = THERM_SAFE;
                }
            }
            else
            {
                if(temperature > THERMAL_WARNING)
                {
                    stateThermalWarning = true;
                    ret = THERM_WARNING;
                }
            }
        }
    }

    *pTemperature = temperature;
    return ret;
}



