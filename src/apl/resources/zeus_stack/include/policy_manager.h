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

#ifndef _POLICY_MANAGER_H_
#define _POLICY_MANAGER_H_
   
#include <stdinc.h>

/******************************************************************************
                Return Values from PE_ValidateMessage API
******************************************************************************/
#define DPM_VALID_REQUEST            1
#define DPM_INVALID_REQUEST          0   
   
#define DPM_OBJECT_POSITION_1                    1
#define PDO_MAX_OBJECTS 				         7

/*Macros to get PDO type, PDO Current, PDO voltage,USB Comm capable bit from
Source/Sink Power delivery objects*/
#define DPM_GET_PDO_TYPE(X)   					((X & 0xC0000000) >> 30)
#define DPM_GET_PDO_CURRENT(X)                  ((X & 0x000003FF))
#define DPM_GET_PDO_VOLTAGE(X)                  ((X & 0x000FFC00) >> 10)	/*in 50mv units*/
#define DPM_GET_PDO_USB_COMM_CAP(X)             ((X & 0x04000000) >> 26)

#define DPM_PD0_VOLTAGE_5                        100

#define DPM_FORM_DATA_REQUEST(OBJECT_POSITION,CAPABLITY_MISMATCH,USB_COMMUNICATION_CAPABLE, \
        OPERATING_CURRENT,MAXIMUM_OPERATING_CURRENT) ((OBJECT_POSITION << 28) | \
        (CAPABLITY_MISMATCH << 26) | (USB_COMMUNICATION_CAPABLE << 25) | (OPERATING_CURRENT << 10) \
          | (MAXIMUM_OPERATING_CURRENT))


/********************* Macros for E-Cable ***************************/
#define DPM_VDM_GET_CMD_TYPE(u32VDMHeader)      ((u32VDMHeader & DPM_VDM_CMD_TYPE_MASK) >> \
                                                        DPM_VDM_CMD_TYPE_POS)

#define DPM_GET_CABLE_CUR_VAL(u32ProductTypeVDO)    ((u32ProductTypeVDO & DPM_CABLE_CUR_VAL_BIT_MASK) >> \
                                                        DPM_CABLE_CUR_VAL_BIT_POS)

#define DPM_CABLE_CUR_VAL_BIT_MASK       (BIT(5) | BIT(6))
#define DPM_CABLE_CUR_VAL_BIT_POS        5

#define DPM_VDM_CMD_TYPE_MASK            (BIT(6) | BIT(7))
#define DPM_VDM_CMD_TYPE_POS             6               

#define DPM_CABLE_CURR_3A                1
#define DPM_CABLE_CURR_5A                2

#define DPM_CABLE_CURR_3A_UNIT           300
#define DPM_CABLE_CURR_5A_UNIT           500

#define DPM_VDM_HEADER_POS              0
#define DPM_VMD_PRODUCT_TYPE_VDO_POS    4

#define DPM_DEBUG_PDO_GENERATION( USB_SUSPEND, UNCONS_POWER, USB_COM, MAX_CURRENT, MAX_VOLTAGE)  \
        (((UINT32)USB_SUSPEND << 28) | ((UINT32)UNCONS_POWER << 27) | ((UINT32)USB_COM << 26) | (((UINT32)MAX_VOLTAGE/50) << 10) | (((UINT32)MAX_CURRENT)/10))

#define DPM_DEBUG_PDO_5V_9MA      DPM_DEBUG_PDO_GENERATION(1, 1, 0, 900, 5000)
#define DPM_DEBUG_PDO_5V_1P5A     DPM_DEBUG_PDO_GENERATION(1, 1, 0, 1500, 5000)
#define DPM_DEBUG_PDO_5V_3A       DPM_DEBUG_PDO_GENERATION(1, 1, 0, 3000, 5000)

