
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

#ifndef _UPD_HW_H_
#define _UPD_HW_H_

#include <stdinc.h>



/***********************************************************************************************/
/*Defines used for 'u8PIONum' argument in UPD_GPIOEnableDisable,UPD_GPIOSetDirection,UPD_GPIOSetBufferType
functions*/
#define UPD_PIO0          0
#define UPD_PIO1          1
#define UPD_PIO2          2
#define UPD_PIO3          3
#define UPD_PIO4          4
#define UPD_PIO5          5
#define UPD_PIO6          6
#define UPD_PIO7          7
#define UPD_PIO8          8
#define UPD_PIO9          9
#define UPD_PIO10         10
#define UPD_PIO11         11
#define UPD_PIO12         12
#define UPD_PIO13         13
#define UPD_PIO14         14
#define UPD_PIO15         15

//Defines used for 'u8EnableDisable' argument in UPD_GPIOEnableDisable function 
#define UPD_ENABLE_GPIO    0
#define UPD_DISABLE_GPIO   1

//Defines used for 'u8Direction' argument in UPD_GPIOSetDirection function 
#define UPD_GPIO_SETDIR_OUTPUT  0
#define UPD_GPIO_SETDIR_INPUT   1

//Defines used for 'u8BufferType' argument in UPD_GPIOSetBufferType function 
#define UPD_GPIO_SETBUF_PUSHPULL    0
#define UPD_GPIO_SETBUF_OPENDRAIN   1

//Defines used for 'u8SetClear' argument in UPD_GPIOSetBufferType function 
#define UPD_GPIO_SET    0
#define UPD_GPIO_CLEAR   1

//Defines used for 'u8IntrType'
#define UPD_GPIO_CLEAR_INTR			0
/* use UPD_GPIO_RISING_ALERT, UPD_GPIO_FALLING_ALERT defines for rising & falling pio intr*/

/*****************************************************************************************************/

/* UPD SPI Opcodes definition */

#define UPD_SPI_WRITE_OPCODE                        0x02
#define UPD_SPI_READ_OPCODE                         0x0B
#define UPD_SPI_DUMMY_BYTE                          0x00
#define UPD_SPI_WRITE_CMD_LEN                       3
#define UPD_SPI_READ_CMD_LEN                        4

/*****************************************************************************************************/
#ifdef CONFIG_BIG_ENDIAN
/* Big endian to Little endian*/

#define BIG_TO_LITTLE_ENDIAN_UINT16(u16Var)		((UINT16)(u16Var & 0xFF) << 8) | (UINT16)(u16Var >> 8)

#define BIG_TO_LITTLE_ENDIAN_UINT32(u32Var)		((UINT32)(u32Var & 0xFF) << 24) |                     \
    											((UINT32)((u32Var >> 8) & 0xFF) << 16) |              \
    											((UINT32)((u32Var >> 16) & 0xFF) << 8) |              \
    											((UINT32)((u32Var >> 24) & 0xFF))
#endif
/*****************************************************************************************************/
/* UPD Address Base*/
#define UPD_SYSTEM_CSR_BASE_ADDR	                0x0000
#define UPD_CLK_PWR_MANAGE_CSR_BASE_ADDR            0x1000

/**************************************************************************************************/

/* System Control and Status Register */
#define UPD_VID          	        UPD_SYSTEM_CSR_BASE_ADDR + 0x04
#define UPD_SPI_TEST      	        UPD_SYSTEM_CSR_BASE_ADDR + 0x0E
#define UPD_HW_CTL          	    UPD_SYSTEM_CSR_BASE_ADDR + 0x18
#define UPD_PIO_STS				    UPD_SYSTEM_CSR_BASE_ADDR + 0x20
#define UPD_PIO_STS_LOW		        UPD_SYSTEM_CSR_BASE_ADDR + 0x20
#define UPD_PIO_STS_HIGH	        UPD_SYSTEM_CSR_BASE_ADDR + 0x21
#define UPD_PIO_INT_STS				UPD_SYSTEM_CSR_BASE_ADDR + 0x22
#define UPD_PIO_INT_EN			    UPD_SYSTEM_CSR_BASE_ADDR + 0x24

