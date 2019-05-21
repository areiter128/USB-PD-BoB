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
/*!fdrv_FaultHandler.c
 * ****************************************************************************
 * File:   fdrv_FaultHandler.c
 * Author: M91406
 *
 * Description:
 * This source file provides multiple functions to set up and monitor user-
 * defined fault objects as well as routines handling default fault cases.
 * 
 * History:
 * Created on June 22, 2018, 01:14 PM
 ******************************************************************************/

#include "xc.h"
#include <stdint.h>
#include <stddef.h>
#include "_root/generic/fdrv_FaultHandler.h"

/* private function prototypes */
inline volatile uint16_t CheckFaultCondition(volatile FAULT_OBJECT_t* fltobj);
inline volatile uint16_t SetFaultCondition(volatile FAULT_OBJECT_t* fltobj);
inline volatile uint16_t ExecFaultHandler(volatile FAULT_OBJECT_t* fltobj);
inline volatile uint16_t ExecGlobalFaultFlagRelease(volatile uint16_t fault_class_code);
inline volatile uint16_t ExecFaultFlagReleaseHandler(volatile FAULT_OBJECT_t* fltobj);

/*!fault_object_list_pointer
 * ***********************************************************************************************
 * Description:
 * The fault_object_list_pointer variable is used by the exec_FaultCheckSequential() function.
 * Instead of checking all fault objects at once, this routine checks one fault object  
 * declared in fault_object_list[] at a time. After the last item was checked, the 
 * fault_object_list_pointer is automatically reset and starts from fault_object_list[0].
 * ***********************************************************************************************/
volatile uint16_t fault_object_list_pointer = 0;

/*!CheckFaultCondition
 * ***********************************************************************************************
 * Parameters:
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault conditions, fault class, and further user-defined
 *          settings.
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * <b>Description:</b>
 * The fault_object_list_pointer variable is used by the exec_FaultCheckSequential() and 
 * exec_FaultCheckAll() functions. In this function the given fault object fltobj of type
 * FAULT_OBJECT_t is checked for violations of its fault condition criteria. When a fault
 * condition is detected, the fltactive flag bit is set. 
 * IF an active fault condition has been detected, the fault filter using the fault counter
 * and associated min/max counter threshold "trip_cnt_threshold" resp. "release_cnt_threshold" is 
 * applied before the fltstat bit is set/cleared.
 * The fltstat bit indicates a persistent fault condition, which then results in the global
 * application notify, warning or critical flag bit to be set/cleared.
 * ***********************************************************************************************/
inline volatile uint16_t CheckFaultCondition(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t compare_value = 0;
    
    // if the fault object is not initialized, exit here
    if(fltobj->object == NULL) { return(1); }
    
    // derive value to monitor
    compare_value = ((*fltobj->object) & (fltobj->object_bit_mask));
    
    // Check the given fault object on threshold violations
    if(fltobj->criteria.fault_ratio == (FAULT_LEVEL_GREATER_THAN))
    // if the fault level is defined to be greater than a given threshold, 
    // check for upper thresholds violation (including hysteresis when defined)
    {
        
        if(compare_value > fltobj->criteria.trip_level)
        // if the upper threshold is exceeded, set "fault present" flag
        { fltobj->status.flags.fltactive = 1; } // set "fault present" bit
        else if(compare_value < fltobj->criteria.reset_level)
        // if the value is above the upper limit of the hysteresis of the threshold, reset fault flag
        { fltobj->status.flags.fltactive = 0; } // reset "fault present" bit
        else
        // if the value hovers within the hysteresis of the threshold => do nothing
        { Nop(); }
        
    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_LESS_THAN))
    // if the fault level is defined to be less than a given threshold, 
    // check for lower thresholds violation (including hysteresis when defined)
    {
        
        if(compare_value < fltobj->criteria.trip_level)
        // if the lower threshold is exceeded, set "fault present" flag
        { fltobj->status.flags.fltactive = 1; } // set "fault present" bit
        else if(compare_value > fltobj->criteria.reset_level)
        // if the value is above the upper limit of the hysteresis of the threshold, reset fault flag
        { fltobj->status.flags.fltactive = 0; } // reset "fault present" bit
        else
        // if the value hovers within the hysteresis of the threshold => do nothing
        { Nop(); }
        
    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_EQUAL))
    // if the fault level is defined to be at a constant number/value, trigger fault (without hysteresis)
    {
        if(compare_value == fltobj->criteria.trip_level)
        // if the fault value is hit, set the fault flag and increment the fault counter
        { fltobj->status.flags.fltactive = 1; } // set "fault present" bit
        else
        // if not equal, reset the fault flag and fault counter
        { fltobj->status.flags.fltactive = 0; } // reset "fault present" bit

    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_NOT_EQUAL))
    // if the fault level is defined to be "off a constant number/value", trigger fault (without hysteresis)
    {
        if(compare_value != fltobj->criteria.trip_level)
        // if the fault value is off constant, set the fault flag and increment the fault counter
        { fltobj->status.flags.fltactive = 1; } // set "fault present" bit
        else
        // if equal, reset the fault flag and fault counter
        { fltobj->status.flags.fltactive = 0; } // reset "fault present" bit

    }
    else
    { // unknown/unsupported compare condition. => Exit with error code
        Nop();
        return(0);
    }
    
    return(1);

}
    
