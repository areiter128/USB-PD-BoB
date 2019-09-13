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

        /*!CONVERTER_STATE_INITIALIZE
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

        /*!CONVERTER_STATE_STANDBY
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
            
        /*!CONVERTER_STATE_POWER_ON_DELAY
         * ================================
         * During the POWER ON DELAY the power controller waits until the programmed delay 
         * period has expired. Neither control loop nor power converter are active.
         * Once this delay period has expired the state machine will switch to 
         * CONVERTER_STATE_LAUNCH_V_RAMP  */
            
        case CONVERTER_STATE_POWER_ON_DELAY:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = true;
            
            // delay startup until POWER ON DELAY has expired
            if(pInstance->soft_start.counter++ > pInstance->soft_start.pwr_on_delay) {

                pInstance->soft_start.counter = 0;  // Reset soft-start counter
                pInstance->status.flags.op_status = CONVERTER_STATE_LAUNCH_V_RAMP; // switch to soft-start phase LAUNCH_V_RAMP
                
            }
                
            break;

        /*!CONVERTER_STATE_PRECHARGE
         * ===========================
         * In this step the soft-start procedure continues with performing the manual pre-charge 
         * process which produces ~120ns wide pulses on the low side PWM signal pre-charging the 
         * half-bridge bootstrap cap. When this phase has expired, the execution step will be 
         * switched to SOFT_START_STEP_LAUNCH_V_RAMP */
        case CONVERTER_STATE_PRECHARGE:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = true;

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

        /*!CONVERTER_STATE_LAUNCH_V_RAMP
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

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = true;

            // Hijack voltage loop controller reference
            pInstance->soft_start.v_reference = 0; // Reset Soft-Start Voltage Reference
            pInstance->soft_start.i_reference = 0; // Reset Soft-Start Current Reference
            
            // Voltage loop reference is hijacked by the soft-start reference
            pInstance->v_loop.controller->ptrControlReference = &pInstance->soft_start.v_reference;
            
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
            pInstance->v_loop.ctrl_Precharge(pInstance->v_loop.controller, 0, int_dummy);

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
            hspwm_set_duty_cycle(pInstance->buck_leg.pwm_instance, int_dummy, 0);
            
            // ToDo: Add boost leg duty ratio pre-charge 
            
            // switch to soft-start phase RAMP UP
            pInstance->status.flags.op_status = CONVERTER_STATE_V_RAMP_UP;
            
            break;
            
        /*!CONVERTER_STATE_V_RAMP_UP
         * ===========================
         * This is the essential step in which the output voltage is ramped up by incrementing the 
         * outer control loop reference. In voltage mode the output voltage will ramp up to the 
         * nominal regulation point. 
         * In average current mode the inner loop will limit the voltage as soon as the current 
         * reference limit is hit and the output is switched to constant current mode. */
        case CONVERTER_STATE_V_RAMP_UP:

            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = true;

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
            pInstance->status.flags.busy = true;

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

        /*!CONVERTER_STATE_POWER_GOOD
         * =============================
         * In this phase of the soft-start procedure the power supply should have reached nominal 
         * level, providing a stable, constant output voltage. A counter is incremented until the 
         * power good delay has expired before the soft-start process is marked as 
         * CONVERTER_STATE_COMPLETE */
        case CONVERTER_STATE_POWER_GOOD:
            
            // Set the BUSY bit indicating a delay/ramp period being executed
            pInstance->status.flags.busy = true;
            
            // Enforce POWER GOOD Delay
            if(pInstance->soft_start.counter++ > pInstance->soft_start.pwr_good_delay) {
                pInstance->status.flags.op_status = CONVERTER_STATE_COMPLETE;  // set startup process COMPLETE
                pInstance->soft_start.counter = 0;  // reset startup counter
            }
            Nop();
            break;
            
        /*!CONVERTER_STATE_COMPLETE
         * =============================
         * When the soft-start step is set to CONVERTER_STATE_COMPLETE, the start-up procedure
         * has been completed and the converter has entered normal operation. From this point 
         * forward the power supply will exclusively be running in interrupt instances executing 
         * the control loops. 
         * 
         * The state machine monitors changes of the user reference setting. Once a change has
         * been detected, the state machine tunes the voltage loop reference into the new level 
         * directly and without ramp-up and power good delays. The fault handler is kept running
         * and no further current limiting functions (like during soft-start) are performed.
         */
        case CONVERTER_STATE_COMPLETE:

            if(!pInstance->status.flags.autorun){
                if(!pInstance->status.flags.enabled)
                { pInstance->status.flags.op_status = CONVERTER_STATE_RESET; } // Always Auto-Clear GO bit
            }
                
            /*!Runtime Reference Tuning
             * ==================================================================================
             * Description:
             * If the user reference setting has been changed and different from the most recent 
             * controller reference, the state machine will tune the controller reference into the 
             * user control reference level. While ramping the output voltage up or down, the 
             * BUSY bit will be set and any new changes to the reference will be ignored until
             * the ramp up/down is complete.
             * =================================================================================*/

            if((pInstance->data.v_ref != pInstance->v_loop.reference) && (!pInstance->status.flags.busy))
            {
                // Set the BUSY bit indicating a delay/ramp period being executed
                pInstance->status.flags.busy = true;
                
                // New reference value is less than controller reference value => ramp down
                if(pInstance->data.v_ref < pInstance->v_loop.reference){
                    // decrement reference until new reference level is reached
                    pInstance->status.flags.tune_dir = CONVERTER_RAMP_DIR_DOWN; // set RAMP_DOWN flag
                    pInstance->v_loop.reference -= pInstance->soft_start.ramp_v_ref_increment; // decrement reference
                    if(pInstance->v_loop.reference < pInstance->data.v_ref) { // check if ramp is complete
                        pInstance->v_loop.reference = pInstance->data.v_ref; // clamp reference level to setting
                    }
                        
                }
                // New reference value is greater than controller reference value => ramp up
                else if(pInstance->data.v_ref > pInstance->v_loop.reference) {
                    // increment reference until new reference level is reached
                    pInstance->status.flags.tune_dir = CONVERTER_RAMP_DIR_UP; // set RAMP_UP flag
                    pInstance->v_loop.reference += pInstance->soft_start.ramp_v_ref_increment; // increment reference
                    if(pInstance->v_loop.reference > pInstance->data.v_ref){ // check if ramp is complete
                        pInstance->v_loop.reference = pInstance->data.v_ref; // clamp reference level to setting
                    }
                }
                
            }
            else{
                // Clear the BUSY bit indicating a delay/ramp period being executed
                pInstance->status.flags.busy = false;

            }
            
            break;

        /*!State Machine Fall-Back 
         * ========================
         * When this soft-start step is executed, something went wrong in the master state machine
         * or a fault condition was set by external code modules. In any of these cases the state 
         * machine falls back to STANDBY waiting to be restarted.  */
        default:
            
            c4SWBB_shut_down(pInstance);
            
            pInstance->status.flags.busy = false; // Clear the BUSY bit indicating a delay/ramp period being executed
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
        pInstance->status.flags.GO = false;
    }
    //-- end of auto-start enforcement -------------------------

    
    return(fres);
}

