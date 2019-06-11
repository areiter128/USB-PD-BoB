
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "debug_uart.h"

#define UART_TX_BUFFER_LENGTH 1024       // This needs to be a power of 2 to make the
                                        // Mask work correctly
#define UART_BUFFER_MASK      0x03FF    // Mask that is AND-ed with the buffer count
                                        // to provide the wrap-around function
uint16_t tx_buffer_head = 0;
uint16_t tx_buffer_tail = 0;
uint8_t debug_tx_buffer[UART_TX_BUFFER_LENGTH] ;

void DEBUG_init(void)
{
    unsigned int i = 0;

    // Set up the TX pin as an output
    PD_DEBUG_UART_TX_TRIS = 0;
    
    //Set PPS to put the UART TX pin on the configured pin
    PD_DEBUG_UART_PPS_OUTPUT_REG = PD_DEBUG_UART_PPS_OUTPUT_SELECT;  

#ifdef INCLUDE_DEBUG_UART_RX
    // Set up RX Pin as an input
    PD_DEBUG_UART_RX_TRIS = 1;    
    //Set PPS to put the UART RX pin on the configured pin
    PD_DEBUG_UART_PPS_INPUT_REG = PD_DEBUG_UART_PPS_INPUT_SELECT;
#endif // INCLUDE_DEBUG_UART_RX    

/**    
     Set the UART1 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // URXEN disabled; RXBIMD RXBKIF flag when Break makes low-to-high transition after being low for at least 23/11 bit periods; UARTEN enabled; MOD Asynchronous 8-bit UART; UTXBRK disabled; BRKOVR TX line driven by shifter; UTXEN disabled; USIDL disabled; WAKE disabled; ABAUD disabled; BRGH enabled; 
    // Data Bits = 8; Parity = None; Stop Bits = 1 Stop bit sent, 1 checked at RX;
    PD_DEBUG_UART_MODE = (0x8080 & ~(1<<15));  // disabling UARTEN bit
    
    // STSEL 1 Stop bit sent, 1 checked at RX; BCLKMOD disabled; SLPEN disabled; FLO Off; BCLKSEL FOSC/2; C0EN disabled; RUNOVF disabled; UTXINV disabled; URXINV disabled; HALFDPLX disabled; 
    PD_DEBUG_UART_MODEH = 0x00;
    // OERIE disabled; RXBKIF disabled; RXBKIE disabled; ABDOVF disabled; OERR disabled; TXCIE disabled; TXCIF disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; CERIF disabled; PERIE disabled; 
    PD_DEBUG_UART_STA = 0x00;
    // URXISEL RX_ONE_WORD; UTXBE enabled; UTXISEL TX_BUF_EMPTY; URXBE enabled; STPMD disabled; TXWRE disabled; 
    PD_DEBUG_UART_STAH = 0x22;
    // BaudRate = 230400; Frequency = 100000000 Hz; BRG 108; 
    // U1BRG = 0x6C; // For 200 MIPS clock setting
    PD_DEBUG_UART_BRG = 0x61;
    // BRG 0; 
    PD_DEBUG_UART_BRGH = 0x00;
    // P1 0; 
    PD_DEBUG_UART_P1 = 0x00;
    // P2 0; 
    PD_DEBUG_UART_P2 = 0x00;
    // P3 0; 
    PD_DEBUG_UART_P3 = 0x00;
    // P3H 0; 
    PD_DEBUG_UART_P3H = 0x00;
    // TXCHK 0; 
    PD_DEBUG_UART_TXCHK = 0x00;
    // RXCHK 0; 
    PD_DEBUG_UART_RXCHK = 0x00;
    // T0PD 1 ETU; PTRCL disabled; TXRPT Retransmit the error byte once; CONV Direct logic; 
    PD_DEBUG_UART_SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; BTCIE disabled; BTCIF disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    PD_DEBUG_UART_SCINT = 0x00;
    // ABDIF disabled; WUIF disabled; ABDIE disabled; 
    PD_DEBUG_UART_INT = 0x00;
    
    PD_DEBUG_UART_UARTEN_BIT = 1;  // enabling UARTEN bit
    PD_DEBUG_UART_UTXEN_BIT = 1;

#ifdef INCLUDE_DEBUG_UART_RX
    PD_DEBUG_UART_URXEN_BIT = 1; 
#endif // INCLUDE_DEBUG_UART_RX
    
    // Wait before running UART
    for(i=0;i<65535;i++) asm(" nop ");
    
    
}


#ifdef INCLUDE_DEBUG_UART_RX
uint8_t DEBUG_read(void)
{
    if (PD_DEBUG_UART_URXBE_BIT == 1)
    {
        /* Receive buffer empty...return '0'*/
        return (0);
    }
    else
    {
        return (PD_DEBUG_UART_RXREG);        
    }
}
#endif // INCLUDE_DEBUG_UART_RX


uint8_t DEBUG_write(uint8_t txData)
{
    uint8_t return_val = 0;
    tx_buffer_head = (tx_buffer_head + 1) & UART_BUFFER_MASK;
    
    if (tx_buffer_head == tx_buffer_tail)
    {
        // Buffer overflow...overwrite the last character with '*' to indicate this
        // for now
        tx_buffer_head = (tx_buffer_head - 1) & UART_BUFFER_MASK;
        debug_tx_buffer[tx_buffer_head] = '*';
        // Return 1 to indicate error
        return_val = 1;
    }
    else
    {
        debug_tx_buffer[tx_buffer_head] = txData;
    }
    
    return (return_val);
}

void DEBUG_print(char *message)
{
    char *text_p = message;
    uint8_t write_error = 0;
    
    while ((*text_p != '\0') &&
            (write_error == 0))
    {
        write_error = DEBUG_write(*text_p);
        text_p++;
    }
}

/* Function to fill the TX FIFO and then exit to allow other application code
 *  to run while bytes are sending 
 */
void debug_uart_tx(void)
{
    while ((tx_buffer_head != tx_buffer_tail) &&
           (PD_DEBUG_UART_UTXBF == 0))
    {
        // We have data to send and the buffer is not full.
        // Load up the FIFO
        PD_DEBUG_UART_TXREG = debug_tx_buffer[tx_buffer_tail];    // Write the data byte to the USART.
        tx_buffer_tail = (tx_buffer_tail + 1) & UART_BUFFER_MASK;
    }
}

/* Function to send all data queued up in the TX buffer.  This blocks until all data
 * has been send
 */
void debug_uart_tx_flush(void)
{
    while (tx_buffer_head != tx_buffer_tail)
    {
        while (PD_DEBUG_UART_UTXBF == 1)
            ;
        PD_DEBUG_UART_TXREG = debug_tx_buffer[tx_buffer_tail];    // Write the data byte to the USART.
        tx_buffer_tail = (tx_buffer_tail + 1) & UART_BUFFER_MASK;
    }
}

