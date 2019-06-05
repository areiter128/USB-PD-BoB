/*
 * File:   soft_start.c
 * Author: M91406
 *
 * Created on October 16, 2018, 1:07 PM
 */


#include <xc.h>
#include "apl/resources/soft_start.h"

/* === Ramp up battery port A output voltage ===================================================== */
volatile uint16_t pwr_on_couter = 0; // Loop counter for power on delay
volatile uint16_t pchrg_couter = 0; // Loop counter for bootstrap pre-charge process
volatile uint16_t pg_couter = 0;    // Loop counter for power good delay

volatile CONTROL_SOFT_START_t ss_shadow;


/*!exec_SoftStart()
 * *****************************************************************************************************
 * Summary:
 * Execute the soft start state machine
 *
 * Parameters: 
 * (none)
 *
 * Description:
 * This routine executes the soft-start state machine. This engine is completely self-suffcient in 
 * terms of tracking the soft-start progress. Once the soft-start procedure is completed, the engine
 * will reset itself waiting for being called again.
 * 
 * *****************************************************************************************************/

volatile uint16_t exec_SoftStart(void) {
    
    volatile float fdummy = 0.0;
    volatile uint16_t int_dummy = 0;
    
    
    switch (ss_shadow.step) {

        /* @@SOFT_START_STEP_INITIALIZE
         * ============================
         * In this step the soft-start procedure and control loops are reset. The soft-start ramp
         * is defined by a power on delay, pre-charge delay, ramp-up period and power good delay. 
         * The internal counters for each of these phases are reset. Then the controller reference
         * is hijacked and reset to zero. 
         * In the next function call the soft-start step POWER_ON_DELAY will be executed */
        case SOFT_START_STEP_INITIALIZE:
            pwr_on_couter = 0;  // Reset power on counter
            pchrg_couter = 0;   // Reset pre-charge counter
            pg_couter = 0;      // Reset power good counter

            // Hijack voltage loop controller reference
            ss_shadow.v_reference = 0; // Reset Soft-Start Voltage Reference
            ss_shadow.i_reference = 0; // Reset Soft-Start Current Reference
            cvmc_cha.ptrControlReference = &ss_shadow.v_reference; // Voltage loop reference is hijacked by the soft-start reference

            // switch to soft-start phase POWER-ON DELAY
            ss_shadow.step = SOFT_START_STEP_POWER_ON_DELAY;

            break;

        /* @@SOFT_START_STEP_POWER_ON_DELAY
         * ================================
         * In this step the soft-start procedure continues with counting up variable pwr_on_couter
         * until the defined power on delay period has expired. At the end of this phase the low-side
         * PWM output is configured as GPIO for the manual pre-charge process and the soft-start step 
         * SOFT_START_STEP_PRECHARGE will be executed */
        case SOFT_START_STEP_POWER_ON_DELAY:

            // delay startup until POWER ON DELAY has expired
            if(pwr_on_couter++ > SOFT_START_POWER_ON_DELAY)
            {
                // switch to soft-start phase PRE-CHARGE BOOTSTRAP
                BUCKL1_WR = 0;
                BUCKL1_INIT_OUTPUT;
                hspwm_set_gpio_low_side(BUCKH1_PGx_CHANNEL);

                pchrg_couter = 0;   // Reset pre-charge counter
                ss_shadow.step = SOFT_START_STEP_PRECHARGE;

            }
                
            break;

        /* @@SOFT_START_STEP_PRECHARGE
         * ===========================
         * In this step the soft-start procedure continues with performing the manual pre-charge 
         * process which produces ~120ns wide pulses on the low side PWM signal pre-charging the 
         * half-bridge bootstrap cap. When this phase has expired, the execution step will be 
         * switched to SOFT_START_STEP_LAUNCH_V_RAMP */
        case SOFT_START_STEP_PRECHARGE:

            // generate n bootstrap pre-charge pulses before enabling switch node
            if(pchrg_couter++ < SOFT_START_PRECHARGE_TICKS)
            { 
                // manually generated pulse on low-side switch
                // pre-charging the bootstrap capacitor
                BUCKL1_WR = 1;
                SOFT_START_PCRG_PULSE_DUTY;
                BUCKL1_WR = 0;
            }
            else
            {
                // switch to soft-start phase LAUNCH RAMP UP
                hspwm_reset_gpio_low_side(BUCKH1_PGx_CHANNEL);
                ss_shadow.step = SOFT_START_STEP_LAUNCH_V_RAMP; 
            }
            
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
        case SOFT_START_STEP_LAUNCH_V_RAMP:

            // Pre-charge reference
            if (application.data.v_out_cha < application.bata_v_loop.reference)
            { ss_shadow.v_reference = application.data.v_out_cha; }
            else 
            { ss_shadow.v_reference = application.bata_v_loop.reference; }

            // In average current mode, set current reference limit to max startup current level
            #if (BATA_CONTROL_MODE == ACMC)
            application.bata_v_loop.maximum = (volatile uint16_t)IBATx_OCL_STARTUP;
            cvmc_bata.MaxOutput = application.bata_v_loop.maximum;
            #endif
            
            // Pre-charge PWM and control loop history
            fdummy = (float)(application.data.v_out_cha) / (float)(application.data.v_in << 1);
            int_dummy = (uint16_t)(fdummy * (float)application.timing.period);
            
            #if (BATA_CONTROL_MODE == VMC)
            
            if(int_dummy < application.bata_v_loop.minimum) 
            { int_dummy = application.bata_v_loop.minimum; }
            else if(int_dummy > application.bata_v_loop.maximum) 
            { int_dummy = application.bata_v_loop.maximum; }
            
            cvmc_bata_Precharge(&cvmc_bata, 0, int_dummy);

            #elif (BATA_CONTROL_MODE == ACMC)

            if(int_dummy < application.bata_i_loop.minimum) 
            { int_dummy = application.bata_i_loop.minimum; }
            else if(int_dummy > application.bata_i_loop.maximum) 
            { int_dummy = application.bata_i_loop.maximum; }

            cacmc_bata_Precharge(&cacmc_bata, 0, int_dummy);
            
            #endif            

            Nop();
            Nop();
            Nop();
            Nop();
            
            // set initial PWM duty ratio
            BATA_PWM_DC = int_dummy;
            
            // Enable input power source
            hspwm_ovr_release(BATA_PWM_CHANNEL); // Release PWM
            
            // switch to soft-start phase RAMP UP
            ss_shadow.step = SOFT_START_STEP_V_RAMP_UP;
            
            break;
            
        /* @@SOFT_START_STEP_V_RAMP_UP
         * ===========================
         * This is the essential step in which the output voltage is ramped up by incrementing the 
         * outer control loop reference. In voltage mode the output voltage will ramp up to the 
         * nominal regulation point. 
         * In average current mode the inner loop will limit the voltage as soon as the current 
         * reference limit is hit and the output is switched to constant current mode. */
        case SOFT_START_STEP_V_RAMP_UP:

            // enable control loop
            #if (BATA_CONTROL_MODE == VMC)
            cvmc_bata.status.flag.enable = 1; // enable voltage loop controller
            #elif (BATA_CONTROL_MODE == ACMC)
            cvmc_bata.status.flag.enable = 1; // enable voltage loop controller
            cacmc_bata.status.flag.enable = 1; // enable current loop controller
            #endif

            // increment reference
            ss_shadow.v_reference += SOFT_START_V_REF_STEP_SIZE;

            // check if ramp is complete
            if (ss_shadow.v_reference >= application.bata_v_loop.reference) 
            {
                ss_shadow.v_reference = application.bata_v_loop.reference;
                cvmc_bata.status.flag.enable = 0;
                cvmc_bata.ptrControlReference = &application.bata_v_loop.reference;
                cvmc_bata.status.flag.enable = 1;
                #if (BATA_CONTROL_MODE == VMC)
                ss_shadow.step = SOFT_START_WAIT_FOR_PWRGOOD;
                #elif (BATA_CONTROL_MODE == ACMC)
                ss_shadow.step = SOFT_START_STEP_I_RAMP_UP;
                #endif
            }
            break;

        /* @@SOFT_START_STEP_I_RAMP_UP
         * ===========================
         * This phase of the soft-start ramp is only executed in average current mode and will 
         * only take effect when the current limit is hit before the nominal voltage regulation 
         * point. In this case the constant output current is ramped up to from the startup current
         * to the nominal constant charging current. */
        case SOFT_START_STEP_I_RAMP_UP:

            // increment current limit
            cvmc_bata.MaxOutput += charger.i_ref_ramp.i_ref_step_size; // SOFT_START_I_REF_STEP_SIZE; // Increment maximum charging current limit

            // check if ramp is complete
            if (cvmc_bata.MaxOutput >= (volatile uint16_t)charger.i_ref_ramp.i_ref_stop) 
            {
                application.bata_v_loop.maximum = (volatile uint16_t)charger.i_ref_ramp.i_ref_stop;
                cvmc_bata.MaxOutput = application.bata_v_loop.maximum;
                ss_shadow.step = SOFT_START_WAIT_FOR_PWRGOOD;
            }
            break;

        /* @@SOFT_START_WAIT_FOR_PWRGOOD
         * =============================
         * In this phase of the soft-start procedure a counter is incremented until the power good 
         * delay has expired before the soft-start process is marked as COMPLETEd */
        case SOFT_START_WAIT_FOR_PWRGOOD:
            // POWER GOOD Delay
            if(pg_couter++ > SOFT_START_POWER_GOOD_DELAY)
            {
                ss_shadow.step = SOFT_START_STEP_COMPLETE; 
                pg_couter = 0; 
            }
            Nop();
            break;
            
        /* @@SOFT_START_STEP_COMPLETE
         * =============================
         * When the soft-start step is set to SOFT_START_STEP_COMPLETE, the soft-start state machine 
         * will not be executed any further and the converter has entered normal operation.  */
        case SOFT_START_STEP_COMPLETE:
            // do nothing => enter normal operation
            Nop();
            Nop();
            break;

        /* @@SOFT_START_STEP_UNDEFINED
         * ===========================
         * When this soft-start step is executed, something went wrong in the master state machine.
         * To fix this issue the soft-start step will be set to INITIALIZATION.  */
        default:
            ss_shadow.step = SOFT_START_STEP_INITIALIZE;
            break;
    }


    return;
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

volatile uint16_t init_SoftStart(void) {

    ss_shadow.direction = SOFT_START_RAMPDIR_UP;    // reset ramp direction to UP
    ss_shadow.ramp_status = SOFT_START_RAMP_OFF;    // Soft-start ramp up status 
    ss_shadow.step = SOFT_START_STEP_INITIALIZE;    // soft-start progress phase

    ss_shadow.v_reference = 0; // shadow copy of the controller voltage reference during soft-start
    ss_shadow.i_reference = 0; // shadow copy of the controller current reference during soft-start
    ss_shadow.interval = 0;    // shadow copy of the soft-start tick interval counter
    
    return(1);
}

