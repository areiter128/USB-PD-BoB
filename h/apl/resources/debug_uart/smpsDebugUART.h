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
 * File:        smpsDGBUART.h
 * Author:      M91406
 * Comments:    SMPS Debugging UART Protocol Header
 * Revision history: 1.0 (initial version)
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCAL_P33SMPS_DEBUG_UART_PROTOCOL_H
#define	MCAL_P33SMPS_DEBUG_UART_PROTOCOL_H

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
 * Digital Power Debugging UART Communication Data Buffer Definitions
 * ********************************************************************************/
#ifndef DBGUART_RX_BUFFER_SIZE
  #define DBGUART_RX_BUFFER_SIZE    64U // Number of Bytes of one frame RECEIVE buffer
#endif
#ifndef DBGUART_RX_FRAMES
  #define DBGUART_RX_FRAMES         8U // Number of RECEIVE buffers
  #define DBGUART_RX_FRAMES_OVRMSK  0x0007 // Index Overrun mask
#endif
//#ifndef DBGUART_TX_BUFFER_SIZE
//  #define DBGUART_TX_BUFFER_SIZE    64U // Number of Bytes of one frame TRANSMIT buffer
//#endif
#if (UART_INSTANCE == 1)
    
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

#elif (UART_INSTANCE == 2)

    #define _DebugUART_RXIP     _U2RXIP // UART1 Receive Interrupt Priority Bits    
    #define _DebugUART_RXIF     _U2RXIF // UART1 Receive Interrupt Flag Bit
    #define _DebugUART_RXIE     _U2RXIE // UART1 Receive Interrupt Enable Control Bit

    #define _DebugUART_TXIP     _U2TXIP // UART1 Transmit Interrupt Priority Bits    
    #define _DebugUART_TXIF     _U2TXIF // UART1 Transmit Interrupt Flag Bit
    #define _DebugUART_TXIE     _U2TXIE // UART1 Transmit Interrupt Enable Control Bit

    #define _DebugUART_ErrorIP  _U2EIP  // UART1 Error Interrupt Priority Bit
    #define _DebugUART_ErrorIF  _U2EIF  // UART1 Error Interrupt Flag Bit
    #define _DebugUART_ErrorIE  _U2EIE  // UART1 Error Interrupt Enable Control Bit

    #define _DebugUART_ErrorInterrupt   _U2EInterrupt // Interrupt Vector Name of UART1 Error Interrupt
    #define _DebugUART_RXInterrupt      _U2RXInterrupt // Interrupt Vector Name of UART1 Receive Interrupt
    #define _DebugUART_TXInterrupt      _U2TXInterrupt // Interrupt Vector Name of UART1 Transmit Interrupt

#elif (UART_INSTANCE == 3)

    #define _DebugUART_RXIP     _U3RXIP // UART1 Receive Interrupt Priority Bits    
    #define _DebugUART_RXIF     _U3RXIF // UART1 Receive Interrupt Flag Bit
    #define _DebugUART_RXIE     _U3RXIE // UART1 Receive Interrupt Enable Control Bit

    #define _DebugUART_TXIP     _U3TXIP // UART1 Transmit Interrupt Priority Bits    
    #define _DebugUART_TXIF     _U3TXIF // UART1 Transmit Interrupt Flag Bit
    #define _DebugUART_TXIE     _U3TXIE // UART1 Transmit Interrupt Enable Control Bit

    #define _DebugUART_ErrorIP  _U3EIP  // UART1 Error Interrupt Priority Bit
    #define _DebugUART_ErrorIF  _U3EIF  // UART1 Error Interrupt Flag Bit
    #define _DebugUART_ErrorIE  _U3EIE  // UART1 Error Interrupt Enable Control Bit
    
    #define _DebugUART_ErrorInterrupt   _U3EInterrupt // Interrupt Vector Name of UART1 Error Interrupt
    #define _DebugUART_RXInterrupt      _U3RXInterrupt // Interrupt Vector Name of UART1 Receive Interrupt
    #define _DebugUART_TXInterrupt      _U3TXInterrupt // Interrupt Vector Name of UART1 Transmit Interrupt

#else
    #pragma message "=== selected UART instance is not available on this device ==="