/* Configure PIOx Registers*/
#define UPD_CFG_PIO_BASE			UPD_SYSTEM_CSR_BASE_ADDR + 0x30                                                  
#define UPD_CFG_PIO0			    UPD_SYSTEM_CSR_BASE_ADDR + 0x30
#define UPD_CFG_PIO1			    UPD_SYSTEM_CSR_BASE_ADDR + 0x31
#define UPD_CFG_PIO2			    UPD_SYSTEM_CSR_BASE_ADDR + 0x32
#define UPD_CFG_PIO3			    UPD_SYSTEM_CSR_BASE_ADDR + 0x33
#define UPD_CFG_PIO4			    UPD_SYSTEM_CSR_BASE_ADDR + 0x34
#define UPD_CFG_PIO5			    UPD_SYSTEM_CSR_BASE_ADDR + 0x35
#define UPD_CFG_PIO6			    UPD_SYSTEM_CSR_BASE_ADDR + 0x36
#define UPD_CFG_PIO7			    UPD_SYSTEM_CSR_BASE_ADDR + 0x37
#define UPD_CFG_PIO8			    UPD_SYSTEM_CSR_BASE_ADDR + 0x38
#define UPD_CFG_PIO9			    UPD_SYSTEM_CSR_BASE_ADDR + 0x39
#define UPD_CFG_PIO10			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3A
#define UPD_CFG_PIO11			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3B
#define UPD_CFG_PIO12			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3C
#define UPD_CFG_PIO13			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3D
#define UPD_CFG_PIO14			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3E
#define UPD_CFG_PIO15			    UPD_SYSTEM_CSR_BASE_ADDR + 0x3F

/* PIO override register*/
#define UPD_PIO_MON_VAL				UPD_SYSTEM_CSR_BASE_ADDR + 0x54
#define UPD_PIO_OVR_EN				UPD_SYSTEM_CSR_BASE_ADDR + 0x55
#define UPD_PIO_OVR_STS				UPD_SYSTEM_CSR_BASE_ADDR + 0x56
#define UPD_PIO_OVR_INT_STS			UPD_SYSTEM_CSR_BASE_ADDR + 0x57
#define UPD_PIO_OVR_INT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0x58
												  											  
#define UPD_CFG_PIO_OUT_LOW		    UPD_SYSTEM_CSR_BASE_ADDR + 0x59
#define UPD_CFG_PIO_OUT_HIGH	    UPD_SYSTEM_CSR_BASE_ADDR + 0x5A
#define UPD_CFG_PIO_OUT_UPD_LOW	    UPD_SYSTEM_CSR_BASE_ADDR + 0x5B
#define UPD_CFG_PIO_OUT_UPD_HIGH	UPD_SYSTEM_CSR_BASE_ADDR + 0x5C
												  
#define UPD_PIO_OVR_OUT				UPD_SYSTEM_CSR_BASE_ADDR + 0x68
#define UPD_PIO_OVR_DIR				UPD_SYSTEM_CSR_BASE_ADDR + 0x6A
                                                  
#define UPD_PIO_DEBOUNCE_10MS_COUNT UPD_SYSTEM_CSR_BASE_ADDR + 0x6C
#define UPD_PIO_DEBOUNCE_1MS_COUNT  UPD_SYSTEM_CSR_BASE_ADDR + 0x6D
#define UPD_PIO_DEBOUNCE_1US_COUNT  UPD_SYSTEM_CSR_BASE_ADDR + 0x6E
#define UPD_PIO_DEBOUNCE_EN         UPD_SYSTEM_CSR_BASE_ADDR + 0x70                                                  
                                                  
                                                 										  
#define UPD_TRIM_ZTC			    UPD_SYSTEM_CSR_BASE_ADDR + 0x98
#define UPD_TRIM_ZTC_BYTE_3		    UPD_TRIM_ZTC + 0x02
												  
