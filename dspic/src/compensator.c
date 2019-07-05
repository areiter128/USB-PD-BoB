
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
#include "compensator.h"
#include "adc1.h"
#include "pwm.h"
#include "pdm_dac.h"
#include "pin_manager.h"
#include "smps_control.h"
#include "softStart.h"
#include "initComp.h"

#ifndef PWM_INPUT_FREQ
#define PWM_INPUT_FREQ 500000000
#endif

#define BOOST_INITIAL_REF   (0.5 * BOOSTVOLTAGEREFERENCEADC)

#define BUCK_PWM_INSTANCE ((struct PWM_INSTANCE*)&PG1CONL)
#define BUCK_SWITCHING_FREQ 500000

#define BOOST_PWM_INSTANCE ((struct PWM_INSTANCE*)&PG2CONL)
#define BOOST_SWITCHING_FREQ 500000

#define BUCK_PWM_PERIOD  (uint16_t)(PWM_INPUT_FREQ/BUCK_SWITCHING_FREQ)
#define BOOST_PWM_PERIOD (uint16_t)(PWM_INPUT_FREQ/BOOST_SWITCHING_FREQ)

//PWM Gen I/O Control
#define BUCK_PWM_MODE 0       //0-Comp, 1-Independent, 2-Push/Pull
#define BUCK_PWM_H_EN 1       // 0-Dis, 1-EN
#define BUCK_PWM_L_EN 1       
#define BUCK_PWM_H_INV 0      // 0-Active High, 1-Active Low
#define BUCK_PWM_L_INV 0

#define BOOST_PWM_MODE 1       //0-Comp, 1-Independent, 2-Push/Pull
#define BOOST_PWM_H_EN 0       // 0-Dis, 1-EN
#define BOOST_PWM_L_EN 1       
#define BOOST_PWM_H_INV 0      // 0-Active High, 1-Active Low
#define BOOST_PWM_L_INV 0

#define BUCK_WRITE_IOCONTROL  ((BUCK_PWM_MODE<<4)  | (BUCK_PWM_H_EN << 3)  | (BUCK_PWM_L_EN << 2)  | (BUCK_PWM_H_INV << 1)  | (BUCK_PWM_L_INV))
#define BOOST_WRITE_IOCONTROL ((BOOST_PWM_MODE<<4) | (BOOST_PWM_H_EN << 3) | (BOOST_PWM_L_EN << 2) | (BOOST_PWM_H_INV << 1) | (BOOST_PWM_L_INV))

#define BUCK_ADC_SAMPLE_DELAY  BUCK_PWM_PERIOD*0.47     // Trigger 1 for DAC slope start
#define BUCK_BLANKING_DELAY     50

#define BOOST_ADC_SAMPLE_DELAY BOOST_PWM_PERIOD*0.45    // Trigger 1 for DAC slope start
#define BOOST_BLANKING_DELAY    50

#define BUCK_ACCEPTQUALIFIER     2     // LEB active
#define BUCK_PCISOURCE          27     // Comparator 1 
#define BUCK_PCIACCEPTCRITERIA   3     // Latched

#define BOOST_ACCEPTQUALIFIER    2     // LEB active
#define BOOST_PCISOURCE         28     // Comparator 2 
#define BOOST_PCIACCEPTCRITERIA  3     // Latched

#define DAC_BUCK_INSTANCE      ((struct DAC_INSTANCE*)&DAC1CONL)
#define DAC_BUCK_INIT_VALUE    0
#define DAC_BUCK_VOLTAGE_HI    (double)3.3
#define DAC_BUCK_VOLTAGE_LO    0
#define DAC_BUCK_SLOPE         (double)-0.55
#define DAC_BUCK_CMP_INVERT    false
#define DAC_BUCK_OUTEN         true
#define DAC_BUCK_INSEL         0     //comparator 1A
#define DAC_BUCK_SLP_CTRL_PWM  1    // PWM1 trigger 1
#define DAC_BUCK_SLP_STOPB     1     // CMP1 Out
#define DAC_BUCK_SLP_STOPA     1    // PWM1 Trigger 2

