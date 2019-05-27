/*
 * File:   task_PowerControl.c
 * Author: M91406
 *
 * Created on May 27, 2019, 3:11 PM
 */


#include <xc.h>

#include "mcal/mcal.h"
#include "hal/hal.h"

volatile uint16_t exec_PowerControl(void) {

    Nop();
    Nop();
    Nop();
    
    return (1);
}

volatile uint16_t init_PowerControl(void) {

    volatile uint16_t fres = 1;
    
    fres &= initialize_adc();
    
    return (fres);
}
