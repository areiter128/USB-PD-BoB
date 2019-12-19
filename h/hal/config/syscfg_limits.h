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

#include "hal/hal.h"

// Converter input and output voltage and current levels

#define VIN_MINIMUM             9.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VIN_MINIMUM_HYST        0.500        // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)

#define VIN_NOMINAL             13.800       // Nominal input voltage in [V]

#define VIN_MAXIMUM             18.000      // input voltage maximum (Under-Voltage-Lockout-Level)
#define VIN_MAXIMUM_HYST        0.500       // input voltage maximum (Under-Voltage-Lockout Hysteresis Level)

#define VOUT_MINIMUM            4.000       // input voltage minimum (Under-Voltage-Lockout-Level)
#define VOUT_MINIMUM_HYST       0.500       // input voltage minimum (Under-Voltage-Lockout Hysteresis Level)

#define VOUT_NOMINAL            5.000       // Nominal input voltage in [V]
#define VOUT_MAX_DEVIATION      0.500       // maximum allowed daviation at output voltage 

#define VOUT_MAXIMUM            22.000      // output voltage maximum (Under-Voltage-Lockout-Level)
#define VOUT_MAXIMUM_HYST       0.500       // output voltage maximum (Under-Voltage-Lockout Hysteresis Level)

#define IOUT_MINIMUM            -0.500       // absolute minimum average output current during normal operation // Carlo
#define IOUT_MAX_STARTUP        1.000       // absolute minimum average output current during startup (inrush current limit)
#define IOUT_MAXIMUM            3.000       // absolute maximum average output current during normal operation
#define IOUT_OVER_CURRENT_LIMIT 3.500       // absolute maximum average output current during normal operation
    
#define IOUT_4SWBB_TRIP_CONV1   1.100       // [A] Upper boost switch threshold for output current - PWM1&PWM2 Buck-Boost leg
#define IOUT_4SWBB_RESET_CONV1  0.900       // [A] Lower boost switch threshold for output current - PWM1&PWM2 Buck-Boost leg
#define IOUT_4SWBB_TRIP_CONV2   1.100       // [A] Upper boost switch threshold for output current - PWM5&PWM7 Buck-Boost leg
#define IOUT_4SWBB_RESET_CONV2  0.900       // [A] Lower boost switch threshold for output current - PWM5&PWM7 Buck-Boost leg

#define TEMP_RELEASE_LIMIT      60.00       // Temperature in [°C] at which warning status flag bit will be cleared
#define TEMP_WARNING_LIMIT      80.00       // Temperature in [°C] at which a warning status flag bit should be set
#define TEMP_PROTECTION_LIMIT   100.0       // Temperature in [°C] at which the power supply will be shut down

#define DUTY_RATIO_BUCK_LEG_INIT    0.0525  // Initial duty ratio of buck leg at PWM start
#define DUTY_RATIO_MIN_BUCK         0.0525  // Minimum duty ration buck leg
#define DUTY_RATIO_MAX_BUCK         0.8950  // maximum duty ratio buck leg

#define DUTY_RATIO_BOOST_LEG_INIT   0.0525  // Initial duty ratio of boost leg at PWM start
#define DUTY_RATIO_MIN_BOOST        0.0525  // Minimum duty ration boost leg
#define DUTY_RATIO_MAX_BOOST        0.7000  // maximum duty ratio boost leg


#define SSM_MOD_RANGE_LEVEL_1       0x7E00  // Spread Spectrum Modulation Range of +/- 1.6 %
#define SSM_MOD_RANGE_LEVEL_2       0x7C00  // Spread Spectrum Modulation Range of +/- 3.2 %
#define SSM_MOD_RANGE_LEVEL_3       0x7800  // Spread Spectrum Modulation Range of +/- 6.7 %

#define SPREAD_SPECTRUM_MODULATION_RANGE    SSM_MOD_RANGE_LEVEL_1    // Range between 0-10 % 


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

#define VIN_UVLO_TRIP           (uint16_t)(VIN_MINIMUM * VIN_DIVIDER_RATIO * HSADC_SCALER) // Input voltage sense ADC ticks
#define VIN_UVLO_RELEASE        (uint16_t)((VIN_MINIMUM + VIN_MINIMUM_HYST) * VIN_DIVIDER_RATIO * HSADC_SCALER) // Input voltage sense ADC ticks
#define VIN_FB_REF_ADC          (uint16_t)((float)VIN_DIVIDER_RATIO * (float)VIN_NOMINAL * HSADC_SCALER)   // Input voltage feedback in ADC ticks
#define VIN_OVLO_TRIP           (uint16_t)((float)VIN_MAXIMUM * (float)VIN_DIVIDER_RATIO * (float)HSADC_SCALER) // Input voltage sense ADC ticks
#define VIN_OVLO_RELEASE        (uint16_t)(((float)VIN_MAXIMUM - (float)VIN_MAXIMUM_HYST) * (float)VIN_DIVIDER_RATIO * (float)HSADC_SCALER) // Input voltage sense ADC ticks

