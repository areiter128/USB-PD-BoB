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
#include "initComp.h"
#include "../dcdt/buck/dcdt_generated_code/buck_dcdt.h"
#include "../dcdt/boost/dcdt_generated_code/boost_dcdt.h"
#include "buck_casc_coeff.h"

extern int16_t buckControlReference, boostControlReference;
extern uint16_t buckVoltage, boostVoltage;   

int16_t buckAccbResults[9], boostAccbResults[9];
int16_t buckErrorControlHistory[4] __attribute__ ((space (ymemory), far));
int16_t boostErrorControlHistory[4] __attribute__ ((space (ymemory), far));

// Decision for which type of controller to use is selectable in initComp.h

// Cascaded (B10,B11,A11,B20,B21,A21,B30,B31,A31)
// Other controllers (B0,B1..Bx,A1,A2..Ax)
#if defined (BUCK_CASCADED)
int16_t buckABCoefficients[9] __attribute__((space (xmemory))) = 
{
    BUCK_CASC_COEFF_B10,            // Cascaded (B10,B11,A11,B20,B21,A21,B30,B31,A31)
    BUCK_CASC_COEFF_B11,            // Other controllers (B0,B1..Bx,A1,A2..Ax)
    BUCK_CASC_COEFF_A11,

    BUCK_CASC_COEFF_B20,
    BUCK_CASC_COEFF_B21,
    BUCK_CASC_COEFF_A21,    
     
    BUCK_CASC_COEFF_B30,
    BUCK_CASC_COEFF_B31,
    BUCK_CASC_COEFF_A31
};      
#else
int16_t buckABCoefficients[5] __attribute__((space (xmemory))) = 
{
    BUCK_COMP_2P2Z_COEFF_B0,      
    BUCK_COMP_2P2Z_COEFF_B1,      
    BUCK_COMP_2P2Z_COEFF_B2,      

    BUCK_COMP_2P2Z_COEFF_A1,      
    BUCK_COMP_2P2Z_COEFF_A2      
};
#endif
 
#if defined (BOOST_CASCADED)
int16_t boostABCoefficients[9] __attribute__((space (xmemory))) = 
{
    BOOST_COEFF_B10,            // Cascaded (B10,B11,A11,B20,B21,A21,B30,B31,A31)
    BOOST_COEFF_B11,            // Other controllers (B0,B1..Bx,A1,A2..Ax)
    BOOST_COEFF_A11,

    BOOST_COEFF_B20,
    BOOST_COEFF_B21,
    BOOST_COEFF_A21,    
     
    BOOST_COEFF_B30,
    BOOST_COEFF_B31,
    BOOST_COEFF_A31
};      
#else
int16_t boostABCoefficients[5] __attribute__((space (xmemory))) = 
{
    BOOST_COMP_2P2Z_COEFF_B0,      
    BOOST_COMP_2P2Z_COEFF_B1,      
    BOOST_COMP_2P2Z_COEFF_B2,      

    BOOST_COMP_2P2Z_COEFF_A1,      
    BOOST_COMP_2P2Z_COEFF_A2      
};
#endif

// Not required
SMPS_Controller_Options_T buckTrigOpt =
{
    .triggerSelectFlag = 0,                     // Trigger opt. 0=Disable, 1=on-time, 2=off-time
    .delayValue = 0,                            // HW delays to be added to trigger
    .trigger = 0,                               // Target write back (&TRIG1)
    .period = 0,                                // For off-time control, what time base register to consider (i.e PTPER)
};
SMPS_Controller_Options_T boostTrigOpt =
{
    .triggerSelectFlag = 0,                     // Trigger opt. 0=Disable, 1=on-time, 2=off-time
    .delayValue = 0,                            // HW delays to be added to trigger
    .trigger = 0,                               // Target write back (&TRIG1)
    .period = 0,                                // For off-time control, what time base register to consider (i.e PTPER)
};

