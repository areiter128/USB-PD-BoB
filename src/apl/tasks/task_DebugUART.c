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
#include "apl/resources/debug_uart/smpsDebugUART_UserCID.h"
#include "apl/tasks/task_PowerControl.h"

volatile uint16_t task_DebugUART_UpdateTimebase(void);

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
    volatile CID0100_TX_t* tx_buf_cid0100;
    
    // Check if task manager call-rate has changed
    if (task_mgr.status.bits.queue_switch)
    { fres &= task_DebugUART_UpdateTimebase(); }
    
    // If UART interface has already been successfully initialized, 
    // Execute DebugUART state machine
    if(DebugUART.status.bits.ready) {
        
        
        if(++tx_frame_cid0100.tx_tmr.counter > (tx_frame_cid0100.tx_tmr.period+1)) 
        {
            // When building a data frame, the order of the data packages is reversed
            // as data longer than 8 bit needs to sorted in the following way:
            // xxx_data[0] = LOW_BYTE, xxx_data[1] = HIGH_BYTE. By using a data structure
            // as value access filter, these values will be revers and thus need to be 
            // swapped before loaded into the data buffer:
            
            tx_buf_cid0100 = (CID0100_TX_t*)(uint8_t*)&tx_data_cid0100[0];

			// Input voltage
			scale_val = (int16_t)(((int32_t)(c4swbb_1.data.v_in - VIN_FB_OFFSET) * VIN_ADC2VAL) >> 15);
            tx_buf_cid0100->vin = SwapWordBytes((uint16_t)scale_val); 
			
			// Output voltage channel #1
			scale_val = (int16_t)(((int32_t)(c4swbb_1.data.v_out - VOUT_FB_OFFSET) * VOUT_ADC2VAL) >> 15);
            tx_buf_cid0100->ch1_vout = SwapWordBytes((uint16_t)scale_val); 
			
			// Output current channel #1
			if(c4swbb_1.data.i_out > c4swbb_1.i_loop.feedback_offset)
                scale_val = (int16_t)(((int32_t)(c4swbb_1.data.i_out - c4swbb_1.i_loop.feedback_offset) * IOUT_ADC2VAL) >> 15);
            else
                scale_val = 0;
            tx_buf_cid0100->ch1_iout = SwapWordBytes((uint16_t)scale_val); 

			// Temperature channel #1 
			scale_val = (int16_t)(((int32_t)(c4swbb_1.data.temp - TEMP_OFFSET_TICKS) * TEMP_ADC2VAL) >> 15);
            tx_buf_cid0100->ch1_temp = SwapWordBytes((uint16_t)scale_val); 
			
            // Converter status #1
            tx_buf_cid0100->ch1_status = (uint16_t)SwapWordBytes((uint16_t)c4swbb_1.status.value);; 
            
            
            // Output voltage channel #2
			scale_val = (int16_t)(((int32_t)(c4swbb_2.data.v_out - VOUT_FB_OFFSET) * VOUT_ADC2VAL) >> 15);
			tx_buf_cid0100->ch2_vout = SwapWordBytes((uint16_t)scale_val); 

			// Output current channel #2
			if(c4swbb_2.data.i_out > c4swbb_2.i_loop.feedback_offset)
                scale_val = (int16_t)(((int32_t)(c4swbb_2.data.i_out - c4swbb_2.i_loop.feedback_offset) * IOUT_ADC2VAL) >> 15);
            else
                scale_val = 0;
            tx_buf_cid0100->ch2_iout = SwapWordBytes((uint16_t)scale_val); 
			
			// Temperature channel #2
			scale_val = (int16_t)(((int32_t)(c4swbb_2.data.temp - TEMP_OFFSET_TICKS) * TEMP_ADC2VAL) >> 15);
            tx_buf_cid0100->ch2_temp = SwapWordBytes((uint16_t)scale_val); 

            // Converter status #2
            tx_buf_cid0100->ch2_status = (uint16_t)SwapWordBytes((uint16_t)c4swbb_2.status.value);; 

            // Dummy data filling up VID and PID place holders
            tx_buf_cid0100->upd1_vid = SwapWordBytes((uint16_t)(task_mgr.op_mode.value & SYSTEM_OPERATION_MODE_MASK)); 
            tx_buf_cid0100->upd1_pid = SwapWordBytes((uint16_t)task_mgr.cpu_load.load); 
            tx_buf_cid0100->upd2_vid = SwapWordBytes((uint16_t)task_mgr.task_time_ctrl.quota); 
            tx_buf_cid0100->upd2_pid = SwapWordBytes((uint16_t)task_mgr.task_time_ctrl.maximum); 

            // Set data length
            tx_frame_cid0100.frame.dlen.value = tx_data_cid0100_size;

            // Pack up frame and put it in Tx queue buffer
            smpsDebugUART_SendFrame(&tx_frame_cid0100); // Andy for James (String Test Only)
            // Reset update counter
            tx_frame_cid0100.tx_tmr.counter = 0;

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
    fres &= smpsPPS_LockIO(); // Carlo it prevent PD stack to work. To be verified
    
    
    // Initialize default data frame for power supply runtime data
	tx_frame_cid0100.tx_tmr.interval = (uint16_t)(SMPS_DBGUART_CID0100_PERIOD/TASK_MGR_TIME_STEP);
    fres &= smpsDebugUART_InitializeFrame(
                &tx_frame_cid0100, SMPS_DBGUART_CID0100, 
                &tx_data_cid0100[0], 
                SMPS_DBGUART_CID0100_TX_DLEN
        );

    // Initialize UART interface and DebugUART data objects
    fres &= smpsDebugUART_Initialize();
    
    return(fres);
}

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

