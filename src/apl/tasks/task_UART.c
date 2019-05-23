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
/*@@task_Switch.h
 * ***************************************************************************
 * File:   task_Switch.h
 * Author: M91406
 * 
 * Summary:
 * Source file of switch button task
 * 
 * Description:
 * This source file is used to register a global data structure allowing to edit
 * parameters of the task. It is also used to publish global function calls.
 * the main task routine is polling on the switch button of the DSP expander
 * board. When a switch event has been triggered, a global switch event flag 
 * is set in the task_Switch data structure for other tasks to respond to.
 * 
 * History:
 * 05/03/2018	File created
 * ***************************************************************************/


#include <xc.h>
#include "task_UART.h"

/* global variables */
volatile SMPS_UART_OBJECT_t smps_uart;

/* private scheduler variables */

#define SMPS_UART_FRMUPDT_INT_CNT 416   // number of scheduler cycles until data update
#define SMPS_UART_SEND_INT_CNT   1    // number of scheduler cycles until sending frame (e.g. 416=2500ms)
volatile uint16_t send_int_cnt = 0;
volatile uint16_t frm_update_int_cnt = 0;
volatile uint16_t msg_cnt = 0;

/* UART data frame definitions and private variables */

#define UART_IO_TIMEOUT 5000

#define FRM_START       0xAA    // start-byte
#define FRM_STOP        0x0D    // stop-byte

#define FRAME_START     1   // one start byte = 0xAA
#define FRAME_CID       2   // two bytes command ID
#define FRAME_DATA_LEN  2   // two bytes data length definition
#define FRAME_CRC       2   // two bytes for 16-bit CRC
#define FRAME_STOP      1   // one stop byte = 0x0D

#define FRAME_START_OVERHEAD    (FRAME_START + FRAME_CID + FRAME_DATA_LEN)
#define FRAME_STOP_OVERHEAD     (FRAME_CRC + FRAME_STOP)
#define FRAME_TOTAL_OVERHEAD    (FRAME_START_OVERHEAD + FRAME_STOP_OVERHEAD)

#define FRAME_TOTAL_RX_LENGTH   (CVRT_UxRXBUF_SIZE + FRAME_TOTAL_OVERHEAD)
#define FRAME_TOTAL_TX_LENGTH   (CVRT_UxTXBUF_SIZE + FRAME_TOTAL_OVERHEAD)

#define _UART_TX_DLEN           (uint16_t)((uint16_t)(UART_RxTx.TXBytes[3] << 8) | (uint16_t)UART_RxTx.TXBytes[4])
#define _UART_RX_DLEN           (uint16_t)((uint16_t)(UART_RxTx.RXBytes[3] << 8) | (uint16_t)UART_RxTx.RXBytes[4])
#define _UART_RX_CID            (uint16_t)((uint16_t)(UART_RxTx.RXBytes[1] << 8) | (uint16_t)UART_RxTx.RXBytes[2])
#define _UART_RX_CRC            (uint16_t)((uint16_t)(UART_RxTx.RXBytes[FRAME_START_OVERHEAD + _UART_RX_DLEN] << 8) | (uint16_t)UART_RxTx.RXBytes[FRAME_START_OVERHEAD + _UART_RX_DLEN + 1])

// private receive and transmit buffers
typedef struct 
{
    volatile SMPS_UART_STATUS_FLAGS_t status;   // UART transmission status bits
    
    volatile uint8_t RXBytes[FRAME_TOTAL_RX_LENGTH];
    volatile uint16_t UartRecLength;    // private receive data length for on-going transmissions
    volatile uint16_t UartRecCounter;   // private receive byte counter for on-going transmissions
    volatile uint16_t UartRecActionID;  // Copy of the command-ID
    
    volatile uint8_t TXBytes[FRAME_TOTAL_TX_LENGTH];
    volatile uint16_t UartSendLength;   // private transmit data length for on-going transmissions
    volatile uint16_t UartSendCounter;  // private transmit byte counter for on-going transmissions

//    volatile uint16_t UartCRCBuffer;    // private CRC buffer for on-going calculations
    volatile uint16_t UARTRXComplete;   // rECEIVE Complete flag
    volatile uint16_t UartTXSendDone;   // Transmit Complete flag
}SMPS_UART_DATA_HANDLER_t;

