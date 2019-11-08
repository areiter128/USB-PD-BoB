/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.72.
 * ***************************************************************************************
 * 3p3z compensation filter coefficients derived for following operating conditions:
 * ***************************************************************************************
 *
 * 	Controller Type:	3P3Z - Basic Voltage Mode Compensator
 * 	Sampling Frequency:	350000 Hz 
 * 	Fixed Point Format:	15
 * 	Scaling Mode:		1 - Single Bit-Shift Scaling
 * 	Input Gain:			0.2
 * 
 * ***************************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__
#define __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__

#include <xc.h>
#include <dsp.h>
#include <stdint.h>

#include "../h/apl/resources/npnz16b.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error history 
 * arrays. The pointer target objects (variables and arrays) are defined in               
 * cha_vloop.c
 * This header file holds the public declarations for these variables and arrays.         
 * 
 * Type definitions for A- and B- coefficient arrays as well as error- and control history
 * arrays are aligned in memory using the 'packed' attribute for optimized addressing     
 * during DSP computations. These aligned data structures need to be placed in specific   
 * memory locations to allow direct X/Y-access from the DSP. This X/Y-memory placement is 
 * covered by the declarations used in cha_vloop.c               
 * ***************************************************************************************/

	typedef struct
	{
		volatile fractional ACoefficients[3]; // A-Coefficients
		volatile fractional BCoefficients[4]; // B-Coefficients
	} __attribute__((packed))CHA_VLOOP_CONTROL_LOOP_COEFFICIENTS_t;

	typedef struct
	{
		volatile fractional ControlHistory[3];  // Control History
		volatile fractional ErrorHistory[4];    // Error History
	} __attribute__((packed))CHA_VLOOP_CONTROL_LOOP_HISTORIES_t;


	extern volatile cNPNZ16b_t cha_vloop; // user-controller data object

/* ***************************************************************************************/

// Function call prototypes for initialization routines and control loops

extern volatile uint16_t cha_vloop_Init( // Loads default coefficients into 3P3Z controller and resets histories to zero
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void cha_vloop_Reset( // Resets the 3P3Z controller histories
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void cha_vloop_Precharge( // Pre-charges histories of the 3P3Z with defined steady-state data
	volatile cNPNZ16b_t* controller, // Pointer to nPnZ data structure
	volatile uint16_t ctrl_input, // user-defined, constant error history value
	volatile uint16_t ctrl_output // user-defined, constant control output history value
	);

extern void cha_vloop_Update( // Calls the 3P3Z controller
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

#endif	// end of __SPECIAL_FUNCTION_LAYER_CHA_VLOOP_H__ header file section
