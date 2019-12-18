/*LICENSE ********************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
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
 * ***************************************************************************/
/*!task_DebugLED.c
 * ***************************************************************************
 * File:   task_PDStack.c
 * Author: James Schaffer - C41076  
 * 
 * Summary:
 * PSF USB PD Stack Task
 * 
 * Description:
 * 
 * This file contains functions that implement the task that initializes
 * and runs the PSF USB PD Stack.
 * 
 * History:
 * 05/23/2019	File created
 * 12/16/2019   Changed from the Zeus stack to the PSF Stack
 * ***************************************************************************/

#include <xc.h>
#include <stdio.h>
#include "apl/resources/fdrv_FunctionPDStack.h"
#include "apl/tasks/task_PDStack.h"
#include "debug_uart.h"

volatile FUNCTION_PD_STACK_CONFIG_t taskPDStack_config;

// Private prototypes


volatile uint16_t task_PDStack(void)
{
    uint8_t index;
    
    if (taskPDStack_config.status.flags.enable)
    {
        // Handle Interrupts from the ports
        for(index = 0; index < CONFIG_PD_PORT_COUNT; index++)
        {
            if (upd_irq_asserted(index))
            {
                // Port[index] has asserted an interrupt.  Handle it.
                UPDIntr_AlertHandler (index);
            }
        }
        
        // Call the main PD Stack state machine
        MchpPSF_RUN();
    }
    
    debug_uart_tx();
   
    return(taskPDStack_config.status.value);
}

volatile uint16_t init_taskPDStack(void)
{
    uint16_t reg_data_16;
    
    // Set up the secondary UART for use by the PD stack
    DEBUG_init();
    
    // Set RC2 as output for debugging
    TRISCbits.TRISC2 = 0;
    LATCbits.LATC2 = 0;
    
    // Initialize the PSF stack.
    MchpPSF_Init();
    
    LOG_PRINT(LOG_INFO, "Init TASK PSF Stack initialization done\r\n");

    // Configure UPD350 gpio pins for functions used outside of the stack
    configure_upd350_gpio();
    
    UPD_RegisterRead(0, 0x0004, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1(LOG_DEBUG, "VID 1: %04X\r\n", reg_data_16);
    UPD_RegisterRead(0, 0x0006, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1(LOG_DEBUG, "PID 1: %04X\r\n", reg_data_16);
    UPD_RegisterRead(1, 0x0004, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1(LOG_DEBUG, "VID 2: %04X\r\n", reg_data_16);
    UPD_RegisterRead(1, 0x0006, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1(LOG_DEBUG, "PID 2: %04X\r\n", reg_data_16);
    
    // Set the flag in the structure to indicate that the stack has been initialized.
    taskPDStack_config.status.flags.enable = PDSTACK_ENABLED;
    
    debug_uart_tx_flush();
    
    return(true);
}