#define VOUT_UVLO_TRIP          (uint16_t)(VOUT_MINIMUM * VOUT_DIVIDER_RATIO * HSADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_UVLO_RELEASE       (uint16_t)((VOUT_MINIMUM + VOUT_MINIMUM_HYST) * VOUT_DIVIDER_RATIO * HSADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_FB_REF_ADC         (uint16_t)((float)VOUT_DIVIDER_RATIO * (float)VOUT_NOMINAL * HSADC_SCALER)   // Output voltage feedback in ADC ticks
#define VOUT_OVP_TRIP           (uint16_t)((float)VOUT_MAXIMUM * (float)VOUT_DIVIDER_RATIO * (float)HSADC_SCALER) // Output voltage sense ADC ticks
#define VOUT_OVP_RELEASE        (uint16_t)(((float)VOUT_MAXIMUM - (float)VOUT_MAXIMUM_HYST) * (float)VOUT_DIVIDER_RATIO * (float)HSADC_SCALER) // Input voltage sense ADC ticks
#define VOUT_MAX_DEV            (uint16_t)((float)VOUT_DIVIDER_RATIO * (float)VOUT_MAX_DEVIATION * HSADC_SCALER)   // Maximum allowed output voltage deviation in ADC ticks 

#define IOUT_LCL_CLAMP          (int16_t)((((float)IOUT_MINIMUM * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output current sense ADC ticks // Carlo
#define IOUT_INRUSH_CLAMP       (uint16_t)((((float)IOUT_MAX_STARTUP * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output current sense ADC ticks
#define IOUT_OCL_TRIP           (uint16_t)((((float)IOUT_OVER_CURRENT_LIMIT * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output current sense ADC ticks
#define IOUT_OCL_RELEASE        (uint16_t)((((float)IOUT_MAXIMUM * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output current sense ADC ticks

#define TEMP_OTW_TRIP           (uint16_t)(((float)TEMP_WARNING_LIMIT * (float)TEMP_SLOPE_TICKS) + (float)TEMP_OFFSET_TICKS) // Temperature sense ADC ticks
#define TEMP_OTW_RELEASE        (uint16_t)(((float)TEMP_RELEASE_LIMIT * (float)TEMP_SLOPE_TICKS) + (float)TEMP_OFFSET_TICKS) // Temperature sense ADC ticks

#define TEMP_OTP_TRIP           (uint16_t)(((float)TEMP_PROTECTION_LIMIT  * (float)TEMP_SLOPE_TICKS) + (float)TEMP_OFFSET_TICKS) // Temperature sense ADC ticks
#define TEMP_OTP_RELEASE        (uint16_t)(((float)TEMP_RELEASE_LIMIT  * (float)TEMP_SLOPE_TICKS) + (float)TEMP_OFFSET_TICKS) // Temperature sense ADC ticks

// 4-Switch Buck/Boost operation PWM-leg control

#define IOUT_4SWBB_UTH_CONV1    (uint16_t)((((float)IOUT_4SWBB_TRIP_CONV1 * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_LTH_CONV1    (uint16_t)((((float)IOUT_4SWBB_RESET_CONV1 * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_UTH_CONV2    (uint16_t)((((float)IOUT_4SWBB_TRIP_CONV2 * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output voltage sense ADC ticks
#define IOUT_4SWBB_LTH_CONV2    (uint16_t)((((float)IOUT_4SWBB_RESET_CONV2 * (float)IOUT_SCALER_RATIO_I2V)) * (float)HSADC_SCALER) // Output voltage sense ADC ticks

#define DUTY_RATIO_INIT_BUCK_REG    (uint16_t)((float)DUTY_RATIO_BUCK_LEG_INIT * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MIN_BUCK_REG     (uint16_t)((float)DUTY_RATIO_MIN_BUCK * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MAX_BUCK_REG     (uint16_t)((float)DUTY_RATIO_MAX_BUCK * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_INIT_BOOST_REG   (uint16_t)((float)DUTY_RATIO_BOOST_LEG_INIT * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MIN_BOOST_REG    (uint16_t)((float)DUTY_RATIO_MIN_BOOST * (float)SWITCHING_PERIOD)
#define DUTY_RATIO_MAX_BOOST_REG    (uint16_t)((float)DUTY_RATIO_MAX_BOOST * (float)SWITCHING_PERIOD)

#define SSM_MOD_RANGE_MASK      (uint16_t)(SPREAD_SPECTRUM_MODULATION_RANGE)


#endif	/* __SYSTEM_DESIGN_LIMITS_H__ */

