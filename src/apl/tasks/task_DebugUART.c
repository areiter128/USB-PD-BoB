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
#include "apl/resources//debug_uart/smpsDebugUART_UserCID.h"


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

// ToDo: REMOVE CID0002 TEST FRAME
// ====  ===========
#define  SMPS_DBGUART_CID002        0x0002
#define  SMPS_DBGUART_CID002_DLEN   16U

volatile SMPS_DGBUART_FRAME_t tx_frame_cid002;
volatile uint8_t tx_data_cid002[SMPS_DBGUART_CID002_DLEN] = {
            0x30, 0x3A, 0x20, 0x48, 0x45, 0x4C, 0x4C, 0x4F,
            0x20, 0x4A, 0x41, 0x4D, 0x45, 0x53, 0x0D, 0x0A
        };
volatile uint16_t tx_data_cid002_size = (sizeof(tx_data_cid002)/sizeof(tx_data_cid002[0]));
volatile uint16_t cid002_update_counter = 0;
// ====  ===========


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
        
// ToDo: REMOVE CID0002 TEST FRAME
// ====  ===========
        if(++cid002_update_counter > (DebugUART.send_period+1)) {

            // Pack up frame and put it in Tx queue buffer
            smpsDebugUART_SendFrame(&tx_frame_cid002); // Andy for James (String Test Only)
            // Reset update counter
            cid002_update_counter = 0;
            // Increment test counter
            if (tx_data_cid002[0]++ > 0x38)
                tx_data_cid002[0] = 0x30;
        }
// ====  ===========
        
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
    fres &= smpsPPS_LockIO(); // Carlo it prevent PD stack to work. To be verified
    
    
    // Initialize default data frame for power supply runtime data
	tx_frame_cid0100.tx_tmr.period = (uint16_t)(SMPS_DBGUART_CID0100_PERIOD/TASK_MGR_TIME_STEP);
    fres &= smpsDebugUART_InitializeFrame(
                &tx_frame_cid100, SMPS_DBGUART_CID100, 
                &tx_data_cid100[0], 
                SMPS_DBGUART_CID100_DLEN
        );

    fres &= smpsDebugUART_InitializeFrame(
                &tx_frame_cid002, SMPS_DBGUART_CID002, 
                &tx_data_cid002[0], 
                SMPS_DBGUART_CID002_DLEN
        );

    // Initialize UART interface and DebugUART data objects
    fres &= smpsDebugUART_Initialize();
    
    return(fres);
}}

/*!task_DebugUART_UpdateTimebase
 * ***********************************************************************************************
 * Private function determining the divider of the task tick rate of the operating system
 * to the desired user task execution tick.
 * 
 * Example:
 * The OS is running on a 100 us time base. Every 100 us ONE task of the most recently
 * selected task queue is executed. Thus, the effective call rate for an individual task
 * within a task queue is n x 100 us.
 * 
 * Let's assume this task should be executed every 300 ms. In this case a counter is used counting 
 * the task manager calls determining when this task should be executed to meet the desired period. 
 * The counter maximum therefore is dependent on the OS tick rate and the number of tasks in the
 * recent task queue. 
 *
 * As the OS tick rate is constant, the following function is only called at task initialization 
 * and as soon as a change of task queues has been detected, calculating the required counter
 * maximum.
 * 
 * *********************************************************************************************** */

volatile uint16_t task_DebugUART_UpdateTimebase(void) {
// By counting the function calls, the scheduler time base tick 
// period can be scaled down to individual task execution period

    // Calculate the delay intervals to meet the user-defined timing
    tx_frame_cid0100.tx_tmr.period = (volatile uint16_t)(tx_frame_cid0100.tx_tmr.interval / (task_mgr.task_queue_ubound+1));

    return(1);
}

