
/**********************************************************************
Copyright(c) 2018 Microchip Technology Inc. and its subsidiaries.
Subject to your compliance with these terms, you may use Microchip
software and any derivatives exclusively with Microchip products. It
is your responsibility to comply with third party license terms
applicable to your use of third-party software (including open source
software) that may accompany Microchip software.
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
FOR A PARTICULAR PURPOSE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THIS SOFTWARE.
**********************************************************************/

#include <xc.h>
#include <stdbool.h>
#include <string.h>
#include "mcc.h"
#include "delay.h"
#include "protocol.h"

#define RX_TIMEOUT  100  // ticks of 1ms = 100ms
#define TX_INTERVAL 1000 // ticks of 1ms = 1000ms

static bool    timeout_flag; // waiting for start of frame, timeout flag
static uint8_t timeout_counter;
static bool    tx_flag;

void ProtocolInit(void)
{
    tx_flag = false;
    // assume that UART1 has been initialized by MCC functions
}

protocol_event_t ProtocolCheck(protocol_data_t *pData)
{
    volatile uint8_t buff_len;
    volatile protocol_event_t ret = PROTO_NO_EVENT;
    static bool WSOF = true;
 
    if(WSOF) // waiting for SOF - start of frame
    {
        if(!UART1_ReceiveBufferIsEmpty())
        {
            uint8_t byte = UART1_Read();
            if(byte == PROTO_SOF)
            {
                WSOF = false; // no longer waiting for SOF, now can load the packet
                timeout_counter++; // start timer for timeout
            }
        }
    }
    else
    {
        buff_len = 32 - (uint8_t)UART1_ReceiveBufferSizeGet(); // 32 must be replaced by UART1 API call
        if(buff_len >= PROTO_DSP_P24_LEN)
        {
            UART1_ReadBuffer((uint8_t *)&ret, PROTO_DSP_P24_LEN);
            WSOF = true; // wait again for SOF
        }
        // if not accumulated enough bytes in the RX uart buffer, then try again next ProtocolCheck cycle
    }
    
    if(timeout_flag)
    {
        WSOF = true;
        timeout_flag = false;
    }
    
    // this flag is activated by timer
    if(tx_flag)
    {
        tx_flag = false;
        UART1_Write(PROTO_SOF);
        UART1_WriteBuffer(pData->byte_array, PROTO_P24_DSP_LEN);
    }
    return ret;
}

void ProtocolClose(void)
{
    tx_flag = false;
    while((UART1_TRANSFER_STATUS_TX_EMPTY & UART1_TransferStatusGet()) == 0)
        ;
    __delay_ms(50);
    U1STAbits.UTXEN = 0;
    U1MODEbits.UARTEN = 0;
}

// called by ISR once at 1ms
void  ProtocolTick(void)
{
    static uint16_t count = 0;
    if(timeout_counter) // started
    {
        if(timeout_counter >= RX_TIMEOUT) // timer expired
        {
            timeout_flag = true; // trigger the flag
            timeout_counter = 0; // and clear counter
        }
        else
        {
            timeout_counter++;
        }
    }
    
    count++;
    if(count >= TX_INTERVAL)
    {
        count = 0;
        tx_flag = true;  // once at each 10 second
    }
}