#define UPD_PIO_OVR0_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC0							
#define UPD_PIO_OVR1_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC1
#define UPD_PIO_OVR2_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC2													  
#define UPD_PIO_OVR3_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC3													  
#define UPD_PIO_OVR4_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC4													  
#define UPD_PIO_OVR5_SRC_SEL		UPD_SYSTEM_CSR_BASE_ADDR + 0xC5													  
												  
#define UPD_PIO_OVR0_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xD0								
#define UPD_PIO_OVR1_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xD2
#define UPD_PIO_OVR2_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xD4													  
#define UPD_PIO_OVR3_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xD6													  
#define UPD_PIO_OVR4_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xD8													  
#define UPD_PIO_OVR5_OUT_EN			UPD_SYSTEM_CSR_BASE_ADDR + 0xDA											  												  
												  
/*Defines used for Configuring PIO register values */
#define UPD_GPIO_ENABLE  		    0x1
#define UPD_GPIO_DIRECTION    	    0x2
#define UPD_GPIO_BUFFER             0x4
#define UPD_GPIO_DATAOUTPUT		    0x8
#define UPD_GPIO_RISING_ALERT		0x10
#define UPD_GPIO_FALLING_ALERT		0x20
#define UPD_GPIO_PULL_DOWN_ENABLE	BIT(6)
#define UPD_GPIO_PULL_UP_ENABLE		BIT(7)
												  
/* Defines for PIO Overridex Source Select Register (PIO_OVRx_SRC_SEL)*/
/* defines for Override Select[4:0]*/
#define UPD_PIO_OVR_SRC_SEL_VBUS_THR	0x11
/* define for VBUS Threshold Select [7:5] field*/											  
#define UPD_PIO_OVR_VBUS_THR_SEL_POS		5

#define UPD_PIO_OVR_VSAFE0V_THR_MATCH		(0 << UPD_PIO_OVR_VBUS_THR_SEL_POS)
#define UPD_PIO_OVR_VBUS0_THR_MATCH			(1 << UPD_PIO_OVR_VBUS_THR_SEL_POS)
#define UPD_PIO_OVR_VBUS1_THR_MATCH			(2 << UPD_PIO_OVR_VBUS_THR_SEL_POS)	
#define UPD_PIO_OVR_VBUS2_THR_MATCH			(3 << UPD_PIO_OVR_VBUS_THR_SEL_POS)													  
#define UPD_PIO_OVR_VBUS3_THR_MATCH			(4 << UPD_PIO_OVR_VBUS_THR_SEL_POS)													  
#define UPD_PIO_OVR_VBUS4_THR_MATCH			(5 << UPD_PIO_OVR_VBUS_THR_SEL_POS)
												  
/* OVerride Selection bit define*/
#define UPD_PIO_OVR_0						BIT(0)										  
#define UPD_PIO_OVR_1						BIT(1)
#define UPD_PIO_OVR_2						BIT(2)	
#define UPD_PIO_OVR_3						BIT(3)	
#define UPD_PIO_OVR_4						BIT(4)
#define UPD_PIO_OVR_5						BIT(5)		
                                                  
#define UPD_MCU_ACTIVE                      0
#define UPD_MCU_IDLE                        1 
                                                  
#define UPD_PIO_DEBOUNCE_FIELD_WIDTH        2

/*Debounce Enable type*/
#define UPD_PIO_DEBOUNCE_DISABLE            0                                                  
#define UPD_PIO_DEBOUNCE_CNT_TYP_1_US       1
#define UPD_PIO_DEBOUNCE_CNT_TYP_1_MS       2
#define UPD_PIO_DEBOUNCE_CNT_TYP_10_MS      3
#define UPD_PIO_DEBOUNCE_DISABLE_MASK       3                                                  
                                                  
/***********************************************************************************************/
												  

/*****************************************************************************************************/

