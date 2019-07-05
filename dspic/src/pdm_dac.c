
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
#if defined(__XC16__)
    #include <libpic30.h>
#endif

#include "pdm_dac.h"

//Note: This code is intended for use with with the PDM DACs + Comparators implemented in the dsPIC33CH128MP508.

//------------------------------------------------------------------------------
//Definitions
//------------------------------------------------------------------------------

//Structure with the order of the registers, as implemented in devices like the dsPIC33CH128MP508
struct DAC_INSTANCE
{
    uint16_t DACxCONL;
    uint16_t DACxCONH;
    uint16_t DACxDATL;
    uint16_t DACxDATH;
    uint16_t SLPxCONL;
    uint16_t SLPxCONH;
    uint16_t SLPxDAT;
};


void PDMDAC_Init(struct DAC_INSTANCE *pInstance, int16_t initialValue, bool AFPLLO500MHzAvailable, bool outputToDACOUTPin)
{
    //If the AUX PLL is available and configured for 500MHz AFPLLO frequency, use
    //that as the clock source for the PDM DAC.  However, if not, use the normal FPLLO in 1:1 instead.
    if(AFPLLO500MHzAvailable == true)
    {
        DACCTRL1L = 0x0080;     //AFPLLO assumed to be at 500MHz, with 1:1 DAC clock input dividers
    }
    else
    {
        DACCTRL1L = 0x00C0;     //FPLLO, 1:1 = ex: up to 200MHz, comparator filter clock div = 1:1.
    }
    
    //Configure the DACx module registers
    pInstance->DACxDATH = initialValue;  
    if(outputToDACOUTPin)
    {
        pInstance->DACxCONL |= 0x0200;   //Set DACOEN to enable output to the DACOUT pin
    }
    pInstance->DACxDATL = 0;            //Low data register (used in sloping output modes)
    
    //Enable the DAC module now.
    pInstance->DACxCONL |= 0x8000;      //Set DACEN bit to enable the module.
    DACCTRL1Lbits.DACON = 1;        //Set top level common enable bit for the all the DAC modules associated with the core  
}

//Updates the DACx to the specified output code between [0 to 4095].
void PDMDAC_SetValue(struct DAC_INSTANCE *pInstance, int16_t outputCode)
{
    //Boundary check the value to make sure it properly fits in a 12-bit number.
    if(outputCode > 4095u)
    {
        outputCode = 4095;
    }
    else if(outputCode < 0)
    {
        outputCode = 0;
    }
    
    //Load the DAC output value register
    pInstance->DACxDATH = outputCode;
}

uint16_t PDMDAC_GetValue(struct DAC_INSTANCE *pInstance)
{
   //Returns the DAC output value register
    return pInstance->DACxDATH;
}

