/*
 * File:   adc.c
 * Author: M91281
 *
 * Created on April 15, 2019, 1:47 PM
 */



#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mcal/mcal.h"
#include "hal/hal.h"


#define PWM_PRE_SST_DURATION    6250 

volatile uint16_t start_pwm(void);
void PWM_Initialize (void);

volatile uint16_t initialize_pwm(void) {
    
    volatile uint16_t fres = 0;
    
    PWM_Initialize();

//    start_pwm();                        // Enable PWM1, PWM5 modules and run soft-start 
    
    // Setting up ADC Trigger 1 events 
    PG1EVTLbits.ADTR1PS     = 0x0;        // Create ADC Trigger 1 events with post scaler = 1:1
    PG1EVTLbits.ADTR1EN1    = 1;           // PG1TRIGA register compare event is enabled as trigger source for ADC Trigger 1
    PG1EVTLbits.UPDTRG      = 0x3;         // A write of the PG1TRIGA register automatically sets the UPDATE bit  
    PG1TRIGA                = TRIGA1_IOUT; // Setting TRIGA compare level for PWM1 for average output current sampling
    
    PG5EVTLbits.ADTR1PS     = 0x0;        // Create ADC Trigger 1 events with post scaler = 1:1
    PG5EVTLbits.ADTR1EN1    = 1;           // PG5TRIGA register compare event is enabled as trigger source for ADC Trigger 1
    PG5EVTLbits.UPDTRG      = 0x3;         // A write of the PG5TRIGA register automatically sets the UPDATE bit  
    PG5TRIGA                = TRIGA5_IOUT; // Setting TRIGA compare level for PWM5 for average output current sampling
    
    // Enable trigger for ADC inputs 
    ADTRIG2Lbits.TRGSRC9   = 0x04;  // PWM1 trigger is enabled for AN9  
    ADTRIG4Hbits.TRGSRC18  = 0x0C;  // PWM5 trigger is enabled for AN18

    fres &= hspwm_enable_pwm(BUCKH1_PGx_CHANNEL, true);
    fres &= hspwm_enable_pwm(BOOSTH1_PGx_CHANNEL, true);
    fres &= hspwm_enable_pwm(BUCKH2_PGx_CHANNEL, true);
    fres &= hspwm_enable_pwm(BOOSTH2_PGx_CHANNEL, true);

    
    return(fres); // ToDo: need function execution success validation
    
}

/* ***************************************************************************************************
 * ToDo: Quick 'n' Dirty Soft Start (don't do this at home, kids!
 * ***************************************************************************************************/

extern volatile uint16_t timer1_expired;
volatile uint16_t softstart_counter;
extern volatile uint16_t SoftStartFinished;
volatile uint16_t PWM5_enabled = 0;


volatile uint16_t start_pwm(void)
{
    volatile uint16_t i=0;
    
    PG1CONLbits.ON = 0b1;           // PWM1 Module is enabled - buck
    PG2CONLbits.ON = 0b1;           // PWM2 Module is enabled - boost
        
    // Wait for Auxiliary PLL to lock
    while (ACLKCON1bits.APLLCK != 1);
    
    // Insert additional delay to keep PWML1, PWML2 active long enough and internal PWM signal to stabilize
//    timer1_expired = 0;
//    start_timer1(PWM_PRE_SST_DURATION);
//    while (!timer1_expired);        // Wait TIMER1 to finish
//    stop_timer1();
    for(i=PWM_PRE_SST_DURATION; i>0; i--);
    
    IFS4bits.PWM1IF     = 0;        // Clearing PWM1 interrupt flag -> the location of this command matters with respect of the phase between PWM1 & PWM5 ??
    IEC4bits.PWM1IE     = 1;        // Enabling PWM1 interrupt
  
    
    
//    while (!PWM5_enabled);          
    
    // Insert additional delay to keep PWML5 and PWML7 active long enough
//    timer1_expired = 0;
//    start_timer1(PWM_PRE_SST_DURATION);
//    while (!timer1_expired);
//    stop_timer1();
    for(i=PWM_PRE_SST_DURATION; i>0; i--);
       
    // Release buck-leg PWM outputs
    PG1IOCONLbits.OVRENL = 0b0;     // User Override disabled for PWM1L Pin bit
    PG1IOCONLbits.OVRENH = 0b0;     // User Override disabled for PWM1H Pin bit
        
    PG5IOCONLbits.OVRENL = 0b0;     // User Override disabled for PWM5L Pin bit
    PG5IOCONLbits.OVRENH = 0b0;     // User Override disabled for PWM5H Pin bit
        
    softstart_counter = 0;
    
    while (!SoftStartFinished);
    
    // Release PWM outputs for low-side boost-legs
    PG2IOCONLbits.SWAP   = 1;       // Swap PWM2H - PWM2L signals
    PG2IOCONLbits.OVRENL = 0b0;     // User Override disabled for PWM2L Pin bit
    PG2IOCONLbits.OVRENH = 0b0;     // User Override disabled for PWM2H Pin bit

    PG7IOCONLbits.SWAP   = 1;       // Swap PWM7H - PWM7L signals
    PG7IOCONLbits.OVRENL = 0b0;     // User Override disabled for PWM7L Pin bit
    PG7IOCONLbits.OVRENH = 0b0;     // User Override disabled for PWM7H Pin bit

    return(1);
}