#define DAC_BOOST_INSTANCE     ((struct DAC_INSTANCE*)&DAC2CONL)
#define DAC_BOOST_INIT_VALUE   0
#define DAC_BOOST_VOLTAGE_HI   (double)3.3
#define DAC_BOOST_VOLTAGE_LO   0
#define DAC_BOOST_SLOPE        (double)-0.5
#define DAC_BOOST_CMP_INVERT   false
#define DAC_BOOST_OUTEN        false
#define DAC_BOOST_INSEL        3    // comparator 2D
#define DAC_BOOST_SLP_CTRL_PWM 2    // PWM2 Trigger 1 
#define DAC_BOOST_SLP_STOPB    2    // CMP2 Out
#define DAC_BOOST_SLP_STOPA    2    // PWM2 Trigger 2

// Phantom PWMs for triggering ADC every other cycle since TRIGA tied to DAC
#define PH_PWM ((struct PWM_INSTANCE*)&PG3CONL)
#define PH2_PWM ((struct PWM_INSTANCE*)&PG4CONL)

extern void smps_2p2z(void);
extern volatile bool buck_event, boost_event;

uint16_t buckControlReference  = 0, boostControlReference = 0; 
uint16_t buckVoltage = 0, boostVoltage = 0, inputVoltage = 0;

volatile bool restartConverterFlag = false;
SOFTSTART_STATE buckSoftStartController, boostSoftStartController;
static bool inputFaultFlag = false;
    
void BuckSoftStartInit(void)
{
    // Init SOFTSTART controller: call rate, soft-start duration
    SOFTSTART_ConfigTiming(&buckSoftStartController, BUCK_SOFT_START_CALLRATE, BUCK_SOFT_START_DURATION); 

    // Read output voltage and set as initial reference
    buckVoltage = ADC1_ManualConvertChannel(13);
    
    // Set soft-start starting point and where to write back control reference 
    SOFTSTART_Initialize(&buckSoftStartController, (int16_t *) &buckControlReference, buckVoltage);

    SOFTSTART_SetReference(&buckSoftStartController, BUCKVOLTAGEREFERENCEADC);      // Set steady state reference
    SOFTSTART_Enabled(&buckSoftStartController);                                    // Enable softstart controller
}

void BoostSoftStartInit(void)
{
    // Init SOFTSTART controller: call rate, soft-start duration
    SOFTSTART_ConfigTiming(&boostSoftStartController, BOOST_SOFT_START_CALLRATE, BOOST_SOFT_START_DURATION); 

    // Read output voltage and set as initial reference
    boostVoltage = ADC1_ManualConvertChannel(18);
    
    // Set soft-start starting point and where to write back control reference 
    SOFTSTART_Initialize(&boostSoftStartController, (int16_t *) &boostControlReference, boostVoltage);

    SOFTSTART_SetReference(&boostSoftStartController, BOOSTVOLTAGEREFERENCEADC);      // Set steady state reference
    SOFTSTART_Enabled(&boostSoftStartController);                                    // Enable softstart controller
}

