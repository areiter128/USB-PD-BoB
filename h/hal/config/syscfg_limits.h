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
 * **************************************************************************************
 * File:   system_scaling.h
 * Author: M91406
 * Comments: 
 * Revision history: 
 * 07/29/2016   initial release
 * **************************************************************************************/

#ifndef __SYSTEM_DESIGN_LIMITS_H__
#define	__SYSTEM_DESIGN_LIMITS_H__

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <dsp.h>
#include <math.h>

#include "syscfg_scaling.h"

// Converter input and output voltage and current levels

#define AUX_POWER_GOOD_TIMEOUT  0x2800  // at startup in UserStartupCode.c ExecuteUserStartupCode() software is polling for the 
                                        // LDO POWER GOOD output pin indicating full auxiliary power is available. This timeout
                                        // counter value is preventing that this polling loop will stall the firmware in case
                                        // AUX_POWER_GOOD is not set for some reason...

#define VIN_MINIMUM             9.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VIN_MINIMUM_HYST        0.500        // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)

#define VIN_NOMINAL             13.800       // Nominal input voltage in [V]

#define VIN_MAXIMUM             18.000      // input voltage maximum (Under-Voltage-Lockout-Level)
#define VIN_MAXIMUM_HYST        0.500       // input voltage maximum (Under-Voltage-Lockout Hysteresis Level)

#define VOUT_MINIMUM            4.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VOUT_MINIMUM_HYST       0.500       // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)

#define VOUT_NOMINAL            5.000       // Nominal input voltage in [V]

#define VOUT_MAXIMUM            22.000      // output voltage maximum (Under-Voltage-Lockout-Level)
#define VOUT_MAXIMUM_HYST       0.500       // output voltage maximum (Under-Voltage-Lockout Hysteresis Level)

#define IOUT_MAXIMUM            3.500       // absolute maximum average output current during normal operation
    
#define IOUT_4SWBB_TRIP_CONV1   1.100       // [A] Upper boost switch threshold for output current - PWM1&PWM2 Buck-Boost leg
#define IOUT_4SWBB_RESET_CONV1  0.900       // [A] Lower boost switch threshold for output current - PWM1&PWM2 Buck-Boost leg
#define IOUT_4SWBB_TRIP_CONV2   1.100       // [A] Upper boost switch threshold for output current - PWM5&PWM7 Buck-Boost leg
#define IOUT_4SWBB_RESET_CONV2  0.900       // [A] Lower boost switch threshold for output current - PWM5&PWM7 Buck-Boost leg

#define DUTY_RATIO_MIN          0.010       // Minimum duty ration 
#define DUTY_RATIO_MAX          0.800       // maximum duty ratio
#define DUTY_RATIO_INIT         0.010       // maximum duty ratio


/*!System Configuration Limits
 * ************************************************************************************************
 * Summary:
 * Set of defines and marcos for easy hardware migration/changes
 *
 * Description:
 * The following macros translate physical values from defines above to 
 * integer values which can be written to registers.
 * 
 * See also:
 * ************************************************************************************************/

#define VIN_UVLO_TRIP           (uint16_t)(VIN_MINIMUM * VIN_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VIN_UVLO_RELEASE        (uint16_t)((VIN_MINIMUM + VIN_MINIMUM_HYST) * VIN_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VIN_FB_REF_ADC          (uint16_t)((float)VIN_DIVIDER_RATIO * (float)VIN_NOMINAL * ADC_SCALER)   // Input voltage feedback in ADC ticks
#define VIN_OVLO_TRIP           (uint16_t)((float)VIN_MAXIMUM * (float)VIN_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks
#define VIN_OVLO_RELEASE        (uint16_t)(((float)VIN_MAXIMUM - (float)VIN_MAXIMUM_HYST) * (float)VIN_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks

#define VOUT_UVLO_TRIP          (uint16_t)(VOUT_MINIMUM * VOUT_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_UVLO_RELEASE       (uint16_t)((VOUT_MINIMUM + VOUT_MINIMUM_HYST) * VOUT_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_FB_REF_ADC         (uint16_t)((float)VOUT_DIVIDER_RATIO * (float)VOUT_NOMINAL * ADC_SCALER)   // Input voltage feedback in ADC ticks
#define VOUT_OVP_TRIP           (uint16_t)((float)VOUT_MAXIMUM * (float)VOUT_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define VOUT_OVP_RELEASE        (uint16_t)(((float)VOUT_MAXIMUM - (float)VOUT_MAXIMUM_HYST) * (float)VOUT_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks

#define IOUT_OCL_TRIP           (uint16_t)((((float)IOUT_MAXIMUM * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks

// 4-Switch Buck/Boost operation PWM-leg control

#define IOUT_4SWBB_UTH_CONV1    (uint16_t)((((float)IOUT_4SWBB_TRIP_CONV1 * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_LTH_CONV1    (uint16_t)((((float)IOUT_4SWBB_RESET_CONV1 * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_UTH_CONV2    (uint16_t)((((float)IOUT_4SWBB_TRIP_CONV2 * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_LTH_CONV2    (uint16_t)((((float)IOUT_4SWBB_RESET_CONV2 * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks

#define DUTY_RATIO_MIN_REG (uint16_t)((float)DUTY_RATIO_MIN * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MAX_REG (uint16_t)((float)DUTY_RATIO_MAX * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_INIT_REG (uint16_t)((float)DUTY_RATIO_INIT * (float)SWITCHING_PERIOD)




#endif	/* __SYSTEM_DESIGN_LIMITS_H__ */

