
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

#ifndef PWM_H
#define	PWM_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

struct PWM_INSTANCE;

//Configures final output conditions for PWM and enabled module
void PWM_InitOutputState(struct PWM_INSTANCE *pInstance, uint8_t PWMOutputMode, bool swapPWMOutput, uint8_t PWMFLData, uint8_t PWMCLData);
//Configures Switching Freq, Duty Cycle, Phase and DT registers 
void PWM_InitTimeBase(struct PWM_INSTANCE *pInstance, uint16_t PWMSwitchingPeriod, int16_t PWMDutyCyclePercentage, uint16_t PWMPhaseShift, uint16_t PWMDeadTimeH, uint16_t PWMDeadTimeL);
//Force update of PWM data registers
void PWM_UpdateOnTime(struct PWM_INSTANCE *pInstance, uint16_t newOnTimeRegisterValue);
//Disable PWM generator
void PWM_DisableModule(struct PWM_INSTANCE *pInstance);

//Option to override PWM manually if fault condition
void PWM_OverrideChannel(struct PWM_INSTANCE *pInstance, bool overrideHighPWM, bool overrideLowPWM, uint8_t overrideData);
//Configure Leading Edge blanking
void PWM_InitLEBState(struct PWM_INSTANCE *pInstance, uint16_t LEBDelay, bool PWMHighRis, bool PWMHighFall, bool PWMLowRis, bool PWMLowFall);
//Configure PWM trigger points
void PWM_InitTrigger(struct PWM_INSTANCE *pInstance, uint16_t triggerA, uint16_t triggerB, uint16_t triggerC);
//Sets PWM trigger to ADC trigger
void PWM_InitADCTrig1(struct PWM_INSTANCE *pInstance, uint8_t pstScaleTrig, bool trigSrcA, bool trigSrcB, bool trigSrcC);
void PWM_InitADCTrig2(struct PWM_INSTANCE *pInstance, bool trigSrcA, bool trigSrcB, bool trigSrcC);
//Configures PWM control interface logic for current limit, doesnt support termination logic only manually terminates when PCI source transitions
void PWM_InitPCILogicCL(struct PWM_INSTANCE *pInstance, bool acceptQaulPol, uint8_t acceptQualSrc, bool pciPol, uint8_t pciSrcSelect, uint8_t pciAcceptCriteria);

#endif	/* PWM_H */