/*!SetFaultCondition
 * ***********************************************************************************************
 * Parameters:
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault conditions, fault class, and further user-defined
 *          settings.
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine has to follow CheckFaultCondition(FAULT_OBJECT_t* fltobj) checking if a detected
 * fault or fault reset condition leads to a set/clear of the fltstat flag bit after passing
 * through the specified counter filter.
 * ***********************************************************************************************/
inline volatile uint16_t SetFaultCondition(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t fres = 1;
    
    // Depending on if a fault state is active or not, set or reset fault counter
    if (!fltobj->status.flags.fltstat)
    // if there is no active fault state...
    {
        if(fltobj->status.flags.fltactive) 
        // if a fault condition has been detected... 
        { 
            fltobj->criteria.counter++ ; // increment fault counter

            // Check if fault counter limits have been exceeded
            if(fltobj->criteria.counter >= fltobj->criteria.trip_cnt_threshold)
            {
                // Call fault handler passing on the recent fault object
                fltobj->status.flags.fltstat = 1; // set "fault status" bit

                // Set global fault flags and execute appropriate response
                fres &= ExecFaultHandler(fltobj);   

            }

        }
        else
        // without active fault state and no fault condition present, reset fault counter
        { fltobj->criteria.counter = 0 ; } // reset fault counter
    
    }
    
    else
    // if there is an active fault state...
    {
        if(!fltobj->status.flags.fltactive) 
        // if no fault condition has been detected ... 
        { 
            fltobj->criteria.counter++ ; // increment fault reset counter

            // Check if fault reset counter limits have been exceeded
            if(fltobj->criteria.counter >= fltobj->criteria.reset_cnt_threshold)
            {
                // Reset the FAULT STAT flag of the fault object
                fltobj->status.flags.fltstat = 0; // set "fault status" bit
                
            }

        }
        else
        // with an active fault state and a fault condition still present, reset fault reset counter
        { fltobj->criteria.counter = 0 ; } // reset fault reset counter
    
    }
        
    
    return(fres);
}

/*!CheckCPUResetRootCause
 * ***********************************************************************************************
 * Parameters: (none)
 *      
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine analyzes the traplog object and CPU RESET register RCON for the latest events.
 * The register status is triaged in critical, warning and notification-level reset causes.
 * If a critical condition was detected, this functions returns 
 * 
 *     0 = Failure (critical-level reset condition)
 *     1 = Success (notification-level reset condition)
 *     2 = Warning (warning-level reset condition)
 * ***********************************************************************************************/
inline uint16_t CheckCPUResetRootCause(void)
{
    volatile uint16_t fres = 1;
/*
    
    // TODO: return value needs to be properly defined and made accessible and fault handling 
    // routines need to be installed
    
    traplog.rcon_reg.reg_block = RCON; // Copy contents of CPU RESET register into monitoring buffer
    
    if (traplog.rcon_reg.reg_block & FLT_CPU_RESET_CLASS_CRITICAL) {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();   
        
        fres = 0;
    }
    else if (traplog.rcon_reg.reg_block & FLT_CPU_RESET_CLASS_WARNING) {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();    

        fres = 2;
    }
    else {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();    

        fres = 1;
    }
*/
    return(fres);
}

