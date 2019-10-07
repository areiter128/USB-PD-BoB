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
/*!task_SystemStatus.c
 * ****************************************************************************
 * File:   task_SystemStatus.c
 * Author: M91406
 *
 * Description:
 * This source file provides multiple functions capturing the most recent 
 * system status determining the required operating mode. The system
 * status includes:
 * 
 *     - Operating from AC adapter (20 DC input)
 *      => Power motherboards from 20V DC input
 *      => Charging available batteries in accordance with charging profile
 *      => dsPIC and peripheral circuits 
 * 
 * Revision history: 
 * 04/18/19     Initial version
 * Author: M91406
 * Comments:
 ******************************************************************************/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "apl/tasks/task_SystemStatus.h"

/* Private function prototypes*/
volatile uint16_t css_GetSystemStatus(void);
volatile uint16_t css_SetSystemMode(void);

/*!task_CaptureSystemStatus
 * ************************************************************************************************
 * Summary:
 * Captures the most recent, application specific state of operation
 *
 * Parameters:
 *	(none)
 * 
 * Returns:
 *   0: failure
 *   1: success
 * 
 * Description:
 * This task is called in every scheduler cycle capturing a set of application dependent signals 
 * of firmware status information to determine the current state of operation. When a change in 
 * operating mode has been detected, the recent operating mode of the task scheduler is changed.
 * Tasks and processes need to respond to this change in state of operation independently from 
 * this function as needed.
 * 
 * Example:
 * The fault handler is continuously monitoring user specific data points. When it detects a
 * critical fault condition, a global, critical fault bit will be set. This fault bit will be 
 * picked up by task_CaptureSystemStatus() of the System Status Monitor, forcing the task 
 * scheduler to switch to the task queue task_queue_fault[]. 
 * 
 * Please note: 
 * In System Status Monitor ONLY (!!!) serves the purpose of controlling the active task manager 
 * task queue. Any other function, like shutting down a peripheral circuit in case of a detected
 * fault condition, needs to be covered by the fault handler directly.
 *  
 * ***********************************************************************************************/

volatile uint16_t exec_CaptureSystemStatus(void) {
    
    volatile uint16_t fres=1;
    
    // System status cannot reliably be detected without running ADC
//    if(!application.ctrl_status.bits.adc_active) 
//    { return(fres); }

    
    fres &= css_GetSystemStatus();
    fres &= css_SetSystemMode();
    
    /* Update time critical items of the MASTER-2-SLAVE interface immediately */
    
    return(fres);
}

/* ************************************************************************************************
 * Capture System Mode and store it in data structure applications.system_mode
 * ************************************************************************************************/

volatile uint16_t css_GetSystemStatus(void) {
    
    volatile SYSTEM_MODE_t sys_mode;
    
    sys_mode.value = 0; // Initialize system mode variable with all bits cleared
    
    /* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
     * Add code identifying the recent operating state and request an op-mode switch
     * when needed.
     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 

//    if ( abc == 0x1234 )
//    { // System is powered from AC adapter (VIN = 19.8V DC / 5A)
//        sys_mode.flags = ( SYSTEM_MODE_NORMAL );  // Set flag for normal mode
//        application.system_status.bits.dummy_bit = (volatile bool)taskDebugLED_config.status.bits.led_status;
//                
//    }



    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // If none of the selections above apply, switch operation into IDLE mode
//    else
//    { 
//        sys_mode.flags = SYSTEM_MODE_IDLE;
//    }


     * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    
    // apply detected system mode
    application.system_mode.value = sys_mode.value;   
    
    return(1);
    
}

/* ************************************************************************************************
 * Set Task Manager Operating Mode
 * ************************************************************************************************/

volatile uint16_t css_SetSystemMode(void) {
    

    /* *************************************************************************************** */
    /* If current operating mode has passed startup and there is no critical fault condition   */
    /* pending, switch operation mode to newly detected system_mode                            */
    /* *************************************************************************************** */

    // Allow switching of operating modes only when the device and system startup procedure has been
    // completed and no fault condition is pending to make sure all peripherals and functions are 
    // available for NORMAL OPERATION modes
    if (task_mgr.status.bits.startup_sequence_complete) 
    {
        // when the fault handler detected a critical fault requiring to shut down the system and
        // hold it in fault recovery mode until the fault flags have been reset, do not allow to 
        // switch operating mode (overrides the detected mode of operation))
        if (task_mgr.status.bits.fault_override)
        { application.system_mode.value = SYSTEM_MODE_FAULT; }
    
        // Set the appropriate task scheduler operating mode depending required for the detected system mode
        if(application.system_mode.value & SYSTEM_MODE_STANDBY)
        { // System sub modules are turned off and MCU is on standby power
            task_mgr.op_mode.value = OP_MODE_STANDBY;
            // add additional application settings
        }
        else if(application.system_mode.value & SYSTEM_MODE_RUN)
        { // System is powered, all sub-modules are on
            task_mgr.op_mode.value = OP_MODE_NORMAL;
            // add additional application settings
        }
        else if(application.system_mode.value & SYSTEM_MODE_FAULT)
        { // System is in fault mode       
            task_mgr.op_mode.value = OP_MODE_FAULT;
            // add additional application settings
        }
        else if(application.system_mode.value == 0)
        { // System is in undefined or idle mode       
            task_mgr.op_mode.value = OP_MODE_IDLE;
            // add additional application settings
        }

    }

    return(1);
    
}