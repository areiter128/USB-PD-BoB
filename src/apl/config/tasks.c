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
/*!tasks.c
 *****************************************************************************
 * File:   tasks.c
 *
 * Summary:
 * Defines lists of tasks which will be called by the scheduler
 *
 * Description:	
 * 
 * In this header file prototypes of external functions are added and combined
 * in arrays. These arrays (task lists) will be used by the task manager executing 
 * all tasks in a list in their order of appearance.
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


#include <xc.h> // include processor files - each processor file is guarded.  

/* ***********************************************************************************************
 * INCLUDE OF HEADERS ALSO CONTAINING GLOBALLY AVAILABLE FUNCTION CALLS
 * ***********************************************************************************************/
  
#include "apl/config/tasks.h"

/*!Task Table
 *  *****************************************************************************************************
 * Task Table lists all tasks which will be called by the task manager
 * *****************************************************************************************************
 * This is the list which defines ALL available tasks as enumerated items of an array.
 * These enumerations will be combined freely in so called Task Flow Lists which will then be called
 * by the manager's function calls from the main loop
 * *****************************************************************************************************/

volatile uint16_t (*Task_Table[])(void) = {
    
    // Cross-function modules
    init_ApplicationSettings, // initialize system-wide application data structure
    init_FaultObjects, // call fault object initialization
    exec_CaptureSystemStatus,           // Captures detection signals and analyzes voltages to determine the operating mode
    
    /* ===== USER FUNCTIONS LIST ===== */
    
    // Chip level initialization
    init_gpio,              // task initializing all used GPIOs in accordance to their application specific function
    init_irq,               // task initializing the interrupt controller
    initialize_dsp,         // task initializing all digital signal controller

    // Board level initialization
    init_taskDebugLED,                   // initialize DebugLED task 
    task_DebugLED,                       // run DebugLED task
            
    // Add System function / Special function initialization

    
    /* ===== END OF USER FUNCTIONS ===== */

    // Empty task used as internal task execution timing buffer
    task_Idle,              // simple task doing nothing 
    
};


/*!Task Queues
 *  *****************************************************************************************************
 * Task Queues 
 * *****************************************************************************************************
 * These queues are used to establish any order of the registered tasks to be executed.
 * As the task manager is running on a fixed tick rate, more critical tasks might be called
 * multiple times while less critical ones might only be called once.
 * *****************************************************************************************************/

/*!task_queue_boot
 * ***********************************************************************************************
 *   In OP_MODE_BOOT this is the first task queue which is loaded right after the task manager 
 *   has been started. 
 *   In this task queue is covering all basic configurations of data objects and user tasks.
 *   It is recommended to add all initializations of default values in data structures, which 
 *   will/might be later used/needed by peripheral drivers to be set up correctly.
 * 
 *   PLEASE NOTE:
 *   The boot task queue is only executed once calling all listed tasks in one sequence.
 *   At the end of this task queue the task manager will automatically switch over to 
 *   task queue device startup.
 * *********************************************************************************************** */

