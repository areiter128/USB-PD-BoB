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
/*!task_PDStack.h
 * ***************************************************************************
 * File:   task_PDStack.h
 * Author: James Schaffer - C41076
 * 
 * Summary:
 * Zeus USB PD Stack Task
 * 
 * Description:
 * 
 * This file contains functions that implement the task that initializes
 * and runs the Zeus USB PD Stack.
 * 
 * History:
 * 05/23/2019	File created
 * ***************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_TASK_PDSTACK_H
#define	APL_TASK_PDSTACK_H

#include <xc.h>   
#include <stdint.h>
#include <stdbool.h>
#include "ZeusStackConfig.h"
#include "upd_interrupts.h"
#include "_root/config/globals.h"
#include "apl/resources/fdrv_FunctionPDStack.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/

extern volatile FUNCTION_PD_STACK_CONFIG_t taskPDStack_config;

/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
extern volatile uint16_t init_taskPDStack(void);
extern volatile uint16_t task_PDStack(void);


#endif	/* APL_TASK_PDSTACK_H */

