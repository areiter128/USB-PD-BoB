/* ****************************************************************************************************
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
 * *****************************************************************************************************
 * File:   devcfg_irq.h
 * Author: M91406
 * Comments: User configuration of the interrupt controller
 * Revision history: v1.0, first release
 * *****************************************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _DEVICE_CONFIGURATION_IRQ_H
#define	_DEVICE_CONFIGURATION_IRQ_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "mcal/mcal.h"

/* Peripheral/Signal Interrupt Settings */

#define ADCORE_EISEL_TAD        8 // Number of Tad cycles by which the interrupts should be generated early to conversion completion (0-8)
#define SHRADCORE_EISEL_TAD     8 // Number of Tad cycles by which the interrupts should be generated early to conversion completion (0-8)

#define FB_VOUT1_ENABLE         true // enable/disable usage of this analog input
#define FB_VOUT1_ISR_PRIORITY   4 // interrupt priority for this analog input
#define FB_VOUT1_ISR_ENABLE     true // interrupt enable/disable for this analog input
#define FB_VOUT1_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_VOUT1_PGxTRIGy       BOOSTH1_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_VOUT1_TRGSRC         BOOSTH1_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_IIN1_ENABLE          false // enable/disable usage of this analog input
#define FB_IIN1_ISR_PRIORITY    5 // interrupt priority for this analog input
#define FB_IIN1_ISR_ENABLE      false // interrupt enable/disable for this analog input
#define FB_IIN1_EIE_ENABLE      true // early interrupt enable/disable for this analog input
#define FB_IIN1_PGxTRIGy        BUCKH1_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_IIN1_TRGSRC          BUCKH1_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_IOUT1_ENABLE         true // enable/disable usage of this analog input
#define FB_IOUT1_ISR_PRIORITY   5 // interrupt priority for this analog input
#define FB_IOUT1_ISR_ENABLE     true // interrupt priority for this analog input
#define FB_IOUT1_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_IOUT1_PGxTRIGy       BUCKH1_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_IOUT1_TRGSRC         BUCKH1_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_TEMP1_ENABLE         true // enable/disable usage of this analog input
#define FB_TEMP1_ISR_PRIORITY   2 // interrupt priority for this analog input
#define FB_TEMP1_ISR_ENABLE     false // interrupt priority for this analog input
#define FB_TEMP1_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_TEMP1_PGxTRIGy       BUCKH1_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_TEMP1_TRGSRC         BUCKH1_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_VOUT2_ENABLE         false // enable/disable usage of this analog input
#define FB_VOUT2_ISR_PRIORITY   4 // interrupt priority for this analog input
#define FB_VOUT2_ISR_ENABLE     true // interrupt priority for this analog input
#define FB_VOUT2_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_VOUT2_PGxTRIGy       BOOSTH2_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_VOUT2_TRGSRC         BOOSTH2_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_IIN2_ENABLE          false // enable/disable usage of this analog input
#define FB_IIN2_ISR_PRIORITY    5 // interrupt priority for this analog input
#define FB_IIN2_ISR_ENABLE      false // interrupt priority for this analog input
#define FB_IIN2_EIE_ENABLE      true // early interrupt enable/disable for this analog input
#define FB_IIN2_PGxTRIGy        BUCKH2_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_IIN2_TRGSRC          BUCKH2_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_IOUT2_ENABLE         false // enable/disable usage of this analog input
#define FB_IOUT2_ISR_PRIORITY   5 // interrupt priority for this analog input
#define FB_IOUT2_ISR_ENABLE     true // interrupt priority for this analog input
#define FB_IOUT2_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_IOUT2_PGxTRIGy       BUCKH2_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_IOUT2_TRGSRC         BUCKH2_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_TEMP2_ENABLE         true // enable/disable usage of this analog input
#define FB_TEMP2_ISR_PRIORITY   2     // interrupt priority for this analog input
#define FB_TEMP2_ISR_ENABLE     false // interrupt priority for this analog input
#define FB_TEMP2_EIE_ENABLE     true // early interrupt enable/disable for this analog input
#define FB_TEMP2_PGxTRIGy       BUCKH2_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_TEMP2_TRGSRC         BUCKH2_ADTRGSRC_1 // ADC Trigger Source of this analog input

#define FB_VBAT_ENABLE          true // enable/disable usage of this analog input
#define FB_VBAT_ISR_PRIORITY    3 // interrupt priority for this analog input
#define FB_VBAT_ISR_ENABLE      false // interrupt priority for this analog input
#define FB_VBAT_EIE_ENABLE      true // early interrupt enable/disable for this analog input
#define FB_VBAT_PGxTRIGy        BOOSTH1_PGxTRIGA // ADC Trigger 1 Compare Register for current feedback
#define FB_VBAT_TRGSRC          BOOSTH1_ADTRGSRC_1 // ADC Trigger Source of this analog input


