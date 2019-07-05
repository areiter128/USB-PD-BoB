
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
#include "pwm.h"

//Note: This code is intended to be used with the "High Resolution PWM with Fine Edge Placement" 
//module, like implemented on the dsPIC33CH128MP508.

//High Speed PWM w/FEP register block structure, as implemented in the dsPIC33CH128MP508 device
struct PWM_INSTANCE
{
    uint16_t PGxCONL;
    uint16_t PGxCONH;
    uint16_t PGxSTAT;
    uint16_t PGxIOCONL;
    uint16_t PGxIOCONH;
    uint16_t PGxEVTL;
    uint16_t PGxEVTH;
    uint16_t PGxFPCIL;
    uint16_t PGxFPCIH;
    uint16_t PGxCLPCIL;
    uint16_t PGxCLPCIH;
    uint16_t PGxFFPCIL;
    uint16_t PGxFFPCIH;
    uint16_t PGxSPCIL;
    uint16_t PGxSPCIH;
    uint16_t PGxLEBL;
    uint16_t PGxLEBH;
    uint16_t PGxPHASE;
    uint16_t PGxDC;
    uint16_t PGxDCA;
    uint16_t PGxPER;
    uint16_t PGxTRIGA;
    uint16_t PGxTRIGB;
    uint16_t PGxTRIGC;
    uint16_t PGxDTL;
    uint16_t PGxDTH;
    uint16_t PGxCAP;    
};

//Note: Below function configures the module to run from the AFPLLO in 1:1.  
//So, to run the PWM module at 500MHz, pre-configure the AUX PLL AFPLLO frequency for 500MHz.
//Note 2: Although this function is primarily module specific, it does write to the common PCLKCON register
//shared by the various PWM modules.
//Note 3: Assumes using local time base not MASTER. Could create an additional API that configures MASTER settings independently 
//Note 4: Assumes Independent Edge PWM mode
void PWM_InitTimeBase(struct PWM_INSTANCE *pInstance, uint16_t PWMSwitchingPeriod, int16_t PWMDutyCyclePercentage, uint16_t PWMPhaseShift, uint16_t PWMDeadTimeH, uint16_t PWMDeadTimeL)
{
    //Setup master/common settings for all high res PWM modules
    //PCLKCON = 0x0001;       //Master clock input: 00 = p13_clock, 01 = AUX PLL VCO /2, 10 = pll_div_clk, 11 = aux_clk
    //PCLKCON = 0x0000;       //Master clock input: 00 = Fosc
    PCLKCON = 0x0003;       //Master clock input: 11 = AFPLLO
      
    pInstance->PGxCONL = 0x0008;       //Clock source is MCLK in 1:1, independent edge PWM mode
    pInstance->PGxCONH = 0x0000;       //This PWM module uses the local duty cycle/period registers, not the common ones. 
    
    pInstance->PGxPHASE = PWMPhaseShift;         //PWM phase
    pInstance->PGxDC = (__builtin_mulus(PWMSwitchingPeriod, PWMDutyCyclePercentage) >> 15);    //PWM duty cycle
    pInstance->PGxPER = PWMSwitchingPeriod;      //PWM period
    pInstance->PGxDTH = PWMDeadTimeH;
    pInstance->PGxDTL = PWMDeadTimeL;
}


void PWM_InitOutputState(struct PWM_INSTANCE *pInstance, uint8_t PWMOutputMode, bool swapPWMOutput, uint8_t PWMFLData, uint8_t PWMCLData)
{
    //Load up PWMx module register settings
    
    pInstance->PGxIOCONL |= (swapPWMOutput << 14);
    pInstance->PGxIOCONL |= ((PWMFLData << 2) | (PWMCLData << 4));
    
    pInstance->PGxIOCONH =  PWMOutputMode;      //TimeBase capture and deadtime compensation cleared
        
    //Enable the PWMx Module now (should see output on PWMxH or PWMxL output pin (as configured)
    pInstance->PGxCONL |= 0x8000;   //ON = 1, module enabled now!
}


void PWM_InitTrigger(struct PWM_INSTANCE *pInstance, uint16_t triggerA, uint16_t triggerB, uint16_t triggerC)
{
    pInstance->PGxTRIGA = triggerA;
    pInstance->PGxTRIGB = triggerB;
    pInstance->PGxTRIGC = triggerC;
}

void PWM_InitADCTrig1(struct PWM_INSTANCE *pInstance, uint8_t pstScaleTrig, bool trigSrcA, bool trigSrcB, bool trigSrcC)
{
    pInstance->PGxEVTL |= ((pstScaleTrig << 11) | (trigSrcA << 8) | (trigSrcB << 9) | (trigSrcC << 10));
    
}

void PWM_InitADCTrig2(struct PWM_INSTANCE *pInstance, bool trigSrcA, bool trigSrcB, bool trigSrcC)
{
    pInstance->PGxEVTH |= ((trigSrcA << 5) | (trigSrcB << 6) | (trigSrcC << 7));
        
}

void PWM_InitPCILogicCL(struct PWM_INSTANCE *pInstance, bool acceptQaulPol, uint8_t acceptQualSrc, bool pciPol, uint8_t pciSrcSelect, uint8_t pciAcceptCriteria)
{
    pInstance->PGxCLPCIL |= 0x1000;     // Set auto-terminate
    
    pInstance->PGxCLPCIL |= ((acceptQaulPol<<11) | (acceptQualSrc<<8) | (pciPol<<5) | (pciSrcSelect));
    
    pInstance->PGxCLPCIH |= (pciAcceptCriteria<<8);

}

//Updates the PWM output duty cycle/on time.
void PWM_UpdateOnTime(struct PWM_INSTANCE *pInstance, uint16_t newOnTimeRegisterValue)
{    
    //Update the PWM duty cycle register now.
    pInstance->PGxDC = newOnTimeRegisterValue;
    
    //Let the hardware know we wrote new value to the register and it should perform an internal bufferred update procedure.
    pInstance->PGxSTAT |= 0x0008;   //Set the UPDREQ bit to initiate the hardware update
}

void PWM_InitLEBState(struct PWM_INSTANCE *pInstance, uint16_t LEBDelay, bool PWMHighRis, bool PWMHighFall, bool PWMLowRis, bool PWMLowFall)
{
    pInstance->PGxLEBL = LEBDelay;
    
    pInstance->PGxLEBH |= ((PWMHighRis<<3)|(PWMHighFall<<2)|(PWMLowRis<<1)|(PWMLowFall)); 
    
}

//Disables the specified PWM module by clearing the respective PGxCONL<ON> bit.
void PWM_DisableModule(struct PWM_INSTANCE *pInstance)
{    
    //Clear the ON bit to turn off the module
    pInstance->PGxCONL &= 0x7FFF;
}

//*******************************
//EOF PWM.c

