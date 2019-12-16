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

#include "hal/hal.h"

#if defined (__00173_USB_PD_BOB_R20__) || defined (__MA330048_P33CK_R30_USB_PD_BOB__)


/*!ADC Settings
 * *************************************************************************************************
 * Summary:
 * Global defines for specific parameters of the device ADC
 * 
 * Description:
 * This section is used to define device specific parameters of ADC reference, resolution
 * and granularity to calculate register values representing physical voltages.
 * Pre-compiler macros are used to translate physical values into binary (integer) numbers 
 * to be written to SFRs
 * 
 * *************************************************************************************************/

#define ADC_REF              3.300 // ADC reference voltage in V
#define ADC_RESOLUTION       12.0  // ADC resolution in [bit]
#define ADC_GRANULARITY  (float)(ADC_REF / pow(2.0, ADC_RESOLUTION)) // ADC granularity in [V/tick]

/*!Hardware Abstraction
 * *************************************************************************************************
 * Summary:
 * Global defines for hardware specific parameters
 * 
 * Description:
 * This section is used to define hardware specific parameters such as output voltage dividers,
 * reference levels or feedback gains. Pre-compiler macros are used to translate physical  
 * values into binary (integer) numbers to be written to SFRs and variables.
 * 
 * *************************************************************************************************/
    

    // DSC bias voltage
    #define DEVICE_VDD                  3.300       // Device bias voltage in [V]

    // Inductance of the main inductor
    #define INDUCTANCE                  5.600       // Inductance in [µH]
    #define CAPACITANCE                 150e-6      // Output Capacity


    // Output Voltage Feedback Scaling and Nominal Signal Levels
    #define C4SWBB_VOUT_NOMINAL          5.0    // Nominal output voltage in [V]
    #define C4SWBB_VOUT_MINIMUM          4.5    // Maximum output voltage in [V]
    #define C4SWBB_VOUT_MAXIMUM          21.0   // Maximum output voltage in [V]
    #define C4SWBB_VOUT_HYSTERESIS       1.0    // Output voltage protection hysteresis in [V]
    #define C4SWBB_VOUT_UPPER_DEVIATION  2.0    // Upper output voltage deviation from reference in [V]
    #define C4SWBB_VOUT_LOWER_DEVIATION  0.8    // Lower output voltage deviation from reference in [V]

    #define C4SWBB_VOUT_LEVEL_5V         5.0    // Nominal output voltage in [V]
    #define C4SWBB_VOUT_LEVEL_9V         9.0    // Nominal output voltage in [V]
    #define C4SWBB_VOUT_LEVEL_12V        12.0   // Nominal output voltage in [V]
    #define C4SWBB_VOUT_LEVEL_15V        15.0   // Nominal output voltage in [V]
    #define C4SWBB_VOUT_LEVEL_20V        20.0   // Nominal output voltage in [V]

    #define C4SWBB_VOUT_DIV_R1           18000.0  // Resitance of upper voltage divider resistor in kOhm
    #define C4SWBB_VOUT_DIV_R2           2870.0   // Resitance of lower voltage divider resistor in kOhm
    #define C4SWBB_VOUT_AMP_GAIN         1.000  // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define C4SWBB_VOUT_SENSE_OFFSET     0.000  // Output voltage sense offset

    //~~~~~~~~~~~~~~~~~ conversion macros ~~~~~~~~~~~~~~~~~~
    #define C4SWBB_VOUT_FB_GAIN      (float)(C4SWBB_VOUT_AMP_GAIN * (((float)C4SWBB_VOUT_DIV_R2) / (((float)C4SWBB_VOUT_DIV_R1) + ((float)C4SWBB_VOUT_DIV_R2))))
    #define C4SWBB_VOUT_OFFSET       (uint16_t)(C4SWBB_VOUT_SENSE_OFFSET * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_REF          (uint16_t)(C4SWBB_VOUT_NOMINAL * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_OVP          (uint16_t)(C4SWBB_VOUT_MAXIMUM * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_HYST         (uint16_t)(C4SWBB_VOUT_HYSTERESIS * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_UDEVI        (uint16_t)(C4SWBB_VOUT_UPPER_DEVIATION * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_LDEVI        (uint16_t)(C4SWBB_VOUT_LOWER_DEVIATION * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)

    #define C4SWBB_VOUT_REF_5V       (uint16_t)(C4SWBB_VOUT_LEVEL_5V * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_REF_9V       (uint16_t)(C4SWBB_VOUT_LEVEL_9V * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_REF_12V      (uint16_t)(C4SWBB_VOUT_LEVEL_12V * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_REF_15V      (uint16_t)(C4SWBB_VOUT_LEVEL_15V * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VOUT_REF_20V      (uint16_t)(C4SWBB_VOUT_LEVEL_20V * C4SWBB_VOUT_FB_GAIN / ADC_GRANULARITY)
    //~~~~~~~~~~~~~~~~~

    // Input Voltage Feedback Scaling
    #define C4SWBB_VIN_DIV_R1          36000.0       // Resitance of upper voltage divider resistor in Ohm
    #define C4SWBB_VIN_DIV_R2          2870.0        // Resitance of lower voltage divider resistor in Ohm
    #define C4SWBB_VIN_AMP_GAIN        1.000       // Gain factor or additional op-amp (set to 1.0 if none is used)
    #define C4SWBB_VIN_FEEDBACK_OFFSET 0.000       // Input voltage sense offset

    #define C4SWBB_VIN_MINIMUM      7.0         // Minimum input voltage in [V]
    #define C4SWBB_VIN_MAXIMUM      20.0        // Maximum input voltage in [V]
    #define C4SWBB_VIN_HYSTERESIS   1.0         // Input voltage protection hysteresis in [V]

    //~~~~~~~~~~~~~~~~~ conversion macros ~~~~~~~~~~~~~~~~~~
    #define C4SWBB_VIN_FB_GAIN       (float)((C4SWBB_VIN_DIV_R2) / (C4SWBB_VIN_DIV_R1 + C4SWBB_VIN_DIV_R2))
    #define C4SWBB_VIN_UVLO          (uint16_t)(C4SWBB_VIN_MINIMUM * C4SWBB_VIN_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VIN_OVLO          (uint16_t)(C4SWBB_VIN_MAXIMUM * C4SWBB_VIN_FB_GAIN / ADC_GRANULARITY)
    #define C4SWBB_VIN_HYST          (uint16_t)(C4SWBB_VIN_HYSTERESIS * C4SWBB_VIN_FB_GAIN / ADC_GRANULARITY)

    #define VIN2VOUT_NORMALIZATION  0x7fff  // (int16_t)(ceiling(log(VOUT_DIVIDER_RATIO/VIN_DIVIDER_RATIO)))
    #define VIN2VOUT_NORM_BSFT      1       // Fixed-Point Bit-Shift of normalization factor
    //~~~~~~~~~~~~~~~~~

    #define C4SWBB_CS_AMP_GAIN          50.000      // Current sense amplifier gain in [V/V]
    #define C4SWBB_CS_SHUNT_RESISTANCE  4.0e-3      // Current sense resistor value in [Ohm]
    #define C4SWBB_CS_PROPAGATION_DELAY 560.0e-9    // signal phase shift for accurate triggering
    #define C4SWBB_CS_COMMON_MODE_V_MIN 0.0       // Common mode minimum voltage at which the amplifier starts to provide an output signal

    #define C4SWBB_IOUT_IS_BI_DIRECTIONAL   false       // Current sens is (0=uni-directional, 1=bi-directional)
    #define C4SWBB_IOUT_FEEDBACK_OFFSET     2020       // Current sense zero offset, 2048 ideal value but need to regulate at no load
                                                       // so 2020 offset allows current loop to integrate down to correct duty cycle for no load
    // System Settings
    #define SWITCHING_FREQUENCY         350e+3      // Nominal switching frequency per converter phase in [Hz]
    #define PWM_NO_OF_PHASES            2.0         // this board has two converters running parallel. Both will be operated 180° out of phase
    #define PWM_DEAD_TIME_RISING        50e-9       // Nominal dead time at the leading edge in [ns]
    #define PWM_DEAD_TIME_FALLING       60e-9       // Nominal dead time at the falling edge in [ns]
    #define LEADING_EDGE_BLANKING_PER   150e-9		// Leading Edge Blanking period in nanoseconds
    #define ADC_TRIGGER_OFFSET_VOUT     120e-9      // ADC trigger offset compensating for propagat6ion delays (voltage feedback)
    #define ADC_TRIGGER_OFFSET_IOUT     120e-9      // ADC trigger offset compensating for propagat6ion delays (current feedback)

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
#define PWM_PHASE_SFT               ((uint16_t)(((float)SWITCHING_PERIOD) / ((float)PWM_NO_OF_PHASES)))
#define PWM_DUTY_RATIO_MAX          ((uint16_t)(PWM_DUTY_RATIO_MAXIMUM * (float)SWITCHING_PERIOD))
#define PWM_DUTY_RATIO_MIN          ((uint16_t)(PWM_DUTY_RATIO_MINIMUM * (float)SWITCHING_PERIOD))

