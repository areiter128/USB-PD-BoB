
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

#ifndef COMPENSATOR_H
#define COMPENSATOR_H

#include <stdbool.h>

// ADC parameters
#define ADCREFERENCE        3.3
#define ADCRESOLUTION     4095UL

// Output Voltage Setpoints
#define BUCKVOLTAGEOUT      3.30   // Buck output voltage in volts
#define BOOSTVOLTAGEOUT    15.00   // Boost output voltage in volts

//buck feedback gains   
#define VBUCKFBGAIN   0.5   // 1k /(1k+1k)
#define BUCKVOLTAGEREFERENCEADC (unsigned int)(VBUCKFBGAIN * ADCRESOLUTION * BUCKVOLTAGEOUT / ADCREFERENCE)
#define BUCKVOLTAGE_GET(X)      (double)(((unsigned long)(X) * ADCREFERENCE) / (VBUCKFBGAIN * ADCRESOLUTION))

// Soft-Start Control
#define BUCK_SOFT_START_DURATION		10000000ul          // 10ms 
#define BUCK_SOFT_START_CALLRATE		10000ul             // 5*Controller rate in ns 

//boost feedback gains   
#define VBOOSTFBGAIN   0.125   // 1k /(1k+7k)
#define BOOSTVOLTAGEREFERENCEADC (unsigned int)(VBOOSTFBGAIN * ADCRESOLUTION * BOOSTVOLTAGEOUT / ADCREFERENCE)
#define BOOSTVOLTAGE_GET(X)      (double)(((unsigned long)(X) * ADCREFERENCE) / (VBOOSTFBGAIN * ADCRESOLUTION))

// Soft-Start Control
#define BOOST_SOFT_START_DURATION		20000000ul          // 20ms 
#define BOOST_SOFT_START_CALLRATE		10000ul             // 5*Controller rate in ns 

//input divider gains   
#define VINPUTFBGAIN   0.125   // 1k /(1k+7k)
#define INPUTVOLTAGE_GET(X)      (double)(((unsigned long)(X) * ADCREFERENCE) / (VINPUTFBGAIN * ADCRESOLUTION))

#define VINMAXFAULT             13.8
#define VINMAXFAULT_ADC         (unsigned int)(VINPUTFBGAIN * ADCRESOLUTION * VINMAXFAULT / ADCREFERENCE)
#define VINMAXFAULT_HYS_ADC     (unsigned int)(VINPUTFBGAIN * ADCRESOLUTION * (VINMAXFAULT-0.8) / ADCREFERENCE)

#define VINMINFAULT             6
#define VINMINFAULT_ADC         (unsigned int)(VINPUTFBGAIN * ADCRESOLUTION * VINMINFAULT / ADCREFERENCE)
#define VINMINFAULT_HYS_ADC     (unsigned int)(VINPUTFBGAIN * ADCRESOLUTION * (VINMINFAULT-0.5) / ADCREFERENCE)

#define FAULT_RESTART_TIME      5  // x*10ms = 50ms

void ConverterBuckInit(void);
void ConverterBoostInit(void);
void BuckSoftStartInit(void);
void BoostSoftStartInit(void);

double   GetVoltageBuck(void);
double   GetVoltageBoost(void);
double   GetVoltageInput(void);
uint16_t GetDacBuck(void);
uint16_t GetDacBoost(void);

#endif	/* COMPENSATOR_H */

