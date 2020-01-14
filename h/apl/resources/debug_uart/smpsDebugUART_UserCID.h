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
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef APL_P33SMPS_DEBUG_UART_PROTOCOL_USER_CID_HANDLER_H
#define	APL_P33SMPS_DEBUG_UART_PROTOCOL_USER_CID_HANDLER_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stddef.h> // include standard definition data types
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

#include "mcal/mcal.h" // include Microcontroller Abstraction Layer
#include "hal/hal.h" // include Hardware Abstraction Layer


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/* *********************************************************************************
 * Digital Power Debugging UART Protocol Global Defines
 * ********************************************************************************/
    
#define DBGUART_CID_DSMPS_GUI           0x0100 // Standard CID for ASCALB GUI (DSMPS)

// Index definition for CID 0x0100 (Ascalab GUI) 
    
#define CID0100_RX_VOUT_CH1_INDEX      0
#define CID0100_RX_IOUT_CH1_INDEX      2
#define CID0100_RX_VOUT_CH2_INDEX      4
#define CID0100_RX_IOUT_CH2_INDEX      6
#define CID0100_RX_TEMPERATURE_INDEX   8
#define CID0100_RX_CONFIG_BITS_INDEX   10


// Bit masks 
#define CID0100_RX_ON_OFF_CH1_BIT      (1<<0)
#define CID0100_RX_ON_OFF_CH2_BIT      (1<<1)
#define CID0100_RX_USB_CH1_ENABLED     (1<<2)
#define CID0100_RX_USB_CH2_ENABLED     (1<<3)
#define CID0100_RX_TEMP_SIMULATION     (1<<4)
#define CID0100_RX_PWM_FREQ_JITTERING  (1<<5)


// From dsPIC to GUI

#define CID0100_TX_VIN_INDEX            0
#define CID0100_TX_VOUT_CH1_INDEX       2
#define CID0100_TX_IOUT_CH1_INDEX       4
#define CID0100_TX_CONVERTER_STATUS     6
#define CID0100_TX_CONVERTER_FAULT      8
#define CID0100_TX_VOUT_CH2_INDEX       10
#define CID0100_TX_IOUT_CH2_INDEX       12
#define CID0100_TX_TEMPERATURE_INDEX    14
#define CID0100_TX_UPD1_DEVICE_VID      16
#define CID0100_TX_UPD1_DEVICE_PID      18
#define CID0100_TX_UPD2_DEVICE_VID      20
#define CID0100_TX_UPD2_DEVICE_PID      22
        
    
/* *********************************************************************************
 * Digital Power Debugging UART Protocol Function Prototypes
 * ********************************************************************************/

extern volatile uint16_t smpsDebugUART_ProcessUserCID(volatile SMPS_DGBUART_FRAME_t* rx_frame);
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* APL_P33SMPS_DEBUG_UART_PROTOCOL_USER_CID_HANDLER_H */

