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
/*!task_Switch.h
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
#include <stdint.h>
#include <stdbool.h>

#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"

/* global variables */
//volatile SMPS_UART_OBJECT_t smps_uart;

/* private scheduler variables */

#define SMPS_UART_FRMUPDT_INT_CNT 416   // number of scheduler cycles until data update
#define SMPS_UART_SEND_INT_CNT   1      // number of scheduler cycles until sending frame (e.g. 416=2500ms)


/* UART data frame definitions and private variables */

#define FRM_START       0x55    // start-byte
#define FRM_STOP        0x0D    // stop-byte

#define FRAME_START     1   // one start byte = 0x55
#define FRAME_CID       2   // two bytes command ID
#define FRAME_DATA_LEN  2   // two bytes data length definition
#define FRAME_CRC       2   // two bytes for 16-bit CRC
#define FRAME_STOP      1   // one stop byte = 0x0D

#define FRAME_START_OVERHEAD    (FRAME_START + FRAME_CID + FRAME_DATA_LEN)
#define FRAME_STOP_OVERHEAD     (FRAME_CRC + FRAME_STOP)
#define FRAME_TOTAL_OVERHEAD    (FRAME_START_OVERHEAD + FRAME_STOP_OVERHEAD)

#define FRAME_TOTAL_RX_LENGTH   (CVRT_UxRXBUF_SIZE_ID0100 + FRAME_TOTAL_OVERHEAD)
#define FRAME_TOTAL_TX_LENGTH   (CVRT_UxTXBUF_SIZE_ID0100 + FRAME_TOTAL_OVERHEAD)

#define _UART_TX_DLEN           (uint16_t)((uint16_t)(UART_RxTx.TXBytes[3] << 8) | (uint16_t)UART_RxTx.TXBytes[4])
#define _UART_RX_DLEN           (uint16_t)((uint16_t)(UART_RxTx.RXBytes[3] << 8) | (uint16_t)UART_RxTx.RXBytes[4])
#define _UART_RX_CID            (uint16_t)((uint16_t)(UART_RxTx.RXBytes[1] << 8) | (uint16_t)UART_RxTx.RXBytes[2])
#define _UART_RX_CRC            (uint16_t)((uint16_t)(UART_RxTx.RXBytes[FRAME_START_OVERHEAD + _UART_RX_DLEN] << 8) | (uint16_t)UART_RxTx.RXBytes[FRAME_START_OVERHEAD + _UART_RX_DLEN + 1])

#define CVRT_UxRXBUF_SIZE_ID0100       (64)
#define CVRT_UxTXBUF_SIZE_ID0100       CVRT_UxRXBUF_SIZE_ID0100

#define GUI_ID_0100        0x001
 
#define CRCH_POS_ID0100     FRAME_START_OVERHEAD+CVRT_UxRXBUF_SIZE_ID0100 
#define CRCL_POS_ID0100     FRAME_START_OVERHEAD+CVRT_UxRXBUF_SIZE_ID0100+1  


// From GUI to dsPIC

#define RX_VOUT_CH1_INDEX      FRAME_START_OVERHEAD
#define RX_IOUT_CH1_INDEX      FRAME_START_OVERHEAD+2
#define RX_VOUT_CH2_INDEX      FRAME_START_OVERHEAD+4
#define RX_IOUT_CH2_INDEX      FRAME_START_OVERHEAD+6
#define RX_TEMPERATURE_INDEX   FRAME_START_OVERHEAD+8
#define RX_CONFIG_BITS_INDEX   FRAME_START_OVERHEAD+10


// Bit masks 
#define RX_ON_OFF_CH1_BIT      (1<<0)
#define RX_ON_OFF_CH2_BIT      (1<<1)
#define RX_USB_CH1_ENABLED     (1<<2)
#define RX_USB_CH2_ENABLED     (1<<3)
#define RX_TEMP_SIMULATION     (1<<4)


// From dsPIC to GUI