/*Structure of Device Policy Manager*/
typedef struct CONFIG_STRUCT_PACKED_START
{
  UINT8 u8DPM_ConfigData;   //Bit 0 - Default Port Role <p />
                            //Bit 1 - Default Data Role <p />
                            //Bit 3:2 - Default PD Spec Revision <p />
                            //Bit 4 - Default Vconn Swap support
  UINT8 u8DPM_Status;       //Bit 0 - Status of Port Role <p />
                            //Bit 1 - Status of Data Role <p />
                            //Bit 3:2 - Status of PD Spec Revision <p />
                            //Bit 4 - Status of Vconn Swap support 
  UINT32  u32NegotiatedPDO; //NegotiatedPDO
  UINT16 u16MaxCurrSupported;   //Maximum current supported by E-Cable
  UINT32 u32SinkReqRDO;         //Sink Requested RDO
  UINT8 u8VCONNErrCounter;
  #if INCLUDE_POWER_FAULT_HANDLING
	  UINT8 u8VBUSPowerGoodTimerID;     //VBUS PowerGood Timer ID
      UINT8 u8VCONNPowerGoodTimerID;    //VConn PowerGood Timer ID
	  UINT8 u8VBUSPowerFaultCount;      //VBUS Power fault count
      UINT8 u8VCONNPowerFaultCount;     //VConn Power fault count     
      UINT8 u8VCONNGoodtoSupply;        //Vconn good to supply
	  UINT8 u8PowerFaultISR;          //Power falut ISR flag
	  UINT8 u8HRCompleteWait;         //Hard Reset complete wait flag
  #endif
  
}CONFIG_STRUCT_PACKED_END DEVICE_POLICY_MANAGER;


/* User Config Structure: This structure contains the user configure variables and PDOs*/

typedef struct _PortData_cfg CONFIG_STRUCT_PACKED_START
{
    UINT32 u32CfgData;			//Bits 2:0 - Port Role <p />
								//Bits 4:3 - Type-C Current (Applicable only for Source)
    UINT32 u32PDO[7];		    //Source/Sink Capabilities PDOs
    UINT8  u8PDOCnt;			//PDO count of Source/Sink Capabilities
#if INCLUDE_POWER_FAULT_HANDLING    
	UINT8  u8VBUSEnPio;         //PIO for UPD350  VBus Enable pin		
	UINT8  u8PrtctlOCSPio;      //PIO for UPD350 Port Control selection pin
#endif
}CONFIG_STRUCT_PACKED_END PORT_CONFIG_DATA;


/*Bit definition for u8DPM_ConfigData variable*/
#define DPM_DEFAULT_POWER_ROLE_MASK           BIT(0)
#define DPM_DEFAULT_DATA_ROLE_MASK            BIT(1)
#define DPM_DEFAULT_PD_SPEC_REV_MASK         (BIT(2) | BIT(3))
#define DPM_VCONN_SWAP_SUPPORT_MASK           BIT(4)

/*Bit position for u8DPM_ConfigData variable*/
#define DPM_DEFAULT_POWER_ROLE_POS           0
#define DPM_DEFAULT_DATA_ROLE_POS            1
#define DPM_DEFAULT_PD_SPEC_REV_POS          2

/*Defines for getting data from u8DPM_ConfigData variable*/
#define DPM_GET_DEFAULT_POWER_ROLE(u8PortNum)         ((gasDPM[u8PortNum].u8DPM_ConfigData & DPM_DEFAULT_POWER_ROLE_MASK) >> DPM_DEFAULT_POWER_ROLE_POS)
#define DPM_GET_DEFAULT_DATA_ROLE(u8PortNum)          ((gasDPM[u8PortNum].u8DPM_ConfigData & DPM_DEFAULT_DATA_ROLE_MASK) >> DPM_DEFAULT_DATA_ROLE_POS)
#define DPM_GET_DEFAULT_PD_SPEC_REV(u8PortNum)        ((gasDPM[u8PortNum].u8DPM_ConfigData & DPM_DEFAULT_PD_SPEC_REV_MASK) >> DPM_DEFAULT_PD_SPEC_REV_POS)
    
/*Defines for getting data from u8DPM_Status variable*/
#define DPM_GET_CURRENT_POWER_ROLE(u8PortNum)         ((gasDPM[u8PortNum].u8DPM_Status & DPM_CURR_POWER_ROLE_MASK) >> DPM_CURR_POWER_ROLE_POS)
#define DPM_GET_CURRENT_DATA_ROLE(u8PortNum)          ((gasDPM[u8PortNum].u8DPM_Status & DPM_CURR_DATA_ROLE_MASK) >> DPM_CURR_DATA_ROLE_POS)
#define DPM_GET_CURRENT_PD_SPEC_REV(u8PortNum)        ((gasDPM[u8PortNum].u8DPM_Status & DPM_CURR_PD_SPEC_REV_MASK) >> DPM_CURR_PD_SPEC_REV_POS)

