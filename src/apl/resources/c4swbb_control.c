/*
 * File:   soft_start.c
 * Author: M91406
 *
 * Created on October 16, 2018, 1:07 PM
 */


#include <xc.h>
#include "mcal/mcal.h"                      // Microcontroller Abstraction Layer Header

#include "apl/resources/c4swbb_control.h"   // 4-Switch Buck/Boost Converter State Machine Header

/* === private state machine counter variables ===================================================== */
// (none)

// Declare two 4-Switch Buck/Boost DC/DC converter objects
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_1;    // USB PD Port A
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_2;    // USB PD Port B


volatile uint16_t ctrl_Init(volatile cNPNZ16b_t* controller);
volatile uint16_t ctrl_Reset(volatile cNPNZ16b_t* controller);
volatile uint16_t ctrl_Precharge(
        volatile cNPNZ16b_t* controller, // Pointer to nPnZ data structure)
        volatile uint16_t ctrl_input, // user-defined, constant error history value
        volatile uint16_t ctrl_output // user-defined, constant control output history value
    );


/*!exec_4SWBB_PowerController()
 * *****************************************************************************************************
 * Summary:
 * Executes the 4-Switch Buck Boost Power Controller state machine
 *
 * Parameters: 
 * C4SWBB_POWER_CONTROLLER_t* pInstance     Instance of a 4-SW BB DC/DC converter object
 *
 * Description:
 * This routine executes the state machine, driving a 4-switch buck boost controller. This engine is 
 * completely self-sufficient in terms of tracking the converter progress during start up, shut down,
 * standby, fault or under normal operating conditions. 
 * 
 * At startup, the power controller initializes the required peripherals and basic power controller
 * state machine data structure including its voltage and current loop controllers. Once everything
 * is set up, the state machine drops into standby mode, waiting for being enabled.
 * 
 * *****************************************************************************************************/

