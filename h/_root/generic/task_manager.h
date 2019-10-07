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
/*!task_manager.h
 *****************************************************************************
 * File:   task_manager.h
 *
 * Summary:
 * Task manager header file
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

#ifndef _ROOT_TASK_MANAGER_H_
#define	_ROOT_TASK_MANAGER_H_
    
#include <stdint.h>
#include <stdbool.h>

/* Data structures */

typedef enum {
    OP_MODE_UNKNOWN          = 0b0000000000000000, // Define for unknown state of the task scheduler => ERROR!
    OP_MODE_BOOT             = 0b0000000000000001, // Operation mode during device start-up => basic task manager setup
    OP_MODE_FIRMWARE_INIT    = 0b0000000000000010, // User-code modules and generic peripherals configuration (initialization in disabled state)
    OP_MODE_STARTUP_SEQUENCE = 0b0000000000000100, // User-code module and generic peripheral start sequence
    OP_MODE_IDLE             = 0b0000000000001000, // Entering Normal operation mode, "NO ACTION" operating mode from which active op-modes are enabled
    OP_MODE_NORMAL           = 0b0000000000010000, // System is powered and performing "normal functions"
    OP_MODE_FAULT            = 0b0100000000000000, // A critical FAULT condition has been detected and system is partially shut down, waiting for a restart-attempt
    OP_MODE_STANDBY          = 0b1000000000000000  // Standby mode, all sub-modules are disabled and CPU is in low-power mode
} SYSTEM_OPERATION_MODE_e;

typedef union {
    struct {
        volatile bool boot:1;           // Bit #0: Operation mode during device start-up and peripheral configuration
        volatile bool device_startup;   // Bit #1: On-chip peripherals start-up period (self-check, soft-start, etc.)
        volatile bool system_startup;   // Bit #2: Power converter start-up period (self-check, soft-start, etc.)
        volatile bool idle;             // Bit #3: Idle operation mode is the generic fall-back op-mode when no other op-mode applies to current conditions
        volatile bool normal;           // Bit #4: Normal operation mode is set when system performs the desired default function (whatever this may be needs to be defined)
        volatile unsigned :1;           // Bit #5: (reserved)
        volatile unsigned :1;           // Bit #6: (reserved)
        volatile unsigned :1;           // Bit #7: (reserved)

        volatile unsigned :1;           // Bit #8: (reserved)
        volatile unsigned :1;           // Bit #9: (reserved)
        volatile unsigned :1;           // Bit #10: (reserved)
        volatile unsigned :1;           // Bit #11: (reserved)
        volatile unsigned :1;           // Bit #12: (reserved)
        volatile unsigned :1;           // Bit #13: (reserved)
        volatile bool fault;            // Bit #14: Fault mode will be entered when a critical fault condition has been detected
        volatile bool standby;          // Bit #15: During standby mode the converter is disabled
    } __attribute__((packed)) bits;
	volatile SYSTEM_OPERATION_MODE_e value;
}SYSTEM_OPERATION_MODE_t;

typedef struct {
    volatile uint32_t ticks; // Counter for CPU load measurement
    volatile uint16_t load; // CPU load result
    volatile uint16_t load_max_buffer; // CPU load maximum is tracked and logged
    volatile uint16_t loop_nomblk; // Number of cycles required for one CPU load counter tick
    volatile uint32_t load_factor; // CPU_TICKS result has to be multiplied with this number to get CPU_LOAD in [10x %] => percentage with 1 digit accuracy, e.g. 124 = 12.4%
} CPU_LOAD_SETTINGS_t;

typedef union {
    struct {
        volatile uint16_t retval; // Function return value
        volatile uint8_t task_id; // task ID of the function called
        volatile uint8_t op_mode; // recent operating mode when the function was called
    } __attribute__((packed))segment;
    volatile uint32_t value;
} TASKMGR_PROCESS_CODE_t;

typedef struct {
    volatile uint16_t quota; // Maximum allowed task execution period
    volatile uint16_t task_time; // Execution time meter result of last called task
    volatile uint16_t maximum; // Task time meter maximum is tracked and logged
} __attribute__((packed))TASK_CONTROL_t;

