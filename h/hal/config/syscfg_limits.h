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

#define VIN_MINIMUM             12.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VIN_MINIMUM_HYST        0.500        // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)
#define VIN_UVLO_TRIP           (uint16_t)(VIN_MINIMUM * VIN_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VIN_UVLO_RELEASE        (uint16_t)((VIN_MINIMUM + VIN_MINIMUM_HYST) * VIN_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks

#define VIN_NOMINAL             19.800       // Nominal input voltage in [V]
#define VIN_FB_REF_ADC          (uint16_t)((float)VIN_DIVIDER_RATIO * (float)VIN_NOMINAL * ADC_SCALER)   // Input voltage feedback in ADC ticks

#define VIN_MAXIMUM             22.000      // input voltage maximum (Under-Voltage-Lockout-Level)
#define VIN_MAXIMUM_HYST        0.500       // input voltage maximum (Under-Voltage-Lockout Hysteresis Level)
#define VIN_OVLO_TRIP           (uint16_t)((float)VIN_MAXIMUM * (float)VIN_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks
#define VIN_OVLO_RELEASE        (uint16_t)(((float)VIN_MAXIMUM - (float)VIN_MAXIMUM_HYST) * (float)VIN_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks


#define V_DCLINK_MINIMUM       12.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define V_DCLINK_MINIMUM_HYST  0.500        // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)
#define V_DCLINK_UVLO_TRIP     (uint16_t)(V_DCLINK_MINIMUM * V_DCLINK_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define V_DCLINK_UVLO_RELEASE  (uint16_t)((V_DCLINK_MINIMUM + V_DCLINK_MINIMUM_HYST) * V_DCLINK_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks

#define V_DCLINK_NOMINAL       19.800       // Nominal input voltage in [V]
#define V_DCLINK_FB_REF_ADC    (uint16_t)((float)VIN_DIVIDER_RATIO * (float)V_DCLINK_NOMINAL * ADC_SCALER)   // Input voltage feedback in ADC ticks

#define V_DCLINK_MAXIMUM       22.000      // input voltage maximum (Under-Voltage-Lockout-Level)
#define V_DCLINK_MAXIMUM_HYST  0.500       // input voltage maximum (Under-Voltage-Lockout Hysteresis Level)
#define V_DCLINK_OVLO_TRIP     (uint16_t)((float)V_DCLINK_MAXIMUM * (float)V_DCLINK_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks
#define V_DCLINK_OVLO_RELEASE  (uint16_t)(((float)V_DCLINK_MAXIMUM - (float)V_DCLINK_MAXIMUM_HYST) * (float)V_DCLINK_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks


#define VOUT_MINIMUM         6.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VOUT_MINIMUM_HYST    0.500       // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)
#define VOUT_UVLO_TRIP       (uint16_t)(VOUT_MINIMUM * VOUT_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_UVLO_RELEASE    (uint16_t)((VOUT_MINIMUM + VOUT_MINIMUM_HYST) * VOUT_DIVIDER_RATIO * ADC_SCALER) // Input voltage sense ADC ticks

#define VOUT_NOMINAL         7.000       // Nominal input voltage in [V]
#define VOUT_FB_REF_ADC      (uint16_t)((float)VOUT_DIVIDER_RATIO * (float)VOUT_NOMINAL * ADC_SCALER)   // Input voltage feedback in ADC ticks

#define VOUT_MAXIMUM         12.000      // output voltage maximum (Under-Voltage-Lockout-Level)
#define VOUT_MAXIMUM_HYST    0.500       // output voltage maximum (Under-Voltage-Lockout Hysteresis Level)
#define VOUT_OVP_TRIP        (uint16_t)((float)VOUT_MAXIMUM * (float)VOUT_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define VOUT_OVP_RELEASE     (uint16_t)(((float)VOUT_MAXIMUM - (float)VOUT_MAXIMUM_HYST) * (float)VOUT_DIVIDER_RATIO * (float)ADC_SCALER) // Input voltage sense ADC ticks

#define IOUT_MAXIMUM        10.000   // absolute maximum average output current during normal operation
#define IOUT_OCL_TRIP       (uint16_t)((((float)IOUT_MAXIMUM * (float)IOUT_SCALER_RATIO_I2V)) * (float)ADC_SCALER) // Output voltage sense ADC ticks
    


#define VBATx_MINIMUM         6.000       // Output voltage minimum (Output Under-Voltage-Protection-Level)
#define VBATx_MINIMUM_HYST    0.300       // Output voltage maximum (Output Under-Voltage-Protection Hysteresis Level)
#define VBATx_UVP_TRIP       (uint16_t)((float)VBATx_MINIMUM * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define VBATx_UVP_RELEASE    (uint16_t)(((float)VBATx_MINIMUM + (float)VBATx_MINIMUM_HYST) * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks

