/*
 * File:   os_Initialize.c
 * Author: M91406
 *
 * Created on October 9, 2019, 10:03 PM
 */


#include <xc.h>
#include "_root/generic/os_Globals.h"

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

volatile uint16_t OS_Initialize(void) {

    volatile uint16_t fres = 1;

    fres &= os_TaskManager_Initialize();
    fres &= os_FaultObjects_Initialize();

    return(fres);
    
}

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

volatile uint16_t CLOCK_Initialize(void){

    volatile uint16_t fres = 1;
    
    // Initialize main oscillator and auxiliary clock
    //Remove: fres = init_SoftwareWatchDogTimer();
    fres &= MainOscillator_Initialize(); // Initialize main oscillator
    fres &= AuxOscillator_Initialize(); // Initialize auxiliary clock for PWM and ADC
    fres &= smpsOSC_GetFrequencies(0);     // Update clock settings of global system_frequencies object
   
    // Setup and start Timer1 as base clock for the task scheduler
    fres &= OSTimer_Initialize(); // Initialize timer @ configured task tick frequency
    fres &= OSTimer_Start();      // Enable Timer without interrupts

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
volatile uint16_t DEVICE_Initialize(void) {

    /* this routine can be used to replace the operation mode OP_MODE_BOOT */

    volatile uint16_t fres = 1;
    
    // Device CPU/DSP, Interrupt Controller and user-defined GPIO initialization
    fres &= DSP_initialize();   // Initializes the DSP with settings defined in mcal/config/devcfg_dsp.h
    fres &= IRQ_initialize();   // Initializes the Interrupt Controller with settings defined in mcal/config/devcfg_irq.h
    fres &= GPIO_initialize();  // Initializes the device GPIOs with settings defined in mcal/config/devcfg_gpio.h
    
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
#if (EXECUTE_MCC_SYSTEM_INITIALIZE == 0)
volatile uint16_t DEVICE_Reset(void){

    /* this routine can be used to replace the operation mode OP_MODE_BOOT */

    volatile uint16_t fres = 1;
    
    // Device reset
    fres &= smpsGPIO_Initialize();               // Sets all device pins to DIGITAL INPUT, disabling all open-drain and pull-up/-down settings
    fres &= smpsPMD_SetPowerStateAll(PMD_POWER_OFF);  // Turns off power and clocks to all peripheral modules offering a PMD control bit
    
    return(fres);
    
}
#endif