#endif    

/* *********************************************************************************
 * Digital Power Debugging UART Communication Timing Definitions
 * ********************************************************************************/
#define DBGUART_SEND_PERIOD    (float)0.250   // Send a UART message every n seconds
#define DBGUART_CLEAR_PERIOD   (float)2.500   // Clear the UART receive buffer after n seconds of inactivity
    
#define DBGUART_SEND_PER   (uint16_t)((((float)DBGUART_SEND_PERIOD / (float)TASK_MGR_TIME_STEP))-1) // LED toggle interval of (2999 + 1) x 100usec = 100ms
#define DBGUART_CLEAR_PER  (uint16_t)((((float)DBGUART_CLEAR_PERIOD / (float)TASK_MGR_TIME_STEP))-1) // interval of (2999 + 1) x 100usec = 100ms

/* *********************************************************************************
 * Digital Power Debugging UART Communication Frame Definitions
 * ********************************************************************************/
#define DBGUART_START_OF_FRAME  0x55 // Every frame starts with a 0x55 to support AUTOBAUD (optional)
#define DBGUART_END_OF_FRAME    0x0D // Every frame ends with a 0x0D as end-marker

#define DBGUART_SOF_LENGTH      (uint16_t)1
#define DBGUART_CID_LENGTH      (uint16_t)2
#define DBGUART_DLEN_LENGTH     (uint16_t)2
#define DBGUART_CRC_LENGTH      (uint16_t)2
#define DBGUART_EOF_LENGTH      (uint16_t)1
    
#define DBGUART_FRAME_HEAD_LEN  (uint16_t)(DBGUART_SOF_LENGTH + DBGUART_CID_LENGTH + DBGUART_DLEN_LENGTH)
#define DBGUART_FRAME_TAIL_LEN  (uint16_t)(DBGUART_CRC_LENGTH + DBGUART_EOF_LENGTH)
#define DBGUART_FRAME_OVHD_LEN  (uint16_t)(DBGUART_FRAME_HEAD_LEN + DBGUART_FRAME_TAIL_LEN)
    
#define DBGUART_INDEX_SOF       (uint16_t)(DBGUART_SOF_LENGTH - 1)
#define DBGUART_INDEX_ID        (uint16_t)(DBGUART_SOF_LENGTH)
#define DBGUART_INDEX_DLEN      (uint16_t)(DBGUART_SOF_LENGTH + DBGUART_CID_LENGTH)
#define DBGUART_INDEX_DATA      (uint16_t)(DBGUART_SOF_LENGTH + DBGUART_CID_LENGTH + DBGUART_DLEN_LENGTH)
 
/* *********************************************************************************
 * PROTOCOL STANDARD CID's
 * *********************************************************************************/
#define DBGUART_CID_ACKNOWLEDGEMENT     0x0100 // Acknowledge-Bit for handshake CIDs
    
#define DBGUART_CID_READ_FROM_ADDR      0xE000 // Standard CID for reading from a memory address
#define DBGUART_CID_WRITE_TO_ADDR       0xE001 // Standard CID for writing to a memory address
#define DBGUART_CID_AND_BIT_MASK        0xE002 // Standard CID for AND-ing a bit mask with a value at a memory address
#define DBGUART_CID_OR_BIT_MASK         0xE003 // Standard CID for OR-ing a bit mask with a value at a memory address
#define DBGUART_CID_BIT_GET             0xE004 // Standard CID for reading a bit within a value at a memory address
#define DBGUART_CID_BIT_SET             0xE005 // Standard CID for setting a bit within a value at a memory address
#define DBGUART_CID_BIT_CLEAR           0xE006 // Standard CID for clearing a bit within a value at a memory address

#define DBGUART_CID_PROPRIETARY         0x0003 // Return value for 
    
