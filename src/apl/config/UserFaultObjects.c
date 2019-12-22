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

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

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
volatile FAULT_OBJECT_t fltobj_UnderVoltageLockOut;     // Custom FAULT object UVLO shutting down the power supply 
                                                        // when input voltage drops below minimum
volatile FAULT_OBJECT_t fltobj_OverVoltageLockOut;      // Custom FAULT object OVLO shutting down the power supply 
                                                        // when input voltage goes above maximum
volatile FAULT_OBJECT_t fltobj_OverVoltageProtection_USBPort_1; // Custom FAULT object OVP shutting down the power supply 
																// when output voltage goes above maximum
volatile FAULT_OBJECT_t fltobj_OverCurrentProtection_USBPort_1; // Custom FAULT object OCP settings a WARNING flag bit
                                                                // when output current goes into limitation
volatile FAULT_OBJECT_t fltobj_OverTempWarning_USBPort_1;       // Custom FAULT object OTW shutting down the power supply 
																// when output voltage goes above maximum
volatile FAULT_OBJECT_t fltobj_OverTempProtection_USBPort_1;    // Custom FAULT object OTP shutting down the power supply 
																// when output current goes above maximum
volatile FAULT_OBJECT_t fltobj_RegulationError_USBPort_1;       // Custom FAULT object CTRLERR shutting down the power supply 
                                                                // when output voltage is significantly off voltage reference
volatile FAULT_OBJECT_t fltobj_OverVoltageProtection_USBPort_2; // Custom FAULT object OVP shutting down the power supply 
																// when output voltage goes above maximum
volatile FAULT_OBJECT_t fltobj_OverCurrentProtection_USBPort_2; // Custom FAULT object OCP settings a WARNING flag bit
                                                                // when output current goes into limitation
volatile FAULT_OBJECT_t fltobj_OverTempWarning_USBPort_2;       // Custom FAULT object OTW settings a WARNING flag bit
                                                                // when output current goes above warning threshold
volatile FAULT_OBJECT_t fltobj_OverTempProtection_USBPort_2;    // Custom FAULT object OTP shutting down the power supply 
																// when output current goes above maximum
volatile FAULT_OBJECT_t fltobj_RegulationError_USBPort_2;       // Custom FAULT object CTRLERR shutting down the power supply 
                                                                // when output voltage is significantly off voltage reference

/*!user_fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

volatile FAULT_OBJECT_t *user_fault_object_list[] = {
    
    // fault objects of firmware modules
    &fltobj_UnderVoltageLockOut,        // UVLO fault object    
    &fltobj_OverVoltageLockOut,         // OVLO fault object
    &fltobj_OverVoltageProtection_USBPort_1,    // OVP fault object
    &fltobj_OverCurrentProtection_USBPort_1,    // OCP fault object
    &fltobj_OverTempWarning_USBPort_1,          // OTW fault object
    &fltobj_OverTempProtection_USBPort_1,       // OTP fault object
    &fltobj_RegulationError_USBPort_1,          // CTRLERR fault object
    &fltobj_OverVoltageProtection_USBPort_2,    // OVP fault object
    &fltobj_OverCurrentProtection_USBPort_2,    // OCP fault object
    &fltobj_OverTempWarning_USBPort_2,          // OTW fault object
    &fltobj_OverTempProtection_USBPort_2,       // OTP fault object
    &fltobj_RegulationError_USBPort_2           // CTRLERR fault object
};
volatile uint16_t user_fltobj_list_size = (sizeof(user_fault_object_list)/sizeof(user_fault_object_list[0]));


/*!User-Defined Fault Objects Initialization
 * ***********************************************************************************************
 * Description:
 * The following prototype declarations represent user-defined initialization routines of each
 * defined fault object. Every fault object used to monitor values of variables or registers 
 * throughout the firmware needs to be initialized by a separate initialization routine.
 * ***********************************************************************************************/
volatile uint16_t flt_UnderVoltageLockOut_Initialize(void);
volatile uint16_t flt_OverVoltageLockOut_Initialize(void);

