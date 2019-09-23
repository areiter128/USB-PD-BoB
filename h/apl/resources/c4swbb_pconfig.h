/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   c4swbb_pconfig.h
 * Author: M91406
 * Comments: 
 * This file is used to provide default pre-configurations of peripherals required to
 * drive a 4-switch buck/boost converter.
 * 
 * THIS FILE NEEDS TO BE USED WITH THE SMPS MCAL PERIPHERAL LIBRARY FOR dsPIC
 * 
 * Revision history: 
 * 9/12/2019    initial release
 */

// This is a guard condition so that contents of this file are not included more than once.  
#ifndef C4SWBB_PERIPHERAL_CONFIG_H
#define	C4SWBB_PERIPHERAL_CONFIG_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "mcal/mcal.h"
#include "apl/resources/c4swbb_control.h" 

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


/*!4-Switch Buck/Boost PWM Configuration 
 * ***********************************************************************************************
 * Dedicated, generic PWM configuration of a dsPIC33C-type PWM to drive a 4-switch buck boost
 * converter.
 * 
 * 
 * 
 * **********************************************************************************************/

/* BUCK LEG */

/*!PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW

    bit 15 ON: Enable bit: 0 = PWM Generator is not enabled
    bit 14 Reserved: Maintain as ?0?
    bit 13-11 Unimplemented: Read as ?0?
    bit 10-8 TRGCNT[2:0]: Trigger Count Select bits: 000 = PWM Generator produces one PWM cycle after triggered
    bit 7 HREN: PWM Generator x High-Resolution Enable bit: 1 = PWM Generator x operates in High-Resolution mode(2)
    bit 6-5 Unimplemented: Read as ?0?
    bit 4-3 CLKSEL[1:0]: Clock Selection bits: 01 = PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    bit 2-0 MODSEL[2:0]: Mode Selection bits: 001 = Variable Phase PWM mode
 */

#define C4SWBB_BUCKLEG_PGxCONL  (   REG_PGCON_MODSEL_VARIABLE_PHASE | \
                                    REG_PGCON_CLKSEL_BY_MCLKSEL | \
                                    REG_PGCON_HREN_HIGH_RES | \
                                    REG_PGCON_TRGCNT_1_PWM_CYCLES | \
                                    REG_PGCON_ON_PWM_DISABLED \
                                )   // 0b0000000010001001

/*!PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH

    bit 15 MDCSEL: Master Duty Cycle Register Select bit: 0 = PWM Generator uses PGxDC register
    bit 14 MPERSEL: Master Period Register Select bit: 1 = PWM Generator uses MPER register
    bit 13 MPHSEL: Master Phase Register Select bit: 0 = PWM Generator uses PGxPHASE register
    bit 12 Unimplemented: Read as ?0?
    bit 11 MSTEN: Master Update Enable bit: 0 = PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    bit 10-8 UPDMOD[2:0]: PWM Buffer Update Mode Selection bits: 001 = Immediate update
        Data registers immediately, or as soon as possible, if UPDATE = 1. The UPDATE status bit will
        be cleared automatically after the update occurs (UPDATE = 1). The UPDATE status bit will be
        cleared automatically after the update occurs.
    bit 7 Reserved: Maintain as ?0?:
    bit 6 TRGMOD: PWM Generator Trigger Mode Selection bit: 1 = PWM Generator operates in Retriggerable mode
    bit 5-4 Unimplemented: Read as ?0?
    bit 3-0 SOCS[3:0]: Start-of-Cycle Selection bits(1,2,3): 0000 = Local EOC ? PWM Generator is self-triggered
 */

#define C4SWBB_BUCKLEG_PGxCONH  ( \
                                    REG_PGCON_SOCS_LOCAL_EOC | \
                                    REG_PGCON_TRGMOD_REPEAT | \
                                    REG_PGCON_UPDMOD_IMMEDIATE | \
                                    REG_PGCON_MSTEN_NO_BROADCAST | \
                                    REG_PGCON_MPHSEL_INDEPENDENT | \
                                    REG_PGCON_MPERSEL_INDEPENDENT | \
                                    REG_PGCON_MDCSEL_INDEPENDENT \
                                )   // 0b0100000101000000

/*!PGxSTAT: PWM GENERATOR x STATUS REGISTER

    Always clear all status bits

 */
#define C4SWBB_BUCKLEG_PGxSTAT      0b0000000000000000

/*!PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW

    bit 15 CLMOD: Current-Limit Mode Select bit: 0 = If PCI current limit is active, then the CLDAT[1:0] bits define the PWM output levels
    bit 14 SWAP: Swap PWM Signals to PWMxH and PWMxL Device Pins bit: 0 = PWMxH/L signals are mapped to their respective pins
    bit 13 OVRENH: User Override Enable for PWMxH Pin bit: 1 = OVRDAT1 provides data for output on the PWMxH pin
    bit 12 OVRENL: User Override Enable for PWMxL Pin bit: 1 = OVRDAT0 provides data for output on the PWMxL pin
    bit 11-10 OVRDAT[1:0]: Data for PWMxH/PWMxL Pins if Override is Enabled bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 9-8 OSYNC[1:0]: User Output Override Synchronization Control bits: 
        00 = User output overrides via the OVRENH/L and OVRDAT[1:0] bits are synchronized to the 
             local PWM time base (next Start-of-Cycle)
    bit 7-6 FLTDAT[1:0]: Data for PWMxH/PWMxL Pins if Fault Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 5-4 CLDAT[1:0]: Data for PWMxH/PWMxL Pins if Current-Limit Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 3-2 FFDAT[1:0]: Data for PWMxH/PWMxL Pins if Feed-Forward Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 1-0 DBDAT[1:0]: Data for PWMxH/PWMxL Pins if Debug Mode is Active bits: 00 PWMxH = LOW, PWMxL = LOW
 */
