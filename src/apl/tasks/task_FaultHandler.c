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
/*!task_FaultHandler.c
 * ****************************************************************************
 * File:   task_FaultHandler.c
 * Author: M91406
 *
 * Description:
 * This source file provides multiple functions to set up and monitor user-
 * defined fault objects as well as routines to handle specific fault cases.
 * 
 * History:
 * Created on June 22, 2018, 01:14 PM
 ******************************************************************************/

#include "xc.h"
#include <stdint.h>

#include "apl/apl.h"
#include "apl/tasks/task_FaultHandler.h"

/*!User-Defined Fault Objects
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent user-defined fault objects. Every fault object
 * used to monitor values of variables or registers throughout the firmware needs to be declared 
 * here.
 *
 * Please note:
 * All fault objects must be added to the list of fault objects fault_object_list[] in file 
 * task_FaultHandler.c. 
 * After having added a fault object to the fault_object_list[], add a friendly label to the
 * fault_object_index_e enumeration.
 * ***********************************************************************************************/

// Fault objects for firmware modules and task manager flow control
FAULT_OBJECT_t fltobj_CPULoadOverrun;
FAULT_OBJECT_t fltobj_TaskExecutionFailure;
FAULT_OBJECT_t fltobj_TaskTimeQuotaViolation;

// Declaration of user defined fault objects
FAULT_OBJECT_t fltobj_PowerSourceFailure;


/*!User-Defined Fault Objects Initialization
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent user-defined initialization routines of each
 * defined fault object. Every fault object used to monitor values of variables or registers 
 * throughout the firmware needs to be initialized by a separate initialization routine.
 * ***********************************************************************************************/

inline uint16_t init_CPULoadOverrunFaultObject(void);
inline uint16_t init_TaskExecutionFaultObject(void);
inline uint16_t init_TaskTimeQuotaViolationFaultObject(void);

    // user defined fault objects
inline uint16_t init_MyCustomFaultObject(void);

/*!fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

FAULT_OBJECT_t *fault_object_list[] = {
    
    // fault objects for firmware modules and task manager flow
    &fltobj_CPULoadOverrun,    // The CPU meter indicated an overrun condition (no free process time left))
    &fltobj_TaskExecutionFailure,   // a task returned an error code ("no success")
    &fltobj_TaskTimeQuotaViolation, // a time execution took longer than specified
    
    // user defined fault objects
    &fltobj_PowerSourceFailure, 

};
uint16_t fltobj_list_size = (sizeof(fault_object_list)/sizeof(fault_object_list[0]));

/*!init_FaultObjects
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile uint16_t init_FaultObjects(void)
{
    volatile uint16_t fres = 0;

    fres = init_CPULoadOverrunFaultObject();
    fres &= init_TaskExecutionFaultObject();
    fres &= init_TaskTimeQuotaViolationFaultObject();
    
    // user defined fault objects
    fres &= init_MyCustomFaultObject();

    // Set global fault flags (need to be cleared during operation)
    task_mgr.status.flags.global_fault = 1;
    task_mgr.status.flags.global_warning = 1;
    task_mgr.status.flags.global_notice = 1;
    
    return(fres);
    
}

/*!init_CPULoadOverrunFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_CPULoadOverrun is initialized here. This fault detects conditions where the CPU
 * meter of the main scheduler detects an overrun condition, where there is no free process
 * time left.
 * ***********************************************************************************************/

