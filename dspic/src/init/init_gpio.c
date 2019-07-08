/*
 * File:   init_gpio.c
 * Author: M91406
 *
 * Created on July 8, 2019, 6:26 PM
 */


#include <xc.h>
#include "init_gpio.h"

volatile uint16_t init_gpio(void) {
    
    DBGLED_INIT;
    DBGPIN_INIT;
    
    return(1);
}
