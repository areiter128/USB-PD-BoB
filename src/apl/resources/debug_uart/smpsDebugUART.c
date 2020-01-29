/*
 * File:   smpsDBGUART.c
 * Author: M91406
 *
 * Created on November 28, 2019, 5:56 PM
 */

#include "apl/resources/debug_uart/smpsDebugUART.h"
#include "apl/resources/debug_uart/smpsDebugUART_UserCID.h"
#include "apl/tasks/task_DebugUART.h"

#include "dsPIC33C/p33SMPS_uart.h"

/* *********************************************************************************
 * UART Communication Data Buffer Definitions
 * ================================================
 * Set up internal UART RECEIVE and TRANSMIT data buffers
 *
 * Please don't mistake UART buffers and DebugUART buffers!
 * UART buffers are used to handle incoming and outgoing data
 * on hardware level. 
 * 
 * DebugUART buffers are used to prepare Tx and/or sort data 
 * into Rx data frames.
 * 
 * ********************************************************************************/

#define UART_RX_BUFFER_DEFAULT_SIZE  256U  // Size of the internal RECEIVE data buffer of the UART driver
#define UART_TX_BUFFER_DEFAULT_SIZE  256U  // Size of the internal TRANSMIT data buffer of the UART driver
#define UART_TX_PACKAGE_DEFAULT_SIZE  16U  // Size of one data package transmitted at a time

// Guarding condition for variable initialization of RX Buffer Size
#ifndef UART_RX_BUFFER_SIZE
  // If users have not specified any size of the RX buffer, set default size here
  #define UART_RX_BUFFER_SIZE  UART_RX_BUFFER_DEFAULT_SIZE
#endif

// Guarding condition for variable initialization of TX Buffer Size
#ifndef UART_TX_BUFFER_SIZE
  // If users have not specified any size of the TX buffer, set default size here
  #define UART_TX_BUFFER_SIZE  UART_TX_BUFFER_DEFAULT_SIZE
#endif

// Guarding condition for variable initialization of TX Package Size
#ifndef UART_TX_PACKAGE_SIZE
  // If users have not specified any size of the TX buffer, set default size here
  #define UART_TX_PACKAGE_SIZE  UART_TX_PACKAGE_DEFAULT_SIZE
#endif


volatile uint8_t  uart_rx_buffer[UART_RX_BUFFER_SIZE];
volatile uint8_t  uart_tx_buffer[UART_TX_BUFFER_SIZE];

volatile UART_t uart; // declare private UART object from p33SMPS_uart library

/* *********************************************************************************
 * DebugUART Object Definitions
 * ================================================
 * Set up internal DEBUG UART objects
 *
 * Please don't mistake UART buffers and DebugUART buffers!
 * UART buffers are used to handle incoming and outgoing data
 * on hardware level. The UART driver provides a wide data space
 * used as Tx/Rx pipelines of multiple incoming or outgoing data
 * frames.
 * 
 * DebugUART buffers are used to prepare Tx and/or sort data 
 * into Rx data frames.
 * 
 * ********************************************************************************/

volatile SMPS_DBGUART_t DebugUART; // Debug UART control data object

volatile SMPS_DGBUART_FRAME_t rx_frame[DBGUART_RX_FRAMES];
volatile uint8_t rx_data[DBGUART_RX_FRAMES][DBGUART_RX_BUFFER_SIZE];
volatile uint16_t rx_data_size = (sizeof(rx_data[0])/sizeof(rx_data[0][0]));

// --------------------------------------
// Declare private function prototypes
// --------------------------------------
volatile uint16_t DebugUART_TimingUpdate(void);

volatile uint16_t smpsDebugUART_ProcessDefaultCID(volatile SMPS_DGBUART_FRAME_t* msg_frame);

volatile uint16_t smpsDebugUART_InitializeFrame(
    volatile SMPS_DGBUART_FRAME_t* msg_frame, 
    volatile uint16_t id, volatile uint8_t* data, volatile uint16_t data_length);

