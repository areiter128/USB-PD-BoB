
#include <stdint.h>
#include "_root/config/globals.h"
#include "_root/config/task_manager_config.h"

uint16_t init_system_timer(void) {

    volatile uint16_t fres = 0;
    TxCON_CONTROL_REGISTER_t tmr;
    
    // Initialize Scheduler Timer
    // Default configuration for 16-bit operation off CPU clock
    
    tmr.flags.ton = TON_DISABLED;
    tmr.flags.tsidl = TSIDL_STOP;
    tmr.flags.tcs = TCS_INTERNAL;
    tmr.flags.tgate = TGATE_DISABLED;
    tmr.flags.tsync = TSYNC_NONE;

    #if defined (__P33SMPS_CH2__) || defined (__P33SMPS_CH5__)
    
    tmr.flags.tmwdis = TMWDIS_ENABLED;
    tmr.flags.tmwip = TMWIP_COMPLETE;
    tmr.flags.prwip = PRWIP_COMPLETE;
    tmr.flags.tecs = TECS_TCY;

    #endif
    
    // write configuration
    fres =  gstmr_reset(TASK_MGR_TIMER_INDEX); 
    fres &= gstmr_init_timer16b(TASK_MGR_TIMER_INDEX, tmr, TASK_MGR_PERIOD, TASK_MGR_ISR_PRIORITY);

    return(fres);
}

uint16_t launch_system_timer(void) {

    volatile uint16_t fres = 0;
    
    // User configuration
    fres &= gstmr_enable(TASK_MGR_TIMER_INDEX, TASK_MGR_ISR_STATE);  // Enable Timer without interrupts
    
    return(fres);
    
}