#define C4SWBB_BUCKLEG_PGxIOCONL    (   REG_IOCON_CLMOD_DISABLED | \
                                        REG_IOCON_SWAP_DISABLED | \
                                        REG_IOCON_OSYNC_PWM | \
                                        REG_IOCON_OVREN_COMP_SET | \
                                        REG_IOCON_OVRDAT_LOW_LOW | \
                                        REG_IOCON_FLTDAT_LOW_LOW | \
                                        REG_IOCON_CLDAT_LOW_LOW | \
                                        REG_IOCON_FFDAT_LOW_LOW | \
                                        REG_IOCON_DBDAT_LOW_LOW \
                                    )  // 0b0011000000000000

/*!PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH

    bit 15 Unimplemented: Read as ?0?
    bit 14-12 CAPSRC[2:0]: Time Base Capture Source Selection bits(1): 000 = No hardware source selected for time base capture ? software only
    bit 11-9 Unimplemented: Read as ?0?
    bit 8 DTCMPSEL: Dead-Time Compensation Select bit: 0 = Dead-time compensation is controlled by PCI Sync logic
    bit 7-6 Unimplemented: Read as ?0?
    bit 5-4 PMOD[1:0]: PWM Generator Output Mode Selection bits: 00 = PWM Generator outputs operate in Complementary mode
    bit 3 PENH: PWMxH Output Port Enable bit: 1 = PWM Generator controls the PWMxH output pin
    bit 2 PENL: PWMxL Output Port Enable bit: 1 = PWM Generator controls the PWMxL output pin
    bit 1 POLH: PWMxH Output Polarity bit: 0 = Output pin is active-high
    bit 0 POLL: PWMxL Output Polarity bit: 0 = Output pin is active-high
 */
#define C4SWBB_BUCKLEG_PGxIOCONH    (   REG_IOCON_POLH_ACTIVE_LOW | \
                                        REG_IOCON_POLL_ACTIVE_LOW | \
                                        REG_IOCON_PENx_COMP_PGx | \
                                        REG_IOCON_PMOD_COMPLEMENTARY | \
                                        REG_IOCON_DTCMPSEL_PCI_SYNC | \
                                        REG_IOCON_CAPSRC_NONE \
                                    )  // 0b0000000000001100

/*!PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW

    bit 15-11 ADTR1PS[4:0]: ADC Trigger 1 Postscaler Selection bits: 00000 = 1:1
    bit 10 ADTR1EN3: ADC Trigger 1 Source is PGxTRIGC Compare Event Enable bit: 0 = PGxTRIGC register compare event is disabled as trigger source for ADC Trigger 1
    bit 9 ADTR1EN2: ADC Trigger 1 Source is PGxTRIGB Compare Event Enable bit: 0 = PGxTRIGB register compare event is disabled as trigger source for ADC Trigger 1
    bit 8 ADTR1EN1: ADC Trigger 1 Source is PGxTRIGA Compare Event Enable bit: 0 = PGxTRIGA register compare event is disabled as trigger source for ADC Trigger 1
    bit 7-5 Unimplemented: Read as ?0?
    bit 4-3 UPDTRG[1:0]: Update Trigger Select bits: 11 = A write of the PGxTRIGA register automatically sets the UPDATE bit
    bit 2-0 PGTRGSEL[2:0]: PWM Generator Trigger Output Selection bits(1): 001 = PGxTRIGA compare event is the PWM Generator trigger
 */
#define C4SWBB_BUCKLEG_PGxEVTL      (   REG_PGEVT_ADTR1PS_POSTSCALE_1 | \
                                        REG_PGEVT_ADTR1EN3_PGxTRIGC_DISABLED | \
                                        REG_PGEVT_ADTR1EN2_PGxTRIGB_DISABLED | \
                                        REG_PGEVT_ADTR1EN1_PGxTRIGA_ENABLED | \
                                        REG_PGEVT_UPDTRG_PGxTRIGA | \
                                        REG_PGEVT_PGTRGSEL_PGxTRIGA \
                                    )  // 0b0000000000011001

/*!PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH

    bit 15 FLTIEN: PCI Fault Interrupt Enable bit(1): 0 = Fault interrupt is disabled
    bit 14 CLIEN: PCI Current-Limit Interrupt Enable bit(2): 0 = Current-limit interrupt is disabled
    bit 13 FFIEN: PCI Feed-Forward Interrupt Enable bit(3): 0 = Feed-forward interrupt is disabled
    bit 12 SIEN: PCI Sync Interrupt Enable bit(4): 0 = Sync interrupt is disabled
    bit 11-10 Unimplemented: Read as ?0?
    bit 9-8 IEVTSEL[1:0]: Interrupt Event Selection bits: 
        11 = Time base interrupts are disabled 
             (Sync, Fault, current-limit and feed-forward events can be independently enabled)
    bit 7 ADTR2EN3: ADC Trigger 2 Source is PGxTRIGC Compare Event Enable bit: 0 = PGxTRIGC register compare event is disabled as trigger source for ADC Trigger 2
    bit 6 ADTR2EN2: ADC Trigger 2 Source is PGxTRIGB Compare Event Enable bit: 0 = PGxTRIGB register compare event is disabled as trigger source for ADC Trigger 2
    bit 5 ADTR2EN1: ADC Trigger 2 Source is PGxTRIGA Compare Event Enable bit: 0 = PGxTRIGA register compare event is disabled as trigger source for ADC Trigger 2 
    bit 4-0 ADTR1OFS[4:0]: ADC Trigger 1 Offset Selection bits: 00000 = No offset 
 */
