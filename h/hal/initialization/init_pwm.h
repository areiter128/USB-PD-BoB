/*LICENSE ********************************************************************
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
 * ***************************************************************************/
/*!init_dsp.h
 * *************************************************************************** 
 * File:   init_adc.h
 * Author: m91406
 *
 * Created on March 8, 2019
 * ***************************************************************************/

#ifndef _HAL_INIT_PWM_H_
#define	_HAL_INIT_PWM_H_

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "hal/hal.h"
#include "mcal/mcal.h"

/* ******************************************************************
   Defines for PWM initialization 
 
   All the parameters values are measured in [ticks]
   Input frequency of the PWM module is 500 MHz, i.e. 1 tick = 2 ns
   High resolution mode is NOT enabled
 ********************************************************************/
#define TRIGA_LEVEL                 555     // 555 Trigger A Compare level used to provide pace for soft-start and create offset between the two buck-boost channels

#define SST_PERIOD                  6       // Update PWM cycle period during soft-start in terms of PWM1 interrupts (in this case "ADC Trigger 1" -> 2 PWM1 cycles = 5.5us) 

#define TRIGA1_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM1 & PWM2
#define TRIGA5_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM5 & PWM7

#define PWM_PHASE_1     500
#define PWM_PHASE_2     500
#define PWM_PHASE_5     500
#define PWM_PHASE_7     500



/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/

#endif	/* _HAL_INIT_PWM_H_ */

