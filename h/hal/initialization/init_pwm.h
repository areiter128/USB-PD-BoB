/*LICENSE ********************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
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
 * ***************************************************************************/
/*!init_dsp.h
 * *************************************************************************** 
 * File:   init_adc.h
 * Author: m91406
 *
 * Created on March 8, 2019
 * ***************************************************************************/

#ifndef _HAL_INIT_PWM_H_
#define	_HAL_INIT_PWM_H_

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "hal/hal.h"
#include "mcal/mcal.h"

/* ******************************************************************
   Defines for PWM initialization 
 
   All the parameters values are measured in [ticks]
   Input frequency of the PWM module is 500 MHz, i.e. 1 tick = 2 ns
   High resolution mode is NOT enabled
 ********************************************************************/
#define TRIGA_LEVEL                 555     // 555 Trigger A Compare level used to provide pace for soft-start and create offset between the two buck-boost channels

#define SST_PERIOD                  6       // Update PWM cycle period during soft-start in terms of PWM1 interrupts (in this case "ADC Trigger 1" -> 2 PWM1 cycles = 5.5us) 

#define TRIGA1_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM1 & PWM2
#define TRIGA5_IOUT                 0    // TRIGA level for output current sampling on the buck-boost leg driven by PWM5 & PWM7

#define PWM_PHASE_1     500
#define PWM_PHASE_2     500
#define PWM_PHASE_5     500
#define PWM_PHASE_7     500

/*!4-Switch Buck/Boost PWM Configuration 
 * ***********************************************************************************************
 * Dedicated, generic PWM configuration of a dsPIC33C-type PWM to drive a 4-switch buck boost
 * converter.
 * 
 * 
 * 
 * **********************************************************************************************/

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

#define C4SWBB_BUCKLEG_PGxCONL      0b0000000010001001

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

#define C4SWBB_BUCKLEG_PGxCONH      0b0100000101000000

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
#define C4SWBB_BUCKLEG_PGxIOCONL    0b0011000000000000

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
#define C4SWBB_BUCKLEG_PGxIOCONH    0b0000000000001100

/*!PGxEVTL: PWM GENERATOR x EVENT REGISTER LOW

    bit 15-11 ADTR1PS[4:0]: ADC Trigger 1 Postscaler Selection bits: 00000 = 1:1
    bit 10 ADTR1EN3: ADC Trigger 1 Source is PGxTRIGC Compare Event Enable bit: 0 = PGxTRIGC register compare event is disabled as trigger source for ADC Trigger 1
    bit 9 ADTR1EN2: ADC Trigger 1 Source is PGxTRIGB Compare Event Enable bit: 0 = PGxTRIGB register compare event is disabled as trigger source for ADC Trigger 1
    bit 8 ADTR1EN1: ADC Trigger 1 Source is PGxTRIGA Compare Event Enable bit: 0 = PGxTRIGA register compare event is disabled as trigger source for ADC Trigger 1
    bit 7-5 Unimplemented: Read as ?0?
    bit 4-3 UPDTRG[1:0]: Update Trigger Select bits: 11 = A write of the PGxTRIGA register automatically sets the UPDATE bit
    bit 2-0 PGTRGSEL[2:0]: PWM Generator Trigger Output Selection bits(1): 001 = PGxTRIGA compare event is the PWM Generator trigger
 */
#define C4SWBB_BUCKLEG_PGxEVTL      0b0000000000011001

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
#define C4SWBB_BUCKLEG_PGxEVTH      0b0000001100000000

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
#define C4SWBB_BUCKLEG_PGxCLPCIL    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxCLPCIH    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxFFPCIL    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxFFPCIH    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxFPCIL    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxFPCIH     0b0000000000000000

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

#define C4SWBB_BUCKLEG_PGxSPCIL    0b0000000000000000

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
#define C4SWBB_BUCKLEG_PGxSPCIH     0b0000000000000000

/*!PGxLEBH: PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH
 
    bit 15-11 Unimplemented: Read as ?0?
    bit 10-8 PWMPCI[2:0]: PWM Source for PCI Selection bits: 000 = PWM Generator #1 output is made available to PCI logic
    bit 7-4 Unimplemented: Read as ?0?
    bit 3 PHR: PWMxH Rising Edge Trigger Enable bit: 1 = Rising edge of PWMxH will trigger the LEB duration counter
    bit 2 PHF: PWMxH Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxH
    bit 1 PLR: PWMxL Rising Edge Trigger Enable bit: 0 = LEB ignores the rising edge of PWMxL
    bit 0 PLF: PWMxL Falling Edge Trigger Enable bit: 0 = LEB ignores the falling edge of PWMxL
 */
#define C4SWBB_BUCKLEG_PGxLEBH      0b0000000000000000

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


/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
extern volatile uint16_t c4swbb_pwm_initialize(volatile HSPWM_C_CHANNEL_CONFIG_t c4swbb_pwm);
extern volatile uint16_t c4swbb_pwm_enable(void); 
extern volatile uint16_t c4swbb_pwm_disable(void); 
extern volatile uint16_t c4swbb_pwm_hold(void); 
extern volatile uint16_t c4swbb_pwm_release(void); 

#endif	/* _HAL_INIT_PWM_H_ */