// Macro calculating Leading Edge Blanking period counter value based on time base frequency selection
#define REG_LEB_PERIOD_MASK         0b1111111111111111
#define LEB_PERIOD                  ((uint16_t)((uint16_t)(((float)(LEADING_EDGE_BLANKING_PER))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY))

// Macro calculating ADC offset period counter value based on time base frequency selection
#define ADC_TRIG_OFFSET_VOUT        ((uint16_t)((uint16_t)(((float)(ADC_TRIGGER_OFFSET_VOUT))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_LEB_PERIOD_MASK)
#define ADC_TRIG_OFFSET_IOUT        ((uint16_t)((uint16_t)(((float)(ADC_TRIGGER_OFFSET_IOUT))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_LEB_PERIOD_MASK)

// Macros calculating Dead Time Rising/Falling Edge period counter value based on time base frequency selection
#define REG_DTRx_VALID_BIT_MSK      0b0011111111111111
#define REG_ALTDTRx_VALID_BIT_MSK   0b0011111111111111
#define PWM_DEAD_TIME_LE            ((uint16_t)((uint16_t)(((float)(PWM_DEAD_TIME_RISING))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_DTRx_VALID_BIT_MSK)
#define PWM_DEAD_TIME_FE            ((uint16_t)((uint16_t)(((float)(PWM_DEAD_TIME_FALLING))/((float)(T_ACLK))) >> PWM_PCLKDIV_PRIMARY) & REG_ALTDTRx_VALID_BIT_MSK)