volatile uint16_t flt_OverVoltageProtection_USBPort_1_Initialize(void);
volatile uint16_t flt_OverCurrentProtection_USBPort_1_Initialize(void);
volatile uint16_t flt_OverTempWarning_USBPort_1_Initialize(void);
volatile uint16_t flt_OverTempProtection_USBPort_1_Initialize(void);
volatile uint16_t flt_RegulationError_USBPort_1_Initialize(void);

volatile uint16_t flt_OverVoltageProtection_USBPort_2_Initialize(void);
volatile uint16_t flt_OverCurrentProtection_USBPort_2_Initialize(void);
volatile uint16_t flt_OverTempWarning_USBPort_2_Initialize(void);
volatile uint16_t flt_OverTempProtection_USBPort_2_Initialize(void);
volatile uint16_t flt_RegulationError_USBPort_2_Initialize(void);


volatile uint16_t (*user_fault_object_init_functions[])(void) = {
    
    // fault objects for firmware modules and task manager flow
    &flt_UnderVoltageLockOut_Initialize,    // 'Input Voltage below Minimum' fault object
    &flt_OverVoltageLockOut_Initialize,     // 'Input Voltage above Maximum' fault object
    &flt_OverVoltageProtection_USBPort_1_Initialize,  // 'Output Voltage above Maximum' fault object 
    &flt_OverCurrentProtection_USBPort_1_Initialize,   // 'Output Current above Maximum' fault object
    &flt_OverTempWarning_USBPort_1_Initialize,   // 'Temperature above Warning Level' fault object
    &flt_OverTempProtection_USBPort_1_Initialize,   // 'Temperature above Protection Level' fault object
    &flt_RegulationError_USBPort_1_Initialize, // 'Regulation out of Range' fault object
    &flt_OverVoltageProtection_USBPort_2_Initialize,  // 'Output Voltage above Maximum' fault object 
    &flt_OverCurrentProtection_USBPort_2_Initialize,   // 'Output Current above Maximum' fault object
    &flt_OverTempWarning_USBPort_2_Initialize,   // 'Temperature above Warning Level' fault object
    &flt_OverTempProtection_USBPort_2_Initialize   // 'Temperature above Protection Level' fault object
    
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

/*!flt_UnderVoltageLockOut_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the input voltage, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the input voltage drops below the declared minimum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_UnderVoltageLockOut_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_UnderVoltageLockOut
    fltobj_UnderVoltageLockOut.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_UnderVoltageLockOut.source_object = &c4swbb_1.data.v_in; // Pointer to a global variable or SFR
    fltobj_UnderVoltageLockOut.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_UnderVoltageLockOut.error_code = (uint32_t)FLTOBJ_UVLO;
    fltobj_UnderVoltageLockOut.id = (uint16_t)FLTOBJ_UVLO;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_UnderVoltageLockOut.criteria.counter = 0;      // Set/reset fault counter
    fltobj_UnderVoltageLockOut.criteria.fault_ratio = FAULT_LEVEL_LESS_THAN;
    fltobj_UnderVoltageLockOut.criteria.trip_level = VIN_UVLO_TRIP;   // Set/reset trip level value
    fltobj_UnderVoltageLockOut.criteria.trip_cnt_threshold = 10; // Set/reset number of successive trips before triggering fault event
    fltobj_UnderVoltageLockOut.criteria.reset_level = VIN_UVLO_RELEASE;  // Set/reset fault release level value
    fltobj_UnderVoltageLockOut.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_UnderVoltageLockOut.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_UnderVoltageLockOut.flt_class.bits.warning = 0;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_UnderVoltageLockOut.flt_class.bits.critical = 1; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_UnderVoltageLockOut.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_UnderVoltageLockOut.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_UnderVoltageLockOut.user_fault_action = &reset_PowerControl; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_UnderVoltageLockOut.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released
        
    fltobj_UnderVoltageLockOut.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_UnderVoltageLockOut.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_UnderVoltageLockOut.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_UnderVoltageLockOut.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_UnderVoltageLockOut.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_UnderVoltageLockOut.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_UnderVoltageLockOut.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverVoltageLockOut_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the input voltage, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the input voltage goes above the declared maximum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_OverVoltageLockOut_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageLockOut
    fltobj_OverVoltageLockOut.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverVoltageLockOut.source_object = &c4swbb_1.data.v_in; // Pointer to a global variable or SFR
    fltobj_OverVoltageLockOut.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverVoltageLockOut.error_code = (uint32_t)FLTOBJ_OVLO;
    fltobj_OverVoltageLockOut.id = (uint16_t)FLTOBJ_OVLO;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverVoltageLockOut.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverVoltageLockOut.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverVoltageLockOut.criteria.trip_level = VIN_OVLO_TRIP;   // Set/reset trip level value
    fltobj_OverVoltageLockOut.criteria.trip_cnt_threshold = 10; // Set/reset number of successive trips before triggering fault event
    fltobj_OverVoltageLockOut.criteria.reset_level = VIN_OVLO_RELEASE;  // Set/reset fault release level value
    fltobj_OverVoltageLockOut.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverVoltageLockOut.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverVoltageLockOut.flt_class.bits.warning = 0;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverVoltageLockOut.flt_class.bits.critical = 1; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverVoltageLockOut.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverVoltageLockOut.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverVoltageLockOut.user_fault_action = &reset_PowerControl; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverVoltageLockOut.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverVoltageLockOut.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverVoltageLockOut.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverVoltageLockOut.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverVoltageLockOut.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverVoltageLockOut.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageLockOut.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageLockOut.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverVoltageProtection_USBPort_1_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output voltage, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the output voltage goes above the declared maximum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_OverVoltageProtection_USBPort_1_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverVoltageProtection_USBPort_1.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverVoltageProtection_USBPort_1.source_object = &c4swbb_1.data.v_out; // Pointer to a global variable or SFR
    fltobj_OverVoltageProtection_USBPort_1.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverVoltageProtection_USBPort_1.error_code = (uint32_t)FLTOBJ_OVP_USB_PORT_1;
    fltobj_OverVoltageProtection_USBPort_1.id = (uint16_t)FLTOBJ_OVP_USB_PORT_1;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverVoltageProtection_USBPort_1.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverVoltageProtection_USBPort_1.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverVoltageProtection_USBPort_1.criteria.trip_level = VOUT_OVP_TRIP;   // Set/reset trip level value
    fltobj_OverVoltageProtection_USBPort_1.criteria.trip_cnt_threshold = 5; // Set/reset number of successive trips before triggering fault event
    fltobj_OverVoltageProtection_USBPort_1.criteria.reset_level = VOUT_OVP_RELEASE;  // Set/reset fault release level value
    fltobj_OverVoltageProtection_USBPort_1.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverVoltageProtection_USBPort_1.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverVoltageProtection_USBPort_1.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverVoltageProtection_USBPort_1.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverVoltageProtection_USBPort_1.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverVoltageProtection_USBPort_1.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverVoltageProtection_USBPort_1.user_fault_action = &reset_USBPort_1; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverVoltageProtection_USBPort_1.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageProtection_USBPort_1.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverCurrentProtection_USBPort_1_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output current, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the output current goes above the declared maximum, the fault 
 * counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'warning' which will not swap the operating system
 * in FAULT mode, nor shut down the power supply. The output will be kept in current limit
 * mode by the control loop. 
 * ***********************************************************************************************/

volatile uint16_t flt_OverCurrentProtection_USBPort_1_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverCurrentProtection_USBPort_1.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverCurrentProtection_USBPort_1.source_object = &c4swbb_1.data.i_out; // Pointer to a global variable or SFR
    fltobj_OverCurrentProtection_USBPort_1.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverCurrentProtection_USBPort_1.error_code = (uint32_t)FLTOBJ_OCP_USB_PORT_1;
    fltobj_OverCurrentProtection_USBPort_1.id = (uint16_t)FLTOBJ_OCP_USB_PORT_1;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverCurrentProtection_USBPort_1.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverCurrentProtection_USBPort_1.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverCurrentProtection_USBPort_1.criteria.trip_level = (IOUT_OCL_TRIP + C4SWBB_IOUT_FEEDBACK_OFFSET);   // Set/reset trip level value
    fltobj_OverCurrentProtection_USBPort_1.criteria.trip_cnt_threshold = 5; // Set/reset number of successive trips before triggering fault event
    fltobj_OverCurrentProtection_USBPort_1.criteria.reset_level = (IOUT_OCL_RELEASE + C4SWBB_IOUT_FEEDBACK_OFFSET);  // Set/reset fault release level value
    fltobj_OverCurrentProtection_USBPort_1.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverCurrentProtection_USBPort_1.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverCurrentProtection_USBPort_1.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverCurrentProtection_USBPort_1.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverCurrentProtection_USBPort_1.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverCurrentProtection_USBPort_1.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverCurrentProtection_USBPort_1.user_fault_action = &reset_USBPort_1; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverCurrentProtection_USBPort_1.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverCurrentProtection_USBPort_1.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverTempWarning_USBPort_1_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the board temperature, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the temperature goes above the declared maximum, the fault 
 * counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'warning' which will not swap the operating system
 * in FAULT mode, nor shut down the power supply. 
 * ***********************************************************************************************/

volatile uint16_t flt_OverTempWarning_USBPort_1_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverTempWarning_USBPort_1.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverTempWarning_USBPort_1.source_object = &c4swbb_1.data.temp; // Pointer to a global variable or SFR
    fltobj_OverTempWarning_USBPort_1.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverTempWarning_USBPort_1.error_code = (uint32_t)FLTOBJ_OTW_USB_PORT_1;
    fltobj_OverTempWarning_USBPort_1.id = (uint16_t)FLTOBJ_OTW_USB_PORT_1;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverTempWarning_USBPort_1.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverTempWarning_USBPort_1.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverTempWarning_USBPort_1.criteria.trip_level = TEMP_OTW_TRIP;   // Set/reset trip level value
    fltobj_OverTempWarning_USBPort_1.criteria.trip_cnt_threshold = 50000; // Set/reset number of successive trips before triggering fault event
    fltobj_OverTempWarning_USBPort_1.criteria.reset_level = TEMP_OTW_RELEASE;  // Set/reset fault release level value
    fltobj_OverTempWarning_USBPort_1.criteria.reset_cnt_threshold = 50000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverTempWarning_USBPort_1.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverTempWarning_USBPort_1.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverTempWarning_USBPort_1.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverTempWarning_USBPort_1.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverTempWarning_USBPort_1.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverTempWarning_USBPort_1.user_fault_action = 0; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverTempWarning_USBPort_1.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverTempWarning_USBPort_1.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverTempWarning_USBPort_1.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverTempWarning_USBPort_1.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverTempWarning_USBPort_1.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverTempWarning_USBPort_1.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverTempWarning_USBPort_1.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverTempWarning_USBPort_1.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverTempProtection_USBPort_1_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the board temperature, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the temperature goes above the declared maximum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_OverTempProtection_USBPort_1_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverTempProtection_USBPort_1.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverTempProtection_USBPort_1.source_object = &c4swbb_1.data.temp; // Pointer to a global variable or SFR
    fltobj_OverTempProtection_USBPort_1.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverTempProtection_USBPort_1.error_code = (uint32_t)FLTOBJ_OTW_USB_PORT_1;
    fltobj_OverTempProtection_USBPort_1.id = (uint16_t)FLTOBJ_OTW_USB_PORT_1;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverTempProtection_USBPort_1.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverTempProtection_USBPort_1.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverTempProtection_USBPort_1.criteria.trip_level = TEMP_OTP_TRIP;   // Set/reset trip level value
    fltobj_OverTempProtection_USBPort_1.criteria.trip_cnt_threshold = 50000; // Set/reset number of successive trips before triggering fault event
    fltobj_OverTempProtection_USBPort_1.criteria.reset_level = TEMP_OTP_RELEASE;  // Set/reset fault release level value
    fltobj_OverTempProtection_USBPort_1.criteria.reset_cnt_threshold = 50000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverTempProtection_USBPort_1.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverTempProtection_USBPort_1.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverTempProtection_USBPort_1.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverTempProtection_USBPort_1.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverTempProtection_USBPort_1.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverTempProtection_USBPort_1.user_fault_action = &reset_USBPort_1; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverTempProtection_USBPort_1.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverTempProtection_USBPort_1.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverTempProtection_USBPort_1.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverTempProtection_USBPort_1.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverTempProtection_USBPort_1.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverTempProtection_USBPort_1.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverTempProtection_USBPort_1.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverTempProtection_USBPort_1.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}

