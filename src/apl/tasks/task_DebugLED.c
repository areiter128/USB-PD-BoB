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
 * File:   task_DebugLED.h
 * Author: John Haroian - C14029
 * 
 * Summary:
 * Task to blink Master Core Heartbeat LED (DBGLED1)
 * 
 * Description:
 * This source file is used to register a global data structure allowing to edit
 * parameters of the task. It is also used to publish global function calls.
 * 
 * The main task routine is operating the Master Core Heartbeat LED (DGBLED1) 
 * by applying the status setting in the data structure.
 * 
 * History:
 * 02/21/2019	File created
 * 04/17/2019   extended LED operation now reflecting operating modes
 * ***************************************************************************/

#include <xc.h>
#include "apl/tasks/task_DebugLED.h"

#define DEBUG_LED_TICK_RATE_DEFAULT  1000 // default on-time during normal operation
#define DEBUG_LED_TICK_RATE_FAULT    100 // default on-time during critical fault conditions

volatile FUNCTION_LED_CONFIG_t taskDebugLED_config;

// Private prototypes
volatile inline uint16_t task_DebugLED_ForceOn(void);
volatile inline uint16_t task_DebugLED_ForceOff(void);
volatile inline uint16_t task_DebugLED_ForceToggle(void);
volatile inline uint16_t DebugLED_SwitchOpMode(void);


volatile uint16_t task_DebugLED_ForceOn(void)
{
    DEBUG_LED_WR = LED_ON;
    taskDebugLED_config.status.flags.pin_status = DEBUG_LED_RD;     // Reading active pin status
    taskDebugLED_config.status.flags.led_status = DEBUG_LED_RD;     // Reading active pin status
    return(true);
}

volatile uint16_t task_DebugLED_ForceOff(void)
{
    DEBUG_LED_WR = LED_OFF;
    taskDebugLED_config.status.flags.pin_status = DEBUG_LED_RD;     // Reading active pin status
    taskDebugLED_config.status.flags.led_status = DEBUG_LED_RD;     // Reading active pin status
    return(true);
}

volatile uint16_t task_DebugLED_ForceToggle(void)
{
    DEBUG_LED_TOGGLE;
    taskDebugLED_config.status.flags.pin_status = DEBUG_LED_RD;     // Reading active pin status
    taskDebugLED_config.status.flags.led_status = DEBUG_LED_RD;     // Reading active pin status
    return(true);
}

volatile uint16_t DebugLED_SwitchOpMode(void)
{

    // Reset status flags and temporary variables
    taskDebugLED_config.status.value = 0; // Reset DebugLED status
    taskDebugLED_config.counter = 0;     // reset internal counter

    // Set OP-MODE specific settings
    switch (task_mgr.op_mode.mode)
    {
        case OP_MODE_BOOT: // Operation mode during device start-up and peripheral configuration
 
            taskDebugLED_config.on_time = 0;   // set on_time
            taskDebugLED_config.period = 0;   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_ALWAYS_OFF;
            taskDebugLED_config.status.flags.enable = 0;
            break;

        case OP_MODE_DEVICE_STARTUP: // On-chip peripherals start-up period (self-check, soft-start, etc.)

            taskDebugLED_config.on_time = 0;   // set on_time
            taskDebugLED_config.period = 0;   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_ALWAYS_ON;
            taskDebugLED_config.status.flags.enable = 1;
            break;

        case OP_MODE_SYSTEM_STARTUP: // System start-up period (self-check, soft-start, etc.)

            taskDebugLED_config.on_time = 0;   // set on_time
            taskDebugLED_config.period = 0;   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_ALWAYS_ON;
            taskDebugLED_config.status.flags.enable = 1;
            break;

        case OP_MODE_NORMAL:  // In Normal mode on-time reflects the system status
            
            taskDebugLED_config.on_time = 1000;   // set on_time
            taskDebugLED_config.period = 2000;   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_DUTY_RATIO;
            taskDebugLED_config.status.flags.enable = 1;
            break;
            
        case OP_MODE_STANDBY: // Standby operation mode

            taskDebugLED_config.on_time = 50;   // set on_time
            taskDebugLED_config.period = 20000;   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_DUTY_RATIO;
            taskDebugLED_config.status.flags.enable = 1;
            break;

        case OP_MODE_FAULT: // Fault mode will be entered when a critical fault condition has been detected

            taskDebugLED_config.on_time = DEBUG_LED_TICK_RATE_FAULT;   // set on_time
            taskDebugLED_config.period = (taskDebugLED_config.on_time << 1);   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_TOGGLE;
            taskDebugLED_config.status.flags.enable = 1;
            break;

        default:          // Generic OP_MODE_IDLE => "DO NOTHING" fallback task

            taskDebugLED_config.on_time = DEBUG_LED_TICK_RATE_DEFAULT;   // set on_time
            taskDebugLED_config.period = (taskDebugLED_config.on_time << 1);   // set period
            taskDebugLED_config.status.flags.mode = LEDCTRL_MODE_TOGGLE;
            taskDebugLED_config.status.flags.enable = 1;
            break;

    }

    return(1);
}