volatile uint16_t exec_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1; // buffer variable of function return value
    volatile float fdummy = 0.0; // buffer variable for control loop pre-charge calculation
    volatile uint16_t int_dummy = 0; // buffer variable for control loop pre-charge calculation
    
    
    switch (pInstance->status.flags.op_status) {

        /* @@CONVERTER_STATE_INITIALIZE
         * ============================
         * In this step the startup procedure and control loops are reset. The soft-start ramp
         * is defined by a power on delay, pre-charge delay, ramp-up period and power good delay. 
         * The internal counters for each of these phases are reset. Then the controller reference
         * is hijacked and reset to zero. 
         * In the next function call the state machine step CONVERTER_STATE_STANDBY will be 
         * executed. */
        
        case CONVERTER_STATE_INITIALIZE:
            
            
            // Switch to operation status CONVERTER_STATE_STANDBY
            pInstance->status.flags.op_status = CONVERTER_STATE_STANDBY;

            break;

        /* @@CONVERTER_STATE_STANDBY
         * ============================
         * In this step the power controller is waiting for being enabled. No action will be taken
         * until c4swbb.status.flags.enable = true and c4swbb.status.flags.GO = 1. The AUTORUN option
         * (c4swbb.status.flags.autorun = true) will automatically enable the power controller 
         * and set the GO bit to bypass this step of the state machine */
            
        case CONVERTER_STATE_STANDBY:

            if( (pInstance->status.flags.enabled) && (pInstance->status.flags.GO) && 
                (!pInstance->status.flags.fault_active)) {
                
                    pInstance->soft_start.counter = 0;  // Reset soft-start counter
                    pInstance->status.flags.op_status = CONVERTER_STATE_POWER_ON_DELAY; // switch to state POWER_ON_DELAY
            
            }            
            break;
            
        /* @@CONVERTER_STATE_POWER_ON_DELAY
         * ================================
         * During the POWER ON DELAY the power controller waits until the programmed delay 
         * period has expired. Neither control loop nor power converter are active.
         * Once this delay period has expired the state machine will switch to 
         * CONVERTER_STATE_LAUNCH_V_RAMP  */
            
        case CONVERTER_STATE_POWER_ON_DELAY:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;
            
            // delay startup until POWER ON DELAY has expired
            if(pInstance->soft_start.counter++ > pInstance->soft_start.pwr_on_delay) {

                pInstance->soft_start.counter = 0;  // Reset soft-start counter
                pInstance->status.flags.op_status = CONVERTER_STATE_LAUNCH_V_RAMP; // switch to soft-start phase LAUNCH_V_RAMP
                
            }
                
            break;

        /* @@CONVERTER_STATE_PRECHARGE
         * ===========================
         * In this step the soft-start procedure continues with performing the manual pre-charge 
         * process which produces ~120ns wide pulses on the low side PWM signal pre-charging the 
         * half-bridge bootstrap cap. When this phase has expired, the execution step will be 
         * switched to SOFT_START_STEP_LAUNCH_V_RAMP */
        case CONVERTER_STATE_PRECHARGE:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;

//            // generate n bootstrap pre-charge pulses before enabling switch node
//            if(pchrg_couter++ < SOFT_START_PRECHARGE_TICKS)
//            { 
//                // manually generated pulse on low-side switch
//                // pre-charging the bootstrap capacitor
//                BUCKL1_WR = 1;
//                SOFT_START_PCRG_PULSE_DUTY;
//                BUCKL1_WR = 0;
//            }
//            else
//            {
//                // switch to soft-start phase LAUNCH RAMP UP
//                hspwm_reset_gpio_low_side(BUCKH1_PGx_CHANNEL);
//                ss_shadow.step = SOFT_START_STEP_LAUNCH_V_RAMP; 
//            }
            
            break;

        /* @@CONVERTER_STATE_LAUNCH_V_RAMP
         * ================================
         * In this step the ramp up starting point is determined by measuring the input and output 
         * voltage and calculates the ideal duty ratio of the PWM. This value is then programmed into
         * the PWM module duty cycle register and is also used to pre-charge the control loop output
         * history. In addition the measured output voltage also set as reference to ensure the loop 
         * starts without jerks and jumps.
         * When voltage mode control is enabled, the voltage loop control history is charged, 
         * when average current mode control is enabled, the current loop control history is charged.
         *  */
        case CONVERTER_STATE_LAUNCH_V_RAMP:

 /*           // Hijack voltage loop controller reference
            pInstance->soft_start.v_reference = 0; // Reset Soft-Start Voltage Reference
            pInstance->soft_start.i_reference = 0; // Reset Soft-Start Current Reference
            
            // Voltage loop reference is hijacked by the soft-start reference
            pInstance->v_loop.controller->ptrControlReference = &pInstance->soft_start.v_reference;
*/            
            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;
            
            // Determine, if the soft-start needs to ramp up or down
            if(pInstance->data.v_out <= pInstance->data.v_ref) {
                pInstance->status.flags.tune_dir = CONVERTER_RAMP_DIR_UP;
            }
            else {
                pInstance->status.flags.tune_dir = CONVERTER_RAMP_DIR_DOWN;
            }
            
            // Set starting point of the soft-start reference to most recent output voltage level
            pInstance->soft_start.v_reference = pInstance->data.v_out;
            
            // In average current mode, set current reference limit to max startup current level
            #if (C4SWBB_CONTROL_MODE == C4SWBB_ACMC)
            // === ToDo: =========
            // Check if this section is required. Removing it is desired as it breaks the 
            // generic nature of this code module by incorporating dedicated HAL labels!!!
//            pInstance->v_loop.maximum = (volatile uint16_t)IOUT_OCL_TRIP;
//            pInstance->v_loop.controller->MaxOutput = pInstance->v_loop.maximum;
            // === ToDoEnd =======
            #endif
            
            // Pre-charge PWM and control loop history
            fdummy = (float)(pInstance->data.v_out) / (float)(pInstance->data.v_in << 1);
            int_dummy = (uint16_t)(fdummy * (float)pInstance->buck_leg.period);
            
            #if (C4SWBB_CONTROL_MODE == C4SWBB_VMC)
            
            // In voltage mode control the PWM duty cycle is determined by the 
            // voltage loop controller. Thus, the voltage loop control history
            // needs to be pre-charged to prevent turn-on glitches.
            
            if(int_dummy < pInstance->v_loop.minimum) 
            { int_dummy = pInstance->v_loop.minimum; }
            else if(int_dummy > pInstance->v_loop.maximum) 
            { int_dummy = pInstance->v_loop.maximum; }
            
            // Call pre-charge routine, loading user values into control histories
            pInstance->v_loop.ctrl_precharge(pInstance->v_loop.controller, 0, int_dummy);

            #elif (C4SWBB_CONTROL_MODE == C4SWBB_ACMC)

            // In average current mode control the PWM duty cycle is determined by the 
            // inner current loop controller. Thus, the current loop control history
            // needs to be pre-charged to prevent turn-on glitches.
            
            if(int_dummy < pInstance->i_loop.minimum) 
            { int_dummy = pInstance->i_loop.minimum; }
            else if(int_dummy > pInstance->i_loop.maximum) 
            { int_dummy = pInstance->i_loop.maximum; }

            ctrl_Precharge(pInstance->i_loop.controller, 0, int_dummy);
            
            #endif            

            // set initial PWM duty ratio
            hspwm_set_duty_cycle(pInstance->buck_leg.pwm_instance, int_dummy);
            
            // ToDo: Add boost leg duty ratio pre-charge 
            
            // switch to soft-start phase RAMP UP
            pInstance->status.flags.op_status = CONVERTER_STATE_V_RAMP_UP;
            
            break;
            
        /* @@CONVERTER_STATE_V_RAMP_UP
         * ===========================
         * This is the essential step in which the output voltage is ramped up by incrementing the 
         * outer control loop reference. In voltage mode the output voltage will ramp up to the 
         * nominal regulation point. 
         * In average current mode the inner loop will limit the voltage as soon as the current 
         * reference limit is hit and the output is switched to constant current mode. */
        case CONVERTER_STATE_V_RAMP_UP:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;

            // Enable input power source
            hspwm_ovr_release(pInstance->buck_leg.pwm_instance); // Release buck leg PWM
            hspwm_ovr_release(pInstance->boost_leg.pwm_instance); // Release boost leg PWM

//            // enable control loop
//            #if (BATA_CONTROL_MODE == VMC)
//            cvmc_bata.status.flag.enable = 1; // enable voltage loop controller
//            #elif (BATA_CONTROL_MODE == ACMC)
//            cvmc_bata.status.flag.enable = 1; // enable voltage loop controller
//            cacmc_bata.status.flag.enable = 1; // enable current loop controller
//            #endif
//
//            // increment reference
//            ss_shadow.v_reference += SOFT_START_V_REF_STEP_SIZE;
//
//            // check if ramp is complete
//            if (ss_shadow.v_reference >= application.bata_v_loop.reference) 
//            {
//                ss_shadow.v_reference = application.bata_v_loop.reference;
//                cvmc_bata.status.flag.enable = 0;
//                cvmc_bata.ptrControlReference = &application.bata_v_loop.reference;
//                cvmc_bata.status.flag.enable = 1;
//                #if (BATA_CONTROL_MODE == VMC)
//                ss_shadow.step = SOFT_START_WAIT_FOR_PWRGOOD;
//                #elif (BATA_CONTROL_MODE == ACMC)
//                ss_shadow.step = SOFT_START_STEP_I_RAMP_UP;
//                #endif
//            }
            break;

        /*!CONVERTER_STATE_I_RAMP_UP
         * =========================
         * !!! THIS SOFT-START STEP IS FOR BATTERY CHARGERS ONLY !!!
         * 
         * During this phase of the soft-start, the maximum current loop reference is incremented
         * to the nominal level. depending on the output current settings, this may enforce different
         * behavior of the power supply. 
         * 
         * a) The outer voltage loop is in clamping mode
         *    When the voltage loop controller has been ramped up to the point, where the maximum 
         *    control output (= reference for the inner current loop) hits the maximum limit,
         *    the voltage loop becomes ineffective while clamped to its maximum control output 
         *    value. In this condition the converter output is only controlled by the inner current 
         *    loop and operates as pure constant current source.
         *    
         *    Under these conditions this part of the soft-start will produce a visible and adjustable
         *    current soft-start ramp, starting from the initial voltage loop limit to the nominal
         *    current limit.
         * 
         * b) The outer voltage loop is operating
         *    In case the output voltage loop was able to drive the converter output voltage up to 
         *    nominal operating level without hitting an output clamping limit, this part of the 
         *    soft-start will still increment the current limit to its nominal level, but won't 
         *    show visible effect at the converter output (neither voltage nor current)
         * 
         *  */
        case CONVERTER_STATE_I_RAMP_UP:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;

            // increment current limit 
            pInstance->v_loop.controller->MaxOutput += pInstance->soft_start.ramp_i_ref_increment; // Increment maximum current limit

            // check if ramp is complete
            if (pInstance->v_loop.controller->MaxOutput >= (volatile uint16_t)pInstance->i_loop.reference) 
            {
                pInstance->v_loop.maximum = (volatile uint16_t)pInstance->i_loop.reference;
                pInstance->v_loop.controller->MaxOutput = pInstance->v_loop.maximum;
                pInstance->status.flags.op_status = CONVERTER_STATE_POWER_GOOD;
            }

            break;

        /* @@CONVERTER_STATE_POWER_GOOD
         * =============================
         * In this phase of the soft-start procedure the power supply should have reached nominal 
         * level, providing a stable, constant output voltage. A counter is incremented until the 
         * power good delay has expired before the soft-start process is marked as 
         * CONVERTER_STATE_COMPLETE */
        case CONVERTER_STATE_POWER_GOOD:
            
            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 1;
            
            // Enforce POWER GOOD Delay
            if(pInstance->soft_start.counter++ > pInstance->soft_start.pwr_good_delay) {
                pInstance->status.flags.op_status = CONVERTER_STATE_COMPLETE;  // set startup process COMPLETE
                pInstance->soft_start.counter = 0;  // reset startup counter
            }
            Nop();
            break;
            
        /*!CONVERTER_STATE_COMPLETE
         * =============================
         * When the soft-start step is set to CONVERTER_STATE_COMPLETE, the state machine 
         * will not be executed any further and the converter has entered normal operation.  
         * From this point forward the power supply will exclusively be running in interrupt 
         * instances executing the control loops. */
        case CONVERTER_STATE_COMPLETE:

            // Clear the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = 0;

            // Monitor changes in reference and step back into RAMP mode when necessary
            if(pInstance->data.v_ref != pInstance->soft_start.v_reference)
            {
                // Set the BUSY bit indicating a delay/ramp period being executed
                pInstance->status.flags.busy = 1;
                
                if(pInstance->data.v_ref < pInstance->soft_start.v_reference){
                    // decrement
                    pInstance->soft_start.v_reference -= pInstance->soft_start.ramp_v_ref_increment;
                    if(pInstance->soft_start.v_reference < pInstance->data.v_ref) {
                        pInstance->soft_start.v_reference = pInstance->data.v_ref;
                    }
                        
                }
                else if(pInstance->data.v_ref > pInstance->soft_start.v_reference) {
                   // increment
                    pInstance->soft_start.v_reference += pInstance->soft_start.ramp_v_ref_increment;
                    if(pInstance->soft_start.v_reference > pInstance->data.v_ref){
                        pInstance->soft_start.v_reference = pInstance->data.v_ref;
                    }
                }
                
            }
            else{
                pInstance->status.flags.busy = 0;

            }
            
            break;

        /*!State Machine Fall-Back 
         * ========================
         * When this soft-start step is executed, something went wrong in the master state machine
         * or a fault condition was set by external code modules. In any of these cases the state 
         * machine falls back to STANDBY waiting to be restarted.  */
        default:
            
            pInstance->status.flags.busy = 0; // Clear the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.fault_active = true;
            pInstance->status.flags.GO = false;
            pInstance->status.flags.op_status = CONVERTER_STATE_STANDBY;
            
            break;
    }

    //----------------------------------------------------------
    /*!Power Converter Autorun Function
     * When the control bit c4swbb.status.flags.auto_start is set, the status bits 'enabled' 
     * and 'GO' are automatically set and continuously enforced to ensure the power supply
     * will enter RAMP UP from STANDBY without the need for user code intervention. */
    // 
    if( (pInstance->status.flags.autorun == true) && (pInstance->status.flags.fault_active == false)) {
        pInstance->status.flags.enabled = true;  // Auto-run power converter
        pInstance->status.flags.GO = true;       // Auto-Kick-off power converter
    }
    else { 
        pInstance->status.flags.GO = false; // Always Auto-Clear GO bit
    }
    //-- end of auto-start enforcement -------------------------

    return(fres);
}