//Enables the comparator and DAC module to operate in positive or negative sloping mode (as would typically be used in a peak current mode control SMPS control loop, where the DAC slope provides the ramp compensation).
//Note: If slopeVoltsPerMicrosecond is a negative number, the result will be a falling slope waveform.  If a positive number is specified, then a positive sloping waveform will be produced instead.
void PDMDAC_InitDACandCMPWithSlope(struct DAC_INSTANCE *pInstance, uint32_t moduleClockFreq, double DACReferenceVoltage, uint16_t startingDACLevel, double slopeVoltsPerMicrosecond, uint32_t PWMFrequency, bool invertComparatorOutput, uint8_t INSELFieldValue, uint8_t startSlopeTrigger, uint8_t stopSlopeTriggerB, uint8_t stopSlopeTriggerA)
{
    uint16_t maxSlopeDATValue;
    uint16_t targetSlopeDATValue;
    bool negativeSlopeRequested = false;
    double DACClocksPerMicrosecond;
    #define DAC_OUTPUT_CODES   4096        //12-bit DAC, so [0-4095] = 4096 DAC output codes
   
    //Load the DAC control registers with appropriate values
    //pInstance->DACxCONL = 0x2200 | ((uint16_t)INSELFieldValue << 3);          //DACOUT enabled,  INSEL value specified used as CMP positive input, negative input is the DAC, no blanking/digital filtering/hysteresis, not inverted

    // this assumes that PDMDAC_Init() was called previously
    pInstance->DACxCONL |= ((uint16_t)INSELFieldValue << 3);          //DACOUT disabled,  INSEL value specified used as CMP positive input, negative input is the DAC, no blanking/digital filtering/hysteresis, not inverted
    if(invertComparatorOutput)
    {
        pInstance->DACxCONL |= 0x0040;      //Set the CMPPOL bit to enable the comparator output to be inverted
    }
    if(slopeVoltsPerMicrosecond < 0.0)
    {
         //Configure for negative slope generation mode
        pInstance->SLPxCONH = 0x0000;         
        negativeSlopeRequested = true;
        slopeVoltsPerMicrosecond = -slopeVoltsPerMicrosecond;   //Get positive/complement value of the negative number (makes below math simpler)
        pInstance->DACxDATL = 0;                   //DAC low value
        pInstance->DACxDATH = startingDACLevel;    //Note: DAC value starts at this, then slopes upwards or downward as configured
    }
    else
    {
        //Configure for positive slope generation mode
        pInstance->SLPxCONH = 0x0200;                   //Configure for positive slope generation mode
        pInstance->DACxDATL = startingDACLevel;         //Starts at this level 
        pInstance->DACxDATH = DAC_OUTPUT_CODES - 1;     //Slopes up until it reaches this level (or the stop trigger signal is received)
    }
    
    //Compute the slope data register value.  The output moves by (SLP1DAT >> 4) number of LSB codes, per DAC clock cycle 
    //(which is 4ns, assuming 500MHz module clock frequency - as internal slope logic frequency is half the module input freq).
    //Note: Fractional LSB moves per clock cycle are allowed.  For example, SLPxDAT value of 0x0001 means that the output value moves by 1/16th of an LSB
    //every clock period.  A value of 0x0011 means that the DAC output moves 1.0625 LSBs every internal clock period.
    moduleClockFreq /= 2;   //Divide input clock frequency of the DAC by 2 to get the internal clock frequency of the DAC change intervals.
    if(negativeSlopeRequested == true)
    {
        //Negative slope
        maxSlopeDATValue = ((double)startingDACLevel / ((double)moduleClockFreq / (double)PWMFrequency)) * (double)16;
    }
    else
    {
        //Positive slope
        maxSlopeDATValue = ((double)((DAC_OUTPUT_CODES - 1) - startingDACLevel) / ((double)moduleClockFreq / (double)PWMFrequency)) * (double)16;
    }
    if(maxSlopeDATValue > 0)
    {
        maxSlopeDATValue--;
    }
    
    //Compute the SLPxDAT value for the specified slopeVoltsPerMicrosecond value.
    DACClocksPerMicrosecond = (double)moduleClockFreq / 1000000;    
    targetSlopeDATValue = (((double)slopeVoltsPerMicrosecond * (double)16) / ((DACClocksPerMicrosecond * DACReferenceVoltage) / (double)DAC_OUTPUT_CODES));
    //Limit the slope to no more than the maximum slew rate (so it doesn't reach the opposite rail and reset to the initial value before the end of the PWM period)
    //If DACDATH level is fixed, uncomment below lines; Disable if softstart is present
    //    if(targetSlopeDATValue > maxSlopeDATValue)
    //    {
    //        targetSlopeDATValue = maxSlopeDATValue;
    //    }
        
   
    //Configure the PDM DAC slope generation slew rate, and start/stop conditions.
    //Note: If the slew rate is too high, such that the output code tries to cross over the DAC1DATL low value before
    //the PWM trigger event resets the DAC output, the DAC will reset itself and go back to the DACxDATH level, potentially
    //before the comparator has tripped and terminated the current PWM on time.  To avoid this, make sure to select a slew rate and DAC1DATL
    //level that ensures that the active DAC output level never tries to cross over the DAC1DATL level during the PWM period.    
    pInstance->SLPxCONL = (uint16_t)(0x0F & startSlopeTrigger) | (((uint16_t)0x0F & stopSlopeTriggerB) << 4) | (((uint16_t)0x0F & stopSlopeTriggerA) << 8);
    pInstance->SLPxDAT = targetSlopeDATValue;           //Slope rate (Note: 12.4 formatted fractional number, larger numbers = faster slew rate).
    
    pInstance->DACxCONL |= 0x8000;      //Set DACEN to enable the DAC + comparator
    pInstance->SLPxCONH |= 0x8000;      //Set SLOPEN to enable the slope generation feature of the DAC
}
//*******************************
//EOF PDM_DAC.c