/*!ExecFaultHandler
 * ***********************************************************************************************
 * Parameters: 
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault conditions, fault class, and further user-defined
 *          settings.
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine executes pre-defined standard actions when a fault of FAULT_OBJECT_CLASS_e has 
 * been detected. 
 * 
 *      - FLT_CLASS_CATASTROPHIC:
 *          * the global fault flag will be set
 *          * the scheduler will be set in OP_MODE_FAULT
 *          * the main loop will be ended to enforce a warm CPU restart
 * 
 *      - FLT_CLASS_CRITICAL:
 *          * the global fault flag will be set
 *          * the scheduler will be set in OP_MODE_FAULT
 * 
 *      - FLT_CLASS_WARNING:
 *          * the global warning flag will be set
 * 
 *      - FLT_CLASS_NOTIFY:
 *          * the global notify flag will be set
 * 
 *      - FLT_CLASS_USER_ACTION:
 *          * a user defined function will be called (of form uint16_t xxxx(void) only)
 * 
 * ***********************************************************************************************/
inline volatile uint16_t ExecFaultHandler(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t fres = 0, log_id = 0;
    
    if(fltobj->classes.class & FLT_CLASS_CATASTROPHIC)
    {
        // if fault is of class CATASTROPHIC, force main loop to reset CPU
        task_mgr.status.flags.global_fault = 1; // setting global fault bit
        task_mgr.status.flags.fault_override = true; // setting global fault override bit
        task_mgr.op_mode.mode = OP_MODE_FAULT; // force main scheduler into fault mode
        log_id = fltobj->id; // ToDo: Log the fault object ID in the traps data structure 
        run_scheduler = 0;
        return(1);
    }

    // if fault is of any other class than CATASTROPHIC, perform response. 
    // Multiple responses are supported when the multiple fault classes are specified
    // by ORing multiple FAULT CLASSES into fltobj.classes

    if(fltobj->classes.class & FLT_CLASS_CRITICAL)
    {
        // if fault is of class CRITICAL, set error flag and force scheduler in standby mode
        task_mgr.status.flags.global_fault = 1;  // set global fault bit
        task_mgr.status.flags.fault_override = true; // setting global fault override bit
        task_mgr.op_mode.mode = OP_MODE_FAULT; // force main scheduler into fault mode
    }

    if(fltobj->classes.class & FLT_CLASS_WARNING)
    {
        // if fault is of class CRITICAL, set error flag and force schedule in standby mode
        task_mgr.status.flags.global_warning = 1;   // set global warning bit 
                                                    // and don't take further action
    }

    if(fltobj->classes.class & FLT_CLASS_NOTIFY)
    {
        // if fault is of class CRITICAL, set error flag and force schedule in standby mode
        task_mgr.status.flags.global_notice = 1;  // setting global notify bit
                                                     // and don't take further action
    }

    if(fltobj->classes.class & FLT_CLASS_USER_ACTION)
    {
        // If a user defined fault handler routine has been specified, 
        // call/execute user defined function of type uint16_t xxxx(void) only
        if(fltobj->user_fault_action != NULL)
        { fres = fltobj->user_fault_action(); } // Call/execute user defined function
    }        
        
    return(fres);
}


/*!ExecGlobalFaultFlagRelease
 * ***********************************************************************************************
 * Parameters: 
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault conditions, fault class, and further user-defined
 *          settings.
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine executes pre-defined standard actions when a fault of FAULT_OBJECT_CLASS_e has 
 * been resolved. 
 * 
 *      - FLT_CLASS_CATASTROPHIC: 
 *          * does not apply as a CPU reset is the only response to catastrophic faults
 * 
 *      - FLT_CLASS_CRITICAL:
 *          * the global fault flag will be reset
 *          * the scheduler will be set in OP_MODE_SYSTEM_STARTUP
 * 
 *      - FLT_CLASS_WARNING:
 *          * the global warning flag will be reset
 * 
 *      - FLT_CLASS_NOTIFY:
 *          * the global notify flag will be reset
 * 
 *      - FLT_CLASS_USER_ACTION:
 *          * a user defined function will be called (of form uint16_t xxxx(void) only)
 * 
 * ***********************************************************************************************/
inline volatile uint16_t ExecGlobalFaultFlagRelease(volatile uint16_t fault_class_code)
{
    volatile uint16_t fres = 1;
    
    // if fault is of any other class than CATASTROPHIC, perform recovery from fault condition. 
    // Multiple responses are supported when multiple fault classes are specified by ORing multiple 
    // FAULT CLASSES into fltobj.classes

    if((!(fault_class_code & FLT_CLASS_CRITICAL)) && (task_mgr.status.flags.global_fault))
    {
        // if fault is of class CRITICAL, reset error flag and force scheduler in standby mode
        task_mgr.status.flags.global_fault = 0;  // reset global fault bit
    }

    if((!(fault_class_code & FLT_CLASS_WARNING)) && (task_mgr.status.flags.global_warning))
    {
        // if fault is of class CRITICAL, set error flag and force schedule in standby mode
        task_mgr.status.flags.global_warning = 0;  // set global warning bit 
                                                      // and don't take further action
    }

    if((!(fault_class_code & FLT_CLASS_NOTIFY)) && (task_mgr.status.flags.global_notice))
    {
        // if fault is of class CRITICAL, set error flag and force schedule in standby mode
        task_mgr.status.flags.global_notice = 0;  // setting global notify bit
                                                     // and don't take further action
    }

    return(fres);
}

