/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.61.
 * ***************************************************************************************
 * 2p2z compensation filter coefficients derived for following operating conditions:
 * ***************************************************************************************
 *
 * 	Controller Type:	2P2Z - Basic Current Mode Compensator
 * 	Sampling Frequency:	300000 Hz 
 * 	Fixed Point Format:	15
 * 	Scaling Mode:		3 - Dual Bit-Shift Scaling
 * 	Input Gain:			1
 * 
 * ***************************************************************************************/

#include "apl/resources/chb_iloop.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in chb_iloop.h
 * ***************************************************************************************/

	volatile CHB_ILOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) chb_iloop_coefficients; // A/B-Coefficients 
	volatile uint16_t chb_iloop_ACoefficients_size = (sizeof(chb_iloop_coefficients.ACoefficients)/sizeof(chb_iloop_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t chb_iloop_BCoefficients_size = (sizeof(chb_iloop_coefficients.BCoefficients)/sizeof(chb_iloop_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CHB_ILOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) chb_iloop_histories; // Control/Error Histories 
	volatile uint16_t chb_iloop_ControlHistory_size = (sizeof(chb_iloop_histories.ControlHistory)/sizeof(chb_iloop_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t chb_iloop_ErrorHistory_size = (sizeof(chb_iloop_histories.ErrorHistory)/sizeof(chb_iloop_histories.ErrorHistory[0])); // Error history array size

/* ***************************************************************************************
 * 	Pole&Zero Placement:
 * ***************************************************************************************
 *
 * 	fP0:	400 Hz 
 * 	fP1:	140000 Hz 
 * 	fZ1:	4700 Hz 
 *
 * ***************************************************************************************
 * 	Filter Coefficients and Parameters:
 * ***************************************************************************************/

	volatile fractional chb_iloop_ACoefficients [2] = 
	{
		0x67D0,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x1831	// Coefficient A2 will be multiplied with controller output u(n-2)
	};

	volatile fractional chb_iloop_BCoefficients [3] = 
	{
		0x6CB9,	// Coefficient B0 will be multiplied with error input e(n)
		0x0A34,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x9D7B	// Coefficient B2 will be multiplied with error input e(n-2)
	};


	volatile int16_t chb_iloop_pre_scaler = 3;
	volatile int16_t chb_iloop_post_shift_A = 0;
	volatile int16_t chb_iloop_post_shift_B = 4;
	volatile fractional chb_iloop_post_scaler = 0x0000;

	volatile cNPNZ16b_t chb_iloop; // user-controller data object

/* ***************************************************************************************/

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

	// Clear error and control histories of the 2P2Z controller
	chb_iloop_Reset(&chb_iloop);

	return(1);
}

