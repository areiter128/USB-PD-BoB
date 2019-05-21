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
 * File:   syscfg_startup.h
 * Author: M91406
 * Comments: Specification of power system startup timing. 
 * Revision history: Initial version
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _HARDWARE_ABSTRACTION_LAYER_SYSTEM_STARTUP_H_
#define	_HARDWARE_ABSTRACTION_LAYER_SYSTEM_STARTUP_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <math.h>
#include "_root/config/task_manager_config.h"
#include "apl/config/tasks.h"

// Soft-Start Timing
#define POWER_ON_DELAY   300.0e-3  // Power On Delay in [sec]
#define RAMP_UP_PERIOD   50.0e-3  // Voltage Ramp-Up Period in [sec]
#define POWER_GOOD_DELAY 100.0e-3  // Power Good Delay in [sec]

//#define POWER_ON_DELAY_TICKS    (uint16_t)(((float)POWER_ON_DELAY / (float)TASK_MGR_TIME_STEP)/ ((float)(task_queue_system_startup_size)))
//#define RAMP_UP_PERIOD_TICKS    (uint16_t)(((float)RAMP_UP_PERIOD / (float)TASK_MGR_TIME_STEP) / ((float)(task_queue_system_startup_size)))
//#define POWER_GOOD_DELAY_TICKS  (uint16_t)(((float)POWER_GOOD_DELAY / (float)TASK_MGR_TIME_STEP) / ((float)(task_queue_system_startup_size)))

#define POWER_ON_DELAY_TICKS    (uint16_t)(((float)POWER_ON_DELAY / (float)TASK_MGR_TIME_STEP)/ ((float)(task_queue_ac_supply_size)))
#define RAMP_UP_PERIOD_TICKS    (uint16_t)(((float)RAMP_UP_PERIOD / (float)TASK_MGR_TIME_STEP) / ((float)(task_queue_ac_supply_size)))
#define POWER_GOOD_DELAY_TICKS  (uint16_t)(((float)POWER_GOOD_DELAY / (float)TASK_MGR_TIME_STEP) / ((float)(task_queue_ac_supply_size)))


#endif	/* _HARDWARE_ABSTRACTION_LAYER_SYSTEM_STARTUP_H_ */

