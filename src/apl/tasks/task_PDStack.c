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
 * Zeus USB PD Stack Task
 * 
 * Description:
 * 
 * This file contains functions that implement the task that initializes
 * and runs the Zeus USB PD Stack.
 * 
 * History:
 * 05/23/2019	File created
 * ***************************************************************************/

#include <xc.h>
#include <stdio.h>
#include "apl/resources/fdrv_FunctionPDStack.h"
#include "apl/tasks/task_PDStack.h"

volatile FUNCTION_PD_STACK_CONFIG_t taskPDStack_config;

/*===== DEMO_BOARD_TEST =====*/
#define LOG_PRINT(x,y) // define away LOG_PRINTs for now
/*===== DEMO_BOARD_TEST =====*/
// Private prototypes


volatile uint16_t task_PDStack(void)
{
    uint8_t index;
    static uint16_t test_counter = 0;
    static uint8_t upd_led_toggle = 0;
    
    if (test_counter++ > 1000)
    {
        test_counter = 0;
        // Blink LEDS on UPD350s at the telemetry transmit interval
        if (upd_led_toggle++ & 0x01)
        {
            UPD_GPIOSetClearOutput(0, UPD_PIO9, UPD_GPIO_SET);
            UPD_GPIOSetClearOutput(1, UPD_PIO9, UPD_GPIO_SET);
        }
        else
        {
            UPD_GPIOSetClearOutput(0, UPD_PIO9, UPD_GPIO_CLEAR);
            UPD_GPIOSetClearOutput(1, UPD_PIO9, UPD_GPIO_CLEAR);
        }

    }
    
    
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
        PD_Run();
    }
    
   
    return(taskPDStack_config.status.value);
}

volatile uint16_t init_taskPDStack(void)
{
    uint16_t reg_data_16;
    char debug_string[20];
    
    
    
    PD_Init();
    LOG_PRINT(LOG_INFO, "Init TASK PD Stack done\r\n");

    // Configure UPD350 gpio pins for functions used outside of the stack
    configure_upd350_gpio();
    
    UPD_RegisterRead(0, 0x0004, (uint8_t *)&reg_data_16, 2);
    sprintf(debug_string, "VID 1: %04X\r\n", reg_data_16);
    LOG_PRINT(LOG_DEBUG, debug_string);
    UPD_RegisterRead(0, 0x0006, (uint8_t *)&reg_data_16, 2);
    sprintf(debug_string, "PID 1: %04X\r\n", reg_data_16);
    LOG_PRINT(LOG_DEBUG, debug_string);

    UPD_RegisterRead(1, 0x0004, (uint8_t *)&reg_data_16, 2);
    sprintf(debug_string, "VID 2: %04X\r\n", reg_data_16);
    LOG_PRINT(LOG_DEBUG, debug_string);
    UPD_RegisterRead(1, 0x0006, (uint8_t *)&reg_data_16, 2);
    sprintf(debug_string, "PID 2: %04X\r\n", reg_data_16);
    LOG_PRINT(LOG_DEBUG, debug_string);
    
    // Set the flag in the structure to indicate that the stack has been initialized.
    taskPDStack_config.status.flags.enable = PDSTACK_ENABLED;
    
    return(true);
}