/*Bit definition for u8DPM_Status variable*/
#define DPM_CURR_POWER_ROLE_MASK            BIT(0)
#define DPM_CURR_DATA_ROLE_MASK             BIT(1)
#define DPM_CURR_PD_SPEC_REV_MASK          (BIT(2) | BIT(3))
#define DPM_VDM_STATE_ACTIVE_MASK           BIT(4)

/*Bit position for u8DPM_Status variable*/
#define DPM_CURR_POWER_ROLE_POS            0
#define DPM_CURR_DATA_ROLE_POS             1
#define DPM_CURR_PD_SPEC_REV_POS           2
#define DPM_VDM_STATE_ACTIVE_POS           4


#define DPM_GET_DPM_STATUS(u8PortNum)				gasDPM[u8PortNum].u8DPM_Status

/*Defines for getting data by passing u8DPM_Status variable*/
#define DPM_GET_CURRENT_POWER_ROLE_FRM_STATUS(u8DPM_Status)   ((u8DPM_Status & DPM_CURR_POWER_ROLE_MASK) >> DPM_CURR_POWER_ROLE_POS)
#define DPM_GET_CURRENT_DATA_ROLE_FRM_STATUS(u8DPM_Status)    ((u8DPM_Status & DPM_CURR_DATA_ROLE_MASK) >> DPM_CURR_DATA_ROLE_POS)
#define DPM_GET_CURRENT_PD_SPEC_REV_FRM_STATUS(u8DPM_Status)  ((u8DPM_Status & DPM_CURR_PD_SPEC_REV_MASK) >> DPM_CURR_PD_SPEC_REV_POS)

/*Defines for getting voltage from PDO*/
#define DPM_PDO_VOLTAGE_MASK                 0x3FF
#define DPM_PDO_VOLTAGE_POS                  10
#define DPM_PDO_VOLTAGE_UNIT                 50
#define DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(u32PDO)    (((u32PDO >> DPM_PDO_VOLTAGE_POS) & DPM_PDO_VOLTAGE_MASK) * DPM_PDO_VOLTAGE_UNIT)

/*Defines for getting current from PDO*/
#define DPM_PDO_CURRENT_MASK                 0x3FF
#define DPM_PDO_CURRENT_POS                  0
#define DPM_PDO_CURRENT_UNIT                 10
#define DPM_GET_CURRENT_FROM_PDO_MILLI_A(u32PDO)    (((u32PDO >> DPM_PDO_CURRENT_POS) & DPM_PDO_CURRENT_MASK) * DPM_PDO_CURRENT_UNIT)

/*u8PowerFaultISR defines */
#define DPM_POWER_FAULT_OVP				BIT(0)
#define DPM_POWER_FAULT_UV				BIT(1)
#define DPM_POWER_FAULT_VBUS_OCS		BIT(2)
#define DPM_POWER_FAULT_VCONN_OCS	    BIT(3)

/*----------Macros for u8VConnEnable argument of DPM_VConnOnOff API ------------*/
#define DPM_VCONN_ON             1
#define DPM_VCONN_OFF            0

/*----------Macros for u8VbusOnorOff argument of DPM_VBusOnOff API ------------*/
#define DPM_VBUS_ON              1
#define DPM_VBUS_OFF             0

/* Macros for CONFIG_HOOK_NOTIFY_POWER_FAULT return value */
#define DPM_HANDLE_PWR_FAULT	TRUE
#define DPM_NEGLECT_PWR_FAULT	FALSE
typedef enum {

	eFIXED_SUPPLY_PDO,
	eBATTERY_SUPPLY_PDO,
	eVARIABLE_SUPPLY_PDO,
	ePROGRAMMABLE_POWER_SUPPLY_APDO

}ePDOType;


/**************************************************************************************************
    Function:
        void DPM_Init(UINT8 u8PortNum);

    Summary:
        This API initializes a given Port to the Power Role and Data role based on the port's global variable

    Devices Supported:
        UPD350 REV A

    Description:
        Port initialization of Device policy manager initialize the member of DPM structure 
        "gasDPM[u8PortNum]"

    Conditions:
        This API is called inside the PD Stack initialisation API call .

    Input:
        u8PortNum - Port Number.

    Return:
        None.

    Remarks:
        None.

**************************************************************************************************/
void DPM_Init(UINT8 u8PortNum);