/*!flt_RegulationError_USBPort_1_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output current, which gets updated by the control
 * loop in every control cycle. Its value is compared against the most recent voltage reference
 * by using a tolerance bit-mask. As soon as the output voltage diverts too much from the reference, 
 * the fault counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_RegulationError_USBPort_1_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_RegulationError_USBPort_1.comp_type = FAULT_COMPARE_DYNAMIC;

    // specify the target value/register to be monitored
    fltobj_RegulationError_USBPort_1.source_object = &c4swbb_1.data.v_out; // Pointer to global variable or SFR
    fltobj_RegulationError_USBPort_1.compare_object = &c4swbb_1.data.v_ref; // pointer to global variable or SFR
    fltobj_RegulationError_USBPort_1.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT; //
    fltobj_RegulationError_USBPort_1.error_code = (uint32_t)FLTOBJ_CTRLERR_USB_PORT_1;
    fltobj_RegulationError_USBPort_1.id = (uint16_t)FLTOBJ_CTRLERR_USB_PORT_1;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_RegulationError_USBPort_1.criteria.counter = 0;      // Set/reset fault counter
    fltobj_RegulationError_USBPort_1.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_RegulationError_USBPort_1.criteria.trip_level = VOUT_MAX_DEV;   // Set/reset trip level value
    fltobj_RegulationError_USBPort_1.criteria.trip_cnt_threshold = 10000; // Set/reset number of successive trips before triggering fault event
    fltobj_RegulationError_USBPort_1.criteria.reset_level = VOUT_MAX_DEV;  // Set/reset fault release level value
    fltobj_RegulationError_USBPort_1.criteria.reset_cnt_threshold = 10; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_RegulationError_USBPort_1.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_RegulationError_USBPort_1.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_RegulationError_USBPort_1.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_RegulationError_USBPort_1.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_RegulationError_USBPort_1.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_RegulationError_USBPort_1.user_fault_action = &reset_USBPort_1; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_RegulationError_USBPort_1.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_RegulationError_USBPort_1.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_RegulationError_USBPort_1.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_RegulationError_USBPort_1.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_RegulationError_USBPort_1.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_RegulationError_USBPort_1.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_RegulationError_USBPort_1.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_RegulationError_USBPort_1.status.bits.fltchken = 0; // Enable/disable fault check
    
    return(fres);
    
}



/*!flt_OverVoltageProtection_USBPort_2_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output voltage, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the output voltage goes above the declared maximum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_OverVoltageProtection_USBPort_2_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverVoltageProtection_USBPort_2.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverVoltageProtection_USBPort_2.source_object = &c4swbb_2.data.v_out; // Pointer to a global variable or SFR
    fltobj_OverVoltageProtection_USBPort_2.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverVoltageProtection_USBPort_2.error_code = (uint32_t)FLTOBJ_OVP_USB_PORT_2;
    fltobj_OverVoltageProtection_USBPort_2.id = (uint16_t)FLTOBJ_OVP_USB_PORT_2;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverVoltageProtection_USBPort_2.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverVoltageProtection_USBPort_2.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverVoltageProtection_USBPort_2.criteria.trip_level = VOUT_OVP_TRIP;   // Set/reset trip level value
    fltobj_OverVoltageProtection_USBPort_2.criteria.trip_cnt_threshold = 5; // Set/reset number of successive trips before triggering fault event
    fltobj_OverVoltageProtection_USBPort_2.criteria.reset_level = VOUT_OVP_RELEASE;  // Set/reset fault release level value
    fltobj_OverVoltageProtection_USBPort_2.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverVoltageProtection_USBPort_2.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverVoltageProtection_USBPort_2.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverVoltageProtection_USBPort_2.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverVoltageProtection_USBPort_2.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverVoltageProtection_USBPort_2.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverVoltageProtection_USBPort_2.user_fault_action = &reset_USBPort_2; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverVoltageProtection_USBPort_2.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverVoltageProtection_USBPort_2.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverCurrentProtection_USBPort_2_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output current, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the output current goes above the declared maximum, the fault 
 * counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'warning' which will not swap the operating system
 * in FAULT mode, nor shut down the power supply. The output will be kept in current limit
 * mode by the control loop. 
 * ***********************************************************************************************/

