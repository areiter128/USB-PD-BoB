/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
;	Filename:			    debug_uart.h            
;	Date:				    6 July 2017
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef DEBUG_UART_H
#define	DEBUG_UART_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

//#define INCLUDE_DEBUG_UART_RX        
        
/*
 *  DEBUG UART definitions
 */
// Define the name of the PPS output select register for the debug UART
//#define DEBUG_UART_PPS_OUTPUT_REG        RPOR6bits.RP44R
#define DEBUG_UART_PPS_OUTPUT_REG        RPOR8bits.RP49R 
// Define the output selection for the PPS output select register for the 
// debug UART that will be written to the PPS output select reg above
#define DEBUG_UART_PPS_OUTPUT_SELECT    0x01

#ifdef INCLUDE_DEBUG_UART_RX
// Define the name of the PPS input select register for the debug UART
#define DEBUG_UART_PPS_INPUT_REG        RPINR18bits.U1RXR  
// Define the output selection for the PPS output select register for the 
// debug UART that will be written to the PPS output select reg above
#define DEBUG_UART_PPS_INPUT_SELECT    50 //53
#endif // INCLUDE_DEBUG_UART_RX
        
#define DEBUG_UART_TRIS TRISCbits.TRISC1
        
// Define the debug UART registers

#define DEBUG_UART_MODE             U1MODE
#define DEBUG_UART_STA              U1STA
#define DEBUG_UART_BRG              U1BRG
#define DEBUG_UART_UARTEN           U1MODEbits.UARTEN
#define DEBUG_UART_UTXEN            U1STAbits.UTXEN
#define DEBUG_UART_URXDA            U1STAbits.URXDA
#define DEBUG_UART_OERR             U1STAbits.OERR
#define DEBUG_UART_RXREG            U1RXREG
#define DEBUG_UART_UTXBF            U1STAbits.UTXBF
#define DEBUG_UART_TXREG            U1TXREG     
#define DEBUG_UART_RXREG            U1RXREG        
        
        
/**
  Section: Data Types
*/

/** UART1 Driver Hardware Flags

  @Summary
    Specifies the status of the hardware receive or transmit

  @Description
    This type specifies the status of the hardware receive or transmit.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/
typedef enum
{
    /* Indicates that Receive buffer has data, at least one more character can be read */
    UART1_RX_DATA_AVAILABLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,
    
    /* Indicates that Receive buffer has overflowed */
    UART1_RX_OVERRUN_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that Framing error has been detected for the current character */
    UART1_FRAMING_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that Parity error has been detected for the current character */
    UART1_PARITY_ERROR
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that Receiver is Idle */
    UART1_RECEIVER_IDLE
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/,

    /* Indicates that the last transmission has completed */
    UART1_TX_COMPLETE
        /*DOM-IGNORE-BEGIN*/  = (1 << 8) /*DOM-IGNORE-END*/,

    /* Indicates that Transmit buffer is full */
    UART1_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 9) /*DOM-IGNORE-END*/

}UART1_STATUS;



/** UART1 Driver Transfer Flags

  @Summary
    Specifies the status of the receive or transmit

  @Description
    This type specifies the status of the receive or transmit operation.
    More than one of these values may be OR'd together to create a complete
    status value.  To test a value of this type, the bit of interest must be
    AND'ed with value and checked to see if the result is non-zero.
*/

typedef enum
{
    /* Indicates that the core driver buffer is full */
    UART1_TRANSFER_STATUS_RX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 0) /*DOM-IGNORE-END*/,

    /* Indicates that at least one byte of Data has been received */
    UART1_TRANSFER_STATUS_RX_DATA_PRESENT
        /*DOM-IGNORE-BEGIN*/  = (1 << 1) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver receiver buffer is empty */
    UART1_TRANSFER_STATUS_RX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 2) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is full */
    UART1_TRANSFER_STATUS_TX_FULL
        /*DOM-IGNORE-BEGIN*/  = (1 << 3) /*DOM-IGNORE-END*/,

    /* Indicates that the core driver transmitter buffer is empty */
    UART1_TRANSFER_STATUS_TX_EMPTY
        /*DOM-IGNORE-BEGIN*/  = (1 << 4) /*DOM-IGNORE-END*/

} UART1_TRANSFER_STATUS;