/*!DebugUART_TimingUpdate
 * ***********************************************************************************************
 * The state machine is called by the OS with a certain frequency. This call-frequency depends
 * on the number of tasks in the recent task queue managed by the scheduler and the task scheduler
 * base frequency (e.g. 10kHz=100usec).  When either of these parameters change during runtime, 
 * user tasks may need to adjust their internal software timer counters to the new call-frequency.
 * *********************************************************************************************** */

volatile uint16_t DebugUART_TimingUpdate(void) {

    // Update SEND_PERIOD
    DebugUART.send_period = 
        (volatile uint16_t)(DBGUART_SEND_PER / (task_mgr.task_queue_ubound + 1));

    DebugUART.clear_period = 
        (volatile uint16_t)(DBGUART_CLEAR_PER / (task_mgr.task_queue_ubound + 1));

    return(1);
}


/*!smpsDebugUART_Execute
 * ************************************************************************************************
 * Summary:
 * Top-Level State Machine Function of the Debug UART Protocol
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 1=success, 0=failure
 *
 * Description:
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_Execute(void) {

    volatile uint16_t fres=1;           // Function return value buffer variable
    volatile uint16_t retval=0;         // Auxiliary function return value buffer variable
    volatile uint16_t i=0, m=0, p=0;    // Auxiliary variables for command execution

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* DISABLE-GUARD                                                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // When DebugUART is disabled, exit here and do not process any data
    if (!DebugUART.status.bits.enable)
    { return(1); }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* TIMING UPDATE ON OS QUEUE-SWITCH                                                                    */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if (task_mgr.status.bits.queue_switch)
    { fres &= DebugUART_TimingUpdate(); }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* PROCESS RECEIVED MESSAGES                                                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(DebugUART.status.bits.rx_frame_ready)
    { 
        // Capture active frame pointer
        p = DebugUART.active_rx_frame;
        
        // Execute all new frames available
        for (i=0; i<DBGUART_RX_FRAMES; i++) {
            
            // Set pointer to oldest frame and move towards latest ones
            m = ((p+i) & DBGUART_RX_FRAMES_OVRMSK); 
            
            // Only process frames which haven't processed yet
            if ( rx_frame[m].status.bits.frame_complete ) {
                
                // Call Default Command ID Processing
                retval = smpsDebugUART_ProcessDefaultCID(&rx_frame[m]); 
                
                // If CID has been recognized as proprietary user command ID,
                // call User Command ID Processing
                if (retval == DBGUART_CID_PROPRIETARY)
                { fres &= smpsDebugUART_ProcessUserCID(&rx_frame[m]); }
                else
                { fres &= retval; }
            }
            
        }
        
        // Reset Frame
        DebugUART.status.bits.rx_frame_ready = false; // Reset FRAME_READY flag bit
        DebugUART.status.bits.rx_frame_error = false; // Reset FRAME_ERROR flag bit 

        // Reset RECEIVE Timeout Counter
        DebugUART.clear_counter = 0;
        
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* SEND NEXT MESSAGE IN QUEUE                                                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    else if ((++DebugUART.send_counter > DebugUART.send_period) || (!uart.tx_buffer.status.msg_complete)) 
    { // Count OS function calls until UART send period is exceeded
      // Send message and reset UART send interval counter
        
        // Reset send counter
        if(DebugUART.send_counter > DebugUART.send_period)
            DebugUART.send_counter = 0; 

        // Write message frame to FIFO buffer
        fres = smpsUART_WriteFIFO(&uart);
        
        Nop(); // for debugging purposes
    } 
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* CLEAR RECEIVE BUFFERS WHICH HAVE NOT BEEN PROCESSED WITHIN DEFINED CLEAR_PERIOD    */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if (DebugUART.clear_counter++ > DebugUART.clear_period)
    { // Clear RECEIVE buffer
    
        uart.rx_buffer.pointer = 0; // Clear data array pointer
        uart.rx_buffer.status.buffer_empty = true;
        uart.rx_buffer.status.buffer_full = false;
        uart.rx_buffer.status.buffer_overun = false;
        
        DebugUART.clear_counter = 0; // Clear BUFFER RESET counter
    
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    
    return(fres);

}

/*!smpsDebugUART_Initialize
 * ************************************************************************************************
 * Summary:
 * Initializes a user specified UART interface and debugging protocol objects
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 1=success, 0=failure
 *
 * Description:
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_Initialize(void) {
    
    volatile uint16_t fres=1;
    volatile uint16_t i=0;
    volatile uint16_t pack_size=0;
    
    // Check buffer sizes
    if ((UART_RX_BUFFER_SIZE<1) || (UART_TX_BUFFER_SIZE<1)) {
    // If buffer sizes are inefficient, exit here uninitialized
        DebugUART.status.bits.enable = false;
        DebugUART.status.bits.ready = false;
        return(0);
    }
    
    // Copy package size for validation and limit size to minimum of 4 byte
    pack_size = UART_TX_PACKAGE_SIZE;
    if (pack_size < 4) pack_size = 4;

    // Initialize standard data objects
    for (i=0; i<DBGUART_RX_FRAMES; i++) {
        rx_frame[i].frame.data = &rx_data[i][0];
    }
    
    // Initialize the user-defined DebugUART object
    DebugUART_TimingUpdate(); // Update send period to adjust to OS task call rate
    
    DebugUART.active_rx_frame = 0;              // Reset pointer to first RECEIVE buffer
    DebugUART.active_rx_dlen = 0;               // Reset data length of receive frame data buffer
    DebugUART.send_counter = 0;                 // Set send period counter
    DebugUART.send_period = DebugUART.send_period;   // Set updated send period
    DebugUART.clear_counter = 0;                // Set clear period counter
    DebugUART.clear_period = DebugUART.clear_period; // Set updated clear period

    // Initialize the user-defined UART object
    uart.instance = UART_INSTANCE;              // UART Instance (e.g. 1=UART1, 2=UART2, etc.)
    uart.baudrate = UART_BAUDRATE_115200;       // Baud rate (e.g. 9600)
    uart.data_bits = UART_DATA_BITS_8;          // Data bits (e.g. 8)
    uart.parity = UART_PARITY_NONE;             // Parity (None, Odd or Even)
    uart.stop_bits = UART_STOP_BITS_1;          // Stop bits (e.g. 1)
    uart.flow_control = UART_FLOW_CONTROL_NONE; // Flow Control (None, Hardware or Xon/Xoff)
    
    uart.rx_buffer.buffer = &uart_rx_buffer[0];   // Initially set pointer to first user buffer
    uart.rx_buffer.size = UART_RX_BUFFER_SIZE;    // absolute size of the internal user buffer (fixed)
    uart.rx_buffer.pointer = 0;                 // Reset pointer to first array cell
    uart.rx_buffer.fifo_isr_mark = UART_FIFO_SIZE_1_BYTE; // trigger interrupt after n bytes

    uart.tx_buffer.buffer = &uart_tx_buffer[0];   // Pointer to user buffer
    uart.tx_buffer.size = UART_TX_BUFFER_SIZE;  // Length to UART TX FIFO buffer
    uart.tx_buffer.data_size = 0;               // Reset 'data in buffer' size 
    uart.tx_buffer.pointer = 0;                 // Reset pointer to first array cell
    uart.tx_buffer.fifo_isr_mark = UART_FIFO_SIZE_1_BYTE; // trigger interrupt after n bytes
    uart.tx_buffer.package_size = pack_size;    // Size of the data package sent at a time
  
    uart.tx_buffer.status.msg_complete = false;  // Clear TX_BUFFER_READY flag bit

    // Initialize and open port using configuration above
    fres &= smpsUART_OpenPort(&uart);

    // Initialize RECEIVE interrupt
    _DebugUART_RXIP = DBGUART_RX_ISR_PRIORITY;    // Set RECEIVE interrupt priority
    _DebugUART_RXIF = 0;    // Clear Interrupt flag bit
    _DebugUART_RXIE = 1;    // Enable RX interrupt
    
    // If UART interface initialization was successful, enable DebugUART Object
    if(fres) {
        DebugUART.status.bits.ready = true;  // Set READY bit
        DebugUART.status.bits.enable = true; // Set ENABLE bit
    }
    else
    {   smpsUART_Close(&uart);  } // Close UART (disables UART peripheral)

    // Return success/failure of function execution
    return(fres);
}

/*!smpsDebugUART_InitializeFrame
 * ************************************************************************************************
 * Summary:
 * Packs up user data in a SMPS Debug UART data frame by adding SOF, CID, DLEN, EOF and CRC
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 1=success, 0=failure
 *
 * Description:
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_InitializeFrame(
            volatile SMPS_DGBUART_FRAME_t* msg_frame, 
            volatile uint16_t id, volatile uint8_t* data, volatile uint16_t data_length) {
    
    volatile uint16_t fres=1;
    
    // Build TRANSMIT frame 
    msg_frame->frame.sof = DBGUART_START_OF_FRAME; // Set START_OF_FRAME
    msg_frame->frame.cid.value = id; // Set message ID
    msg_frame->frame.dlen.value = data_length; // Set message data length
    msg_frame->frame.data = data; // Set pointer to data array
    msg_frame->frame.crc.value = 0; // Clear frame CRC16
    msg_frame->frame.eof = DBGUART_END_OF_FRAME; // Set END_OF_FRAME

    msg_frame->status.value = 0; // Clear status bits
    
    return(fres);

}

/*!smpsDebugUART_SendFrame
 * ************************************************************************************************
 * Summary:
 * Packs up user data in a SMPS Debug UART data frame
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 1=success, 0=failure
 *
 * Description:
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_SendFrame(volatile SMPS_DGBUART_FRAME_t* msg_frame) {
    
    volatile uint16_t fres=1;
    volatile uint16_t i=0;
    volatile uint8_t ubound=0;
    
    
    // Protect against buffer overrun
    if((msg_frame->frame.dlen.value + DBGUART_FRAME_OVHD_LEN) >= UART_TX_BUFFER_SIZE)
    { uart.tx_buffer.status.buffer_overun = true; return(0); }
    else
    { uart.tx_buffer.status.buffer_overun = false; }
    
    // Capture the recent buffer status
    ubound = (volatile uint8_t)uart.tx_buffer.data_size;
    
    // Build UART transmission frame
    uart_tx_buffer[ubound+0] = msg_frame->frame.sof;            // Set START_OF_FRAME
    uart_tx_buffer[ubound+1] = msg_frame->frame.cid.bytes.idh;  // Set ID High Byte
    uart_tx_buffer[ubound+2] = msg_frame->frame.cid.bytes.idl;  // Set ID Low Byte
    uart_tx_buffer[ubound+3] = msg_frame->frame.dlen.bytes.dlh; // Set Data Length High Byte
    uart_tx_buffer[ubound+4] = msg_frame->frame.dlen.bytes.dll; // Set Data Length Low Byte

    // Copy data buffer
    for (i=0; i<msg_frame->frame.dlen.value; i++)
    { uart_tx_buffer[i+(DBGUART_FRAME_HEAD_LEN+ubound)] = (uint8_t)msg_frame->frame.data[i]; }
    i += DBGUART_FRAME_HEAD_LEN;
    
    // Calculate and set CRC16
    if (msg_frame->frame.cid.value > DBGUART_CID_CRC_BYPASS)
        msg_frame->frame.crc.value = smpsCRC_GetStandard_Data8CRC16(&uart_tx_buffer[0], ubound, i);
    else
        msg_frame->frame.crc.value = 0;

    // Add CRC to data frame
    i += ubound;                                            // Add buffer pointer offset
    uart_tx_buffer[i++] = msg_frame->frame.crc.bytes.crch;  // Set CRC16 High Byte
    uart_tx_buffer[i++] = msg_frame->frame.crc.bytes.crcl;  // Set CRC16 Low Byte

    uart_tx_buffer[i++] = msg_frame->frame.eof;             // Set END_OF_FRAME

    uart.tx_buffer.buffer = &uart_tx_buffer[0];    // Set pointer to internal FIFO data buffer
    uart.tx_buffer.data_size = (uint8_t)(i);       // Set size of data to be sent

    
    return(fres);
    
}

/*!smpsDebugUART_ProcessDefaultCID
 * ************************************************************************************************
 * Summary:
 * Processes received default protocol message frames
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 0=failure, 1=success, 3=unsupported/proprietary CID
 *
 * Description:
 * The Debug UART protocol defines a certain set of default CIDs used for standard operations
 * such as read from/write to memory addresses, get, set or clear bits and more. When a message
 * frame is received, the debug UART driver will first check for default functions. If the 
 * given CID is not a default command ID, this function returns the value DBGUART_CID_PROPRIETARY 
 * (=0b11) indicating that the frame has been received correctly (CRC verification passed successfully)
 * but the CID has not been recognized. 
 * 
 * Unrecognized CIDs are considered to be proprietary user commands and are therefor passed on
 * to be handled in user code.
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_ProcessDefaultCID(volatile SMPS_DGBUART_FRAME_t* msg_frame) {

    // Function return value
    volatile uint16_t fres=1;

    // Frame-Validation variables
    volatile uint16_t crc=0;
    
    // Command execution buffer variables
    volatile uint16_t val_buf=0;
    volatile uint16_t* addr_ptr;
    
    // Run Cyclic Redundancy Check if ID and data contents are valid
    // for all IDs greater than 0x000F. CIDs from 0 to 15 (0x0000-0x000F)
    // are used to bypass CRC calculation
    if (msg_frame->frame.cid.value > 0x000F) {
    
        // Run Cyclic Redundancy Check 
        crc = smpsCRC_GetStandard_Data8CRC16((uint8_t*)msg_frame, 0, (msg_frame->frame.dlen.value + DBGUART_FRAME_HEAD_LEN));
    
        // if there is a CRC mismatch, stop and exit here
        if (crc == msg_frame->frame.crc.value) {
            msg_frame->status.value = FDEC_STAT_SOF_SYNC; // Reset frame object and RX FIFO data buffer pointer
            return(0);  // Exit and return FALSE
        }
    }

    // Select CID response action
    switch (msg_frame->frame.cid.value) {

        /*!DBGUART_CID_READ_FROM_ADDR
         * *********************************************************************
         * Returns the value [VALUE] found at address [ADDR]. 
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The value is returned by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = VALUE high byte
         *   - DATA[3] = VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_READ_FROM_ADDR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[2] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[0] of frame
            msg_frame->frame.data[3] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[1] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_WRITE_TO_ADDR
         * *********************************************************************
         * Writes a new value [VALUE] to address [ADDR]. 
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The value is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = VALUE high byte
         *   - DATA[3] = VALUE low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_WRITE_TO_ADDR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read new value to be written to memory address
            val_buf = msg_frame->frame.data[2]; // Load value high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load value low-byte

            // Write value to memory address
            *addr_ptr = (volatile uint16_t)val_buf;

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_OR_BIT_MASK
         * *********************************************************************
         * OR's a bit mask [BITMSK] with a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to this memory 
         * address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit mask is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = BITMSK high byte
         *   - DATA[3] = BITMSK low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_OR_BIT_MASK:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read bit mask from message frame
            val_buf = msg_frame->frame.data[2]; // Load bit mask high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load bit mask low-byte

            // Write [value | bit mask] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr | (volatile uint16_t)val_buf);

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_AND_BIT_MASK
         * *********************************************************************
         * AND's a bit mask [BITMSK] with a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to this memory 
         * address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit mask is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = BITMSK high byte
         *   - DATA[3] = BITMSK low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_AND_BIT_MASK:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read bit mask from message frame
            val_buf = msg_frame->frame.data[2]; // Load bit mask high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load bit mask low-byte

            // Write [value & bit mask] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr & (volatile uint16_t)val_buf);

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_GET
         * *********************************************************************
         * Gets a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and returns its value to sender
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is extracted from the value found at the given address
         *  and returned to the sender, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_GET:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_SET
         * *********************************************************************
         * Sets a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to the given
         * memory address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is set within the value found at the given address. The
         * value is read back, the bit is extracted and returned to the sender 
         * for verification, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_SET:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Write [value | bit] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr | (0x0001 << msg_frame->frame.data[2]));

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_CLEAR
         * *********************************************************************
         * Clears a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to the given
         * memory address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is cleared within the value found at the given address. The
         * value is read back, the bit is extracted and returned to the sender 
         * for verification, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_CLEAR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Write [value | bit] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr & (~(0x0001 << msg_frame->frame.data[2])));

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!Proprietary Protocol Commands
         * *********************************************************************
         * If the received CID is not recognized as Default Command ID, 
         * return DBGUART_CID_PROPRIETARY.
         * ********************************************************************/    
        default:
            // The received CID has not been recognized and is considered to be a 
            // proprietary Command ID which needs to be processed in user code.
            // Thus the Rx Frame is kept alive by not resetting its status
            // and is handed back to the calling function.
            return(DBGUART_CID_PROPRIETARY);
            break;
    }
    
    
    // Reset frame object and RX FIFO data buffer pointer
    msg_frame->status.value = FDEC_STAT_SOF_SYNC;
    
    return(fres);

}


