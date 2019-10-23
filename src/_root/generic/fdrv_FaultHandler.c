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
#include <math.h>
#include "_root/generic/os_Globals.h"

/* private function prototypes */
volatile uint16_t CheckFaultCondition(volatile FAULT_OBJECT_t* fltobj);
volatile uint16_t SetFaultCondition(volatile FAULT_OBJECT_t* fltobj);
volatile uint16_t ExecFaultHandler(volatile FAULT_OBJECT_t* fltobj);
volatile uint16_t ExecGlobalFaultFlagRelease(volatile uint16_t fault_class_code);
volatile uint16_t ExecFaultFlagReleaseHandler(volatile FAULT_OBJECT_t* fltobj);

/*!FaultObjects_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile uint16_t os_FaultObjects_Initialize(void)
{
    volatile uint16_t fres = 1;
    volatile uint16_t i = 0;

    // Initialize all fault objects in OS Fault Object list
    for(i=0; i<os_fault_object_init_functions_size; i++) {
        if (os_fault_object_init_functions[i] != NULL) {
            fres &= os_fault_object_init_functions[i]();
        }
    }
    
    for(i=0; i<user_fault_object_init_functions_size; i++) {
        if (user_fault_object_init_functions[i] != NULL) {
            fres &= user_fault_object_init_functions[i]();
        }
    }

    // ====================================================
    // Set global fault flags (need to be cleared during operation)
    task_mgr.status.bits.global_fault = 1;
    task_mgr.status.bits.global_warning = 1;
    task_mgr.status.bits.global_notify = 1;
    // ====================================================
    
    return(fres);
    
}

/*!CheckFaultCondition
 * ***********************************************************************************************
 * Parameters:
 *      FAULT_OBJECT_t* fltobj: Pointer to fault object fltobj of type FAULT_OBJECT_t, holding
 *          all the information about fault criteria, fault class and fault response settings
 * 
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * <b>Description:</b>
 * exec_FaultCheckAll() the given fault object fltobj of type FAULT_OBJECT_t is checked for 
 * violations of its fault condition criteria. When a fault condition is detected, the flt_active 
 * flag bit is set. If the fault flag bit flt_active is set, the fault filter counter is incremented.
 * Once the specified counter maximum threshold "trip_cnt_threshold" is reached/exceeded, the fltstat 
 * bit is set and the specified fault response is tripped. If a fault condition disappears while the 
 * fault filter counter has not reached its maximum threshold, flag bit flt_active will be cleared and 
 * the fault filter counter will reset to zero.
 * 
 * While a certain fault condition is flagged, the fault object is still monitored for fault reset 
 * conditions. Once the fault condition disappears, the fault active flag bit is reset and the 
 * fault filter counter is incremented.  
 * Once the specified counter maximum threshold "release_cnt_threshold" is reached/exceeded, the fltstat 
 * bit is cleared and the specified fault release response is triggered. If a fault condition 
 * reappears while the fault filter counter has not reached its maximum threshold, flag bit flt_active 
 * will be set and the fault filter counter will reset to zero.
 * ***********************************************************************************************/
