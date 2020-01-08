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
 * File:   smpsDebugUART_User.h
 * Author: M91406
 * Comments:    
 *      Header file used for user-declarations of settings and communication frames
 *      used by smpsDebugUART.c/h
 * Revision history: 
 *      1.0     (initial version)
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SMPS_DBG_PROTOCOL_USER_DECLARATIONS_H
#define	SMPS_DBG_PROTOCOL_USER_DECLARATIONS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

//#include "apl/resources/debug_uart/smpsDebugUART.h"
//#include "dsPIC33C/p33SMPS_uart.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/* *********************************************************************************
 * UART Hardware Definitions
 * ********************************************************************************/
    
#define UART_INSTANCE       1  // Number of UART peripheral instance (1=UART1, 2=UART2, etc)
#define DBGUART_RX_ISR_PRIORITY 2   // UART1 Receive Interrupt Priority
    
#define _DebugUART_RXIP     _U1RXIP // UART1 Receive Interrupt Priority Bits    
#define _DebugUART_RXIF     _U1RXIF // UART1 Receive Interrupt Flag Bit
#define _DebugUART_RXIE     _U1RXIE // UART1 Receive Interrupt Enable Control Bit

#define _DebugUART_TXIP     _U1TXIP // UART1 Transmit Interrupt Priority Bits    
#define _DebugUART_TXIF     _U1TXIF // UART1 Transmit Interrupt Flag Bit
#define _DebugUART_TXIE     _U1TXIE // UART1 Transmit Interrupt Enable Control Bit
    
#define _DebugUART_ErrorIP  _U1EIP  // UART1 Error Interrupt Priority Bit
#define _DebugUART_ErrorIF  _U1EIF  // UART1 Error Interrupt Flag Bit
#define _DebugUART_ErrorIE  _U1EIE  // UART1 Error Interrupt Enable Control Bit
    
#define _DebugUART_ErrorInterrupt   _U1EInterrupt // Interrupt Vector Name of UART1 Error Interrupt
#define _DebugUART_RXInterrupt      _U1RXInterrupt // Interrupt Vector Name of UART1 Receive Interrupt
#define _DebugUART_TXInterrupt      _U1TXInterrupt // Interrupt Vector Name of UART1 Transmit Interrupt
    
/* *********************************************************************************
 * Transmission Data Frame Definitions
 * ********************************************************************************/

//#define  SMPS_DBGUART_CID11          0x11

    
/*!CID100
 *  *********************************************************************************
 * CID100
 * ********************************************************************************/

    
//#define  SMPS_DBGUART_CID100        0x0100
//#define  SMPS_DBGUART_CID100_DLEN   32U
//    
//extern volatile SMPS_DGBUART_FRAME_t tx_frame_cid100;
//extern volatile uint8_t tx_data_cid100[];
//extern volatile uint16_t tx_data_cid100_size;
//

/* *********************************************************************************
 * Receive Data Frame Definitions
 * ********************************************************************************/

/* *********************************************************************************
 * Global task function prototypes
 * ********************************************************************************/
extern volatile uint16_t task_DebugUART_Initialize(void);
extern volatile uint16_t task_DebugUART_Execute(void);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SMPS_DBG_PROTOCOL_USER_DECLARATIONS_H */

