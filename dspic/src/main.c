/*
 * File:   main.c
 * Author: M91406
 *
 * Created on July 8, 2019, 1:52 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "../h/main.h"

#ifdef DPSK3_R30
// DPSK3 Debug Pins 
    #define DBGLED_SET		{ _LATB6 = 1; }
    #define DBGLED_CLEAR	{ _LATB6 = 0; }
    #define DBGLED_TOGGLE	{ _LATB6 ^= 1; }
    #define DBGLED_INIT		{ _LATB6 = 0; _TRISB6 = 0; }
#endif

#ifdef MA330048_R30
// dsPIC33CK DP PIM Debug Pins
    #define DBGLED_SET		{ _LATD15 = 1; }
    #define DBGLED_CLEAR	{ _LATD15 = 0; }
    #define DBGLED_TOGGLE	{ _LATD15 ^= 1; }
    #define DBGLED_INIT		{ _LATD15 = 0; _TRISD15 = 0; }
#endif


volatile uint16_t tgl_cnt = 0; // local counter of LED toggle loops
#define TGL_INTERVAL    999     // LED toggle interval of (999 + 1) x 100usec = 100ms
#define TMR1_TIMEOUT    30000   // Timeout protection for Timer1 interrupt flag bit

int main(void) {

    volatile uint16_t timeout = 0;

    init_fosc();
    init_timer1();

    DBGLED_INIT;

    while (1) {

        // wait for timer1 to overrun
        while ((!_T1IF) && (timeout++ < TMR1_TIMEOUT));
        timeout = 0;    // Reset timeout counter
        _T1IF = 0; // reset Timer1 interrupt flag bit

        if (tgl_cnt++ > TGL_INTERVAL) // Count 100usec loops until LED toggle interval is exceeded
        {
            DBGLED_TOGGLE;
            tgl_cnt = 0;
        } // Toggle LED and reset toggle counter

    }


    return (0);
}
