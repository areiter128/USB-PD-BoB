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
/*!UserAppManager.c
 *****************************************************************************
 * File:   UserAppManager.c
 *
 * Summary:
 * User code modules required to manage the APPLICATION_SETTINGS_t data structure 
 *
 * Description:	
 * Most applications require a certain set of high-level information to set basic 
 * parameters for internal functions and status information. These parameters are
 * consolidated in the APPLICATION_SETTINGS_t data structure, which is 100% user 
 * defined.
 *
 * The following routines are used to initialize or reset the APPLICATION_SETTINGS_t
 * data structure. Users can add and/or modify these code modules to tailor the 
 * APPLICATION_SETTINGS_t items to application specific requirements.
 * 
 * References:
 * -
 *
 * See also:
 * 
 * Revision history: 
 * 04/10/19     Initial version
 * Author: M91406
 * Comments:
 *****************************************************************************/


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "apl/config/UserAppManager.h"

// Defining the global APPLICATION object "application" of type APPLICATION_SETTINGS_t
volatile APPLICATION_t application; // global APPLICATION object holding settings, status and error code information


/*!APPLICATION_Initialize
 *****************************************************************************
 * Summary:
 * User code initializing the APPLICATION_t data structure
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 *
 * Description:	
 * The following routine will be called automatically after the device reset and before 
 * the OS is executing the task scheduler. Any settings, which need to be in place before
 * other tasks are executed, can be set here.
 * 
 * References:
 * -
 *
 * See also:
 * 
 * Revision history: 
 * 04/10/19     Initial version
 * Author: M91406
 * Comments:
 *****************************************************************************/

volatile uint16_t APPLICATION_Initialize(void) {
    
    volatile uint16_t fres = 1;
    
    /* Initialization of system status flags */
    application.system_status.value = 0;
    application.system_mode.bits = SYSTEM_MODE_RUN;
    
    /* Reset of system tasks and settings */
    
    // ToDo: 
    //  Add function calls initializing user task state machines
    //  during boot phase

    return(fres);
}

/*!APPLICATION_Reset.c
 *****************************************************************************
 * Summary:
 * User code resetting the entire system into a safe, passive condition
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 *
 * Description:	
 * The following routine will be called automatically when a catastrophic 
 * fault condition has been detected and the system has to be brought into
 * a safe and passive state. After this routine has been executed the CPU 
 * may or may not be reset.
 * 
 * Please add all application-wide function calls terminating tasks which 
 * could potentially drive board functions causing issues when executed
 * by an unreliable CPU/memory or corrupted firmware modules.
 * 
 * References:
 * -
 *
 * See also:
 * 
 * Revision history: 
 * 04/10/19     Initial version
 * Author: M91406
 * Comments:
 *****************************************************************************/

volatile uint16_t APPLICATION_Reset(void) {
    
    volatile uint16_t fres = 1;
    
    /* Reset of system tasks and settings */
    application.system_status.value = 0;
    application.system_mode.bits = SYSTEM_MODE_IDLE;
    

    // ToDo: Add function calls resetting user task state machines
    
    return(fres);
}

/*!CaptureSystemStatus
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
 * and/or firmware status information to determine the current state of operation. When a change in 
 * operating mode has been detected, the recent operating mode of the task scheduler is changed.
 * Tasks and processes need to respond to this change in state of operation independently from 
 * this function as needed.
 * 
 * Example:
 * The fault handler is continuously monitoring user specific data points. When it detects a
 * critical fault condition, a global, critical fault bit will be set. This fault bit will be 
 * picked up by CaptureSystemStatus() of the System Status Monitor, forcing the task 
 * scheduler to switch to the task queue task_queue_fault[]. 
 * 
 * Please note: 
 * In System Status Monitor ONLY (!!!) serves the purpose of controlling the active task manager 
 * task queue. Any other function, like shutting down a peripheral circuit in case of a detected
 * fault condition, needs to be covered by the fault handler user function directly.
 *  
 * ***********************************************************************************************/


volatile uint16_t APPLICATION_CaptureSystemStatus(void) {
    
    volatile uint16_t fres=1;
    
    /* ToDo: Add your application wide operating mode conditions here 

     * Example:
     * 
     * if ( my_value = 0x1234)
     * {
     *      task_mgr.op_mode.value = OP_MODE_IDLE;
     * }
     * 
    
     * **************************************************************/
    
    return(fres);
}