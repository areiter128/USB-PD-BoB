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
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_1;
volatile C4SWBB_POWER_CONTROLLER_t c4swbb_2;

volatile uint16_t exec_PowerControl(void) {

    
    return (1);
}

volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    /* Initializing 4SW-BB DC/DC converter at USB port #1 */
    init_4SWBB_PowerController(&c4swbb_1);  // Initialize power controller of USB port 1
    
    // Set PWM settings
    c4swbb_1.boost_leg.pwm_instance = 5; // Instance of the PWM generator used (e.g. 1=PG1, 2=PG2, etc.)
    c4swbb_1.boost_leg.period = SWITCHING_PERIOD; // set switching period 
    c4swbb_1.boost_leg.phase = PWM_PHASE_SFT; // Phase shift of the PWM switching frequency 
    c4swbb_1.boost_leg.dead_time_rising = PWM_DEAD_TIME_LE;  // set half-bridge dead time at leading edge
    c4swbb_1.boost_leg.dead_time_falling = PWM_DEAD_TIME_FE; // set half-bridge dead time at falling edge
    c4swbb_1.boost_leg.duty_ratio_init = PWM_DUTY_RATIO_MIN; // reset initial duty cycle
    c4swbb_1.boost_leg.duty_ratio_min = PWM_DUTY_RATIO_MIN; // set minimum duty cycle
    c4swbb_1.boost_leg.duty_ratio_max = PWM_DUTY_RATIO_MAX; // set maximum duty cycle
    c4swbb_1.boost_leg.leb_period = LEB_PERIOD; // set leading edge blanking period
    
    c4swbb_2 = c4swbb_1;
    
    init_4SWBB_PowerController(&c4swbb_2);  // Initialize power controller of USB port 2
    
    return (fres);
}
