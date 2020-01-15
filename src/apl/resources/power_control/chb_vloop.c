/* **********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.1.80
 * **********************************************************************************
 * 2p2z compensation filter coefficients derived for following operating
 * conditions:
 * **********************************************************************************
 *
 *  Controller Type:    2P2Z - Basic Current Mode Compensator
 *  Sampling Frequency: 87500 Hz
 *  Fixed Point Format: 15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         0.2
 *
 * *********************************************************************************
 * CGS Version:         1.1.5
 * CGS Date:            01/13/2020
 * *********************************************************************************
 * User:                M91406
 * Date/Time:           01/15/2020 1:48:16 PM
 * ********************************************************************************/

#include "../h/apl/resources/power_control/chb_vloop.h"

/* *********************************************************************************
 * Data Arrays:
 * This source file declares the default parameters of the z-domain compensation
 * filter. The cNPNZ_t data structure contains two pointers to A- and B-
 * coefficient arrays and two pointers to control and error history arrays.
 *
 * For optimized data processing during DSP computations, these arrays must be
 * located in specific memory locations (X-space for coefficient arrays and
 * Y-space for control and error history arrays).
 *
 * The following declarations are used to define the array data contents, their
 * length and memory location. These declarations are made publicly accessible
 * through defines in source file chb_vloop.c
 * ********************************************************************************/

volatile CHB_VLOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) chb_vloop_coefficients; // A/B-Coefficients
volatile uint16_t chb_vloop_ACoefficients_size = (sizeof(chb_vloop_coefficients.ACoefficients)/sizeof(chb_vloop_coefficients.ACoefficients[0])); // A-coefficient array size
volatile uint16_t chb_vloop_BCoefficients_size = (sizeof(chb_vloop_coefficients.BCoefficients)/sizeof(chb_vloop_coefficients.BCoefficients[0])); // B-coefficient array size

volatile CHB_VLOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) chb_vloop_histories; // Control/Error Histories
volatile uint16_t chb_vloop_ControlHistory_size = (sizeof(chb_vloop_histories.ControlHistory)/sizeof(chb_vloop_histories.ControlHistory[0])); // Control history array size
volatile uint16_t chb_vloop_ErrorHistory_size = (sizeof(chb_vloop_histories.ErrorHistory)/sizeof(chb_vloop_histories.ErrorHistory[0])); // Error history array size

/* *********************************************************************************
 * Pole&Zero Placement:
 * *********************************************************************************
 *
 *    fP0:    40 Hz
 *    fP1:    40000 Hz
 *    fZ1:    450 Hz
 *
 * *********************************************************************************
 * Filter Coefficients and Parameters:
 * ********************************************************************************/
volatile fractional chb_vloop_ACoefficients [2] =
{
    0x6916, // Coefficient A1 will be multiplied with controller output u(n-1)
    0x16EB  // Coefficient A2 will be multiplied with controller output u(n-2)
};

volatile fractional chb_vloop_BCoefficients [3] =
{
    0x4429, // Coefficient B0 will be multiplied with error input e(n-0)
    0x022B, // Coefficient B1 will be multiplied with error input e(n-1)
    0xBE03  // Coefficient B2 will be multiplied with error input e(n-2)
};

// Coefficient normalization factors
volatile int16_t chb_vloop_pre_scaler = 3;
volatile int16_t chb_vloop_post_shift_A = 0;
volatile int16_t chb_vloop_post_shift_B = 1;
volatile fractional chb_vloop_post_scaler = 0x0000;

volatile cNPNZ16b_t chb_vloop; // user-controller data object

/* ********************************************************************************/

/*!chb_vloop_Init()
 * *********************************************************************************
 * Summary: Initializes controller coefficient arrays and normalization
 *
 * Parameters:
 *     - cNPNZ16b_t* controller
 *
 * Returns:
 *     - uint16_t:  0->failure
 *                  1->success

 * Description:
 * This function needs to be called from user code once to initialize coefficient
 * arrays and number normalization settings of the chb_vloop controller
 * object.
 *
 * PLEASE NOTE:
 * This routine DOES NOT initialize the complete controller object.
 * User-defined settings such as pointers to the control reference, source and
 * target registers, output minima and maxima and further, design-dependent
 * settings, need to be specified in user code.
 * ********************************************************************************/
volatile uint16_t chb_vloop_Init(volatile cNPNZ16b_t* controller)
{
    volatile uint16_t i=0;

    // Initialize controller data structure at runtime with pre-defined default values
    controller->status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))
    
    controller->ptrACoefficients = &chb_vloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
    controller->ptrBCoefficients = &chb_vloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
    controller->ptrControlHistory = &chb_vloop_histories.ControlHistory[0]; // initialize pointer to control history array
    controller->ptrErrorHistory = &chb_vloop_histories.ErrorHistory[0]; // initialize pointer to error history array
    controller->normPostShiftA = chb_vloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
    controller->normPostShiftB = chb_vloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
    controller->normPostScaler = chb_vloop_post_scaler; // initialize control output value normalization scaling factor
    controller->normPreShift = chb_vloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler
    
    controller->ACoefficientsArraySize = chb_vloop_ACoefficients_size; // initialize A-coefficients array size
    controller->BCoefficientsArraySize = chb_vloop_BCoefficients_size; // initialize A-coefficients array size
    controller->ControlHistoryArraySize = chb_vloop_ControlHistory_size; // initialize control history array size
    controller->ErrorHistoryArraySize = chb_vloop_ErrorHistory_size; // initialize error history array size
    
    
    // Load default set of A-coefficients from user RAM into X-Space controller A-array
    for(i=0; i<controller->ACoefficientsArraySize; i++)
    {
        chb_vloop_coefficients.ACoefficients[i] = chb_vloop_ACoefficients[i];
    }

    // Load default set of B-coefficients from user RAM into X-Space controller B-array
    for(i=0; i<controller->BCoefficientsArraySize; i++)
    {
        chb_vloop_coefficients.BCoefficients[i] = chb_vloop_BCoefficients[i];
    }

    // Clear error and control histories of the 3P3Z controller
    chb_vloop_Reset(&chb_vloop);
    
    return(1);
}
 
//**********************************************************************************
// Download latest version of this tool here: https://areiter128.github.io/DCLD
//**********************************************************************************
 
