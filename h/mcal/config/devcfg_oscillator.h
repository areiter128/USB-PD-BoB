/* ****************************************************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 * *****************************************************************************************************
 * File:   devcfg_oscillator.h
 * Author: M91406
 * Comments: This file is offering default defines of basic system oscillator frequencies based on user selected CPU speed settings.
 * Revision history: 
 *  10/27/2017  iniial release
 * *****************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DEVICE_CONFIGURATION_OSCILLATOR_H_
#define	_DEVICE_CONFIGURATION_OSCILLATOR_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#include "mcal/mcal.h"

/*!System Oscillator Settings
 * ************************************************************************************************
 * Summary:
 * Predefined settings for standard oscillator configurations
 *
 * Description:
 * These defines are used to setup the oscillator using predefined settings to achieve common
 * system clock speeds/frequencies. By selecting one of the given MIPS_xx options, all required register
 * values for scalers and gating options will be selected and adjusted accordingly.
 * ***********************************************************************************************/

/* user settings */
#define USE_EXTERNAL_OSC	0			// Usage of external oscillator (0= Internal FRC, 1= external Oscillator)
                                        // If FRS is selected, FRC will be tuned to 7.5 MHz
            

#define CPU_PERFORMANCE 	C_90MIPS	// Device speed selection (MIPS40, MIPS50, MIPS60, MIPS70)

/*!System Frequency Presets
 * ************************************************************************************************
 * Summary:
 * Set of defines for default oscillator settings
 *
 * Description:
 * For quick setup this library offers fixed parameter sets for standard configurations
 * ***********************************************************************************************/

#define C_MIPS_NONE 0   // Oscillator settings are set in user code (no preset is used)
#define C_100MIPS   1   // Oscillator settings are set for 200 MHz core clock (= 100 MIPS operation)
#define C_90MIPS    2   // Oscillator settings are set for 180 MHz core clock (=  90 MIPS operation)
#define C_80MIPS    3   // Oscillator settings are set for 160 MHz core clock (=  80 MIPS operation)
#define C_70MIPS    4   // Oscillator settings are set for 140 MHz core clock (=  70 MIPS operation)
#define C_60MIPS    5   // Oscillator settings are set for 120 MHz core clock (=  60 MIPS operation)
#define C_50MIPS    6   // Oscillator settings are set for 100 MHz core clock (=  50 MIPS operation)
#define C_40MIPS    7   // Oscillator settings are set for  80 MHz core clock (=  40 MIPS operation)
#define C_30MIPS    8   // Oscillator settings are set for  60 MHz core clock (=  30 MIPS operation)
#define C_20MIPS    9   // Oscillator settings are set for  40 MHz core clock (=  20 MIPS operation)

#if (CPU_PERFORMANCE == C_100MIPS)
// PLL is set for 100 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      100
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_90MIPS)
// PLL is set for 90 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      90
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_80MIPS)
// PLL is set for 80 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      80
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_70MIPS)
// PLL is set for 70 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      70
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_60MIPS)
// PLL is set for 80 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      60
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_50MIPS)
// PLL is set for 50 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      50
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_40MIPS)
// PLL is set for 40 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      40
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_30MIPS)
// PLL is set for 30 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      60
  #define OSC_PLLDIV_N2     4
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_20MIPS)
// PLL is set for 20 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      40
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#elif  (CPU_PERFORMANCE == C_MIPS_NONE)
// PLL is set for 20 MIPS operation at 8 MHz input frequency
  #define OSC_PLLDIV_N1     1
  #define OSC_PLLDIV_M      40
  #define OSC_PLLDIV_N2     2
  #define OSC_PLLDIV_N3     1

#else
// PLL preset is not available
  #error === no PLL preset available for this frequency === 
#endif


/*!System Oscillator Settings
 * ************************************************************************************************
 * Summary:
 * Predefined settings for standard oscillator configurations
 *
 * Description:
 * These defines are used to setup the oscillator using predefined settings to achieve common
 * system clock speeds/frequencies. By selecting one of the given MIPS_xx options, all required register
 * values for scalers and gating options will be selected and adjusted accordingly.
 * ***********************************************************************************************/

#define OSC_FREQ ((uint32_t)((float)OSC_FRC_FREQ + (float)((float)OSC_FRC_TUN * (OSC_TUN_SCALER * (float)OSC_FRC_FREQ))))

// this oscillator frequency will be used in further macros
#define OSC_FREQUENCY		OSC_FREQ    

// FRC Output Frequency in Hertz (incl. OSCTUN)
#define AUXOSCFREQUENCY	((uint32_t)(OSC_FRC_FREQ + (OSC_FRC_TUN * (OSC_TUN_SCALER * OSC_FRC_FREQ))))

// PLL Output Frequency in Hertz (~100 MHz max.)
#define FOSC	(uint32_t)((((float)OSC_FREQUENCY * (float)OSC_PLLDIV_M) / ((float)OSC_PLLDIV_N1 * (float)OSC_PLLDIV_N2 * (float)OSC_PLLDIV_N3)) / 2.0)

// Operating Frequency in Hertz (~100 MHz max.)
#define FCY		((uint32_t)(FOSC / 2))

// Instruction Cycle in Seconds (~10 ns max.)
#define TCY		((float)(1.0/(float)(FCY)))

#endif	/* _DEVICE_CONFIGURATION_OSCILLATOR_H_ */