/* Mask Macros of System Control and Status Register */

/* TRIM_ZTC */
#define UPD_PM_V2I_ENABLE		    	BIT(0)

/* TYPEC_HW_CTL Register Bits */
#define UPD_SRESET						BIT(0)
#define UPD_DEV_READY					BIT(2)
#define UPD_HW_CTL_REG_DEV_RDY_MSK  	BIT(2)

/*****************************************************************************************************/

/* Clock and Power Management control and status register */ 
#define UPD_CLK_CTL				    	UPD_CLK_PWR_MANAGE_CSR_BASE_ADDR + 0x00
#define UPD_CC_SAMP_CLK             	UPD_CLK_PWR_MANAGE_CSR_BASE_ADDR + 0x06
#define UPD_VBUS_SAMP_CLK		    	UPD_CLK_PWR_MANAGE_CSR_BASE_ADDR + 0x07

/*Defines for UPD_CC_SAMP_CLK register*/
#define UPD_CC_CLK_20_KHZ               0
#define UPD_CC_CLK_48_KHZ               BIT(3)
#define UPD_CC_SAMP_GEN_10_KS           0

/*Defines for UPD_CC_SAMP_CLK register*/
#define UPD_VBUS_CLK_20_KHZ             0
#define UPD_VBUS_CLK_48_KHZ             BIT(3)
#define UPD_VBUS_SAMP_GEN_10_KS         0
                                                  
/*Vendor ID & Product ID information*/
#define UPD_VID_LSB                     0x24
#define UPD_VID_MSB                     0x04  
                                                  
#define UPD_PID_LSB                     0x50   
#define UPD_PID_MSB                     0x03
                                                  
#define UPD_SPI_TEST_VAL                0x02   
												  
/*****************************************************************************************************/

/* UPD idle state*/
#define UPD_STATE_ACTIVE					0x01
#define UPD_STATE_IDLE						0x02
#define UPD_STATE_STARTED_IDLE_TIMER		0x03
                                                  
#define UPD_48MHZ_OSC_ENABLE	BIT(1)
#define UPD_RING_OSC_ENABLE		BIT(2)
#define UPD_SYS_CLK_ENABLE		BIT(6)
                                                  
												  
/*****************************************************************************************************/

						/* Function defines*/

/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegWriteByte (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8WriteData)

	Summary:
		wrapper to do BYTE write to UPD register through SPI
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to write a BYTE to any given UPD register address
		
	Precondition:
		None.

	Parameters:
		u8PortNum		- Corresponding port number
		u16RegOffset	- UPD Register Address where given data to be written
		u8WriteData		- Byte data to be written to the location

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/


void UPD_RegWriteByte (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8WriteData);


/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegWriteWord (UINT8 u8PortNum, UINT16 u16RegOffset, UINT16 u16WriteData)

	Summary:
		wrapper to do WORD write to UPD register through SPI
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to write a WORD to any given UPD register address
		
	Precondition:
		None.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address where given data to be written
		u16WriteData	-  16-bit WORD data to be written to the location

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/


void UPD_RegWriteWord (UINT8 u8PortNum, UINT16 u16RegOffset, UINT16 u16WriteData);


/*****************************************************************************************************/
	/*
	Function:
		UINT8 UPD_RegReadByte (UINT8 u8PortNum, UINT16 u16RegOffset)

	Summary:
		wrapper to read a BYTE from a UPD register through SPI
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to read a BYTE from any given UPD register address. 
		It returns the read value.
		
	Precondition:
		None.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address from where data to be read

	Return:
		UINT8 			- Read data is written.

	Remarks:
		None.
	**************************************************************************************************/


UINT8 UPD_RegReadByte (UINT8 u8PortNum, UINT16 u16RegOffset);