volatile uint16_t flt_OverCurrentProtection_USBPort_2_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverCurrentProtection_USBPort_2.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverCurrentProtection_USBPort_2.source_object = &c4swbb_2.data.i_out; // Pointer to a global variable or SFR
    fltobj_OverCurrentProtection_USBPort_2.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverCurrentProtection_USBPort_2.error_code = (uint32_t)FLTOBJ_OCP_USB_PORT_2;
    fltobj_OverCurrentProtection_USBPort_2.id = (uint16_t)FLTOBJ_OCP_USB_PORT_2;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverCurrentProtection_USBPort_2.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverCurrentProtection_USBPort_2.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverCurrentProtection_USBPort_2.criteria.trip_level = (IOUT_OCL_TRIP + C4SWBB_IOUT_FEEDBACK_OFFSET);   // Set/reset trip level value
    fltobj_OverCurrentProtection_USBPort_2.criteria.trip_cnt_threshold = 5; // Set/reset number of successive trips before triggering fault event
    fltobj_OverCurrentProtection_USBPort_2.criteria.reset_level = (IOUT_OCL_RELEASE + C4SWBB_IOUT_FEEDBACK_OFFSET);  // Set/reset fault release level value
    fltobj_OverCurrentProtection_USBPort_2.criteria.reset_cnt_threshold = 1000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverCurrentProtection_USBPort_2.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverCurrentProtection_USBPort_2.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverCurrentProtection_USBPort_2.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverCurrentProtection_USBPort_2.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverCurrentProtection_USBPort_2.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverCurrentProtection_USBPort_2.user_fault_action = &reset_USBPort_2; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverCurrentProtection_USBPort_2.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverCurrentProtection_USBPort_2.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverTempWarning_USBPort_2_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the board temperature, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the temperature goes above the declared maximum, the fault 
 * counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'warning' which will not swap the operating system
 * in FAULT mode, nor shut down the power supply. 
 * ***********************************************************************************************/