void ConverterBuckInit(void)
{
    PDMDAC_Init(DAC_BUCK_INSTANCE, DAC_BUCK_INIT_VALUE, true, DAC_BUCK_OUTEN);
    PDMDAC_InitDACandCMPWithSlope(DAC_BUCK_INSTANCE, PWM_INPUT_FREQ, DAC_BUCK_VOLTAGE_HI, DAC_BUCK_VOLTAGE_LO, DAC_BUCK_SLOPE, BUCK_SWITCHING_FREQ, DAC_BUCK_CMP_INVERT, DAC_BUCK_INSEL, DAC_BUCK_SLP_CTRL_PWM, DAC_BUCK_SLP_STOPB, DAC_BUCK_SLP_STOPA);

    PWM_InitTimeBase(BUCK_PWM_INSTANCE, BUCK_PWM_PERIOD, (0.8 * 32767), 0x0, 25, 25); //100ns dead time
    PWM_InitLEBState(BUCK_PWM_INSTANCE, BUCK_BLANKING_DELAY, true, false, false, false);
       
    PWM_InitTrigger(BUCK_PWM_INSTANCE, BUCK_ADC_SAMPLE_DELAY, (BUCK_PWM_PERIOD*.82), 0); 
    PWM_InitADCTrig1(BUCK_PWM_INSTANCE, 0x0, true, false, false);
    PWM_InitADCTrig2(BUCK_PWM_INSTANCE, false, true, false);

    PG1EVTLbits.PGTRGSEL = 3;   // TRIGC 0ns is broadcasted output for PWM3 (Phantom) start
    
    PWM_InitPCILogicCL(BUCK_PWM_INSTANCE, true, BUCK_ACCEPTQUALIFIER, false, BUCK_PCISOURCE, BUCK_PCIACCEPTCRITERIA);
    PWM_InitOutputState(BUCK_PWM_INSTANCE, BUCK_WRITE_IOCONTROL, false, 0x0, 0x1);
    
    // Phantom PWM for triggering ADC every other cycle and triggering Boost Converter Start
    PWM_InitTimeBase(PH_PWM, BUCK_PWM_PERIOD, 0, 0, 0, 0); 
    PWM_InitADCTrig1(PH_PWM, 0x1, true, false, false);
    PWM_InitTrigger(PH_PWM, 100, (BUCK_PWM_PERIOD>>1), 0); 
    PG3CONHbits.SOCS = 1;       //PG1 TRIGC is start of cycle
    PG3EVTLbits.PGTRGSEL = 2;   //TRIGB 50% period broadcasted to Boost PWM
    PWM_InitOutputState(PH_PWM, 0, false, 0x0, 0x0);
}

void ConverterBoostInit(void)
{
    PDMDAC_Init(DAC_BOOST_INSTANCE, DAC_BOOST_INIT_VALUE, true, DAC_BOOST_OUTEN);
    PDMDAC_InitDACandCMPWithSlope(DAC_BOOST_INSTANCE, PWM_INPUT_FREQ, DAC_BOOST_VOLTAGE_HI, DAC_BOOST_VOLTAGE_LO, DAC_BOOST_SLOPE, BOOST_SWITCHING_FREQ, DAC_BOOST_CMP_INVERT, DAC_BOOST_INSEL, DAC_BOOST_SLP_CTRL_PWM, DAC_BOOST_SLP_STOPB, DAC_BOOST_SLP_STOPA);
    
    PWM_InitTimeBase(BOOST_PWM_INSTANCE, BOOST_PWM_PERIOD, (0.85 * 32767), 0x0, 0, 0);
    PWM_InitLEBState(BOOST_PWM_INSTANCE, BOOST_BLANKING_DELAY, true, false, false, false);
       
    PWM_InitTrigger(BOOST_PWM_INSTANCE, BOOST_ADC_SAMPLE_DELAY, (BOOST_PWM_PERIOD*.9), 0);
    PWM_InitADCTrig1(BOOST_PWM_INSTANCE, 0, true, false, false);
    PWM_InitADCTrig2(BOOST_PWM_INSTANCE, false, true, false);
    
    PG2CONHbits.SOCS = 3;       //PG3 TRIGB is start of cycle
    
    PWM_InitPCILogicCL(BOOST_PWM_INSTANCE, true, BOOST_ACCEPTQUALIFIER, false, BOOST_PCISOURCE, BOOST_PCIACCEPTCRITERIA);
    PWM_InitOutputState(BOOST_PWM_INSTANCE, BOOST_WRITE_IOCONTROL, false, 0x0, 0x0);
    
    // Phantom PWM for triggering ADC every other cycle 
    PWM_InitTimeBase(PH2_PWM, BOOST_PWM_PERIOD, 0, 0, 0, 0); 
    PWM_InitADCTrig1(PH2_PWM, 0x1, true, false, false);
    PWM_InitTrigger(PH2_PWM, 100, 0, 0); 
    PG4CONHbits.SOCS = 2;       //PG2 TRIGC is start of cycle
    PWM_InitOutputState(PH2_PWM, 0, false, 0x0, 0x0);
}