volatile SMPS_UART_DATA_HANDLER_t UART_RxTx;

/* private prototypes */
volatile inline int16_t  task_UARTsend(void);
volatile inline uint16_t task_UARTreceive(void);
volatile inline uint16_t task_DecodeFrame(void);
volatile uint16_t smpsuart_get_crc(volatile uint8_t *ptrDataFrame, volatile uint16_t data_len);

/*@@exec_TaskUART
 *****************************************************************************
 * Function:	 uint16_t init_uart(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure)
 *
 * Summary:
 * Initializes the uart module and opens a port
 *
 * Description:	
 * This routine initializes the UART peripheral module of the dsPIC33 and opens 
 * a port with user defined settings. 
 * Multiple UARTs can be used in parallel using the initialization routine 
 * below.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile uint16_t exec_TaskUART(void) {

    volatile uint16_t fres=0, i=0;

    Nop();
    Nop();
    Nop();

    // Check if a receive buffer is ready to be processed in every scheduler call cycle
    if(UART_RxTx.status.flag.RXFrameReady)
    {
        fres = task_UARTreceive();
        
        if(fres)
        {  
            task_DecodeFrame();

            UART_RxTx.UARTRXComplete = 0;
            smps_uart.RXBytes.id = 0; // reset ID after it was executed
            
        }
        else
        { return(1); }
    }
    // send status frame when the send-tick-timer interval SMPS_UART_FRMUPDT_INT_CNT has expired
    if((frm_update_int_cnt++ == SMPS_UART_FRMUPDT_INT_CNT) && 
        (UART_RxTx.UartTXSendDone = 1))
    {
        
        frm_update_int_cnt = 0;
        UART_RxTx.status.flag.TXFrameReady = 0;

        // build data frame
        smps_uart.TXBytes.id = 0x434C;
        smps_uart.TXBytes.data_len = 4;
        smps_uart.TXBytes.data[0] = (task_mgr.cpu_load.load >> 8);
        smps_uart.TXBytes.data[1] = (task_mgr.cpu_load.load & 0x00FF);
        smps_uart.TXBytes.data[2] = (msg_cnt >> 8);
        smps_uart.TXBytes.data[3] = (msg_cnt & 0x00FF);

        smps_uart.TXBytes.crc = smpsuart_get_crc((uint8_t *)&smps_uart.TXBytes.data[0], smps_uart.TXBytes.data_len);
        
        // copy global data frame into buffer frame
        UART_RxTx.TXBytes[0] = FRM_START;
        UART_RxTx.TXBytes[1] = (smps_uart.TXBytes.id >> 8);    // CID high byte
        UART_RxTx.TXBytes[2] = (smps_uart.TXBytes.id & 0x00FF);    // CID low byte

        UART_RxTx.TXBytes[3] = (smps_uart.TXBytes.data_len >> 8);    // data length high byte
        UART_RxTx.TXBytes[4] = (smps_uart.TXBytes.data_len & 0x00FF);    // data length low byte
        
        for(i=0; i<smps_uart.TXBytes.data_len; i++)
        {
            UART_RxTx.TXBytes[FRAME_START_OVERHEAD + i] = smps_uart.TXBytes.data[i]; // copy data byte #n
        }

        UART_RxTx.TXBytes[smps_uart.TXBytes.data_len + FRAME_START_OVERHEAD + 0] = (smps_uart.TXBytes.crc >> 8);    // CRC high byte
        UART_RxTx.TXBytes[smps_uart.TXBytes.data_len + FRAME_START_OVERHEAD + 1] = (smps_uart.TXBytes.crc & 0x00FF);    // CRC low byte
        UART_RxTx.TXBytes[smps_uart.TXBytes.data_len + FRAME_START_OVERHEAD + 2] = FRM_STOP;
        
        UART_RxTx.UartSendLength = _UART_TX_DLEN;
        UART_RxTx.UartSendCounter = 0;
        UART_RxTx.UartTXSendDone = 0;
        
        UART_RxTx.status.flag.TXFrameReady = 1;
        msg_cnt++;
//        
//UART_RxTx.UartSendCounter = 1;
//CVRT_UxRXREG = 0xAA;

    }
    
    if ((UART_RxTx.status.flag.TXFrameReady) && (!UART_RxTx.UartTXSendDone))
    {
        if(send_int_cnt++ == SMPS_UART_SEND_INT_CNT)
        {
            send_int_cnt = 0;
            task_UARTsend();
        }

    }

    return (fres);
}

/*@@init_TaskUART
 *****************************************************************************
 * Function:	 uint16_t init_TaskUART(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure)
 *
 * Summary:
 * Initializes the uart module and opens a port
 *
 * Description:	
 * This routine initializes the UART peripheral module of the dsPIC33 and opens 
 * a port with user defined settings. 
 * Multiple UARTs can be used in parallel using the initialization routine 
 * below.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile uint16_t init_TaskUART(void) {
    
    volatile uint16_t fres = 0, i = 0;

    // copy essential port setting into data structure
    smps_uart.port_index = CVRT_UART_IDX;
    smps_uart.baudrate = CVRT_UART_BAUDRATE;

    // reset private variables
    UART_RxTx.UartRecCounter = 0; // reset RX buffer counter
    UART_RxTx.UartSendCounter = 0; // reset TX buffer counter

    // clear receive data frame
    for (i = 0; i < FRAME_TOTAL_RX_LENGTH; i++) {
        UART_RxTx.RXBytes[i] = 0;
    }

    // clear transmit data frame
    for (i = 0; i < FRAME_TOTAL_TX_LENGTH; i++) {
        UART_RxTx.TXBytes[i] = 0;
    }

    // reset transmit buffer 
    UART_RxTx.TXBytes[0] = 0xAA; // pre-charge START OF FRAME code
    UART_RxTx.TXBytes[FRAME_TOTAL_TX_LENGTH - 1] = 0x0D; // pre-charge STOP OF FRAME code

    // Initialize UART peripheral
    fres = init_smps_uart();

    // set DATA TRANSMISSION COMPLETE flag to enable new transmissions
    UART_RxTx.UartTXSendDone = 1;   
    
    return (fres);
}

/*@@task_UARTsendFrame
 *****************************************************************************
 * Function:	 int16_t task_UARTsendFrame(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure
 *
 * Summary:
 * Sends pre-charged data frame over UART
 *
 * Description:	
 * This routine sends a pre-charged data frame over UART. The 16-bit CRC 
 * needs to be calculated and its result be placed in the data frame in 
 * advance.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile inline int16_t task_UARTsend(void) 
{
    volatile uint16_t fres=1, timeout=0;
 
    // send byte
    while((_CVRT_UxTXBF) && (timeout++ < UART_IO_TIMEOUT));
    if(timeout < UART_IO_TIMEOUT) 
    {
        // send test code A, B, C, D, E, ... in the size of the recent transmit buffer 
        // by direct write to the UART Transmit Buffer Register
        // CVRT_UxTXREG = 0x041 + UART_RxTx.UartSendCounter++; // UART_RxTx.TXBytes[UART_RxTx.UartSendCounter++];
        
        // call library function to send byte via UART
        fres &= gsuart_write_byte(smps_uart.port_index, UART_RxTx.TXBytes[UART_RxTx.UartSendCounter++]);
    
        // when all bytes of a data frame has been sent, reset flags and counter
        if(UART_RxTx.UartSendCounter > (_UART_TX_DLEN + FRAME_TOTAL_OVERHEAD))
        {
            UART_RxTx.UartSendCounter = 0;
            UART_RxTx.status.flag.TXFrameReady = 0;
            UART_RxTx.UartTXSendDone = 1;
        }
    }
    else { fres = 0; }
    
    return(fres);
}

/*@@task_UARTsend
 *****************************************************************************
 * Function:	 int16_t task_UARTsend(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure
 *
 * Summary:
 * Sends a single byte over UART
 *
 * Description:	
 * This routine sends a single byte from the data frame over UART and processes 
 * the 16-bit CRC in parallel, which will be added to the end of the communication 
 * frame.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/


volatile inline uint16_t task_UARTreceive(void) {

    volatile uint16_t crc_buffer=0;

    // calculate 16-bit CRC of data content
    crc_buffer = smpsuart_get_crc((volatile uint8_t *)&smps_uart.RXBytes.data[0], smps_uart.RXBytes.data_len);

    // if CRC matches transmitted CRC code, then the data frame is considered to be valid
    // if (UART_RxTx.UartCRCBuffer == smps_uart.RXBytes.crc) 
    if (crc_buffer == smps_uart.RXBytes.crc) 
    {
        UART_RxTx.status.flag.RXFrameReady = 0;
        UART_RxTx.UARTRXComplete = 1;
        smps_uart.status.flags = UART_RxTx.status.flags;
    }

    // return the RXComplete-Flag
    return (UART_RxTx.UARTRXComplete);
}

/*@@task_DecodeFrame
 *****************************************************************************
 * Function:	 int16_t task_DecodeFrame(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure
 *
 * Summary:
 * Decodes a comm frame once it has been received
 *
 * Description:	
 * In this routine a comm-frame is decoded once it has been completely received.
 * The ActionID forces a defined response.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile inline uint16_t task_DecodeFrame(void) {

//    volatile uint16_t value16 = 0;

    switch (smps_uart.RXBytes.id) 
    {
        case (0x01DD):  // toggles a test-pin when the command has successfully been received 
            TSTOUT_WR ^= 1;
            break;
            
        default: // unknown command
            return (0);
    }

    return (1);

}

/*@@smpsuart_get_crc
 *****************************************************************************
 * Function:	 int16_t smpsuart_get_crc(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure
 *
 * Summary:
 * Calculates the CRC16 across a given array line
 *
 * Description:	
 * This routine is called after a communication data frame was received or 
 * before a new data frame is sent out. The CRC is only calculated across 
 * the data content, excluding START, ID, DATA_LEN, CRC and STOP.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/
volatile uint16_t smpsuart_get_crc(volatile uint8_t *ptrDataFrame, volatile uint16_t data_len)
{
    volatile uint16_t result=0;
    volatile uint16_t i=0;
    volatile uint16_t byte_index;
    volatile uint8_t CHECK=0;

    // calculate 16-bit CRC of data content
    for (byte_index = 0; byte_index < data_len; byte_index++) 
    {
        CHECK = *ptrDataFrame;
        
        result ^= *ptrDataFrame;
        ptrDataFrame++;
        
        for (i = 0; i < 8; ++i) 
        {
            if ((result & 1) == 1)
                result = (result >> 1) ^ 0xA001;
            else
                result = (result >> 1);
        }
    }

    return(result);
}

/*@@_CVRT_UxRXInterrupt
 *****************************************************************************
 * Function:	 void __attribute__((__interrupt__, no_auto_psv)) _CVRT_UxRXInterrupt(void)
 * Arguments:	 (none)
 * Return Value: (none)
 *
 * Summary:
 * UART RX interrupt is used to fill the comm-frame, tracking the comm-frame position
 *
 * Description:	
 * In this interrupt service routine the receive buffer is filled. while receiving 
 * bytes, the buffer position is tracked and data contents is filtered.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

void __attribute__((__interrupt__, no_auto_psv)) _CVRT_UxRXInterrupt() 
{

    volatile uint8_t rec_buf=0;
    volatile uint16_t i=0;
    
    rec_buf = CVRT_UxRXREG; // read receive buffer in a buffer variable
    
    // Sync up with START-OF-FRAME
    if ((rec_buf == FRM_START) && (!UART_RxTx.status.flag.SOF))
    {
        UART_RxTx.status.flag.RXFrameReady = 0;
        UART_RxTx.UartRecCounter = 1;
        UART_RxTx.status.flag.SOF = 1;
        UART_RxTx.UartRecLength = 0;
        UART_RxTx.RXBytes[0] = rec_buf; 
    }

    // Receiving command ID and data length
    else if (UART_RxTx.status.flag.SOF)
    {

        // Receive transmission bytes adding them to the data array
        UART_RxTx.RXBytes[UART_RxTx.UartRecCounter++] = rec_buf;

        // when START, CID and DLEN has been received, update data length setting
        if (UART_RxTx.UartRecCounter == FRAME_START_OVERHEAD) 
        { UART_RxTx.UartRecLength = _UART_RX_DLEN; }

        // if data-length, STOP and SOF flag bit adds up, the frame is perceived to be complete
        // (no CRC check yet)
        if ((rec_buf == FRM_STOP) && 
            (UART_RxTx.UartRecCounter > (UART_RxTx.UartRecLength + FRAME_START_OVERHEAD)) && 
            (UART_RxTx.status.flag.SOF))
        {
            // copy received frame in global data structure
            smps_uart.RXBytes.start = UART_RxTx.RXBytes[0];
            smps_uart.RXBytes.id = _UART_RX_CID;
            smps_uart.RXBytes.data_len = _UART_RX_DLEN;
                
            for(i=FRAME_START_OVERHEAD; i<(UART_RxTx.UartRecLength + FRAME_START_OVERHEAD); i++)
            {
                smps_uart.RXBytes.data[i-FRAME_START_OVERHEAD] = UART_RxTx.RXBytes[i];
            }
            
            smps_uart.RXBytes.crc = _UART_RX_CRC;       // copy CRC code into global data structure
            smps_uart.RXBytes.stop = rec_buf;           // copy STOP into global data structure

            // set/clear status flags
            UART_RxTx.status.flag.RXFrameReady = 1;    // set FRAME READY flag
            UART_RxTx.status.flag.RXComplete = 0;      // clear RX COMPLETE flag (requires validated CRC to be set)
            UART_RxTx.status.flag.SOF = 0;             // clear START-OF-FRAME flag

            // copy status flags into global UART object
            smps_uart.status.flags = UART_RxTx.status.flags;
                
        }

    }

    _CVRT_UxRXIF = 0;
    
    return;
    
}


/*@@_CVRT_UxTXInterrupt
 *****************************************************************************
 * Function:	 void __attribute__((__interrupt__, no_auto_psv)) _CVRT_UxTXInterrupt(void)
 * Arguments:	 (none)
 * Return Value: (none)
 *
 * Summary:
 * UART TX interrupt is used to send the comm-frame, tracking the comm-frame position
 *
 * Description:	
 * In this interrupt service routine the transmit buffer is sent. The interrupt is
 * configured to be called when the buffer runs empty. The ISR code then pulls in 
 * the next byte of the data frame until the entire frame has been sent.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

void __attribute__((__interrupt__, no_auto_psv)) _CVRT_UxTXInterrupt() 
{

    Nop();
    Nop();
    Nop();

    if(!UART_RxTx.status.flag.TXFrameReady)
    {
        return;
    }
    if(UART_RxTx.UartSendCounter < (UART_RxTx.UartSendLength + FRAME_TOTAL_OVERHEAD))
    {
        CVRT_UxRXREG = UART_RxTx.TXBytes[UART_RxTx.UartSendCounter++];
//        gsuart_write(smps_uart.port_index, UART_RxTx.TXBytes[UART_RxTx.UartSendCounter++]);
    }
    else
    {
        UART_RxTx.UartSendCounter = 0;
        UART_RxTx.status.flag.TXFrameReady = 0;
        UART_RxTx.UartTXSendDone = 1;
        smps_uart.status.flags = UART_RxTx.status.flags;
    }

    _CVRT_UxTXIF = 0;

    return;
    
}



// EOF
