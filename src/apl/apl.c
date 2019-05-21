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
/*!apl.c
 * ****************************************************************************
 * File:   apl.c
 * Author: M91406
 *
 * Created on October 23, 2017, 5:17 PM
 * ****************************************************************************/


#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

#include "apl/tasks/task_FaultHandler.h"

/*!CLOCK_Initialize()
 * ************************************************************************************************
 * Summary:
 * Initializes the oscillator and task scheduler timer
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * Initializes the main oscillator, the auxiliary oscillator and task scheduler timer peripheral.
 * All other, application specific peripheral configurations are executed within the scheduler 
 * where they can be monitored and faults can be detected and handled directly.
 * 
 * Please Note:
 * In case users would like to use MCC to generate code for device peripheral configurations, 
 * the function call CLOCK_Initialize() will directly call the MCC generated code modules instead
 * of the peripheral libraries used in this example.
 * 
 * ***********************************************************************************************/

uint16_t CLOCK_Initialize(void){

    volatile uint16_t fres = 0;
    
    // Initialize main oscillator and auxiliary clock
    //Remove: fres = init_SoftwareWatchDogTimer();
    fres &= init_oscillator();
    fres &= init_aux_oscillator();
   
    // Setup and start Timer1 as base clock for the task scheduler
    fres &= init_system_timer();               // Initialize timer @ 10 kHz
    fres &= launch_system_timer();             // Enable Timer without interrupts

    return(fres);
    
}

/*!OS_Initialize()
 * ************************************************************************************************
 * Summary:
 * Initializes the task scheduler.
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * Initializes the task scheduler and sets it up for the boot phase during which the functional 
 * peripheral blocks will be initialized and the system reaches full functionality.
 * 
 * Please Note:
 * In case users would like to use MCC to generate code for device peripheral configurations, 
 * the function call SYSTEM_initialize() will directly call the MCC generated code modules instead
 * of the peripheral libraries used in this example. 
 * If you use MCC all peripheral modules will be configured by SYSTEM_Initialize(). We recommend,
 * however, to initialize all modules used in a disabled state and use individual tasks to enable
 * functions when they are needed, resp. when their startup timing and execution can be monitored 
 * by the scheduler.
 * 
 * ***********************************************************************************************/

uint16_t OS_Initialize(void) {

    volatile uint16_t fres = 0;

    fres = init_TaskManager();
    fres &= init_FaultObjects();
    
    return(fres);
    
}


/*!APPLICATION_Initialize()
 * ************************************************************************************************
 * Summary:
 * Initializes the application data structure.
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * Initializes the application data structure
 * 
 * Please Note:
 * In case users would like to use MCC to generate code for device peripheral configurations, 
 * the function call SYSTEM_initialize() will directly call the MCC generated code modules instead
 * of the peripheral libraries used in this example. 
 * If you use MCC all peripheral modules will be configured by SYSTEM_Initialize(). We recommend,
 * however, to initialize all modules used in a disabled state and use individual tasks to enable
 * functions when they are needed, resp. when their startup timing and execution can be monitored 
 * by the scheduler.
 * 
 * ***********************************************************************************************/

uint16_t APPLICATION_Initialize(void) {

    volatile uint16_t fres = 0;

    fres = init_ApplicationSettings();
    
    return(fres);
    
}

/*!DEVICE_Reset()
 * ************************************************************************************************
 * Summary:
 * Resets GPIOs and peripheral blocks to a defined default state
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * PICmicro controllers have analog pins set to ANALOG function and all peripherals powered
 * when the device comes out RESET. This may not be desired for many designs. Therefore the
 * GPIOs are reset to DIGITAL function and the power to all peripheral modules is turned off 
 * using the PMDx registers by default.
 * 
 * Please Note:
 * In case users would like to use MCC to generate code for device peripheral configurations, 
 * the function call SYSTEM_initialize() will directly call the MCC generated code modules instead
 * of the peripheral libraries used in this example. As of today, MCC does not cover PMD registers 
 * the function DEVICE_Reset() will cause configurations of peripheral functions of un-powered 
 * peripherals to fail.
 * 
 * ***********************************************************************************************/

uint16_t Device_Reset(void){

    /* this routine can be used to replace the operation mode OP_MODE_BOOT */

    volatile uint16_t fres = 1;
    
    // Device reset
    fres &= gpio_reset();               // Sets all device pins to DIGITAL INPUT, disabling all open-drain and pull-up/-down settings
    fres &= pmd_reset(PMD_POWER_OFF);   // Turns off power and clocks to all peripheral modules offering a PMD control bit
    
    return(fres);
    
}