#define C4SWBB_BUCKLEG_PGxEVTH      (   REG_PGEVT_FLTIEN_DISABLED | \
                                        REG_PGEVT_CLIEN_DISABLED | \
                                        REG_PGEVT_FFIEN_DISABLED | \
                                        REG_PGEVT_SIEN_DISABLED | \
                                        REG_PGEVT_IEVTSEL_NONE | \
                                        REG_PGEVT_ADTR2EN3_PGxTRIGC_DISABLED | \
                                        REG_PGEVT_ADTR2EN2_PGxTRIGB_DISABLED | \
                                        REG_PGEVT_ADTR2EN1_PGxTRIGA_DISABLED | \
                                        REG_PGEVT_ADTR1OFS_OFFSET_EVENTS_0 \
                                    )   // 0b0000001100000000

/*!PGxyPCIL: PWM GENERATOR x CL PCI REGISTER LOW (x = PWM GENERATOR #; CL = Current Limit)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BUCKLEG_PGxCLPCIL    (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x FF PCI REGISTER HIGH (x = PWM GENERATOR #; CL = Current Limit)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BUCKLEG_PGxCLPCIH    (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x FF PCI REGISTER LOW (x = PWM GENERATOR #; FF = Feed Forward)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BUCKLEG_PGxFFPCIL    (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x FF PCI REGISTER HIGH (x = PWM GENERATOR #; FF = Feed Forward)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BUCKLEG_PGxFFPCIH    (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x F PCI REGISTER LOW (x = PWM GENERATOR #; F = Fault)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BUCKLEG_PGxFPCIL     (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x F PCI REGISTER HIGH (x = PWM GENERATOR #; F = Fault)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BUCKLEG_PGxFPCIH     (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x S PCI REGISTER LOW (x = PWM GENERATOR #; S = Debug/Software)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */

#define C4SWBB_BUCKLEG_PGxSPCIL     (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x S PCI REGISTER HIGH (x = PWM GENERATOR #; S = Debug/Software)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BUCKLEG_PGxSPCIH     (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxLEBH: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH

    bit 15-11 Unimplemented: Read as ?0?
    bit 10-8 PWMPCI[2:0]: PWM Source for PCI Selection bits: 000 = PWM Generator #1 output is made available to PCI logic
    bit 7-4 Unimplemented: Read as ?0?
    bit 3 PHR: PWMxH Rising Edge Trigger Enable bit: 1 = Rising edge of PWMxH will trigger the LEB duration counter
    bit 2 PHF: PWMxH Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxH
    bit 1 PLR: PWMxL Rising Edge Trigger Enable bit: 0 = LEB ignores the rising edge of PWMxL
    bit 0 PLF: PWMxL Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxL
 */
#define C4SWBB_BUCKLEG_PGxLEBH      (   REG_LEBCON_PWMPCI_PG1 | \
                                        REG_PGxLEBCON_LEBTRG_PHR_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PHF_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PLR_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PLF_DISABLE \
                                    )  // 0b0000000000000000

/*!PWM Generator Timing Registers

Description: 

    The following registers will be configured by the driver routines using user values
    defined in the hardware abstraction layer. Teh values efined below have been added
    for compatability reasons only and are used to initially reset registers to a known 
    state.

    PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW
    PGxPHASE: PWM GENERATOR x PHASE REGISTER
    PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
    PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER
    PGxPER: PWM GENERATOR x PERIOD REGISTER
    PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
    PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER HIGH
    PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PGxTRIGB: PWM GENERATOR x TRIGGER A REGISTER
    PGxTRIGC: PWM GENERATOR x TRIGGER A REGISTER
    PGxCAP: PWM GENERATOR x CAPTURE REGISTER

 */
#define C4SWBB_BUCKLEG_PGxLEBL      0b0000000000000000
#define C4SWBB_BUCKLEG_PGxPHASE     0b0000000000000000
#define C4SWBB_BUCKLEG_PGxDC        0b0000000000000000
#define C4SWBB_BUCKLEG_PGxDC_LIMIT  0b0000000000011111
#define C4SWBB_BUCKLEG_PGxDCA       0b0000000000000000
#define C4SWBB_BUCKLEG_PGxPER       0b0000000000000000
#define C4SWBB_BUCKLEG_PGxPER_LIMIT 0b0000000001111111
#define C4SWBB_BUCKLEG_PGxDTL       0b0000000000000000
#define C4SWBB_BUCKLEG_PGxDTH       0b0000000000000000
#define C4SWBB_BUCKLEG_PGxTRIGA     0b0000000000000000
#define C4SWBB_BUCKLEG_PGxTRIGB     0b0000000000000000
#define C4SWBB_BUCKLEG_PGxTRIGC     0b0000000000000000
#define C4SWBB_BUCKLEG_PGxCAP       0b0000000000000000



/* BOOST LEG */

/*!PGxCONL: PWM GENERATOR x CONTROL REGISTER LOW

    bit 15 ON: Enable bit: 0 = PWM Generator is not enabled
    bit 14 Reserved: Maintain as ?0?
    bit 13-11 Unimplemented: Read as ?0?
    bit 10-8 TRGCNT[2:0]: Trigger Count Select bits: 000 = PWM Generator produces one PWM cycle after triggered
    bit 7 HREN: PWM Generator x High-Resolution Enable bit: 1 = PWM Generator x operates in High-Resolution mode(2)
    bit 6-5 Unimplemented: Read as ?0?
    bit 4-3 CLKSEL[1:0]: Clock Selection bits: 01 = PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    bit 2-0 MODSEL[2:0]: Mode Selection bits: 001 = Variable Phase PWM mode
 */