// Buck-Leg #1 ADC Trigger Generator Settings
#define BUCKH1_PGxEVT_ADTR1EN   0b001   // PGxTRIGA register compare event is enabled as trigger source for ADC Trigger 1
#define BUCKH1_PGxEVT_ADTR2EN   0b000   // All PGxTRIGn registers compare events are disabled as trigger source for ADC Trigger 2
#define BUCKH1_PGxEVT_ADTR1PS   0b00001 // ADC Trigger 1 Postscaler Selection: Trigger will be generated every other cycle
#define BUCKH1_PGxEVT_ADTR1OFS  0b00000 // ADC Trigger 1 Offset Selection: Offset by 0 trigger event
#define BUCKH1_PGxEVT_EVTSEL    0b11    // Time base interrupts are disabled


// Boost-Leg #1 ADC Trigger Generator Settings
#define BOOSTH1_PGxEVT_ADTR1EN  0b001   // PGxTRIGA register compare event is enabled as trigger source for ADC Trigger 1
#define BOOSTH1_PGxEVT_ADTR1PS  0b00001 // ADC Trigger 1 Postscaler Selection: Trigger will be generated every other cycle
#define BOOSTH1_PGxEVT_ADTR1OFS 0b00000 // ADC Trigger 1 Offset Selection: Offset by 0 trigger event (triggered in the first cycle)
#define BOOSTH1_PGxEVT_ADTR2EN  0b000   // All PGxTRIGn registers compare events are disabled as trigger source for ADC Trigger 2
#define BOOSTH1_PGxEVT_EVTSEL   0b11    // Time base interrupts are disabled

// Buck-Leg #2 ADC Trigger Generator Settings
#define BUCKH2_PGxEVT_ADTR1EN   0b001   // PGxTRIGA register compare event is enabled as trigger source for ADC Trigger 1
#define BUCKH2_PGxEVT_ADTR1PS   0b00001 // ADC Trigger 1 Postscaler Selection: Trigger will be generated every other cycle
#define BUCKH2_PGxEVT_ADTR1OFS  0b00001 // ADC Trigger 1 Offset Selection: Offset by 1 trigger event
#define BUCKH2_PGxEVT_ADTR2EN   0b000   // All PGxTRIGn registers compare events are disabled as trigger source for ADC Trigger 2
#define BUCKH2_PGxEVT_EVTSEL    0b11    // Time base interrupts are disabled

// Boost-Leg #2 ADC Trigger Generator Settings
#define BOOSTH2_PGxEVT_ADTR1EN  0b001   // PGxTRIGA register compare event is enabled as trigger source for ADC Trigger 1
#define BOOSTH2_PGxEVT_ADTR1PS  0b00001 // ADC Trigger 1 Postscaler Selection: Trigger will be generated every other cycle
#define BOOSTH2_PGxEVT_ADTR1OFS 0b00001 // ADC Trigger 1 Offset Selection: Offset by 1 trigger event 
#define BOOSTH2_PGxEVT_ADTR2EN  0b000   // All PGxTRIGn registers compare events are disabled as trigger source for ADC Trigger 2
#define BOOSTH2_PGxEVT_EVTSEL   0b11    // Time base interrupts are disabled



/* INTCON1 Settings */

#define IRQ_INTCON1_CFG    (REG_INTCON1_NSTDIS_ENABLED | \
                            REG_INTCON1_OVATE_DISABLED | \
                            REG_INTCON1_OVBTE_DISABLED | \
                            REG_INTCON1_COVTE_DISABLED | \
                            REG_INTCON1_OVAERR_FLAG_CLEAR | \
                            REG_INTCON1_OVBERR_FLAG_CLEAR | \
                            REG_INTCON1_COVAERR_FLAG_CLEAR | \
                            REG_INTCON1_COVBERR_FLAG_CLEAR \
                            )

/* INTCON2 Settings */

#define IRQ_INTCON2_CFG    (REG_INTCON2_GIE_ENABLED | \
                            REG_INTCON2_STAT_DISI_CLEAR | \
                            REG_INTCON2_SWTRAP_DISABLED | \
                            REG_INTCON2_AIVTEN_DISABLE | \
                            REG_INTCON2_INT3EP_RISING | \
                            REG_INTCON2_INT2EP_RISING | \
                            REG_INTCON2_INT1EP_RISING | \
                            REG_INTCON2_INT0EP_RISING \
                            )

/* INTCON3 Settings */

#define IRQ_INTCON3_CFG    (REG_INTCON3_CAN_CLEAR | \
                            REG_INTCON3_NAE_CLEAR | \
                            REG_INTCON3_CAN2_CLEAR | \
                            REG_INTCON3_DOOVR_CLEAR | \
                            REG_INTCON3_APLL_CLEAR \
                            )

/* INTCON4 Settings */

#define IRQ_INTCON4_CFG    (REG_INTCON4_ECCDBE_CLEAR | \
                            REG_INTCON4_SGHT_CLEAR \
                            )

#endif	/* _DEVICE_CONFIGURATION_IRQ_H */

