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

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APPLICATION_LAYER_FAULT_HANDLER_H_
#define	_APPLICATION_LAYER_FAULT_HANDLER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "../h/_root/generic/os_Globals.h"

#include "apl/apl.h"
#include "hal/hal.h"


/*!fault_object_index
 * ***********************************************************************************************
 * Description:
 * The enumeration fault_object_index provides a list of friendly labels to access user-defined
 * fault objects in fault_object_list[] more comfortably. Labels also allow fast reordering of the
 * array items without further code edits
 * 
 * Please note:
 * The enumerated indices have to match the fault object indices in
 * fault_object[]. It is therefore vital that the enumeration labels are in the exact same order 
 * as the fault objects listed in fault_object_list[]! 
 * ***********************************************************************************************/

typedef enum {

    FLTOBJ_CPU_FAILURE_ERROR, // The CPU trap handler has detected a critical CPU failure error
    FLTOBJ_CPU_LOAD_OVERRUN, // CPU load counter exceeds task period => not enough bandwidth
    FLTOBJ_TASK_EXECUTION_FAILURE, // Fault object Task Execution Failure
    FLTOBJ_TASK_TIME_QUOTA_VIOLATION, // Fault object Task Time Quota Violation
    FLTOBJ_TASK_MGR_PERIOD_VIOLATION, // Fault object Task Manager Period Violation
    FLTOBJ_OS_COMPONENT_FAILURE, // Fault object Operating System Component Failure
        
//    FLTOBJ_POWER_SOURCE_FAILURE, // Input voltage is out of range preventing DC/DC converters to run
    FLTOBJ_POWER_CONTROL_FAILURE_PORT_A, // A critical fault was detected in DC/DC converter of port A
    FLTOBJ_POWER_CONTROL_FAILURE_PORT_B, // A critical fault was detected in DC/DC converter of port B
//    FLTOBJ_SOFT_START, // Fault object Soft-Start Failure
        
    FLTOBJ_UVLO, // Fault object Under Voltage Lock-Out
    FLTOBJ_OVLO, // Fault object Over Voltage Lock-Out
    FLTOBJ_OVP_USB_PORT_1, // Fault object Output Over Voltage Protection of USB port converter #1
    FLTOBJ_OCP_USB_PORT_1, // Fault object Over Current Protection of USB port converter #1
    FLTOBJ_OTW_USB_PORT_1, // Fault object Over Temperature Warning of USB port converter #1
    FLTOBJ_OTP_USB_PORT_1, // Fault object Over Temperature Protection of USB port converter #1
    FLTOBJ_CTRLERR_USB_PORT_1, // Fault object Regulation Error of USB port converter #1
    FLTOBJ_OVP_USB_PORT_2, // Fault object Output Over Voltage Protection of USB port converter #2
    FLTOBJ_OCP_USB_PORT_2, // Fault object Over Current Protection of USB port converter #2
    FLTOBJ_OTW_USB_PORT_2, // Fault object Over Temperature Warning of USB port converter #2
    FLTOBJ_OTP_USB_PORT_2, // Fault object Over Temperature Protection of USB port converter #2
    FLTOBJ_CTRLERR_USB_PORT_2 // Fault object Regulation Error of USB port converter #2
	
}fault_object_index_e;


typedef enum
{
    ERR_CPU_LOAD_OVERRUN, // CPU load counter exceeds task period => not enough bandwidth
    ERR_TASK_EXECUTION_FAILURE, // Fault object Task Execution Failure
    ERR_TASK_TIME_QUOTA_VIOLATION, // Fault object Task Time Quota Violation

    ERR_UVLO = 0b0000000000001000, // Fault object Under Voltage Lock-Out
    ERR_OVLO = 0b0000000000010000, // Fault object Over Voltage Lock-Out
    ERR_OVP  = 0b0000000000100000, // Fault object Output Over Voltage Protection
    ERR_OCP  = 0b0000000001000000, // Fault object Over Current Protection
    ERR_OTW  = 0b0000000010000000, // Fault object Over Temperature Warning
    ERR_OTP  = 0b0000000100000000  // Fault object Over Temperature Protection
}FAULT_OBJECT_ERROR_CODE_e;


/* PROTOTYPES ALLOWING THE OS TO ACCESS THE USER-DEFINED INITIALIZATION ROUTINES */
extern volatile uint16_t (*user_fault_object_init_functions[])(void);
extern volatile uint16_t user_fault_object_init_functions_size;

/* GLOBAL FAULT OBJECT PROTOTYPES */
extern volatile FAULT_OBJECT_t fltobj_UnderVoltageLockOut;     // Custom UVLO FAULT object
extern volatile FAULT_OBJECT_t fltobj_OverVoltageLockOut;      // Custom OVLO FAULT object 
extern volatile FAULT_OBJECT_t fltobj_OverVoltageProtection_USBPort_1;   // Custom OVP FAULT object USB port #1
extern volatile FAULT_OBJECT_t fltobj_OverCurrentProtection_USBPort_1;   // Custom OCP FAULT object USB port #1  
extern volatile FAULT_OBJECT_t fltobj_OverTempWarning_USBPort_1;   // Custom OVP FAULT object USB port #1
extern volatile FAULT_OBJECT_t fltobj_OverTempProtection_USBPort_1;   // Custom OCP FAULT object USB port #1  
extern volatile FAULT_OBJECT_t fltobj_RegulationError_USBPort_1;    // Custom CTRLERR FAULT object USB port #1
extern volatile FAULT_OBJECT_t fltobj_OverVoltageProtection_USBPort_2;   // Custom OVP FAULT object USB port #2
extern volatile FAULT_OBJECT_t fltobj_OverCurrentProtection_USBPort_2;   // Custom OCP FAULT object USB port #2
extern volatile FAULT_OBJECT_t fltobj_OverTempWarning_USBPort_2;   // Custom OVP FAULT object USB port #2
extern volatile FAULT_OBJECT_t fltobj_OverTempProtection_USBPort_2;   // Custom OCP FAULT object USB port #2
extern volatile FAULT_OBJECT_t fltobj_RegulationError_USBPort_2;    // Custom CTRLERR FAULT object USB port #2
#endif	/* _APPLICATION_LAYER_FAULT_HANDLER_H_ */