uint8_t UART1_Read( void);


/**
  @Summary
    Returns the number of bytes read by the UART1 peripheral

  @Description
    This routine returns the number of bytes read by the Peripheral and fills the
    application read buffer with the read data.

  @Preconditions
    UART1_Initializer function should have been called 
    before calling this function

  @Param
    buffer       - Buffer into which the data read from the UART1

  @Param
    numbytes     - Total number of bytes that need to be read from the UART1
                   (must be equal to or less than the size of the buffer)

  @Returns
    Number of bytes actually copied into the caller's buffer or -1 if there
    is an error.

  @Example
    <code>
    char                     myBuffer[MY_BUFFER_SIZE];
    unsigned int             numBytes;
    UART1_TRANSFER_STATUS status ;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while( numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet ( ) ;
        if (status & UART1_TRANSFER_STATUS_RX_FULL)
        {
            numBytes += UART1_ReadBuffer( myBuffer + numBytes, MY_BUFFER_SIZE - numBytes )  ;
            if(numBytes < readbufferLen)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            continue;
        }

        // Do something else...
    }
    </code>
*/

unsigned int UART1_ReadBuffer( uint8_t *buffer ,  const unsigned int numbytes);


/**
  @Summary
    Writes a byte of data to the UART1

  @Description
    This routine writes a byte of data to the UART1.

  @Preconditions
    UART1_Initializer function should have been called 
    before calling this function. The transfer status should be checked to see if
    transmitter is not full before calling this function.

  @Param
    byte         - Data byte to write to the UART1

  @Returns
    None.

  @Example
    <code>
    char            myBuffer[MY_BUFFER_SIZE];
    unsigned int    numBytes;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while( numBytes < MY_BUFFER_SIZE);
    {
        if( !(UART1_TRANSFER_STATUS_TX_FULL & UART1_TransferStatusGet()) )
        {
            UART1_Write(handle, myBuffer[numBytes++]);
        }

        // Do something else...
    }
    </code>
*/

void UART1_Write( const uint8_t byte);



/**
  @Summary
    Returns the number of bytes written into the internal buffer

  @Description
    This API transfers the data from application buffer to internal buffer and 
    returns the number of bytes added in that queue

  @Preconditions
    UART1_Initializer function should have been called 
    before calling this function

  @Example
    <code>
    char                     myBuffer[MY_BUFFER_SIZE];
    unsigned int             numBytes;
    UART1_TRANSFER_STATUS status ;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while( numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet ( ) ;
        if (status & UART1_TRANSFER_STATUS_TX_EMPTY)
        {
            numBytes += UART1_WriteBuffer ( myBuffer + numBytes, MY_BUFFER_SIZE - numBytes )  ;
            if(numBytes < writebufferLen)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            continue;
        }

        // Do something else...
    }
    </code>
*/

unsigned int UART1_WriteBuffer( const uint8_t *buffer , const unsigned int numbytes );



/**
  @Summary
    Returns the transmitter and receiver transfer status

  @Description
    This returns the transmitter and receiver transfer status.The returned status 
    may contain a value with more than one of the bits
    specified in the UART1_TRANSFER_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART1_Initializer function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART1_TRANSFER_STATUS value describing the current status 
    of the transfer.

  @Example
    Refer to UART1_ReadBuffer and UART1_WriteBuffer for example

*/

UART1_TRANSFER_STATUS UART1_TransferStatusGet (void );




