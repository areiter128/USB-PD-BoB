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

#ifndef _HARDWARE_ABSTRACTION_LAYER_SYSTEM_SCALING_H_
#define	_HARDWARE_ABSTRACTION_LAYER_SYSTEM_SCALING_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include <dsp.h>
#include <math.h>

#ifdef __10888_P33CK_R30__

    // DSC bias voltage
    #define DEVICE_VDD                  3.300       // Device bias voltage in [V]

    // Inductance of the main inductor
    #define INDUCTANCE                  4.700       // Inductance in [µH]
    #define CAPACITANCE                 300e-6      // Output Capacity

    // Feedback Scaling
    #define VIN_DIVIDER_R1              18000       // Resitance of upper voltage divider resistor in Ohm
    #define VIN_DIVIDER_R2              2000        // Resitance of lower voltage divider resistor in Ohm
    #define VIN_AMP_GAIN                1.000       // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define VIN_FEEDBACK_OFFSET         0.000       // Input voltage sense offset

    #define VOUT_DIVIDER_R1             8200        // Resitance of upper voltage divider resistor in Ohm
    #define VOUT_DIVIDER_R2             2050        // Resitance of lower voltage divider resistor in Ohm
    #define VOUT_AMP_GAIN               1.000       // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define VOUT_SENSE_OFFSET           0.000       // Output voltage sense offset

    #define VIN2VOUT_NORMALIZATION      0x7fff      //(int16_t)(ceiling(log(VOUT_DIVIDER_RATIO/VIN_DIVIDER_RATIO)))
    #define VIN2VOUT_NORM_BSFT          1

    #define CS_AMP_GAIN                 20.000      // Current sense amplifier gain in [V/V]
    #define CS_SHUNT_RESISTANCE         10.0e-3     // Current sense resistor value in [Ohm]
    #define CS_PROPAGATION_DELAY        560.0e-9    // signal phase shift for accurate triggering
    #define CS_COMMON_MODE_V_MIN        2.500       // Common mode minimum voltage at which the amplifier starts to provide an output signal

    #define IOUT_IS_BI_DIRECTIONAL      false       // Current sens is (0=uni-directional, 1=bi-directional)
    #define IOUT_FEEDBACK_OFFSET        0.000       // Current sense zero offset 

    // System Settings
    #define SWITCHING_FREQUENCY         300e+3      // Nominal switching frequency per converter phase in [Hz]
    #define PWM_DEAD_TIME_RISING        20e-9       // Nominal dead time at the leading edge in [ns]
    #define PWM_DEAD_TIME_FALLING       60e-9       // Nominal dead time at the falling edge in [ns]
    #define LEADING_EDGE_BLANKING_PER   150e-9		// Leading Edge Blanking period in nanoseconds
    #define ADC_TRIGGER_OFFSET          120e-9      // ADC trigger offset compensating for propagat6ion delays

    // PWM time base Settings
    #define f_ACLK                      4e+9        // 4 GHz PWM tick rate
    #define T_ACLK                      250e-12     // 250 ps PWM resolution
    #define PWM_PCLKDIV_PRIMARY         1           // PWM Input Clock Divider

#endif

#ifdef __10889_P33CH_R10__

    // DSC bias voltage
    #define DEVICE_VDD                  3.300       // Device bias voltage in [V]

    // Inductance of the main inductor
    #define INDUCTANCE                  4.700       // Inductance in [µH]
    #define CAPACITANCE                 300e-6      // Output Capacity

    // Feedback Scaling
    #define VIN_DIVIDER_R1              18000       // Resitance of upper voltage divider resistor in Ohm
    #define VIN_DIVIDER_R2              2000        // Resitance of lower voltage divider resistor in Ohm
    #define VIN_AMP_GAIN                1.000       // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define VIN_FEEDBACK_OFFSET         0.000       // Input voltage sense offset

    #define VOUT_DIVIDER_R1             8200        // Resitance of upper voltage divider resistor in Ohm
    #define VOUT_DIVIDER_R2             2050        // Resitance of lower voltage divider resistor in Ohm
    #define VOUT_AMP_GAIN               1.000       // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define VOUT_SENSE_OFFSET           0.000       // Output voltage sense offset

    #define VIN2VOUT_NORMALIZATION      0x7fff      //(int16_t)(ceiling(log(VOUT_DIVIDER_RATIO/VIN_DIVIDER_RATIO)))
    #define VIN2VOUT_NORM_BSFT          1

    #define CS_AMP_GAIN                 20.000      // Current sense amplifier gain in [V/V]
    #define CS_SHUNT_RESISTANCE         10.0e-3     // Current sense resistor value in [Ohm]
    #define CS_PROPAGATION_DELAY        560.0e-9    // signal phase shift for accurate triggering
    #define CS_COMMON_MODE_V_MIN        2.500       // Common mode minimum voltage at which the amplifier starts to provide an output signal

    #define IOUT_IS_BI_DIRECTIONAL      false       // Current sens is (0=uni-directional, 1=bi-directional)
    #define IOUT_FEEDBACK_OFFSET        0.000       // Current sense zero offset 

    // System Settings
    #define SWITCHING_FREQUENCY         300e+3      // Nominal switching frequency per converter phase in [Hz]
    #define PWM_DEAD_TIME_RISING        20e-9       // Nominal dead time at the leading edge in [ns]
    #define PWM_DEAD_TIME_FALLING       60e-9       // Nominal dead time at the falling edge in [ns]
    #define LEADING_EDGE_BLANKING_PER   150e-9		// Leading Edge Blanking period in nanoseconds
    #define ADC_TRIGGER_OFFSET          120e-9      // ADC trigger offset compensating for propagat6ion delays

    // PWM time base Settings
    #define f_ACLK                      4e+9        // 4 GHz PWM tick rate
    #define T_ACLK                      250e-12     // 250 ps PWM resolution
    #define PWM_PCLKDIV_PRIMARY         1           // PWM Input Clock Divider

