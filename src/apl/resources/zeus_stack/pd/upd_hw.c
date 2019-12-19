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

/******************************************************************************************************/


void UPD_RegWriteByte (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8WriteValue)
{
	UPD_RegisterWrite (u8PortNum, u16RegOffset, &u8WriteValue, BYTE_LEN_1);
}

void UPD_RegWriteWord (UINT8 u8PortNum, UINT16 u16RegOffset, UINT16 u16WriteValue)
{
    UPD_RegisterWrite (u8PortNum, u16RegOffset, (UINT8 *)&u16WriteValue, BYTE_LEN_2);
}

/******************************************************************************************************/

UINT8 UPD_RegReadByte (UINT8 u8PortNum, UINT16 u16RegOffset)
{
	UINT8 u8ReadData;
	UPD_RegisterRead (u8PortNum, u16RegOffset, &u8ReadData, BYTE_LEN_1);
	return u8ReadData;
}

UINT16 UPD_RegReadWord (UINT8 u8PortNum, UINT16 u16RegOffset)
{
	UINT16 u16ReadData;
	UPD_RegisterRead (u8PortNum, u16RegOffset, (UINT8 *)&u16ReadData, BYTE_LEN_2);
	return u16ReadData;
}

/******************************************************************************************************/

void UPD_RegByteSetBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk)
{
	UINT8 u8Data = 0;
	UPD_RegisterRead (u8PortNum, u16RegOffset, &u8Data, BYTE_LEN_1);
	u8Data |= u8BitMsk; 
	UPD_RegisterWrite (u8PortNum, u16RegOffset, &u8Data, BYTE_LEN_1);
}

void UPD_RegByteClearBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk)
{

    UINT8 u8Data = 0;
    UPD_RegisterRead (u8PortNum, u16RegOffset, &u8Data, BYTE_LEN_1);
    u8Data &= ~u8BitMsk;
    UPD_RegisterWrite (u8PortNum, u16RegOffset, &u8Data, BYTE_LEN_1);
}

/******************************************************************************************************/
void UPD_RegisterWrite (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8WriteData, UINT16 u16DataSize)
{
    CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
    
	UINT8 u8Command [UPD_SPI_WRITE_CMD_LEN];
	
	u8Command [0] = UPD_SPI_WRITE_OPCODE;
	u8Command [1] = HIBYTE(u16RegOffset);
	u8Command [2] = LOBYTE(u16RegOffset);

	CONFIG_HOOK_HW_SPI_CS_LOW (u8PortNum);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (u8Command, (UINT16)UPD_SPI_WRITE_CMD_LEN);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (pu8WriteData, u16DataSize);

	CONFIG_HOOK_HW_SPI_CS_HIGH (u8PortNum);
    
    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
}
/******************************************************************************************************/
void UPD_RegisterRead(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8ReadData, UINT16 u16DataSize)
{
	CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
    
    UINT8 u8Command [UPD_SPI_READ_CMD_LEN];

	u8Command[0] = UPD_SPI_READ_OPCODE;
	u8Command[1] = HIBYTE (u16RegOffset);
	u8Command[2] = LOBYTE (u16RegOffset);
	u8Command[3] = UPD_SPI_DUMMY_BYTE;

	CONFIG_HOOK_HW_SPI_CS_LOW (u8PortNum);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (u8Command, (UINT16)UPD_SPI_READ_CMD_LEN);

	CONFIG_HOOK_HW_SPI_READ_TRANSFER (pu8ReadData, u16DataSize);

	CONFIG_HOOK_HW_SPI_CS_HIGH (u8PortNum);
    
    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();

}

/******************************************************************************************************/

void UPD_RegisterWriteISR (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8WriteData, UINT16 u16DataSize)
{
	UINT8 u8Command [UPD_SPI_WRITE_CMD_LEN];
	
	u8Command [0] = UPD_SPI_WRITE_OPCODE;
	u8Command [1] = HIBYTE(u16RegOffset);
	u8Command [2] = LOBYTE(u16RegOffset);

	CONFIG_HOOK_HW_SPI_CS_LOW (u8PortNum);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (u8Command, (UINT16)UPD_SPI_WRITE_CMD_LEN);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (pu8WriteData, u16DataSize);

	CONFIG_HOOK_HW_SPI_CS_HIGH (u8PortNum);
}