/**
  @Summary
    Returns the character in the read sequence at the offset provided, without
    extracting it

  @Description
    This routine returns the character in the read sequence at the offset provided,
    without extracting it
 
  @Param
    None.
    
  @Example 
    <code>
    const uint8_t readBuffer[5];
    unsigned int data, numBytes = 0;
    unsigned int readbufferLen = sizeof(readBuffer);
    UART1_Initializer();
    
    while(numBytes < readbufferLen)        
    {   
        UART1_TasksReceive ( );
        //Check for data at a particular place in the buffer
        data = UART1_Peek(3);
        if(data == 5)
        {
            //discard all other data if byte that is wanted is received.    
            //continue other operation
            numBytes += UART1_ReadBuffer ( readBuffer + numBytes , readbufferLen ) ;
        }
        else
        {
            break;
        }
    }
    </code>
 
*/
uint8_t UART1_Peek(uint16_t offset);



/**
  @Summary
    Returns the size of the receive buffer

  @Description
    This routine returns the size of the receive buffer.

  @Param
    None.

  @Returns
    Size of receive buffer.
    
  @Example 
    <code>
    const uint8_t readBuffer[5];
    unsigned int size, numBytes = 0;
    unsigned int readbufferLen = sizeof(readBuffer);
    UART1__Initializer();
    
    while(size < readbufferLen)
	{
	    UART1_TasksReceive ( );
	    size = UART1_ReceiveBufferSizeGet();
	}
    numBytes = UART1_ReadBuffer ( readBuffer , readbufferLen ) ;
    </code>
 
*/
unsigned int UART1_ReceiveBufferSizeGet(void);


/**
  @Summary
    Returns the size of the transmit buffer

  @Description
    This routine returns the size of the transmit buffer.

 @Param
    None.
 
 @Returns
    Size of transmit buffer.

 @Example
    Refer to UART1_Initializer(); for example.
*/
unsigned int UART1_TransmitBufferSizeGet(void);



/**
  @Summary
    Returns the status of the receive buffer

  @Description
    This routine returns if the receive buffer is empty or not.

  @Param
    None.
 
  @Returns
    True if the receive buffer is empty
    False if the receive buffer is not empty
    
  @Example
    <code>
    char                     myBuffer[MY_BUFFER_SIZE];
    unsigned int             numBytes;
    UART1_TRANSFER_STATUS status ;

    // Pre-initialize myBuffer with MY_BUFFER_SIZE bytes of valid data.

    numBytes = 0;
    while( numBytes < MY_BUFFER_SIZE);
    {
        status = UART1_TransferStatusGet ( ) ;
        if (!UART1_ReceiveBufferIsEmpty())
        {
            numBytes += UART1_ReadBuffer( myBuffer + numBytes, MY_BUFFER_SIZE - numBytes )  ;
            if(numBytes < readbufferLen)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            continue;
        }

        // Do something else...
    }
    </code>
 
*/
bool UART1_ReceiveBufferIsEmpty (void);



/**
  @Summary
    Returns the status of the transmit buffer

  @Description
    This routine returns if the transmit buffer is full or not.

 @Param
    None.
 
 @Returns
    True if the transmit buffer is full
    False if the transmit buffer is not full

 @Example
    Refer to UART1_Initializer() for example.
 
*/
bool UART1_TransmitBufferIsFull (void);



/**
  @Summary
    Returns the transmitter and receiver status

  @Description
    This returns the transmitter and receiver status. The returned status may 
    contain a value with more than one of the bits
    specified in the UART1_STATUS enumeration set.  
    The caller should perform an "AND" with the bit of interest and verify if the
    result is non-zero (as shown in the example) to verify the desired status
    bit.

  @Preconditions
    UART1_Initializer function should have been called 
    before calling this function

  @Param
    None.

  @Returns
    A UART1_STATUS value describing the current status 
    of the transfer.

  @Example
    <code>
        while(!(UART1_StatusGet & UART1_TX_COMPLETE ))
        {
           // Wait for the tranmission to complete
        }
    </code>
*/

UART1_STATUS UART1_StatusGet (void );

    
void DEBUG_init(void);
uint8_t DEBUG_read(void);
uint8_t DEBUG_write(uint8_t txData);
void DEBUG_print(char *message);

void debug_uart_tx(void);
void debug_uart_tx_flush(void);

extern char debug_string[];

#endif // DEBUG_UART_H