/*****************************************************************************************************/
	/*
	Function:
		UINT16 UPD_RegReadWord (UINT8 u8PortNum, UINT16 u16RegOffset)

	Summary:
		wrapper to read a WORD from a UPD register through SPI
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to read a WORD from any given UPD register address. 
		It returns the read value.
		
	Precondition:
		None.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address from where data to be read

	Return:
		UINT16 			- Read data is written.

	Remarks:
		None.
	**************************************************************************************************/


UINT16 UPD_RegReadWord (UINT8 u8PortNum, UINT16 u16RegOffset);


/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegisterWrite(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8WriteData, UINT16 u16DataSize)

	Summary:
		To write a buffer to a UPD register address through SPI.
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to write a buffer to UPD Register Address.
		
	Precondition:
		None.

	Parameters:
		u8PortNum		- Corresponding port number
		u16RegOffset	- UPD Register Address where data buffer to be written
		pu8WriteData	- Pointer to buffer to be written
		u16DataSize		- size of buffer to be writtem

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/


void UPD_RegisterWrite(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8WriteData, UINT16 u16DataSize);


/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegisterRead(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8ReadData, UINT16 u16DataSize)

	Summary:
		To read a buffer from a UPD Register Address through SPI
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to read buffer of passed data size from UPD Register Address.
		
	Precondition:
		None.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address from where buffer to be read
		*pu8ReadData	-  Pointer to data buffer where read data is to be updated
		u16DataSize 	-  size of data to read from the register

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/


void UPD_RegisterRead(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8ReadData, UINT16 u16DataSize);


/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegByteSetBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk);

	Summary:
		To SET a bit in a Byte accessed UPD Register.
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to SET a specified bit in a UPD Register through Byte access.
		
	Precondition:
		It is confined to byte access of the UPD Register.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address
		u8BitMsk		-  Mask for the bit to be SET

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/



void UPD_RegByteSetBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk);



/*****************************************************************************************************/
	/*
	Function:
		void UPD_RegByteClearBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk)

	Summary:
		To CLEAR a bit in a Byte accessed UPD Register.
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is to CLEAR a specified bit in a UPD Register through Byte access.
		
	Precondition:
		It is confined to byte access of the UPD Register.

	Parameters:
		u8PortNum		-  Corresponding port number
		u16RegOffset	-  UPD Register Address
		u8BitMsk		-  Mask for the bit to be CLEARed

	Return:
		None.

	Remarks:
		None.
	**************************************************************************************************/


void UPD_RegByteClearBit (UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 u8BitMsk);


/*****************************************************************************************************/

void UPD_GPIOEnableDisable(UINT8 u8PortNum,UINT8 u8PIONum, UINT8 u8EnableDisable);
void UPD_GPIOSetDirection(UINT8 u8PortNum,UINT8 u8PIONum, UINT8 u8Direction);
void UPD_GPIOSetBufferType(UINT8 u8PortNum,UINT8 u8PIONum, UINT8 u8BufferType);
void UPD_GPIOSetClearOutput(UINT8 u8PortNum,UINT8 u8PIONum, UINT8 u8SetClear);
void UPD_RegisterWriteISR(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8WriteData, UINT16 u16DataSize);
void UPD_RegisterReadISR(UINT8 u8PortNum, UINT16 u16RegOffset, UINT8 *pu8ReadData, UINT16 u16DataSize);
void UPD_GPIOSetIntrAlert (UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8IntrType);
void UPD_ConfigurePIODebounceCount(UINT8 u8PortNum, UINT8 u8CountType, UINT8 u8CountValue);
void UPD_GPIOSetDebounce (UINT8 u8PortNum, UINT8 u8PIONum, UINT8 u8DebounceEnType);
void UPD_PIOHandleISR (UINT8 u8PortNum);
void UPD_GPIOInit(UINT8 u8PortNum);
void UPD_ConfigPIOOvrforPwrFault (UINT8 u8PortNum);
void UPD_SetIdleCB (UINT8 u8PortNum, UINT8 u8PESubState);
void PD_StartIdleTimer(UINT8 u8PortNum);
UINT8 UPD_CheckUPDsActive();

#endif
