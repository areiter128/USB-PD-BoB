/*
 * File:   soft_start.c
 * Author: M91406
 *
 * Created on October 16, 2018, 1:07 PM
 */


#include <xc.h>
#include "apl/resources/c4swbb_control.h"

/* === private state machine counter variables ===================================================== */
volatile uint16_t pwr_on_couter = 0; // Loop counter for power on delay
volatile uint16_t pchrg_couter = 0; // Loop counter for bootstrap pre-charge process
volatile uint16_t pg_couter = 0;    // Loop counter for power good delay


/*!exec_SoftStart()
 * *****************************************************************************************************
 * Summary:
 * Execute the soft start state machine
 *
 * Parameters: 
 * (none)
 *
 * Description:
 * This routine executes the soft-start state machine. This engine is completely self-sufficient in 
 * terms of tracking the soft-start progress. Once the soft-start procedure is completed, the engine
 * will reset itself waiting for being called again.
 * 
 * *****************************************************************************************************/

volatile uint16_t exec_4SWBB_PowerController(C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 0; // buffer variable of function return value
    volatile float fdummy = 0.0;
    volatile uint16_t int_dummy = 0;
    
    
    switch (ss_shadow.step) {

        /* @@SOFT_START_STEP_INITIALIZE
         * ============================
         * In this step the startup procedure and control loops are reset. The soft-start ramp
         * is defined by a power on delay, pre-charge delay, ramp-up period and power good delay. 
         * The internal counters for each of these phases are reset. Then the controller reference
         * is hijacked and reset to zero. 
         * In the next function call the soft-start step POWER_ON_DELAY will be executed */
        case CONVERTER_STATE_INITIALIZE:
            
            pwr_on_couter = 0;  // Reset power on counter
            pchrg_couter = 0;   // Reset pre-charge counter
            pg_couter = 0;      // Reset power good counter

            fres &= initialize_adc();
            fres &= initialize_pwm();
            
//            // Hijack voltage loop controller reference
//            ss_shadow.v_reference = 0; // Reset Soft-Start Voltage Reference
//            ss_shadow.i_reference = 0; // Reset Soft-Start Current Reference
//            ctrl_vloop.ptrControlReference = &ss_shadow.v_reference; // Voltage loop reference is hijacked by the soft-start reference
//
//            // switch to soft-start phase POWER-ON DELAY
//            ss_shadow.step = SOFT_START_STEP_POWER_ON_DELAY;

            break;

        /* @@SOFT_START_STEP_POWER_ON_DELAY
         * ================================
         * In this step the soft-start procedure continues with counting up variable pwr_on_couter
         * until the defined power on delay period has expired. At the end of this phase the low-side
         * PWM output is configured as GPIO for the manual pre-charge process and the soft-start step 
         * SOFT_START_STEP_PRECHARGE will be executed */
        case CONVERTER_STATE_POWER_ON_DELAY:

//            // delay startup until POWER ON DELAY has expired
//            if(pwr_on_couter++ > SOFT_START_POWER_ON_DELAY)
//            {
//                // switch to soft-start phase PRE-CHARGE BOOTSTRAP
//                BUCKL1_WR = 0;
//                BUCKL1_INIT_OUTPUT;
//                hspwm_set_gpio_low_side(BUCKH1_PGx_CHANNEL);
//
//                pchrg_couter = 0;   // Reset pre-charge counter
//                ss_shadow.step = SOFT_START_STEP_PRECHARGE;
//
//            }
                
            break;

        /* @@SOFT_START_STEP_PRECHARGE
         * ===========================
         * In this step the soft-start procedure continues with performing the manual pre-charge 
         * process which produces ~120ns wide pulses on the low side PWM signal pre-charging the 
         * half-bridge bootstrap cap. When this phase has expired, the execution step will be 
         * switched to SOFT_START_STEP_LAUNCH_V_RAMP */
        case CONVERTER_STATE_PRECHARGE:

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

        /* @@SOFT_START_STEP_LAUNCH_V_RAMP
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

//            // Pre-charge reference
//            if (application.data.v_out_cha < application.bata_v_loop.reference)
//            { ss_shadow.v_reference = application.data.v_out_cha; }
//            else 
//            { ss_shadow.v_reference = application.bata_v_loop.reference; }
//
//            // In average current mode, set current reference limit to max startup current level
//            #if (BATA_CONTROL_MODE == ACMC)
//            application.bata_v_loop.maximum = (volatile uint16_t)IBATx_OCL_STARTUP;
//            cvmc_bata.MaxOutput = application.bata_v_loop.maximum;
//            #endif
//            
//            // Pre-charge PWM and control loop history
//            fdummy = (float)(application.data.v_out_cha) / (float)(application.data.v_in << 1);
//            int_dummy = (uint16_t)(fdummy * (float)application.timing.period);
//            
//            #if (BATA_CONTROL_MODE == VMC)
//            
//            if(int_dummy < application.bata_v_loop.minimum) 
//            { int_dummy = application.bata_v_loop.minimum; }
//            else if(int_dummy > application.bata_v_loop.maximum) 
//            { int_dummy = application.bata_v_loop.maximum; }
//            
//            cvmc_bata_Precharge(&cvmc_bata, 0, int_dummy);
//
//            #elif (BATA_CONTROL_MODE == ACMC)
//
//            if(int_dummy < application.bata_i_loop.minimum) 
//            { int_dummy = application.bata_i_loop.minimum; }
//            else if(int_dummy > application.bata_i_loop.maximum) 
//            { int_dummy = application.bata_i_loop.maximum; }
//
//            cacmc_bata_Precharge(&cacmc_bata, 0, int_dummy);
//            
//            #endif            
//
//            Nop();
//            Nop();
//            Nop();
//            Nop();
//            
//            // set initial PWM duty ratio
//            BATA_PWM_DC = int_dummy;
//            
//            // Enable input power source
//            hspwm_ovr_release(BATA_PWM_CHANNEL); // Release PWM
//            
//            // switch to soft-start phase RAMP UP
//            ss_shadow.step = SOFT_START_STEP_V_RAMP_UP;
//            
            break;
            
        /* @@SOFT_START_STEP_V_RAMP_UP
         * ===========================
         * This is the essential step in which the output voltage is ramped up by incrementing the 
         * outer control loop reference. In voltage mode the output voltage will ramp up to the 
         * nominal regulation point. 
         * In average current mode the inner loop will limit the voltage as soon as the current 
         * reference limit is hit and the output is switched to constant current mode. */
        case CONVERTER_STATE_V_RAMP_UP:

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
         * This soft-start step is for Battery charger Applications only!
         * This phase of the soft-start ramp is only executed in average current mode and will 
         * only take effect when the current limit is hit before the nominal voltage regulation 
         * point. In this case the constant output current is ramped up to from the startup current
         * to the nominal constant charging current. */
        case CONVERTER_STATE_I_RAMP_UP:

            // increment current limit
            pInstance->i_loop->MaxOutput += pInstance->soft_start.ramp_i_ref_increment; // Increment maximum current limit

            // check if ramp is complete
            if (pInstance->i_loop->MaxOutput >= (volatile uint16_t)pInstance->data.) 
            {
                application.bata_v_loop.maximum = (volatile uint16_t)charger.i_ref_ramp.i_ref_stop;
                cvmc_bata.MaxOutput = application.bata_v_loop.maximum;
                ss_shadow.step = SOFT_START_WAIT_FOR_PWRGOOD;
            }

            //            
//            cvmc_bata.MaxOutput += charger.i_ref_ramp.i_ref_step_size; // SOFT_START_I_REF_STEP_SIZE; 
//
//            // check if ramp is complete
//            if (cvmc_bata.MaxOutput >= (volatile uint16_t)charger.i_ref_ramp.i_ref_stop) 
//            {
//                application.bata_v_loop.maximum = (volatile uint16_t)charger.i_ref_ramp.i_ref_stop;
//                cvmc_bata.MaxOutput = application.bata_v_loop.maximum;
//                ss_shadow.step = SOFT_START_WAIT_FOR_PWRGOOD;
//            }
            break;

        /* @@CONVERTER_STATE_POWER_GOOD
         * =============================
         * In this phase of the soft-start procedure the power supply should have reached nominal 
         * level, providing a stable, constant output voltage. A counter is incremented until the 
         * power good delay has expired before the soft-start process is marked as 
         * CONVERTER_STATE_COMPLETE */
        case CONVERTER_STATE_POWER_GOOD:
            // Enforce POWER GOOD Delay
            if(pInstance->soft_start.counter++ > pInstance->soft_start.pwr_good_delay) {
                pInstance->status.flags.op_status.CONVERTER_STATE_COMPLETE;  // set startup process COMPLETE
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
            // do nothing => enter normal operation
            Nop();
            Nop();
            break;

        /*!State Machine Fall-Back 
         * ========================
         * When this soft-start step is executed, something went wrong in the master state machine
         * or a fault condition was set by external code modules. In any of these cases the state 
         * machine falls back to STANDBY waiting to be restarted.  */
        default:
            pInstance->status.flags.op_status = CONVERTER_STATE_STANDBY;
            break;
    }

    //----------------------------------------------------------
    /*!Power Converter Auto-Start Function
     * When the control bit c4swbb.status.flags.auto_start is set, the status bits 'enabled' 
     * and 'GO' are automatically set and continuously enforced to ensure the power supply
     * will enter RAMP UP from STANDBY without the need for user code intervention. */
    // 
    if( (pInstance->status.flags.auto_start == true) && (pInstance->status.flags.fault_active == false)) {
        pInstance->status.flags.enabled = true;  // Auto-Enable power converter
        pInstance->status.flags.GO = true;       // Auto-Kick-off power converter
    }
    else { 
        pInstance->status.flags.GO = false; // Always Auto-Clear GO bit
    }
    //-- end of auto-start enforcement -------------------------

    return(1);
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

volatile uint16_t init_4SWBB_PowerController(C4SWBB_POWER_CONTROLLER_t* pInstance) {

    // Reset Startup Settings
    pInstance->soft_start.pwr_good_delay = CONVERTER_STATE_INITIALIZE; // reset state machine
    pInstance->soft_start.counter = 0; // reset startup counter
    pInstance->soft_start.v_reference = 0;  // reset voltage reference
    pInstance->soft_start.i_reference = 0;  // reset current reference
    pInstance->soft_start.pwr_on_delay = C4SWBB_PODLY;  // set power-on delay
    pInstance->soft_start.precharge_delay = 10;  // set pre-charge delay
    pInstance->soft_start.ramp_period = C4SWBB_RPER;  // set ramp up period
    pInstance->soft_start.pwr_good_delay = C4SWBB_PGDLY;  // set power good delay

    // Reset data buffers
    pInstance->data.v_in = 0;   // clear input voltage buffer
    pInstance->data.v_out = 0;  // reset output voltage buffer
    pInstance->data.i_out = 0;  // reset output current buffer
    pInstance->data.v_ref = C4SWBB_VOUT_REF;  // set initial voltage reference
    pInstance->data.temp = 0;   // reset converter board temperature buffer
    
    // Reset controller status
    pInstance->status.flags.power_source_detected = false; // reset POWER_SOURCE_DETECTED flag bit
    pInstance->status.flags.adc_active = false; // reset ADC_ACTIVE flag bit
    pInstance->status.flags.pwm_active = false; // reset PWM_ACTIVE flag bit
    pInstance->status.flags.tune_dir = 0; // reset voltage tune-in direction to UP
    pInstance->status.flags.fault_active = false; // reset power controller global fault flag bit
    pInstance->status.flags.GO = 0; // reset GO bit
    pInstance->status.flags.auto_start = false; // clear AUTO_START bit
    pInstance->status.flags.enabled = false; // disable power controller
    pInstance->status.flags.op_status = CONVERTER_STATE_INITIALIZE; // reset state machine
    
    
    return(1);
}

