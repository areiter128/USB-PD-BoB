#ifndef SOFTSTART_H
#define SOFTSTART_H

#include <stdint.h>
#include <stdbool.h>
#include <xc.h>

#define UINT_MAX   0xFFFF

// 
typedef struct
{
   volatile int16_t   *ptrSftStrtReference;         // Pointer to control Reference
   volatile int16_t   sftStrtRefInitial;            // Initial set point for reference
   volatile int16_t   sftStrtTargetRef;             // Final value for sftStrt to complete
   volatile int16_t   sftStrtDelta;                 // Difference between current reference and target
   volatile uint16_t  sftStrtScaler;                // Calculated value based on timing requirements
   volatile uint16_t  sftStrtScalerAcc;             // Accumulated scaler to give proper ramp meeting timings
   volatile uint8_t   sftStrtActiveFlag;            // Flag automatically disabled after soft start completes
        
}SOFTSTART_STATE;  

// Sets pointer to application's control reference and initializes states of the structure
void SOFTSTART_Initialize(SOFTSTART_STATE *sftStrtControl, int16_t *ptrSftStrtVar, int16_t initRef);

// Configures the target reference set point. Function will calculate delta 
// count change to be applied from current operating state
void SOFTSTART_SetReference(SOFTSTART_STATE *sftStrtControl, int16_t targetRef);

// Determines the step size for control reference to meet start up timings
// Should be called after setting up references (initial and limit)
// Routine to call softstart function is user responsibility
static inline void SOFTSTART_ConfigTiming(SOFTSTART_STATE *sftStrtControl, uint32_t sftStartCallRate_ns, uint32_t sftStartDuration_ns);

// Enable / Disable APIs for softstart
void SOFTSTART_Enabled(SOFTSTART_STATE *sftStrtControl);
void SOFTSTART_Disabled(SOFTSTART_STATE *sftStrtControl);

bool SOFTSTART_Initiate(SOFTSTART_STATE *sftStrtControl);



/*******************************************************************************
 * Function: 	SOFTSTART_ConfigTiming
 * Description:	Determines scaler based on timing inputs that would ramp to
 *              desired reference at rate defined with proper resolution.
 *              If call Rate and soft start duration are constants, this scaler
 *              should be calculated at compile time, eliminating run time requirements
 * Inputs:      Pointer to softStartControl structure, CallRate and SoftStart duration in nanoseconds
 * Output:      None
*******************************************************************************/

static inline void __attribute__((always_inline)) SOFTSTART_ConfigTiming(SOFTSTART_STATE *sftStrtControl, uint32_t sftStartCallRate_ns, uint32_t sftStartDuration_ns)
{    
    uint32_t tempDiv;
    
    
    if((__builtin_constant_p(sftStartCallRate_ns)) && (__builtin_constant_p(sftStartDuration_ns)))
    {
        sftStrtControl->sftStrtScaler = (UINT_MAX / (sftStartDuration_ns / sftStartCallRate_ns));
    }    
    else
    { 
        tempDiv = (sftStartDuration_ns / sftStartCallRate_ns);

        if(tempDiv <= UINT_MAX) {
            sftStrtControl->sftStrtScaler = __builtin_divud(UINT_MAX, tempDiv);
        }
        else {
            sftStrtControl->sftStrtScaler = (UINT_MAX / tempDiv);
        }    
    }
}



#endif 
