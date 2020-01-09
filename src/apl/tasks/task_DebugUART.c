/*
 * File:   smpsDebugUART_User.c
 * Author: M91406
 *
 * Created on December 11, 2019, 9:42 AM
 */


#include <xc.h> // include processor files - each processor file is guarded.  
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "apl/tasks/task_DebugUART.h"
#include "apl/resources/debug_uart/smpsDebugUART.h"


#define  SMPS_DBGUART_CID100        0x0100
#define  SMPS_DBGUART_CID100_DLEN   64U

volatile SMPS_DGBUART_FRAME_t tx_frame_cid100;
volatile uint8_t tx_data_cid100[SMPS_DBGUART_CID100_DLEN] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
volatile uint16_t tx_data_cid100_size = (sizeof(tx_data_cid100)/sizeof(tx_data_cid100[0]));
volatile uint16_t cid100_update_counter = 0;

/*!task_DebugUART_Execute
 * ************************************************************************************************
 * Summary:
 * Processes received messages
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

volatile uint16_t task_DebugUART_Execute(void) {

    volatile uint16_t fres=1;

    // If UART interface has already been successfully initialized, 
    // Execute DebugUART state machine
    if(DebugUART.status.bits.ready) {
        
        if(++cid100_update_counter > DebugUART.send_period) {

            tx_data_cid100[0] = (volatile uint8_t)((c4swbb_1.data.v_in & 0xFF00) >> 8);
            tx_data_cid100[1] = (volatile uint8_t)(c4swbb_1.data.v_in & 0x00FF);
            tx_data_cid100[2] = (volatile uint8_t)((c4swbb_1.data.v_out & 0xFF00) >> 8);
            tx_data_cid100[3] = (volatile uint8_t)(c4swbb_1.data.v_out & 0x00FF);
            
            tx_data_cid100[4] = (volatile uint8_t)((c4swbb_1.data.i_out & 0xFF00) >> 8);
            tx_data_cid100[5] = (volatile uint8_t)(c4swbb_1.data.i_out & 0x00FF);
            
            tx_data_cid100[10] = (volatile uint8_t)((c4swbb_2.data.v_out & 0xFF00) >> 8);
            tx_data_cid100[11] = (volatile uint8_t)(c4swbb_2.data.v_out & 0x00FF);
            tx_data_cid100[12] = (volatile uint8_t)((c4swbb_2.data.i_out & 0xFF00) >> 8);
            tx_data_cid100[13] = (volatile uint8_t)(c4swbb_2.data.i_out & 0x00FF);
            tx_frame_cid100.frame.dlen.value = 64;

            smpsDebugUART_SendFrame(&tx_frame_cid100); // Carlo
            
            cid100_update_counter = 0;
        }
        
        fres = smpsDebugUART_Execute();
    }
    // If UART initialization has not been performed yet, 
    // do so now.
    else {

        fres = smpsDebugUART_Initialize();
    }

    
    return(fres);

}

volatile uint16_t task_DebugUART_Initialize(void) {
    
    volatile uint16_t fres=1;
    
    //return(0); // Carlo

    // Initialize DebugUART Rx/Tx device pins to communicate via UART adapter
    HUB_PRTPWR1_INIT_OUTPUT; // Tx Channel
    HUB_PRTPWR2_INIT_INPUT;  // Rx Channel
    
    fres &= smpsPPS_UnlockIO();
    #if (UART_INSTANCE == 1)
    smpsPPS_RemapInput(HUB_PRTPWR2_RP, PPSIN_U1RX);
    smpsPPS_RemapOutput(HUB_PRTPWR1_RP, PPSOUT_U1TX);
    #elif (UART_INSTANCE == 2)
    fres &= smpsPPS_RemapInput(HUB_PRTPWR2_RP, PPSIN_U2RX);
    fres &= smpsPPS_RemapOutput(HUB_PRTPWR1_RP, PPSOUT_U2TX);
    #elif (UART_INSTANCE == 3)
    smpsPPS_RemapInput(HUB_PRTPWR2_RP, PPSIN_U3RX);
    smpsPPS_RemapOutput(HUB_PRTPWR1_RP, PPSOUT_U3TX);
    #endif
    //fres &= smpsPPS_LockIO(); // Carlo it prevent PD stack to work. To be verified
    
    
    // Initialize default data frame for power supply runtime data
    fres &= smpsDebugUART_InitializeFrame(
                &tx_frame_cid100, SMPS_DBGUART_CID100, 
                &tx_data_cid100[0], 
                SMPS_DBGUART_CID100_DLEN
        );

    // Initialize UART interface and DebugUART data objects
    fres &= smpsDebugUART_Initialize();
    
    return(fres);
}