/*!_DebugUART_RXInterrupt
 * ************************************************************************************************
 * Summary:
 * Receive Interrupt Service Routine of user-selected UART instance
 *
 * Parameters:
 *  (none)
 * 
 * Returns:
 *  (none)
 *
 * Description:
 * 
 * ************************************************************************************************/

void __attribute__((__interrupt__, auto_psv)) _DebugUART_RXInterrupt()
{

    volatile UART_CONFIG_t *ux_regbuf;
    volatile uint8_t rx_char=0;
    volatile uint16_t dum=0;
    volatile bool frame_error=false;

    // Clear state machine BUFFER RESET counter as long as there is activity
    DebugUART.clear_counter = 0;    

    ux_regbuf = (volatile UART_CONFIG_t*)uart.handle; // Capture start of the UART register block

    // Read entire FIFO buffer
    while(!(ux_regbuf->status.bits.urxbe)) // while buffer is not empty...
    {    

        // Read Byte from UART FIFO buffer
        rx_char = (volatile uint8_t)ux_regbuf->rx_reg.value;
        uart.rx_buffer.pointer++;

        switch (DebugUART.rx_status.value) {

            case FDEC_STAT_SOF_SYNC:
                // If no START_OF_FRAME has been detected, sync on START_OF_FRAME
                
                // Incoming data is ignored until START_OF_FRAME has been detected
                uart.rx_buffer.pointer = 0; // Keep RECEIVE buffer pointer at zero

                // Check for START_OF_FRAME
                if(rx_char == DBGUART_START_OF_FRAME) { 
                    rx_frame[DebugUART.active_rx_frame].frame.sof = rx_char; // Copy into frame buffer
                    uart.rx_buffer.pointer = DBGUART_SOF_LENGTH; // Set RECEIVE buffer pointer to start of ID
                    DebugUART.rx_status.bits.SOF_detected = true; // Set START_OF_FRAME status flag bit
                }
                break;

            case FDEC_STAT_GET_ID:
                // START_OF_FRAME has been detected, waiting for ID
                
                if ((uart.rx_buffer.pointer == (DBGUART_INDEX_ID + 1)) && (rx_char == DBGUART_START_OF_FRAME)) {
                // If HIGH BYTE of ID is START_OF_FRAME, reset START_OF_FRAME
                    uart.rx_buffer.pointer = DBGUART_SOF_LENGTH; // Set RECEIVE buffer pointer to start of ID
                }
                else if (uart.rx_buffer.pointer == (DBGUART_INDEX_ID + 1)) {
                    rx_frame[DebugUART.active_rx_frame].frame.cid.bytes.idh = rx_char; // Copy into frame buffer
                }
                else if (uart.rx_buffer.pointer == (DBGUART_INDEX_DLEN)) {
                    rx_frame[DebugUART.active_rx_frame].frame.cid.bytes.idl = rx_char; // Copy into frame buffer
                    DebugUART.rx_status.bits.ID_received = true; // Set ID_RECEIVED status flag bit
                }
                break;

            case FDEC_STAT_GET_DLEN:
                // START_OF_FRAME + ID has been detected, waiting for DLEN
                
                if (uart.rx_buffer.pointer == (DBGUART_INDEX_DLEN + 1)) {
                    rx_frame[DebugUART.active_rx_frame].frame.dlen.bytes.dlh = rx_char; // Copy into frame buffer
                    DebugUART.active_rx_dlen = rx_char;
                    DebugUART.active_rx_dlen <<= 8;
                }
                else if (uart.rx_buffer.pointer == (DBGUART_INDEX_DATA)) {
                    rx_frame[DebugUART.active_rx_frame].frame.dlen.bytes.dll = rx_char; // Copy into frame buffer
                    DebugUART.active_rx_dlen |= rx_char;
                    
                    rx_frame[DebugUART.active_rx_frame].pointer = 0; // Reset frame data pointer
                    DebugUART.rx_status.bits.DLEN_received = true; // Set ID_RECEIVED status flag bit
                }
                break;

            case FDEC_STAT_GET_DATA:
                // START_OF_FRAME + ID + DLEN has been detected, waiting for DATA
                
                rx_frame[DebugUART.active_rx_frame].frame.data[rx_frame[DebugUART.active_rx_frame].pointer++] = rx_char; // Copy into frame buffer
                
                if (uart.rx_buffer.pointer == (DBGUART_FRAME_HEAD_LEN + DebugUART.active_rx_dlen)) {
                    DebugUART.rx_status.bits.DATA_compelte = true; // Set DATA_COMPLETE status flag bit
                }
                break;

            case FDEC_STAT_GET_CRC:
                // START_OF_FRAME + ID + DLEN + DATA has been detected, waiting for CRC
                
                
                if (uart.rx_buffer.pointer == (DBGUART_FRAME_HEAD_LEN + DebugUART.active_rx_dlen + 1)) {
                    rx_frame[DebugUART.active_rx_frame].frame.crc.bytes.crch = rx_char;
                }
                else if (uart.rx_buffer.pointer == (DBGUART_FRAME_HEAD_LEN + DebugUART.active_rx_dlen + DBGUART_CRC_LENGTH)) {
                    rx_frame[DebugUART.active_rx_frame].frame.crc.bytes.crcl = rx_char;
                    DebugUART.rx_status.bits.CRC_received = true; // Set CRC_RECEIVED status flag bit
                }
                break;

            case FDEC_STAT_EOF_SYNC:
                // START_OF_FRAME + ID + DLEN + DATA + CRC has been detected, expecting EOF

                rx_frame[DebugUART.active_rx_frame].frame.eof = rx_char;
                
                if(rx_char == DBGUART_END_OF_FRAME) { 
                    
                    DebugUART.rx_status.bits.EOF_received = true; // Set EOF_RECEIVED status flag bit
                    
                    rx_frame[DebugUART.active_rx_frame].pointer = 0; // Reset data pointer of frame 
                    rx_frame[DebugUART.active_rx_frame].status.value = FDEC_STAT_COMPLETE; // Set status for FRAME_COMPLETE

                    DebugUART.rx_status.bits.frame_complete = true; // Set FRAME_COMPLETE status flag bit
                    DebugUART.status.bits.rx_frame_ready = true; // Set FRAME_COMPLETE status flag bit 

                    dum = (DebugUART.active_rx_frame + 1);
                    DebugUART.active_rx_frame = (dum & DBGUART_RX_FRAMES_OVRMSK);
                    DebugUART.rx_status.value = FDEC_STAT_SOF_SYNC;
                    
                }
                else {
                // if this byte is != EOF, something went wrong and the entire frame will be rejected
                    frame_error = true; // Set FRAME_ERROR flag
                }

                break;

            default:
                // If the RECEIVE status is none of the above, something went wrong and the 
                // entire frame will be rejected
                frame_error = true; // Set FRAME_ERROR flag
                break;

        }

        if (frame_error) {

            uart.rx_buffer.pointer = 0; // Reset RECEIVE buffer data pointer to ZERO
            
            rx_frame[DebugUART.active_rx_frame].pointer = 0; // Reset data pointer of frame 
            rx_frame[DebugUART.active_rx_frame].status.value = FDEC_STAT_SOF_SYNC; // Set status for FRAME_COMPLETE

            DebugUART.rx_status.value = FDEC_STAT_SOF_SYNC; // Reset status to EOF_SYNC
            DebugUART.status.bits.rx_frame_error = true; // Set FRAME_COMPLETE status flag bit
            DebugUART.status.bits.rx_frame_ready = false; // Clear FRAME_READY status flag bit
            
            // Empty RX FIFO rejecting all data
            while(!(ux_regbuf->status.bits.urxbe)) // while buffer is not empty...
            { rx_char = (volatile uint8_t)ux_regbuf->rx_reg.value; }
            
            break; // Exit WHILE loop
            
        }
        
    }

    _DebugUART_RXIF = 0; // Clear interrupt flag bit

    return;
}