/******************************************************************************************************/

void UPD_RegisterReadISR(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8ReadData, UINT16 u16DataSize)
{
	UINT8 u8Command [UPD_SPI_READ_CMD_LEN];

	u8Command[0] = UPD_SPI_READ_OPCODE;
	u8Command[1] = HIBYTE (u16RegOffset);
	u8Command[2] = LOBYTE (u16RegOffset);
	u8Command[3] = UPD_SPI_DUMMY_BYTE;

	CONFIG_HOOK_HW_SPI_CS_LOW (u8PortNum);

	CONFIG_HOOK_HW_SPI_WRITE_TRANSFER (u8Command, (UINT16)UPD_SPI_READ_CMD_LEN);

	CONFIG_HOOK_HW_SPI_READ_TRANSFER (pu8ReadData, u16DataSize);

	CONFIG_HOOK_HW_SPI_CS_HIGH (u8PortNum);

}

/******************************************************************************************************/

void UPD_GPIOEnableDisable(UINT8 u8PortNum,UINT8 u8PIONum, UINT8 u8EnableDisable)
{
    if(u8EnableDisable == UPD_ENABLE_GPIO)
    {
         UPD_RegByteSetBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_ENABLE);
    }
   
    else
    {
        UPD_RegByteClearBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_ENABLE);
    }   

}

/******************************************************************************************************/

void UPD_GPIOSetDirection(UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8Direction)
{
  
    if(UPD_GPIO_SETDIR_OUTPUT == u8Direction)
    {
         UPD_RegByteSetBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_DIRECTION);
    }
   
    else
    {
        UPD_RegByteClearBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_DIRECTION);
    }   

}

/******************************************************************************************************/

void UPD_GPIOSetBufferType(UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8BufferType)
{
  
    if(UPD_GPIO_SETBUF_PUSHPULL == u8BufferType)
    {
         UPD_RegByteSetBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_BUFFER);
    }
   
    else
    {
        UPD_RegByteClearBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_BUFFER);
    }   
}

/******************************************************************************************************/

void UPD_GPIOSetClearOutput(UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8SetClear)
{
    if(UPD_GPIO_SET == u8SetClear)
    {
         UPD_RegByteSetBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_DATAOUTPUT);
    }
   
    else
    {
        UPD_RegByteClearBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), UPD_GPIO_DATAOUTPUT);
    }   
}

/******************************************************************************************************/

void UPD_GPIOSetIntrAlert (UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8IntrType)
{
	if(u8IntrType)
    {
         UPD_RegByteSetBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), u8IntrType); 
    }
	else
    {
        UPD_RegByteClearBit (u8PortNum, (UPD_CFG_PIO_BASE + u8PIONum), \
		  						(UPD_GPIO_FALLING_ALERT | UPD_GPIO_RISING_ALERT));
    } 
}
/******************************************************************************************************/
void UPD_ConfigurePIODebounceCount(UINT8 u8PortNum, UINT8 u8CountType, UINT8 u8CountValue)
{
    UINT16 u16RegOffset = SET_TO_ZERO;
    switch(u8CountType)
    {
        case UPD_PIO_DEBOUNCE_CNT_TYP_1_US:
        {
            u16RegOffset= UPD_PIO_DEBOUNCE_1US_COUNT;
            break;
        }
        case UPD_PIO_DEBOUNCE_CNT_TYP_1_MS:
        {
            u16RegOffset = UPD_PIO_DEBOUNCE_1MS_COUNT;
            break;
        }
        case UPD_PIO_DEBOUNCE_CNT_TYP_10_MS:
        {
            u16RegOffset = UPD_PIO_DEBOUNCE_10MS_COUNT;
            break;
        }     
    }
    UPD_RegWriteByte(u8PortNum, u16RegOffset, u8CountValue);
     
}

/******************************************************************************************************/

