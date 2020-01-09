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
/*!UserTasks.c
 *****************************************************************************
 * File:   UserTasks.c
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
 * os_TaskManager.c
 * os_TaskManager.h
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
  
#include "apl/config/UserTasks.h"

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
    APPLICATION_Initialize, // initialize system-wide application data structure
    
    /* ==================== USER FUNCTIONS LIST ==================== */
    
    init_PowerControl,      // Initializes the power controller of both 4-SWBB converters
    reset_PowerControl,     // Shuts down both 4-SWBB converters
    exec_PowerControl,      // Executes the power controller state machine

    init_taskPDStack,
    task_PDStack,
    
    task_DebugUART_Initialize,
    task_DebugUART_Execute,
    
    /* ==================== END OF USER FUNCTIONS ==================== */

    // Empty task used as internal task execution timing buffer
    task_Idle               // simple task doing nothing 
    
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
 *   The OP_MODE_BOOT marks the period where the CPU is coming out of reset. Before this task queue
 *   is loaded, the following sequence of configurations will be executed by the task scheduler. 
 *   The execution of some of the listed, optional functions can be configured by using the given 
 *   flags in task_manager_config.h
 * 
 *     - CheckCPUResetRootCause()
 *     - DEVICE_Reset()             (optional, set/clear flag EXECUTE_DEVICE_RESET)
 *     - ExecuteUserStartupCode()   (optional, set/clear flag EXECUTE_USER_STARTUP_CODE)
 *     - CLOCK_Initialize()         (optional, set/clear flag EXECUTE_MCC_SYSTEM_INITIALIZE)
 *     - DEVICE_Initialize()        (optional, set/clear flag EXECUTE_MCC_SYSTEM_INITIALIZE)
 *     - OS_Initialize()
 * 
 *   After this sequence has been completed, the CPU is running at maximum performance,
 *   starting to execute user defined task queues managed by the main task scheduler.
 * 
 *   In this task queue is reserved for all basic configurations of internal data objects
 *   and software root modules of the task manager.
 *  
 *   It is recommended to add all Initialization and configuration functions of user code
 *   modules and tasks to the task queue task_queue_firmware_init[] in a disabled state
 *   and further use task queue task_queue_startup_sequence[] to execute their enable 
 *   sequence.
 * 
 *   PLEASE NOTE:
 *   The boot task queue is only executed once calling all listed tasks in one sequence.
 *   At the end of this task queue the task manager will automatically switch over to 
 *   task queue task_queue_firmware_init[].
 * *********************************************************************************************** */

volatile uint16_t task_queue_boot[] = {
    TASK_INIT_APPLICATION, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_boot_size = (sizeof(task_queue_boot)/sizeof(task_queue_boot[0]));

/*!task_queue_firmware_init
 * ***********************************************************************************************
 *   In OP_MODE_FIRMWARE_INIT the task queue covers all user software modules and basic  
 *   peripheral configurations 
 * 
 *   To support this approach, all initialization functions of peripheral and software modules 
 *   are configured in a disabled state by default (e.g. by masking out the ENABLE bit).
 *   Each peripheral of software module should offer an additional ENABLE function 
 *   call or ENABLE bit for the purpose of enabling a pre-configured peripheral whenever needed. 
 * 
 *   Once all peripherals and software modules have been set up, they should be enabled in the
 *   desired, application specific sequence/order within the task_queue_startup_sequence[]. 
 * 
 *   PLEASE NOTE:
 *   The device startup task queue is only executed once calling all listed tasks in one successive 
 *   sequence.  At the end of this task queue the task manager will automatically switch over to 
 *   task_queue_startup_sequence[].
 * *********************************************************************************************** */

volatile uint16_t task_queue_firmware_init[] = {
    TASK_PWR_CONTROL_INIT,  // Step #0
    TASK_DEBUG_UART_INIT,  // Step #1
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_firmware_init_size = (sizeof(task_queue_firmware_init)/sizeof(task_queue_firmware_init[0]));

/*!task_queue_startup_sequence
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

volatile uint16_t task_queue_startup_sequence[] = {
    TASK_PWR_CONTROL_EXECUTE, // Step #0
    TASK_INIT_PDSTACK, // Step #1
    TASK_DEBUG_UART_EXECUTE, // Step #2
    TASK_IDLE  // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_startup_sequence_size = (sizeof(task_queue_startup_sequence)/sizeof(task_queue_startup_sequence[0]));

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
    TASK_PWR_CONTROL_EXECUTE,  // Step #0
    TASK_PDSTACK, // Step #1
    TASK_DEBUG_UART_EXECUTE, // Step #2
    TASK_IDLE
};
volatile uint16_t task_queue_idle_size = (sizeof(task_queue_idle)/sizeof(task_queue_idle[0]));
volatile uint16_t task_queue_idle_init(void)
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    DBGLED_INIT_OUTPUT;
    DBGLED_WR = LED_ON;
#endif
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
volatile uint16_t task_queue_run[] = {
    TASK_1,                     // Step #0
    TASK_2                      // Step #1
    TASK_3                      // Step #2
    (...),                      // Step #3
    TASK_IDLE                   // Step #n => empty buffer task execution window to account for 
                                // overrunning task execution time
};
volatile uint16_t task_queue_run_size = (sizeof(task_queue_run)/sizeof(task_queue_run[0]));
*/

/*!task_queue_run
 * ***********************************************************************************************
 *   In OP_MODE_RUN task queue run is executed until a new operating mode is selected and a 
 *   new/different task queue is loaded.
 * 
 *   In NORMAL MODE the system is performing its normal function. All tasks which need to be
 *   executed in this mode need to added to this task queue.
 * *********************************************************************************************** */

volatile uint16_t task_queue_run[] = {
    TASK_PWR_CONTROL_EXECUTE, // Step #0
    TASK_PDSTACK, // Step #1
    TASK_DEBUG_UART_EXECUTE, // Step #2
    TASK_IDLE  // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_run_size = (sizeof(task_queue_run)/sizeof(task_queue_run[0]));
volatile uint16_t task_queue_run_init(void)
{
#if defined (__MA330048_P33CK_R30_USB_PD_BOB__)
    DBGLED_INIT_OUTPUT;
    DBGLED_WR = LED_OFF;
#endif
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
    TASK_PWR_CONTROL_EXECUTE,  // Step #0
    TASK_DEBUG_UART_EXECUTE, // Step #1
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_fault_size = (sizeof(task_queue_fault)/sizeof(task_queue_fault[0]));
volatile uint16_t task_queue_fault_init(void)
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
    TASK_DEBUG_UART_EXECUTE, // Step #0
    TASK_IDLE   // empty task used as task list execution time buffer 
};
volatile uint16_t task_queue_standby_size = (sizeof(task_queue_standby)/sizeof(task_queue_standby[0]));
volatile uint16_t task_queue_standby_init(void)
{
    Nop();
    return(1);
}

// EOF