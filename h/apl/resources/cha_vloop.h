/* ********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.0.76
 * ********************************************************************************
 * 3p3z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * ********************************************************************************
 *
 *  Controller Type:    3P3Z - Basic Voltage Mode Compensator
 *  Sampling Frequency: 87500 Hz
 *  Fixed Point Format: 15
 *  Scaling Mode:       1 - Single Bit-Shift Scaling
 *  Input Gain:         0.2
 *
 * *******************************************************************************
 * CGS Version:         1.0.0
 * CGS Date:            11/08/19
 * *******************************************************************************
 * User:                C14220
 * Date/Time:           11/12/2019 10:10:29 AM
 * *******************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__
#define __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__

#include <xc.h> // include processor files - each processor file is guarded
#include <dsp.h> // include DSP data types (e.g. fractional)
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

#include "../h/apl/resources/npnz16b.h" // include NPNZ library header file

/* *******************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error
 * history arrays. The pointer target objects (variables and arrays) are defined
 * in controller source file cha_vloop.c
 *
 * Type definitions for A- and B- coefficient arrays as well as error- and control
 * history arrays are aligned in memory using the 'packed' attribute for optimized
 * addressing during DSP computations. These aligned data structures need to be
 * placed in specific memory locations to allow direct X/Y-access from the DSP.
 * This X/Y-memory placement is covered by the declarations used in controller
 * source file cha_vloop.c
 * ******************************************************************************/
typedef struct
{
    volatile fractional ACoefficients[3]; // A-Coefficients
    volatile fractional BCoefficients[4]; // B-Coefficients
} __attribute__((packed)) CHA_VLOOP_CONTROL_LOOP_COEFFICIENTS_t;

typedef struct
{
    volatile fractional ControlHistory[3];  // Control History Array
    volatile fractional ErrorHistory[4];  // Error History Array
} __attribute__((packed)) CHA_VLOOP_CONTROL_LOOP_HISTORIES_t;


extern volatile cNPNZ16b_t cha_vloop; // user-controller data object

/* *******************************************************************************
 * Function call prototypes for initialization routines and control loops
 * ******************************************************************************/

// Initialization of cha_vloop controller object
extern volatile uint16_t cha_vloop_Init( // cha_vloop initialization function call
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Clears the 3P3Z controller output and error histories
extern void cha_vloop_Reset( // cha_vloop reset function call (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Loads user-defined values into 3P3Z controller output and error histories
extern void cha_vloop_Precharge( // cha_vloop history pre-charge function call (Assembly)
        volatile cNPNZ16b_t* controller, // Pointer to nPnZ data type object
        volatile fractional ctrl_input, // user-defined, constant error history value
        volatile fractional ctrl_output // user-defined, constant control output history value
    );

// Calls the cha_vloop controller object
extern void cha_vloop_Update( // Calls the 3P3Z controller (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );


#endif // end of __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__
 
