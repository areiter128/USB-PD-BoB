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
/*!task_LED_Green.h
 * ***************************************************************************
 * File:   fdrv_FunctionPDStack.h
 * Author: James Schaffer - C41076
 * 
 * Summary:
 * PD Stack support functions
 * 
 * Description:
 * 
 * History:
 * 05/23/2019	File created
 * ***************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_FUNCTION_DRIVER_PD_STACK_H
#define	APL_FUNCTION_DRIVER_PD_STACK_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/
typedef enum
{
    PDSTACK_ENABLED = 0b1,  // LED function is enabled
    PDSTACK_DISABLED = 0b0  // LED function is disabled
}PDSTACK_ENABLE_e;

typedef struct{

	volatile unsigned :1;	// Bit #0:  Reserved
    volatile unsigned :1;	// Bit #1:  Reserved
    volatile unsigned :1;	// Bit #2:  Reserved
    volatile unsigned :1;	// Bit #3:  Reserved
	volatile unsigned :1;	// Bit #4:  Reserved
	volatile unsigned :1;	// Bit #5:  Reserved
	volatile unsigned :1;	// Bit #6:  Reserved
	volatile unsigned :1;	// Bit #7:  Reserved
    
	volatile unsigned :1;	// Bit #8:  Reserved
	volatile unsigned :1;	// Bit #9:  Reserved
	volatile unsigned :1;	// Bit #10: Reserved
	volatile unsigned :1;	// Bit #11: Reserved
	volatile unsigned :1;	// Bit #12: Reserved
	volatile unsigned :1;	// Bit #13: Reserved
	volatile unsigned :1;	// Bit #14:  Reserved
    volatile unsigned :1;	// Bit #15:  Reserved
    volatile PDSTACK_ENABLE_e enable:1;	// Bit #15: flag bit used to enable/disable the PD Stack function
} FUNCTION_PD_STACK_STATUS_BIT_FIELD_t;

typedef union 
{
	volatile uint16_t value; // buffer for 16-bit word read/write operations
	volatile FUNCTION_PD_STACK_STATUS_BIT_FIELD_t flags; // data structure for single bit addressing operations
} FUNCTION_PD_STACK_STATUS_FLAGS_t;

typedef struct
{
    volatile FUNCTION_PD_STACK_STATUS_FLAGS_t status;  // used to globally publish the PD Stack status
    volatile uint16_t counter;  // internal tick counter
}FUNCTION_PD_STACK_CONFIG_t;


/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
// (none)


#endif	/* APL_FUNCTION_DRIVER_ON_BOARD_LED_H */