#define C4SWBB_BOOSTLEG_PGxCONL (   REG_PGCON_MODSEL_VARIABLE_PHASE | \
                                    REG_PGCON_CLKSEL_BY_MCLKSEL | \
                                    REG_PGCON_HREN_HIGH_RES | \
                                    REG_PGCON_TRGCNT_1_PWM_CYCLES | \
                                    REG_PGCON_ON_PWM_DISABLED \
                                )   // 0b0000000010001001

/*!PGxCONH: PWM GENERATOR x CONTROL REGISTER HIGH

    bit 15 MDCSEL: Master Duty Cycle Register Select bit: 0 = PWM Generator uses PGxDC register
    bit 14 MPERSEL: Master Period Register Select bit: 1 = PWM Generator uses MPER register
    bit 13 MPHSEL: Master Phase Register Select bit: 0 = PWM Generator uses PGxPHASE register
    bit 12 Unimplemented: Read as ?0?
    bit 11 MSTEN: Master Update Enable bit: 0 = PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    bit 10-8 UPDMOD[2:0]: PWM Buffer Update Mode Selection bits: 001 = Immediate update
        Data registers immediately, or as soon as possible, if UPDATE = 1. The UPDATE status bit will
        be cleared automatically after the update occurs (UPDATE = 1). The UPDATE status bit will be
        cleared automatically after the update occurs.
    bit 7 Reserved: Maintain as ?0?:
    bit 6 TRGMOD: PWM Generator Trigger Mode Selection bit: 1 = PWM Generator operates in Retriggerable mode
    bit 5-4 Unimplemented: Read as ?0?
    bit 3-0 SOCS[3:0]: Start-of-Cycle Selection bits(1,2,3): 0000 = Local EOC ? PWM Generator is self-triggered
 */

#define C4SWBB_BOOSTLEG_PGxCONH     (   REG_PGCON_SOCS_LOCAL_EOC | \
                                        REG_PGCON_TRGMOD_REPEAT | \
                                        REG_PGCON_UPDMOD_IMMEDIATE | \
                                        REG_PGCON_MSTEN_NO_BROADCAST | \
                                        REG_PGCON_MPHSEL_INDEPENDENT | \
                                        REG_PGCON_MPERSEL_INDEPENDENT | \
                                        REG_PGCON_MDCSEL_INDEPENDENT \
                                    )   // 0b0100000101000000

/*!PGxSTAT: PWM GENERATOR x STATUS REGISTER

    Always clear all status bits

 */
#define C4SWBB_BOOSTLEG_PGxSTAT      0b0000000000000000

/*!PGxIOCONL: PWM GENERATOR x I/O CONTROL REGISTER LOW

    bit 15 CLMOD: Current-Limit Mode Select bit: 0 = If PCI current limit is active, then the CLDAT[1:0] bits define the PWM output levels
    bit 14 SWAP: Swap PWM Signals to PWMxH and PWMxL Device Pins bit: 0 = PWMxH/L signals are mapped to their respective pins
    bit 13 OVRENH: User Override Enable for PWMxH Pin bit: 1 = OVRDAT1 provides data for output on the PWMxH pin
    bit 12 OVRENL: User Override Enable for PWMxL Pin bit: 1 = OVRDAT0 provides data for output on the PWMxL pin
    bit 11-10 OVRDAT[1:0]: Data for PWMxH/PWMxL Pins if Override is Enabled bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 9-8 OSYNC[1:0]: User Output Override Synchronization Control bits: 
        00 = User output overrides via the OVRENH/L and OVRDAT[1:0] bits are synchronized to the 
             local PWM time base (next Start-of-Cycle)
    bit 7-6 FLTDAT[1:0]: Data for PWMxH/PWMxL Pins if Fault Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 5-4 CLDAT[1:0]: Data for PWMxH/PWMxL Pins if Current-Limit Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 3-2 FFDAT[1:0]: Data for PWMxH/PWMxL Pins if Feed-Forward Event is Active bits: 00 PWMxH = LOW, PWMxL = LOW
    bit 1-0 DBDAT[1:0]: Data for PWMxH/PWMxL Pins if Debug Mode is Active bits: 00 PWMxH = LOW, PWMxL = LOW
 */
#define C4SWBB_BOOSTLEG_PGxIOCONL   (   REG_IOCON_CLMOD_DISABLED | \
                                        REG_IOCON_SWAP_DISABLED | \
                                        REG_IOCON_OSYNC_PWM | \
                                        REG_IOCON_OVREN_COMP_SET | \
                                        REG_IOCON_OVRDAT_LOW_LOW | \
                                        REG_IOCON_FLTDAT_LOW_LOW | \
                                        REG_IOCON_CLDAT_LOW_LOW | \
                                        REG_IOCON_FFDAT_LOW_LOW | \
                                        REG_IOCON_DBDAT_LOW_LOW \
                                    )  // 0b0011000000000000

/*!PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH

    bit 15 Unimplemented: Read as ?0?
    bit 14-12 CAPSRC[2:0]: Time Base Capture Source Selection bits(1): 000 = No hardware source selected for time base capture ? software only
    bit 11-9 Unimplemented: Read as ?0?
    bit 8 DTCMPSEL: Dead-Time Compensation Select bit: 0 = Dead-time compensation is controlled by PCI Sync logic
    bit 7-6 Unimplemented: Read as ?0?
    bit 5-4 PMOD[1:0]: PWM Generator Output Mode Selection bits: 00 = PWM Generator outputs operate in Complementary mode
    bit 3 PENH: PWMxH Output Port Enable bit: 1 = PWM Generator controls the PWMxH output pin
    bit 2 PENL: PWMxL Output Port Enable bit: 1 = PWM Generator controls the PWMxL output pin
    bit 1 POLH: PWMxH Output Polarity bit: 0 = Output pin is active-high
    bit 0 POLL: PWMxL Output Polarity bit: 0 = Output pin is active-high
 */