/*!_DebugUART_ErrorInterrupt
 * ************************************************************************************************
 * Summary:
 * Error Interrupt Service Routine of user-selected UART instance
 *
 * Parameters:
 *  (none)
 * 
 * Returns:
 *  (none)
 *
 * Description:
 * 
 * ************************************************************************************************/

void __attribute__((__interrupt__, auto_psv)) _DebugUART_ErrorInterrupt()
{
    volatile UART_CONFIG_t *ux_regbuf;

    // Capture UART register block
    ux_regbuf = (volatile UART_CONFIG_t*)uart.handle; // Capture start of the UART register block
    
    // Check for ISR Flag Bits which need to be reset
    if ((ux_regbuf->status.value & UART_UxSTA_ISR_FLAGS_MASK))
    {
        Nop();
        
        ux_regbuf->status.bits.trmt = 0; // Clear Transmit Shifter Empty Interrupt Flag bit
        ux_regbuf->status.bits.txcif = 0; // Clear Transmit Collision Interrupt Enable bit
        ux_regbuf->status.bits.rxbkif = 0; // Clear Receive Break Interrupt Flag bit
        ux_regbuf->status.bits.ferr = 0; // Clear Framing Error Interrupt Flag bit
        ux_regbuf->status.bits.perr = 0; // Clear Parity Error/Address Received/Forward Frame Interrupt Flag bit
        ux_regbuf->status.bits.cerif = 0; // Clear Checksum Error Interrupt Flag bit
        ux_regbuf->status.bits.oerr = 0; // Clear Receive Buffer Overflow Interrupt Flag bit
        ux_regbuf->status.bits.abdovf = 0; // Clear Auto-Baud Rate Acquisition Interrupt Flag bit
        
    }
    
    _DebugUART_ErrorIF = 0; // Clear interrupt flag bit
    
}