// Macros calculating register values based on the physical values given above

#define VIN_DIVIDER_RATIO           (float)((float)C4SWBB_VIN_AMP_GAIN * ((float)C4SWBB_VIN_DIV_R2) / ((float)(C4SWBB_VIN_DIV_R1 + C4SWBB_VIN_DIV_R2)))
#define VIN_DIVIDER_RATIO_INV       (float)( 1.0 / VIN_DIVIDER_RATIO )
#define VIN_FB_OFFSET               (uint16_t)(C4SWBB_VIN_FEEDBACK_OFFSET * HSADC_SCALER)    // Input voltage sense offset ADC ticks

#define VOUT_DIVIDER_RATIO          (float)((float)C4SWBB_VOUT_AMP_GAIN * ((float)C4SWBB_VOUT_DIV_R2) / ((float)(C4SWBB_VOUT_DIV_R1 + C4SWBB_VOUT_DIV_R2)))
#define VOUT_DIVIDER_RATIO_INV      (float)( 1.0 / VOUT_DIVIDER_RATIO )
#define VOUT_FB_OFFSET              (int16_t)(C4SWBB_VOUT_SENSE_OFFSET * HSADC_SCALER)   // Output voltage sense offset ADC ticks

#define IOUT_SCALER_RATIO_I2V       (float)((float)C4SWBB_CS_SHUNT_RESISTANCE * (float)C4SWBB_CS_AMP_GAIN) // Current feeback ratio in [V/A] => used to convert current into feedback voltage
#define IOUT_SCALER_RATIO_V2I       (float)(1.0/((float)IOUT_SCALER_RATIO_I2V))  // Current feeback ratio in [A/V] => used to convert feedback voltage into current
#define IOUT_SCALER_RATIO_TICKS     (uint16_t)((float)IOUT_SCALER_RATIO_I2V * (float)HSADC_SCALER) // Current feeback ratio in [Ticks/A] => used to convert current into ADC ticks

#define IOUT_SCALER_OFFSET_TICKS    (uint16_t)((float)C4SWBB_IOUT_FEEDBACK_OFFSET * (float)HSADC_SCALER) // Current sense offset ADC ticks
#define IOUT_PROPAGATION_DELAY      (uint16_t)((float)C4SWBB_CS_PROPAGATION_DELAY /(float)T_ACLK) // current feedback signal phase shift
#define IOUT_COMMON_MODE_V_MIN      (uint16_t)((float)C4SWBB_CS_COMMON_MODE_V_MIN * (float)VOUT_DIVIDER_RATIO * (float)HSADC_SCALER) // Current sense minimum common mode voltage ADC ticks


#endif	/* _HARDWARE_ABSTRACTION_LAYER_SYSTEM_SCALING_H_ */

