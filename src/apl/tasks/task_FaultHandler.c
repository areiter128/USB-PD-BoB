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
#include "hal/hal.h"
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
volatile FAULT_OBJECT_t fltobj_CPUFailure;
volatile FAULT_OBJECT_t fltobj_CPULoadOverrun;
volatile FAULT_OBJECT_t fltobj_TaskExecutionFailure;
volatile FAULT_OBJECT_t fltobj_TaskTimeQuotaViolation;

// Declaration of user defined fault objects
volatile FAULT_OBJECT_t fltobj_PowerSourceFailure;
volatile FAULT_OBJECT_t fltobj_PowerControlFailure_PortA;
volatile FAULT_OBJECT_t fltobj_PowerControlFailure_PortB;


/*!User-Defined Fault Objects Initialization
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent user-defined initialization routines of each
 * defined fault object. Every fault object used to monitor values of variables or registers 
 * throughout the firmware needs to be initialized by a separate initialization routine.
 * ***********************************************************************************************/

volatile uint16_t init_CPUFailureObject(void);
volatile uint16_t init_CPULoadOverrunFaultObject(void);
volatile uint16_t init_TaskExecutionFaultObject(void);
volatile uint16_t init_TaskTimeQuotaViolationFaultObject(void);

    // user defined fault objects
volatile uint16_t init_PowerSourceFaultObject(void);
volatile uint16_t init_PowerControlFaultObject_PortA(void);
volatile uint16_t init_PowerControlFaultObject_PortB(void);

/*!fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile FAULT_OBJECT_t *fault_object_list[] = {
    
    // fault objects for firmware modules and task manager flow
    &fltobj_CPUFailure,        // The CPU trap handler has detected a critical address error
    &fltobj_CPULoadOverrun,         // The CPU meter indicated an overrun condition (no free process time left))
    &fltobj_TaskExecutionFailure,   // A user task returned an error code ("no success")
    &fltobj_TaskTimeQuotaViolation, // A user time execution took longer than specified
    
    // user defined fault objects
    &fltobj_PowerSourceFailure,         // Input voltage is out of range preventing DC/DC converters to run
    &fltobj_PowerControlFailure_PortA,  // A critical fault was detected in DC/DC converter of port A
    &fltobj_PowerControlFailure_PortB   // A critical fault was detected in DC/DC converter of port B 

};
volatile uint16_t fltobj_list_size = (sizeof(fault_object_list)/sizeof(fault_object_list[0]));

/*!init_FaultObjects
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile uint16_t init_FaultObjects(void)
{
    volatile uint16_t fres = 1;

    fres &= init_CPUFailureObject();
    fres &= init_CPULoadOverrunFaultObject();
    fres &= init_TaskExecutionFaultObject();
    fres &= init_TaskTimeQuotaViolationFaultObject();
    
    // user defined fault objects
    fres &= init_PowerSourceFaultObject();
    fres &= init_PowerControlFaultObject_PortA();
    fres &= init_PowerControlFaultObject_PortB();

    // Set global fault flags (need to be cleared during operation)
    task_mgr.status.bits.global_fault = 1;
    task_mgr.status.bits.global_warning = 1;
    task_mgr.status.bits.global_notify = 1;
    
    return(fres);
    
}

/*!init_CPUFailure
 * ***********************************************************************************************
 * Description:
 * The fltobj_CPUFailure is initialized here. This fault detects conditions which enforces a 
 * CPU RESET by software. The common fault handler will monitor the traplog object using 
 * a bit mask defining all traps which will initiate the software-initiated Warm CPU Reset.
 * ***********************************************************************************************/

