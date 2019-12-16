
#include <stdint.h>
#include "_root/generic/os_Globals.h"

volatile uint16_t OSTimer_Initialize(void) {

    volatile uint16_t fres = 1;
    TxCON_CONTROL_REGISTER_t tmr;
    
    // Initialize Scheduler Timer
    // Default configuration for 16-bit operation off CPU clock
    
    tmr.bits.ton = TON_DISABLED;
    tmr.bits.tsidl = TSIDL_STOP;
    tmr.bits.tcs = TCS_INTERNAL;
    tmr.bits.tgate = TGATE_DISABLED;
    tmr.bits.tsync = TSYNC_NONE;

    #if defined (__P33SMPS_CH2__) || defined (__P33SMPS_CH5__)
    
    tmr.bits.tmwdis = TMWDIS_ENABLED;
    tmr.bits.tmwip = TMWIP_COMPLETE;
    tmr.bits.prwip = PRWIP_COMPLETE;
    tmr.bits.tecs = TECS_TCY;

    #endif
    
    // write configuration
    fres &= smpsTimer_Reset(TASK_MGR_TIMER_INDEX); 
    fres &= smpsTimer_Initialize16b(TASK_MGR_TIMER_INDEX, tmr, TASK_MGR_PERIOD, TASK_MGR_ISR_PRIORITY);
    
    return(fres);
}

volatile uint16_t OSTimer_Start(void) {

    volatile uint16_t fres = 1;
    
    // User configuration
    fres &= smpsTimer_Enable(TASK_MGR_TIMER_INDEX, TASK_MGR_ISR_STATE);  // Enable Timer without interrupts
    
    return(fres);
    
}