#define TX_VIN_INDEX            FRAME_START_OVERHEAD
#define TX_VOUT_CH1_INDEX       FRAME_START_OVERHEAD+2
#define TX_IOUT_CH1_INDEX       FRAME_START_OVERHEAD+4
#define TX_CONVERTER_STATUS     FRAME_START_OVERHEAD+6
#define TX_CONVERTER_FAULT      FRAME_START_OVERHEAD+8
#define TX_VOUT_CH2_INDEX       FRAME_START_OVERHEAD+10
#define TX_IOUT_CH2_INDEX       FRAME_START_OVERHEAD+12
#define TX_TEMPERATURE_INDEX    FRAME_START_OVERHEAD+14
#define TX_UPD1_DEVICE_VID      FRAME_START_OVERHEAD+16
#define TX_UPD1_DEVICE_PID      FRAME_START_OVERHEAD+18
#define TX_UPD2_DEVICE_VID      FRAME_START_OVERHEAD+20
#define TX_UPD2_DEVICE_PID      FRAME_START_OVERHEAD+22



// private receive and transmit buffers
typedef struct
  {
      unsigned RXFrameReady : 1;
      unsigned TXFrameReady : 1;
      unsigned TXSendDone : 1;
      unsigned Sof : 1;

      unsigned not_used: 12;

      volatile uint8_t RXBytes[FRAME_TOTAL_RX_LENGTH];;
      volatile uint16_t UartRecCounter;
      volatile uint16_t UartRecActionID;
      volatile uint16_t UartRecLength;

      volatile uint8_t TXBytes[FRAME_TOTAL_TX_LENGTH];
      volatile uint16_t UartSendCounter;
      volatile uint16_t UartSendLength;

      volatile uint16_t CRC;
  } SMPS_UART_DATA_HANDLER_t;


volatile SMPS_UART_DATA_HANDLER_t UART_RxTx;

/* private prototypes */
volatile uint16_t  init_DebugUART(void);
volatile uint16_t  exec_DebugUART(void);
volatile uint16_t  dispose_DebugUART(void);

volatile uint16_t  task_DebugUARTsend_ID0100(void);
volatile uint16_t task_DebugUARTreceive(void);
volatile uint16_t task_DebugDecodeFrame(void);
volatile uint16_t smpsuart_get_crc(volatile uint8_t *ptrDataFrame, volatile uint16_t data_len);