inline uint16_t init_CPULoadOverrunFaultObject(void)
{
    // Configuring the CPU Load Overrun fault object

    // specify the target value/register to be monitored
    fltobj_CPULoadOverrun.object = &task_mgr.cpu_load.load_max_buffer; // monitoring the CPU meter result
    fltobj_CPULoadOverrun.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_CPULoadOverrun.error_code = (uint32_t)FLTOBJ_CPU_LOAD_OVERRUN;
    fltobj_CPULoadOverrun.id = (uint16_t)FLTOBJ_CPU_LOAD_OVERRUN;
    
    /* TODO: identify and set generic CPU load warning/fault thresholds */
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_CPULoadOverrun.criteria.counter = 0;      // Set/reset fault counter
    fltobj_CPULoadOverrun.criteria.fault_ratio = FAULT_LEVEL_LESS_THAN;
    fltobj_CPULoadOverrun.criteria.trip_level = 50;   // Set/reset trip level value
    fltobj_CPULoadOverrun.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_CPULoadOverrun.criteria.reset_level = 100;  // Set/reset fault release level value
    fltobj_CPULoadOverrun.criteria.reset_cnt_threshold = 1; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_CPULoadOverrun.classes.flags.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_CPULoadOverrun.classes.flags.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_CPULoadOverrun.classes.flags.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_CPULoadOverrun.classes.flags.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_CPULoadOverrun.classes.flags.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPULoadOverrun.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPULoadOverrun.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_CPULoadOverrun.status.flags.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_CPULoadOverrun.status.flags.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_CPULoadOverrun.status.flags.fltlvlsi = 1; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_CPULoadOverrun.status.flags.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_CPULoadOverrun.status.flags.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_CPULoadOverrun.status.flags.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_CPULoadOverrun.status.flags.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!init_TaskExecutionFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskExecutionFailure is initialized here. This fault detects conditions where a 
 * user defined task called by the main scheduler returns a failure flag
 * ***********************************************************************************************/

inline uint16_t init_TaskExecutionFaultObject(void)
{
    // Configuring the Task Execution Failure fault object

    // specify the target value/register to be monitored
    fltobj_TaskExecutionFailure.object = &task_mgr.proc_code.segments.retval;
    fltobj_TaskExecutionFailure.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_TaskExecutionFailure.error_code = (uint32_t)FLTOBJ_TASK_EXECUTION_FAILURE;
    fltobj_TaskExecutionFailure.id = (uint16_t)FLTOBJ_TASK_EXECUTION_FAILURE;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_TaskExecutionFailure.criteria.counter = 0;      // Set/reset fault counter
    fltobj_TaskExecutionFailure.criteria.fault_ratio = FAULT_LEVEL_NOT_EQUAL;
    fltobj_TaskExecutionFailure.criteria.trip_level = 1;   // Set/reset trip level value
    fltobj_TaskExecutionFailure.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_TaskExecutionFailure.criteria.reset_level = 0;  // Set/reset fault release level value
    fltobj_TaskExecutionFailure.criteria.reset_cnt_threshold = 1; // Set/reset number of successive resets before triggering fault release

    // specifying fault class, fault level and enable/disable status
    fltobj_TaskExecutionFailure.classes.flags.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_TaskExecutionFailure.classes.flags.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_TaskExecutionFailure.classes.flags.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_TaskExecutionFailure.classes.flags.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_TaskExecutionFailure.classes.flags.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskExecutionFailure.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskExecutionFailure.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_TaskExecutionFailure.status.flags.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_TaskExecutionFailure.status.flags.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_TaskExecutionFailure.status.flags.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_TaskExecutionFailure.status.flags.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_TaskExecutionFailure.status.flags.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_TaskExecutionFailure.status.flags.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskExecutionFailure.status.flags.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!init_TaskTimeQuotaViolationFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskTimeQuotaViolation is initialized here. This fault detects conditions where a 
 * user defined task takes more time than defined in the user task time quota or exceeds the 
 * maximum time quota defined within the task manager data structure.
 * ***********************************************************************************************/

inline uint16_t init_TaskTimeQuotaViolationFaultObject(void)
{
    // Configuring the Task Time Quota Violation fault object
    fltobj_TaskTimeQuotaViolation.object = &task_mgr.task_time_ctrl.maximum;
    fltobj_TaskTimeQuotaViolation.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_TaskTimeQuotaViolation.error_code = (uint32_t)FLTOBJ_TASK_TIME_QUOTA_VIOLATION;
    fltobj_TaskTimeQuotaViolation.id = (uint16_t)FLTOBJ_TASK_TIME_QUOTA_VIOLATION;


    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_TaskTimeQuotaViolation.criteria.counter = 0;      // Set/reset fault counter
    fltobj_TaskTimeQuotaViolation.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_TaskTimeQuotaViolation.criteria.trip_level = (task_mgr.task_time_ctrl.quota - (task_mgr.task_time_ctrl.quota >> 3));   // Set/reset trip level value
    fltobj_TaskTimeQuotaViolation.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_TaskTimeQuotaViolation.criteria.reset_level = (task_mgr.task_time_ctrl.quota - (task_mgr.task_time_ctrl.quota >> 2));  // Set/reset fault release level value
    fltobj_TaskTimeQuotaViolation.criteria.reset_cnt_threshold = 10; // Set/reset number of successive resets before triggering fault release
        
    // specifying fault class, fault level and enable/disable status
    fltobj_TaskTimeQuotaViolation.classes.flags.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_TaskTimeQuotaViolation.classes.flags.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_TaskTimeQuotaViolation.classes.flags.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_TaskTimeQuotaViolation.classes.flags.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_TaskTimeQuotaViolation.classes.flags.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskTimeQuotaViolation.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskTimeQuotaViolation.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_TaskTimeQuotaViolation.status.flags.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_TaskTimeQuotaViolation.status.flags.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_TaskTimeQuotaViolation.status.flags.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_TaskTimeQuotaViolation.status.flags.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_TaskTimeQuotaViolation.status.flags.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.flags.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.flags.fltchken = 1; // Enable/disable fault check

    return(1);
}


/*!init_PowerSourceFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_PowerSourceFailure is initialized here. This fault object captures the condition 
 * when no power source is available (no AC source and no batteries)
 * ***********************************************************************************************/

inline uint16_t init_MyCustomFaultObject(void)
{
    // Configuring the Task Time Quota Violation fault object
    fltobj_PowerSourceFailure.object = &application.ctrl_status.value;
    fltobj_PowerSourceFailure.object_bit_mask = CTRL_STAT_POWERSOURCE_DETECTED;
    fltobj_PowerSourceFailure.error_code = (uint32_t)FLTOBJ_POWER_SOURCE_FAILURE;
    fltobj_PowerSourceFailure.id = (uint16_t)FLTOBJ_POWER_SOURCE_FAILURE;

    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_PowerSourceFailure.criteria.counter = 0;      // Set/reset fault counter
    fltobj_PowerSourceFailure.criteria.fault_ratio = FAULT_LEVEL_EQUAL;
    fltobj_PowerSourceFailure.criteria.trip_level = 0;   // Set/reset trip level value
    fltobj_PowerSourceFailure.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_PowerSourceFailure.criteria.reset_level = 1;  // Set/reset fault release level value
    fltobj_PowerSourceFailure.criteria.reset_cnt_threshold = 3; // Set/reset number of successive resets before triggering fault release

    // specifying fault class, fault level and enable/disable status
    fltobj_PowerSourceFailure.classes.flags.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_PowerSourceFailure.classes.flags.warning = 0;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_PowerSourceFailure.classes.flags.critical = 1; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_PowerSourceFailure.classes.flags.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_PowerSourceFailure.classes.flags.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_PowerSourceFailure.user_fault_action = 0; // Set = 0 if no function should be called, Set= [function pointer] to function which should be executed
    fltobj_PowerSourceFailure.user_fault_reset = 0; // Set = 0 if no function should be called, Set = [function pointer] to function which should be executed

    fltobj_PowerSourceFailure.status.flags.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_PowerSourceFailure.status.flags.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_PowerSourceFailure.status.flags.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_PowerSourceFailure.status.flags.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_PowerSourceFailure.status.flags.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_PowerSourceFailure.status.flags.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_PowerSourceFailure.status.flags.fltchken = 1; // Enable/disable fault check

    return(1);
}

