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

#include "apl/resources/cha_vloop.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in cha_vloop.h
 * ***************************************************************************************/

	volatile CHA_VLOOP_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) cha_vloop_coefficients; // A/B-Coefficients 
	volatile uint16_t cha_vloop_ACoefficients_size = (sizeof(cha_vloop_coefficients.ACoefficients)/sizeof(cha_vloop_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t cha_vloop_BCoefficients_size = (sizeof(cha_vloop_coefficients.BCoefficients)/sizeof(cha_vloop_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CHA_VLOOP_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) cha_vloop_histories; // Control/Error Histories 
	volatile uint16_t cha_vloop_ControlHistory_size = (sizeof(cha_vloop_histories.ControlHistory)/sizeof(cha_vloop_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t cha_vloop_ErrorHistory_size = (sizeof(cha_vloop_histories.ErrorHistory)/sizeof(cha_vloop_histories.ErrorHistory[0])); // Error history array size

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

	volatile fractional cha_vloop_ACoefficients [3] = 
	{
		0x5A8C,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x2374,	// Coefficient A2 will be multiplied with controller output u(n-2)
		0x0202	// Coefficient A3 will be multiplied with controller output u(n-3)
	};

	volatile fractional cha_vloop_BCoefficients [4] = 
	{
		0x7EB2,	// Coefficient B0 will be multiplied with error input e(n)
		0x90F2,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x81BF,	// Coefficient B2 will be multiplied with error input e(n-2)
		0x6F7F	// Coefficient B3 will be multiplied with error input e(n-3)
	};


	volatile int16_t cha_vloop_pre_scaler = 3;
	volatile int16_t cha_vloop_post_shift_A = 0;
	volatile int16_t cha_vloop_post_shift_B = 0;
	volatile fractional cha_vloop_post_scaler = 0x0000;

	volatile cNPNZ16b_t cha_vloop; // user-controller data object

/* ***************************************************************************************/

volatile uint16_t cha_vloop_Init(volatile cNPNZ16b_t* controller)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	controller->status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	controller->ptrACoefficients = &cha_vloop_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	controller->ptrBCoefficients = &cha_vloop_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	controller->ptrControlHistory = &cha_vloop_histories.ControlHistory[0]; // initialize pointer to control history array
	controller->ptrErrorHistory = &cha_vloop_histories.ErrorHistory[0]; // initialize pointer to error history array
	controller->normPostShiftA = cha_vloop_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	controller->normPostShiftB = cha_vloop_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	controller->normPostScaler = cha_vloop_post_scaler; // initialize control output value normalization scaling factor
	controller->normPreShift = cha_vloop_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	controller->ACoefficientsArraySize = cha_vloop_ACoefficients_size; // initialize A-coefficients array size
	controller->BCoefficientsArraySize = cha_vloop_BCoefficients_size; // initialize A-coefficients array size
	controller->ControlHistoryArraySize = cha_vloop_ControlHistory_size; // initialize control history array size
	controller->ErrorHistoryArraySize = cha_vloop_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<controller->ACoefficientsArraySize; i++)
	{
		cha_vloop_coefficients.ACoefficients[i] = cha_vloop_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<controller->BCoefficientsArraySize; i++)
	{
		cha_vloop_coefficients.BCoefficients[i] = cha_vloop_BCoefficients[i];
	}

	// Clear error and control histories of the 3P3Z controller
	cha_vloop_Reset(&cha_vloop);

	return(1);
}