/*!init_SoftStart()
 * *****************************************************************************************************
 * Summary:
 * Initializes the soft start state machine
 *
 * Parameters: 
 * (none)
 *
 * Description:
 * This routine sets the default values of the soft-start engine considering the power supply is 
 * started up for the first time (clean startup).
 * 
 * *****************************************************************************************************/

volatile uint16_t init_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

//    // Reset Startup Settings
//    pInstance->soft_start.pwr_good_delay = CONVERTER_STATE_INITIALIZE; // reset state machine
//    pInstance->soft_start.counter = 0; // reset startup counter
//    pInstance->soft_start.v_reference = 0;  // reset voltage reference
//    pInstance->soft_start.i_reference = 0;  // reset current reference
//    pInstance->soft_start.pwr_on_delay = C4SWBB_PODLY;  // set power-on delay
//    pInstance->soft_start.precharge_delay = 10;  // set pre-charge delay
//    pInstance->soft_start.ramp_period = C4SWBB_RPER;  // set ramp up period
//    pInstance->soft_start.pwr_good_delay = C4SWBB_PGDLY;  // set power good delay
//
//    
//    // Reset data buffers
//    pInstance->data.v_in = 0;   // clear input voltage buffer
//    pInstance->data.v_out = 0;  // reset output voltage buffer
//    pInstance->data.i_out = 0;  // reset output current buffer
//    pInstance->data.v_ref = C4SWBB_VOUT_REF;  // set initial voltage reference
//    pInstance->data.temp = 0;   // reset converter board temperature buffer
//    
//    // Reset controller status
//    pInstance->status.flags.power_source_detected = false; // reset POWER_SOURCE_DETECTED flag bit
//    pInstance->status.flags.adc_active = false; // reset ADC_ACTIVE flag bit
//    pInstance->status.flags.pwm_active = false; // reset PWM_ACTIVE flag bit
//    pInstance->status.flags.tune_dir = 0; // reset voltage tune-in direction to UP
//    pInstance->status.flags.fault_active = false; // reset power controller global fault flag bit
//    pInstance->status.flags.GO = 0; // reset GO bit
//    pInstance->status.flags.autorun = false; // clear AUTORUN bit
//    pInstance->status.flags.enabled = false; // disable power controller
//    pInstance->status.flags.op_status = CONVERTER_STATE_INITIALIZE; // reset state machine
//    
    
    return(1);
}