typedef enum {
    EXEC_STAT_FAULT_OVERRIDE        = 0b0000000000000001, // Some fault condition is overriding task settings and actions
    EXEC_STAT_START_COMPLETE        = 0b0000000000000010, // Firmware has passed startup sequence
    EXEC_STAT_QUEUE_SWITCH          = 0b0000000000000100, // Task manager has just switched task queues
    EXEC_STAT_TSKMGR_PER_OVR        = 0b0000000000001000, // Task manager base timer period overrun flag bit
    EXEC_STAT_OS_COMP_CHECK         = 0b0000000000010000, // Task manager internal component check flag bit
        
    EXEC_STAT_NOTIFICATION_PENDING  = 0b0010000000000000, // Some condition raised a notification flag
    EXEC_STAT_WARNING_PENDING       = 0b0100000000000000, // Some condition raised a warning flag
    EXEC_STAT_FAULT_PENDING         = 0b1000000000000000  // Some condition raised a critical fault flag
}TASKMGR_STATUS_e;

typedef union  {
    struct {
        volatile bool fault_override :1; // Bit #0: Flag bit indicating that all other operating modes are overridden by the FAULT_HANDLER
        volatile bool startup_sequence_complete :1; // Bit #1: Flag bit indicating that device and system startup has been completed
        volatile bool queue_switch :1; // Bit #2: queue_switch occurred (active for one queue loop)
        volatile bool task_mgr_period_overrun :1; // Bit #3:  Flag bit indicating task manager base time has overrun before an execution period was complete
        volatile bool os_component_check :1; // Bit #4: OS component function return value validation (0=failure, 1=success)
        volatile unsigned :1; // Bit #5:  (reserved)
        volatile unsigned :1; // Bit #6:  (reserved)
        volatile unsigned :1; // Bit #7:  (reserved)

        volatile unsigned :1; // Bit #8:  (reserved)
        volatile unsigned :1; // Bit #9:  (reserved)
        volatile unsigned :1; // Bit #10: (reserved)
        volatile unsigned :1; // Bit #11: (reserved)
        volatile unsigned :1; // Bit #12: (reserved)
        volatile bool global_notify :1;	// Bit #13: flag bit indicating the presence of notify events
        volatile bool global_warning :1;	// Bit #14: flag bit indicating the presence of warning events
        volatile bool global_fault :1;	// Bit #15: flag bit indicating the presence of fault events
    } __attribute__((packed))bits;
	volatile TASKMGR_STATUS_e value; // buffer for 16-bit word read/write operations
} TASKMGR_STATUS_t;


typedef struct {

    /* System operation mode (selects the active task queue) */
    volatile SYSTEM_OPERATION_MODE_t pre_op_mode; // ID of previous operating mode (=op_mode after switch-over)
    volatile SYSTEM_OPERATION_MODE_t op_mode; // ID of current operating mode
    volatile uint16_t (*op_mode_switch_over_function)(void); // pointer to a user function called when a switch in op_mode is performed
    volatile TASKMGR_PROCESS_CODE_t proc_code;   // in case an execution error occurred, this code contains task ID
                                    // and queue ID which caused the error 
    
    /* Active task queue properties */
    volatile uint16_t exec_task_id; // Main task ID from task id definition table
    volatile uint16_t *task_queue; // Pointer to the task queue (lookup table of task flow combinations)
    volatile uint16_t task_queue_tick_index; // Most recent index of the task queue element to be executed 
    volatile uint16_t task_queue_ubound; // Number of tasks in the current queue (n-1)

    /* Settings for task scheduler timer */
    volatile uint16_t task_timer_index; // specifies the timer used for the task manager (e.g. 1 for Timer1)
    volatile uint16_t *reg_task_timer_period; // Pointer to Timer period register (e.g. PR1)
    volatile uint16_t *reg_task_timer_counter; // Pointer to Timer counter register (e.g. TMR1))
    volatile uint16_t *reg_task_timer_irq_flag; // Pointer to Timer interrupt flag register (e.g. IFS0)
    volatile uint16_t task_timer_irq_flag_mask; // Bit-Mask for filtering on dedicated interrupt flag bit

    /* Generic task execution time control settings and buffer variables */
    volatile TASK_CONTROL_t task_time_ctrl; // Task time control settings and monitoring

    /* CPU Load Meter variables */
    volatile CPU_LOAD_SETTINGS_t cpu_load;
    
    /* Global task manager status flags */
    volatile TASKMGR_STATUS_t status;
    
} TASK_MANAGER_t;

// Public Task Manager data structure declaration
extern volatile TASK_MANAGER_t task_mgr; // Declare a data structure holding the settings of the task manager


// Public Task Manager Function Prototypes
extern volatile uint16_t init_TaskManager(void);
extern volatile uint16_t task_manager_tick(void);
extern volatile uint16_t task_CheckOperationModeStatus(void);


#endif	/* _ROOT_TASK_MANAGER_H_ */