double GetVoltageBuck(void)
{
    return BUCKVOLTAGE_GET(buckVoltage);
}

double GetVoltageBoost(void)
{
    return BOOSTVOLTAGE_GET(boostVoltage);
}

double GetVoltageInput(void)
{
    return INPUTVOLTAGE_GET(inputVoltage);
}

uint16_t GetDacBuck(void)
{
    return PDMDAC_GetValue(DAC_BUCK_INSTANCE);
}

uint16_t GetDacBoost(void)
{
    return PDMDAC_GetValue(DAC_BOOST_INSTANCE);
}


void  ADC1_ADCAN13_CallBack(uint16_t adcVal)
{  
    buckVoltage = adcVal;

    if(buck_event == false)
    {
        #if defined (BUCK_CASCADED)
        __asm__("CTXTSWP #0x1");
        SMPS_ControllerCascadeUpdate_HW_Accel();
        __asm__("CTXTSWP #0x0");
        #else
        __asm__("CTXTSWP #0x1");
        __asm__("mov _buckControlReference, w0");
        smps_2p2z();
        __asm__("CTXTSWP #0x0");
        #endif
    }

    // When current is ~<250mA switch to asynchronous mode
    // Low side switch should be ON with load level 1
    if(DAC1DATH < 200)
        PG1IOCONLbits.CLDAT = 0b00;   
    else if (DAC1DATH > 250)
        PG1IOCONLbits.CLDAT = 0b01;
   
}

void  ADC1_ADCAN18_CallBack(uint16_t adcVal)
{   
    boostVoltage = adcVal;

    if(boost_event == false)
    {
        #if defined (BOOST_CASCADED)
        __asm__("CTXTSWP #0x2");        // Switch to Boost context 
        SMPS_ControllerCascadeUpdate_HW_Accel();
        __asm__("CTXTSWP #0x0");
        #else
        __asm__("CTXTSWP #0x2");
        __asm__("mov _boostControlReference, w0");
        smps_2p2z(); 
        __asm__("CTXTSWP #0x0");
        #endif
    }    

}

// SCCP1 is 10us timer for softstart control and for input voltage sampling 
void __attribute__ ( (interrupt, no_auto_psv ) ) _CCT1Interrupt ( void )
{
    static uint8_t counter = 0;
    static uint16_t acc_inputVoltage = 0;
    
    ADC1_SoftwareTriggerEnable(); // Software trigger for input voltage
    
    SOFTSTART_Initiate(&buckSoftStartController);
    SOFTSTART_Initiate(&boostSoftStartController);
    
    acc_inputVoltage += ADC1_SharedChannelAN12ConversionResultGet();
    if(++counter == 8)
    {
        counter = 0;
        inputVoltage = acc_inputVoltage>>3;
        acc_inputVoltage = 0;
        
        // Check for input voltage fault
        if((inputVoltage > VINMAXFAULT_ADC) || (inputVoltage < VINMINFAULT_ADC)) 
        {
           buck_event = true;
           boost_event = true;
           inputFaultFlag = true;  
           restartConverterFlag = 0;

           //To do: APIs
           PG1IOCONLbits.OVRENH = 1;
           PG1IOCONLbits.OVRENL = 1;
           PG2IOCONLbits.OVRENL = 1;
        }    
        else if ((inputVoltage < VINMAXFAULT_HYS_ADC) && (inputVoltage > VINMINFAULT_HYS_ADC) && (inputFaultFlag == true)) // input within limits
        {
            restartConverterFlag = 1;
            inputFaultFlag = false;
            
            COMPENSATOR_Initialize();
        }
    }
    
    IFS0bits.CCT1IF = 0;
}