/**************************************************************************************************
 Function:
        void DPM_StateMachine (UINT8 u8PortNum);

    Summary:
        This API is called to run the DPM State machine for a given port.

    Devices Supported:
        UPD350 REV A

    Description:
        This API is called to run the Type C and Policy Engine State machine for a given port.

    Conditions:
        None.

    Input:
        u8PortNum - Port Number.

    Return:
        None.

    Remarks:
        None.
**************************************************************************************************/
void DPM_StateMachine (UINT8 u8PortNum);

/****************************** DPM APIs Accessing Type C Port Control Module*********************/

/**************************************************************************************************
    Function:
        void DPM_SetPortPower(UINT8 u8PortNum);

    Summary:
        This API is used to drive the VBUS for requested power.

    Devices Supported:
        UPD350 REV A

    Description:
        This API is used to drive the VBUS for requested power.

    Conditions:
        None.

    Input:
        u8PortNum     - Port Number for power to be driven

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_SetPortPower(UINT8 u8PortNum);

/****************************** DPM Source related APIs*****************************************/

/**************************************************************************************************
    Function:
        void DPM_Get_Source_Capabilities(UINT8 u8PortNum, UINT8* NumOfPdo, UINT32* pu32DataObj);

    Summary:
        This API is used to get the port source capabilities from the DPM.

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to get the port source capabilities from the DPM.

    Conditions:
        None.

    Input:
        u8PortNum - Port Number for which source cabilities to be returned.
        NumOfPdo - Pointer to hold number of PDOs supported by the port
        pu32DataObj - Pointer to hold the source capabilities.

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_Get_Source_Capabilities(UINT8 u8PortNum, UINT8* NumOfPdo, UINT32* pu32DataObj);

/**************************************************************************************************
    Function:
        UINT8 DPM_ValidateRequest(UINT8 u8PortNum, UINT16 u16Header, UINT8 *u8DataBuf);

    Summary:
        This API is used to validate the received request messgae from the sink port parnter.

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to validate the received request messgae from the sink port parnter.

    Conditions:
        None.

    Input:
        u8PortNum     - Port Number for which the received request message to be validated
        u16Header - Request message Header
        u8DataBuf - Pointer which holds the data objects of received request message.

    Return:
        DPM_VALID_REQUEST - Received message is valid request
        

    Remarks:
        None
**************************************************************************************************/
UINT8 DPM_ValidateRequest(UINT8 u8PortNum, UINT16 u16Header, UINT8 *u8DataBuf);

/**************************************************************************************************
    Function:
        DPM_StoreVDMECableData(UINT8 u8PortNum, UINT8 u8SOPType, UINT16 u16Header, UINT32* u8DataBuf);

    Summary:
        This API is used to store the capabilities received from the E-Marked cable.

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to store the capabilities received from the E-Marked cable.

    Conditions:
        None.

    Input:
        u8PortNum - Port Number for which E-Cable data to be stored
        u8SOPType - Sop type of received 
        u16Header - Header of received Discover Identity command response
        u8DataBuf - Pointer which holds the data objects of received Discover Identity command response.

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
UINT8 DPM_StoreVDMECableData(UINT8 u8PortNum, UINT8 u8SOPType, UINT16 u16Header, UINT32* u8DataBuf);

/****************************** DPM Fault handling related APIs*****************************************/
void DPM_PowerFaultHandler(UINT8 u8PortNum);
void DPM_HandleFaultInISR(UINT8 u8PortNum);
void DPM_ConfigurePwrFault(UINT8 u8PortNum);

/**************************************************************************************************
    Function:
        void DPM_VCONNPowerGood_TimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable);

    Summary:
        This API is given as the timer call back API when starting the VCONNPowerGood Timer from 
        Type-C state machine.
       
    Devices Supported:
        UPD350 REV A

    Description:
        This API is given as the timer call back API when starting the VCONNPowerGood Timer from 
        Type-C state machine.
        
    Conditions:
        None

    Input:
        u8PortNum       - Port Number.
        u8DummyVariable - Dummy Argument

    Return:
        None.

    Remarks:
        None.

**************************************************************************************************/
void DPM_VCONNPowerGood_TimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable);

