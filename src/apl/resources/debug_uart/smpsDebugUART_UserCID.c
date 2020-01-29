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


/*!Proprietary Message Frame Declarations
 * ************************************************************************************************
 * Summary:
 * Declarations of custom data objects and data arrays
 *
 * Description:
 * The following section is used to declare data objects of application specific, 
 * proprietary message frames. The declarations which need to be placed in 
 * smpsDebugUART_UserCID.c are as follows:
 * 
 *     - Transmit message frame data object of type SMPS_DBGUART_FRAME_t:
 * 
 *          Suggested standard naming convention: tx_frame_cidXXX where XXX = [CID_NUMBER]
 *          Example: Messages of type CID = 0x0035 are named tx_frame_cid0035
 * 
 *     - Transmit message byte-array data object of type uint8_t[]:
 * 
 *          Suggested standard naming convention: tx_data_cidXXX where XXX = [CID_NUMBER]
 *          Example: Data arrays of messages of type CID = 0x0035 are named tx_data_cid0035
 * 
 *     - Transmit message byte-array data length variable of type uint16_t (pre-initialized)
 *          Suggested standard naming convention: tx_data_cidXXX_size where XXX = [CID_NUMBER]
 *          Example: Data arrays of messages of type CID = 0x0035 are named tx_data_cid0035_size
 *       
 *          It is recommended to initialize this variable dynamically at compile time by using 
 *          the unary operator sizeof().
 * 
 * Example:
 * In this example a message frame of CID type 0x0035 with a data length of 16 bytes is added to 
 * the project. The byte-array data object may or may not be initialized but its length needs
 * to be defined.
 * The required declarations would be:
 * 
 * volatile SMPS_DGBUART_FRAME_t tx_frame_cid0035; // declare frame object
 * volatile uint8_t tx_data_cid0035[SMPS_DBGUART_CID0022_DLEN] = {
 *          'M', 'Y', ' ', 'M', 'E', 'S', 'S', 'A',
 *          'G', 'E', ' ', 'F', 'R', 'A', 'M', 'E'
 *      };
 * volatile uint16_t tx_data_cid0035_size = (sizeof(tx_data_cid0035)/sizeof(tx_data_cid0035[0]));
 * volatile uint16_t cid0035_update_counter = 0;
 *
 * 
 * Please Note:
 * This is only the basic definition of fundamental data objects. The detailed declaration of 
 * the data structure of contents and CID number is placed in the smpsDebugUART_UserCID.h header 
 * file.
 * ************************************************************************************************/

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ASCALAB GUI INTERFACE PROTOCOL
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Transmit data frame
volatile SMPS_DGBUART_FRAME_t tx_frame_cid0100;
volatile uint8_t tx_data_cid0100[SMPS_DBGUART_CID0100_TX_DLEN] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
volatile uint16_t tx_data_cid0100_size = (sizeof(tx_data_cid0100)/sizeof(tx_data_cid0100[0]));

// Receive data frame
volatile uint8_t rx_data_cid0100[SMPS_DBGUART_CID0100_RX_DLEN];
volatile uint16_t rx_data_cid0100_size = (sizeof(rx_data_cid0100)/sizeof(rx_data_cid0100[0]));

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
    volatile CID0100_RX_t* rx_cid0100;

    /*!Processing Proprietary Protocol Command IDs
     * *********************************************************************
     * The following commands are hardware and/or application specific
     * and not covered by the default protocol. Users have to write their
     * own code decoding and responding the given message frame.
     * ********************************************************************/    
    switch (msg_frame->frame.cid.value) {

        case SMPS_DBGUART_CID0100:
            // Carlo Add code to mange buffer from GUI here
            
//            config=(uint16_t)msg_frame->frame.data[CID0100_RX_CONFIG_BITS_INDEX+1]+(((uint16_t)msg_frame->frame.data[CID0100_RX_CONFIG_BITS_INDEX])<<8);
//            temperature_simulation=((uint16_t)msg_frame->frame.data[CID0100_RX_TEMPERATURE_INDEX+1]+(((uint16_t)msg_frame->frame.data[CID0100_RX_TEMPERATURE_INDEX])<<8))/10; // GUI send T*10
//            
//            
//            if((config&CID0100_RX_PWM_FREQ_JITTERING)!=0)
//            {
//                c4swbb_1.pwm_dist.status.bits.ssm_enable=1;
//                c4swbb_2.pwm_dist.status.bits.ssm_enable=1;
//            }
//            else
//            {
//                c4swbb_1.pwm_dist.status.bits.ssm_enable=0;
//                c4swbb_2.pwm_dist.status.bits.ssm_enable=0;
//            }    
            
            // Map frame data structure onto data buffer
            rx_cid0100 = (CID0100_RX_t*)msg_frame->frame.data;
            
            // flip bytes as they have been received in reversed order
            SwapWordBytes(rx_cid0100->config_bits.value);
            
            if (rx_cid0100->config_bits.bits.ch1_pwr_enable) {
                // Do whatever may be required
            }

            if (rx_cid0100->config_bits.bits.ch1_usb_enable) {
                // Do whatever may be required
            }

            if (rx_cid0100->config_bits.bits.ch2_pwr_enable) {
                // Do whatever may be required
            }
            
            if (rx_cid0100->config_bits.bits.ch2_usb_enable) {
                // Do whatever may be required
            }

            if (rx_cid0100->config_bits.bits.pwm_dithering) {
                // Do whatever may be required
            }
            
            if (rx_cid0100->config_bits.bits.temp_override) {
                // Do whatever may be required
            }
            
            c4swbb_1.data.i_ref = SwapWordBytes(rx_cid0100->ref_ch1_iout);
            c4swbb_1.data.v_ref = SwapWordBytes(rx_cid0100->ref_ch1_vout);
            c4swbb_1.data.temp  = SwapWordBytes(rx_cid0100->ref_temp);
            c4swbb_2.data.i_ref = SwapWordBytes(rx_cid0100->ref_ch2_iout);
            c4swbb_2.data.v_ref = SwapWordBytes(rx_cid0100->ref_ch2_vout);
            
            break;
            
            
        default:
            fres = 0; // CID is not supported => return 'failure'
            break;
    }
    
    
    // Reset frame object and RX FIFO data buffer pointer
    msg_frame->status.value = FDEC_STAT_SOF_SYNC;
    
    return(fres);

}