void UPD_GPIOSetDebounce (UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8DebounceEnType)
{
    UINT32 u32Data = 0;
    if (UPD_PIO_DEBOUNCE_DISABLE == u8DebounceEnType)
    {
        
        UPD_RegisterRead (u8PortNum, UPD_PIO_DEBOUNCE_EN, (UINT8 *)&u32Data, BYTE_LEN_4);
        u32Data &= ~(((UINT32)UPD_PIO_DEBOUNCE_DISABLE_MASK) << (u8PIONum * UPD_PIO_DEBOUNCE_FIELD_WIDTH));
        UPD_RegisterWrite (u8PortNum, UPD_PIO_DEBOUNCE_EN, (UINT8 *)&u32Data, BYTE_LEN_4);

    }
    else
    {
        UPD_RegisterRead (u8PortNum, UPD_PIO_DEBOUNCE_EN, (UINT8 *)&u32Data, BYTE_LEN_4);
        u32Data |= (((UINT32)u8DebounceEnType) << (u8PIONum * UPD_PIO_DEBOUNCE_FIELD_WIDTH));
        UPD_RegisterWrite (u8PortNum, UPD_PIO_DEBOUNCE_EN, (UINT8 *)&u32Data, BYTE_LEN_4);
    }   
}
/******************************************************************************************************/
void UPD_GPIOInit(UINT8 u8PortNum)
{
	/*Enable GPIO interrupt for UPD350*/
	UPD_RegWriteWord (u8PortNum, UPDINTR_INT_EN, UPDINTR_PIO_INT);
	
	#if INCLUDE_POWER_FAULT_HANDLING
	
	/* Configure Fault Pin */
    CONFIG_HOOK_PRTCTL_OCS_INIT(u8PortNum);  
	
	#if INCLUDE_UPD_PIO_OVERRIDE_SUPPORT
		/* Configure PIO override for fault conditions */
		UPD_ConfigPIOOvrforPwrFault(u8PortNum);
	#endif 
		
	#endif /* endif of INCLUDE_POWER_FAULT_HANDLING */
}

/******************************************************************************************************/

void UPD_PIOHandleISR(UINT8 u8PortNum)
{
	UINT16 u16PIOIntSts = 0;
	
 	/* Read the interrupt status*/
	UPD_RegisterReadISR (u8PortNum, UPD_PIO_INT_STS, (UINT8 *)&u16PIOIntSts, BYTE_LEN_2);
	
    /* Hook for the user to configure PIO interrupts*/
	CONFIG_HOOK_PIO_HANDLER_ISR(u8PortNum, u16PIOIntSts);
	
	/* clear the interrupt status */
	UPD_RegisterWriteISR (u8PortNum, UPD_PIO_INT_STS, (UINT8 *)&u16PIOIntSts, BYTE_LEN_2);
}
/******************************************************************************************************/

#if INCLUDE_UPD_PIO_OVERRIDE_SUPPORT

void UPD_ConfigPIOOvrforPwrFault (UINT8 u8PortNum)
{
	/* Override 0 - Overvoltage Threshold*/
	/* Override 1 - Fault Low*/
	/* Under voltage cannot be controlled through Override concept
		as there is no provision see a threshold  is below a given threshold*/
	
	/* get the PIO number for EN_VBUS */
	UINT8 u8PIONum = gasPortConfigurationData[u8PortNum].u8VBUSEnPio;
	
	/* Enable monitoring for Overide 0*/
	/* Overide 1 should monitor for '0' on line thus it is not enabled*/
	UPD_RegWriteByte (u8PortNum, UPD_PIO_MON_VAL, UPD_PIO_OVR_0 );
	
	/* Pio override output is set as low */
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR_OUT, 0x0);
	
	/* Configure the Source for override 0 as OverVoltage Threshold 2*/
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR0_SRC_SEL, \
	  (UPD_PIO_OVR_SRC_SEL_VBUS_THR | UPD_PIO_OVR_VBUS2_THR_MATCH));
	
	/* Configure the Source for override 1 as Fault_IN/PRT_CTL pin low from Load switch */
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR1_SRC_SEL, gasPortConfigurationData[u8PortNum].u8PrtctlOCSPio);
	
	/* VBUS_EN is configured as override Pin in output mode */
	/* Override 0*/
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR_DIR, BIT(u8PIONum));
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR0_OUT_EN, BIT(u8PIONum));

	/* Override 1*/
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR_DIR, BIT(u8PIONum));
	UPD_RegWriteWord (u8PortNum, UPD_PIO_OVR1_OUT_EN, BIT(u8PIONum));
}
#endif

