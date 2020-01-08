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

/*!User Task Rules
 * *****************************************************************************************************
 * Prototypes of external functions used in task queues
 * *****************************************************************************************************
 * Functions which should be used in task queues can be prototyped here. The functions can
 * come from any source and are usually located in external C-files.
 * 
 * Limitations:
 *   - function has to be of the type volatile uint16_t ... (void)
 *   - The function must return a volatile unsigned integer value of 16 bit data length
 *   - The function cannot take specific parameters
 *   - Specific parameters have to be derived from or exchanged through semaphores (e.g. global data structures)
 *
 * Architecture:
 * User tasks are encapsulated state machines. The highest level of the state machine needs to provide
 * standard functions for initialization and execution. The recommended naming conventions use the 
 * pre-label "init_" and "exec_" to distinguish between the these two functions.
 * 
 * Example:
 * There is a task called MyTask which describes some clear defined feature (e.g. communication, 
 * power converter control, system management, etc.). This task may consist of many files, internal
 * function drivers and libraries. However simple or complex this task may be, it should always provide 
 * the two basic function calls which can be used by the task manager to integrate this feature.
 * 
 *   - volatile uint16_t init_MyTask(void)
 * 
 *     This function is used to initialize required peripherals, variables and data structures and 
 *     basically everything that needs to be done before the state machine can be executed.
 *     This function will only be called once. A return value indicating an unsuccessful initialization
 *     should be declared as critical fault to prevent the firmware to run with malfunctioning tasks.
 * 
 *   - volatile uint16_t exec_MyTask(void)
 * 
 *     This function will be called periodically by the task scheduler. The call frequency will depend
 *     on the heartbeat frequency of the scheduler and number of tasks in the active task queue. Default
 *     values for the scheduler heartbeat is 100 usec. With three tasks in one task queue exec_MyTask
 *     will be called every 300 usec.
 *
 *     The state machine executed by exec_MYTask has to be 100% self organized and should not depend on
 *     other functions outside of MyTask. Data and status information from other tasks which may be 
 *     required should be exchanged through proper semaphores (global data structures and variables.
 *
 *     Silicon specific settings or registers contents should use the generic labels declared in 
 *     the Microcontroller Abstraction Layer (MCAL). 
 *  
 *   - volatile uint16_t dispose_MyTask(void)       (optional)
 * 
 *     Some features may require to load and unload tasks on-the-fly at runtime. In this particular
 *     case it is also recommended to create a third function call named dispose_MyTask in which
 *     all used resources are given back (e.g. Special Function Registers (SFR) need to be reset, 
 *     data structures need to be reset to default, port pins need to be reset to the default state 
 *     (high impedance input) and power to peripheral modules no longer in use should be turned off
 *     by setting the appropriate PMD register bit (if available)
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
    TASK_INIT_APPLICATION, // Task initializing system-wide application data structure

    /* ===== USER FUNCTIONS LIST ===== */
    TASK_PWR_CONTROL_INIT,
    TASK_PWR_CONTROL_RESET,
    TASK_PWR_CONTROL_EXECUTE,
        
    TASK_INIT_PDSTACK,          // initialize PD Stack task
    TASK_PDSTACK,               // run PD Stack task

    TASK_DEBUG_UART_INIT,
    TASK_DEBUG_UART_EXECUTE,

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

extern volatile uint16_t task_queue_firmware_init[];
extern volatile uint16_t task_queue_firmware_init_size;

extern volatile uint16_t task_queue_startup_sequence[];
extern volatile uint16_t task_queue_startup_sequence_size;

extern volatile uint16_t task_queue_idle[];
extern volatile uint16_t task_queue_idle_size;
extern volatile uint16_t task_queue_idle_init(void);

extern volatile uint16_t task_queue_run[];
extern volatile uint16_t task_queue_run_size;
extern volatile uint16_t task_queue_run_init(void);

extern volatile uint16_t task_queue_fault[];
extern volatile uint16_t task_queue_fault_size;
extern volatile uint16_t task_queue_fault_init(void);

extern volatile uint16_t task_queue_standby[];
extern volatile uint16_t task_queue_standby_size;
extern volatile uint16_t task_queue_standby_init(void);

#endif	/* _APPLICATION_LAYER_TASK_FLOW_QUEUES_H_ */

