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
 */

/* 
 * File:   task_PowerControl.h  
 * Author: M91406   
 * Comments: 
 * Power control state machine for operating a 4-Switch Buck/Boost converter in 
 * average current mode control (ACMC)
 * Revision history: 
 * 07/24/2019   initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_TASK_POWER_CONTROL_H
#define	APL_TASK_POWER_CONTROL_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "hal/hal.h"
#include "mcal/mcal.h"

#include "apl/resources/c4swbb_control.h"


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

extern volatile C4SWBB_POWER_CONTROLLER_t c4swbb_1;
extern volatile C4SWBB_POWER_CONTROLLER_t c4swbb_2;

// Public function prototypes
extern volatile uint16_t init_PowerControl(void);
extern volatile uint16_t exec_PowerControl(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* APL_TASK_POWER_CONTROL_H */