/*!c4swbb_reset()
 * *****************************************************************************************************
 * Summary:
 * Turns off the power converter and switches the state machine back into STANDBY
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * This routine resets the the 4-switch buck/boost converter by turning off the PWM immediately.
 * Once the PWM output have been disabled, the control loop histories are cleared and the 
 * power controller state machine is switched into STANDBY.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4SWBB_shut_down(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // Overriding PWM output pins with pin states defined in PGxIOCONL->OVRDAT
    fres &= hspwm_ovr_hold(pInstance->buck_leg.pwm_instance);
    fres &= hspwm_ovr_hold(pInstance->boost_leg.pwm_instance);
    
    // void functions don't return values and therefore their execution doesn't get checked
    pInstance->v_loop.ctrl_Reset(pInstance->v_loop.controller);
    pInstance->i_loop.ctrl_Reset(pInstance->i_loop.controller);
    
    return(fres); // ToDo: need function execution success validation
    
}

/*!reset_4SWBB_PowerController()
 * *****************************************************************************************************
 * Summary:
 * Resets the 4-switch buck/boost controller state machine
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * This routine resets the default values of the state machine of the 4-switch buck/boost controller 
 * specified by function parameter 'pInstance'. This also resets all previously made settings.
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t reset_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

    // Reset PWM settings
    pInstance->buck_leg.pwm_instance = 0; // Clear PWM instance of the buck leg
    pInstance->buck_leg.period = 0; // Reset PWM period of the buck leg
    pInstance->buck_leg.phase = 0; // Clear PWM phase of the buck leg
    pInstance->buck_leg.leb_period = 0; // Clear PWM LEB period of the buck leg
    pInstance->buck_leg.duty_ratio_min = 0; // Clear minimum PWM duty cycle of the buck leg
    pInstance->buck_leg.duty_ratio_max = 0; // Clear maximum PWM duty cycle of the buck leg
    pInstance->buck_leg.duty_ratio_init = 0; // Clear initial PWM duty cycle of the buck leg
    pInstance->buck_leg.dead_time_rising = 0; // Clear PWM leading edge half-bridge dead time of the buck leg
    pInstance->buck_leg.dead_time_falling = 0; // Clear PWM falling edge half-bridge dead time of the buck leg
    pInstance->buck_leg.pwm_swap = 0; // Reset PWMxH/PWMxL swap setting of the buck leg
    
    pInstance->boost_leg.pwm_instance = 0; // Clear PWM instance of the boost leg
    pInstance->boost_leg.period = 0; // Reset PWM period of the boost leg
    pInstance->boost_leg.phase = 0; // Clear PWM phase of the boost leg
    pInstance->boost_leg.leb_period = 0; // Clear PWM LEB period of the boost leg
    pInstance->boost_leg.duty_ratio_min = 0; // Clear minimum PWM duty cycle of the boost leg
    pInstance->boost_leg.duty_ratio_max = 0; // Clear maximum PWM duty cycle of the boost leg
    pInstance->boost_leg.duty_ratio_init = 0; // Clear initial PWM duty cycle of the boost leg
    pInstance->boost_leg.dead_time_rising = 0; // Clear PWM leading edge half-bridge dead time of the boost leg
    pInstance->boost_leg.dead_time_falling = 0; // Clear PWM falling edge half-bridge dead time of the boost leg
    pInstance->boost_leg.pwm_swap = 0; // Reset PWMxH/PWMxL swap setting of the boost leg

    // Reset Controller Settings
    pInstance->v_loop.controller = 0; // Clear pointer to voltage control loop object
    pInstance->v_loop.ctrl_Init = 0; // Clear function pointer to voltage control loop initialization routine
    pInstance->v_loop.ctrl_Precharge = 0; // Clear function pointer to voltage control loop pre-charge routine
    pInstance->v_loop.ctrl_Reset = 0; // Clear function pointer to voltage control loop reset routine
    pInstance->v_loop.ctrl_Update = 0; // Clear function pointer to voltage control loop update routine
    pInstance->v_loop.feedback_offset = 0; // Reset the feedback offset setting of the voltage control loop
    pInstance->v_loop.minimum = 0; // Reset the minimum output setting of the voltage control loop
    pInstance->v_loop.maximum = 0; // Reset the maximum output setting of the voltage control loop
    pInstance->v_loop.trigger_offset = 0; // Reset the ADC trigger offset setting of the voltage control loop
    pInstance->v_loop.reference = 0; // Reset the control reference of the voltage control loop
        
    pInstance->i_loop.controller = 0; // Clear pointer to current control loop object
    pInstance->i_loop.ctrl_Init = 0; // Clear function pointer to current control loop initialization routine
    pInstance->i_loop.ctrl_Precharge = 0; // Clear function pointer to current control loop pre-charge routine
    pInstance->i_loop.ctrl_Reset = 0; // Clear function pointer to current control loop reset routine
    pInstance->i_loop.ctrl_Update = 0; // Clear function pointer to current control loop update routine
    pInstance->i_loop.feedback_offset = 0; // Reset the feedback offset setting of the current control loop
    pInstance->i_loop.minimum = 0; // Reset the minimum output setting of the current control loop
    pInstance->i_loop.maximum = 0; // Reset the maximum output setting of the current control loop
    pInstance->i_loop.trigger_offset = 0; // Reset the ADC trigger offset setting of the current control loop
    pInstance->i_loop.reference = 0; // Reset the control reference of the current control loop
    
    // Reset Startup Settings
    pInstance->soft_start.pwr_good_delay = 0; // reset state machine
    pInstance->soft_start.counter = 0; // reset startup counter
    pInstance->soft_start.v_reference = 0;  // reset voltage tuning reference
    pInstance->soft_start.i_reference = 0;  // reset current tuning reference
    pInstance->soft_start.inrush_limit = 0; // reset soft-start inrush current limit
    pInstance->soft_start.pwr_on_delay = 0;  // set power-on delay
    pInstance->soft_start.precharge_delay = 10;  // set pre-charge delay
    pInstance->soft_start.ramp_period = 0;  // set ramp up period
    pInstance->soft_start.pwr_good_delay = 0;  // set power good delay
    
    // Reset data buffers
    pInstance->data.v_in = 0;   // clear input voltage buffer
    pInstance->data.v_out = 0;  // reset output voltage buffer
    pInstance->data.i_out = 0;  // reset output current buffer
    pInstance->data.v_ref = 0;  // reset initial voltage reference
    pInstance->data.temp = 0;   // reset converter board temperature buffer
    
    // Reset controller status
    pInstance->status.flags.power_source_detected = false; // reset POWER_SOURCE_DETECTED flag bit
    pInstance->status.flags.adc_active = false; // reset ADC_ACTIVE flag bit
    pInstance->status.flags.pwm_active = false; // reset PWM_ACTIVE flag bit
    pInstance->status.flags.tune_dir = 0; // reset voltage tune-in direction to UP
    pInstance->status.flags.fault_active = false; // reset power controller global fault flag bit
    pInstance->status.flags.GO = 0; // reset GO bit
    pInstance->status.flags.autorun = false; // clear AUTORUN bit
    pInstance->status.flags.enabled = false; // disable power controller
    pInstance->status.flags.op_status = CONVERTER_STATE_INITIALIZE; // reset state machine
    
    return(1);
}



/*!init_4SWBB_PowerController()
 * *****************************************************************************************************
 * Summary:
 * Initializes the 4-switch buck/boost controller state machine
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * This routine initializes the default values of the state machine of the 4-switch buck/boost controller 
 * specified by function parameter 'pInstance'. This also overrides all previously made settings.
 * 
 * 
 * *****************************************************************************************************/

