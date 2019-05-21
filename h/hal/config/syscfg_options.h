/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
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
 * **************************************************************************************
 * File:   syscfg_options.h
 * Author: M91406
 * Comments: 
 * Revision history: 
 * 08/19/2016   initial release
 * **************************************************************************************/

#ifndef _APPLICATION_LAYER_SYSTEM_OPTIONS_H_
#define	_APPLICATION_LAYER_SYSTEM_OPTIONS_H_

#define DBG_MODE_GPIO       1       // the debug pin is used as GPIO
#define DBG_MODE_DAC        2       // the debug pin is used as digital-to-analog output
#define DBG_MODE_PWM        3       // the debug pin is used as pulse-width-modulated output


#define USE_I2C             0       // This option enables/disables I2C communication
#define USE_UART            0       // This option enables/disables UART communication

#define USE_DEBUG_PIN		1       // This option enables/disables the Debug Pin
#define DEBUG_PIN_MODE      DBG_MODE_GPIO   // This option selects the Debug Mode GPIO, DAC or PWM

#define USE_SPREAD_SPECTRUM_MODULATION 0       // This option will enable/disable spread spectrum modulation


#define CURRENT_SENSE_TRANSFORMER  1 // Current sensor is a current sense transformer
#define CURRENT_SENSE_AMPLIFIER    2 // Current sensor is a shunt amplifier

#define CS_TYPE             CURRENT_SENSE_AMPLIFIER  // Set current sense type used
#if (CS_TYPE == CURRENT_SENSE_TRANSFORMER)
  #define __CS_TYPE_CT__
#elif (CS_TYPE == CURRENT_SENSE_AMPLIFIER)    
  #define __CS_TYPE_SHUNT_AMP__
#else
  #warning === Current Sense Device Type not specified ===
#endif
    
    
    
#define TRG_OPTION_ADC      0       // Control loops are executed in ADC interrupt service routine
#define TRG_OPTION_PWM      1       // Control loops are executed in PWM interrupt service routines

#define TRIGGER_OPTION      TRG_OPTION_ADC     // Set ISR type used to execute control loops

/* ***************************************************************************************
 *	DEBUGGING ONLY
 * **************************************************************************************/
 
#ifdef __DEBUG

	#define DEBUG_ARRAY_SIZE	1023

#endif

#endif	/* SYSTEM_OPTIONS_H */