void PWM_Initialize (void)
{
    // MCLKSEL AFPLLO - Auxiliary Clock with PLL Enabled; HRERR disabled; LOCK disabled; DIVSEL 1:2; 
    PCLKCON = 0x03;
    // FSCL 0; 
    FSCL = 0x00;
    // FSMINPER 0; 
    FSMINPER = 0x00;
    // MPHASE 0; 
    MPHASE = 0x00;
    // MDC 0; 
    MDC = 0x00;
    // MPER 16; 
    MPER = 0x10;
    // LFSR 0; 
    LFSR = 0x00;
    // CTA7EN disabled; CTA8EN disabled; CTA1EN disabled; CTA2EN disabled; CTA5EN disabled; CTA6EN disabled; CTA3EN disabled; CTA4EN disabled; 
    CMBTRIGL = 0x00;
    // CTB8EN disabled; CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB7EN disabled; CTB6EN disabled; CTB5EN disabled; CTB4EN disabled; 
    CMBTRIGH = 0x00;
    // PWMLFA PWMS1 or PWMS2;; S1APOL Positive logic; S2APOL Positive logic; PWMLFAD No Assignment; PWMS1A PWM1H; PWMS2A PWM1H; 
    LOGCONA = 0x00;
    // PWMLFB PWMS1 | PWMS2; S2BPOL Positive logic; PWMLFBD No Assignment; S1BPOL Positive logic; PWMS2B PWM1H; PWMS1B PWM1H; 
    LOGCONB = 0x00;
    // PWMLFC PWMS1 | PWMS2; PWMLFCD No Assignment; S2CPOL Positive logic; S1CPOL Positive logic; PWMS1C PWM1H; PWMS2C PWM1H; 
    LOGCONC = 0x00;
    // PWMS1D PWM1H; S1DPOL Positive logic; PWMLFD PWMS1 | PWMS2; PWMLFDD No Assignment; S2DPOL Positive logic; PWMS2D PWM1H; 
    LOGCOND = 0x00;
    // PWMS1E PWM1H; PWMS2E PWM1H; S1EPOL Positive logic; PWMLFE PWMS1 | PWMS2; S2EPOL Positive logic; PWMLFED No Assignment; 
    LOGCONE = 0x00;
    // S1FPOL Positive logic; PWMS2F PWM1H; PWMS1F PWM1H; S2FPOL Positive logic; PWMLFFD No Assignment; PWMLFF PWMS1 | PWMS2; 
    LOGCONF = 0x00;
    // EVTASEL PGTRGSEL bits; EVTASYNC Not synchronized; EVTAPOL Active-high; EVTAPGS PG1; EVTASTRD Stretched to 8 PWM clock cycles minimum; EVTAOEN disabled; 
    PWMEVTA = 0x00;
    // EVTBPGS PG1; EVTBSYNC Not synchronized; EVTBPOL Active-high; EVTBSEL PGTRGSEL bits; EVTBSTRD Stretched to 8 PWM clock cycles minimum; EVTBOEN disabled; 
    PWMEVTB = 0x00;
    // EVTCPGS PG1; EVTCPOL Active-high; EVTCSEL PGTRGSEL bits; EVTCSTRD Stretched to 8 PWM clock cycles minimum; EVTCSYNC Not synchronized; EVTCOEN disabled; 
    PWMEVTC = 0x00;
    // EVTDOEN disabled; EVTDSTRD Stretched to 8 PWM clock cycles minimum; EVTDPOL Active-high; EVTDPGS PG1; EVTDSEL PGTRGSEL bits; EVTDSYNC Not synchronized; 
    PWMEVTD = 0x00;
    // EVTEOEN disabled; EVTEPOL Active-high; EVTEPGS PG1; EVTESTRD Stretched to 8 PWM clock cycles minimum; EVTESEL PGTRGSEL bits; EVTESYNC Not synchronized; 
    PWMEVTE = 0x00;
    // EVTFPOL Active-high; EVTFPGS PG1; EVTFSTRD Stretched to 8 PWM clock cycles minimum; EVTFSEL PGTRGSEL bits; EVTFOEN disabled; EVTFSYNC Not synchronized; 
    PWMEVTF = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG1CONH = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG2CONH = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG5CONH = 0x00;
    // MSTEN disabled; TRGMOD Single trigger mode; SOCS Self-trigger; UPDMOD SOC update; MPHSEL disabled; MPERSEL disabled; MDCSEL disabled; 
    PG7CONH = 0x00;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG1STAT = 0x00;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG2STAT = 0x00;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG5STAT = 0x00;
    // TRSET disabled; UPDREQ disabled; CLEVT disabled; TRCLR disabled; CAP disabled; SEVT disabled; FFEVT disabled; UPDATE disabled; FLTEVT disabled; 
    PG7STAT = 0x00;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH enabled; OVRENL enabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 1; 
    PG1IOCONL = 0x3400;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH enabled; OVRENL enabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG2IOCONL = 0x3000;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH enabled; OVRENL enabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 1; 
    PG5IOCONL = 0x3400;
    // FLTDAT 0; DBDAT 0; SWAP disabled; OVRENH enabled; OVRENL enabled; OSYNC User output overrides are synchronized to the local PWM time base; CLMOD disabled; FFDAT 0; CLDAT 0; OVRDAT 0; 
    PG7IOCONL = 0x3000;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
    PG1IOCONH = 0x0C;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
    PG2IOCONH = 0x0C;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
    PG5IOCONH = 0x0C;
    // PENL enabled; DTCMPSEL PCI Sync Logic; PMOD Complementary; POLL Active-high; PENH enabled; CAPSRC Software; POLH Active-high; 
    PG7IOCONH = 0x0C;
    // UPDTRG Duty Cycle; ADTR1PS 1:1; PGTRGSEL EOC event; ADTR1EN3 disabled; ADTR1EN1 enabled; ADTR1EN2 disabled; 
    PG1EVTL = 0x108;
    // UPDTRG Duty Cycle; ADTR1PS 1:1; PGTRGSEL EOC event; ADTR1EN3 disabled; ADTR1EN1 disabled; ADTR1EN2 disabled; 
    PG2EVTL = 0x08;
    // UPDTRG Duty Cycle; ADTR1PS 1:1; PGTRGSEL EOC event; ADTR1EN3 disabled; ADTR1EN1 disabled; ADTR1EN2 disabled; 
    PG5EVTL = 0x08;
    // UPDTRG Duty Cycle; ADTR1PS 1:1; PGTRGSEL EOC event; ADTR1EN3 disabled; ADTR1EN1 disabled; ADTR1EN2 disabled; 
    PG7EVTL = 0x08;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG1EVTH = 0x00;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG2EVTH = 0x00;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG5EVTH = 0x00;
    // ADTR2EN1 disabled; IEVTSEL EOC; SIEN disabled; FFIEN disabled; ADTR1OFS None; CLIEN disabled; FLTIEN disabled; ADTR2EN2 disabled; ADTR2EN3 disabled; 
    PG7EVTH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1FPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5FPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG7FPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG1FPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2FPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5FPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG7FPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1CLPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2CLPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5CLPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG7CLPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG1CLPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2CLPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5CLPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG7CLPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1FFPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2FFPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5FFPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG7FFPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG1FFPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2FFPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5FFPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG7FFPCIH = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG1SPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG2SPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG5SPCIL = 0x00;
    // PSS Tied to 0; PPS Not inverted; SWTERM disabled; PSYNC disabled; TERM Manual Terminate; AQPS Not inverted; AQSS None; TSYNCDIS PWM EOC; 
    PG7SPCIL = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG1SPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG2SPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG5SPCIH = 0x00;
    // PCIGT disabled; TQPS Not inverted; SWPCI Drives '0'; BPEN disabled; TQSS None; SWPCIM PCI acceptance logic; BPSEL PWM Generator 1; ACP Level-sensitive; 
    PG7SPCIH = 0x00;
    // LEB 0; 
    PG1LEBL = 0x00;
    // LEB 0; 
    PG2LEBL = 0x00;
    // LEB 0; 
    PG5LEBL = 0x00;
    // LEB 0; 
    PG7LEBL = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG1LEBH = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG2LEBH = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG5LEBH = 0x00;
    // PWMPCI 1; PLR disabled; PLF disabled; PHR disabled; PHF disabled; 
    PG7LEBH = 0x00;
    // PHASE 0; 
    PG1PHASE = 0x00;
    // PHASE 0; 
    PG2PHASE = 0x00;
    // PHASE 0; 
    PG5PHASE = 0x00;
    // PHASE 0; 
    PG7PHASE = 0x00;
    // DC 554; 
    PG1DC = 0x22A;
    // DC 135; 
    PG2DC = 0x87;
    // DC 554; 
    PG5DC = 0x22A;
    // DC 137; 
    PG7DC = 0x89;
    // DCA 0; 
    PG1DCA = 0x00;
    // DCA 0; 
    PG2DCA = 0x00;
    // DCA 0; 
    PG5DCA = 0x00;
    // DCA 0; 
    PG7DCA = 0x00;
    // PER 1388; 
    PG1PER = 0x56C;
    // PER 1388; 
    PG2PER = 0x56C;
    // PER 1388; 
    PG5PER = 0x56C;
    // PER 1388; 
    PG7PER = 0x56C;
    // TRIGA 250; 
    PG1TRIGA = 0xFA;
    // TRIGA 0; 
    PG2TRIGA = 0x00;
    // TRIGA 0; 
    PG5TRIGA = 0x00;
    // TRIGA 0; 
    PG7TRIGA = 0x00;
    // TRIGB 0; 
    PG1TRIGB = 0x00;
    // TRIGB 0; 
    PG2TRIGB = 0x00;
    // TRIGB 0; 
    PG5TRIGB = 0x00;
    // TRIGB 0; 
    PG7TRIGB = 0x00;
    // TRIGC 0; 
    PG1TRIGC = 0x00;
    // TRIGC 0; 
    PG2TRIGC = 0x00;
    // TRIGC 0; 
    PG5TRIGC = 0x00;
    // TRIGC 0; 
    PG7TRIGC = 0x00;
    // DTL 50; 
    PG1DTL = 0x32;
    // DTL 0; 
    PG2DTL = 0x00;
    // DTL 50; 
    PG5DTL = 0x32;
    // DTL 0; 
    PG7DTL = 0x00;
    // DTH 50; 
    PG1DTH = 0x32;
    // DTH 0; 
    PG2DTH = 0x00;
    // DTH 50; 
    PG5DTH = 0x32;
    // DTH 0; 
    PG7DTH = 0x00;
   
    PG2CONHbits.SOCS = 0x1; // PWM2 to be triggered by PWM1
    PG7CONHbits.SOCS = 0x1; // PWM7 to be triggered by PWM5
    
    PG1IOCONLbits.OVRDAT = 0b01;    // PWMH override value = 0, PWML override value = 1
    PG5IOCONLbits.OVRDAT = 0b01;    // PWMH override value = 0, PWML override value = 1
    PG2IOCONLbits.OVRDAT = 0b00;    // PWMH override value = 0, PWML override value = 0 
    PG7IOCONLbits.OVRDAT = 0b00;    // PWMH override value = 0, PWML override value = 0
    
    // Configuring and enabling PWM1 interrupt ->  used for soft-start timing and also to enable PWM5 as well as PWM7
    PG1EVTHbits.IEVTSEL = 0b01;     // Trig A compare event interrupts CPU 
    BUCKH2_PWM_IP    = 5;           // Setting PWM1 interrupt priority
      
    
    // Write configuration
    PG1TRIGA    = TRIGA_LEVEL;              // This should ensure approx. 50% shift between 4SWBB_12 and 4SWBB_57      
    
    BUCKH2_PGx_DTH      = DEAD_TIME_RISING_EDGE;
    BUCKH2_PGx_DTL      = DEAD_TIME_FALLING_EDGE;
    BUCKH2_PGx_PER      = SWITCHING_PERIOD;
    BUCKH2_PGx_PHASE    = PWM_PHASE_1;
    BUCKH2_PGx_DC       = MIN_DUTY_CYCLE;
    
    BUCKH1_PGx_DTH      = DEAD_TIME_RISING_EDGE;
    BUCKH1_PGx_DTL      = DEAD_TIME_FALLING_EDGE;
    BUCKH1_PGx_PER      = SWITCHING_PERIOD;
    BUCKH1_PGx_PHASE    = PWM_PHASE_5;
    BUCKH1_PGx_DC       = MIN_DUTY_CYCLE;
        
    BOOSTH2_PGx_DTH      = DEAD_TIME_RISING_EDGE;
    BOOSTH2_PGx_DTL      = DEAD_TIME_FALLING_EDGE;
    BOOSTH2_PGx_PER      = SWITCHING_PERIOD;
    BOOSTH2_PGx_PHASE    = PWM_PHASE_2;
    BOOSTH2_PGx_DC       = DUTY_CYCLE_2;
    
    BOOSTH1_PGx_DTH      = DEAD_TIME_RISING_EDGE;
    BOOSTH1_PGx_DTL      = DEAD_TIME_FALLING_EDGE;
    BOOSTH1_PGx_PER      = SWITCHING_PERIOD;
    BOOSTH1_PGx_PHASE    = PWM_PHASE_7;
    BOOSTH1_PGx_DC       = DUTY_CYCLE_7;
   
    // Clamping duty cycle values
    if (PG1DC < MIN_DUTY_CYCLE)             PG1DC = MIN_DUTY_CYCLE;
    if (PG1DC > MAX_DUTY_CYCLE_PWM1_SST)    PG1DC = MAX_DUTY_CYCLE_PWM1_SST;
    if (PG5DC < MIN_DUTY_CYCLE)             PG5DC = MIN_DUTY_CYCLE;
    if (PG5DC > MAX_DUTY_CYCLE_PWM1_SST)    PG5DC = MAX_DUTY_CYCLE_PWM1_SST;
    
    if (PG2DC < MIN_DUTY_CYCLE)             PG2DC = MIN_DUTY_CYCLE;
    //if (PG2DC > MAX_DUTY_CYCLE_PWM2_SST)    PG2DC = MAX_DUTY_CYCLE_PWM2_SST;
    if (PG7DC < MIN_DUTY_CYCLE)             PG7DC = MIN_DUTY_CYCLE;
    //if (PG7DC > MAX_DUTY_CYCLE_PWM2_SST)    PG7DC = MAX_DUTY_CYCLE_PWM2_SST;
    
    // HREN enabled; MODSEL Variable Phase; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG1CONL = 0x89;
    // HREN enabled; MODSEL Variable Phase; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG5CONL = 0x89;
    // HREN enabled; MODSEL Variable Phase; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG2CONL = 0x89;
    // HREN enabled; MODSEL Variable Phase; TRGCNT 1; CLKSEL Master clock; ON disabled; 
    PG7CONL = 0x89;
}

void __attribute__((__interrupt__, no_auto_psv)) _BUCKH2_PWM_Interrupt(void)
{
           
    // ToDo: Questionable code... when PWM not enabled this ISR will never be triggered
    if (!PWM5_enabled)
    {
        PG5CONLbits.ON = 0b1;  // PWM5 (buck) Module is enabled
        PG7CONLbits.ON = 0b1;  // PWM7 (boost) Module is enabled
        PWM5_enabled = 1;  
    } 
    
    if ( (++softstart_counter == SST_PERIOD) && PWM5_enabled )
    {
        softstart_counter = 0;
        if (BUCKH2_PGx_DC <= MAX_DUTY_CYCLE_PWM1_SST) {
            BUCKH2_PGx_DC++;
            BUCKH2_PGx_DC++; 
        }
        else {
            BUCKH2_PWM_IE      = 0;    // Disabling PWM1 interrupt when MAX_DUTY_CYCLE_PWM1_SST is reached
            SoftStartFinished  = 1; 
        }
    }
    
    BUCKH2_PWM_IF     = 0;                // Clearing PWM1 interrupt flag
}