// Can be const or normal RAM structure (timing varies based on definition)
COMPENSATOR_STATE buckController = 
{
    .ptrReference = &buckControlReference,                                   // Address of control Reference variable for cascaded controller, other controller ref is passed in W0 
	.ptrFeedback =  (int16_t *) &ADCBUF13,                          // Target read data (feedback i.e. &ADCBUF)
	.ptrControlOutput = (int16_t *) &DAC1DATH,                        // Target write back pointer (&variable, &PDCx, &PTPER)
	.ptrResultacc = &buckAccbResults[0],                           // For cascaded, this points to 9-element array, else should be 0.
#if defined (BUCK_CASCADED)
	.postScaler = BUCK_CASC_POSTSCALER,                                 // Output Scale Factor for coeff normalization
	.postShift = BUCK_CASC_POSTSHIFT,                                   // Output Shift Factor for coeff normalization
#else
    .postScaler = BUCK_COMP_2P2Z_POSTSCALER,                                 // Output Scale Factor for coeff normalization
	.postShift = BUCK_COMP_2P2Z_POSTSHIFT,                                   // Output Shift Factor for coeff normalization
#endif
    .triggerOpt = &buckTrigOpt,
    .ptrABCoefficients = &buckABCoefficients[0],                   // Address of A/B Coefficients Array
    .ptrCntrlErrorHys = &buckErrorControlHistory[0],            // Address of Error/ControlHistory Array
#if defined (BUCK_CASCADED)
    .minClamp = BUCK_CASC_MIN_CLAMP,                                    // Compensator output minimum clamp value
	.maxClamp = BUCK_CASC_MAX_CLAMP,                                    // Compensator output maximum clamp value    
#else
    .minClamp = BUCK_COMP_2P2Z_MIN_CLAMP,                                    // Compensator output minimum clamp value
	.maxClamp = BUCK_COMP_2P2Z_MAX_CLAMP,                                    // Compensator output maximum clamp value 
#endif
    
};

COMPENSATOR_STATE boostController = 
{
    .ptrReference = &boostControlReference,                                   // Address of control Reference variable for cascaded controller, other controller ref is passed in W0 
	.ptrFeedback =  (int16_t *) &ADCBUF18,                          // Target read data (feedback i.e. &ADCBUF)
	.ptrControlOutput = (int16_t *) &DAC2DATH,                        // Target write back pointer (&variable, &PDCx, &PTPER)
	.ptrResultacc = &boostAccbResults[0],                           // For cascaded, this points to 9-element array, else should be 0.
	.postScaler = BOOST_POSTSCALER,                                 // Output Scale Factor for coeff normalization
	.postShift = BOOST_POSTSHIFT,                                   // Output Shift Factor for coeff normalization
    .triggerOpt = &boostTrigOpt,
    .ptrABCoefficients = &boostABCoefficients[0],                   // Address of A/B Coefficients Array
    .ptrCntrlErrorHys = &boostErrorControlHistory[0],            // Address of Error/ControlHistory Array
    .minClamp = BOOST_MIN_CLAMP,                                    // Compensator output minimum clamp value
	.maxClamp = BOOST_MAX_CLAMP,                                    // Compensator output maximum clamp value      	          
};


/*******************************************************************************
Function:       INIT_COMPENSATOR
Description:	Initialize compensators for PFC 
*******************************************************************************/
void COMPENSATOR_Initialize(void)
{   
    // Function initializes ACCAResults and control/error history arrays to zero
    COMPENSATOR_ClearArrays(&buckController, sizeof (buckErrorControlHistory));
    COMPENSATOR_ClearArrays(&boostController, sizeof (boostErrorControlHistory));
    
    // Setup context register set: W-reg context to use, address of structure for 
    // state data, and compensator type to initialize (1-cascaded, 0-traditional) 
#if defined (BUCK_CASCADED)
    COMPENSATOR_AltWregInitialize(0x1, &buckController, 0x1);;
#else
    COMPENSATOR_AltWregInitialize(0x1, &buckController, 0x0);
#endif
    
#if defined (BOOST_CASCADED)
    COMPENSATOR_AltWregInitialize(0x2, &boostController, 0x1);
#else
    COMPENSATOR_AltWregInitialize(0x2, &boostController, 0x0);
#endif
    
}
/*******************************************************************************
End of Function
*******************************************************************************/

/*******************************************************************************
Function:       CLR_COMPENSATOR_ARRAYS
Description:	Clears arrays associated to compensator 
*******************************************************************************/
void COMPENSATOR_ClearArrays(const COMPENSATOR_STATE *compState, uint16_t errorCntHyst)
{
    uint16_t i;
    
    for(i=0;i<(errorCntHyst>>1);i++)
    {
        compState->ptrCntrlErrorHys[i] = 0;
    }
    
    // If defined, then we need to clear the ACCAResults for cascaded controller
    if(compState->ptrResultacc)
    {
        for(i=0;i<9;i++)
        {
           compState->ptrResultacc[i] = 0; 
        }    
    }    
}        
/*******************************************************************************
End of Function
*******************************************************************************/