/*!ctrl_Init
 * *****************************************************************************************************
 * Summary:
 * Initializes a nPnZ control structure
 *
 * Parameters: 
 *      volatile cNPNZ16b_t* controller
 *
 * Description:
 * This routine Initializes of a IIR-based control loop filter data structure. 
 * 
 * Please note: 
 * The control library provides similar functions implemented in C-code. These are not used
 * as this specific code module supports multiple controllers and therefore offers a generic version
 * of the init, reset and precharge routine.
 * 
 * *****************************************************************************************************/
volatile uint16_t ctrl_Init(volatile cNPNZ16b_t* controller) { // Pointer to nPnZ data structure)
    
//	volatile uint16_t i = 0;

//	// Initialize controller data structure at runtime with pre-defined default values
//	controller->status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))
//
//	controller->ptrACoefficients = &cha_vloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
//	controller->ptrBCoefficients = &cha_vloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
//	controller->ptrControlHistory = &cha_vloop_histories.ControlHistory[0]; // initialize pointer to control history array
//	controller->ptrErrorHistory = &cha_vloop_histories.ErrorHistory[0]; // initialize pointer to error history array
//	controller->normPostShiftA = cha_vloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
//	controller->normPostShiftB = cha_vloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
//	controller->normPostScaler = cha_vloop_post_scaler; // initialize control output value normalization scaling factor
//	controller->normPreShift = cha_vloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler
//
//	controller->ACoefficientsArraySize = cha_vloop_ACoefficients_size; // initialize A-coefficients array size
//	controller->BCoefficientsArraySize = cha_vloop_BCoefficients_size; // initialize A-coefficients array size
//	controller->ControlHistoryArraySize = cha_vloop_ControlHistory_size; // initialize control history array size
//	controller->ErrorHistoryArraySize = cha_vloop_ErrorHistory_size; // initialize error history array size
//
//
//	// Load default set of A-coefficients from user RAM into X-Space controller A-array
//	for(i=0; i<controller->ACoefficientsArraySize; i++)
//	{
//		controller->ptrACoefficients[i] = cha_vloop_ACoefficients[i];
//	}
//
//	// Load default set of B-coefficients from user RAM into X-Space controller B-array
//	for(i=0; i<controller->BCoefficientsArraySize; i++)
//	{
//		controller->ptrBCoefficients[i] = cha_vloop_BCoefficients[i];
//	}
//
//	// Clear error and control histories of the 3P3Z controller
//	ctrl_Reset(controller);
    
    return(1);  // Return success
    
}
