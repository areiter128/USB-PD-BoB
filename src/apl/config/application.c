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
/*!ApplicationSettings.c
 *****************************************************************************
 * File:   ApplicationSettings.c
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

#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

// Defining the global APPLICATION object "application" of type APPLICATION_SETTINGS_t
volatile APPLICATION_t application; // global APPLICATION object holding settings, status and error code information

// Private prototypes
//Remove: volatile uint16_t initialize_main_loop(void);


/*!init_ApplicationSettings.c
 *****************************************************************************
 * Summary:
 * User code initializing the APPLICATION_SETTINGS_t data structure
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
 * other tasks are executed can be set here.
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

volatile uint16_t init_ApplicationSettings(void) {
    
    /* Initialization of system status flags */
    application.system_status.flags.dummy_bit = STAT_BIT_DUMMY_1;
    

    return(1);
}

