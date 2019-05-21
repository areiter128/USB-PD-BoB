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
/*!tasks.h
 *****************************************************************************
 * File:   tasks.h
 *
 * Summary:
 * Globally defines the task table ID flags and operating modes task queues
 *
 * Description:	
 * -
 *
 * References:
 * -
 *
 * See also:
 * task_manager.c
 * task_manager.h
 * 
 * Revision history: 
 * 07/27/16     Initial version
 * Author: M91406
 * Comments:
 *****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APPLICATION_LAYER_TASK_FLOW_QUEUES_H_
#define	_APPLICATION_LAYER_TASK_FLOW_QUEUES_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <math.h>

/* ***********************************************************************************************
 * INCLUDE OF HEADERS ALSO CONTAINING GLOBALLY AVAILABLE FUNCTION CALLS
 * ***********************************************************************************************/
#include "apl/apl.h"

/* *****************************************************************************************************
 * Prototypes of external function used in task lists
 * *****************************************************************************************************
 * Functions which should be used in task flow lists can be prototyped here. The functions can
 * come from any source and are usually located in external C-files.
 * 
 * Limitations:
 *   - function has to be of the type int ... (void)
 *   - The function must return an integer value
 *   - The function cannot take specific parameters
 *   - Specific parameters have to be derived from global or private data structures
 *
 * *****************************************************************************************************/

/* Prototypes of additional initialization task functions */

/*!Task Table
 * *****************************************************************************************************
 * Task Table lists all tasks which will be called by the task manager
 * *****************************************************************************************************
 * This is the list which defines ALL available tasks as enumerated items of an array.
 * These enumerations will be combined freely in so called Task Flow Lists which will then be called
 * by the manager's function calls from the main loop
 * *****************************************************************************************************/

extern volatile uint16_t(*Task_Table[])(void);

/*!task_id_no_e
 * *****************************************************************************************************
 * The task_id_no_e enum is for easy addressing task-items from Task_Table using readable 
 * defines instead of indices. 
 * *****************************************************************************************************/
typedef enum {
    
    
    // Cross-function modules
    TASK_INIT_APPLICATION_SETTINGS, // Task initializing system-wide application data structure
    TASK_INIT_FAULT_OBJECTS,        // Task initializing default and user defined fault objects
    TASK_CAPTURE_SYSTEM_STATUS,     // Captures detection signals and analyzes voltages to determine the operating mode

    /* ===== USER FUNCTIONS LIST ===== */
            
    // Chip level initialization
    TASK_INIT_GPIO, // Task initializing the chip GPIOs
    TASK_INIT_IRQ, // Task initializing the interrupt controller
    TASK_INIT_DSP, // Task initializing the digital signal controller
        
    // Board level initialization
    TASK_INIT_DebugLED,          // initialize DebugLED task
    TASK_DGBLED,               // run DebugLED task

    // Add System function / Special function initialization

            
    /* ===== END OF USER FUNCTIONS ===== */

    // Empty task used as internal task execution timing buffer
    TASK_IDLE  // Default task not performing any action but occupying a task time frame

} task_id_no_e;

/*!Task Queues
 *  *****************************************************************************************************
 * Task Queues 
 * *****************************************************************************************************
 * These queues are used to establish any order of the registered tasks to be executed.
 * As the task manager is running on a fixed tick rate, more critical tasks might be called
 * multiple times while less critical ones might only be called once.
 * *****************************************************************************************************/

extern volatile uint16_t task_queue_boot[];
extern volatile uint16_t task_queue_boot_size;

extern volatile uint16_t task_queue_device_startup[];
extern volatile uint16_t task_queue_device_startup_size;

extern volatile uint16_t task_queue_system_startup[];
extern volatile uint16_t task_queue_system_startup_size;

extern volatile uint16_t task_queue_idle[];
extern volatile uint16_t task_queue_idle_size;
extern volatile uint16_t task_queue_init_idle(void);

extern volatile uint16_t task_queue_normal[];
extern volatile uint16_t task_queue_normal_size;
extern volatile uint16_t task_queue_init_normal(void);

extern volatile uint16_t task_queue_fault[];
extern volatile uint16_t task_queue_fault_size;
extern volatile uint16_t task_queue_init_fault(void);

extern volatile uint16_t task_queue_standby[];
extern volatile uint16_t task_queue_standby_size;
extern volatile uint16_t task_queue_init_standby(void);

#endif	/* _APPLICATION_LAYER_TASK_FLOW_QUEUES_H_ */