#define VBATx_MAXIMUM         8.900       // Output voltage minimum (Output Over-Voltage-Protection-Level)
#define VBATx_MAXIMUM_HYST    0.300       // Output voltage maximum (Output Over-Voltage-Protection Hysteresis Level)
#define VBATx_OVP_TRIP       (uint16_t)((float)VBATx_MAXIMUM * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks
#define VBATx_OVP_RELEASE    (uint16_t)(((float)VBATx_MAXIMUM - (float)VBATx_MAXIMUM_HYST) * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER) // Output voltage sense ADC ticks

// Charging Profile Voltage Levels
#define VBATx_CRG_TRICKLE     6.300       // battery voltage level enforcing trickle current charging in [V]
#define VBATx_CRG_PULSE       6.800       // battery voltage level enforcing pulse current charging in [V]
#define VBATx_CRG_CONST_I     7.300       // battery voltage level enforcing constant current charging in [V]
#define VBATx_CRG_COMPLETE    8.400       // battery voltage level enforcing constant voltage charging in [V]
#define VBATx_CRG_HYSTERESIS  0.200       // battery voltage level enforcing constant voltage charging in [V]

#define VBATx_CRG_TRICKLE_ADC (uint16_t)((float)VBATx_CRG_TRICKLE * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER)   // Battery voltage in ADC ticks
#define VBATx_CRG_PULSE_ADC   (uint16_t)((float)VBATx_CRG_PULSE * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER)   // Battery voltage in ADC ticks
#define VBATx_CRG_CONST_I_ADC (uint16_t)((float)VBATx_CRG_CONST_I * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER)   // Battery voltage in ADC ticks
#define VBATx_CRG_COMPLETE_ADC (uint16_t)((float)VBATx_CRG_COMPLETE * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER)   // Battery voltage in ADC ticks
#define VBATx_CRG_HYST_ADC    (uint16_t)((float)VBATx_CRG_HYSTERESIS * (float)VBATx_DIVIDER_RATIO * (float)ADC_SCALER)   // Battery voltage in ADC ticks

#define IBATx_OVER_CURRENT_THSHLD 4.500   // absolute maximum average output current during normal operation
#define IBATx_OCL_TRIP      (uint16_t)((float)(((float)IBATx_OVER_CURRENT_THSHLD * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks

#define IBATx_STARTUP         0.080 // absolute maximum average output current during st sartup in [A]
#define IBATx_CRG_TRICKLE     0.150 // battery voltage level enforcing trickle current charging in [A]
#define IBATx_CRG_PULSE       1.500 // battery voltage level enforcing pulse current charging in [A]
#define IBATx_CRG_CONST_I     2.000 // current reference for constant current charging in [A]
#define IBATx_CRG_EOC_HOLD    0.500 // current reference for constant Hold-up current charging at END OF CHARGE in [A]
#define IBATx_CRG_COMPLETE    0.100 // battery voltage level enforcing constant voltage charging in [A]

#define IBATx_OCL_STARTUP   (uint16_t)((float)(((float)IBATx_STARTUP * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_TRICKLE   (uint16_t)((float)(((float)IBATx_CRG_TRICKLE * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_PULSE     (uint16_t)((float)(((float)IBATx_CRG_PULSE * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_CONST_I   (uint16_t)((float)(((float)IBATx_CRG_CONST_I * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_CONST_I   (uint16_t)((float)(((float)IBATx_CRG_CONST_I * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_EOC_HOLD  (uint16_t)((float)(((float)IBATx_CRG_EOC_HOLD * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks
#define IBATx_OCL_COMPLETE  (uint16_t)((float)(((float)IBATx_CRG_COMPLETE * (float)IBATx_SCALER_RATIO_I2V) * (float)ADC_SCALER)) // Current feedback voltage sense ADC ticks


#define DUTY_RATIO_MIN      0.01    // Minimum duty ration 
#define DUTY_RATIO_MAX      0.80    // maximum duty ratio
#define DUTY_RATIO_INIT     0.01    // maximum duty ratio

#define DUTY_RATIO_MIN_REG (uint16_t)((float)DUTY_RATIO_MIN * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MAX_REG (uint16_t)((float)DUTY_RATIO_MAX * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_INIT_REG (uint16_t)((float)DUTY_RATIO_INIT * (float)SWITCHING_PERIOD)

#endif	/* __SYSTEM_DESIGN_LIMITS_H__ */