/*!exec_DebugUART
 *****************************************************************************
 * Function:	 uint16_t exec_DebugUART(void)
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

volatile uint16_t exec_DebugUART(void) 
{
    volatile uint16_t fres = 1;
    static task_cycles_counter=0;
    
    if (1==UART_RxTx.RXFrameReady)
    {
      UART_RxTx.RXFrameReady = 0;
      fres=task_DebugUARTreceive();
    }
            
    
    // For protocol debug only
    // TODO decide how to trigger buffer transmission
    
    task_cycles_counter++;
    if(task_cycles_counter>50)
    {
        UART_RxTx.TXFrameReady=1;
        task_cycles_counter=0;
    }
        
    
    if(1==UART_RxTx.TXSendDone && 1==UART_RxTx.TXFrameReady)
    {
        fres=task_DebugUARTsend_ID0100();
    }
    
    return (fres);
}

/*!init_DebugUART
 *****************************************************************************
 * Function:	 uint16_t init_DebugUART(void)
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

volatile uint16_t init_DebugUART(void) {
    
    volatile uint16_t fres = 0;

#ifdef __00173_USB_PD_BOB_R20__
    
    HUB_PRTPWR1_INIT_OUTPUT;
    HUB_PRTPWR2_INIT_INPUT;
    
    // Set PPS for UART
    pps_UnlockIO();
    pps_RemapInput(HUB_PRTPWR2_RP, PPSIN_U2RX);
    pps_RemapOutput(HUB_PRTPWR1_RP, PPSOUT_U2TX);
    pps_LockIO();    
    
#endif    

#ifdef  __MA330048_P33CK_R30_USB_PD_BOB__   
    
    UART_TX_INIT_OUTPUT;
    UART_RX_INIT_INPUT;

    // Set PPS for UART
    pps_UnlockIO();
    pps_RemapInput(UART_RX_RP, PPSIN_U2RX);
    pps_RemapOutput(UART_TX_RP, PPSOUT_U2TX);
    pps_LockIO();
    
#endif    
    // Configure UART peripheral
    fres=smps_uart_open_port(CVRT_UART_IDX,CVRT_UART_BAUDRATE, CVRT_UART_DATA_BITS, CVRT_UART_PARITY, CVRT_UART_STOP_BITS,CVRT_UART_IRS_PRIORITY);

    UART_RxTx.TXSendDone=1; //
    return (fres);
}

/*!dispose_DebugUART
 *****************************************************************************
 * Function:	 uint16_t dispose_DebugUART(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 2: failure
 *
 * Summary:
 * Resets the UART driver and used peripherals
 *
 * Description:	
 * This routine resets all data structures, closes the UART, resets the 
 * peripheral configuration, disables all interrupts and resets used to
 * default (high impedance input).
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile uint16_t  dispose_DebugUART(void) {
    
    // ToDo: Add DISPOSE code here (see description above)
    
    return (1);
}


/*!task_DecodeFrame
 *****************************************************************************
 * Function:	 int16_t task_DecodeFrame(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 0: failure
 *
 * Summary:
 * Decodes a UART frame once it has been received and CRC verified
 *
 * Description:	
 * In this routine a comm-frame is decoded once it has been completely received.
 * The ActionID forces a defined response.
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

inline volatile uint16_t task_DebugDecodeFrame(void) 
{
    switch(UART_RxTx.UartRecActionID)
        {
            case GUI_ID_0100:
            {
                // Recover 1/10 once the GUI will send correct data
//                tmpf=(float)(UART_RxTx.RXBytes[VSETP_INDEX]*256+UART_RxTx.RXBytes[VSETP_INDEX+1])*K_VDCOUT_TO_VDCOUTBIT/10.0;
//                gui_vsetp=(unsigned short)tmpf;
//                tmpf=(float)(UART_RxTx.RXBytes[IMAX_INDEX]*256+UART_RxTx.RXBytes[IMAX_INDEX+1])*(K_I_TO_IBIT*0.9/10.0); // Average value in bit
//                gui_imax=(unsigned short)tmpf;
//                if(gui_imax>PFC_MAX_INPUT_CURRENT)
//                {
//                    gui_imax=PFC_MAX_INPUT_CURRENT; 
//                }
//                gui_config_bits.converter_conf_bits=UART_RxTx.RXBytes[BITS_INDEX]*256+UART_RxTx.RXBytes[BITS_INDEX+1];
                
                break;
            }
            default:
            {
                
            }
        }
        UART_RxTx.UartRecActionID = 0;  
    return (1);
}

/*!smpsuart_get_crc
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


volatile uint16_t smpsuart_get_crc(volatile uint8_t *ptrDataFrame,volatile uint16_t data_len)
{
    uint16_t cnt1,cnt2,crc=0;
    
    for (cnt1 = 0; cnt1 < (data_len + 5); cnt1++)
    {
        crc ^= ptrDataFrame[cnt1];
        for (cnt2 = 0; cnt2 < 8; ++cnt2)
        {
            if ((crc & 1) == 1)
                crc = (crc >> 1) ^ 0xA001;
            else
                crc = (crc >> 1);
        }
    }
    return(crc);
}


/*!_CVRT_UxRXInterrupt
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

    unsigned short rx_tmp;
    
    rx_tmp = CVRT_UxRXREG;
    if (( rx_tmp == FRM_START) &&(!UART_RxTx.Sof))
    {
        UART_RxTx.RXBytes[0]=rx_tmp;
        UART_RxTx.UartRecCounter = 1;
        UART_RxTx.Sof = 1;
    } 
    else
    {
        UART_RxTx.RXBytes[UART_RxTx.UartRecCounter++] = rx_tmp;
    }

    if (UART_RxTx.UartRecCounter == FRAME_START_OVERHEAD) 
    {
        UART_RxTx.UartRecLength = _UART_RX_DLEN;
    }

    if(UART_RxTx.UartRecCounter >(UART_RxTx.UartRecLength + FRAME_START_OVERHEAD + FRAME_CRC)) 
    {
        if ((rx_tmp == FRM_STOP) && (UART_RxTx.Sof))
        {
            UART_RxTx.RXFrameReady = 1;
            UART_RxTx.UartRecActionID = (UART_RxTx.RXBytes[1] << 8) | UART_RxTx.RXBytes[2];
            UART_RxTx.Sof = 0;
        }
        else
        {
            UART_RxTx.UartRecCounter=0;
            UART_RxTx.Sof=0;
        }
    }
    _CVRT_UxRXIF = false;
}
    
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CVRT_UxEInterrupt( void )
{
    if ((_CVRT_OERR == 1))
    {
        _CVRT_OERR = 0;
        UART_RxTx.UartRecCounter = 0;
        UART_RxTx.Sof = 0;
    }

    _CVRT_UxEIF = false;
}



/*!_CVRT_UxTXInterrupt
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

    if(UART_RxTx.UartSendCounter<(UART_RxTx.UartSendLength + FRAME_START_OVERHEAD+FRAME_STOP_OVERHEAD)) 
    {
        CVRT_UxTXREG=UART_RxTx.TXBytes[UART_RxTx.UartSendCounter++];
    }
    else
    {
        UART_RxTx.TXSendDone = 1;
    }
    _CVRT_UxTXIF = 0;
    return;
}


volatile uint16_t task_DebugUARTreceive(void)
{
    volatile uint16_t fres = 1;
    unsigned short crc;
    float tmpf;
    
    UART_RxTx.CRC=smpsuart_get_crc(UART_RxTx.RXBytes,UART_RxTx.UartRecLength);
    crc = (UART_RxTx.RXBytes[UART_RxTx.UartRecLength+5] << 8) | UART_RxTx.RXBytes[UART_RxTx.UartRecLength+6];

    if (UART_RxTx.CRC == crc) // CRC OK
    {
        switch(UART_RxTx.UartRecActionID)
        {
        
            // Manage converter on off
            case GUI_ID_0100:
            {
                // Recover 1/10 once the GUI will send correct data
//                tmpf=(float)(UART_RxTx.RXBytes[VSETP_INDEX]*256+UART_RxTx.RXBytes[VSETP_INDEX+1])*K_VDCOUT_TO_VDCOUTBIT/10.0;
//                gui_vsetp=(unsigned short)tmpf;
//                tmpf=(float)(UART_RxTx.RXBytes[IMAX_INDEX]*256+UART_RxTx.RXBytes[IMAX_INDEX+1])*(K_I_TO_IBIT*0.9/10.0); // Average value in bit
//                gui_imax=(unsigned short)tmpf;
//                if(gui_imax>PFC_MAX_INPUT_CURRENT)
//                {
//                    gui_imax=PFC_MAX_INPUT_CURRENT; 
//                }
//                gui_config_bits.converter_conf_bits=UART_RxTx.RXBytes[BITS_INDEX]*256+UART_RxTx.RXBytes[BITS_INDEX+1];
                
                break;
            }
            default:
            {
                
            }
        }
        UART_RxTx.UartRecActionID = 0;  
    } 
    else
    {
        fres=0;
    }
    return(fres);
}

/*!task_DebugUARTsend_ID0100
 *****************************************************************************
 * Function:	 int16_t task_DebugUARTsend_ID0100(void)
 * Arguments:	 (none)
 * Return Value: 1: success, 0: failure
 *
 * Summary:
 * Sends pre-charged data frame over UART for protocol ID 0x0100
 *
 * Description:	
 * This routine sends data frame over UART. 
 * The 16-bit CRC is calculated befor sending data
 *
 *
 * See also:
 * (none)
 * 
 *****************************************************************************/

