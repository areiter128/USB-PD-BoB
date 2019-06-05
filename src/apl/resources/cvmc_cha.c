/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.58.
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

#include "../../apl/resources/cvmc_cha.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in cvmc_cha.h
 * ***************************************************************************************/

	volatile CVMC_CHA_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) cvmc_cha_coefficients; // A/B-Coefficients 
	volatile uint16_t cvmc_cha_ACoefficients_size = (sizeof(cvmc_cha_coefficients.ACoefficients)/sizeof(cvmc_cha_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t cvmc_cha_BCoefficients_size = (sizeof(cvmc_cha_coefficients.BCoefficients)/sizeof(cvmc_cha_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CVMC_CHA_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) cvmc_cha_histories; // Control/Error Histories 
	volatile uint16_t cvmc_cha_ControlHistory_size = (sizeof(cvmc_cha_histories.ControlHistory)/sizeof(cvmc_cha_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t cvmc_cha_ErrorHistory_size = (sizeof(cvmc_cha_histories.ErrorHistory)/sizeof(cvmc_cha_histories.ErrorHistory[0])); // Error history array size

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

	volatile fractional cvmc_cha_ACoefficients [3] = 
	{
		0x5A8C,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x2374,	// Coefficient A2 will be multiplied with controller output u(n-2)
		0x0202	// Coefficient A3 will be multiplied with controller output u(n-3)
	};

	volatile fractional cvmc_cha_BCoefficients [4] = 
	{
		0x7EB2,	// Coefficient B0 will be multiplied with error input e(n)
		0x90F2,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x81BF,	// Coefficient B2 will be multiplied with error input e(n-2)
		0x6F7F	// Coefficient B3 will be multiplied with error input e(n-3)
	};


	volatile int16_t cvmc_cha_pre_scaler = 3;
	volatile int16_t cvmc_cha_post_shift_A = 0;
	volatile int16_t cvmc_cha_post_shift_B = 0;
	volatile fractional cvmc_cha_post_scaler = 0x0000;

	volatile cNPNZ16b_t cvmc_cha; // user-controller data object

/* ***************************************************************************************/

uint16_t cvmc_cha_Init(void)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	cvmc_cha.status.flags = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	cvmc_cha.ptrACoefficients = &cvmc_cha_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	cvmc_cha.ptrBCoefficients = &cvmc_cha_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	cvmc_cha.ptrControlHistory = &cvmc_cha_histories.ControlHistory[0]; // initialize pointer to control history array
	cvmc_cha.ptrErrorHistory = &cvmc_cha_histories.ErrorHistory[0]; // initialize pointer to error history array
	cvmc_cha.normPostShiftA = cvmc_cha_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	cvmc_cha.normPostShiftB = cvmc_cha_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	cvmc_cha.normPostScaler = cvmc_cha_post_scaler; // initialize control output value normalization scaling factor
	cvmc_cha.normPreShift = cvmc_cha_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	cvmc_cha.ACoefficientsArraySize = cvmc_cha_ACoefficients_size; // initialize A-coefficients array size
	cvmc_cha.BCoefficientsArraySize = cvmc_cha_BCoefficients_size; // initialize A-coefficients array size
	cvmc_cha.ControlHistoryArraySize = cvmc_cha_ControlHistory_size; // initialize control history array size
	cvmc_cha.ErrorHistoryArraySize = cvmc_cha_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<cvmc_cha.ACoefficientsArraySize; i++)
	{
		cvmc_cha_coefficients.ACoefficients[i] = cvmc_cha_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<cvmc_cha.BCoefficientsArraySize; i++)
	{
		cvmc_cha_coefficients.BCoefficients[i] = cvmc_cha_BCoefficients[i];
	}

	// Clear error and control histories of the 3P3Z controller
	cvmc_cha_Reset(&cvmc_cha);

	return(1);
}