inline volatile uint16_t CheckFaultCondition(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t source_value = 0;
    volatile uint16_t compare_value = 0;
    volatile int32_t diff_dummy = 0;
    
    // if the fault object is not initialized, exit here
    if(fltobj == NULL) { return(1); }
    
    // read value to monitor (with bit-mask filtering)
    source_value = ((*fltobj->source_object) & (fltobj->object_bit_mask));
    
    // If compare type is 'dynamic', capture compare object value and calculate absolute difference
    // between variable source and variable compare value (a.k.a. source and reference)
    if (fltobj->comp_type == FAULT_COMPARE_DYNAMIC) {
        
        if(fltobj->compare_object != NULL) 
        {
            compare_value = (*fltobj->compare_object); // read value with which the monitored value should be compared with
            diff_dummy = abs(((int32_t)source_value) - ((int32_t)compare_value)); // subtract "source from reference" and make result an absolute number
            source_value = (uint16_t)diff_dummy; // map absolute difference back into source value
        }
        else{ return(0); }  // Return error code if pointer is empty
    }
        
    // Check the given fault object on threshold violations
    if(fltobj->criteria.fault_ratio == (FAULT_LEVEL_GREATER_THAN))
    // if the fault level is defined to be greater than a given threshold, 
    // check for upper thresholds violation (including hysteresis when defined)
    {
        
        if(source_value > fltobj->criteria.trip_level)
        // if the upper threshold is exceeded, set "fault present" flag
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else if(source_value < fltobj->criteria.reset_level)
        // if the value is above the upper limit of the hysteresis of the threshold, reset fault flag
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit
        else
        // if the value hovers within the hysteresis of the threshold => do nothing
        { Nop(); }
        
    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_LESS_THAN))
    // if the fault level is defined to be less than a given threshold, 
    // check for lower thresholds violation (including hysteresis when defined)
    {
        
        if(source_value < fltobj->criteria.trip_level)
        // if the lower threshold is exceeded, set "fault present" flag
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else if(source_value > fltobj->criteria.reset_level)
        // if the value is above the upper limit of the hysteresis of the threshold, reset fault flag
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit
        else
        // if the value hovers within the hysteresis of the threshold => do nothing
        { Nop(); }
        
    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_BOOLEAN))
    // if the fault level is defined to be at a constant number/value, trigger fault (without hysteresis)
    {
        if(((bool)source_value) == ((bool)fltobj->criteria.trip_level))
        // if the fault value is hit, set the fault flag and increment the fault counter
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else
        // if not equal, reset the fault flag and fault counter
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit

    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_EQUAL))
    // if the fault level is defined to be at a constant number/value, trigger fault (without hysteresis)
    {
        if(source_value == fltobj->criteria.trip_level)
        // if the fault value is hit, set the fault flag and increment the fault counter
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else
        // if not equal, reset the fault flag and fault counter
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit

    }
    else if (fltobj->criteria.fault_ratio == (FAULT_LEVEL_NOT_EQUAL))
    // if the fault level is defined to be "off a constant number/value", trigger fault (without hysteresis)
    {
        if(source_value != fltobj->criteria.trip_level)
        // if the fault value is off constant, set the fault flag and increment the fault counter
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else
        // if equal, reset the fault flag and fault counter
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit

    }
    else if(fltobj->criteria.fault_ratio == (FAULT_LEVEL_OUT_OF_RANGE)) 
    // the fault condition is defined to be triggered, when the monitored value is outside a window 
    // defined by the 'trip' and 'reset' fault levels, where 'trip' is the upper and 'reset' is the  
    // lower threshold
    {
        if((source_value > fltobj->criteria.trip_level) || (source_value < fltobj->criteria.reset_level))
        // if the fault value is outside the window, set the fault flag and increment the fault counter
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else
        // if inside the window, reset the fault flag and fault counter
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit
        
    }
    else if(fltobj->criteria.fault_ratio == (FAULT_LEVEL_IN_RANGE)) 
    // the fault condition is defined to be triggered, when the monitored value is inside a window 
    // defined by the 'trip' and 'reset' fault levels, where 'trip' is the upper and 'reset' is the  
    // lower threshold
    {
        if((fltobj->criteria.reset_level < source_value) && (source_value < fltobj->criteria.trip_level))
        // if the fault value is inside the window, set the fault flag and increment the fault counter
        { fltobj->status.bits.fltactive = 1; } // set "fault present" bit
        else
        // if outside the window, reset the fault flag and fault counter
        { fltobj->status.bits.fltactive = 0; } // reset "fault present" bit
        
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
volatile uint16_t SetFaultCondition(volatile FAULT_OBJECT_t* fltobj)
{
    volatile uint16_t f_res = 1;
    
    // if the fault object is not initialized, exit here
    if(fltobj == NULL) { return(1); }

    // Depending on if a fault state is active or not, set or reset fault counter
    if (!fltobj->status.bits.fltstat)
    // if no active FAULT FLAG has been set yet state...
    {
        if(fltobj->status.bits.fltactive) 
        // if a fault condition has been detected... 
        { 
            fltobj->criteria.counter++ ; // increment fault counter

            // Check if fault counter limits have been exceeded
            if(fltobj->criteria.counter >= fltobj->criteria.trip_cnt_threshold)
            {
                // Call fault handler passing on the recent fault object
                fltobj->status.bits.fltstat = 1; // set "fault status" bit

                // Set global fault flags and execute appropriate response
                f_res &= ExecFaultHandler(fltobj);   

            }

        }
        else
        // without active fault state and no fault condition present, reset fault counter
        { fltobj->criteria.counter = 0 ; } // reset fault counter
    
    }
    
    else
    // if there is an active fault state...
    {
        if(!fltobj->status.bits.fltactive) 
        // if no fault condition has been detected ... 
        { 
            fltobj->criteria.counter++ ; // increment fault reset counter

            // Check if fault reset counter limits have been exceeded
            if(fltobj->criteria.counter >= fltobj->criteria.reset_cnt_threshold)
            {
                // Clear the FAULT STAT flag of the fault object
                fltobj->status.bits.fltstat = 0; // clear "fault status" bit
                
                // Execute individual release response
                f_res &= ExecFaultFlagReleaseHandler(fltobj); 

            }

        }
        else
        // with an active fault state and a fault condition still present, reset fault reset counter
        { fltobj->criteria.counter = 0 ; } // reset fault reset counter
    
    }
        
    
    return(f_res);
}

/*!CaptureCPUInterruptStatus
 * ***********************************************************************************************
 * Parameters: (none)
 *      
 * Return:
 *      type: uint16_t
 *      0: Failure
 *      1: Success
 * 
 * Description:
 * This routine captures the most recent status or the registers RCON and INTTREG as
 * well as trap status bits into the persistent data structure of traplog of type TRAP_LOGGER_t.
 * This information will be recover after the next CPU start (given that the device is kept 
 * under power). This allows the software to enter a latched stop condition after a certain 
 * number of restart attempts where unsuccessful.
 * 
 * ***********************************************************************************************/
volatile uint16_t CaptureCPUInterruptStatus(void) 
{
    volatile uint16_t fres = 1;

   // Capture recent interrupt vector and priority status
    traplog.inttreg.value = INTTREG;
    INTTREG = 0x0000; // Reset status flag bits

    // Capture recent status of RESET CONTROL register RCON
    traplog.rcon_reg.value = RCON;
    RCON = 0x0000; // Reset status flag bits
    
    // Capture all available trap flag bits
    traplog.trap_flags.bits.ADDRERR = _ADDRERR;  // Address Error Trap Status bit
    _ADDRERR = 0; // Reset flag bit
    traplog.trap_flags.bits.APLL = _APLL; // Auxiliary PLL Loss of Lock Soft Trap Status bit
    _APLL = 0; // Reset flag bit
    #if defined (_CAN)
    traplog.trap_flags.bits.CAN = _CAN; // CAN Address Error Soft Trap Status bit
    _CAN = 0; // Reset flag bit
    #endif
    #if defined (_CAN2)
    traplog.trap_flags.bits.CAN2 = _CAN2; // CAN2 Address Error Soft Trap Status bit
    _CAN2 = 0; // Reset flag bit
    #endif
    traplog.trap_flags.bits.COVAERR = _COVAERR; // Accumulator A Catastrophic Overflow Trap Flag bit
    _COVAERR = 0; // Reset flag bit
    traplog.trap_flags.bits.COVBERR = _COVBERR; // Accumulator B Catastrophic Overflow Trap Flag bit
    _COVBERR = 0; // Reset flag bit
    traplog.trap_flags.bits.DIV0ERR = _DIV0ERR; // Divide-by-Zero Error Status bit
    _DIV0ERR = 0; // Reset flag bit
    #if defined (_DMACERR)
    traplog.trap_flags.bits.DMACERR = _DMACERR; // DMA Controller Trap Status bit
    _DMACERR = 0; // Reset flag bit
    #endif
    traplog.trap_flags.bits.DOOVR = _DOOVR; // DO Stack Overflow Soft Trap Status bit
    _DOOVR = 0; // Reset flag bit
    #if defined (_ECCDBE)
    traplog.trap_flags.bits.ECCDBE = _ECCDBE; // DO Stack Overflow Soft Trap Status bit
    _ECCDBE = 0; // Reset flag bit
    #endif
    traplog.trap_flags.bits.MATHERR = _MATHERR; // Math Error Status bit
    _MATHERR = 0; // Reset flag bit
    traplog.trap_flags.bits.NAE = _NAE; // NVM Address Error Soft Trap Status bit
    _NAE = 0; // Reset flag bit
    traplog.trap_flags.bits.OSCFAIL = _OSCFAIL; // Oscillator Failure Trap Status bit
    _OSCFAIL = 0; // Reset flag bit
    traplog.trap_flags.bits.OVAERR = _OVAERR; // Accumulator A Overflow Trap Flag bit
    _OVAERR = 0; // Reset flag bit
    traplog.trap_flags.bits.OVBERR = _OVBERR; // Accumulator B Overflow Trap Flag bit
    _OVBERR = 0; // Reset flag bit
    #if defined (_SFTACERR)
    traplog.trap_flags.bits.SFTACERR = _SFTACERR; // Shift Accumulator Error Status bit
    _SFTACERR = 0; // Reset flag bit
    #endif
    traplog.trap_flags.bits.SGHT = _SGHT; // Software Generated Hard Trap Status bit
    _SGHT = 0; // Reset flag bit

    // Check trap flags for conditions triggering a CPU reset
    if(traplog.trap_flags.value & CPU_RESET_TRIGGER_LOW_BIT_MASK) {
    // Set the CPU RESET trigger bit
        traplog.status.bits.cpu_reset_trigger = true;
    }
    else {
    // Clear the CPU RESET trigger bit
        traplog.status.bits.cpu_reset_trigger = false;
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
 * This functions returns 
 * 
 *     3 = (critical-level reset condition)
 *     2 = (warning-level reset condition)
 *     1 = (notification-level reset condition)
 *     0 = unknown condition/function failure
 * 
 * ***********************************************************************************************/
volatile uint16_t CheckCPUResetRootCause(void)
{
    volatile uint16_t fres = 1;

    // TODO: after reset, the RCON ; INTTRE AND trap flag bits need to be checked
    // to determine the root cause of the previous CPU reset. If a software CPU reset
    // was triggered, the number of enforced CPU RESETs need to be limited by the code
    // and the application needs to be brought into a safe condition

    // Check if CPU RESET root cause is different from logged status
    if (traplog.rcon_reg.value != RCON) {
        // TODO: handle condition after restart 
        Nop();
        Nop();
    }
    
    // Check if CPU RESET was tripped by software
    if (traplog.status.bits.sw_reset) {
        // TODO: handle condition after restart 
        Nop();
        Nop();
    }
    
    // Check if previous CPU RESET was cause by critical causes
    if (traplog.rcon_reg.value & FLT_CPU_RESET_CLASS_CRITICAL) {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();   
        
        fres = 3;
    }
    else if (traplog.rcon_reg.value & FLT_CPU_RESET_CLASS_WARNING) {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();    

        fres = 2;
    }
    else if (traplog.rcon_reg.value & FLT_CPU_RESET_CLASS_NORMAL) {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();    

        fres = 1;
    }
    else {
        // TODO: handle exceptions after restart 
        Nop();    
        Nop();    

        fres = 0;
    }

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
    volatile uint16_t f_ret = 1, log_id = 0;
    
    // if the fault object is not initialized, exit here
    if(fltobj == NULL) { return(1); }

    if(fltobj->flt_class.value & FLT_CLASS_CATASTROPHIC)
    {
        // if fault is of class CATASTROPHIC, force main loop to reset CPU
        task_mgr.status.bits.global_fault = 1; // setting global fault bit
        task_mgr.status.bits.fault_override = true; // setting global fault override bit
        task_mgr.op_mode.value = OP_MODE_FAULT; // force main scheduler into fault mode
        log_id = fltobj->id; // ToDo: Log the fault object ID in the traps data structure 
        run_scheduler = false; // Terminate main scheduler, enforcing a warm CPU restart
        return(f_ret); // Return success immediately, don't execute rest of function
    }

    // if fault is of any other class than CATASTROPHIC, perform response. 
    // Multiple responses are supported when the multiple fault classes are specified
    // by ORing multiple FAULT CLASSES into fltobj.classes

    if(fltobj->flt_class.value & FLT_CLASS_CRITICAL)
    {
        // if fault is of class CRITICAL, set error flag and force scheduler in standby mode
        task_mgr.status.bits.global_fault = 1;      // set global fault bit
        task_mgr.status.bits.fault_override = true; // setting global fault override bit
        task_mgr.op_mode.value = OP_MODE_FAULT;       // force main scheduler into fault mode
    }

    if(fltobj->flt_class.value & FLT_CLASS_WARNING)
    {
        // if fault is of class WARNING, set error flag and force schedule in standby mode
        task_mgr.status.bits.global_warning = 1;   // set global warning bit 
                                                    // and don't take further action
    }

    if(fltobj->flt_class.value & FLT_CLASS_NOTIFY)
    {
        // if fault is of class NOTIFY, set error flag and force schedule in standby mode
        task_mgr.status.bits.global_notify = 1;    // setting global notify bit
                                                    // and don't take further action
    }

    if(fltobj->flt_class.value & FLT_CLASS_USER_RESPONSE)
    {
        // If a user defined fault handler routine has been specified, 
        // call/execute user defined function of type uint16_t xxxx(void) only
        if(fltobj->user_fault_action != NULL)
        { f_ret = fltobj->user_fault_action(); } // Call/execute user defined function
    }        
        
    return(f_ret); // return 1=success, 0=failure
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
    
    // if fault is of any other class than CATASTROPHIC, perform recovery from fault condition. 
    // Multiple responses are supported when multiple fault classes are specified by ORing multiple 
    // FAULT CLASSES into fltobj.classes

    if((!(fault_class_code & FLT_CLASS_CRITICAL)) && (task_mgr.status.bits.global_fault))
    {
        // if fault is of class CRITICAL, reset error flag and force scheduler in standby mode
        task_mgr.status.bits.global_fault = 0;  // clear global fault bit
        task_mgr.status.bits.fault_override = false; // clear global fault override bit
        if(task_mgr.status.bits.startup_sequence_complete)
        { task_mgr.op_mode.value = OP_MODE_IDLE; }      // force main scheduler into IDLE mode
    }

    if((!(fault_class_code & FLT_CLASS_WARNING)) && (task_mgr.status.bits.global_warning))
    {
        // if fault is of class WARNING, set error flag and force scheduler in standby mode
        task_mgr.status.bits.global_warning = 0;   // set global warning bit 
                                                    // and don't take further action
    }

    if((!(fault_class_code & FLT_CLASS_NOTIFY)) && (task_mgr.status.bits.global_notify))
    {
        // if fault is of class NOTIFY, set error flag and force scheduler in standby mode
        task_mgr.status.bits.global_notify = 0;    // setting global notify bit
                                                    // and don't take further action
    }

    return(1);
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

    // if the fault object is not initialized, exit here
    if(fltobj == NULL) { return(1); }

    if(fltobj->flt_class.value & FLT_CLASS_USER_RESPONSE)
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
volatile uint16_t exec_FaultCheckAll(void)
{
    volatile uint16_t i=0, global_fault_present=0, fres=1;
    
    // First scan through all operating system fault objects for violation of fault conditions
    for (i=0; i<os_fltobj_list_size; i++)
    {
        // only test objects which have been enabled for fault testing
        if (os_fault_object_list[i] != NULL) {
        if (os_fault_object_list[i]->status.bits.fltchken)
        {
            fres &= CheckFaultCondition(os_fault_object_list[i]);  // Check fault condition
            fres &= SetFaultCondition(os_fault_object_list[i]);    // Set fault flags and execute user fault function

            // track global fault status
            if(os_fault_object_list[i]->status.bits.fltstat)
            { global_fault_present |= os_fault_object_list[i]->flt_class.value; }

        }}
    }
    
    
    // Scan through all user-defined fault objects for violation of fault conditions
    for (i=0; i<user_fltobj_list_size; i++)
    {
        // only test objects which have been enabled for fault testing
        if (user_fault_object_list[i] != NULL) {
        if (user_fault_object_list[i]->status.bits.fltchken)
        {
            fres &= CheckFaultCondition(user_fault_object_list[i]);  // Check fault condition
            fres &= SetFaultCondition(user_fault_object_list[i]);    // Set fault flags and execute user fault response
            
            // track global fault status
            if(user_fault_object_list[i]->status.bits.fltstat)
            { global_fault_present |= user_fault_object_list[i]->flt_class.value; }

        }}
    }

    // =============================================================================
    // Clear global fault flags if no fault conditions are present
    
    fres &= ExecGlobalFaultFlagRelease((FAULT_OBJECT_CLASS_e)global_fault_present);
        

    
    return(fres);

}

