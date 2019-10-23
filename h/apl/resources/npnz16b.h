/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.70.
 * ***************************************************************************************
 * Generic library header for z-domain compensation filter assembly functions
 * ***************************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__
#define __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__

#include <xc.h>
#include <dsp.h>
#include <stdint.h>
#include <stdbool.h>

/* Status flags (Single Bit) */
#define NPNZ16_STATUS_LSAT_SET             1
#define NPNZ16_STATUS_LSAT_CLEAR           0
#define NPNZ16_STATUS_USAT_SET             1
#define NPNZ16_STATUS_USAT_CLEAR           0
#define NPNZ16_STATUS_INPUT_INVERTED       1
#define NPNZ16_STATUS_INPUT_NOT_INVERTED   0
#define NPNZ16_STATUS_ENABLED              1
#define NPNZ16_STATUS_DISABLED             0

/* Status flags (bit-field) */
typedef enum {
    CONTROLLER_STATUS_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_SATUATION_MSK = 0b0000000000000011,
    CONTROLLER_STATUS_LSAT_ACTIVE = 0b0000000000000001,
    CONTROLLER_STATUS_LSAT_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_USAT_ACTIVE = 0b0000000000000010,
    CONTROLLER_STATUS_USAT_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_INV_INPUT_OFF = 0b0000000000000000,
    CONTROLLER_STATUS_INV_INPUT_ON = 0b0100000000000000,
    CONTROLLER_STATUS_ENABLE_OFF = 0b0000000000000000,
    CONTROLLER_STATUS_ENABLE_ON = 0b1000000000000000
} CONTROLLER_STATUS_FLAGS_t;

typedef union {
    struct {
        volatile unsigned flt_clamp_min : 1; // Bit 0: control loop is clamped at minimum output level
        volatile unsigned flt_clamp_max : 1; // Bit 1: control loop is clamped at maximum output level
        volatile unsigned : 1; // Bit 2: reserved
        volatile unsigned : 1; // Bit 3: reserved
        volatile unsigned : 1; // Bit 4: reserved
        volatile unsigned : 1; // Bit 5: reserved
        volatile unsigned : 1; // Bit 6: reserved
        volatile unsigned : 1; // Bit 7: reserved
        volatile unsigned : 1; // Bit 8: reserved
        volatile unsigned : 1; // Bit 9: reserved
        volatile unsigned : 1; // Bit 11: reserved
        volatile unsigned : 1; // Bit 11: reserved
        volatile unsigned : 1; // Bit 12: reserved
        volatile unsigned : 1; // Bit 13: reserved
        volatile unsigned invert_input: 1; // Bit 14: when set, most recent error input value to controller is inverted
        volatile unsigned enable : 1; // Bit 15: enables/disables control loop execution
    } __attribute__((packed))bits;    // Controller status bitfield for direct bit access
    volatile uint16_t value;          // Controller status full register access
} __attribute__((packed))CONTROLLER_STATUS_t; // Controller status data structure

typedef struct {
    // External control and monitoring
    volatile CONTROLLER_STATUS_t status; // Control Loop Status flags

    // Input/Output to controller
    volatile uint16_t* ptrSource; // Pointer to source register or variable where the input value is read from (e.g. ADCBUF0)
    volatile uint16_t* ptrTarget; // Pointer to target register or variable where the control output is written to (e.g. PCD1)
    volatile uint16_t* ptrControlReference; // Pointer to global variable of input register holding the controller reference value (e.g. uint16_t my_ref)

    // Filter coefficients and input/output histories
    volatile fractional* ptrACoefficients; // Pointer to A coefficients located in X-space 
    volatile fractional* ptrBCoefficients; // Pointer to B coefficients located in X-space 
    volatile fractional* ptrControlHistory; // Pointer to n delay-line samples located in Y-space with first sample being the most recent 
    volatile fractional* ptrErrorHistory; // Pointer to n+1 delay-line samples located in Y-space with first sample being the most recent 

    // Array size information
    volatile uint16_t ACoefficientsArraySize; // Size of the A coefficients array in X-space
    volatile uint16_t BCoefficientsArraySize; // Size of the B coefficients array in X-space
    volatile uint16_t ControlHistoryArraySize; // Size of the control history array in Y-space
    volatile uint16_t ErrorHistoryArraySize; // Size of the error history array in Y-space

    // Feedback scaling Input/Output Normalization
    volatile int16_t normPreShift; // Normalization of ADC-resolution to Q15 (R/W)
    volatile int16_t normPostShiftA; // Normalization of A-term control output to Q15 (R/W)
    volatile int16_t normPostShiftB; // Normalization of B-term control output to Q15 (R/W)
    volatile int16_t normPostScaler; // Control output normalization factor (Q15) (R/W)

    // Feedback conditioning
    volatile int16_t InputOffset; // Control input source offset value (R/W)

    // System clamping/Anti-windup
    volatile int16_t MinOutput; // Minimum output value used for clamping (R/W)
    volatile int16_t MaxOutput; // Maximum output value used for clamping (R/W)

    // Voltage/Average Current Mode Control Trigger handling
    volatile uint16_t* ptrADCTriggerRegister; // Pointer to ADC trigger register (e.g. TRIG1)
    volatile uint16_t ADCTriggerOffset; // ADC trigger offset to compensate propagation delays 
    
} __attribute__((packed))cNPNZ16b_t; // Generic nPnZ Controller Object


/* ***************************************************************************************/
#endif	// end of __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__ header file section
