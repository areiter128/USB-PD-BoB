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
#ifndef _DEVICE_CONFIGURATION_DSP_H_
#define	_DEVICE_CONFIGURATION_DSP_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "mcal/mcal.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/* CORCON Settings 

    CORCONbits.ACCSAT = CORCON_ACCSAT_931;  // Accumulator Saturation Mode Selection: 9.31 saturation (super saturation)
    CORCONbits.IF = CORCON_IF_FRACTIONAL;   // Integer or Fractional Multiplier Mode Selection: Fractional mode is enabled for DSP multiply
    CORCONbits.RND = CORCON_RND_UNBIASED;   // Rounding Mode Selection: Unbiased (convergent) rounding is enabled
    CORCONbits.SATA = CORCON_SATA_ON;       // ACCA Saturation Enable: Accumulator A saturation is enabled
    CORCONbits.SATB = CORCON_SATB_ON;       // ACCB Saturation Enable: Accumulator B saturation is enabled
    CORCONbits.SATDW = CORCON_SATDW_ON;     // Data Space Write from DSP Engine Saturation Enable: Data Space write saturation is enabled
    CORCONbits.US = CORCON_US_SIGNED;       // DSP Multiply Unsigned/Signed Control: DSP engine multiplies are signed
    CORCONbits.VAR = CORCON_VAR_FIXED;      // Variable Exception Processing Latency Control: Fixed exception processing is enabled
*/
    
#define DSP_CORECON_CFG    (REG_CORCON_ACCSAT_931 | \
                            REG_CORCON_IF_FRACTIONAL | \
                            REG_CORCON_RND_UNBIASED | \
                            REG_CORCON_SATA_ON | \
                            REG_CORCON_SATB_ON | \
                            REG_CORCON_SATDW_ON | \
                            REG_CORCON_US_SIGNED | \
                            REG_CORCON_VAR_FIXED \
                            )

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _DEVICE_CONFIGURATION_DSP_H_ */

