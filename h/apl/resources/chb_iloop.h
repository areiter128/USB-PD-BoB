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

#ifndef __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__
#define __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__

#include <xc.h>
#include <dsp.h>
#include <stdint.h>

#include "../../apl/resources/npnz16b.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains a pointer to derived coefficients in X-space and
 * other pointers to controller and error history in Y-space.
 * This header file holds public declarations for variables and arrays defined in 
 * chb_iloop.c
 * 
 * Type definition for A- and B- coefficient arrays and error- and control-history arrays, 
 * which are aligned in memory for optimized addressing during DSP computations.           
 * These data structures need to be placed in specific memory locations to allow direct    
 * X/Y-access from the DSP. (coefficients in x-space, histories in y-space)                
 * ***************************************************************************************/

	typedef struct
	{
		volatile fractional ACoefficients[2]; // A-Coefficients
		volatile fractional BCoefficients[3]; // B-Coefficients
	} __attribute__((packed))CHB_ILOOP_CONTROL_LOOP_COEFFICIENTS_t;

	typedef struct
	{
		volatile fractional ControlHistory[2];  // Control History
		volatile fractional ErrorHistory[3];    // Error History
	} __attribute__((packed))CHB_ILOOP_CONTROL_LOOP_HISTORIES_t;


	extern volatile cNPNZ16b_t chb_iloop; // user-controller data object

/* ***************************************************************************************/

// Function call prototypes for initialization routines and control loops

extern volatile uint16_t chb_iloop_Init( // Loads default coefficients into 2P2Z controller and resets histories to zero
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void chb_iloop_Reset( // Resets the 2P2Z controller histories
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void chb_iloop_Precharge( // Pre-charges histories of the 2P2Z with defined steady-state data
	volatile cNPNZ16b_t* controller, // Pointer to nPnZ data structure
	volatile uint16_t ctrl_input, // user-defined, constant error history value
	volatile uint16_t ctrl_output // user-defined, constant control output history value
	);

extern void chb_iloop_Update( // Calls the 2P2Z controller
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

#endif	// end of __SPECIAL_FUNCTION_LAYER_CHB_ILOOP_H__ header file section
