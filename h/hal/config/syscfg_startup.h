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

/*!Startup Behavior
 * *************************************************************************************************
 * Summary:
 * Global defines for soft-start specific parameters
 * 
 * Description:
 * This section is used to define power supply startup timing setting. The soft-start sequence 
 * is part of the power controller. It allows to program specific timings for Power On Delay,
 * Ramp Period and Power Good Delay. After the startup has passed these three timing periods,
 * the power supply is ending up in "normal" operation, continuously regulating the output until 
 * a fault is detected or the operating state is changed for any other reason.
 * 
 * Pre-compiler macros are used to translate physical values into binary (integer) numbers to 
 * be written to SFRs and variables.
 * 
 * *************************************************************************************************/

#define C4SWBB_POWER_ON_DELAY    100e-3      // power on delay in [sec]
#define C4SWBB_RAMP_PERIOD       50e-3       // ramp period in [sec]
#define C4SWBB_POWER_GOOD_DELAY  100e-3      // power good in [sec]

#define C4SWBB_VMC              0           // Flag for voltage mode control
#define C4SWBB_ACMC             1           // Flag for average current mode control
#define C4SWBB_CONTROL_MODE     C4SWBB_ACMC // Active control mode selection

#define C4SWBB_PODLY     (uint16_t)((C4SWBB_POWER_ON_DELAY / TASK_MGR_PERIOD)-1.0)
#define C4SWBB_RPER      (uint16_t)((C4SWBB_RAMP_PERIOD / TASK_MGR_PERIOD)-1.0)
#define C4SWBB_PGDLY     (uint16_t)((C4SWBB_POWER_GOOD_DELAY / TASK_MGR_PERIOD)-1.0)
#define C4SWBB_VREF_STEP (uint16_t)((C4SWBB_VOUT_REF / (C4SWBB_RPER + 1.0)))
#define C4SWBB_IREF_STEP (uint16_t)((C4SWBB_VOUT_REF / (C4SWBB_RPER + 1.0)))


#endif	/* _HARDWARE_ABSTRACTION_LAYER_SYSTEM_STARTUP_H_ */

