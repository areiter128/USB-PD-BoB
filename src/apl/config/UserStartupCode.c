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
/*!UserStartupCode.c
 *****************************************************************************
 * File:   UserStartupCode.c
 *
 * Summary:
 * Highly application and hardware specific user startup-code extension
 *
 * Description:	
 * Some designs require immediate actions after device reset like fast recovery
 * after power brown-out or to set a state of a certain, external peripheral circuit
 * such as an auxiliary power supply, before any other function can be enabled.
 * 
 * This code module will be called right after the DEVICE_Reset function call and only
 * if the user option EXECUTE_USER_STARTUP_CODE in the header file apl.h is set to 1 
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

#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

volatile uint16_t ExecuteUserStartupCode(void) {

    /*!ExecuteUserStartupCode() 
     * *********************************************************************************
     * When the task manager setting EXECUTE_USER_STARTUP_CODE is set to 1, this
     * function will be called right after the device is coming out of RESET and
     * the function DEVOCE_Reset has been executed.
     * 
     * PLEASE NOTE:
     * ============
     * This special feature of the task scheduler should only be used when critical,
     * low-level procedures need to be performed when the system gets powered up.
     * If no special action needs to be taken at startup, it's recommended to 
     * disable this feature by setting (EXECUTE_USER_STARTUP_CODE = 0). 
     * 
     * All conventional startup code should be incorporated into the task scheduler 
     * task queues.
     * *********************************************************************************/
    
    return(1);
}
