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

#include "../../apl/resources/ctrl_iloop.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in ctrl_iloop.h
 * ***************************************************************************************/

	volatile CTRL_ILOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) ctrl_iloop_coefficients; // A/B-Coefficients 
	volatile uint16_t ctrl_iloop_ACoefficients_size = (sizeof(ctrl_iloop_coefficients.ACoefficients)/sizeof(ctrl_iloop_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t ctrl_iloop_BCoefficients_size = (sizeof(ctrl_iloop_coefficients.BCoefficients)/sizeof(ctrl_iloop_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CTRL_ILOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) ctrl_iloop_histories; // Control/Error Histories 
	volatile uint16_t ctrl_iloop_ControlHistory_size = (sizeof(ctrl_iloop_histories.ControlHistory)/sizeof(ctrl_iloop_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t ctrl_iloop_ErrorHistory_size = (sizeof(ctrl_iloop_histories.ErrorHistory)/sizeof(ctrl_iloop_histories.ErrorHistory[0])); // Error history array size

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

	volatile fractional ctrl_iloop_ACoefficients [2] = 
	{
		0x67D0,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x1831	// Coefficient A2 will be multiplied with controller output u(n-2)
	};

	volatile fractional ctrl_iloop_BCoefficients [3] = 
	{
		0x6CB9,	// Coefficient B0 will be multiplied with error input e(n)
		0x0A34,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x9D7B	// Coefficient B2 will be multiplied with error input e(n-2)
	};


	volatile int16_t ctrl_iloop_pre_scaler = 3;
	volatile int16_t ctrl_iloop_post_shift_A = 0;
	volatile int16_t ctrl_iloop_post_shift_B = 4;
	volatile fractional ctrl_iloop_post_scaler = 0x0000;

	volatile cNPNZ16b_t ctrl_iloop; // user-controller data object

/* ***************************************************************************************/

uint16_t ctrl_iloop_Init(void)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	ctrl_iloop.status.flags = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	ctrl_iloop.ptrACoefficients = &ctrl_iloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	ctrl_iloop.ptrBCoefficients = &ctrl_iloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	ctrl_iloop.ptrControlHistory = &ctrl_iloop_histories.ControlHistory[0]; // initialize pointer to control history array
	ctrl_iloop.ptrErrorHistory = &ctrl_iloop_histories.ErrorHistory[0]; // initialize pointer to error history array
	ctrl_iloop.normPostShiftA = ctrl_iloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	ctrl_iloop.normPostShiftB = ctrl_iloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	ctrl_iloop.normPostScaler = ctrl_iloop_post_scaler; // initialize control output value normalization scaling factor
	ctrl_iloop.normPreShift = ctrl_iloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	ctrl_iloop.ACoefficientsArraySize = ctrl_iloop_ACoefficients_size; // initialize A-coefficients array size
	ctrl_iloop.BCoefficientsArraySize = ctrl_iloop_BCoefficients_size; // initialize A-coefficients array size
	ctrl_iloop.ControlHistoryArraySize = ctrl_iloop_ControlHistory_size; // initialize control history array size
	ctrl_iloop.ErrorHistoryArraySize = ctrl_iloop_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<ctrl_iloop.ACoefficientsArraySize; i++)
	{
		ctrl_iloop_coefficients.ACoefficients[i] = ctrl_iloop_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<ctrl_iloop.BCoefficientsArraySize; i++)
	{
		ctrl_iloop_coefficients.BCoefficients[i] = ctrl_iloop_BCoefficients[i];
	}

	// Clear error and control histories of the 2P2Z controller
	ctrl_iloop_Reset(&ctrl_iloop);

	return(1);
}


