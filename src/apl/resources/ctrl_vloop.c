/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.61.
 * ***************************************************************************************
 * 3p3z compensation filter coefficients derived for following operating conditions:
 * ***************************************************************************************
 *
 * 	Controller Type:	3P3Z - Basic Voltage Mode Compensator
 * 	Sampling Frequency:	300000 Hz 
 * 	Fixed Point Format:	15
 * 	Scaling Mode:		1 - Single Bit-Shift Scaling
 * 	Input Gain:			0.2
 * 
 * ***************************************************************************************/

#include "apl/resources/ctrl_vloop.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in ctrl_vloop.h
 * ***************************************************************************************/

	volatile CTRL_VLOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) ctrl_vloop_coefficients; // A/B-Coefficients 
	volatile uint16_t ctrl_vloop_ACoefficients_size = (sizeof(ctrl_vloop_coefficients.ACoefficients)/sizeof(ctrl_vloop_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t ctrl_vloop_BCoefficients_size = (sizeof(ctrl_vloop_coefficients.BCoefficients)/sizeof(ctrl_vloop_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CTRL_VLOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) ctrl_vloop_histories; // Control/Error Histories 
	volatile uint16_t ctrl_vloop_ControlHistory_size = (sizeof(ctrl_vloop_histories.ControlHistory)/sizeof(ctrl_vloop_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t ctrl_vloop_ErrorHistory_size = (sizeof(ctrl_vloop_histories.ErrorHistory)/sizeof(ctrl_vloop_histories.ErrorHistory[0])); // Error history array size

/* ***************************************************************************************
 * 	Pole&Zero Placement:
 * ***************************************************************************************
 *
 * 	fP0:	50 Hz 
 * 	fP1:	110000 Hz 
 * 	fZ1:	2100 Hz 
 * 	fP2:	150000 Hz 
 * 	fZ2:	4000 Hz 
 *
 * ***************************************************************************************
 * 	Filter Coefficients and Parameters:
 * ***************************************************************************************/

	volatile fractional ctrl_vloop_ACoefficients [3] = 
	{
		0x5A8C,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x2374,	// Coefficient A2 will be multiplied with controller output u(n-2)
		0x0202	// Coefficient A3 will be multiplied with controller output u(n-3)
	};

	volatile fractional ctrl_vloop_BCoefficients [4] = 
	{
		0x7EB2,	// Coefficient B0 will be multiplied with error input e(n)
		0x90F2,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x81BF,	// Coefficient B2 will be multiplied with error input e(n-2)
		0x6F7F	// Coefficient B3 will be multiplied with error input e(n-3)
	};


	volatile int16_t ctrl_vloop_pre_scaler = 3;
	volatile int16_t ctrl_vloop_post_shift_A = 0;
	volatile int16_t ctrl_vloop_post_shift_B = 0;
	volatile fractional ctrl_vloop_post_scaler = 0x0000;

	volatile cNPNZ16b_t ctrl_vloop; // user-controller data object

/* ***************************************************************************************/

uint16_t ctrl_vloop_Init(void)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	ctrl_vloop.status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	ctrl_vloop.ptrACoefficients = &ctrl_vloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	ctrl_vloop.ptrBCoefficients = &ctrl_vloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	ctrl_vloop.ptrControlHistory = &ctrl_vloop_histories.ControlHistory[0]; // initialize pointer to control history array
	ctrl_vloop.ptrErrorHistory = &ctrl_vloop_histories.ErrorHistory[0]; // initialize pointer to error history array
	ctrl_vloop.normPostShiftA = ctrl_vloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	ctrl_vloop.normPostShiftB = ctrl_vloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	ctrl_vloop.normPostScaler = ctrl_vloop_post_scaler; // initialize control output value normalization scaling factor
	ctrl_vloop.normPreShift = ctrl_vloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	ctrl_vloop.ACoefficientsArraySize = ctrl_vloop_ACoefficients_size; // initialize A-coefficients array size
	ctrl_vloop.BCoefficientsArraySize = ctrl_vloop_BCoefficients_size; // initialize A-coefficients array size
	ctrl_vloop.ControlHistoryArraySize = ctrl_vloop_ControlHistory_size; // initialize control history array size
	ctrl_vloop.ErrorHistoryArraySize = ctrl_vloop_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<ctrl_vloop.ACoefficientsArraySize; i++)
	{
		ctrl_vloop_coefficients.ACoefficients[i] = ctrl_vloop_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<ctrl_vloop.BCoefficientsArraySize; i++)
	{
		ctrl_vloop_coefficients.BCoefficients[i] = ctrl_vloop_BCoefficients[i];
	}

	// Clear error and control histories of the 3P3Z controller
	ctrl_vloop_Reset(&ctrl_vloop);

	return(1);
}


