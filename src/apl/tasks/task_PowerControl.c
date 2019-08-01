/*
 * File:   task_PowerControl.c
 * Author: M91406
 *
 * Created on May 27, 2019, 3:11 PM
 */


#include <xc.h>

#include "apl/apl.h"
#include "mcal/mcal.h"
#include "hal/hal.h"

//#include "apl/tasks/task_PowerControl.h"


volatile uint16_t exec_PowerControl(void) {

    Nop();
    Nop();
    Nop();
    
    return (1);
}

volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    fres &= initialize_adc();
    fres &= initialize_pwm();
    
    /* SDB AIC power converter default settings */
//    application.timing.period = SWITCHING_PERIOD; // n x 250 ps (e.g. 20,000 = ~250 kHz)
//    application.timing.duty_ratio_init = DUTY_RATIO_INIT_REG; // n x 250 ps (e.g. 1% x 20,000 = 200 ticks)
//    application.timing.duty_ratio_min = DUTY_RATIO_MIN_REG + (PWM_DEAD_TIME_LE + PWM_DEAD_TIME_FE); // n x 250 ps (e.g. 1% x 20,000 = 200 ticks)
//    application.timing.duty_ratio_max = DUTY_RATIO_MAX_REG; // n x 250 ps (e.g. 1% x 20,000 = 200 ticks)
//    application.timing.dead_time_rising = PWM_DEAD_TIME_LE; // n x 250 ps (e.g. 200 = 50 ns)
//    application.timing.dead_time_falling = PWM_DEAD_TIME_FE; // n x 250 ps (e.g. 320 = 80 ns)
//    
    /* power supply converter default settings */

    
    // reset global flags
//    application.ctrl_status.flags.adc_active = false; // ADC has not been started yet
//    application.ctrl_status.flags.pwm_started = false; // PWM has not been started yet
//    application.ctrl_status.flags.system_startup = true; // System is in startup mode
//    application.ctrl_status.flags.system_ready = false; // system is not ready yet
//    application.ctrl_status.flags.power_source_detected = false; // reset power source detection
    
    
    
    return (fres);
}
