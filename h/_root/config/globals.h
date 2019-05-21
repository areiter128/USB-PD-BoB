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

/*!globals.h
 * ***********************************************************************************************
 * File:   globals.h
 * Author: M91406
 * 
 * Summary:
 * Global variables are published here
 * 
 * Description:
 * Global variables, function prototypes and other declarations are published globally by referencing 
 * to external declarations in other project files. 
 * 
 * History:
 * 07/28/2017	File created
 * ***********************************************************************************************/

#ifndef PROJECT_GLOBAL_DECLARATIONS_H
#define	PROJECT_GLOBAL_DECLARATIONS_H


/* ***********************************************************************************************
 * DEFAULT INCLUDES
 * ***********************************************************************************************/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "_root/generic/fdrv_FaultHandler.h"
#include "_root/generic/fdrv_TrapHandler.h"
#include "_root/generic/task_manager.h"
#include "_root/generic/task_scheduler.h"

/* ***********************************************************************************************
 * PROJECT SPECIFIC INCLUDES
 * ***********************************************************************************************/

#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"
#include "sfl/sfl.h"

/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/

/*!SPECIAL_FUNCTION_REGISTER_t
 *****************************************************************************
 * 
 * Summary:
 * Universal masking data structure to conveniently address any default 
 * 16-bit wide Special Function Registers (SFRs)
 *
 * Description:	
 * This data structure is an empty frame which can be used as data mask
 * for local copies of or pointers to specific registers for operations
 * requiring single-bit manipulations within a 16-bit wide register
 *
 * See also:
 * 
 *****************************************************************************/

 typedef struct
 {
     volatile uint16_t bit0:1;	// Bit #0:  generic bit placeholder bit #0
     volatile uint16_t bit1:1;	// Bit #1:  generic bit placeholder bit #1
     volatile uint16_t bit2:1;	// Bit #2:  generic bit placeholder bit #2
     volatile uint16_t bit3:1;	// Bit #3:  generic bit placeholder bit #3
     volatile uint16_t bit4:1;	// Bit #4:  generic bit placeholder bit #4
     volatile uint16_t bit5:1;	// Bit #5:  generic bit placeholder bit #5
     volatile uint16_t bit6:1;	// Bit #6:  generic bit placeholder bit #6
     volatile uint16_t bit7:1;	// Bit #7:  generic bit placeholder bit #7
     
     volatile uint16_t bit8:1;	// Bit #8:  generic bit placeholder bit #8
     volatile uint16_t bit9:1;	// Bit #9:  generic bit placeholder bit #9
     volatile uint16_t bit10:1;	// Bit #11:  generic bit placeholder bit #10
     volatile uint16_t bit11:1;	// Bit #11:  generic bit placeholder bit #11
     volatile uint16_t bit12:1;	// Bit #12:  generic bit placeholder bit #12
     volatile uint16_t bit13:1;	// Bit #13:  generic bit placeholder bit #13
     volatile uint16_t bit14:1;	// Bit #14:  generic bit placeholder bit #14
     volatile uint16_t bit15:1;	// Bit #15:  generic bit placeholder bit #15
 }__attribute__((packed)) SFR16b_FRAME_t;
 
typedef union 
{
	volatile uint16_t reg_block;    // buffer for 16-bit word read/write operations
	volatile SFR16b_FRAME_t flags;  // data structure for single bit addressing operations
}SPECIAL_FUNCTION_REGISTER_t;

    

#endif	/* PROJECT_GLOBAL_DECLARATIONS_H */

// EOF