/******************************************************************************************************/

#if INCLUDE_POWER_MANAGEMENT_CTRL

UINT8 UPD_CheckUPDsActive()
{
    UINT8 u8IsAllUPDsActive = FALSE;
    
    for (UINT8 u8PortNo = 0; u8PortNo < CONFIG_PD_PORT_COUNT; u8PortNo++)
  	{
		/*Ignore if port is disabled, so consider only for enabled ports*/
		if (gau8PortDisable[u8PortNo] == PORT_STATUS_ENABLED)
		{
			/*UPD_STATE_ACTIVE will be set frequently by respective Alert ISR.
			  It means that the appropriate port is active, so skip MCU IDLE*/
			if (gau8ISRPortState[u8PortNo] == UPD_STATE_ACTIVE ||
			/*Verify any other IDLE timer is running for all other ports.
			if its running, then lets handle in that timer expire event, so skip MCU
			IDLE for now*/
             ((gasPDTimers[gau8PortIdleTimerID[u8PortNo]].u8TimerSt_PortNum & GENERIC_TIMER_STATE ) == GENERIC_TIMER_ACTIVE))

			{
				u8IsAllUPDsActive = TRUE;
				break;
			}
		}
	}
  
    return u8IsAllUPDsActive;
}
void UPD_SetIdleCB (UINT8 u8PortNum, UINT8 u8PESubState)
{
 
	/*Invalidate this Timer ID since it is stored in global*/
    gau8PortIdleTimerID[u8PortNum] = MAX_CONCURRENT_TIMERS;
	
	/*Set gau8PortState to UPD_STATE_IDLE*/
	gau8ISRPortState[u8PortNum] = UPD_STATE_IDLE;

	/*Enable RX_AFE: In order to receive a PD message the RX AFE shall be enabled by SW and the trip point set via
	  CC RX DAC Control Register (CC_RX_DAC_CTL) and  CC RX DAC Filter Register
	  (CC_RX_DAC_FILT)*/
	//TBD
	
	/*Disable Ring , 48 MHz Oscillator and System clock*/
	UPD_RegByteClearBit (u8PortNum, UPD_CLK_CTL , (UPD_RING_OSC_ENABLE | UPD_48MHZ_OSC_ENABLE | UPD_SYS_CLK_ENABLE) );
    
    HOOK_DEBUG_PORT_STR (u8PortNum,"UPDHW: Set Port Idle");
	
	//Put MCU into IDLE

	
	if (FALSE == UPD_CheckUPDsActive())
	{
        HOOK_DEBUG_PORT_STR (u8PortNum,"UPDHW: Set MCU IDLE");
                
		gu8SetMCUidle = UPD_MCU_IDLE;
	}
	
}
          
void PD_StartIdleTimer(UINT8 u8PortNum)
{
    CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
                
    /*Restart UPD IDLE Timer*/
    if (gau8ISRPortState[u8PortNum] == UPD_STATE_ACTIVE)
    {
                
        PDTimer_Kill (gau8PortIdleTimerID[u8PortNum]);
        
        gau8PortIdleTimerID[u8PortNum] = MAX_CONCURRENT_TIMERS;
        
        gau8PortIdleTimerID[u8PortNum] = PDTimer_Start(\
                    CONFIG_PORT_UPD_IDLE_TIMEOUT_MS,\
                    UPD_SetIdleCB,\
                    u8PortNum, \
                    NULL);
                    
        gau8ISRPortState[u8PortNum] = UPD_STATE_STARTED_IDLE_TIMER;
    }
    
    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
}    
#endif
