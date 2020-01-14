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

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/* *********************************************************************************
 * UART Hardware Definitions
 * ********************************************************************************/
    
#define UART_INSTANCE       3       // Number of UART peripheral instance (1=UART1, 2=UART2, etc)
#define DBGUART_RX_ISR_PRIORITY 2   // UARTx Receive Interrupt Priority


/* *********************************************************************************
 * Global task function prototypes
 * ********************************************************************************/
extern volatile uint16_t task_DebugUART_Initialize(void);
extern volatile uint16_t task_DebugUART_Execute(void);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* SMPS_DBG_PROTOCOL_USER_DECLARATIONS_H */

