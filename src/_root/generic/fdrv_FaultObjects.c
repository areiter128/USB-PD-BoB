/*
 * File:   os_FaultObjects.c
 * Author: M91406
 *
 * Created on October 9, 2019, 4:11 PM
 */

#include "_root/generic/os_Globals.h"

/*!Operating System Fault Object Declaration
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent OS-defined fault objects. These declarations 
 * have the same structure as the user-defined fault objects. The fault handler function driver
 * fdrv_FaultHandler checks the OS-related fault objects first and then checks all other,
 * user-defined fault objects declared in task_FaultHandler.c and added to the fault object list
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
volatile FAULT_OBJECT_t fltobj_TaskMgrPeriodViolation;
volatile FAULT_OBJECT_t fltobj_OSComponentFailure;

/*!os_fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The os_fault_object_list[] array is a list of operating-system specific fault objects. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user-defined fault actions.
 * ***********************************************************************************************/

volatile FAULT_OBJECT_t *os_fault_object_list[] = {
    
    // fault objects for firmware modules and task manager flow
    &fltobj_CPUFailure,        // The CPU trap handler has detected a critical address error
    &fltobj_CPULoadOverrun,         // The CPU meter indicated an overrun condition (no free process time left))
    &fltobj_TaskExecutionFailure,   // A user task returned an error code ("no success")
    &fltobj_TaskTimeQuotaViolation, // A user time execution took longer than specified
    &fltobj_TaskMgrPeriodViolation, // Task manager base timer period has expired while one execution period has not completed
    &fltobj_OSComponentFailure,     // One of the internal OS component functions has returned a failure
    
    // user defined fault objects
    /* ToDo: Add user defined fault objects here */

};
volatile uint16_t os_fltobj_list_size = (sizeof(os_fault_object_list)/sizeof(os_fault_object_list[0]));


/*!fault_object_init_functions[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile uint16_t CPUFailureObject_Initialize(void);
volatile uint16_t CPULoadOverrunFaultObject_Initialize(void);
volatile uint16_t TaskExecutionFaultObject_Initialize(void);
volatile uint16_t TaskTimeQuotaViolationFaultObject_Initialize(void);
volatile uint16_t TaskMgrPeriodViolationFaultObject_Initialize(void);
volatile uint16_t OSComponentFailureFaultObject_Initialize(void);


volatile uint16_t (*os_fault_object_init_functions[])(void) = {
    
    // fault objects for firmware modules and task manager flow
    &CPUFailureObject_Initialize,        // The CPU trap handler has detected a critical address error
    &CPULoadOverrunFaultObject_Initialize,         // The CPU meter indicated an overrun condition (no free process time left))
    &TaskExecutionFaultObject_Initialize,   // A user task returned an error code ("no success")
    &TaskTimeQuotaViolationFaultObject_Initialize, // A user time execution took longer than specified
    &TaskMgrPeriodViolationFaultObject_Initialize, // Task manager base timer period has expired while one execution period has not completed
    &OSComponentFailureFaultObject_Initialize,     // One of the internal OS component functions has returned a failure
    
};
volatile uint16_t os_fault_object_init_functions_size = (sizeof(os_fault_object_init_functions)/sizeof(os_fault_object_init_functions[0]));



/*!CPUFailureObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_CPUFailure is initialized here. This fault detects conditions which enforces a 
 * CPU RESET by software. The common fault handler will monitor the traplog object using 
 * a bit mask defining all traps which will initiate the software-initiated Warm CPU Reset.
 * ***********************************************************************************************/

volatile uint16_t CPUFailureObject_Initialize(void) 
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
    fltobj_CPUFailure.user_fault_action = &APPLICATION_Reset; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_CPUFailure.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_CPUFailure.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsi = 1; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_CPUFailure.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_CPUFailure.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_CPUFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_CPUFailure.status.bits.fltchken = 1; // Enable/disable fault check

    return(fres);
}

/*!CPULoadOverrunFaultObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_CPULoadOverrun is initialized here. This fault detects conditions where the CPU
 * meter of the main scheduler detects an overrun condition, where there is no free process
 * time left.
 * ***********************************************************************************************/

volatile uint16_t CPULoadOverrunFaultObject_Initialize(void)
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

    fltobj_CPULoadOverrun.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_CPULoadOverrun.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_CPULoadOverrun.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!TaskExecutionFaultObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskExecutionFailure is initialized here. This fault detects conditions where a 
 * user defined task called by the main scheduler returns a failure flag
 * ***********************************************************************************************/

volatile uint16_t TaskExecutionFaultObject_Initialize(void)
{
    // Configuring the Task Execution Failure fault object

    // specify the target value/register to be monitored
    fltobj_TaskExecutionFailure.source_object = &task_mgr.proc_code.segment.retval;
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

    fltobj_TaskExecutionFailure.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_TaskExecutionFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskExecutionFailure.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
    
}

/*!TaskTimeQuotaViolationFaultObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskTimeQuotaViolation is initialized here. This fault detects conditions where a 
 * user defined task takes more time than defined in the user task time quota or exceeds the 
 * maximum time quota defined within the task manager data structure.
 * ***********************************************************************************************/

volatile uint16_t TaskTimeQuotaViolationFaultObject_Initialize(void)
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

    fltobj_TaskTimeQuotaViolation.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskTimeQuotaViolation.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}

/*!TaskMgrPeriodViolationFaultObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_TaskMgrPeriodViolation is initialized here. This fault detects conditions where  
 * task manager base timer has overrun while the most recent execution period was not complete.
 * This fault may be tripped by stalling user tasks, violating their time quota and exceeding the
 * maximum execution period of the task manager.
 * ***********************************************************************************************/

volatile uint16_t TaskMgrPeriodViolationFaultObject_Initialize(void) 
{
    // Configuring the Task Time Quota Violation fault object
    fltobj_TaskMgrPeriodViolation.source_object = &task_mgr.status.value;
    fltobj_TaskMgrPeriodViolation.object_bit_mask = EXEC_STAT_TSKMGR_PER_OVR;
    fltobj_TaskMgrPeriodViolation.error_code = (uint32_t)FLTOBJ_TASK_MGR_PERIOD_VIOLATION;
    fltobj_TaskMgrPeriodViolation.id = (uint16_t)FLTOBJ_TASK_MGR_PERIOD_VIOLATION;

    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_TaskMgrPeriodViolation.criteria.counter = 0;      // Set/reset fault counter
    fltobj_TaskMgrPeriodViolation.criteria.fault_ratio = FAULT_LEVEL_EQUAL; // Set comparison type
    fltobj_TaskMgrPeriodViolation.criteria.trip_level = true;   // Set/reset trip level value
    fltobj_TaskMgrPeriodViolation.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_TaskMgrPeriodViolation.criteria.reset_level = false;  // Set/reset fault release level value
    fltobj_TaskMgrPeriodViolation.criteria.reset_cnt_threshold = 100; // Set/reset number of successive resets before triggering fault release
        
    // specifying fault class, fault level and enable/disable status
    fltobj_TaskMgrPeriodViolation.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_TaskMgrPeriodViolation.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_TaskMgrPeriodViolation.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_TaskMgrPeriodViolation.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_TaskMgrPeriodViolation.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskMgrPeriodViolation.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_TaskMgrPeriodViolation.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_TaskMgrPeriodViolation.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_TaskMgrPeriodViolation.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_TaskMgrPeriodViolation.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_TaskMgrPeriodViolation.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_TaskMgrPeriodViolation.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_TaskMgrPeriodViolation.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_TaskMgrPeriodViolation.status.bits.fltchken = 1; // Enable/disable fault check

    return(1);
}

/*!OSComponentFailureFaultObject_Initialize
 * ***********************************************************************************************
 * Description:
 * The fltobj_OSComponentFailure is initialized here. This fault detects conditions where a 
 * operating system component (CPU meter, fault handler or capturing system status fails.
 * this fault condition is critical.
 * ***********************************************************************************************/

volatile uint16_t OSComponentFailureFaultObject_Initialize(void) 
{
    // Configuring the Task Time Quota Violation fault object
    fltobj_OSComponentFailure.comp_type = FAULT_COMPARE_CONSTANT;

    fltobj_OSComponentFailure.source_object = &task_mgr.status.value;
    fltobj_OSComponentFailure.object_bit_mask = EXEC_STAT_OS_COMP_CHECK;
    fltobj_OSComponentFailure.error_code = (uint32_t)FLTOBJ_OS_COMPONENT_FAILURE;
    fltobj_OSComponentFailure.id = (uint16_t)FLTOBJ_OS_COMPONENT_FAILURE;

    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OSComponentFailure.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OSComponentFailure.criteria.fault_ratio = FAULT_LEVEL_BOOLEAN;
    fltobj_OSComponentFailure.criteria.trip_level = true;   // Set/reset trip level value
    fltobj_OSComponentFailure.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_OSComponentFailure.criteria.reset_level = false;  // Set/reset fault release level value
    fltobj_OSComponentFailure.criteria.reset_cnt_threshold = 100; // Set/reset number of successive resets before triggering fault release
        
    // specifying fault class, fault level and enable/disable status
    fltobj_OSComponentFailure.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OSComponentFailure.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OSComponentFailure.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OSComponentFailure.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OSComponentFailure.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OSComponentFailure.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OSComponentFailure.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_OSComponentFailure.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OSComponentFailure.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_OSComponentFailure.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OSComponentFailure.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_OSComponentFailure.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OSComponentFailure.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OSComponentFailure.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(1);
}

