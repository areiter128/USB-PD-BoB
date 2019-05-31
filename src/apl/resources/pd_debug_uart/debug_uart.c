
#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "debug_uart.h"

#define UART_TX_BUFFER_LENGTH 512       // This needs to be a power of 2 to make the
                                        // Mask work correctly
#define UART_BUFFER_MASK      0x01FF    // Mask that is AND-ed with the buffer count
                                        // to provide the wrap-around function
uint16_t tx_buffer_head = 0;
uint16_t tx_buffer_tail = 0;
uint8_t debug_tx_buffer[UART_TX_BUFFER_LENGTH] ;

void DEBUG_init(void)
{
    unsigned int i = 0;
///**    
//     Set the UART1 module to the options selected in the user interface.
//     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
//*/
//    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
//    DEBUG_UART_MODE = (0x8008 & ~(1<<15));  // disabling UARTEN bit
//    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN enabled; ADDEN disabled; 
//    DEBUG_UART_STA = 0x0000;
//    
//    // BaudRate = 115200; Frequency = 1842500 Hz; 
//    DEBUG_UART_BRG = 0x004B; //0x0097;
//    
//    DEBUG_UART_UARTEN = 1;
//    DEBUG_UART_UTXEN = 1;
//
    DEBUG_UART_TRIS = 0;
    
    //Set PPS to put the UART TX pin on the configured pin
    DEBUG_UART_PPS_OUTPUT_REG = DEBUG_UART_PPS_OUTPUT_SELECT;  

#ifdef INCLUDE_DEBUG_UART_RX
    // Set up RX Pin as an input
    TRISCbits.TRISC2 = 1;    
    //Set PPS to put the UART RX pin on the configured pin
    DEBUG_UART_PPS_INPUT_REG = DEBUG_UART_PPS_INPUT_SELECT;
#endif // INCLUDE_DEBUG_UART_RX    

/**    
     Set the UART1 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // URXEN disabled; RXBIMD RXBKIF flag when Break makes low-to-high transition after being low for at least 23/11 bit periods; UARTEN enabled; MOD Asynchronous 8-bit UART; UTXBRK disabled; BRKOVR TX line driven by shifter; UTXEN disabled; USIDL disabled; WAKE disabled; ABAUD disabled; BRGH enabled; 
    // Data Bits = 8; Parity = None; Stop Bits = 1 Stop bit sent, 1 checked at RX;
    U1MODE = (0x8080 & ~(1<<15));  // disabling UARTEN bit
    // STSEL 1 Stop bit sent, 1 checked at RX; BCLKMOD disabled; SLPEN disabled; FLO Off; BCLKSEL FOSC/2; C0EN disabled; RUNOVF disabled; UTXINV disabled; URXINV disabled; HALFDPLX disabled; 
    U1MODEH = 0x00;
    // OERIE disabled; RXBKIF disabled; RXBKIE disabled; ABDOVF disabled; OERR disabled; TXCIE disabled; TXCIF disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; CERIF disabled; PERIE disabled; 
    U1STA = 0x00;
    // URXISEL RX_ONE_WORD; UTXBE enabled; UTXISEL TX_BUF_EMPTY; URXBE enabled; STPMD disabled; TXWRE disabled; 
    U1STAH = 0x22;
    // BaudRate = 230400; Frequency = 100000000 Hz; BRG 108; 
    // U1BRG = 0x6C; // For 200 MIPS clock setting
    U1BRG = 0x61; // For 180 MIPS clock setting
    // BRG 0; 
    U1BRGH = 0x00;
    // P1 0; 
    U1P1 = 0x00;
    // P2 0; 
    U1P2 = 0x00;
    // P3 0; 
    U1P3 = 0x00;
    // P3H 0; 
    U1P3H = 0x00;
    // TXCHK 0; 
    U1TXCHK = 0x00;
    // RXCHK 0; 
    U1RXCHK = 0x00;
    // T0PD 1 ETU; PTRCL disabled; TXRPT Retransmit the error byte once; CONV Direct logic; 
    U1SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; BTCIE disabled; BTCIF disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    U1SCINT = 0x00;
    // ABDIF disabled; WUIF disabled; ABDIE disabled; 
    U1INT = 0x00;
    
    U1MODEbits.UARTEN = 1;  // enabling UARTEN bit
    U1MODEbits.UTXEN = 1;

#ifdef INCLUDE_DEBUG_UART_RX
    U1MODEbits.URXEN = 1; 
#endif // INCLUDE_DEBUG_UART_RX
    
    // Wait before running UART
    for(i=0;i<65535;i++) asm(" nop ");
    
    
}


#ifdef INCLUDE_DEBUG_UART_RX
uint8_t DEBUG_read(void)
{
    if (U1STAHbits.URXBE == 1)
    {
        /* Receive buffer empty...return '0'*/
        return (0);
    }
    else
    {
        return (DEBUG_UART_RXREG);        
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
           (U1STAHbits.UTXBF == 0))
    {
        // We have data to send and the buffer is not full.
        // Load up the FIFO
        DEBUG_UART_TXREG = debug_tx_buffer[tx_buffer_tail];    // Write the data byte to the USART.
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
        while (U1STAHbits.UTXBF == 1)
            ;
        DEBUG_UART_TXREG = debug_tx_buffer[tx_buffer_tail];    // Write the data byte to the USART.
        tx_buffer_tail = (tx_buffer_tail + 1) & UART_BUFFER_MASK;
    }
}

