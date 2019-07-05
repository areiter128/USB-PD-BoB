#include "softStart.h"

/*******************************************************************************
 * Function: 	SOFTSTART_Initialize
 * Description:	Sets up the pointer to controller's control reference and
 *              initializes the states of the structure along with any intial
 *              reference for the controller
*******************************************************************************/
void SOFTSTART_Initialize(SOFTSTART_STATE *sftStrtControl, int16_t *ptrSftStrtVar, int16_t initRef)
{
    sftStrtControl->ptrSftStrtReference = ptrSftStrtVar;
    
    // Need to initial structure with initial set reference
    *sftStrtControl->ptrSftStrtReference = initRef;
    sftStrtControl->sftStrtRefInitial = initRef;
   
    sftStrtControl->sftStrtActiveFlag = false;
}


/*******************************************************************************
 * Function: 	SOFTSTART_SetReference
 * Description:	Sets new target reference for controller and finds delta count
 *              change based on current reference value
*******************************************************************************/
void SOFTSTART_SetReference(SOFTSTART_STATE *sftStrtControl, int16_t targetRef)
{    
    sftStrtControl->sftStrtTargetRef = targetRef;
    
    //Find delta between current reference set point and new target reference
    sftStrtControl->sftStrtDelta = (targetRef - *sftStrtControl->ptrSftStrtReference);
    
    // When modifying control reference after soft start event completed, the initial starting
    // point needs to be updated to current reference position.
    sftStrtControl->sftStrtRefInitial = *sftStrtControl->ptrSftStrtReference;
    
    // If target reference is modified during soft start active, then accumulated
    // Scaler value needs to be cleared. This should be cleared any time soft start 
    // is being enabled too. As this API is required to be used with soft start
    // just using it here should suffice.
    sftStrtControl->sftStrtScalerAcc = 0;
}

/*******************************************************************************
 * Function: 	SOFTSTART_Enabled
 * Description:	Sets internal flag for activating the soft start function and 
 *              resets structure internal states
*******************************************************************************/
void SOFTSTART_Enabled(SOFTSTART_STATE *sftStrtControl)
{   
    sftStrtControl->sftStrtActiveFlag = true;
}

/*******************************************************************************
 * Function: 	SOFTSTART_Disabled
 * Description:	Clears internal flag for deactivating the soft start function
*******************************************************************************/
void SOFTSTART_Disabled(SOFTSTART_STATE *sftStrtControl)
{
    sftStrtControl->sftStrtActiveFlag = false;
}


bool SOFTSTART_Initiate(SOFTSTART_STATE *sftStrtControl)
{
    int16_t tempVar;
    
    if (sftStrtControl->sftStrtActiveFlag == true)
    {    
        // Accumulate scaler to give ramp for soft start
        sftStrtControl->sftStrtScalerAcc += sftStrtControl->sftStrtScaler;
        
        // Calculate new control reference set point
        tempVar = __builtin_mulsu(sftStrtControl->sftStrtDelta, sftStrtControl->sftStrtScalerAcc) >> 16;
        *sftStrtControl->ptrSftStrtReference = (sftStrtControl->sftStrtRefInitial + tempVar); 
   
        // Check if adding another sftStrtScaler would overflow indicating the end of the soft start
        if((UINT_MAX - sftStrtControl->sftStrtScalerAcc) < sftStrtControl->sftStrtScaler)
        {
            *sftStrtControl->ptrSftStrtReference  = sftStrtControl->sftStrtTargetRef;
            sftStrtControl->sftStrtActiveFlag = false;
        }       
    }    
    
    return sftStrtControl->sftStrtActiveFlag;    
}