inline volatile uint16_t init_CPUFailureObject(void) 
{
    volatile uint16_t fres = 1;
    
    // Configuring the CPU Address Error fault object

    // specify the target value/register to be monitored
    fltobj_CPUFailure.source_object = &traplog.status.value; // monitoring the CPU traplog status
    fltobj_CPUFailure.object_bit_mask = FAULT_OBJECT_CPU_RESET_TRIGGER_BIT_MASK;
    fltobj_CPUFailure.error_code = (uint32_t)FLTOBJ_CPU_FAILURE_ERROR;
    fltobj_CPUFailure.id = (uint16_t)FLTOBJ_CPU_FAILURE_ERROR;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_CPUFailure.criteria.counter = 0;      // Set/reset fault counter
    fltobj_CPUFailure.criteria.fault_ratio = FAULT_LEVEL_EQUAL;
    fltobj_CPUFailure.criteria.trip_level = 1;   // Set/reset trip level value
    fltobj_CPUFailure.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_CPUFailure.criteria.reset_level = 1;  // Set/reset fault release level value
    fltobj_CPUFailure.criteria.reset_cnt_threshold = 1; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_CPUFailure.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_CPUFailure.flt_class.bits.warning = 0;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_CPUFailure.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_CPUFailure.flt_class.bits.catastrophic = 1; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_CPUFailure.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPUFailure.user_fault_action = &Application_reset; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPUFailure.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_CPUFailure.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsi = 1; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_CPUFailure.status.bits.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_CPUFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_CPUFailure.status.bits.fltchken = 1; // Enable/disable fault check

    return(fres);
}

/*!init_CPULoadOverrunFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_CPULoadOverrun is initialized here. This fault detects conditions where the CPU
 * meter of the main scheduler detects an overrun condition, where there is no free process
 * time left.
 * ***********************************************************************************************/

