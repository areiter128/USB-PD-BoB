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
#ifndef MCAL_DEVICE_CONFIGURATION_OSCILLATOR_H
#define	MCAL_DEVICE_CONFIGURATION_OSCILLATOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>


#if defined (__P33SMPS_CK__) || defined (__P33SMPS_CH_SLV__)

    #define MAIN_CLOCK_SPEED    CPU_SPEED_100_MIPS
    #define AUX_CLOCK_SPEED     AFPLLO_500_MHZ

#elif defined (__P33SMPS_CH_MSTR__)

    #define MAIN_CLOCK_SPEED    CPU_SPEED_90_MIPS
    #define AUX_CLOCK_SPEED     AFPLLO_500_MHZ

#else
    #pragma message "=== selected device is not defined and may not be supported ==="
#endif

#endif	/* MCAL_DEVICE_CONFIGURATION_OSCILLATOR_H */

