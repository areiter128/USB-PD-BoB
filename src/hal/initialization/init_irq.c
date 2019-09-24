/*
 * File:   init_irq.c
 * Author: M91406
 *
 * Created on August 3, 2018, 9:50 AM
 */


#include "mcal/mcal.h"
#include "mcal/config/devcfg_irq.h"
#include "hal/config/syscfg_options.h"

volatile uint16_t irq_initialize(void)
{

    volatile uint16_t fres = 0;
    volatile INTERRUPT_CONFIG_t irq_config;
    
    irq_config.intcon1.value = 0x0000; // Reset all interrupt status bits
    irq_config.intcon2.value = 0x0000; // Reset all interrupt status bits
    irq_config.intcon3.value = 0x0000; // Reset all interrupt status bits
    irq_config.intcon4.value = 0x0000; // Reset all interrupt status bits
    irq_config.inttreg.value = 0x0000; // Reset all interrupt status bits
    
    irq_config.inttreg.bits.VHOLD = INTTREG_VHOLD_ENABLED;           // Enable Vector Number Capture 
    
    irq_config.intcon2.bits.AIVTEN = INTCON2_AIVTEN_DISABLED;   // Disable alternate interrupt vector table
    irq_config.intcon2.bits.GIE = INTCON2_GIE_ENABLE;           // Enable global interrupts
    
    fres = gsirq_irq_initialize(irq_config);
    fres &= gsirq_soft_traps_initialize(0, 0, 0);
    

    return(fres);
}
