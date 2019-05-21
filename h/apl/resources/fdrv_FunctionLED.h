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
 * File:   task_LED_Green.h
 * Author: M91406
 * 
 * Summary:
 * Header of green LED expander board LED task
 * 
 * Description:
 * This header is used to register a global data structure allowing to edit
 * parameters of the task. It is also used to publish global function calls.
 * 
 * The main task routine is operating the green LED of the expander board by 
 * applying the status setting in the data structure.
 * 
 * History:
 * 05/03/2018	File created
 * ***************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_FUNCTION_DRIVER_ON_BOARD_LED_H
#define	APL_FUNCTION_DRIVER_ON_BOARD_LED_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/

typedef enum
{
    LEDCTRL_LED_STATUS_ON      = 0b00,  // Status of the LED is on (active))
    LEDCTRL_LED_STATUS_OFF     = 0b01,  // Status of the LED is off (inactive)
    LEDCTRL_LED_STATUS_FAILURE = 0b10   // Status of the LED is not matching pin state
}FUNCTION_LED_STATUS_e;

typedef enum
{
    LEDCTRL_PIN_STATUS_LOW     = 0b0,  // Status of the GPIO is LOW
    LEDCTRL_PIN_STATUS_HIGH    = 0b1   // Status of the GPIO is HIGH
}LEDCTRL_PIN_STATUS_e;

typedef enum
{
    LEDCTRL_MODE_TOGGLE = 0b00,     // LED is toggled with 50% on/off time
    LEDCTRL_MODE_DUTY_RATIO = 0b01, // LED is forced on with an user specified on/off duty ratio
    LEDCTRL_MODE_ALWAYS_ON = 0b10,  // LED is forced on with an user specified on/off duty ratio
    LEDCTRL_MODE_ALWAYS_OFF = 0b11  // LED is forced on with an user specified on/off duty ratio
}LEDCTRL_OPERATING_MODE_e;


typedef enum
{
    LEDCTRL_ENABLED = 0b1,  // LED function is enabled
    LEDCTRL_DISABLED = 0b0  // LED function is disabled
}LEDCTRL_ENABLE_e;

typedef struct{

	volatile LEDCTRL_PIN_STATUS_e  pin_status:1;	// Bit #0:  LED control pin HIGH/LOW status
	volatile FUNCTION_LED_STATUS_e led_status:2;	// Bit #<1:2>:  LED On/Off/Failure status
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
	volatile LEDCTRL_OPERATING_MODE_e mode:2;	// Bit #<14:13>: flag bit indicating LED operating mode (forced on/off or toggle))
	volatile LEDCTRL_ENABLE_e enable:1;	// Bit #15: flag bit used to enable/disable the LED function
} FUNCTION_LED_STATUS_BIT_FIELD_t;


typedef union 
{
	volatile uint16_t value; // buffer for 16-bit word read/write operations
	volatile FUNCTION_LED_STATUS_BIT_FIELD_t flags; // data structure for single bit addressing operations
} FUNCTION_LED_STATUS_FLAGS_t;

typedef struct
{
    volatile FUNCTION_LED_STATUS_FLAGS_t status;  // used to globally publish the LED status
    volatile uint16_t period;  // number of scheduler ticks until the status of the LED is toggled
    volatile uint16_t on_time;  // number of scheduler ticks for which the LED will be ON
    volatile uint16_t counter;  // internal tick counter
}FUNCTION_LED_CONFIG_t;


/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
// (none)


#endif	/* APL_FUNCTION_DRIVER_ON_BOARD_LED_H */