#define C4SWBB_BOOSTLEG_PGxIOCONH   (   REG_IOCON_POLH_ACTIVE_LOW | \
                                        REG_IOCON_POLL_ACTIVE_LOW | \
                                        REG_IOCON_PENx_COMP_PGx | \
                                        REG_IOCON_PMOD_COMPLEMENTARY | \
                                        REG_IOCON_DTCMPSEL_PCI_SYNC | \
                                        REG_IOCON_CAPSRC_NONE \
                                    )  // 0b0000000000001100

/*!PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW

    bit 15-11 ADTR1PS[4:0]: ADC Trigger 1 Postscaler Selection bits: 00000 = 1:1
    bit 10 ADTR1EN3: ADC Trigger 1 Source is PGxTRIGC Compare Event Enable bit: 0 = PGxTRIGC register compare event is disabled as trigger source for ADC Trigger 1
    bit 9 ADTR1EN2: ADC Trigger 1 Source is PGxTRIGB Compare Event Enable bit: 0 = PGxTRIGB register compare event is disabled as trigger source for ADC Trigger 1
    bit 8 ADTR1EN1: ADC Trigger 1 Source is PGxTRIGA Compare Event Enable bit: 0 = PGxTRIGA register compare event is disabled as trigger source for ADC Trigger 1
    bit 7-5 Unimplemented: Read as ?0?
    bit 4-3 UPDTRG[1:0]: Update Trigger Select bits: 11 = A write of the PGxTRIGA register automatically sets the UPDATE bit
    bit 2-0 PGTRGSEL[2:0]: PWM Generator Trigger Output Selection bits(1): 001 = PGxTRIGA compare event is the PWM Generator trigger
 */
#define C4SWBB_BOOSTLEG_PGxEVTL     (   REG_PGEVT_ADTR1PS_POSTSCALE_1 | \
                                        REG_PGEVT_ADTR1EN3_PGxTRIGC_DISABLED | \
                                        REG_PGEVT_ADTR1EN2_PGxTRIGB_DISABLED | \
                                        REG_PGEVT_ADTR1EN1_PGxTRIGA_ENABLED | \
                                        REG_PGEVT_UPDTRG_PGxTRIGA | \
                                        REG_PGEVT_PGTRGSEL_PGxTRIGA \
                                    )  // 0b0000000000011001

/*!PGxEVTH: PWM GENERATOR x EVENT REGISTER HIGH

    bit 15 FLTIEN: PCI Fault Interrupt Enable bit(1): 0 = Fault interrupt is disabled
    bit 14 CLIEN: PCI Current-Limit Interrupt Enable bit(2): 0 = Current-limit interrupt is disabled
    bit 13 FFIEN: PCI Feed-Forward Interrupt Enable bit(3): 0 = Feed-forward interrupt is disabled
    bit 12 SIEN: PCI Sync Interrupt Enable bit(4): 0 = Sync interrupt is disabled
    bit 11-10 Unimplemented: Read as ?0?
    bit 9-8 IEVTSEL[1:0]: Interrupt Event Selection bits: 
        11 = Time base interrupts are disabled 
             (Sync, Fault, current-limit and feed-forward events can be independently enabled)
    bit 7 ADTR2EN3: ADC Trigger 2 Source is PGxTRIGC Compare Event Enable bit: 0 = PGxTRIGC register compare event is disabled as trigger source for ADC Trigger 2
    bit 6 ADTR2EN2: ADC Trigger 2 Source is PGxTRIGB Compare Event Enable bit: 0 = PGxTRIGB register compare event is disabled as trigger source for ADC Trigger 2
    bit 5 ADTR2EN1: ADC Trigger 2 Source is PGxTRIGA Compare Event Enable bit: 0 = PGxTRIGA register compare event is disabled as trigger source for ADC Trigger 2 
    bit 4-0 ADTR1OFS[4:0]: ADC Trigger 1 Offset Selection bits: 00000 = No offset 
 */
#define C4SWBB_BOOSTLEG_PGxEVTH     (   REG_PGEVT_FLTIEN_DISABLED | \
                                        REG_PGEVT_CLIEN_DISABLED | \
                                        REG_PGEVT_FFIEN_DISABLED | \
                                        REG_PGEVT_SIEN_DISABLED | \
                                        REG_PGEVT_IEVTSEL_NONE | \
                                        REG_PGEVT_ADTR2EN3_PGxTRIGC_DISABLED | \
                                        REG_PGEVT_ADTR2EN2_PGxTRIGB_DISABLED | \
                                        REG_PGEVT_ADTR2EN1_PGxTRIGA_DISABLED | \
                                        REG_PGEVT_ADTR1OFS_OFFSET_EVENTS_0 \
                                    )   // 0b0000001100000000

