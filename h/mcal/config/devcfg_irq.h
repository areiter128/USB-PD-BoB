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
#include "mcal/mcal.h"

/* INTCON1 Settings */

#define IRQ_INTCON1_CFG    (REG_INTCON1_NSTDIS_ENABLED | \
                            REG_INTCON1_OVATE_DISABLE | \
                            REG_INTCON1_OVBTE_DISABLE | \
                            REG_INTCON1_COVTE_DISABLE | \
                            REG_INTCON1_OVAERR_FLAG_CLEAR | \
                            REG_INTCON1_OVBERR_FLAG_CLEAR | \
                            REG_INTCON1_COVAERR_FLAG_CLEAR | \
                            REG_INTCON1_COVBERR_FLAG_CLEAR \
                            )

/* INTCON2 Settings */

#define IRQ_INTCON2_CFG    (REG_INTCON2_GIE_ENABLE | \
                            REG_INTCON2_STAT_DISI_CLEAR | \
                            REG_INTCON2_SWTRAP_DISABLE | \
                            REG_INTCON2_AIVTEN_DISABLE | \
                            REG_INTCON2_INT4EP_RISING | \
                            REG_INTCON2_INT2EP_RISING | \
                            REG_INTCON2_INT1EP_RISING | \
                            REG_INTCON2_INT0EP_RISING \
                            )

/* INTCON3 Settings */

#define IRQ_INTCON3_CFG    (REG_INTCON3_STAT_CAN_CLEAR | \
                            REG_INTCON3_STAT_NAE_CLEAR | \
                            REG_INTCON3_STAT_CAN2_CLEAR | \
                            REG_INTCON3_STAT_DOOVR_CLEAR | \
                            REG_INTCON3_STAT_APLL_CLEAR \
                            )


#endif	/* _DEVICE_CONFIGURATION_IRQ_H */

