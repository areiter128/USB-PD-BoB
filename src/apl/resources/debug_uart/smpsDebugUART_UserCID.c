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

#include "apl/resources/debug_uart/smpsDebugUART.h"
#include "apl/resources/debug_uart/smpsDebugUART_UserCID.h"


/*!smpsDebugUART_ProcessUserCID
 * ************************************************************************************************
 * Summary:
 * Processes received messages
 *
 * Parameters:
 * (none)
 * 
 * Returns:
 *  uint16_t: 0=failure, 1=success, 3=unsupported/proprietary CID
 *
 * Description:
 * 
 * ************************************************************************************************/

volatile uint16_t smpsDebugUART_ProcessUserCID(volatile SMPS_DGBUART_FRAME_t* msg_frame) {

    // Function return value
    volatile uint16_t fres=1;

    /*!Processing Proprietary Protocol Command IDs
     * *********************************************************************
     * The following commands are hardware and/or application specific
     * and not covered by the default protocol. Users have to write their
     * own code decoding and responding the given message frame.
     * ********************************************************************/    
    switch (msg_frame->frame.cid.value) {

        case DBGUART_CID_DSMPS_GUI:
            // Carlo Add code to mange buffer from GUI here
            
            Nop();
            Nop();
            Nop();
            Nop();
            
            break;
            
            
        default:
            fres = 0; // CID is not supported => return 'failure'
            break;
    }
    
    
    // Reset frame object and RX FIFO data buffer pointer
    msg_frame->status.value = FDEC_STAT_SOF_SYNC;
    
    return(fres);

}

