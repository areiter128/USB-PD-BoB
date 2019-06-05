/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.58.
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

#include "../../apl/resources/cacmc_bata.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This source file declares the default parameters of the z-domain compensation filter.
 * These declarations are made publicly accessible through defines in cacmc_bata.h
 * ***************************************************************************************/

	volatile CACMC_BATA_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) cacmc_bata_coefficients; // A/B-Coefficients 
	volatile uint16_t cacmc_bata_ACoefficients_size = (sizeof(cacmc_bata_coefficients.ACoefficients)/sizeof(cacmc_bata_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t cacmc_bata_BCoefficients_size = (sizeof(cacmc_bata_coefficients.BCoefficients)/sizeof(cacmc_bata_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile CACMC_BATA_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) cacmc_bata_histories; // Control/Error Histories 
	volatile uint16_t cacmc_bata_ControlHistory_size = (sizeof(cacmc_bata_histories.ControlHistory)/sizeof(cacmc_bata_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t cacmc_bata_ErrorHistory_size = (sizeof(cacmc_bata_histories.ErrorHistory)/sizeof(cacmc_bata_histories.ErrorHistory[0])); // Error history array size

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

	volatile fractional cacmc_bata_ACoefficients [2] = 
	{
		0x67D0,	// Coefficient A1 will be multiplied with controller output u(n-1)
		0x1831	// Coefficient A2 will be multiplied with controller output u(n-2)
	};

	volatile fractional cacmc_bata_BCoefficients [3] = 
	{
		0x6CB9,	// Coefficient B0 will be multiplied with error input e(n)
		0x0A34,	// Coefficient B1 will be multiplied with error input e(n-1)
		0x9D7B	// Coefficient B2 will be multiplied with error input e(n-2)
	};


	volatile int16_t cacmc_bata_pre_scaler = 3;
	volatile int16_t cacmc_bata_post_shift_A = 0;
	volatile int16_t cacmc_bata_post_shift_B = 4;
	volatile fractional cacmc_bata_post_scaler = 0x0000;

	volatile cNPNZ16b_t cacmc_bata; // user-controller data object

/* ***************************************************************************************/

uint16_t cacmc_bata_Init(void)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	cacmc_bata.status.flags = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	cacmc_bata.ptrACoefficients = &cacmc_bata_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	cacmc_bata.ptrBCoefficients = &cacmc_bata_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	cacmc_bata.ptrControlHistory = &cacmc_bata_histories.ControlHistory[0]; // initialize pointer to control history array
	cacmc_bata.ptrErrorHistory = &cacmc_bata_histories.ErrorHistory[0]; // initialize pointer to error history array
	cacmc_bata.normPostShiftA = cacmc_bata_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	cacmc_bata.normPostShiftB = cacmc_bata_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	cacmc_bata.normPostScaler = cacmc_bata_post_scaler; // initialize control output value normalization scaling factor
	cacmc_bata.normPreShift = cacmc_bata_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	cacmc_bata.ACoefficientsArraySize = cacmc_bata_ACoefficients_size; // initialize A-coefficients array size
	cacmc_bata.BCoefficientsArraySize = cacmc_bata_BCoefficients_size; // initialize A-coefficients array size
	cacmc_bata.ControlHistoryArraySize = cacmc_bata_ControlHistory_size; // initialize control history array size
	cacmc_bata.ErrorHistoryArraySize = cacmc_bata_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<cacmc_bata.ACoefficientsArraySize; i++)
	{
		cacmc_bata_coefficients.ACoefficients[i] = cacmc_bata_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<cacmc_bata.BCoefficientsArraySize; i++)
	{
		cacmc_bata_coefficients.BCoefficients[i] = cacmc_bata_BCoefficients[i];
	}

	// Clear error and control histories of the 2P2Z controller
	cacmc_bata_Reset(&cacmc_bata);

	return(1);
}


