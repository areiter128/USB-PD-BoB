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
#include <string.h>
#include "apl/resources/fdrv_FunctionPDStack.h"
#include "apl/tasks/task_PDStack.h"
#include "apl/resources/debug_uart/smpsDebugUART.h"

volatile FUNCTION_PD_STACK_CONFIG_t taskPDStack_config;

volatile SMPS_DGBUART_FRAME_t pd_stack_msg_frame;
char pd_debug_string[64];
// Private prototypes


void pd_stack_debug_string(char *output_str)
{
    pd_stack_msg_frame.frame.sof = DBGUART_START_OF_FRAME;
    pd_stack_msg_frame.frame.cid.value = DBGUART_CID_STRING_OUTPUT; // Set standard CID for STRING OUTPUT
    pd_stack_msg_frame.frame.dlen.value = strlen(output_str); // Specify data length (length of byte-array or number of bytes to send)
    pd_stack_msg_frame.frame.data = (uint8_t *)&output_str[0]; // Set data buffer pointer
    pd_stack_msg_frame.frame.crc.value = 0; // Frame will not be CRC checked but CRC needs to be ZERO;
    pd_stack_msg_frame.frame.eof = DBGUART_END_OF_FRAME; // Set default END_OF_FRAME
        
    smpsDebugUART_SendFrame(&pd_stack_msg_frame);
}

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
    
    //debug_uart_tx();
   
    return(taskPDStack_config.status.value);
}

volatile uint16_t init_taskPDStack(void)
{
    uint16_t reg_data_16;
    
    // Set RC2 as output for debugging
    TRISCbits.TRISC2 = 0;
    LATCbits.LATC2 = 0;
    
    // Initialize the PSF stack.
    MchpPSF_Init();
    
    LOG_PRINT("Init TASK PSF Stack initialization done\r\n");

    // Configure UPD350 gpio pins for functions used outside of the stack
    configure_upd350_gpio();

    UPD_RegisterRead(0, 0x0004, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1("VID 1: %04X\r\n", reg_data_16);
    UPD_RegisterRead(0, 0x0006, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1("PID 1: %04X\r\n", reg_data_16);
    UPD_RegisterRead(1, 0x0004, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1("VID 2: %04X\r\n", reg_data_16);
    UPD_RegisterRead(1, 0x0006, (uint8_t *)&reg_data_16, 2);
    LOG_PRINT1("PID 2: %04X\r\n", reg_data_16);
    // Set the flag in the structure to indicate that the stack has been initialized.
    taskPDStack_config.status.flags.enable = PDSTACK_ENABLED;
 
    return(true);
}

