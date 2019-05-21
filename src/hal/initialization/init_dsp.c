/*
 * File:   init_dsp.c
 * Author: M91406
 *
 * Created on October 16, 2018, 12:00 PM
 */


#include <xc.h>
#include "mcal/mcal.h"

/* === Initialize CPU ===================================================== */
volatile uint16_t initialize_dsp(void) {

    CORCONbits.ACCSAT = CORCON_ACCSAT_131;
//    CORCONbits.DL is read only
//    CORCONbits.EDT = CORCON_EDT_RUN;      // control bit => do not set during configuration
//    CORCONbits.SFA = CORCON_SFA_ACTIVE;   // read only
    CORCONbits.IF = CORCON_IF_FRACTIONAL;
    CORCONbits.RND = CORCON_RND_UNBIASED;
    CORCONbits.SATA = CORCON_SATA_ON;
    CORCONbits.SATB = CORCON_SATB_ON;
    CORCONbits.SATDW = CORCON_SATDW_ON;
    CORCONbits.US = CORCON_US_SIGNED;
    CORCONbits.VAR = CORCON_VAR_FIXED;

    Nop();
    Nop();
    Nop();
    
    return(true);
}

