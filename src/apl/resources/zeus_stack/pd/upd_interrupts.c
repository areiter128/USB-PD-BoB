
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

void UPDIntr_AlertHandler (UINT8 u8PortNum)
{
    do
    {
        if (gau8PortDisable[u8PortNum] & PORT_STATUS_DISABLED)
        {
            break;
        }
              
        CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
        
        UINT16 u16InterruptStatus = 0;
        UINT16 u16Data = 0;

#if INCLUDE_POWER_MANAGEMENT_CTRL 
        UINT8 u8ReadData = 0x00;
	
        if (gau8ISRPortState[u8PortNum] ==  UPD_STATE_IDLE)
        {
            CONFIG_HOOK_MCU_RESUME_FROM_IDLE();
              
            /*UPD350 was in idle , make sure SPI_TEST register is read as 0x02*/
            while (TRUE)
            {
                /*Read SPI_TEST register*/
                UPD_RegisterReadISR(u8PortNum, (UINT16)UPD_SPI_TEST, &u8ReadData, 1);
                    
                /*Check the SPI_TEST register value is 0x02*/
                if (u8ReadData == UPD_SPI_TEST_VAL)
                {
                    break;
                }
            }
        }
#endif

        UPD_RegisterReadISR (u8PortNum,UPDINTR_INT_STS,(UINT8 *)&u16InterruptStatus,BYTE_LEN_2);
        
        /*Checking for Device ready Interrupt*/
        if(u16InterruptStatus & UPDINTR_RDY_INT)
        {    
            
            UPD_RegisterReadISR (u8PortNum, UPDINTR_INT_EN, (UINT8 *)&u16Data, BYTE_LEN_2);
            
            u16Data &= ~UPDINTR_RDY_INT; 
            
            UPD_RegisterWriteISR (u8PortNum, UPDINTR_INT_EN, (UINT8 *)&u16Data, BYTE_LEN_2);
            
        }

        /*CC,PWR,VBUS interrupts are handled by the function "TypeC_InterruptHandler"*/
        if((u16InterruptStatus & UPDINTR_CC_INT) || (u16InterruptStatus & UPDINTR_PWR_INT) || (u16InterruptStatus & UPDINTR_VBUS_INT))
        {
            TypeC_HandleISR (u8PortNum, u16InterruptStatus);
        }
        
        /*Checking for PD MAC Interrupt*/
        if (u16InterruptStatus & UPDINTR_MAC_INT)
        {
            PRL_HandleISR (u8PortNum);
        }
		
		/* Checking for UPD GPIO interrupt */
		if (u16InterruptStatus & UPDINTR_PIO_INT)
		{
			UPD_PIOHandleISR (u8PortNum);
		}

#if INCLUDE_POWER_MANAGEMENT_CTRL
        
        /*Set UPD_STATE_ACTIVE at End of ISR*/
        gau8ISRPortState[u8PortNum] = UPD_STATE_ACTIVE;
#endif
        
        CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();	
    }
    while (FALSE);
}
