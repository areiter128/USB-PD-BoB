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
#include "apl/config/UserFaultObjects.h"

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

// Fault objects of user firmware modules 
volatile FAULT_OBJECT_t fltobj_MyFaultObject;


/*!user_fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile FAULT_OBJECT_t *user_fault_object_list[] = {
    
    // fault objects of firmware modules
    &fltobj_MyFaultObject        // My User Fault Object
    

};
volatile uint16_t user_fltobj_list_size = (sizeof(user_fault_object_list)/sizeof(user_fault_object_list[0]));


/*!User-Defined Fault Objects Initialization
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent user-defined initialization routines of each
 * defined fault object. Every fault object used to monitor values of variables or registers 
 * throughout the firmware needs to be initialized by a separate initialization routine.
 * ***********************************************************************************************/
volatile uint16_t MyFaultObject_Initialize(void);


volatile uint16_t (*user_fault_object_init_functions[])(void) = {
    
    // fault objects for firmware modules and task manager flow
    &MyFaultObject_Initialize,        // The CPU trap handler has detected a critical address error
    
};
volatile uint16_t user_fault_object_init_functions_size = 
    (sizeof(user_fault_object_init_functions)/sizeof(user_fault_object_init_functions[0]));


/*!User Defined Fault Object Configuration
 * ***********************************************************************************************
 * Description:
 * Each user fault object of type FAULT_OBJECT_t listed in the user_fault_object_list[] array needs 
 * to be configured to allow the fault handler to detect and manage related fault conditions of the 
 * given monitored object.
 * 
 * The following function can be used as template of how such a configuration may look like.
 * ***********************************************************************************************/

volatile uint16_t MyFaultObject_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring MyFaultObject

    // specify the target value/register to be monitored
    fltobj_MyFaultObject.source_object = &traplog.status.value; // Pointer to a global variable or SFR
    fltobj_MyFaultObject.object_bit_mask = FAULT_OBJECT_CPU_RESET_TRIGGER_BIT_MASK;
    fltobj_MyFaultObject.error_code = (uint32_t)FLTOBJ_CPU_FAILURE_ERROR;
    fltobj_MyFaultObject.id = (uint16_t)FLTOBJ_CPU_FAILURE_ERROR;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_MyFaultObject.criteria.counter = 0;      // Set/reset fault counter
    fltobj_MyFaultObject.criteria.fault_ratio = FAULT_LEVEL_EQUAL;
    fltobj_MyFaultObject.criteria.trip_level = 1;   // Set/reset trip level value
    fltobj_MyFaultObject.criteria.trip_cnt_threshold = 1; // Set/reset number of successive trips before triggering fault event
    fltobj_MyFaultObject.criteria.reset_level = 0;  // Set/reset fault release level value
    fltobj_MyFaultObject.criteria.reset_cnt_threshold = 1; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_MyFaultObject.flt_class.bits.notify = 1;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_MyFaultObject.flt_class.bits.warning = 0;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_MyFaultObject.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_MyFaultObject.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_MyFaultObject.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_MyFaultObject.user_fault_action = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_MyFaultObject.user_fault_reset = 0; // Set =1 if this fault object triggers a user-defined fault condition response
        
    fltobj_MyFaultObject.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_MyFaultObject.status.bits.fltlvlsw = 1; // Set =1 if this fault condition is software-level fault condition
    fltobj_MyFaultObject.status.bits.fltlvlsi = 1; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_MyFaultObject.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_MyFaultObject.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_MyFaultObject.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_MyFaultObject.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}