volatile uint16_t flt_OverTempWarning_USBPort_2_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverTempWarning_USBPort_2.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverTempWarning_USBPort_2.source_object = &c4swbb_2.data.temp; // Pointer to a global variable or SFR
    fltobj_OverTempWarning_USBPort_2.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverTempWarning_USBPort_2.error_code = (uint32_t)FLTOBJ_OTW_USB_PORT_2;
    fltobj_OverTempWarning_USBPort_2.id = (uint16_t)FLTOBJ_OTW_USB_PORT_2;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverTempWarning_USBPort_2.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverTempWarning_USBPort_2.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverTempWarning_USBPort_2.criteria.trip_level = TEMP_OTW_TRIP;   // Set/reset trip level value
    fltobj_OverTempWarning_USBPort_2.criteria.trip_cnt_threshold = 50000; // Set/reset number of successive trips before triggering fault event
    fltobj_OverTempWarning_USBPort_2.criteria.reset_level = TEMP_OTW_RELEASE;  // Set/reset fault release level value
    fltobj_OverTempWarning_USBPort_2.criteria.reset_cnt_threshold = 50000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverTempWarning_USBPort_2.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverTempWarning_USBPort_2.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverTempWarning_USBPort_2.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverTempWarning_USBPort_2.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverTempWarning_USBPort_2.flt_class.bits.user_class = 0; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverTempWarning_USBPort_2.user_fault_action = 0; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverTempWarning_USBPort_2.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverTempWarning_USBPort_2.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverTempWarning_USBPort_2.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverTempWarning_USBPort_2.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverTempWarning_USBPort_2.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverTempWarning_USBPort_2.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverTempWarning_USBPort_2.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverTempWarning_USBPort_2.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}


