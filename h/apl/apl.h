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
/*!apl.h
 * ****************************************************************************
 * File:   apl.h
 * Author: M91406
 * Comments:
 * Revision history: 
 * ****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APPLICATION_LAYER_H
#define	APPLICATION_LAYER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "config/application.h"

//Remove: #include "task_ConverterStateControl.h"
#include "../h/apl/tasks/task_Idle.h"
#include "../h/apl/tasks/task_FaultHandler.h"
#include "../h/apl/tasks/task_SystemStatus.h"
#include "../h/apl/tasks/task_PDStack.h"

/* ***********************************************************************************************
 * GLOBAL APPLICATION LAYER USER OPTIONS
 * ***********************************************************************************************/


/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/

#if (EXECUTE_MCC_SYSTEM_INITIALIZE == 0)
extern volatile uint16_t DEVICE_Reset(void);         // Declare prototype if MCC option is disabled
#endif
#if (EXECUTE_MCC_SYSTEM_INITIALIZE == 0)
extern uint16_t CLOCK_Initialize(void);     // Declare prototype if MCC option is disabled
#endif
#if (EXECUTE_USER_STARTUP_CODE == 1)
    extern volatile uint16_t ExecuteUserStartupCode(void);  // Declare prototype if Startup Code option is enabled
#endif
extern volatile uint16_t APPLICATION_Initialize(void);

#endif	/* APPLICATION_LAYER_H */