volatile uint16_t init_4SWBB_PowerController(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

    // Initialize PWM settings
    pInstance->buck_leg.pwm_instance = 0; // Clear PWM instance of the buck leg
    pInstance->buck_leg.period = 0; // Reset PWM period of the buck leg
    pInstance->buck_leg.phase = 0; // Clear PWM phase of the buck leg
    pInstance->buck_leg.leb_period = 0; // Clear PWM LEB period of the buck leg
    pInstance->buck_leg.duty_ratio_min = 0; // Clear minimum PWM duty cycle of the buck leg
    pInstance->buck_leg.duty_ratio_max = 0; // Clear maximum PWM duty cycle of the buck leg
    pInstance->buck_leg.duty_ratio_init = 0; // Clear initial PWM duty cycle of the buck leg
    pInstance->buck_leg.dead_time_rising = 0; // Clear PWM leading edge half-bridge dead time of the buck leg
    pInstance->buck_leg.dead_time_falling = 0; // Clear PWM falling edge half-bridge dead time of the buck leg
    
    pInstance->boost_leg.pwm_instance = 0; // Clear PWM instance of the buck leg
    pInstance->boost_leg.period = 0; // Reset PWM period of the buck leg
    pInstance->boost_leg.phase = 0; // Clear PWM phase of the buck leg
    pInstance->boost_leg.leb_period = 0; // Clear PWM LEB period of the buck leg
    pInstance->boost_leg.duty_ratio_min = 0; // Clear minimum PWM duty cycle of the buck leg
    pInstance->boost_leg.duty_ratio_max = 0; // Clear maximum PWM duty cycle of the buck leg
    pInstance->boost_leg.duty_ratio_init = 0; // Clear initial PWM duty cycle of the buck leg
    pInstance->boost_leg.dead_time_rising = 0; // Clear PWM leading edge half-bridge dead time of the buck leg
    pInstance->boost_leg.dead_time_falling = 0; // Clear PWM falling edge half-bridge dead time of the buck leg

    // Reset Controller Settings
    pInstance->v_loop.controller = 0; // Clear pointer to voltage control loop object
    pInstance->v_loop.ctrl_Init = 0; // Clear function pointer to voltage control loop initialization routine
    pInstance->v_loop.ctrl_Precharge = 0; // Clear function pointer to voltage control loop precharge routine
    pInstance->v_loop.ctrl_Reset = 0; // Clear function pointer to voltage control loop reset routine
    pInstance->v_loop.ctrl_Update = 0; // Clear function pointer to voltage control loop update routine
    pInstance->v_loop.feedback_offset = 0; // Reset the feedback offset setting of the voltage control loop
    pInstance->v_loop.minimum = 0; // Reset the minimum output setting of the voltage control loop
    pInstance->v_loop.maximum = 0; // Reset the maximum output setting of the voltage control loop
    pInstance->v_loop.trigger_offset = 0; // Reset the ADC trigger offset setting of the voltage control loop
    pInstance->v_loop.reference = 0; // Reset the control reference of the voltage control loop
        
    pInstance->i_loop.controller = 0; // Clear pointer to current control loop object
    pInstance->i_loop.ctrl_Init = 0; // Clear function pointer to current control loop initialization routine
    pInstance->i_loop.ctrl_Precharge = 0; // Clear function pointer to current control loop precharge routine
    pInstance->i_loop.ctrl_Reset = 0; // Clear function pointer to current control loop reset routine
    pInstance->i_loop.ctrl_Update = 0; // Clear function pointer to current control loop update routine
    pInstance->i_loop.feedback_offset = 0; // Reset the feedback offset setting of the current control loop
    pInstance->i_loop.minimum = 0; // Reset the minimum output setting of the current control loop
    pInstance->i_loop.maximum = 0; // Reset the maximum output setting of the current control loop
    pInstance->i_loop.trigger_offset = 0; // Reset the ADC trigger offset setting of the current control loop
    pInstance->i_loop.reference = 0; // Reset the control reference of the current control loop
    
    // Reset Startup Settings
    pInstance->soft_start.pwr_good_delay = 0; // reset state machine
    pInstance->soft_start.counter = 0; // reset startup counter
    pInstance->soft_start.v_reference = 0;  // reset voltage tuning reference
    pInstance->soft_start.i_reference = 0;  // reset current tuning reference
    pInstance->soft_start.inrush_limit = 0; // reset soft-start inrush current limit
    pInstance->soft_start.pwr_on_delay = 0;  // set power-on delay
    pInstance->soft_start.precharge_delay = 10;  // set pre-charge delay
    pInstance->soft_start.ramp_period = 0;  // set ramp up period
    pInstance->soft_start.pwr_good_delay = 0;  // set power good delay
    
    // Reset data buffers
    pInstance->data.v_in = 0;   // clear input voltage buffer
    pInstance->data.v_out = 0;  // reset output voltage buffer
    pInstance->data.i_out = 0;  // reset output current buffer
    pInstance->data.v_ref = 0;  // reset initial voltage reference
    pInstance->data.temp = 0;   // reset converter board temperature buffer
    
    // Reset controller status
    pInstance->status.flags.power_source_detected = false; // reset POWER_SOURCE_DETECTED flag bit
    pInstance->status.flags.adc_active = false; // reset ADC_ACTIVE flag bit
    pInstance->status.flags.pwm_active = false; // reset PWM_ACTIVE flag bit
    pInstance->status.flags.tune_dir = 0; // reset voltage tune-in direction to UP
    pInstance->status.flags.fault_active = false; // reset power controller global fault flag bit
    pInstance->status.flags.GO = 0; // reset GO bit
    pInstance->status.flags.autorun = false; // clear AUTORUN bit
    pInstance->status.flags.enabled = false; // disable power controller
    pInstance->status.flags.op_status = CONVERTER_STATE_INITIALIZE; // reset state machine
    
    return(1);
}