/*!PGxyPCIL: PWM GENERATOR x CL PCI REGISTER LOW (x = PWM GENERATOR #; CL = Current Limit)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BOOSTLEG_PGxCLPCIL   (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x FF PCI REGISTER HIGH (x = PWM GENERATOR #; CL = Current Limit)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BOOSTLEG_PGxCLPCIH   (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x FF PCI REGISTER LOW (x = PWM GENERATOR #; FF = Feed Forward)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BOOSTLEG_PGxFFPCIL   (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x FF PCI REGISTER HIGH (x = PWM GENERATOR #; FF = Feed Forward)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BOOSTLEG_PGxFFPCIH   (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x F PCI REGISTER LOW (x = PWM GENERATOR #; F = Fault)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */
#define C4SWBB_BOOSTLEG_PGxFPCIL    (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x F PCI REGISTER HIGH (x = PWM GENERATOR #; F = Fault)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BOOSTLEG_PGxFPCIH    (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxyPCIL: PWM GENERATOR x S PCI REGISTER LOW (x = PWM GENERATOR #; S = Debug/Software)

    bit 15 TSYNCDIS: Termination Synchronization Disable bit: 0 = Termination of latched PCI occurs at PWM EOC
    bit 14-12 TERM[2:0]: Termination Event Selection bits: 000 = Manual Terminate: Terminate on a write of ?1? to the SWTERM bit location
    bit 11 AQPS: Acceptance Qualifier Polarity Select bit: 0 = Not inverted
    bit 10-8 AQSS[2:0]: Acceptance Qualifier Source Selection bits: 000 = No acceptance qualifier is used (qualifier forced to ?1?)
    bit 7 SWTERM: PCI Software Termination bit: This bit location always reads as ?0?.
    bit 6 PSYNC: PCI Synchronization Control bit: 0 = PCI source is not synchronized to PWM EOC
    bit 5 PPS: PCI Polarity Select bit: 0 = Not inverted
    bit 4-0 PSS[4:0]: PCI Source Selection bits: 00000 = Tied to ?0?
 */

#define C4SWBB_BOOSTLEG_PGxSPCIL    (   REG_PGxyPCIL_TSYNCDIS_EOC | \
                                        REG_PGxyPCIL_TERM_MANUAL | \
                                        REG_PGxyPCIL_AQPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_AQSS_NONE | \
                                        REG_PGxyPCIL_SWTERM_RUN | \
                                        REG_PGxyPCIL_PSYNC_NONE | \
                                        REG_PGxyPCIL_PPS_NOT_INVERTED | \
                                        REG_PGxyPCIL_PSS_VSS \
                                    )   // 0b0000000000000000

/*!PGxyPCIH: PWM GENERATOR x S PCI REGISTER HIGH (x = PWM GENERATOR #; S = Debug/Software)

    bit 15 BPEN: PCI Bypass Enable bit: 0 = PCI function is not bypassed
    bit 14-12 BPSEL[2:0]: PCI Bypass Source Selection bits(1): 000 = PCI control is sourced from PWM Generator 1 PCI logic when BPEN = 1
    bit 11 Unimplemented: Read as ?0?
    bit 10-8 ACP[2:0]: PCI Acceptance Criteria Selection bits: 000 = Level-sensitive
    bit 7 SWPCI: Software PCI Control bit: 0 = Drives a ?0? to PCI logic assigned to by the SWPCIM[1:0] control bits
    bit 6-5 SWPCIM[1:0]: Software PCI Control Mode bits: 00 = SWPCI bit is assigned to PCI acceptance logic
    bit 4 LATMOD: PCI SR Latch Mode bit: 0 = SR latch is Set-dominant in Latched Acceptance modes
    bit 3 TQPS: Termination Qualifier Polarity Select bit: 0 = Not inverted
    bit 2-0 TQSS[2:0]: Termination Qualifier Source Selection bits: 000 = No termination qualifier used (qualifier forced to ?1?)
 */
#define C4SWBB_BOOSTLEG_PGxSPCIH    (   REG_PGxyPCIH_BPEN_DISABLED | \
                                        REG_PGxyPCIH_BPSEL_PG1 | \
                                        REG_PGxyPCIH_REG_ACP_LEVEL | \
                                        REG_PGxyPCIH_SWPCI_LOW | \
                                        REG_PGxyPCIH_SWPCIM_PCI | \
                                        REG_PGxyPCIH_LATMOD_SET | \
                                        REG_PGxyPCIH_TQPS_NOT_INVERTED | \
                                        REG_PGxyPCIH_TQSS_NONE \
                                    )  // 0b0000000000000000

/*!PGxLEBH: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH

    bit 15-11 Unimplemented: Read as ?0?
    bit 10-8 PWMPCI[2:0]: PWM Source for PCI Selection bits: 000 = PWM Generator #1 output is made available to PCI logic
    bit 7-4 Unimplemented: Read as ?0?
    bit 3 PHR: PWMxH Rising Edge Trigger Enable bit: 1 = Rising edge of PWMxH will trigger the LEB duration counter
    bit 2 PHF: PWMxH Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxH
    bit 1 PLR: PWMxL Rising Edge Trigger Enable bit: 0 = LEB ignores the rising edge of PWMxL
    bit 0 PLF: PWMxL Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxL
 */
#define C4SWBB_BOOSTLEG_PGxLEBH     (   REG_LEBCON_PWMPCI_PG1 | \
                                        REG_PGxLEBCON_LEBTRG_PHR_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PHF_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PLR_DISABLE | \
                                        REG_PGxLEBCON_LEBTRG_PLF_DISABLE \
                                    )  // 0b0000000000000000

/*!PWM Generator Timing Registers

Description: 

    The following registers will be configured by the driver routines using user values
    defined in the hardware abstraction layer. Teh values efined below have been added
    for compatability reasons only and are used to initially reset registers to a known 
    state.

    PGxLEBL: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER LOW
    PGxPHASE: PWM GENERATOR x PHASE REGISTER
    PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
    PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER
    PGxPER: PWM GENERATOR x PERIOD REGISTER
    PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
    PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER HIGH
    PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PGxTRIGB: PWM GENERATOR x TRIGGER A REGISTER
    PGxTRIGC: PWM GENERATOR x TRIGGER A REGISTER
    PGxCAP: PWM GENERATOR x CAPTURE REGISTER

 */
