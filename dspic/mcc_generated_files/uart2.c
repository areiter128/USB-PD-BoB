/**
  UART2 Generated Driver File 

  @Company
    Microchip Technology Inc.

  @File Name
    uart2.c

  @Summary
    This is the generated source file for the UART2 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for UART2. 
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  dsPIC33CK256MP505
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "uart2.h"

/**
  Section: Data Type Definitions
*/

/** UART Driver Queue Status

  @Summary
    Defines the object required for the status of the queue.
*/

typedef union
{
    struct
    {
            uint8_t full:1;
            uint8_t empty:1;
            uint8_t reserved:6;
    }s;
    uint8_t status;
}

UART_BYTEQ_STATUS;

/** UART Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

*/

typedef struct
{
    /* RX Byte Q */
    uint8_t                                      *rxTail ;

    uint8_t                                      *rxHead ;

    /* TX Byte Q */
    uint8_t                                      *txTail ;

    uint8_t                                      *txHead ;

    UART_BYTEQ_STATUS                        rxStatus ;

    UART_BYTEQ_STATUS                        txStatus ;

} UART_OBJECT ;

static UART_OBJECT uart2_obj ;

/** UART Driver Queue Length

  @Summary
    Defines the length of the Transmit and Receive Buffers

*/

#define UART2_CONFIG_TX_BYTEQ_LENGTH 32
#define UART2_CONFIG_RX_BYTEQ_LENGTH 32

/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

static uint8_t uart2_txByteQ[UART2_CONFIG_TX_BYTEQ_LENGTH] ;
static uint8_t uart2_rxByteQ[UART2_CONFIG_RX_BYTEQ_LENGTH] ;

/**
  Section: Driver Interface
*/