/**************************************************************************************************
    Function:
        void DPM_VConnOnOff(UINT8 u8PortNum, UINT8 u8VConnEnable);

    Summary:
        This API is used to turn on/off the VCONN supply of a given port

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to turn on/off the VCONN of a given port

    Conditions:
        None.

    Input:
        u8PortNum     - Port Number for which the sink capability to be returned
        u8VConnEnable - Variable denoting either to turn on or off the VCONN
                      - DPM_VCONN_ON (Turn on VCONN)
                      - DPM_VCONN_OFF (Turn off VCONN)

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_VConnOnOff(UINT8 u8PortNum, UINT8 u8VConnEnable);
/**************************************************************************************************
    Function:
        UINT16 DPM_GetVBUSVoltage(UINT8 u8PortNum);

    Summary:
        This API returns the VBUS level of a given port

    Devices Supported:
        UPD350 REV A

    Description:
        This API returns the VBUS level of a given port

    Conditions:
        None.

    Input:
        u8PortNum       - Port Number for which the sink capability to be returned

    Return:
        UINT16

    Remarks:
        None
**************************************************************************************************/
UINT16 DPM_GetVBUSVoltage(UINT8 u8PortNum);
/**************************************************************************************************
    Function:
        void DPM_GetTypeCStates(UINT8 u8PortNum, UINT8 *pu8TypeCState, UINT8 *pu8TypeCSubState);

    Summary:
        This API is used to get the present Type C state and Type C sub state for a given port

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to get the present Type C state and Type C sub state for a given port

    Conditions:
        None.

    Input:
        u8PortNum       - Port Number for which the sink capability to be returned
        *pu8TypeCState   -  Pointer holding the Type C State
        *pu8TypeCSubState - Pointer holding the Type C Sub State

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_GetTypeCStates(UINT8 u8PortNum, UINT8 *pu8TypeCState, UINT8 *pu8TypeCSubState);
/**************************************************************************************************
    Function:
        void DPM_SetTypeCState(UINT8 u8PortNum, UINT8 u8TypeCState, UINT8 u8TypeCSubState);

    Summary:
        This API is used to set the state and sub state of Type C State machine for a given port

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to set the state and sub state of Type C State machine for a given port

    Conditions:
        None.

    Input:
        u8PortNum       - Port Number for which the sink capability to be returned
        u8TypeCState   -  Type C State to be set
        u8TypeCSubState - Type C SubState to be set

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_SetTypeCState(UINT8 u8PortNum, UINT8 u8TypeCState, UINT8 u8TypeCSubState);
/**************************************************************************************************
    Function:
        void DPM_GetPoweredCablePresence(UINT8 u8PortNum, UINT8 *pu8RaPresence);

    Summary:
        This API is used to find out the presence of powered cable in the CC lines for a given port

    Devices Supported:
        UPD350 REV A

    Description:
         This API is used to find out the presence of powered cable in the CC lines for a given port

    Conditions:
        None.

    Input:
        u8PortNum       - Port Number for which the sink capability to be returned
        *pu8RaPresence   - Pointer returning the Powered cable presence

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_GetPoweredCablePresence(UINT8 u8PortNum, UINT8 *pu8RaPresence);
/**************************************************************************************************
    Function:
        void DPM_VBusOnOff(UINT8 u8PortNum, UINT8 u8VbusOnorOff);

    Summary:
        This API drives the VBUS line of a given port to either 0V or 5V.

    Devices Supported:
        UPD350 REV A

    Description:
        This API drives the VBUS line of a given port to either 0V or 5V depending on the value of the argument 
    u8VbusOnorOff

    Conditions:
        None.

    Input:
        u8PortNum       - Port Number for which the sink capability to be returned
        u8VbusOnorOff   - Variable denoting either to turn on or off the VBUS
                        - DPM_VBUS_ON (Turn on VBUS)
                        - DPM_VBUS_OFF (Turn off VBUS)

    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_VBusOnOff(UINT8 u8PortNum, UINT8 u8VbusOnorOff);
/**************************************************************************************************
    Function:
        UINT8 DPM_IsPort_VCONN_Source(UINT8 u8PortNum);

    Summary:
        This API is used find whether the port is currently sourcing VCONN or not

    Devices Supported:
        UPD350 REV A

    Description:
        This API is used find whether the port is currently sourcing VCONN or not. It returns 1 if it is a 
    VCONN Source and 0 if it does not supply VCONN currently

    Conditions:
        None.

    Input:
        u8PortNum  - Port Number for which the sink capability to be returned

    Return:
        UINT8

    Remarks:
        None
**************************************************************************************************/
UINT8 DPM_IsPort_VCONN_Source(UINT8 u8PortNum);
/**************************************************************************************************
    Function:
        void DPM_Evaluate_Received_Src_caps(UINT8 u8PortNum ,UINT16 u16RecvdSrcCapsHeader, UINT32 *u32RecvdSrcCapsPayload);

    Summary:
        Device Policy Manager evaluates the received source capability aganist the sink capability and 
    chooses the nearest match PDO for the data request message

    Devices Supported:
        UPD350 REV A

    Description:
        This Function is called by the policy engine to the Device policy Manager to choose the PDO for the 
    data request message

    Conditions:
        None.

    Input:

        u8PortNum               - Port Number for which the sink capability to be returned
        u16RecvdSrcCapsHeader  -  Header of the received source capability message
        u32RecvdSrcCapsPayload  -  Pointer variable holding the Data object of Source Capability message



    Return:
    None

    Remarks:
    None
**************************************************************************************************/
void DPM_Evaluate_Received_Src_caps(UINT8 u8PortNum ,UINT16 u16RecvdSrcCapsHeader, UINT32 *u32RecvdSrcCapsPayload);
/**************************************************************************************************
    Function:
        UINT8 DPM_Find_Src_Sink_Caps_match(UINT32 u32In_SrcPDO, UINT32 u32In_SinkPDO);

    Summary:
        Device Policy Manager compares a given source PDO and a sink PDO and returns the match

    Devices Supported:
        UPD350 REV A

    Description:
        This Function is used to find the match between the single source and sink PDO

    Conditions:
        None.

    Input:

        u32In_SrcPDO  -  Given Source PDO
        u32In_SinkPDO  - Given Sink PDO

    Return:
        UINT8

    Remarks:
        None
**************************************************************************************************/
UINT8 DPM_Find_Src_Sink_Caps_match(UINT32 u32In_SrcPDO, UINT32 u32In_SinkPDO);
/**************************************************************************************************
    Function:
        void DPM_Get_Sink_Capabilities(UINT8 u8PortNum,UINT8* u8pSinkPDOCnt, UINT32 * pu32DataObj);

    Summary:
        Device Policy Manager updates the policy engine about the sink capability for a given port

    Devices Supported:
        UPD350 REV A

    Description:
        This Function is called by the policy engine to the Device policy Manager to get the sink capability Power data object for a given port

    Conditions:
        None.

    Input:

        u8PortNum      - Port Number for which the sink capability to be returned
        u8pSinkPDOCnt  - Pointer variable holding the PDO count of sink capability
        pu32DataObj   - Pointer variable holding the Data object of Sink Capability message



    Return:
        None

    Remarks:
        None
**************************************************************************************************/
void DPM_Get_Sink_Capabilities(UINT8 u8PortNum, UINT8* u8pSinkPDOCnt, UINT32 * pu32DataObj);
/**************************************************************************************************/

/**************************************************************************************************
    Function:
        void DPM_VBUSOnOffTimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable);

    Summary:
        This API is given as the timer call back API when starting the VBUSOnOff Timer from 
        Type-C and source policy engine state machines.
       
    Devices Supported:
        UPD350 REV A

    Description:
        This API is given as the timer call back API when starting the VBUSOnOff Timer from 
        Type-C and source policy engine state machines.
        
    Conditions:
        None

    Input:
        u8PortNum       - Port Number.
        u8DummyVariable - Dummy Argument

    Return:
        None.

    Remarks:
        None.

**************************************************************************************************/
void DPM_VBUSOnOffTimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable);

void DPM_SrcReadyTimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable);

void DPM_VCONNONTimerErrorCB (UINT8 u8PortNum , UINT8 u8DummyVariable);

void DPM_VCONNOFFErrorTimerCB (UINT8 u8PortNum , UINT8 u8DummyVariable);

void DPM_ResetVCONNErrorCnt (UINT8 u8PortNum);

void DPM_SetPowerFaultISR(UINT8 u8PortNum, UINT8 u8FaultSt);

UINT8 DPM_IsHardResetInProgress(UINT8 u8PortNum);
#endif