#define C4SWBB_BOOSTLEG_PGxLEBL      0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxPHASE     0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxDC        0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxDC_LIMIT  0b0000000000011111
#define C4SWBB_BOOSTLEG_PGxDCA       0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxPER       0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxPER_LIMIT 0b0000000001111111
#define C4SWBB_BOOSTLEG_PGxDTL       0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxDTH       0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxTRIGA     0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxTRIGB     0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxTRIGC     0b0000000000000000
#define C4SWBB_BOOSTLEG_PGxCAP       0b0000000000000000



/*!4-Switch Buck/Boost ADC Configuration 
 * ***********************************************************************************************
 * Dedicated, generic ADC configuration of a dsPIC33C-type ADC establish a 4-switch buck boost
 * converter control loop.
 * 
 * 
 * 
 * **********************************************************************************************/

/* ADC MODULE BASE REGISTERS */

/*!ADCON1L: ADC CONTROL REGISTER 1 LOW

    bit 15 ADON: ADC Enable bit
    bit 14 Unimplemented: Read as ?0?
    bit 13 ADSIDL: ADC Stop in Idle Mode bit
    bit 12 Unimplemented: Read as ?0?
    bit 11 Reserved: Maintain as ?0?
    bit 10-0 Unimplemented: Read as ?0?
 */
    
#define C4SWBB_ADC_ADCON1L          (   REG_ADCON1L_ADON_DISABLED | \
                                        REG_ADCON1L_ADSIDL_RUN \
                                    )  // 0b0000000000000000

/*!ADCON1H: ADC CONTROL REGISTER 1 HIGH

    bit 15-8 Unimplemented: Read as ?0?
    bit 7 FORM: Fractional Data Output Format bit
    bit 6-5 SHRRES<1:0>: Shared ADC Core Resolution Selection bits
    bit 4-0 Unimplemented: Read as ?0? 
  */
#define C4SWBB_ADC_ADCON1H          (   REG_ADCON1H_FORM_INTEGER | \
                                        REG_ADCON1H_SHRRES_12BIT \
                                    )  // 0b0000000001100000
   
/*!ADCON2L: ADC CONTROL REGISTER 2 LOW

    bit 15 REFCIE: Band Gap and Reference Voltage Ready Common Interrupt Enable bit
    bit 14 REFERCIE: Band Gap or Reference Voltage Error Common Interrupt Enable bit
    bit 13 Unimplemented: Read as ?0?
    bit 12 EIEN: Early Interrupts Enable bit
    bit 11 PTGEN: External Conversion Request Interface bit
    bit 10-8 SHREISEL<2:0>: Shared Core Early Interrupt Time Selection bits(1)
    bit 7 Unimplemented: Read as ?0?
    bit 6-0 SHRADCS<6:0>: Shared ADC Core Input Clock Divider bits
 */
#define C4SWBB_ADC_ADCON2L          (   REG_ADCON2L_REFCIE_ENABLED | \
                                        REG_ADCON2L_REFERCIE_DISABLED | \
                                        REG_ADCON2L_EIEN_ENABLED | \
                                        REG_ADCON2L_PTGEN_DISABLED | \
                                        REG_ADCON2L_SHREISEL_8TAD | \
                                        REG_SHRADCS(1) \
                                    )  // 0b0001011100000001
   
/*!ADCON2H: ADC CONTROL REGISTER 2 HIGH

    bit 15 REFRDY: Band Gap and Reference Voltage Ready Flag bit
    bit 14 REFERR: Band Gap or Reference Voltage Error Flag bit
    bit 13 Unimplemented: Read as ?0?
    bit 12-10 Reserved: Maintain as ?0?
    bit 9-0 SHRSAMC<9:0>: Shared ADC Core Sample Time Selection bits
 */
#define C4SWBB_ADC_ADCON2H          (   REG_ADCON2H_REFRDY_NOT_READY | \
                                        REG_ADCON2H_REFERR_OK | \
                                        REG_ADCON2H_SHRSAMC(10) \
                                    )  // 0b0000000000001000

/*!ADCON3L: ADC CONTROL REGISTER 3 LOW

    bit 15-13 REFSEL<2:0>: ADC Reference Voltage Selection bits
    bit 12 SUSPEND: All ADC Core Triggers Disable bit
    bit 11 SUSPCIE: Suspend All ADC Cores Common Interrupt Enable bit
    bit 10 SUSPRDY: All ADC Cores Suspended Flag bit
    bit 9 SHRSAMP: Shared ADC Core Sampling Direct Control bit
    bit 8 CNVRTCH: Software Individual Channel Conversion Trigger bit
    bit 7 SWLCTRG: Software Level-Sensitive Common Trigger bit
    bit 6 SWCTRG: Software Common Trigger bit
    bit 5-0 CNVCHSEL <5:0>: Channel Number Selection for Software Individual Channel Conversion Trigger bits
 */
#define C4SWBB_ADC_ADCON3L          (   REG_ADCON3L_REFSEL_AVDD_AVSS | \
                                        REG_ADCON3L_SUSPEND_RUN | \
                                        REG_ADCON3L_SUSPCIE_DISABLED | \
                                        REG_ADCON3L_SUSPRDY_RUNNING | \
                                        REG_ADCON3L_SHRSAMP_HWTRIG | \
                                        REG_ADCON3L_CNVRTCH_READY | \
                                        REG_ADCON3L_SWLCTRG_LVLTRG_BY_HW | \
                                        REG_ADCON3L_SWCTRG_READY | \
                                        REG_ADCON3L_CNVCHSEL(0) \
                                    )  // 0b0000000000000000
    
