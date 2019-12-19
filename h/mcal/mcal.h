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
/*!mcal.h
 * ***********************************************************************************************
 * File:   mcal.h
 * Author: M91406
 * 
 * Summary:
 * Microcontroller Abstraction Layer header file
 * 
 * Description:
 * This header is used to publish generic peripheral drivers of the MCAL layer. A file, which 
 * needs to access routines of any generic peripheral driver should include this header.
 * 
 * History:
 * 07/28/2017	File created
 * ***********************************************************************************************/

#ifndef MICROCONTROLLER_ABSTRACTION_LAYER_H
#define	MICROCONTROLLER_ABSTRACTION_LAYER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>

/* ***********************************************************************************************
 * INCLUDES
 * ***********************************************************************************************/
/* generic drivers */
#include "../../../plib/p33SMPS_mcal.X/p33SMPS_plib.h"
    
/* ***********************************************************************************************
 * Define a macro in the project properties as filter for hardware specific pin mapping
 * ***********************************************************************************************/
/*
*/

/* Include hardware descriptor file */
#include "mcal/config/devcfg_dsp.h"
#include "mcal/config/devcfg_irq.h"
#include "mcal/config/devcfg_oscillator.h"
#include "mcal/config/devcfg_pinmap.h"

    // Hardware-specific peripheral initialization
#include "mcal/initialization/init_gpio.h"
#include "mcal/initialization/init_irq.h"
#include "mcal/initialization/init_dsp.h"
#include "mcal/initialization/init_timer.h"
#include "mcal/initialization/init_fosc.h"

/* generic peripheral drives */    
#include "dsPIC33C/p33SMPS_irq.h"
#include "dsPIC33C/p33SMPS_dsp.h"
#include "dsPIC33C/p33SMPS_hsadc.h"
#include "dsPIC33C/p33SMPS_hspwm_c.h"
#include "dsPIC33C/p33SMPS_gpio.h"
#include "dsPIC33C/p33SMPS_oscillator.h"
#include "dsPIC33C/p33SMPS_pmd.h"
#include "dsPIC33C/p33SMPS_timer.h"
#include "dsPIC33C/p33SMPS_pps.h"
#include "dsPIC33C/p33SMPS_pmd.h"
#include "dsPIC33C/p33SMPS_mailboxes.h"


/* ***********************************************************************************************
 * GENERIC DEFINES
 * ***********************************************************************************************/
 
    
/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/


#endif	/* MICROCONTROLLER_ABSTRACTION_LAYER_H */

// EOF