/* *********************************************************************************
 * Digital Power Debugging UART Communication Frame
 * ================================================
 * 
 * 1) Data Frame Format:
 * 
 *     SOF   IDH   IDL   DLH   DLL   DAT0  DAT1  ?  DATn  CRCH  CRCL  EOF
 *    [0x55][0xnn][0xmm][0xkk][0xkk][0xkk][0xkk][?][0xkk][0xkk][0xkk][0x0D]
 * 
 *    SOF = START_OF_FRAME (always 0x55)
 *    IDH = IDENTIFIER_HIGH_BYTE
 *    IDL = IDENTIFIER_LOW_BYTE
 *    DLH = DATA_LENGTH_HIGH_BYTE
 *    DLL = DATA_LENGTH_LOW_BYTE
 *    DAT0?DATn = DATA_BYTES
 *    CRCH = CRC16_HIGH_BYTE (IBM CRC16 format)
 *    CRCL = CRC16_LOW_BYTE  (IBM CRC16 format)
 *    EOF = END_OF_FRAME (always 0x0D)
 * 
 * 2) Conventions:
 * 
 *    - SOF-byte is always 0x55 to support the MCU AUTOBAUD feature (optional)
 *    - IBM CRC16 calculation is ran across all frame bytes up to the end of
 *      the data section, starting and including SOF, IDH, IDL, DLH, DLL, DAT0?DATn 
 *      but excluding CRC16- and EOF-bytes.
 *    - Data length of ZERO must be supported on both ends. These messages are 
 *      used for action commands without data.
 *
 * 3) ID-Encoding:
 * 
 *    - Data Streaming IDs (no CRC)
 *      
 *      IDs between 0?255 (IDH = 0x00 and IDL = 0x00 and 0xFF) are exclusively 
 *      used without CRC16 calculation 
 *      (CRC calculation is skipped by default when IDH = 0x00)
 * 
 *      These IDs should only be used for streaming of larger data frames and when 
 *      potential data corruption is acceptable.
 * 
 *    - Echo Data Frame IDs (Master-Slave acknowledge)
 * 
 *      a) Immediate acknowledge
 *      b) Delayed acknowledge
 * 
 *    - Default Command Set IDs
 *    - Proprietary Command Set IDs
 * 
 * ********************************************************************************/
    
    typedef union {
        struct {
            volatile bool rx_frame_ready    : 1; // Bit 0: START_OF_FRAME received
            volatile bool rx_frame_error    : 1; // Bit 1: Frame error detected during decoding
            volatile bool tx_frame_ready    : 1; // Bit 2: TRANSMIT_FRAME ready for transmission 
            volatile bool tx_complete       : 1; // Bit 3: TRANSMIT_FRAME data transmission completed
            volatile unsigned               : 10;// Bit 13-4: (reserved)
            volatile bool ready             : 1; // Bit 14: READY bit indicating that UART interface is initialized and ready
            volatile bool enable            : 1; // Bit 15: Enable Debug UART communication
        } __attribute__((packed)) bits; // Common debugging UART object status bits
        volatile uint16_t value;        // Common debugging UART object status word
    } SMPS_DBGUART_STATUS_t;  // Common debugging UART object status
        
    #define FDEC_STAT_SOF_SYNC  0b0000000000000000
    #define FDEC_STAT_GET_ID    0b0000000000000001
    #define FDEC_STAT_GET_DLEN  0b0000000000000011
    #define FDEC_STAT_GET_DATA  0b0000000000000111
    #define FDEC_STAT_GET_CRC   0b0000000000001111
    #define FDEC_STAT_EOF_SYNC  0b0000000000011111
    #define FDEC_STAT_COMPLETE  0b1000000000111111
    
    typedef union {
        struct {
            volatile unsigned SOF_detected      : 1; // Bit 0:  START_OF_FRAME found flag bit
            volatile unsigned ID_received       : 1; // Bit 1:  FRAME_ID receive complete flag bit
            volatile unsigned DLEN_received     : 1; // Bit 2:  FRAME_DLEN receive complete flag bit
            volatile unsigned DATA_compelte     : 1; // Bit 3:  FRAME_DATA receive complete flag bit
            volatile unsigned CRC_received      : 1; // Bit 4:  FRAME_CRC receive complete flag bit
            volatile unsigned EOF_received      : 1; // Bit 5:  END_OF_FRAME found flag bit
            volatile unsigned                   : 1; // Bit 6:  (reserved)
            volatile unsigned                   : 1; // Bit 7:  (reserved)
            //
            volatile unsigned                   : 1; // Bit 8:  (reserved)
            volatile unsigned                   : 1; // Bit 9:  (reserved)
            volatile unsigned                   : 1; // Bit 10: (reserved)
            volatile unsigned                   : 1; // Bit 11: (reserved)
            volatile unsigned                   : 1; // Bit 12: (reserved)
            volatile unsigned                   : 1; // Bit 13: (reserved)
            volatile unsigned                   : 1; // Bit 14: (reserved)
            volatile unsigned frame_complete    : 1; // Bit 15: FRAME_COMPLETE flag bit
        } __attribute__((packed)) bits; // RECEIVE frame decoding status bits
        volatile uint16_t value;        // RECEIVE frame decoding status word
    } SMPS_DBGUART_FRAME_STATUS_t;      // SMPS Debug UART data frame encoding/decoding status object
    
    typedef struct {
        volatile uint8_t sof;           // START_OF_FRAME byte
        union {
            struct {
                volatile uint8_t idl;   // ID High-Byte
                volatile uint8_t idh;   // ID LOW-Byte
            } __attribute__((packed)) bytes; // 2x 8-bit wide data length access
            volatile uint16_t value;    // 16-bit wide data length value
        } cid;                          // 16-bit wide command ID
        union {
            struct {
                volatile uint8_t dll;   // ID High-Byte
                volatile uint8_t dlh;   // ID LOW-Byte
            } __attribute__((packed)) bytes; // 2x 8-bit wide data length access
            volatile uint16_t value;    // 16-bit wide data length value
        }dlen;
        volatile uint8_t* data;         // Data buffer
        union{
            struct {
                volatile uint8_t crcl;  // CRC16 High-Byte
                volatile uint8_t crch;  // CRC16 LOW-Byte
            } __attribute__((packed)) bytes; // 2x 8-bit wide data length access
            volatile uint16_t value;    // 16-bit wide CRC16 value
        } crc;                          // 16-bit wide Cyclic Redundancy Checksum (CRC)
        volatile uint8_t eof;           // END_OF_FRAME byte
    } SMPS_DBGUART_DATA_FRAME_t;        // SMPS Debug UART Protocol Communication Data Frame
    
    typedef struct {
        volatile SMPS_DBGUART_DATA_FRAME_t frame;    // Data frame object
        volatile SMPS_DBGUART_FRAME_STATUS_t status; // Parsing status of the data frame object
        volatile uint16_t pointer;                   // Pointer to recent frame buffer byte position
    } SMPS_DGBUART_FRAME_t;
    
    typedef struct {
        volatile SMPS_DBGUART_STATUS_t status;  // Common debugging UART object status
        volatile SMPS_DBGUART_FRAME_STATUS_t rx_status; // RECEIVE FRAME object status
        volatile uint16_t active_rx_dlen;       // Most recent RECEIVE buffer data frame length
        volatile uint16_t active_rx_frame;      // Most recent RECEIVE buffer index
        volatile uint16_t send_counter;         // internal software timer period counter
        volatile uint16_t send_period;          // internal software timer period to send next message
        volatile uint16_t clear_counter;        // internal software timer period counter
        volatile uint16_t clear_period;         // internal software timer period to clear RECEIVE buffer
    } SMPS_DBGUART_t;
  
/* *********************************************************************************
 * Digital Power Debugging UART Communication Frame - END
 * ********************************************************************************/

// Public access to DEBUG UART object
extern volatile SMPS_DBGUART_t DebugUART; 
 
/* *********************************************************************************
 * Digital Power Debugging UART Protocol Function Prototypes
 * ********************************************************************************/

extern volatile uint16_t smpsDebugUART_Initialize(void);
extern volatile uint16_t smpsDebugUART_Execute(void);

extern volatile uint16_t smpsDebugUART_SendFrame(volatile SMPS_DGBUART_FRAME_t* tx_frame);
extern volatile uint16_t smpsDebugUART_InitializeFrame(volatile SMPS_DGBUART_FRAME_t* msg_frame, 
            volatile uint16_t id, volatile uint8_t* data, volatile uint16_t data_length);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* MCAL_P33SMPS_DEBUG_UART_PROTOCOL_H */