/*!ADCON3H: ADC CONTROL REGISTER 3 HIGH

    bit 15-14 CLKSEL<1:0>: ADC Module Clock Source Selection bits(1)
    bit 13-8 CLKDIV<5:0>: ADC Module Clock Source Divider bits(2)
    bit 7 SHREN: Shared ADC Core Enable bit
    bit 6-2 Unimplemented: Read as ?0?
    bit 1 C1EN: Dedicated ADC Core 1 Enable bits
    bit 0 C0EN: Dedicated ADC Core 0 Enable bits    
 */
#define C4SWBB_ADC_ADCON3H          (   REG_ADCON3H_CLKSEL_AFVCODIV | \
                                        REG_ADCON3H_CLKDIV(1) | \
                                        REG_ADCON3H_SHREN_DISABLED | \
                                        REG_ADCON3H_C1EN_DISABLED | \
                                        REG_ADCON3H_C0EN_DISABLED \
                                    )  // 0b1100000000000000

/*!ADCON4L: ADC CONTROL REGISTER 4 LOW

    bit 15-10 Unimplemented: Read as ?0?
    bit 9-8 Reserved: Must be written as ?0?
    bit 7-2 Unimplemented: Read as ?0?
    bit 1 SAMC1EN: Dedicated ADC Core 1 Conversion Delay Enable bit
    bit 0 SAMC0EN: Dedicated ADC Core 0 Conversion Delay Enable bit        
 */
#define C4SWBB_ADC_ADCON4L          (   REG_SAMC1EN_DISABLED | \
                                        REG_SAMC0EN_DISABLED | \
                                        REG_SYNCTRG1_INDEPENDENT | \
                                        REG_SYNCTRG0_INDEPENDENT \
                                    )  // 0b0000000000000000
    
/*!ADCON4H: ADC CONTROL REGISTER 4 HIGH

    bit 15-4 Unimplemented: Read as ?0?
    bit 3-2 C1CHS<1:0>: Dedicated ADC Core 1 Input Channel Selection bits
    bit 1-0 C0CHS<1:0>: Dedicated ADC Core 0 Input Channel Selection bits        
 */
#define C4SWBB_ADC_ADCON4H          (   REG_ADCON4H_C0CHS_AN0 | \
                                        REG_ADCON4H_C1CHS_AN1 \
                                    )  // 0b0000000000000000

/*!ADCON5L: ADC CONTROL REGISTER 5 LOW

    bit 15 SHRRDY: Shared ADC Core Ready Flag bit
    bit 14-10 Unimplemented: Read as ?0?
    bit 9 C1RDY: Dedicated ADC Core 1 Ready Flag bit
    bit 8 C0RDY: Dedicated ADC Core 0 Ready Flag bit
    bit 7 SHRPWR: Shared ADC Core Power Enable bit
    bit 6-2 Unimplemented: Read as ?0?
    bit 1 C1PWR: Dedicated ADC Core 1 Power Enable bit
    bit 0 C0PWR: Dedicated ADC Core 0 Power Enable bit       
 */
#define C4SWBB_ADC_ADCON5L          (   REG_ADCON5L_SHRRDY_FF | \
                                        REG_ADCON5L_C1RDY_FF | \
                                        REG_ADCON5L_C0RDY_FF | \
                                        REG_ADCON5L_SHRPWR_OFF | \
                                        REG_ADCON5L_C1PWR_OFF | \
                                        REG_ADCON5L_C0PWR_OFF \
                                    )  // 0b0000000000000000
    
/*!ADCON5H: ADC CONTROL REGISTER 5 HIGH

    bit 15-12 Unimplemented: Read as ?0?
    bit 11-8 WARMTIME<3:0>: ADC Dedicated Core x Power-up Delay bits
    bit 7 SHRCIE: Shared ADC Core Ready Common Interrupt Enable bit
    bit 6-2 Unimplemented: Read as ?0?
    bit 1 C1CIE: Dedicated ADC Core 1 Ready Common Interrupt Enable bit
    bit 0 C0CIE: Dedicated ADC Core 0 Ready Common Interrupt Enable bit
 */
#define C4SWBB_ADC_ADCON5H          (   REG_ADCON5H_WARMTIME_CLK_32768 | \
                                        REG_ADCON5H_SHRCIE_DISABLED | \
                                        REG_ADCON5H_C1CIE_DISABLED | \
                                        REG_ADCON5H_C0CIE_DISABLED \
                                    )  // 0b0000111100000000

    
/*!ADCORExL: DEDICATED ADC CORE x CONTROL REGISTER LOW

    bit 15-10 Unimplemented: Read as "0"
    bit 9-0 SAMC<9:0>: Dedicated ADC Core x Conversion Delay Selection bits
 */
#define C4SWBB_ADC_ADCORExL         (   REG_SAMC(2) \
                                    )  // 0b0000000000000000

/*!ADCORExH: DEDICATED ADC CORE x CONTROL REGISTER HIGH

    bit 15-13 Unimplemented: Read as ?0?
    bit 12-10 EISEL<2:0>: ADC Core x Early Interrupt Time Selection bits
    bit 9-8 RES<1:0>: ADC Core x Resolution Selection bits
    bit 7 Unimplemented: Read as ?0?
    bit 6-0 ADCS<6:0>: ADC Core x Input Clock Divider bits
 */
#define C4SWBB_ADC_ADCORExH         (   REG_EISEL_8TAD | \
                                        REG_ADC_RES_12BIT | \
                                        REG_ADCS(2) \
                                    )  // 0b0001111100000000

    
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* C4SWBB_PERIPHERAL_CONFIG_H */

