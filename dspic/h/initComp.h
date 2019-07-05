/*******************************************************************************
Microchip's products.  Microchip and its licensors retain all ownership and
intellectual property rights in the accompanying software and in all
derivatives here to.

This software and any accompanying information is for suggestion only. It
does not modify Microchip's standard warranty for its products. You agree
that you are solely responsible for testing the software and determining its
suitability. Microchip has no obligation to modify, test, certify, or
support the software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS,
COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT
(INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY,
INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
THESE TERMS.
*******************************************************************************/
#ifndef INIT_COMPENSATOR_H
#define INIT_COMPENSATOR_H

#include "stdint.h"
#include "smps_control.h"
                
typedef struct
{
	volatile int16_t *  		ptrReference;
	volatile int16_t *   	    ptrFeedback;
	volatile int16_t * 		    ptrControlOutput;
	volatile int16_t *  		ptrResultacc;
	int16_t            			postScaler;
	int16_t                 	postShift;
    SMPS_Controller_Options_T*	triggerOpt;
    int16_t *           	    ptrABCoefficients;
    int16_t *                   ptrCntrlErrorHys;
	int16_t	  					minClamp;
	int16_t   					maxClamp;
}
COMPENSATOR_STATE;

typedef struct
{
    int16_t                     postScaler;
	int16_t                     postShift;
    int16_t                     ABCoefficients[9];
}
__attribute__ ((space(xmemory))) COMPENSATOR_ALT_CONFIG_OPT;


// Main function that will initialize the controllers
void COMPENSATOR_Initialize(void);       

// Setup context register set: W-reg context to use, address of structure for 
// state data, and compensator type to initialize (1-cascaded, 0-traditional)
void COMPENSATOR_AltWregInitialize(uint16_t regSet, const COMPENSATOR_STATE *compState, uint16_t controlType);            	

// Function that clears the data arrays associated with controller
void COMPENSATOR_ClearArrays(const COMPENSATOR_STATE *compState, uint16_t errorCntHyst);

// Function to support adaptive gain control, or just multiple banks of coefficients
void COMPENSATOR_UpdateParameters(uint16_t regSet, const COMPENSATOR_ALT_CONFIG_OPT *compState);


// Decide which type of controller to use
#define BUCK_CASCADED
//#define BOOST_CASCADED


#endif
