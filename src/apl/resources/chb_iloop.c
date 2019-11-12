/* **********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.0.76
 * **********************************************************************************
 * 2p2z compensation filter coefficients derived for following operating
 * conditions:
 * **********************************************************************************
 *
 *  Controller Type:    2P2Z - Basic Current Mode Compensator
 *  Sampling Frequency: 87500 Hz
 *  Fixed Point Format: 15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         1
 *
 * *********************************************************************************
 * CGS Version:         1.0.0
 * CGS Date:            11/08/19
 * *********************************************************************************
 * User:                C14220
 * Date/Time:           11/12/2019 10:10:40 AM
 * ********************************************************************************/

#include "../h/apl/resources/chb_iloop.h"

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
 * through defines in source file chb_iloop.c
 * ********************************************************************************/

volatile CHB_ILOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) chb_iloop_coefficients; // A/B-Coefficients
volatile uint16_t chb_iloop_ACoefficients_size = (sizeof(chb_iloop_coefficients.ACoefficients)/sizeof(chb_iloop_coefficients.ACoefficients[0])); // A-coefficient array size
volatile uint16_t chb_iloop_BCoefficients_size = (sizeof(chb_iloop_coefficients.BCoefficients)/sizeof(chb_iloop_coefficients.BCoefficients[0])); // B-coefficient array size

volatile CHB_ILOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) chb_iloop_histories; // Control/Error Histories
volatile uint16_t chb_iloop_ControlHistory_size = (sizeof(chb_iloop_histories.ControlHistory)/sizeof(chb_iloop_histories.ControlHistory[0])); // Control history array size
volatile uint16_t chb_iloop_ErrorHistory_size = (sizeof(chb_iloop_histories.ErrorHistory)/sizeof(chb_iloop_histories.ErrorHistory[0])); // Error history array size

/* *********************************************************************************
 * 	Pole&Zero Placement:
 * *********************************************************************************
 *
 *    fP0:    400 Hz
 *    fP1:    140000 Hz
 *    fZ1:    4700 Hz
 *
 * *********************************************************************************
 * 	Filter Coefficients and Parameters:
 * ********************************************************************************/
volatile fractional chb_iloop_ACoefficients [2] =
{
    0x2A7B, // Coefficient A1 will be multiplied with controller output u(n-1)
    0x5586  // Coefficient A2 will be multiplied with controller output u(n-2)
};

volatile fractional chb_iloop_BCoefficients [3] =
{
    0x54F5, // Coefficient B0 will be multiplied with error input e(n-0)
    0x1889, // Coefficient B1 will be multiplied with error input e(n-1)
    0xC394  // Coefficient B2 will be multiplied with error input e(n-2)
};

// Coefficient normalization factors
volatile int16_t chb_iloop_pre_scaler = 3;
volatile int16_t chb_iloop_post_shift_A = 0;
volatile int16_t chb_iloop_post_shift_B = 3;
volatile fractional chb_iloop_post_scaler = 0x0000;

volatile cNPNZ16b_t chb_iloop; // user-controller data object

/* ********************************************************************************/

/*!chb_iloop_Init()
 * *********************************************************************************
 * Summary: Initializes controller coefficient arrays and normalization
 *
 * Parameters:
 *     - cNPNZ16b_t* controller
 *
 * Returns:
 *     - uint16_t:  0=failure, 1=success
 *
 * Description:
 * This function needs to be called from user code once to initialize coefficient
 * arrays and number normalization settings of the chb_iloop controller
 * object.
 *
 * PLEASE NOTE:
 * This routine DOES NOT initialize the complete controller object.
 * User-defined settings such as pointers to the control reference, source and
 * target registers, output minima and maxima and further, design-dependent
 * settings, need to be specified in user code.
 * ********************************************************************************/
volatile uint16_t chb_iloop_Init(volatile cNPNZ16b_t* controller)
{
    volatile uint16_t i = 0;

    // Initialize controller data structure at runtime with pre-defined default values
    controller->status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))
    
    controller->ptrACoefficients = &chb_iloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
    controller->ptrBCoefficients = &chb_iloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
    controller->ptrControlHistory = &chb_iloop_histories.ControlHistory[0]; // initialize pointer to control history array
    controller->ptrErrorHistory = &chb_iloop_histories.ErrorHistory[0]; // initialize pointer to error history array
    controller->normPostShiftA = chb_iloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
    controller->normPostShiftB = chb_iloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
    controller->normPostScaler = chb_iloop_post_scaler; // initialize control output value normalization scaling factor
    controller->normPreShift = chb_iloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler
    
    controller->ACoefficientsArraySize = chb_iloop_ACoefficients_size; // initialize A-coefficients array size
    controller->BCoefficientsArraySize = chb_iloop_BCoefficients_size; // initialize A-coefficients array size
    controller->ControlHistoryArraySize = chb_iloop_ControlHistory_size; // initialize control history array size
    controller->ErrorHistoryArraySize = chb_iloop_ErrorHistory_size; // initialize error history array size
    
    
    // Load default set of A-coefficients from user RAM into X-Space controller A-array
    for(i=0; i<controller->ACoefficientsArraySize; i++)
    {
        chb_iloop_coefficients.ACoefficients[i] = chb_iloop_ACoefficients[i];
    }

    // Load default set of B-coefficients from user RAM into X-Space controller B-array
    for(i=0; i<controller->BCoefficientsArraySize; i++)
    {
        chb_iloop_coefficients.BCoefficients[i] = chb_iloop_BCoefficients[i];
    }

    // Clear error and control histories of the 3P3Z controller
    chb_iloop_Reset(&chb_iloop);
    
    return(1);
}
 
