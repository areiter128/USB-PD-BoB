
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

/* Including header files */
#include <xc.h>
#include <stdbool.h>
#include <string.h>
#include "delay.h"
#include "uart2.h"
#include "proto24.h"
#include "interrupt_manager.h"

#define RX_TIMEOUT  10  // ticks of 10ms = 100ms

static volatile bool    timeout_flag;
static volatile uint8_t timeout_counter;


void Proto24Init(protocol_data_t * pData)
{
    INTERRUPT_GlobalDisable();
    UART2_Initialize();
    timeout_flag = false;
    timeout_counter = 0;
    if(pData != NULL)
        memset((void *)pData, 0, PROTO_P24_DSP_LEN);
    INTERRUPT_GlobalEnable();
}

// returns true if something new has been received over UART, otherwise false
bool Proto24Check(protocol_data_t *pData)
{
    uint8_t buff_len, transfer_len;
    bool ret = false;
    static bool WSOF = true;
 
    if(WSOF) // waiting for SOF - start of frame
    {
        if(!UART2_ReceiveBufferIsEmpty())
        {
            uint8_t byte = UART2_Read();
            if(byte == PROTO_SOF)
            {
                WSOF = false; // no longer waiting for SOF, now can load the packet
                timeout_counter++; // start timer for timeout
            }
        }
    }
    else
    {
        buff_len = 32 - (uint8_t)UART2_ReceiveBufferSizeGet(); // 32 must be replaced by UART2 API call
        if(buff_len >= PROTO_P24_DSP_LEN)
        {
            transfer_len = UART2_ReadBuffer((uint8_t *)pData, PROTO_P24_DSP_LEN);
            WSOF = true; // wait again for SOF
            if(transfer_len == PROTO_P24_DSP_LEN)
                ret = true;
        }
        // if not accumulated enough bytes in the RX uart buffer, then try again next Proto24Check cycle
    }
    if(timeout_flag)
    {
        WSOF = true;
        timeout_flag = false;
    }
    return ret;
}

void Proto24Send(protocol_event_t p24_event)
{
    UART2_Write(PROTO_SOF);
    UART2_WriteBuffer((uint8_t *)&p24_event, PROTO_DSP_P24_LEN);
}

// called by ISR once at 10ms
void  Proto24Tick(void)
{
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
}