#endif


/*!System Configuration Scaling
 * ************************************************************************************************
 * Summary:
 * Set of defines and marcos for easy hardware migration/changes
 *
 * Description:
 * The following macros translate physical values of hardware specifications and signals into 
 * integer values which can be written to registers.
 * 
 * See also:
 * ************************************************************************************************/

// Macros are used to translate physical values into register values

#define SWITCHING_PERIOD            ((uint16_t)(((float)((1.0/(float)(SWITCHING_FREQUENCY))/T_ACLK)-1)))

// Macro calculating Leading Edge Blanking period counter value based on time base frequency selection
#define REG_LEB_PERIOD_MASK         0b1111111111111111
#define LEB_PERIOD                  ((uint16_t)((uint16_t)(((float)(LEADING_EDGE_BLANKING_PER))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY))

// Macro calculating ADC offset period counter value based on time base frequency selection
#define ADC_TRIG_OFFSET             ((uint16_t)((uint16_t)(((float)(ADC_TRIGGER_OFFSET))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_LEB_PERIOD_MASK)

// Macros calculating Dead Time Rising/Falling Edge period counter value based on time base frequency selection
#define REG_DTRx_VALID_BIT_MSK      0b0011111111111111
#define REG_ALTDTRx_VALID_BIT_MSK   0b0011111111111111
#define PWM_DEAD_TIME_LE            ((uint16_t)((uint16_t)(((float)(PWM_DEAD_TIME_RISING))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_DTRx_VALID_BIT_MSK)
#define PWM_DEAD_TIME_FE            ((uint16_t)((uint16_t)(((float)(PWM_DEAD_TIME_FALLING))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_ALTDTRx_VALID_BIT_MSK)

// Macros calculating register values based on the physical values given above

#define VIN_DIVIDER_RATIO           (float)((float)VIN_AMP_GAIN * ((float)VIN_DIVIDER_R2) / ((float)(VIN_DIVIDER_R1 + VIN_DIVIDER_R2)))
#define VIN_DIVIDER_RATIO_INV       (float)( 1.0 / VIN_DIVIDER_RATIO )
#define VIN_FB_OFFSET               (uint16_t)(VIN_FEEDBACK_OFFSET * ADC_SCALER)    // Input voltage sense offset ADC ticks

#define VOUT_DIVIDER_RATIO          (float)((float)VOUT_AMP_GAIN * ((float)VOUT_DIVIDER_R2) / ((float)(VOUT_DIVIDER_R1 + VOUT_DIVIDER_R2)))
#define VOUT_DIVIDER_RATIO_INV      (float)( 1.0 / VOUT_DIVIDER_RATIO )
#define VOUT_FB_OFFSET              (int16_t)(VOUT_SENSE_OFFSET * ADC_SCALER)   // Output voltage sense offset ADC ticks

#define IOUT_SCALER_RATIO_I2V       (float)((float)CS_SHUNT_RESISTANCE * (float)CS_AMP_GAIN) // Current feeback ratio in [V/A] => used to convert current into feedback voltage
#define IOUT_SCALER_RATIO_V2I       (float)(1.0/((float)IOUT_SCALER_RATIO_I2V))  // Current feeback ratio in [A/V] => used to convert feedback voltage into current
#define IOUT_SCALER_RATIO_TICKS     (uint16_t)((float)IOUT_SCALER_RATIO_I2V * (float)ADC_SCALER) // Current feeback ratio in [Ticks/A] => used to convert current into ADC ticks

#define IOUT_SCALER_OFFSET_TICKS    (uint16_t)((float)IOUT_FEEDBACK_OFFSET * (float)ADC_SCALER) // Current sense offset ADC ticks
#define IOUT_PROPAGATION_DELAY      (uint16_t)((float)CS_PROPAGATION_DELAY /(float)T_ACLK) // current feedback signal phase shift
#define IOUT_COMMON_MODE_V_MIN      (uint16_t)((float)CS_COMMON_MODE_V_MIN * (float)VOUT_DIVIDER_RATIO * (float)ADC_SCALER) // Current sense minimum common mode voltage ADC ticks


#endif	/* _HARDWARE_ABSTRACTION_LAYER_SYSTEM_SCALING_H_ */

