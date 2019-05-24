
/*
* Copyright (c) 2017 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute
* Software only when embedded on a Microchip microcontroller or digital signal
* controller that is integrated into your product or third party product
* (pursuant to the sublicense terms in the accompanying license agreement).
*
* You should refer to the license agreement accompanying this Software for
* additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
* MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
* CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
* OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
* INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
* CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
* SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
* (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*/

#include <stdinc.h>

UINT8 PDTimer_Init()
{

	/*Setting all the PD Software timer's state to Non Active during PD stack initilization*/

	for (UINT8 u8TimerID = 0; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++)
	{

		gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
        gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_NON_ACTIVE;

	}
    
    /*CONFIG_HOOK_HW_PDTIMER_INIT() will configure and start the hardware timer on 
    the MCU to generate periodic interrupts*/
	return CONFIG_HOOK_HW_PDTIMER_INIT();
	

}


UINT8 PDTimer_Start (UINT32 u32Timeout_ticks, PDTimerCallback pfnTimerCallback, UINT8 u8PortNum, UINT8 u8PDState)
{

	UINT8 u8TimerID;
    
    /*Find the unused PD Software timer and start the given timeout value with the found timer*/    
	for (u8TimerID = 0; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++)
	{

		if (((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE ) == GENERIC_TIMER_NON_ACTIVE) || ((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE)== GENERIC_TIMER_EXPIRED))
		{

#if defined(CONFIG_16_BIT_PDTIMEOUT)

			gasPDTimers[u8TimerID].u16Timeout_Tickcnt = (UINT16)u32Timeout_ticks;
#else
			gasPDTimers[u8TimerID].u32Timeout_Tickcnt = u32Timeout_ticks;
#endif

            /*Store the callback function address and arguments to be passed in the PD Software 
            timer structure*/
			gasPDTimers[u8TimerID].pfnTimerCallback = pfnTimerCallback;
			gasPDTimers[u8TimerID].u8TimerSt_PortNum = (u8PortNum & GENERIC_TIMER_PORT_NUM);
			gasPDTimers[u8TimerID].u8PDState = u8PDState;
            
            /*Setting the PD Software timer state to "Active"*/
			gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
            gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_ACTIVE;
            break;

		}

	}
	return u8TimerID;

}

void PDTimer_WaitforTicks (UINT32 u32Timeout_ticks)
{
    UINT8 u8TimerID;
    
    /*Find the unused PD Software timer and start the given timeout value with the found timer*/    
	for (u8TimerID = 0; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++)
	{

		if (((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE ) == GENERIC_TIMER_NON_ACTIVE) || ((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE)== GENERIC_TIMER_EXPIRED))
		{

#if defined(CONFIG_16_BIT_PDTIMEOUT)

			gasPDTimers[u8TimerID].u16Timeout_Tickcnt = (UINT16)u32Timeout_ticks;
#else
			gasPDTimers[u8TimerID].u32Timeout_Tickcnt = u32Timeout_ticks;
#endif
            /*Setting the PDTimer Call back function as NULL*/
            gasPDTimers[u8TimerID].pfnTimerCallback = NULL;
            
            /*Setting the PD Software timer state to "Active"*/
			gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
            gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_ACTIVE;
            
            do
            {
                /*Wait here until the Timer state changes to Timer Expired*/
              
            }while((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE) == GENERIC_TIMER_ACTIVE);
          
            break;
        }        
    }
    
}


void PDTimer_Kill (UINT8 u8TimerID)
{  
   /*Disabling Global interrupts, So that Timer Variable will not be corrupted by the 
   PDTimer ISR Handler*/       
   CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
   
    if(u8TimerID < MAX_CONCURRENT_TIMERS)
    {       
        /*Setting the PD Software timer to "Non Active"  state will disable the PDTimer 
        ISR Handler from calling the callback function*/
        gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
        gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_NON_ACTIVE;

        gasPDTimers[u8TimerID].pfnTimerCallback = NULL;        
        
    }
	/*Enabling the Global interrupts*/
	CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();    
}


void PDTimer_KillPortTimers (UINT8 u8PortNum)
{

	/*Disabling Global interrupts, So that Timer Variable will not be 
    corrupted by the PDTimer ISR Handler*/
	CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
	
	gasPolicy_Engine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
	gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = MAX_CONCURRENT_TIMERS;
	gasChunkSM [u8PortNum].u8CAorChunkSMTimerID = MAX_CONCURRENT_TIMERS;
	gasPolicy_Engine[u8PortNum].u8PENoResponseTimerID = MAX_CONCURRENT_TIMERS;
	#if INCLUDE_POWER_FAULT_HANDLING
	gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
    gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
	#endif

    //gau8PortIdleTimerID[u8PortNum] = MAX_CONCURRENT_TIMERS;

    /*Setting the PD Software timers of a given port number to "Non Active"  state will disable 
    the PDTimer ISR Handler from calling the callback function*/
    for (UINT8 u8TimerID = 0; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++)
	{

		if (((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE) == GENERIC_TIMER_ACTIVE)\
          && ((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_PORT_NUM) == u8PortNum)
            
#if INCLUDE_POWER_MANAGEMENT_CTRL
			/*If power management is active dont kill IDLE Timer*/
            && (u8TimerID != gau8PortIdleTimerID[u8PortNum])
#endif
              )
		{
			
			gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
            gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_NON_ACTIVE;            
			gasPDTimers[u8TimerID].pfnTimerCallback = NULL;
		}		

	}

	/*Enabling the Global interrupts*/
	CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();


}

void PDTimer_InterruptHandler ()
{

	CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
	
	for (UINT8 u8TimerID = 0; u8TimerID < MAX_CONCURRENT_TIMERS; u8TimerID++)
	{
         
      /*Checking for a "Active" State PD Software timer*/
      
		if (((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE) == GENERIC_TIMER_ACTIVE))
		{
			
#if defined(CONFIG_16_BIT_PDTIMEOUT)

       /*If the Timeout_Tickcnt value is 0, then the timer has expired*/
          
			if (--gasPDTimers[u8TimerID].u16Timeout_Tickcnt == 0)
			{
#else
			
			if (--gasPDTimers[u8TimerID].u32Timeout_Tickcnt == 0)
			{
#endif
				
				if (gasPDTimers[u8TimerID].pfnTimerCallback != NULL)
				{
                  
                    /*Calling the callback function with a set of arguemnts 
                    namely portnumber and PD state*/
					gasPDTimers[u8TimerID].pfnTimerCallback((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_PORT_NUM), gasPDTimers[u8TimerID].u8PDState);
				}
				
				/*Setting the timer state as "Timer Expired"*/
				gasPDTimers[u8TimerID].u8TimerSt_PortNum &= ~GENERIC_TIMER_STATE;
                gasPDTimers[u8TimerID].u8TimerSt_PortNum |= GENERIC_TIMER_EXPIRED;   
				

			}

		}

	}
	
	CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
}
