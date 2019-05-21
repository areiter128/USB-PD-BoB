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
/*!task_DebugLED.h
 * ***************************************************************************
 * File:   task_DebugLED.h
 * Author: John Haroian - C14029
 * 
 * Summary:
 * Task to blink Master Core Heartbeat LED (DebugLED)
 * 
 * Description:
 * This source file is used to register a global data structure allowing to edit
 * parameters of the task. It is also used to publish global function calls.
 * 
 * The main task routine is operating the Master Core Heartbeat LED (DGBLED1) 
 * by applying the status setting in the data structure.
 * 
 * History:
 * 02/21/2019	File created
 * ***************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_TASK_DBGLED_H
#define	APL_TASK_DBGLED_H

#include <xc.h>   
#include <stdint.h>
#include <stdbool.h>
#include "_root/config/globals.h"
#include "apl/resources/fdrv_FunctionLED.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/

// Mapping  target LED to hardware
#define DEBUG_LED_WR            DBGLED_WR
#define DEBUG_LED_RD            DBGLED_RD
#define DEBUG_LED_TOGGLE        DBGLED_TOGGLE
#define DEBUG_LED_INIT_OUTPUT   DBGLED_INIT_OUTPUT

extern volatile FUNCTION_LED_CONFIG_t taskDebugLED_config;

/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
extern volatile uint16_t init_taskDebugLED(void);
extern volatile uint16_t task_DebugLED(void);


#endif	/* APL_TASK_DBGLED_H */

