/* ********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.0.77
 * ********************************************************************************
 * 2p2z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * ********************************************************************************
 *
 *  Controller Type:    2P2Z - Basic Current Mode Compensator
 *  Sampling Frequency: 175000 Hz
 *  Fixed Point Format: 15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         1
 *
 * *******************************************************************************
 * CGS Version:         1.0.0
 * CGS Date:            11/08/19
 * *******************************************************************************
 * User:                M91406
 * Date/Time:           12/21/2019 10:18:40 PM
 * *******************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__
#define __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__

#include <xc.h> // include processor files - each processor file is guarded
#include <dsp.h> // include DSP data types (e.g. fractional)
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

#include "../h/apl/resources/npnz16b.h" // include NPNZ library header file

/* *******************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error
 * history arrays. The pointer target objects (variables and arrays) are defined
 * in controller source file chb_iloop.c
 *
 * Type definitions for A- and B- coefficient arrays as well as error- and control
 * history arrays are aligned in memory using the 'packed' attribute for optimized
 * addressing during DSP computations. These aligned data structures need to be
 * placed in specific memory locations to allow direct X/Y-access from the DSP.
 * This X/Y-memory placement is covered by the declarations used in controller
 * source file chb_iloop.c
 * ******************************************************************************/
typedef struct
{
    volatile fractional ACoefficients[2]; // A-Coefficients
    volatile fractional BCoefficients[3]; // B-Coefficients
} __attribute__((packed)) CHB_ILOOP_CONTROL_LOOP_COEFFICIENTS_t;

typedef struct
{
    volatile fractional ControlHistory[2];  // Control History Array
    volatile fractional ErrorHistory[3];  // Error History Array
} __attribute__((packed)) CHB_ILOOP_CONTROL_LOOP_HISTORIES_t;


extern volatile cNPNZ16b_t chb_iloop; // user-controller data object

/* *******************************************************************************
 * Function call prototypes for initialization routines and control loops
 * ******************************************************************************/

// Initialization of chb_iloop controller object
extern volatile uint16_t chb_iloop_Init( // chb_iloop initialization function call
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Clears the 2P2Z controller output and error histories
extern void chb_iloop_Reset( // chb_iloop reset function call (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Loads user-defined values into 2P2Z controller output and error histories
extern void chb_iloop_Precharge( // chb_iloop history pre-charge function call (Assembly)
        volatile cNPNZ16b_t* controller, // Pointer to nPnZ data type object
        volatile fractional ctrl_input, // user-defined, constant error history value
        volatile fractional ctrl_output // user-defined, constant control output history value
    );

// Calls the chb_iloop controller object
extern void chb_iloop_Update( // Calls the 2P2Z controller (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );


#endif // end of __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__

//**********************************************************************************
//  https://areiter128.github.io/DCLD
//**********************************************************************************

