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

#define UART_RX_BUFFER_SIZE  256U  // Size of the internal RECEIVE data buffer of the UART driver
#define UART_TX_BUFFER_SIZE  4096U  // Size of the internal TRANSMIT data buffer of the UART driver
#define UART_TX_PACKAGE_SIZE 16U  // Size of one data package transmitted at a time
    
/* *********************************************************************************
 * User Defined Data Frames
 * ********************************************************************************/
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Declaration of Debug UART Test-Frame 0x0100:    
 * This frame was introduced to support GUIs developed by ASCALAB.
 * These GUIs load dedicated I/O masks for certain designs. Thus,
 * the data content is fully proprietary and needs to be defined 
 * in user code.
 * 
 * Message Frame Type:  transmit/receive 
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
    
#define SMPS_DBGUART_CID0100_PERIOD     (float)0.500    // 500 ms send interval

#define SMPS_DBGUART_CID0100            0x0100
#define SMPS_DBGUART_CID0100_TX_DLEN    64U
#define SMPS_DBGUART_CID0100_RX_DLEN    12U

extern volatile SMPS_DGBUART_FRAME_t tx_frame_cid0100;
extern volatile uint8_t tx_data_cid0100[];
extern volatile uint16_t tx_data_cid0100_size;

extern volatile uint8_t rx_data_cid0100[];
extern volatile uint16_t rx_data_cid0100_size;


// From dsPIC to GUI
typedef struct {
    volatile uint16_t vin;          // DBYTE[1:0]   Most recent input voltage
    volatile uint16_t ch1_vout;     // DBYTE[3:2]   Most recent output voltage of channel #1
    volatile uint16_t ch1_iout;     // DBYTE[5:4]   Most recent output current of channel #1
    volatile uint16_t ch1_temp;     // DBYTE[7:6]   Most recent board temperature near channel #1
    volatile uint16_t ch1_status;   // DBYTE[9:8]   Most recent value of the system status flags
    volatile uint16_t ch2_vout;     // DBYTE[11:10] Most recent output voltage of channel #2
    volatile uint16_t ch2_iout;     // DBYTE[13:12] Most recent output current of channel #2
    volatile uint16_t ch2_temp;     // DBYTE[15:14] Most recent board temperature near channel #2
    volatile uint16_t ch2_status;   // DBYTE[17:16] Most recent value of the system status flags
    volatile uint16_t upd1_vid;     // DBYTE[19:18] UPD350 #1: connected device VID
    volatile uint16_t upd1_pid;     // DBYTE[21:20] UPD350 #1: connected device PID
    volatile uint16_t upd2_vid;     // DBYTE[23:22] UPD350 #2: connected device VID
    volatile uint16_t upd2_pid;     // DBYTE[25:24] UPD350 #2: connected device PID
} __attribute__((packed)) CID0100_TX_t;      

// From GUI to dsPIC

extern volatile SMPS_DGBUART_FRAME_t rx_frame_cid0100;
extern volatile uint8_t rx_data_cid0100[];
extern volatile uint16_t rx_data_cid0100_size;

// Set values and System Control Bits
typedef union {
    struct {
        volatile bool ch1_pwr_enable : 1; // Bit [0]: enables/disables power supply channel #1
        volatile bool ch2_pwr_enable : 1; // Bit [1]: enables/disables power supply channel #2
        volatile bool ch1_usb_enable : 1; // Bit [2]: enables/disables USB control over channel #1
        volatile bool ch2_usb_enable : 1; // Bit [3]: enables/disables USB control over channel #2
        volatile bool temp_override  : 1; // Bit [4]: enables/disables temperature override
        volatile bool pwm_dithering  : 1; // Bit [5]: enables/disables PWM spread-spectrum modulation
        volatile unsigned            : 10; // Bit [15:6]: (not used)
    } __attribute__((packed)) bits; // Configuration Bits bit-field
    volatile uint16_t value; // Configuration Bits value
} CID0100_CONFIG_t;
    
typedef struct {
    volatile uint16_t ref_ch1_vout;     // DBYTE[1:0] Output voltage reference for channel #1
    volatile uint16_t ref_ch1_iout;     // DBYTE[3:2] Output current reference for channel #1
    volatile uint16_t ref_ch2_vout;     // DBYTE[5:4] Output voltage reference for channel #2
    volatile uint16_t ref_ch2_iout;     // DBYTE[7:6] Output current reference for channel #2
    volatile uint16_t ref_temp;         // DBYTE[9:8] Simulation value for board temperature
    volatile CID0100_CONFIG_t config_bits;  // DBYTE[11:10] System Control Bits
} __attribute__((packed)) CID0100_RX_t;      
      
    
/* *********************************************************************************
 * Digital Power Debugging UART Protocol Function Prototypes
 * ********************************************************************************/

extern volatile uint16_t smpsDebugUART_ProcessUserCID(volatile SMPS_DGBUART_FRAME_t* rx_frame);
    
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* APL_P33SMPS_DEBUG_UART_PROTOCOL_USER_CID_HANDLER_H */

