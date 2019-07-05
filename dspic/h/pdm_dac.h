
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

#ifndef PDM_DAC_H
#define	PDM_DAC_H

#include "stdint.h"
#include "stdbool.h"

struct DAC_INSTANCE;

//------------------------------------------------------------------------------
//Prototypes
//------------------------------------------------------------------------------
void     PDMDAC_Init(struct DAC_INSTANCE *pInstance, int16_t initialValue, bool AFPLLO500MHzAvailable, bool outputToDACOUTPin);
void     PDMDAC_SetValue(struct DAC_INSTANCE *pInstance, int16_t outputCode);
void     PDMDAC_InitDACandCMPWithSlope(struct DAC_INSTANCE *pInstance, uint32_t moduleClockFreq, double DACReferenceVoltage, uint16_t startingDACLevel, double slopeVoltsPerMicrosecond, uint32_t PWMFrequency, bool invertComparatorOutput, uint8_t INSELFieldValue, uint8_t startSlopeTrigger, uint8_t stopSlopeTriggerB, uint8_t stopSlopeTriggerA);
uint16_t PDMDAC_GetValue(struct DAC_INSTANCE *pInstance);

#endif	/* PDM_DAC_H */

