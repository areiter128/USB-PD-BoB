/*
 * File:   main.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:52 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "main.h"


volatile uint16_t tgl_cnt = 0; // local counter of LED toggle loops
#define TGL_INTERVAL    999     // LED toggle interval of (999 + 1) x 100usec = 100ms
#define TMR1_TIMEOUT    30000   // Timeout protection for Timer1 interrupt flag bit

int main(void) {

    volatile uint16_t timeout = 0;

    init_fosc();
    init_timer1();
    init_gpio();
    

    while (1) {

        // wait for timer1 to overrun
        while ((!_T1IF) && (timeout++ < TMR1_TIMEOUT));
        timeout = 0;    // Reset timeout counter
        _T1IF = 0; // reset Timer1 interrupt flag bit
        DBGPIN_TOGGLE; // Toggle DEBUG-PIN

        if (tgl_cnt++ > TGL_INTERVAL) // Count 100usec loops until LED toggle interval is exceeded
        {
            DBGLED_TOGGLE;
            tgl_cnt = 0;
        } // Toggle LED and reset toggle counter

    }


    return (0);
}
