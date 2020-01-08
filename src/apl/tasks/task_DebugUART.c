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
#define  SMPS_DBGUART_CID100_DLEN   32U

volatile SMPS_DGBUART_FRAME_t tx_frame_cid100;
volatile uint8_t tx_data_cid100[SMPS_DBGUART_CID100_DLEN] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
volatile uint16_t tx_data_cid100_size = (sizeof(tx_data_cid100)/sizeof(tx_data_cid100[0]));

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

//    fres &= smpsDebugUART_BuildFrame(
//                    &tx_frame_cid100, SMPS_DBGUART_CID100, 
//                    &tx_data_cid100[0], 
//                    SMPS_DBGUART_CID100_DLEN
//            );

    fres &= smpsDebugUART_Initialize();
    
    return(fres);
}