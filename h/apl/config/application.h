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
/*!application.h
 *****************************************************************************
 * File:   application.h
 *
 * Summary:
 * Globally defines the APPLICATION_t data structure
 *
 * Description:	
 * Most applications require a certain set of high-level information to set basic 
 * parameters for internal tasks and functions as well as status information. These 
 * parameters are consolidated in the APPLICATION_t data structure, which 
 * is 100% user defined. The status, settings and data broadcast data structures
 * added to the APPLICITON_t data structure should be considered as template only 
 * and can be edited and modified as necessary. 
 * 
 * This file is shared between master and slave project to keep the application status 
 * information in synchronization.
 *
 * References:
 * -
 *
 * See also:
 * 
 * Revision history: 
 * 04/10/19     Initial version
 * Author: M91406
 * Comments:
 *****************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APL_APPLICATION_SETTINGS_AND_DATA_H_
#define	_APL_APPLICATION_SETTINGS_AND_DATA_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "apl/apl.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


    
/*!APPLICATION_STATUS_t
 *****************************************************************************
 * 
 * Summary:
 * Common and specific application-level status flags
 *
 * Description:	
 * This data structure provides status flag bits specifying most recent results
 * of the fault handler and other sections of the user firmware.
 * 
 * Bit <15> is reserved for a global fault flag bit indicating that any fault
 * condition of the level NOTICE, WARNING or FAULT has been detected. These flag
 * bit is an unspecific indication on global level only.
 * 
 * Specific information about which part of the firmware has detected a fault 
 * condition, if there is only one or more fault conditions of the same type pending
 * and additional information about root cause and significance of every single one
 * of them is stored in the individual FAULT_OBJECT of the fault handler.
 *
 * APPLICATION_FAULT_STATUS_BIT_FIELD_t defines individual status flag bits, 
 * which can directly be addressed (set and cleared by software individually)
 * 
 * APPLICATION_FAULT_STATUS_FLAGS_t merges the single-bit data structure into 
 * an unsigned 16-bit value to also allow to apply bit masks or ease the process of 
 * resetting the entire data structure.
 * 
 * APPLICATION_STATUS_t is the data structure, which holds the status flag bits 
 * and other parameters about the most recent status of the application.
 * 
 * See also:
 * 
 *****************************************************************************/

typedef enum {
    STAT_BIT_DUMMY_0 = 0b0,     // Dummy value 0
    STAT_BIT_DUMMY_1 = 0b1      // Dummy value 1
}STAT_BIT_DUMMY_e;   // Battery connected/disconnected status bit 

typedef struct {
    volatile unsigned: 1;               // Bit 1: (reserved)
    volatile unsigned: 1;               // Bit 1: (reserved)
    volatile unsigned: 1;               // Bit 2: (reserved)
    volatile unsigned: 1;               // Bit 3: (reserved)
    volatile unsigned: 1;               // Bit 4: (reserved)
    volatile unsigned: 1;               // Bit 5: (reserved)
    volatile unsigned: 1;               // Bit 6: (reserved)
    volatile unsigned: 1;               // Bit 7: (reserved)
    volatile unsigned: 1;               // Bit 8:  (reserved)
    volatile unsigned: 1;               // Bit 9:  (reserved)
    volatile unsigned: 1;               // Bit 10: (reserved)
    volatile unsigned: 1;               // Bit 11: (reserved)
    volatile unsigned: 1;               // Bit 12: (reserved)
    volatile unsigned: 1;               // Bit 13: (reserved)
    volatile bool temp_warning: 1;      // Bit 14:  Status flag distribution indicating a temperature warning condition 
	volatile bool critical_fault :1;    // Bit #15: Status flag distribution indicating a critical fault condition (forcing power converters to shut down)
}SYSTEM_STATUS_BITS_t; // Internal system status flag bits

typedef union {
    volatile uint16_t value; // 16-bit wide access to status bit field
    volatile SYSTEM_STATUS_BITS_t flags; // single bit access to status bit field
} SYSTEM_STATUS_t; // Internal system status of converters and control signals


typedef enum {
    SYSTEM_MODE_FAULT      = 0b0000000000000000, // power supply is turned off and MCU is running in fault mode
    SYSTEM_MODE_OFF        = 0b0000000000000001, // power supply is turned off and MCU is running in idle mode
    SYSTEM_MODE_ON         = 0b0000000000000010, // System is powered by source and performing normal function
    SYSTEM_MODE_STANDBY    = 0b0000000000000100  // System completely turned off and MCU is on standby power
} SYSTEM_MODE_FLAG_BITS_e;

typedef union 
{
	volatile uint16_t value; // buffer for 16-bit word read/write operations
	volatile SYSTEM_MODE_FLAG_BITS_e flags; // data structure for single bit addressing operations
} SYSTEM_MODE_t;


typedef struct {

    volatile SYSTEM_STATUS_t system_status; // converter and port status
    volatile SYSTEM_MODE_t system_mode; // system operating mode classification
    
}APPLICATION_t; // Data structure defining application settings, status flags and recent data


// Global application data structure 
extern volatile APPLICATION_t application;


// Initialization of the application data structure
extern volatile uint16_t init_ApplicationSettings(void);



#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* _APL_APPLICATION_SETTINGS_H_ */