volatile uint16_t task_DebugLED(void)
{
    
    // if task manager operating mode has changed, read new settings
    if(task_mgr.status.flags.queue_switch)
    { DebugLED_SwitchOpMode(); }
    
    
    switch (taskDebugLED_config.status.flags.mode)
    {
        case LEDCTRL_MODE_TOGGLE: // Operation mode during device start-up and peripheral configuration
 
            if(taskDebugLED_config.counter++ > taskDebugLED_config.on_time)
            {
                task_DebugLED_ForceToggle();
                taskDebugLED_config.counter = 0;
            }
            break;

        case LEDCTRL_MODE_DUTY_RATIO: // On-chip peripherals start-up period (self-check, soft-start, etc.)

            taskDebugLED_config.counter++;
            if ((DEBUG_LED_RD == LED_ON) && (taskDebugLED_config.counter > taskDebugLED_config.on_time))
            { // if the user defined number of ticks has expired, the LED is turned off
                task_DebugLED_ForceOff();
            }
            else if ((DEBUG_LED_RD == LED_OFF) && (taskDebugLED_config.counter > taskDebugLED_config.period))
            { // if the user defined number of ticks has expired, the LED is turned on
                task_DebugLED_ForceOn();
                taskDebugLED_config.counter = 0;
            }
            break;

        case LEDCTRL_MODE_ALWAYS_ON: // Power converter start-up period (self-check, soft-start, etc.)

            task_DebugLED_ForceOn();
            taskDebugLED_config.counter = 0;
            break;

        case LEDCTRL_MODE_ALWAYS_OFF: // Standby operation mode

            task_DebugLED_ForceOff();
            taskDebugLED_config.counter = 0;
            break;

        default:
            task_DebugLED_ForceOn();
            taskDebugLED_config.counter = 0;
            break;
            
    }
    
    
    // Checking pin and LED on/off status and check for errors
    taskDebugLED_config.status.flags.pin_status = DEBUG_LED_RD; // Reading active pin status
    
    if(DEBUG_LED_RD == DEBUG_LED_WR) // the real pin status is compared with the desired status...
    { // if pin status matches, everything is OK
        taskDebugLED_config.status.flags.led_status = taskDebugLED_config.status.flags.pin_status;
    }
    else
    { // if pin status does not match, the fault flag is set
        taskDebugLED_config.status.flags.led_status = LEDCTRL_LED_STATUS_FAILURE;
    }                    
    
    return(taskDebugLED_config.status.value);
}

volatile uint16_t init_taskDebugLED(void)
{
    // Hardware pin initialization should be done in init_gpio.c
    // Alternatively the controlling GPIO can also be set here
    DEBUG_LED_WR = LED_OFF;
    DEBUG_LED_INIT_OUTPUT;
    
    // Initialize status structure
    taskDebugLED_config.status.flags.pin_status = LEDCTRL_PIN_STATUS_HIGH;
    taskDebugLED_config.status.flags.led_status = LEDCTRL_LED_STATUS_OFF;
    taskDebugLED_config.status.flags.enable = 1;
    
    DebugLED_SwitchOpMode();
    
    return(true);
}

