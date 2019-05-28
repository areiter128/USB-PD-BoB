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
/*!task_UART.h
 * ***************************************************************************
 * File:   task_UART.h
 * Author: M91406
 * 
 * Summary:
 * Header of switch button task
 * 
 * Description:
 * This header covers the global data structures, variables and function call 
 * prototypes of the generic SMPS UART communication stack.
 * 
 * History:
 * 05/03/2018	File created
 * ***************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APL_TASK_SMPS_UART_H_
#define	_APL_TASK_SMPS_UART_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "hal/hal.h"
#include "mcal/mcal.h"

/* ***********************************************************************************************
 * DECLARATIONS
 * ***********************************************************************************************/

/* ToDo: the following declarations starting with CVRT_xxx need to be pushed into the hardware abstraction layer */

#define CVRT_UART_IDX           1                       // Index of UART module for control and monitoring
#define CVRT_UART_BAUDRATE      UART_BAUDRATE_57600		// Baudrate
#define CVRT_UART_DATA_BITS     UART_DATA_BITS_8        // Number of data bits
#define CVRT_UART_PARITY        UART_PARITY_NONE        // Parity setting of the UART 
#define CVRT_UART_STOP_BITS     UART_STOP_BITS_1        // Number of stop bits
#define CVRT_UART_IRS_PRIORITY  UART_ISR_PRIORITY_1     // Priority of the UART interrupts

#define CVRT_UART_RX_PPS_NO     PPSI_RC15
#define CVRT_UART_RX_PPS        PPSIN_U1RX
#define CVRT_UART_TX_PPS_NO     PPSO_RB4
#define CVRT_UART_TX_PPS        PPSOUT_U1TX

#define CVRT_UxRXBUF_SIZE       (32)
#define CVRT_UxTXBUF_SIZE       (32)

#if (CVRT_UART_IDX == 1)
    #define _CVRT_UxRXInterrupt _U1RXInterrupt
    #define _CVRT_UxRXIF        _U1RXIF
    #define CVRT_UxRXREG        U1RXREG

    #define _CVRT_UxTXInterrupt _U1TXInterrupt
    #define _CVRT_UxTXIF        _U1TXIF
    #define CVRT_UxTXREG        U1TXREG
    #define _CVRT_UxTXBF        U1STAbits.UTXBF

    #define _CVRT_UxEInterrupt  _U1ErrInterrupt
    #define _CVRT_UxEIF         _U1EIF
#endif

/*!SMPS_UART_STATUS_BIT_FIELD_t
 *****************************************************************************
 * 
 * Summary:
 * Universal masking data structure to conveniently address specific 
 * SMPS UART protocol settings and status flag bits
 *
 * Description:	
 * 
 *
 * See also:
 * 
 *****************************************************************************/

typedef struct{

	volatile unsigned RXFrameReady:1;	// Bit #0:  
	volatile unsigned TXFrameReady:1;	// Bit #1:  Reserved
	volatile unsigned RXComplete:1;	// Bit #2:  Reserved
	volatile unsigned TXComplete:1;	// Bit #3:  Reserved
	volatile unsigned SOF:1;	// Bit #4:  Reserved
	volatile unsigned :1;	// Bit #5:  Reserved
	volatile unsigned :1;	// Bit #6:  Reserved
	volatile unsigned :1;	// Bit #7:  Reserved
    
	volatile unsigned fault:1;	// Bit #8:  communication error was detected
	volatile unsigned :1;	// Bit #9:  Reserved
	volatile unsigned :1;	// Bit #10: Reserved
	volatile unsigned :1;	// Bit #11: Reserved
	volatile unsigned :1;	// Bit #12: Reserved
	volatile unsigned :1;	// Bit #13: Reserved
	volatile unsigned :1;	// Bit #14: Reserved
	volatile unsigned enable:1;	// Bit #15: flag bit to enable/disable (suspend) the communication 
} __attribute__((packed))SMPS_UART_STATUS_BIT_FIELD_t;

typedef union 
{
	volatile uint16_t flags; // buffer for 16-bit word read/write operations
	volatile SMPS_UART_STATUS_BIT_FIELD_t flag; // data structure for single bit addressing operations
}SMPS_UART_STATUS_FLAGS_t;

typedef struct{
    
    volatile uint8_t  start;    // start-byte (always 0xAA)
    volatile uint16_t id;       // Command-ID
    volatile uint16_t data_len; // data length of the data content
    volatile uint8_t  data[CVRT_UxRXBUF_SIZE]; // data content
    volatile uint16_t crc;      // CRC16 result over id, data-length and data content
    volatile uint8_t  stop;     // start-byte (always 0x0D)
} __attribute__((packed))SMPS_UART_RX_COMM_FRAME_t;

typedef struct{
    
    volatile uint8_t  start;    // start-byte (always 0xAA)
    volatile uint16_t id;       // Command-ID
    volatile uint16_t data_len; // data length of the data content
    volatile uint8_t  data[CVRT_UxTXBUF_SIZE]; // data content
    volatile uint16_t crc;      // CRC16 result over id, data-length and data content
    volatile uint8_t  stop;     // start-byte (always 0x0D)
} __attribute__((packed))SMPS_UART_TX_COMM_FRAME_t;


typedef struct
{
    volatile SMPS_UART_STATUS_FLAGS_t status;
    
    volatile uint32_t baudrate;
    volatile uint16_t port_index;
    
    volatile SMPS_UART_RX_COMM_FRAME_t RXBytes;
    volatile SMPS_UART_TX_COMM_FRAME_t TXBytes;

}__attribute__((packed))SMPS_UART_OBJECT_t;

/** UART Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
typedef enum
{
    UART_RX_DATA_AVAILABLE = (1 << 0), // Indicates that Receive buffer has data, at least one more character can be read 
    UART_RX_OVERRUN_ERROR = (1 << 1), // Indicates that Receive buffer has overflowed
    UART_FRAMING_ERROR = (1 << 2), // Indicates that Framing error has been detected for the current character
    UART_PARITY_ERROR = (1 << 3), // Indicates that Parity error has been detected for the current character
    UART_RECEIVER_IDLE = (1 << 4), // Indicates that Receiver is Idle
    UART_TX_COMPLETE = (1 << 8), // Indicates that the last transmission has completed 
    UART_TX_FULL = (1 << 9) // Indicates that Transmit buffer is full 
}UART_STATUS_e;

extern volatile SMPS_UART_OBJECT_t smps_uart;


/* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
extern volatile inline uint16_t init_DebugUART(void);
extern volatile inline uint16_t exec_DebugUART(void);
extern volatile inline int16_t  dispose_DebugUART(void);

#endif	/* _APL_TASK_SMPS_UART_H_ */

