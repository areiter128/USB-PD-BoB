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
/*!task_manager.c
 *****************************************************************************
 * File:   task_manager.c
 *
 * Summary:
 * Task manager initialization, operation mode switch-over and task execution routines
 *
 * Description:	
 * This file holds all routines of the basic scheduler functions covering scheduler 
 * settings initialization, basic task execution with time measurement and the 
 * operation mode switch over routine. CPU meter and time quota fault detection
 * are located in the main loop.
 * 
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


#include <xc.h>
#include <stdint.h>

#include "_root/config/task_manager_config.h"
#include "_root/generic/task_manager.h"
#include "apl/config/tasks.h"

// Private label for resetting a task queue
#define TASK_ZERO   0   

// Task Manager
volatile task_manager_settings_t task_mgr; // Declare a data structure holding the settings of the task manager

//------------------------------------------------------------------------------
// execute task manager scheduler
//------------------------------------------------------------------------------

uint16_t task_manager_tick(void) {

    volatile uint16_t fres = 0, tbuf = 0;

    // The task manager scheduler runs through the currently selected task queue in n steps.
    // After the last item of each queue the operation mode switch-over check is performed and the 
    // task tick index is reset to zero, which causes the first task of the queue to be called at 
    // the next scheduler tick.

    // Indices 0 ... (n-1) are calling queued user tasks
    task_mgr.exec_task_id = task_mgr.task_queue[task_mgr.task_queue_tick_index]; // Pick next task in the queue

    // Determine error code for the upcoming task
    task_mgr.proc_code.segments.op_mode = (uint8_t)(task_mgr.op_mode.mode);    // log operation mode
    task_mgr.proc_code.segments.task_id = (uint8_t)(task_mgr.exec_task_id);   // log upcoming task-ID

    // Capture task start time for time quota monitoring
    task_mgr.task_time_ctrl.buffer = *task_mgr.reg_task_timer_counter; // Capture timer counter before task execution

    // Execute next task in the queue
    fres = Task_Table[task_mgr.exec_task_id](); // Execute currently selected task

    // Capture time to determine elapsed task executing time
    tbuf = *task_mgr.reg_task_timer_counter;
    
    // Copy return value into process code for fault analysis
    task_mgr.proc_code.segments.retval = fres;
    
    if(tbuf > task_mgr.task_time_ctrl.buffer)
    // if timer period has not expired ...
    { 
        task_mgr.task_time_ctrl.task_time = tbuf - task_mgr.task_time_ctrl.buffer; // measure most recent task time
    }
    else
    // if timer has overrun try to capture the total elapsed time
    {
        tbuf = (*task_mgr.reg_task_timer_period - tbuf); // capture expired time until end of timer period
        task_mgr.task_time_ctrl.task_time = (tbuf + task_mgr.task_time_ctrl.buffer); // add elapsed time into the new period
    }

    // track maximum execution time
    if(task_mgr.task_time_ctrl.task_time > task_mgr.task_time_ctrl.maximum)
    {
        task_mgr.task_time_ctrl.maximum = task_mgr.task_time_ctrl.task_time; // override maximum time buffer value
    }
    
    return (fres);
}


//------------------------------------------------------------------------------
// Check operation mode status and switch op mode if needed
//------------------------------------------------------------------------------

uint16_t task_CheckOperationModeStatus(void) {

    // Short Fix if MCC Configuration is used
    if ((task_mgr.pre_op_mode.mode == OP_MODE_BOOT) && (task_mgr.op_mode.mode == OP_MODE_BOOT)) 
     // Boot-up task queue is only run once
    {
        task_mgr.op_mode.mode = OP_MODE_DEVICE_STARTUP;
    } 
    else if ((task_mgr.pre_op_mode.mode == OP_MODE_DEVICE_STARTUP) && (task_mgr.op_mode.mode == OP_MODE_DEVICE_STARTUP)) 
    // device resources start-up task queue is only run once before ending in FAULT mode.
    // only when all fault flags have been cleared the system will be able to enter startup-mode
    // to enter normal operation.
    { 
        task_mgr.op_mode.mode = OP_MODE_SYSTEM_STARTUP; // put system into Fault mode to make sure all FAULT flags are cleared before entering normal operation
    }
    else if ((task_mgr.pre_op_mode.mode == OP_MODE_SYSTEM_STARTUP) && (task_mgr.op_mode.mode == OP_MODE_SYSTEM_STARTUP)) 
    // system-level start-up task queue is only run once before ending in NORMAL mode.
    { 
        task_mgr.status.flags.startup_sequence_complete = true;
        task_mgr.op_mode.mode = OP_MODE_IDLE;
    }
    
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Skip execution if operation mode has not changed
    if (task_mgr.pre_op_mode.mode != task_mgr.op_mode.mode) {

        // If a change was detected, select the task queue and reset settings and flags
        switch (task_mgr.op_mode.mode) {
            
            case OP_MODE_BOOT:
                // Switch to initialization mode operation
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_boot; // Set task queue INIT
                task_mgr.task_queue_ubound = (task_queue_boot_size-1);
                task_mgr.op_mode_switch_over_function = 0; // Do not perform any user function during switch-over to this mode
                break;

            case OP_MODE_DEVICE_STARTUP:
                // Switch to device startup mode operation (launching and enabling peripherals)
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_device_startup; // Set task queue DEVICE_STARTUP
                task_mgr.task_queue_ubound = (task_queue_device_startup_size-1);
                task_mgr.op_mode_switch_over_function = 0; // Do not perform any user function during switch-over to this mode
                break;

            case OP_MODE_SYSTEM_STARTUP:
                // Switch to system startup mode operation (launching external systems / power sequencing / soft-start)
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_system_startup; // Set task queue SYSTEM_STARTUP
                task_mgr.task_queue_ubound = (task_queue_system_startup_size-1);
                task_mgr.op_mode_switch_over_function = 0; // Do not perform any user function during switch-over to this mode
                break;

            case OP_MODE_NORMAL:
                // Switch to normal operation
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_normal; // Set task queue NORMAL
                task_mgr.task_queue_ubound = (task_queue_normal_size-1);
                task_mgr.op_mode_switch_over_function = &task_queue_init_normal; // Execute user function before switching to this operating mode
                break;

            case OP_MODE_FAULT:
                // Switch to fault mode operation
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_fault; // Set task queue FAULT
                task_mgr.task_queue_ubound = (task_queue_fault_size-1);
                task_mgr.status.flags.fault_override = true; // set global fault override flag bit
                task_mgr.op_mode_switch_over_function = &task_queue_init_fault; // Execute user function before switching to this operating mode
                break;

            case OP_MODE_STANDBY:
                // Switch to standby mode operation 
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_standby; // Set task queue STANDBY
                task_mgr.task_queue_ubound = (task_queue_standby_size-1);
                task_mgr.op_mode_switch_over_function = &task_queue_init_standby; // Execute user function before switching to this operating mode
                break;

            default: // OP_MODE_IDLE
                // Switch to normal operation
                task_mgr.exec_task_id = TASK_ZERO; // Set task ID to DEFAULT (Idle Task))
                task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
                task_mgr.task_time_ctrl.task_time = 0; // Reset recent task time meter result
                task_mgr.task_time_ctrl.maximum = 0; // Reset max task time gauge
                task_mgr.task_queue = task_queue_idle; // Set task queue NORMAL
                task_mgr.task_queue_ubound = (task_queue_idle_size-1);
                task_mgr.op_mode_switch_over_function = &task_queue_init_idle; // Execute user function before switching to this operating mode
                break;
                
        }

        if(task_mgr.op_mode_switch_over_function != NULL) // If op-mode switch-over function has been defined, ...
        { task_mgr.op_mode_switch_over_function(); } // Execute user function before switching to this operating mode
        task_mgr.pre_op_mode.mode = task_mgr.op_mode.mode; // Sync OpMode Flags
        task_mgr.status.flags.queue_switch = true; // set queue switch flag for one queue execution loop

    }
    else // if operating mode has not changed, reset task queue change flag bit
    {
        task_mgr.status.flags.queue_switch = false; // reset queue switch flag for one queue execution loop
    }

    return (1);
}


// ======================================================================================================
// Basic Task Manager Structure Initialization
// ==============================================================================================

uint16_t init_TaskManager(void) {

    uint16_t fres = 1;

    // initialize private flag variable pre-op-mode used by task_CheckOperationModeStatus to identify changes in op_mode
    task_mgr.pre_op_mode.mode = OP_MODE_BOOT;

    // Initialize basic Task Manager Status
    task_mgr.op_mode.mode = OP_MODE_BOOT; // Set operation mode to STANDBY
    task_mgr.proc_code.value = 0; // Reset process code
    task_mgr.exec_task_id = TASK_IDLE; // Set task ID to DEFAULT (IDle Task))
    task_mgr.task_queue_tick_index = 0; // Reset task queue pointer
    task_mgr.task_time_ctrl.task_time = 0; // Reset maximum task time meter result
    task_mgr.task_queue = task_queue_boot; // Set task queue INIT
    task_mgr.task_queue_ubound = (task_queue_boot_size-1);

    task_mgr.status.flags.queue_switch = false;
    task_mgr.status.flags.startup_sequence_complete = false;
    task_mgr.status.flags.fault_override = false;
    
    // Scheduler Timer Configuration
    task_mgr.task_timer_index = TASK_MGR_TIMER_INDEX; // Index of the timer peripheral used
    task_mgr.reg_task_timer_counter = &TASK_MGR_TIMER_COUNTER_REGISTER;
    task_mgr.reg_task_timer_period = &TASK_MGR_TIMER_PERIOD_REGISTER;
    task_mgr.task_time_ctrl.quota = *task_mgr.reg_task_timer_period; // Global task execution period 
    task_mgr.reg_task_timer_irq_flag = &TASK_MGR_TIMER_ISR_FLAG_REGISTER;
    task_mgr.task_timer_irq_flag_mask = TASK_MGR_TIMER_ISR_FLAG_BIT_MASK;

    // CPU Load Monitor Configuration
    task_mgr.cpu_load.load = 0;
    task_mgr.cpu_load.load_max_buffer = 0;
    task_mgr.cpu_load.ticks = 0;
    task_mgr.cpu_load.loop_nomblk = TASK_MGR_CPU_LOAD_NOMBLK;
    task_mgr.cpu_load.load_factor = TASK_MGR_CPU_LOAD_FACTOR;

    #if (USE_TASK_EXECUTION_CLOCKOUT_PIN == 1)
        TS_CLOCKOUT_PIN_INIT_OUTPUT;
    #endif

    return (fres);
}

