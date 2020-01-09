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
    volatile int16_t scale_val=0;
    
    // If UART interface has already been successfully initialized, 
    // Execute DebugUART state machine
    if(DebugUART.status.bits.ready) {
        
        if(++cid100_update_counter > DebugUART.send_period) {

            // Input voltage
            scale_val = (int16_t)(((int32_t)(c4swbb_1.data.v_in - VIN_FB_OFFSET) * VIN_ADC2VAL) >> 15);
            tx_data_cid100[CID0100_TX_VIN_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_VIN_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);
            
            // Output voltage channel #1
            scale_val = (int16_t)(((int32_t)(c4swbb_1.data.v_out - VOUT_FB_OFFSET) * VOUT_ADC2VAL) >> 15);
            tx_data_cid100[CID0100_TX_VOUT_CH1_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_VOUT_CH1_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);

            // Output current channel #1
            if(c4swbb_1.data.i_out > c4swbb_1.i_loop.feedback_offset)
                scale_val = (int16_t)(((int32_t)(c4swbb_1.data.i_out - c4swbb_1.i_loop.feedback_offset) * IOUT_ADC2VAL) >> 15);
            else
                scale_val = 0;
            tx_data_cid100[CID0100_TX_IOUT_CH1_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_IOUT_CH1_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);
            
            // Temperature channel #1 (ToDo: second temp sensor not supported by GUI yet. Add when available)
            scale_val = (int16_t)(((int32_t)(c4swbb_1.data.temp - TEMP_OFFSET_TICKS) * TEMP_ADC2VAL) >> 15);
            tx_data_cid100[CID0100_TX_TEMPERATURE_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_TEMPERATURE_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);
            

            // Output voltage channel #2
            scale_val = (int16_t)(((int32_t)(c4swbb_2.data.v_out - VOUT_FB_OFFSET) * VOUT_ADC2VAL) >> 15);
            tx_data_cid100[CID0100_TX_VOUT_CH2_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_VOUT_CH2_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);

            // Output current channel #2
            if(c4swbb_2.data.i_out > c4swbb_2.i_loop.feedback_offset)
                scale_val = (int16_t)(((int32_t)(c4swbb_2.data.i_out - c4swbb_2.i_loop.feedback_offset) * IOUT_ADC2VAL) >> 15);
            else
                scale_val = 0;
            tx_data_cid100[CID0100_TX_IOUT_CH2_INDEX] = (volatile uint8_t)((scale_val & 0xFF00) >> 8);
            tx_data_cid100[CID0100_TX_IOUT_CH2_INDEX+1] = (volatile uint8_t)(scale_val & 0x00FF);

            
            // Set data length
            tx_frame_cid100.frame.dlen.value = 64;

            // Pack up frame and put it in Tx queue buffer
            smpsDebugUART_SendFrame(&tx_frame_cid100); // Carlo
            
            // Reset update counter
            cid100_update_counter = 0;
        }
        
        // Execute Debug UART State Machine
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