inline volatile uint16_t init_CPULoadOverrunFaultObject(void)
{
    // Configuring the CPU Load Overrun fault object

    // specify the target value/register to be monitored
    fltobj_CPULoadOverrun.source_object = &task_mgr.cpu_load.load_max_buffer; // monitoring the CPU meter result
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
    fltobj_CPULoadOverrun.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_CPULoadOverrun.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_CPULoadOverrun.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_CPULoadOverrun.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_CPULoadOverrun.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPULoadOverrun.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPULoadOverrun.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_CPULoadOverrun.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_CPULoadOverrun.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_CPULoadOverrun.status.bits.fltlvlsi = 1; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_CPULoadOverrun.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_CPULoadOverrun.status.bits.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_CPULoadOverrun.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_CPULoadOverrun.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!init_TaskExecutionFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskExecutionFailure is initialized here. This fault detects conditions where a 
 * user defined task called by the main scheduler returns a failure flag
 * ***********************************************************************************************/

inline volatile uint16_t init_TaskExecutionFaultObject(void)
{
    // Configuring the Task Execution Failure fault object

    // specify the target value/register to be monitored
    fltobj_TaskExecutionFailure.source_object = &task_mgr.proc_code.segments.retval;
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
    fltobj_TaskExecutionFailure.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_TaskExecutionFailure.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_TaskExecutionFailure.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_TaskExecutionFailure.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_TaskExecutionFailure.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskExecutionFailure.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskExecutionFailure.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_TaskExecutionFailure.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_TaskExecutionFailure.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_TaskExecutionFailure.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_TaskExecutionFailure.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_TaskExecutionFailure.status.bits.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_TaskExecutionFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskExecutionFailure.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!init_TaskTimeQuotaViolationFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskTimeQuotaViolation is initialized here. This fault detects conditions where a 
 * user defined task takes more time than defined in the user task time quota or exceeds the 
 * maximum time quota defined within the task manager data structure.
 * ***********************************************************************************************/

inline volatile uint16_t init_TaskTimeQuotaViolationFaultObject(void)
{
    // Configuring the Task Time Quota Violation fault object
    fltobj_TaskTimeQuotaViolation.source_object = &task_mgr.task_time_ctrl.maximum;
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
    fltobj_TaskTimeQuotaViolation.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_TaskTimeQuotaViolation.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_TaskTimeQuotaViolation.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_TaskTimeQuotaViolation.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_TaskTimeQuotaViolation.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskTimeQuotaViolation.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskTimeQuotaViolation.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_TaskTimeQuotaViolation.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_TaskTimeQuotaViolation.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_TaskTimeQuotaViolation.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_TaskTimeQuotaViolation.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_TaskTimeQuotaViolation.status.bits.fltstat = 1; // Set/ret fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}


/*!init_PowerSourceFaultObject
 * ***********************************************************************************************
 * Description:
 * The fltobj_PowerSourceFailure for 4-Switch BuckBoost converter #1 is initialized here. 
 * This fault object captures the condition when no power source is available.
 * ***********************************************************************************************/

/* ToDo:
 * There is no user function declared yet shutting down the power supply in case of a critical
 * fault condition. All critical power-related fault objects need to enable the USER_FAULT_CLASS
 * and need to declare the user function used to shut-down and restart the power supplies.
 */

inline volatile uint16_t init_PowerSourceFaultObject(void)
{
    // Configuring the Task Time Quota Violation fault object
    
    fltobj_PowerSourceFailure.source_object = &c4swbb_1.status.value;
    
    fltobj_PowerSourceFailure.object_bit_mask = C4SWBB_CTRL_STAT_POWERSOURCE_DETECTED;
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
    fltobj_PowerSourceFailure.flt_class.bits.notify = 0;   // Set if this fault object triggers a fault condition notification
    fltobj_PowerSourceFailure.flt_class.bits.warning = 0;  // Set if this fault object triggers a warning fault condition response
    fltobj_PowerSourceFailure.flt_class.bits.critical = 1; // Set if this fault object triggers a critical fault condition response
    fltobj_PowerSourceFailure.flt_class.bits.catastrophic = 0; // Set if this fault object triggers a catastrophic fault condition response

    fltobj_PowerSourceFailure.flt_class.bits.user_class = 0; // Set if this fault object triggers a user-defined fault condition response
    fltobj_PowerSourceFailure.user_fault_action = 0; // Clear if no function should be called, Set = [function pointer] to function which should be executed
    fltobj_PowerSourceFailure.user_fault_reset = 0; // Clear if no function should be called, Set = [function pointer] to function which should be executed

    fltobj_PowerSourceFailure.status.bits.fltlvlhw = 1; // Set if this fault condition is board-level fault condition
    fltobj_PowerSourceFailure.status.bits.fltlvlsw = 0; // Set if this fault condition is software-level fault condition
    fltobj_PowerSourceFailure.status.bits.fltlvlsi = 0; // Set if this fault condition is silicon-level fault condition
    fltobj_PowerSourceFailure.status.bits.fltlvlsys = 1; // Set if this fault condition is system-level fault condition

    fltobj_PowerSourceFailure.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_PowerSourceFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_PowerSourceFailure.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}

/*!init_PowerControlFaultObject_PortA
 * ***********************************************************************************************
 * Description:
 * The fltobj_PowerControlFailure for 4-Switch BuckBoost converter #1 is initialized here. 
 * This fault object captures the condition when the output voltage deviates from its reference
 * too much for too long.
 * ***********************************************************************************************/

inline volatile uint16_t init_PowerControlFaultObject_PortA(void)
{
    // Configuring the Task Time Quota Violation fault object
    
    // ToDo: Declare fault object by re-enabling the following code line:
    fltobj_PowerControlFailure_PortA.source_object = &c4swbb_1.data.v_out;
    fltobj_PowerControlFailure_PortA.source_object = &c4swbb_1.v_loop.reference;
    
    fltobj_PowerControlFailure_PortA.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_PowerControlFailure_PortA.error_code = (uint32_t)FLTOBJ_POWER_CONTROL_FAILURE_PORT_A;
    fltobj_PowerControlFailure_PortA.id = (uint16_t)FLTOBJ_POWER_CONTROL_FAILURE_PORT_A;

    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_PowerControlFailure_PortA.criteria.counter = 0;      // Set/reset fault counter
    fltobj_PowerControlFailure_PortA.criteria.fault_ratio = FAULT_LEVEL_EQUAL;
    fltobj_PowerControlFailure_PortA.criteria.trip_level = 0;   // Set/reset trip level value
    fltobj_PowerControlFailure_PortA.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_PowerControlFailure_PortA.criteria.reset_level = 1;  // Set/reset fault release level value
    fltobj_PowerControlFailure_PortA.criteria.reset_cnt_threshold = 3; // Set/reset number of successive resets before triggering fault release

    // specifying fault class, fault level and enable/disable status
    fltobj_PowerControlFailure_PortA.flt_class.bits.notify = 0;   // Set if this fault object triggers a fault condition notification
    fltobj_PowerControlFailure_PortA.flt_class.bits.warning = 0;  // Set if this fault object triggers a warning fault condition response
    fltobj_PowerControlFailure_PortA.flt_class.bits.critical = 1; // Set if this fault object triggers a critical fault condition response
    fltobj_PowerControlFailure_PortA.flt_class.bits.catastrophic = 0; // Set if this fault object triggers a catastrophic fault condition response

    fltobj_PowerControlFailure_PortA.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_PowerControlFailure_PortA.user_fault_action = 0; // Clear if no function should be called, Set= [function pointer] to function which should be executed
    fltobj_PowerControlFailure_PortA.user_fault_reset = 0; // Clear if no function should be called, Set = [function pointer] to function which should be executed

    fltobj_PowerControlFailure_PortA.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_PowerControlFailure_PortA.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_PowerControlFailure_PortA.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_PowerControlFailure_PortA.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_PowerControlFailure_PortA.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_PowerControlFailure_PortA.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_PowerControlFailure_PortA.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}

/*!init_PowerControlFaultObject_PortB
 * ***********************************************************************************************
 * Description:
 * The fltobj_PowerControlFailure for 4-Switch BuckBoost converter #2 is initialized here. 
 * This fault object captures the condition when the output voltage deviates from its reference
 * too much for too long.
 * ***********************************************************************************************/

inline volatile uint16_t init_PowerControlFaultObject_PortB(void)
{
    // Configuring the Task Time Quota Violation fault object
    
    // ToDo: Declare fault object by re-enabling the following code line:
    fltobj_PowerControlFailure_PortB.source_object = &c4swbb_2.data.v_out;
    fltobj_PowerControlFailure_PortB.compare_object = &c4swbb_2.v_loop.reference;
    
    fltobj_PowerControlFailure_PortB.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_PowerControlFailure_PortB.error_code = (uint32_t)FLTOBJ_POWER_CONTROL_FAILURE_PORT_B;
    fltobj_PowerControlFailure_PortB.id = (uint16_t)FLTOBJ_POWER_CONTROL_FAILURE_PORT_B;

    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_PowerControlFailure_PortB.criteria.counter = 0;      // Set/reset fault counter
    fltobj_PowerControlFailure_PortB.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_PowerControlFailure_PortB.criteria.trip_level = VOUT_MAX_DEV;   // Set/reset trip level value
    fltobj_PowerControlFailure_PortB.criteria.trip_cnt_threshold = 10; // Set/reset number of successive trips before triggering fault event
    fltobj_PowerControlFailure_PortB.criteria.reset_level = VOUT_MAX_DEV;  // Set/reset fault release level value
    fltobj_PowerControlFailure_PortB.criteria.reset_cnt_threshold = 2; // Set/reset number of successive resets before triggering fault release

    // specifying fault class, fault level and enable/disable status
    fltobj_PowerControlFailure_PortB.flt_class.bits.notify = 0;   // Set if this fault object triggers a fault condition notification
    fltobj_PowerControlFailure_PortB.flt_class.bits.warning = 0;  // Set if this fault object triggers a warning fault condition response
    fltobj_PowerControlFailure_PortB.flt_class.bits.critical = 1; // Set if this fault object triggers a critical fault condition response
    fltobj_PowerControlFailure_PortB.flt_class.bits.catastrophic = 0; // Set if this fault object triggers a catastrophic fault condition response

    fltobj_PowerControlFailure_PortB.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_PowerControlFailure_PortB.user_fault_action = 0; // Clear if no function should be called, Set= [function pointer] to function which should be executed
    fltobj_PowerControlFailure_PortB.user_fault_reset = 0; // Clear if no function should be called, Set = [function pointer] to function which should be executed

    fltobj_PowerControlFailure_PortB.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_PowerControlFailure_PortB.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_PowerControlFailure_PortB.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_PowerControlFailure_PortB.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_PowerControlFailure_PortB.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_PowerControlFailure_PortB.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_PowerControlFailure_PortB.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}