void UART2_Initialize(void)
{
    // URXEN disabled; RXBIMD RXBKIF flag when Break makes low-to-high transition after being low for at least 23/11 bit periods; UARTEN enabled; MOD Asynchronous 8-bit UART; UTXBRK disabled; BRKOVR TX line driven by shifter; UTXEN disabled; USIDL disabled; WAKE disabled; ABAUD disabled; BRGH enabled; 
    // Data Bits = 8; Parity = None; Stop Bits = 1 Stop bit sent, 1 checked at RX;
    U2MODE = (0x8080 & ~(1<<15));  // disabling UARTEN bit
    // STSEL 1 Stop bit sent, 1 checked at RX; BCLKMOD disabled; SLPEN disabled; FLO Off; BCLKSEL FOSC; C0EN disabled; RUNOVF disabled; UTXINV disabled; URXINV disabled; HALFDPLX disabled; 
    U2MODEH = 0x400;
    // OERIE disabled; RXBKIF disabled; RXBKIE disabled; ABDOVF disabled; OERR disabled; TXCIE disabled; TXCIF disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; CERIF disabled; PERIE disabled; 
    U2STA = 0x00;
    // URXISEL RX_ONE_WORD; UTXBE enabled; UTXISEL TX_BUF_EMPTY; URXBE enabled; STPMD disabled; TXWRE disabled; 
    U2STAH = 0x22;
	// BaudRate = 230400; Frequency = 200000000 Hz; BRG 216; 
    U2BRG = 0xD8;
    // BRG 0; 
    U2BRGH = 0x00;
    // P1 0; 
    U2P1 = 0x00;
    // P2 0; 
    U2P2 = 0x00;
    // P3 0; 
    U2P3 = 0x00;
    // P3H 0; 
    U2P3H = 0x00;
    // TXCHK 0; 
    U2TXCHK = 0x00;
    // RXCHK 0; 
    U2RXCHK = 0x00;
    // T0PD 1 ETU; PTRCL disabled; TXRPT Retransmit the error byte once; CONV Direct logic; 
    U2SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; BTCIE disabled; BTCIF disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    U2SCINT = 0x00;
    // ABDIF disabled; WUIF disabled; ABDIE disabled; 
    U2INT = 0x00;

    IEC1bits.U2RXIE = 1;
    
     //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U2MODEbits.UARTEN = 1;  // enabling UARTEN bit
    U2MODEbits.UTXEN = 1; 
    U2MODEbits.URXEN = 1;  

    uart2_obj.txHead = uart2_txByteQ;
    uart2_obj.txTail = uart2_txByteQ;
    uart2_obj.rxHead = uart2_rxByteQ;
    uart2_obj.rxTail = uart2_rxByteQ;
    uart2_obj.rxStatus.s.empty = true;
    uart2_obj.txStatus.s.empty = true;
    uart2_obj.txStatus.s.full = false;
    uart2_obj.rxStatus.s.full = false;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2TXInterrupt ( void )
{ 
    if(uart2_obj.txStatus.s.empty)
    {
        IEC1bits.U2TXIE = false;
        return;
    }

    IFS1bits.U2TXIF = false;

    while(!(U2STAHbits.UTXBF == 1))
    {

        U2TXREG = *uart2_obj.txHead;

        uart2_obj.txHead++;

        if(uart2_obj.txHead == (uart2_txByteQ + UART2_CONFIG_TX_BYTEQ_LENGTH))
        {
            uart2_obj.txHead = uart2_txByteQ;
        }

        uart2_obj.txStatus.s.full = false;

        if(uart2_obj.txHead == uart2_obj.txTail)
        {
            uart2_obj.txStatus.s.empty = true;
            break;
        }
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2RXInterrupt( void )
{
    while(!(U2STAHbits.URXBE == 1))    //Check for the RX Buffer not empty
    {
        *uart2_obj.rxTail = U2RXREG;

        uart2_obj.rxTail++;

        if(uart2_obj.rxTail == (uart2_rxByteQ + UART2_CONFIG_RX_BYTEQ_LENGTH))
        {
            uart2_obj.rxTail = uart2_rxByteQ;
        }

        uart2_obj.rxStatus.s.empty = false;
        
        if(uart2_obj.rxTail == uart2_obj.rxHead)
        {
            //Sets the flag RX full
            uart2_obj.rxStatus.s.full = true;
            break;
        }   
    }

    IFS1bits.U2RXIF = false;
   
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2EInterrupt( void )
{
    if ((U2STAbits.OERR == 1))
    {
        U2STAbits.OERR = 0;
    }
	
    IFS3bits.U2EIF = false;
}

/* ISR for UART Event Interrupt */
void __attribute__ ( ( interrupt, no_auto_psv ) ) _U2EVTInterrupt ( void )
{
    /* Add handling for UART events here */

    IFS11bits.U2EVTIF = false;
}

/**
  Section: UART Driver Client Routines
*/

uint8_t UART2_Read( void)
{
    uint8_t data = 0;

    data = *uart2_obj.rxHead;

    uart2_obj.rxHead++;

    if (uart2_obj.rxHead == (uart2_rxByteQ + UART2_CONFIG_RX_BYTEQ_LENGTH))
    {
        uart2_obj.rxHead = uart2_rxByteQ;
    }

    if (uart2_obj.rxHead == uart2_obj.rxTail)
    {
        uart2_obj.rxStatus.s.empty = true;
    }

    uart2_obj.rxStatus.s.full = false;

    return data;
}

unsigned int UART2_ReadBuffer( uint8_t *buffer, const unsigned int bufLen)
{
    unsigned int numBytesRead = 0 ;
    while ( numBytesRead < ( bufLen ))
    {
        if( uart2_obj.rxStatus.s.empty)
        {
            break;
        }
        else
        {
            buffer[numBytesRead++] = UART2_Read () ;
        }
    }

    return numBytesRead ;
}

void UART2_Write( const uint8_t byte)
{
    IEC1bits.U2TXIE = false;
    
    *uart2_obj.txTail = byte;

    uart2_obj.txTail++;
    
    if (uart2_obj.txTail == (uart2_txByteQ + UART2_CONFIG_TX_BYTEQ_LENGTH))
    {
        uart2_obj.txTail = uart2_txByteQ;
    }

    uart2_obj.txStatus.s.empty = false;

    if (uart2_obj.txHead == uart2_obj.txTail)
    {
        uart2_obj.txStatus.s.full = true;
    }

    IEC1bits.U2TXIE = true ;
}

unsigned int UART2_WriteBuffer( const uint8_t *buffer , const unsigned int bufLen )
{
    unsigned int numBytesWritten = 0 ;

    while ( numBytesWritten < ( bufLen ))
    {
        if((uart2_obj.txStatus.s.full))
        {
            break;
        }
        else
        {
            UART2_Write (buffer[numBytesWritten++] ) ;
        }
    }

    return numBytesWritten ;
}

UART2_TRANSFER_STATUS UART2_TransferStatusGet (void )
{
    UART2_TRANSFER_STATUS status = 0;

    if(uart2_obj.txStatus.s.full)
    {
        status |= UART2_TRANSFER_STATUS_TX_FULL;
    }

    if(uart2_obj.txStatus.s.empty)
    {
        status |= UART2_TRANSFER_STATUS_TX_EMPTY;
    }

    if(uart2_obj.rxStatus.s.full)
    {
        status |= UART2_TRANSFER_STATUS_RX_FULL;
    }

    if(uart2_obj.rxStatus.s.empty)
    {
        status |= UART2_TRANSFER_STATUS_RX_EMPTY;
    }
    else
    {
        status |= UART2_TRANSFER_STATUS_RX_DATA_PRESENT;
    }
    return status;
}

/*
    Uart Peek function returns the character in the read sequence with
    the provided offset, without extracting it.
*/
uint8_t UART2_Peek(uint16_t offset)
{
    if( (uart2_obj.rxHead + offset) >= (uart2_rxByteQ + UART2_CONFIG_RX_BYTEQ_LENGTH))
    {
      return uart2_rxByteQ[offset - (uart2_rxByteQ + UART2_CONFIG_RX_BYTEQ_LENGTH - uart2_obj.rxHead)];
    }
    else
    {
      return *(uart2_obj.rxHead + offset);
    }
}

/*
    Uart PeekSafe function validates all the possible conditions and get the character  
    in the read sequence with the provided offset, without extracting it.
*/
bool UART2_PeekSafe(uint8_t *dataByte, uint16_t offset)
{
    uint16_t index = 0;
    bool status = true;
    
    if((offset >= UART2_CONFIG_RX_BYTEQ_LENGTH) || (uart2_obj.rxStatus.s.empty)\
            || (!dataByte))
    {
        status = false;
    }
    else
    {
        //Compute the offset buffer overflow range
        index = ((uart2_obj.rxHead - uart2_rxByteQ) + offset)\
                % UART2_CONFIG_RX_BYTEQ_LENGTH;
        
        /**
         * Check for offset input value range is valid or invalid. If the range 
         * is invalid, then status set to false else true.
         */
        if(uart2_obj.rxHead < uart2_obj.rxTail) 
        {
            if((uart2_obj.rxHead + offset) > (uart2_obj.rxTail - 1))
                status = false;
        }
        else if(uart2_obj.rxHead > uart2_obj.rxTail)
        {
            if((uart2_rxByteQ + index) > (uart2_obj.rxTail - 1))
                status = false;
        }

        if(status == true)
        {
            *dataByte = UART2_Peek(index);
        }
    }
    return status;
}

unsigned int UART2_ReceiveBufferSizeGet(void)
{
    if(!uart2_obj.rxStatus.s.full)
    {
        if(uart2_obj.rxHead > uart2_obj.rxTail)
        {
            return(uart2_obj.rxHead - uart2_obj.rxTail);
        }
        else
        {
            return(UART2_CONFIG_RX_BYTEQ_LENGTH - (uart2_obj.rxTail - uart2_obj.rxHead));
        } 
    }
    return 0;
}

unsigned int UART2_TransmitBufferSizeGet(void)
{
    if(!uart2_obj.txStatus.s.full)
    { 
        if(uart2_obj.txHead > uart2_obj.txTail)
        {
            return(uart2_obj.txHead - uart2_obj.txTail);
        }
        else
        {
            return(UART2_CONFIG_TX_BYTEQ_LENGTH - (uart2_obj.txTail - uart2_obj.txHead));
        }
    }
    return 0;
}

bool UART2_ReceiveBufferIsEmpty (void)
{
    return((bool) uart2_obj.rxStatus.s.empty);
}

bool UART2_TransmitBufferIsFull(void)
{
    return((bool) uart2_obj.txStatus.s.full);
}

uint32_t UART2_StatusGet (void)
{
    uint32_t statusReg = U2STAH;
    return ((statusReg << 16 ) | U2STA);
}

