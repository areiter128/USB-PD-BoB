/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   task_scheduler.h
 * Author: M91406
 * Comments: This code will be executed as main() program
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ROOT_TASK_SCHEDULER_H
#define	ROOT_TASK_SCHEDULER_H

#include "_root/config/globals.h"   // globals.h also include the 4-layer headers for 
                                    //   - Application Layer (APL)
                                    //   - Hardware Abstraction Layer (HAL)
                                    //   - Microcontroller Abstraction Layer (MCAL)
                                    //   - Special Function Layer (SFL)


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    

/*!run_main_loop
 * ***********************************************************************************************
 * Description:
 * [run_main_loop] is a global flag, which enables a CPU reset from any part of the firmware.
 * This is meant to be used as "main fuse" in case something is badly going out of control 
 * and the CPU has to be restarted in a deterministic way.
 * 
 * When [run_main_loop] is set to zero, the scheduler will complete the execution of the most 
 * recent task end exit the main while() loop, where a CPU_RESET instruction will reset the CPU,
 * effectively causing a system restart.
 * 
 * If an immediate restart is necessary, use the CPU_RESET macro directly.
 * 
 * See also:
 * CPU_RESET
 * ***********************************************************************************************/
extern volatile uint16_t run_scheduler;


/*!CPU_LOAD_DEBUG_BUFFER_LENGTH
 * ***********************************************************************************************
 * Description:
 * CPU load and task execution time monitoring can be enabled internally during debug mode
 * by setting this option =1.
 * 
 * When enabled, two data arrays are used to log most recent CPU meter and task execution time
 * meter results. This function collects data continuously by filling the arrays from index 0
 * to n, rolls over and continues to add data from index 0. A software breakpoint needs to be 
 * placed to stop code execution and inspect the collected data arrays.
 * 
 * CPU_LOAD_DEBUG_BUFFER_LENGTH determines the length of the data arrays.
 * 
 * See also:
 * CPU_LOAD_DEBUG_BUFFER_LENGTH
 * ***********************************************************************************************/

// in debugging mode two generic arrays are available for CPU load and task execution time
// measurements
#if (__DEBUG && (USE_TASK_MANAGER_TIMING_DEBUG_ARRAYS == 1))
#define CPU_LOAD_DEBUG_BUFFER_LENGTH     128
extern volatile uint16_t task_time_buffer[];
extern volatile uint16_t cpu_time_buffer[];
#endif

 /* ***********************************************************************************************
 * PROTOTYPES
 * ***********************************************************************************************/
    
    
extern inline volatile uint16_t exec_scheduler(void);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* APL_TASK_SCHEDULER_H */

