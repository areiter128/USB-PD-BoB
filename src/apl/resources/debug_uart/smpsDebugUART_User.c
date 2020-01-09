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


/*!smpsDebugUART_ExecuteCID
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

volatile uint16_t smpsDebugUART_ProcessCID(volatile SMPS_DGBUART_FRAME_t* msg_frame) {

    // Function return value
    volatile uint16_t fres=1;

    // Frame-Validation variables
    volatile uint16_t crc=0;
    
    // Command execution buffer variables
    volatile uint16_t val_buf=0;
    volatile uint16_t* addr_ptr;
    
    // Run Cyclic Redundancy Check if ID and data contents are valid
    // for all IDs greater than 0x000F. CIDs from 0 to 15 (0x0000-0x000F)
    // are used to bypass CRC calculation
    if (msg_frame->frame.cid.value > 0x000F) {
    
        // Run Cyclic Redundancy Check 
        crc = smpsCRC_GetStandard_Data8CRC16((uint8_t*)msg_frame, 0, (msg_frame->frame.dlen.value + DBGUART_FRAME_HEAD_LEN));
    
        // if there is a CRC mismatch, stop and exit here
        if (crc == msg_frame->frame.crc.value) {
            msg_frame->status.value = FDEC_STAT_SOF_SYNC; // Reset frame object and RX FIFO data buffer pointer
            return(0);  // Exit and return FALSE
        }
    }

    // Select CID response action
    switch (msg_frame->frame.cid.value) {

        /*!DBGUART_CID_READ_FROM_ADDR
         * *********************************************************************
         * Returns the value [VALUE] found at address [ADDR]. 
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The value is returned by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = VALUE high byte
         *   - DATA[3] = VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_READ_FROM_ADDR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[2] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[0] of frame
            msg_frame->frame.data[3] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[1] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_WRITE_TO_ADDR
         * *********************************************************************
         * Writes a new value [VALUE] to address [ADDR]. 
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The value is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = VALUE high byte
         *   - DATA[3] = VALUE low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_WRITE_TO_ADDR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read new value to be written to memory address
            val_buf = msg_frame->frame.data[2]; // Load value high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load value low-byte

            // Write value to memory address
            *addr_ptr = (volatile uint16_t)val_buf;

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_OR_BIT_MASK
         * *********************************************************************
         * OR's a bit mask [BITMSK] with a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to this memory 
         * address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit mask is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = BITMSK high byte
         *   - DATA[3] = BITMSK low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_OR_BIT_MASK:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read bit mask from message frame
            val_buf = msg_frame->frame.data[2]; // Load bit mask high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load bit mask low-byte

            // Write [value | bit mask] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr | (volatile uint16_t)val_buf);

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_AND_BIT_MASK
         * *********************************************************************
         * AND's a bit mask [BITMSK] with a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to this memory 
         * address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit mask is given by data bytes DATA[2] and DATA[3] where
         *   - DATA[2] = BITMSK high byte
         *   - DATA[3] = BITMSK low byte
         * 
         * The value is written to the given address, read back and returned
         * to the sender for verification, where
         *   - DATA[4] = RETURN_VALUE high byte
         *   - DATA[5] = RETURN_VALUE low byte
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_AND_BIT_MASK:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

             // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf;

            // Read bit mask from message frame
            val_buf = msg_frame->frame.data[2]; // Load bit mask high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[3]; // Load bit mask low-byte

            // Write [value & bit mask] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr & (volatile uint16_t)val_buf);

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[4] = ((*addr_ptr & 0xFF00) >> 8); // Load value high byte in DATA[2] of frame
            msg_frame->frame.data[5] = (*addr_ptr & 0x00FF); // Load value low byte in DATA[3] of frame

            msg_frame->frame.dlen.value = 6; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_GET
         * *********************************************************************
         * Gets a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and returns its value to sender
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is extracted from the value found at the given address
         *  and returned to the sender, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_GET:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_SET
         * *********************************************************************
         * Sets a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to the given
         * memory address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is set within the value found at the given address. The
         * value is read back, the bit is extracted and returned to the sender 
         * for verification, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_SET:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Write [value | bit] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr | (0x0001 << msg_frame->frame.data[2]));

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!DBGUART_CID_BIT_CLEAR
         * *********************************************************************
         * Clears a bit [BIT] within a 16-bit wide value [VALUE] at memory 
         * address [ADDR] and writes the result as new value to the given
         * memory address.
         * The address is given by data bytes DATA[0] and DATA[1] where 
         *   - DATA[0] = ADDR high byte
         *   - DATA[1] = ADDR low byte
         * 
         * The bit position is given by data byte DATA[2] ranging from 0 to 15
         * where 0 = LSB and 15 = MSB
         * 
         * The bit is cleared within the value found at the given address. The
         * value is read back, the bit is extracted and returned to the sender 
         * for verification, where
         *   - DATA[3] = RETURN_VALUE (0=cleared, 1=set)
         * 
         * PLEASE NOTE:
         * This message needs to be acknowledged by setting bit #0 of CID high
         * byte = 1
         * ********************************************************************/
        case DBGUART_CID_BIT_CLEAR:

            // Read memory address
            val_buf = msg_frame->frame.data[0]; // Load address high-byte
            val_buf <<= 8;
            val_buf |= msg_frame->frame.data[1]; // Load address low-byte

            // Convert to pointer
            addr_ptr = (volatile uint16_t*)val_buf; 

            // Write [value | bit] to memory address
            *addr_ptr = (volatile uint16_t)(*addr_ptr & (~(0x0001 << msg_frame->frame.data[2])));

            // Build response
            msg_frame->frame.cid.value |= DBGUART_CID_ACKNOWLEDGEMENT;   // ID acknowledge
            msg_frame->frame.data[3] = (uint16_t)(bool)(*addr_ptr & (0x0001 << msg_frame->frame.data[2])); // Load value high byte in DATA[2] of frame

            msg_frame->frame.dlen.value = 4; // Set data length

            // Send response
            fres = smpsDebugUART_SendFrame (msg_frame); // Built frame and put it in transmission queue

            break;

        /*!Proprietary Protocol Commands
         * *********************************************************************
         * The following commands are hardware and/or application specific
         * and not covered by standard definitions.
         * ********************************************************************/    

            
            
        default:
            break;
    }
    
    
    // Reset frame object and RX FIFO data buffer pointer
    msg_frame->status.value = FDEC_STAT_SOF_SYNC;
    
    return(fres);

}