/*!flt_OverTempProtection_USBPort_2_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the board temperature, which gets updated by the control
 * loop in every control cycle. Its value is compared against a user defined limit declared in
 * syscfg_limits.h. As soon as the temperature goes above the declared maximum, the fault 
 * counter starts incrementing. When the the counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a user defined function is called.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_OverTempProtection_USBPort_2_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_OverTempProtection_USBPort_2.comp_type = FAULT_COMPARE_CONSTANT;

    // specify the target value/register to be monitored
    fltobj_OverTempProtection_USBPort_2.source_object = &c4swbb_2.data.temp; // Pointer to a global variable or SFR
    fltobj_OverTempProtection_USBPort_2.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT;
    fltobj_OverTempProtection_USBPort_2.error_code = (uint32_t)FLTOBJ_OTW_USB_PORT_2;
    fltobj_OverTempProtection_USBPort_2.id = (uint16_t)FLTOBJ_OTW_USB_PORT_2;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_OverTempProtection_USBPort_2.criteria.counter = 0;      // Set/reset fault counter
    fltobj_OverTempProtection_USBPort_2.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_OverTempProtection_USBPort_2.criteria.trip_level = TEMP_OTP_TRIP;   // Set/reset trip level value
    fltobj_OverTempProtection_USBPort_2.criteria.trip_cnt_threshold = 50000; // Set/reset number of successive trips before triggering fault event
    fltobj_OverTempProtection_USBPort_2.criteria.reset_level = TEMP_OTP_RELEASE;  // Set/reset fault release level value
    fltobj_OverTempProtection_USBPort_2.criteria.reset_cnt_threshold = 50000; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_OverTempProtection_USBPort_2.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_OverTempProtection_USBPort_2.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_OverTempProtection_USBPort_2.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_OverTempProtection_USBPort_2.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_OverTempProtection_USBPort_2.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_OverTempProtection_USBPort_2.user_fault_action = &reset_USBPort_2; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_OverTempProtection_USBPort_2.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_OverTempProtection_USBPort_2.status.bits.fltlvlhw = 1; // Set =1 if this fault condition is board-level fault condition
    fltobj_OverTempProtection_USBPort_2.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_OverTempProtection_USBPort_2.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_OverTempProtection_USBPort_2.status.bits.fltlvlsys = 0; // Set =1 if this fault condition is system-level fault condition

    fltobj_OverTempProtection_USBPort_2.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_OverTempProtection_USBPort_2.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_OverTempProtection_USBPort_2.status.bits.fltchken = 1; // Enable/disable fault check
    
    return(fres);
    
}

/*!flt_RegulationError_USBPort_2_Initialize
 * ***********************************************************************************************
 * Description:
 * The fault handler continuously monitors the output current, which gets updated by the control
 * loop in every control cycle. Its value is compared against the most recent voltage reference
 * by using a tolerance bit-mask. As soon as the output voltage diverts too much from the reference, 
 * the fault counter starts incrementing. When this counter exceeds the maximum value defined by 
 * 'trip_cnt_threshold' in this initialization routine, a warning flag is set.
 * 
 * This fault is declared as 'critical' which will automatically swap the operating system
 * in FAULT mode, switching the most recent task queue from its recent origin to 
 * 'task_queue_fault'
 * ***********************************************************************************************/

