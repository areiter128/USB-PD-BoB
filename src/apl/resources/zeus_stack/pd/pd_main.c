
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
#include "..\..\thermal_power_management.h"

/*******************************************************************/
/******************* Functions**************************************/
/*******************************************************************/


void PD_CheckAndDisablePorts ()
{
    UINT8 u8ReadData[4];
    
    /*Start 10ms timer*/
    UINT8 u8TimerID = PDTimer_Start (MILLISECONDS_TO_TICKS(10), NULL, NULL, NULL);
#if INCLUDE_POWER_MANAGEMENT_CTRL ==1
    CONFIG_HOOK_UPDRESET_THRU_GPIO();
#endif    
    /*Check if timer is Active, if Timer expired, come out of this loop and go ahead with the status of 
      gau8PortDisable[u8PortNum]*/
    while ((gasPDTimers[u8TimerID].u8TimerSt_PortNum & GENERIC_TIMER_STATE) != GENERIC_TIMER_EXPIRED)
    {    
        for (UINT8 u8PortNum = 0; u8PortNum < CONFIG_PD_PORT_COUNT; u8PortNum++)
        { 
            /*u8IsSPI_CommActive[u8PortNum] default value is FALSE*/
            if (gau8PortDisable[u8PortNum] == PORT_STATUS_DISABLED)
            {
                /*Read SPI_TEST register*/
                UPD_RegisterRead(u8PortNum, (UINT16)UPD_SPI_TEST, u8ReadData, 4);
                    
                /*Check the SPI_TEST register value is 0x02*/
                if (u8ReadData[0] == UPD_SPI_TEST_VAL)
                {
                    /*Read VID & PID register*/
                    UPD_RegisterRead(u8PortNum, (UINT16)UPD_VID, u8ReadData, 4);          
             
                    /*Verify the default values*/
                    if((u8ReadData[0] == UPD_VID_LSB) && (u8ReadData[1] == UPD_VID_MSB) && \
                      (u8ReadData[2] == UPD_PID_LSB) && (u8ReadData[3] == UPD_PID_MSB))
                    {  
                        /*Value read from this port is right, so enable the ports, Set SPI 
                           Communcation is active for this port*/
                        gau8PortDisable[u8PortNum] = PORT_STATUS_ENABLED;

                    }
                }
            }
        } 
    }   
  
}


void PD_StateMachinesInit()
{
	for (UINT8 u8PortNum = 0; u8PortNum < CONFIG_PD_PORT_COUNT; u8PortNum++)
  	{
        if (PORT_STATUS_ENABLED == gau8PortDisable[u8PortNum])
        {
		  	/* Init UPD350 GPIO */
		  	UPD_GPIOInit(u8PortNum);
			
            /*Type-C UPD350 register configuration for a port*/
            TypeC_InitPort(u8PortNum);
            
            /* PRL Init for all the port present */
            PRL_Init (u8PortNum);
        }
    }
}

UINT8 PD_Init(void)
{
    UINT8 u8InitStatus = 1;
       
    /*Timer module Initialization*/
    (void)PDTimer_Init();
    
    /*Initialize HW SPI module defined by the user*/
    CONFIG_HOOK_HW_SPI_INIT();
    
    /*UPD350 Reset GPIO Init*/
    CONFIG_HOOK_HW_UPDRESETGPIO_INIT();
    
    /*Initialize config global variables*/
    PD_InitializeConfigGlobals();
	
	/*Initialize Internal global variables*/
    PD_InitializeInternalGlobals();
    
    PD_CheckAndDisablePorts();
    
    //JMS
    CONFIG_HOOK_PORTS_ENABLE_DISABLE(&gau8PortDisable[0]/*,&gasPortConfigurationData[0]*/);
    
    /*Initialize debug hardware*/
    CONFIG_HOOK_DEBUG_INIT();
    
    CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
    
    /*User defined UPD Interrupt Initialization for MCU*/
    CONFIG_HOOK_HW_UPDALERTGPIO_INIT(&gau8PortDisable[0]);
    
    CONFIG_HOOK_HW_PORTPWR_INIT();
	    
    PD_StateMachinesInit();  

    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
    
    return u8InitStatus;

}

void PD_Run()
{
	thermal_power_management_state_machine();
    
    for (UINT8 u8PortNum = 0; u8PortNum < CONFIG_PD_PORT_COUNT; u8PortNum++)
  	{
          if (PORT_STATUS_ENABLED == gau8PortDisable[u8PortNum])
          {
             DPM_StateMachine (u8PortNum);
              
			#if INCLUDE_POWER_MANAGEMENT_CTRL
                
              	/*Restart IDLE Timer if UPD350 is Active*/
				PD_StartIdleTimer (u8PortNum);
				
				if (gu8SetMCUidle)
                {
                    /*Invalidate MCU Idle*/
                    gu8SetMCUidle = UPD_MCU_ACTIVE;      
                    
                    CONFIG_HOOK_SET_MCU_IDLE();
                    
                    CONFIG_HOOK_MCU_RESUME_FROM_IDLE();
                                  
                }
              
			#endif
      
          }
	}
}