/*!ExecFaultFlagReleaseHandler
 * ***********************************************************************************************
 * Parameters: 
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault conditions, fault class, and further user-defined
 *          settings.
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine executes pre-defined standard actions when a fault of FAULT_OBJECT_CLASS_e has 
 * been resolved. 
 * 
 *      - FLT_CLASS_USER_ACTION:
 *          * a user defined function will be called (of form uint16_t xxxx(void) only)
 * 
 * ***********************************************************************************************/
inline volatile uint16_t ExecFaultFlagReleaseHandler(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t fres = 1;
    

    if(fltobj->classes.class & FLT_CLASS_USER_ACTION)
    {
        // If a user defined fault release handler routine has been specified, 
        // call/execute user defined function of type volatile uint16_t xxxx(void) only
        if(fltobj->user_fault_reset != NULL)
        { fres &= fltobj->user_fault_reset(); } 

    }        

    return(fres);
}

/*!exec_FaultCheckAll
 * ***********************************************************************************************
 * Parameters: 
 *      (none)
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine checks all fault objects listed in *fault_object_list[] in one execution cycle.
 * any fault action triggered will be executed immediately after every individual fault object 
 * check.
 * ***********************************************************************************************/
uint16_t exec_FaultCheckAll(void)
{
    volatile uint16_t i=0, global_fault_present=0, fres=1;
    
    // Scan through all fault objects for violation of fault conditions
    for (i=0; i<fltobj_list_size; i++)
    {
        // only test objects which have been enabled for fault testing
        if(fault_object_list[i]->status.flags.fltchken)
        {
            fres &= CheckFaultCondition(fault_object_list[i]);  // Check fault condition
            fres &= SetFaultCondition(fault_object_list[i]);    // Set fault flags and execute user fault function

            // track global fault status
            if(fault_object_list[i]->status.flags.fltstat)
            { global_fault_present |= fault_object_list[i]->classes.class; }

        }
    }

    // Reset fault flags if no fault conditions are present
    fres &= ExecGlobalFaultFlagRelease((FAULT_OBJECT_CLASS_e)global_fault_present);
        
    // Set/reset operating mode when global fault flag has been reset 
    if((task_mgr.op_mode.mode == OP_MODE_FAULT) && (!task_mgr.status.flags.global_fault))
    { 
        // when recovering from active fault, check if user recovery functions have to be executed
        for (i=0; i<fltobj_list_size; i++)
        {
            if(fault_object_list[i]->status.flags.fltchken)
            { fres &= ExecFaultFlagReleaseHandler(fault_object_list[i]); }
        }    

        task_mgr.status.flags.fault_override = false;   // Reset global fault override flag
        task_mgr.status.flags.startup_sequence_complete = false; // Reset startup sequence complete flag
        task_mgr.pre_op_mode.mode = OP_MODE_FAULT;  // set pre_op_mode to provoke op-mode switch-over
        task_mgr.op_mode.mode = OP_MODE_SYSTEM_STARTUP; // set op_mode to provoke op-mode switch-over

    } 
        
    return(fres);

}

/*!exec_FaultCheckSequential
 * ***********************************************************************************************
 * Parameters: 
 *      (none)
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine checks one fault object listed in *fault_object_list[] sequentially, one at a time
 * and only one per function call. With every call the fault_object_list_pointer is incremented for
 * the next function call. 
 * Any fault action triggered by any of the fault objects, will be executed immediately after every 
 * individual fault object check.
 * ***********************************************************************************************/
/*
uint16_t exec_FaultCheckSequential(void)
{
    volatile uint16_t fres = 0;
    
    // check next fault object
    fres = CheckFaultCondition(fault_object_list[fault_object_list_pointer]);
    fres = SetFaultCondition(fault_object_list[fault_object_list_pointer]);

    // check fault_object_list_pointer overrun
    if(fault_object_list_pointer++ >= fltobj_list_size) fault_object_list_pointer = 0;
    
    return(fres);

}
*/
/*************************************************************************************************/