volatile uint16_t flt_RegulationError_USBPort_2_Initialize(void)
{
    volatile uint16_t fres = 1;

    // Configuring fltobj_OverVoltageProjection
    fltobj_RegulationError_USBPort_2.comp_type = FAULT_COMPARE_DYNAMIC;

    // specify the target value/register to be monitored
    fltobj_RegulationError_USBPort_2.source_object = &c4swbb_2.data.v_out; // Pointer to global variable or SFR
    fltobj_RegulationError_USBPort_2.compare_object = &c4swbb_2.data.v_ref; // pointer to global variable or SFR
    fltobj_RegulationError_USBPort_2.object_bit_mask = FAULT_OBJECT_BIT_MASK_DEFAULT; //
    fltobj_RegulationError_USBPort_2.error_code = (uint32_t)FLTOBJ_CTRLERR_USB_PORT_2;
    fltobj_RegulationError_USBPort_2.id = (uint16_t)FLTOBJ_CTRLERR_USB_PORT_2;
    
    // configuring the trip and reset levels as well as trip and reset event filter setting
    fltobj_RegulationError_USBPort_2.criteria.counter = 0;      // Set/reset fault counter
    fltobj_RegulationError_USBPort_2.criteria.fault_ratio = FAULT_LEVEL_GREATER_THAN;
    fltobj_RegulationError_USBPort_2.criteria.trip_level = VOUT_MAX_DEV;   // Set/reset trip level value
    fltobj_RegulationError_USBPort_2.criteria.trip_cnt_threshold = 10000; // Set/reset number of successive trips before triggering fault event
    fltobj_RegulationError_USBPort_2.criteria.reset_level = VOUT_MAX_DEV;  // Set/reset fault release level value
    fltobj_RegulationError_USBPort_2.criteria.reset_cnt_threshold = 10; // Set/reset number of successive resets before triggering fault release
    
    // specifying fault class, fault level and enable/disable status
    fltobj_RegulationError_USBPort_2.flt_class.bits.notify = 0;   // Set =1 if this fault object triggers a fault condition notification
    fltobj_RegulationError_USBPort_2.flt_class.bits.warning = 1;  // Set =1 if this fault object triggers a warning fault condition response
    fltobj_RegulationError_USBPort_2.flt_class.bits.critical = 0; // Set =1 if this fault object triggers a critical fault condition response
    fltobj_RegulationError_USBPort_2.flt_class.bits.catastrophic = 0; // Set =1 if this fault object triggers a catastrophic fault condition response

    fltobj_RegulationError_USBPort_2.flt_class.bits.user_class = 1; // Set =1 if this fault object triggers a user-defined fault condition response
    fltobj_RegulationError_USBPort_2.user_fault_action = &reset_USBPort_2; // Set pointer to user function which should be called when the FAULT is tripped
    fltobj_RegulationError_USBPort_2.user_fault_reset = 0; // Set pointer to user function which should be called when the FAULT is released

    fltobj_RegulationError_USBPort_2.status.bits.fltlvlhw = 0; // Set =1 if this fault condition is board-level fault condition
    fltobj_RegulationError_USBPort_2.status.bits.fltlvlsw = 0; // Set =1 if this fault condition is software-level fault condition
    fltobj_RegulationError_USBPort_2.status.bits.fltlvlsi = 0; // Set =1 if this fault condition is silicon-level fault condition
    fltobj_RegulationError_USBPort_2.status.bits.fltlvlsys = 1; // Set =1 if this fault condition is system-level fault condition

    fltobj_RegulationError_USBPort_2.status.bits.fltstat = 1; // Set/reset fault condition as present/active
    fltobj_RegulationError_USBPort_2.status.bits.fltactive = 1; // Set/reset fault condition as present/active
    fltobj_RegulationError_USBPort_2.status.bits.fltchken = 0; // Enable/disable fault check
    
    return(fres);
    
}