volatile uint16_t task_DebugUARTsend_ID0100(void)
{   
    volatile uint16_t fres = 1;
    
    static unsigned short iin;
    static unsigned short cnt,tmps;
    static float tmpf;
    
    UART_RxTx.TXBytes[0] = FRM_START;
    UART_RxTx.TXBytes[1] = (unsigned char)((GUI_ID_0100 & 0xFF00)>>8);
    UART_RxTx.TXBytes[2] = (unsigned char)((GUI_ID_0100 & 0x00FF));
    UART_RxTx.UartSendLength = CVRT_UxTXBUF_SIZE_ID0100;
    UART_RxTx.TXBytes[3] = (unsigned char)(((CVRT_UxTXBUF_SIZE_ID0100) & 0xFF00)>>8);
    UART_RxTx.TXBytes[4] = (unsigned char)(((CVRT_UxTXBUF_SIZE_ID0100) & 0x00FF));
    
 
    
    //tmpf=10*(float)Voutavg1/K_VDCOUT_TO_VDCOUTBIT;
    //tmps=(unsigned short)tmpf;
    tmps=123;
    UART_RxTx.TXBytes[TX_VIN_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_VIN_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=51;
    UART_RxTx.TXBytes[TX_VOUT_CH1_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_VOUT_CH1_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=151;
    UART_RxTx.TXBytes[TX_IOUT_CH1_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_IOUT_CH1_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=0x001f;
    UART_RxTx.TXBytes[TX_CONVERTER_STATUS]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_CONVERTER_STATUS+1]=(unsigned char)(tmps&0xff);

    tmps=0x1;
    UART_RxTx.TXBytes[TX_CONVERTER_FAULT]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_CONVERTER_FAULT+1]=(unsigned char)(tmps&0xff);

    tmps=49;
    UART_RxTx.TXBytes[TX_VOUT_CH2_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_VOUT_CH2_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=290;
    UART_RxTx.TXBytes[TX_IOUT_CH2_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_IOUT_CH2_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=350;
    UART_RxTx.TXBytes[TX_TEMPERATURE_INDEX]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_TEMPERATURE_INDEX+1]=(unsigned char)(tmps&0xff);
    
    tmps=1;
    UART_RxTx.TXBytes[TX_UPD1_DEVICE_VID]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_UPD1_DEVICE_VID+1]=(unsigned char)(tmps&0xff);
    
    tmps=2;
    UART_RxTx.TXBytes[TX_UPD1_DEVICE_PID]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_UPD1_DEVICE_PID+1]=(unsigned char)(tmps&0xff);
    
    tmps=3;
    UART_RxTx.TXBytes[TX_UPD2_DEVICE_VID]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_UPD2_DEVICE_VID+1]=(unsigned char)(tmps&0xff);
    
    tmps=4;
    UART_RxTx.TXBytes[TX_UPD2_DEVICE_PID]=(unsigned char)(tmps>>8);
    UART_RxTx.TXBytes[TX_UPD2_DEVICE_PID+1]=(unsigned char)(tmps&0xff);
    
    UART_RxTx.CRC=smpsuart_get_crc(UART_RxTx.TXBytes,CVRT_UxTXBUF_SIZE_ID0100);
    UART_RxTx.TXBytes[CRCH_POS_ID0100]=(unsigned char)((UART_RxTx.CRC & 0xff00)>>8);
    UART_RxTx.TXBytes[CRCL_POS_ID0100]=(unsigned char)((UART_RxTx.CRC & 0x00ff));
    
    UART_RxTx.TXBytes[UART_RxTx.UartSendLength + 7] = FRM_STOP;
    UART_RxTx.UartSendCounter=1;
    UART_RxTx.TXSendDone = 0;
    UART_RxTx.TXFrameReady = 0;
    
    CVRT_UxTXREG=UART_RxTx.TXBytes[0]; // It starts transmission managed by UART TX interrupt
    return(fres);
}

// EOF