volatile uint16_t task_queue_boot[] = {
    TASK_INIT_GPIO,         // Step #0
    TASK_INIT_APPLICATION_SETTINGS, // Step #1
    TASK_INIT_FAULT_OBJECTS, // Step #2
//    TASK_INIT_DBGLED,      // Step #4
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_boot_size = (sizeof(task_queue_boot)/sizeof(task_queue_boot[0]));

/*!task_queue_device_startup
 * ***********************************************************************************************
 *   In OP_MODE_DEVICE_STARTUP this task queue covers all peripheral configurations. 
 *   During the execution of this task sequence the peripheral initialization may set up modules 
 *   in a disabled state. It is recommended to add a user defined task taking care of the 
 *   peripheral startup sequence to have maximum control over the functional device startup process.
 * 
 *   To support this approach, all initialization functions of peripheral driver library modules 
 *   are configuring peripherals masking out the ENABLE bit to keep them in a disabled state by 
 *   default. Each driver module offers an additional ENABLE function call for the purpose of
 *   enabling a pre-configured peripheral whenever needed. 
 * 
 *   PLEASE NOTE:
 *   The device startup task queue is only executed once calling all listed tasks in one sequence.
 *   At the end of this task queue the task manager will automatically switch over to 
 *   task queue system startup.
 * *********************************************************************************************** */

volatile uint16_t task_queue_device_startup[] = {
    TASK_DGBLED,                   // Step #1
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_device_startup_size = (sizeof(task_queue_device_startup)/sizeof(task_queue_device_startup[0]));

/*!task_queue_system_startup
 * ***********************************************************************************************
 *   In OP_MODE_SYSTEM_STARTUP task queue system startup is executed.
 *   Once variable/data structure default values have been loaded and peripherals have been 
 *   configured, the system can be started. 
 *   This task queue is used to start up system level peripheral circuits bringing the final 
 *   product up to life. Whatever operating mode is initially needed, needs to be set in user 
 *   code. If no initial op-mode is selected, the task manager will automatically switch to 
 *   task queue idle, expecting that the system status capturing determines and select the 
 *   appropriate operating mode.
 * 
 *   PLEASE NOTE:
 *   The system startup task queue is only executed once calling all listed tasks in one sequence.
 *   At the end of this task queue the task manager will automatically switch over to 
 *   task queue idle. if this is not desired, another operating mode needs to be actively set
 *   in user code.
 * *********************************************************************************************** */

volatile uint16_t task_queue_system_startup[] = {
    TASK_DGBLED, // Step #1
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_system_startup_size = (sizeof(task_queue_system_startup)/sizeof(task_queue_system_startup[0]));

/*!task_queue_idle
 * ***********************************************************************************************
 *   In OP_MODE_IDLE task queue idle is executed until a new operating mode is selected and a 
 *   new/different task queue is loaded.
 *   This is the generic idle task which is called after the startup-procedure has been completed.
 *   The system status detection, fault handler and/or remote control through communication will
 *   determine the operating mode from this point forward.
 *   In systems with multiple, equally prioritized task queues, switching from one state into 
 *   another often requires a fall-back task queue to start from. This IDLE mode covers this 
 *   requirement as well as serves as safety layer when no valid operating mode is set.
 * *********************************************************************************************** */

volatile uint16_t task_queue_idle[] = {
    TASK_DGBLED, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_idle_size = (sizeof(task_queue_idle)/sizeof(task_queue_idle[0]));
volatile uint16_t task_queue_init_idle(void)
{
    Nop();
    return(1);
}

/*!Operating Mode Templates
 * ***********************************************************************************************
 *
 * - OP_MODE_NORMAL:
 *   In NORMAL MODE the system is performing its normal function. Depending on system complexity, 
 *   this may break down into multiple other operating modes / task queues which may be defined 
 *   by the user
 * 
 * - OP_MODE_FAULT:
 *   In FAULT MODE power supplies usually have to be brought into a safe, defined state where the 
 *   power converter is usually shut down and the system starts to monitor operating conditions and
 *   fault conditions, waiting for a chance to restart the system.
 * 
 * - OP_MODE_STANDBY:
 *   In standby the system is usually disabling all power converters and entering into low-power 
 *   mode. The MCU may be in sleep mode.
 * 
 * *********************************************************************************************** */
/* ORIGINAL DEFINITION OF OP_MODE_NORMAL
 * 
volatile uint16_t task_queue_normal[] = {
    TASK_1,                     // Step #0
    TASK_2                      // Step #1
    TASK_3                      // Step #2
    (...),                      // Step #3
    TASK_IDLE                   // Step #n => empty buffer task execution window to account for 
                                // overrunning task execution time
};
volatile uint16_t task_queue_normal_size = (sizeof(task_queue_normal)/sizeof(task_queue_normal[0]));
*/

/*!task_queue_normal
 * ***********************************************************************************************
 *   In OP_MODE_NORMAL task queue normal is executed until a new operating mode is selected and a 
 *   new/different task queue is loaded.
 * 
 *   In NORMAL MODE the system is performing its normal function. All tasks which need to be
 *   executed in this mode need to added to this task queue.
 * *********************************************************************************************** */

volatile uint16_t task_queue_normal[] = {
    TASK_DGBLED, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_normal_size = (sizeof(task_queue_normal)/sizeof(task_queue_normal[0]));
volatile uint16_t task_queue_init_normal(void)
{
    Nop();
    
    return(1);
}

/*!task_queue_fault
 * ***********************************************************************************************
 *   In OP_MODE_FAULT task queue fault is executed until a new operating mode is selected and a 
 *   new/different task queue is loaded.
 *   In FAULT MODE power supplies usually have to be brought into a safe, defined state where the 
 *   power converter is usually shut down and the system starts to monitor operating conditions 
 *   and fault conditions, waiting for a chance to restart the system.
 *   The fault condition monitoring and system status capturing is continuously performed by the
 *   task manager and does not to be covered. Only additional tasks which need to be executed
 *   under fault conditions need to be added to this task queue.
 * *********************************************************************************************** */

volatile uint16_t task_queue_fault[] = {
    TASK_DGBLED, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_fault_size = (sizeof(task_queue_fault)/sizeof(task_queue_fault[0]));
volatile uint16_t task_queue_init_fault(void)
{
    Nop();
    return(1);
}

/*!task_queue_standby
 * ***********************************************************************************************
 *   In OP_MODE_STANDBY task queue fault is executed until a new operating mode is selected and a 
 *   new/different task queue is loaded.
 *   In standby the system is usually disabling all power converters entering a low-power mode. 
 *   The MCU may be in sleep mode. Not every application may need this mode. If the functional 
 *   profile does not require a standby mode, this task queue can be ignored..
 * *********************************************************************************************** */

volatile uint16_t task_queue_standby[] = {
    TASK_DGBLED, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_standby_size = (sizeof(task_queue_standby)/sizeof(task_queue_standby[0]));
volatile uint16_t task_queue_init_standby(void)
{
    Nop();
    return(1);
}

// EOF