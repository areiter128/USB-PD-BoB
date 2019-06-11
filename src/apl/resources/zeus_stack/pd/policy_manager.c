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

void DPM_Init(UINT8 u8PortNum)
{
    UINT8 u8DPM_Status = gasDPM[u8PortNum].u8DPM_Status;
    UINT8 u8DPM_ConfigData = gasDPM[u8PortNum].u8DPM_ConfigData;
    
    u8DPM_Status |= (CONFIG_PD_DEFAULT_SPEC_REV << DPM_CURR_PD_SPEC_REV_POS);
    u8DPM_ConfigData |= (CONFIG_PD_DEFAULT_SPEC_REV  << DPM_DEFAULT_PD_SPEC_REV_POS);
        
    if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK)== (PD_ROLE_SOURCE))
    {   
        /* Set Port Power Role as Source in DPM Configure variable*/
        u8DPM_ConfigData |= (PD_ROLE_SOURCE << DPM_DEFAULT_POWER_ROLE_POS); 
        
        /* Set Port Data Role as DFP in DPM Cofigure variable*/
        u8DPM_ConfigData |= (PD_ROLE_DFP << DPM_DEFAULT_DATA_ROLE_POS);
        
        /* Set Port Power Role as Source in DPM Status variable */
        u8DPM_Status |= (PD_ROLE_SOURCE << DPM_CURR_POWER_ROLE_POS);
        
        /* Set Port Data Role as DFP in DPM Status variable */
        u8DPM_Status |= (PD_ROLE_DFP << DPM_CURR_DATA_ROLE_POS);
    }       
    else
    {
        /* Set the Default Port Power Role as Sink in DPM Status variable */
        u8DPM_ConfigData |= (PD_ROLE_SINK << DPM_DEFAULT_POWER_ROLE_POS);
        
        /* Set the Default Port Data Role as UFP in DPM Status variable */
        u8DPM_ConfigData |= (PD_ROLE_UFP << DPM_DEFAULT_DATA_ROLE_POS);
        
        /* Set the Current Port Power Role as Sink in DPM Status variable */
        u8DPM_Status |= (PD_ROLE_SINK << DPM_CURR_POWER_ROLE_POS);
        
        /* Set the Current  Port Data Role as UFP in DPM Status variable */
        u8DPM_Status |= (PD_ROLE_UFP << DPM_CURR_DATA_ROLE_POS);
    }
    
    gasDPM[u8PortNum].u8DPM_Status =  u8DPM_Status;
    gasDPM[u8PortNum].u8DPM_ConfigData  = u8DPM_ConfigData;
	
#if INCLUDE_POWER_FAULT_HANDLING
	gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
	gasDPM[u8PortNum].u8PowerFaultISR = SET_TO_ZERO;
	gasDPM[u8PortNum].u8VBUSPowerFaultCount = RESET_TO_ZERO;
	gasDPM[u8PortNum].u8HRCompleteWait = RESET_TO_ZERO;
    /*VCONN OCS related variables*/
    gasDPM[u8PortNum].u8VCONNGoodtoSupply = TRUE;
    gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
    gasDPM[u8PortNum].u8VCONNPowerFaultCount = SET_TO_ZERO;

#endif
	
    
}

void DPM_StateMachine (UINT8 u8PortNum)
{
    CONFIG_HOOK_DEVICE_POLICY_MANAGER_PRE_PROCESS(u8PortNum);
    
    /*Run Type C State machine*/
    TypeC_RunStateMachine (u8PortNum);
    
    /*Run Policy engine State machine*/
    PE_RunStateMachine(u8PortNum);
	
	/* Power Fault hanling*/
	#if INCLUDE_POWER_FAULT_HANDLING
		DPM_PowerFaultHandler(u8PortNum);
	#endif
    
    CONFIG_HOOK_DEVICE_POLICY_MANAGER_POST_PROCESS(u8PortNum);
}


/****************************** DPM APIs Accessing Type C Port Control Module*********************/

void DPM_GetTypeCStates(UINT8 u8PortNum, UINT8 *pu8TypeCState, UINT8 *pu8TypeCSubState)
{
    *pu8TypeCState = gasTypeCcontrol[u8PortNum].u8TypeCState;
    *pu8TypeCSubState = gasTypeCcontrol[u8PortNum].u8TypeCSubState;
}

void DPM_GetPoweredCablePresence(UINT8 u8PortNum, UINT8 *pu8RaPresence)
{
    *pu8RaPresence = (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_PWDCABLE_PRES_MASK);
}

void DPM_SetTypeCState(UINT8 u8PortNum, UINT8 u8TypeCState, UINT8 u8TypeCSubState)
{
    gasTypeCcontrol[u8PortNum].u8TypeCState = u8TypeCState;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState = u8TypeCSubState;
}

void DPM_SetPortPower(UINT8 u8PortNum)
{
    UINT16 u16PDOVoltage = DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasDPM[u8PortNum].u32NegotiatedPDO);
	
	if (DPM_GET_CURRENT_POWER_ROLE(u8PortNum) == PD_ROLE_SOURCE)
	{
		TypeC_VBUSDrive (u8PortNum, u16PDOVoltage);
	}
	else
	{
		TypeC_ConfigureVBUSThr(u8PortNum, u16PDOVoltage, TYPEC_CONFIG_NON_PWR_FAULT_THR);
	}
}

void DPM_ConfigurePwrFault(UINT8 u8PortNum)
{	
	#if INCLUDE_POWER_FAULT_HANDLING
	/* Obtain voltage from negoitated PDO*/
    UINT16 u16PDOVoltage = DPM_GET_VOLTAGE_FROM_PDO_MILLI_V(gasDPM[u8PortNum].u32NegotiatedPDO);
	/* set the threshold to detect fault*/
	TypeC_ConfigureVBUSThr(u8PortNum, u16PDOVoltage, TYPEC_CONFIG_PWR_FAULT_THR);
	#endif
}

void DPM_VConnOnOff(UINT8 u8PortNum, UINT8 u8VConnEnable)
{
    if(u8VConnEnable == DPM_VCONN_ON)
    {
        /*Enable VCONN by switching on the VCONN FETS*/
        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_ENABLE);              
    }    
    else
    {
        /*Disable VCONN by switching off the VCONN FETS*/
        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);     
    }
}

UINT16 DPM_GetVBUSVoltage(UINT8 u8PortNum)
{  
    
    UINT16 u16VBUSvoltage =  gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK;
	
	switch(u16VBUSvoltage)
	{
		case TYPEC_VBUS_0V:
		{
			u16VBUSvoltage = PWRCTRL_VBUS_0V;
			break;
		}
		case TYPEC_VBUS_5V:
		{
			u16VBUSvoltage = PWRCTRL_VBUS_5V;
			break;
		}
		case TYPEC_VBUS_9V:
		{
			u16VBUSvoltage = PWRCTRL_VBUS_9V;
			break;
		}
		case TYPEC_VBUS_15V:
		{
			u16VBUSvoltage = PWRCTRL_VBUS_15V;
			break;
		}
		case TYPEC_VBUS_20V:
		{
			u16VBUSvoltage = PWRCTRL_VBUS_20V;
			break;
		}
	}
    return u16VBUSvoltage;
}
/*****************************************************************************************/
void DPM_VBusOnOff(UINT8 u8PortNum, UINT8 u8VbusOnorOff)
{
  	if (u8VbusOnorOff)
	{
 		TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_5V);
	}
	else
	{
		TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);
		CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
	}
}

/****************************** DPM Source related APIs*****************************************/

/* Validate the received Request message */
UINT8 DPM_ValidateRequest(UINT8 u8PortNum, UINT16 u16Header, UINT8 *u8DataBuf)
{
    UINT8 u8RetVal = FALSE;
    UINT8 u8SinkReqObjPos= SET_TO_ZERO;
    UINT16 u16SinkReqCurrVal = SET_TO_ZERO;
    UINT16 u16SrcPDOCurrVal = SET_TO_ZERO;
    UINT8 u8RaPresence = SET_TO_ZERO;
    
    /* Get the status of E-Cable presence and ACK status */
    u8RaPresence = (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_PWDCABLE_PRES_MASK) & \
                    (~((gasPolicy_Engine[u8PortNum].u8PEPortSts & \
                                            PE_CABLE_RESPOND_NAK) >> PE_CABLE_RESPOND_NAK_POS));
    
    /* Get the Requested PDO object position from received buffer */
    u8SinkReqObjPos= ((u8DataBuf[3]) & PE_REQUEST_OBJ_MASK) >> PE_REQUEST_OBJ_POS;
    
    /* Get the Requested Max current value */
    u16SinkReqCurrVal = ((UINT16)((u8DataBuf[1]) << 8) | u8DataBuf[0]);
    u16SinkReqCurrVal = (u16SinkReqCurrVal & PE_REQUEST_MAX_CUR_MASK);

    /* Get the current value of Requested Source PDO */
    u16SrcPDOCurrVal = ((gasPortConfigurationData[u8PortNum].u32PDO[u8SinkReqObjPos-1]) & \
                     PE_REQUEST_MAX_CUR_MASK); 
    
    /* If Requested Max current is greater current value of Requested Source PDO or
        Requested object position is invalid, received request is invalid request */ 
    u8RetVal = (u16SinkReqCurrVal > u16SrcPDOCurrVal) ? DPM_INVALID_REQUEST : (((u8SinkReqObjPos<= FALSE) || \
               (u8SinkReqObjPos> gasPortConfigurationData[u8PortNum].u8PDOCnt))) ? \
                DPM_INVALID_REQUEST : (u8RaPresence == FALSE) ? DPM_VALID_REQUEST : \
                (u16SinkReqCurrVal > gasDPM[u8PortNum].u16MaxCurrSupported) ? \
                DPM_INVALID_REQUEST : DPM_VALID_REQUEST;   
    
    /* If request is valid set the Negotiated PDO as requested */
    if(u8RetVal == DPM_VALID_REQUEST)
    {
        u8RetVal = CONFIG_HOOK_PDO_REQUEST_POST_PROCESS_VALID(u8PortNum, u16SinkReqCurrVal, u8SinkReqObjPos);
        if (u8RetVal)
        {
            gasDPM[u8PortNum].u32NegotiatedPDO = (gasPortConfigurationData[u8PortNum].u32PDO[u8SinkReqObjPos-1]);        
            HOOK_DEBUG_PORT_STR (u8PortNum,"DPM-PE: Requested is Valid \r\n");
        }
    }
      
    return u8RetVal;
}

/* Reset the current value in PDO */
UINT32 DPM_CurrentCutDown (UINT32 u32PDO)
{
    /* If PDO max current greater than E-Cable supported current, reset the current value */
    if((u32PDO & PE_MAX_CURR_MASK) > DPM_CABLE_CURR_3A_UNIT)
    {
        u32PDO &= ~PE_MAX_CURR_MASK;
        u32PDO |= DPM_CABLE_CURR_3A_UNIT;
    }
    
    return u32PDO; 
}

/* Copy the Source capabilities */
void DPM_ChangeCapbilities (UINT32* pu32DataObj, UINT32 *pu32SrcCaps, UINT8 u8pSrcPDOCnt)
{
    for (UINT8 u8PDOindex = 0; u8PDOindex < u8pSrcPDOCnt; u8PDOindex++)
    {   
        /* Reset the current value to E-Cable supported current */
        pu32DataObj[u8PDOindex] = DPM_CurrentCutDown (pu32SrcCaps[u8PDOindex]);
    } 
}

/* Get the source capabilities from the port configuration structure */
void DPM_Get_Source_Capabilities(UINT8 u8PortNum, UINT8* u8pSrcPDOCnt, UINT32* pu32DataObj)
{   
    /* Get the source PDO count */
    UINT8 u8RaPresence = SET_TO_ZERO;
    *u8pSrcPDOCnt = gasPortConfigurationData[u8PortNum].u8PDOCnt;
   
    UINT32 *pu32SrcCap = (UINT32 *)&gasPortConfigurationData[u8PortNum].u32PDO[0];
    
    DPM_GetPoweredCablePresence(u8PortNum, &u8RaPresence);
   
    /* E-Cable presents */
    if((TRUE == u8RaPresence))
    {
        /* If E-Cable max current is 5A, pass the capabilities without change */
        if(gasDPM[u8PortNum].u16MaxCurrSupported == DPM_CABLE_CURR_5A_UNIT)
        {
             (void)CONFIG_HOOK_MEMCPY( &pu32DataObj[0], &pu32SrcCap[0], \
              ((*u8pSrcPDOCnt) * 4));
        }
        /* If E-Cable max current is 3A and PDO current value is more than 3A, 
            reset the current value of PDOs */
        else
        {
            DPM_ChangeCapbilities (&pu32DataObj[0], &pu32SrcCap[0], *u8pSrcPDOCnt);
        }
          
    }
    
    else
    {
        DPM_ChangeCapbilities (pu32DataObj, &pu32SrcCap[0],*u8pSrcPDOCnt);  
    }
}

UINT8 DPM_StoreVDMECableData(UINT8 u8PortNum, UINT8 u8SOPType, UINT16 u16Header, UINT32* u32DataBuf)
{
    UINT32 u32ProductTypeVDO;
    UINT8 u8RetVal = FALSE;
    UINT8 u8CurVal;
    
    /* Get the CMD type from received VDM */
    u8RetVal = DPM_VDM_GET_CMD_TYPE(u32DataBuf[DPM_VDM_HEADER_POS]);
    
    /* if Data object is one, received message is NAK */
    if(u8RetVal == PE_VDM_NAK || u8RetVal == PE_VDM_BUSY)
    {
        u8RetVal = PE_VDM_NAK;
    }
    
    else
    {
        /* Get the product VDO from the received message */
        u32ProductTypeVDO = u32DataBuf[DPM_VMD_PRODUCT_TYPE_VDO_POS];               
       
        /* Get the Cable supported current value */
        u8CurVal = DPM_GET_CABLE_CUR_VAL(u32ProductTypeVDO);
        
        /* Setting E-Cable Max Current Value */
        if(u8CurVal == DPM_CABLE_CURR_3A)
        {
            gasDPM[u8PortNum].u16MaxCurrSupported = DPM_CABLE_CURR_3A_UNIT;
        }
        
        else if(u8CurVal == DPM_CABLE_CURR_5A)
        {
            gasDPM[u8PortNum].u16MaxCurrSupported = DPM_CABLE_CURR_5A_UNIT;
        }
        
        else
        {
           /* Do nothing */ 
        }
        
        /* Received message is ACK */
        u8RetVal = PE_VDM_ACK;
    }
    
    return u8RetVal;
}

#if INCLUDE_PD_SINK_ONLY
/****************************** DPM Sink related APIs*****************************************/
void DPM_Get_Sink_Capabilities(UINT8 u8PortNum,UINT8 *u8pSinkPDOCnt, UINT32 * pu32DataObj)
{   
    /*Get Sink Capability from Port Configuration Data Structure*/
    *u8pSinkPDOCnt = gasPortConfigurationData[u8PortNum].u8PDOCnt;
    
     (void)CONFIG_HOOK_MEMCPY ( pu32DataObj, gasPortConfigurationData[u8PortNum].u32PDO, \
                            (gasPortConfigurationData[u8PortNum].u8PDOCnt * 4));
}

void  DPM_Evaluate_Received_Src_caps(UINT8 u8PortNum ,UINT16 u16RecvdSrcCapsHeader,
                                     UINT32 *pu32RecvdSrcCapsPayload)
{
 
    INT8 i8SinkPDOIndex;
	UINT8 u8SrcPDOIndex;
	UINT8 u8IsMatch = FALSE;
    UINT8 u8CapMismatch = FALSE;
    /*Sink PDO Matched with received Source PDO*/
    UINT32 u32SinkSelectedPDO;    
    /*PDO Count of the sink*/
	UINT8 u8SinkPDOCnt = gasPortConfigurationData[u8PortNum].u8PDOCnt;
    /*PDO Count of the source derived from received src caps*/
	UINT8 u8Recevd_SrcPDOCnt =  PRL_GET_OBJECT_COUNT(u16RecvdSrcCapsHeader);
    UINT32 u32RcvdSrcPDO;
    UINT32 u32PDO;
    
    /*Pointer to Port Configuration Data Structure to access Sink Capability
    and Sink PD Count*/
    PORT_CONFIG_DATA *psConfigData;
    
    psConfigData = &gasPortConfigurationData[u8PortNum];

	/*Loop through each of the Sink capability and find the match with the 
    received source capability message*/
    
	for (i8SinkPDOIndex = u8SinkPDOCnt-1; i8SinkPDOIndex >= 0; i8SinkPDOIndex--)
	{
        u32PDO = psConfigData->u32PDO[i8SinkPDOIndex];
        
		for (u8SrcPDOIndex = 0; u8SrcPDOIndex < u8Recevd_SrcPDOCnt; u8SrcPDOIndex++)
		{          
            u32RcvdSrcPDO = pu32RecvdSrcCapsPayload[u8SrcPDOIndex];
                        
			u8IsMatch = DPM_Find_Src_Sink_Caps_match(u32RcvdSrcPDO,u32PDO);

			if (u8IsMatch)
			{   
                /*If the Match has ocurred and there is a mismatch in voltage between the selected 
                source PDO and Max Sink Voltage requirement*/
                if(DPM_GET_PDO_VOLTAGE(u32RcvdSrcPDO) != \
                   DPM_GET_PDO_VOLTAGE(psConfigData->u32PDO[u8SinkPDOCnt-1]) )
                {                
                    u8CapMismatch = TRUE;
                }
                
                /*Update the "u32SinkReqRDO" variable based on the received source capability*/
                /*Selected Source PDO object position is (u8SrcPDOIndex + 1)*/
                gasDPM[u8PortNum].u32SinkReqRDO = DPM_FORM_DATA_REQUEST((u8SrcPDOIndex + 1),\
                                                u8CapMismatch,DPM_GET_PDO_USB_COMM_CAP(u32PDO),\
                                                DPM_GET_PDO_CURRENT(u32PDO),\
                                                DPM_GET_PDO_CURRENT(u32PDO));
                
               /* updating the globals with Sink PDO selected */
               gasDPM[u8PortNum].u32NegotiatedPDO = u32PDO;
			   /*VBUS Threshold are configured for the requested PDO*/
			   DPM_SetPortPower (u8PortNum);							  
                return;
			}
		}
	}
    
    /*u8IsMatch will remain false if the Source and Sink PDOs does not match even for Source Vsafe5V PDO*/
    if(u8IsMatch!= TRUE)
    {
         /*Check whether PDO_1 of Source is 5V*/
         /*Else Set the RDO as 00 to denote that received source capability is invalid*/
         if(DPM_GET_PDO_VOLTAGE(pu32RecvdSrcCapsPayload[0]) == DPM_PD0_VOLTAGE_5)
         {
            u32SinkSelectedPDO = psConfigData->u32PDO[0];  
            u8CapMismatch = TRUE;

            /*Update the "u32SinkReqRDO" variable based on the received source capability*/
            /*Selected Source PDO object position is 1*/
            gasDPM[u8PortNum].u32SinkReqRDO = DPM_FORM_DATA_REQUEST(DPM_OBJECT_POSITION_1,u8CapMismatch,\
            DPM_GET_PDO_USB_COMM_CAP(u32SinkSelectedPDO),DPM_GET_PDO_CURRENT(pu32RecvdSrcCapsPayload[0]),\
            DPM_GET_PDO_CURRENT(pu32RecvdSrcCapsPayload[0]));

            /*Updating the globals with Sink PDO selected */
            gasDPM[u8PortNum].u32NegotiatedPDO = u32SinkSelectedPDO;
			/*VBUS Threshold are configured for the requested PDO*/
			DPM_SetPortPower (u8PortNum);
         
         }
         else
         {
            gasDPM[u8PortNum].u32SinkReqRDO = SET_TO_ZERO;         
         }        
    }    
	return;
}

UINT8 DPM_Find_Src_Sink_Caps_match(UINT32 u32SrcPDO, UINT32 u32SinkPDO)
{
    
    ePDOType eSrcPDOType, eSnkPDOType;
    UINT8 u8RetVal = FALSE;
           
    eSrcPDOType  = (ePDOType)DPM_GET_PDO_TYPE(u32SrcPDO);    
    eSnkPDOType = (ePDOType)DPM_GET_PDO_TYPE(u32SinkPDO);
    
	if ((eSrcPDOType == eFIXED_SUPPLY_PDO) && (eSnkPDOType == eFIXED_SUPPLY_PDO))
	{
         /* Match condition for fixed supply source PDO and fixed supply sink PDO  are 
          1. Source Fixed Voltage == Sink Fixed Voltage 
          2.Source Current >= Sink Current*/     
		if ((DPM_GET_PDO_VOLTAGE(u32SrcPDO) == DPM_GET_PDO_VOLTAGE(u32SinkPDO)) &&
			(DPM_GET_PDO_CURRENT(u32SrcPDO) >= DPM_GET_PDO_CURRENT(u32SinkPDO)))
		{
			u8RetVal = TRUE;

		}
	}   
	else
	{
         /*case 1*/
        /*Sink with Fixed Supply PDO cannot neogotiate with Source that has Battery Supply PDO*/
        /*(eSrcPDOType == eBATTERY_SUPPLY_PDO) && (SinkPDOType == eFIXED_SUPPLY_PDO)*/
        /*case 2*/
        /*Sink with Fixed Supply PDO cannot neogotiate with Source that has Variable Supply PDO*/
        /*(eSrcPDOType == eVARIABLE_SUPPLY_PDO) && (SinkPDOType == eFIXED_SUPPLY_PDO)*/
        /*case 3*/
        /*Sink with Fixed Supply PDO cannot neogotiate with Source that has Programmable power Supply PDO*/
        /*(eSrcPDOType == ePROGRAMMABLE_POWER_SUPPLY_APDO) && (SinkPDOType == eFIXED_SUPPLY_PDO)*/
		u8RetVal = FALSE;

	}
    
    return u8RetVal;
}
#endif
/********************************VCONN Related APIs**********************************************/
UINT8 DPM_Evaluate_VCONN_Swap(UINT8 u8PortNum)
{
    /*As of now, Accept the VCONN Swap without any restriction*/
    return 1;
    
}


UINT8 DPM_IsPort_VCONN_Source(UINT8 u8PortNum)
{ 
  
    UINT8 u8IsVCONNSrc;

    if(gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VCONN_SOURCE_MASK)
    {
        u8IsVCONNSrc =TRUE;
    }
    else
    {
        u8IsVCONNSrc =FALSE;
    }

    return u8IsVCONNSrc;
}

/********************************Power Fault API ******************************/

#if INCLUDE_POWER_FAULT_HANDLING

void DPM_PowerFaultHandler(UINT8 u8PortNum)
{
    
  	/* Incase detach reset the Power Fault handling variables*/
	if (((gasTypeCcontrol[u8PortNum].u8TypeCState == TYPEC_UNATTACHED_SRC) &&
		    (gasTypeCcontrol[u8PortNum].u8TypeCSubState == TYPEC_UNATTACHED_SRC_INIT_SS))||
				 ((gasTypeCcontrol[u8PortNum].u8TypeCState == TYPEC_UNATTACHED_SNK) &&
				   (gasTypeCcontrol[u8PortNum].u8TypeCSubState == TYPEC_UNATTACHED_SNK_INIT_SS)))
    {
		/* Configure PRT_CTL/OCS to detect OCS & PRT_CTL*/
		CONFIG_HOOK_DRIVE_PRTCTL_OCS(u8PortNum, CONFIG_RESET_PRTCTL_OCS_TO_DET);
		
		/* Reset Wait for HardReset Complete bit*/
		gasDPM[u8PortNum].u8HRCompleteWait = SET_TO_ZERO;
		
		/* Kill the timer*/
		PDTimer_Kill (gasDPM[u8PortNum].u8VBUSPowerGoodTimerID);
		
		/*Setting the u8VBUSPowerGoodTimerID to MAX_CONCURRENT_TIMERS to indicate that
    	TimerID does not hold any valid timer IDs anymore*/
    	gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
		
		/* Setting the power fault count to Zero */
		gasDPM[u8PortNum].u8VBUSPowerFaultCount = SET_TO_ZERO;	
        
        /*******Resetting the VCONN OCS related variables************/
        
        /*Setting VCONNGoodtoSupply flag as true*/        
        gasDPM[u8PortNum].u8VCONNGoodtoSupply = TRUE;
        
        /* Killing the VCONN power good timer*/
		PDTimer_Kill (gasDPM[u8PortNum].u8VCONNPowerGoodTimerID);
        
        /*Setting the u8VCONNPowerGoodTimerID to MAX_CONCURRENT_TIMERS to indicate that
    	TimerID does not hold any valid timer IDs anymore*/
    	gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
        
        /*Resetting the VCONN OCS fault count to Zero */
		gasDPM[u8PortNum].u8VCONNPowerFaultCount = SET_TO_ZERO;
        
        /*ISR flag for OVP,UVP,OCP,VCONN OCS is cleared by disabling the interrupt*/
		CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
		gasDPM[u8PortNum].u8PowerFaultISR = SET_TO_ZERO;
    	CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
        
	}
		
	if(gasDPM[u8PortNum].u8HRCompleteWait) 
	{ 
		if((gasPolicy_Engine[u8PortNum].ePESubState == ePE_SRC_TRANSITION_TO_DEFAULT_POWER_ON_SS) ||
				 (gasPolicy_Engine[u8PortNum].ePEState == ePE_SNK_STARTUP))
		{
            if(gasDPM[u8PortNum].u8VCONNPowerFaultCount >= CONFIG_MAX_POWER_FAULT_COUNT)
            {            
                /*Setting the VCONN Good to Supply Flag as False*/
                 gasDPM[u8PortNum].u8VCONNGoodtoSupply = FALSE;
            
            }
		    if (gasDPM[u8PortNum].u8VBUSPowerFaultCount >= CONFIG_MAX_POWER_FAULT_COUNT)
			{
				/* Disable the receiver*/
				PRL_EnableRx (u8PortNum, FALSE);
				
				/* kill all the timers*/
				PDTimer_KillPortTimers (u8PortNum);
				
				/* set the fault count to zero */
		  		gasDPM[u8PortNum].u8VBUSPowerFaultCount = SET_TO_ZERO;
				
				HOOK_DEBUG_PORT_STR (u8PortNum, "PWR_FAULT: u8HRCompleteWait Resetted ");
				
				if (DPM_GET_CURRENT_POWER_ROLE(u8PortNum) == PD_ROLE_SOURCE)
				{			
					/* Assign an idle state wait for detach*/
					gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SRC_IDLE_SS;
				}
				else
				{ 
					/* Assign an idle state wait for detach*/
					gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SNK_IDLE_SS;
				}
				
				/* Assign an idle state wait for detach*/
				gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
				
				HOOK_DEBUG_PORT_STR (u8PortNum, "PWR_FAULT: Entered SRC/SNK Powered OFF state");
			}
			
		
			/* Reset Wait for HardReset Complete bit*/
			gasDPM[u8PortNum].u8HRCompleteWait = SET_TO_ZERO;
			
			/* Configure PRT_CTL/OCS to detect OCS & PRT_CTL*/
			CONFIG_HOOK_DRIVE_PRTCTL_OCS(u8PortNum, CONFIG_RESET_PRTCTL_OCS_TO_DET);
			
		}
	}
	
	
	if (gasDPM[u8PortNum].u8PowerFaultISR)
	{
	  	HOOK_DEBUG_PORT_STR(u8PortNum, "DPM Fault Handling");
		
		/* Inform Power Fault*/
		if (DPM_NEGLECT_PWR_FAULT == (CONFIG_HOOK_NOTIFY_POWER_FAULT(u8PortNum, \
		  								&gasDPM[u8PortNum].u8PowerFaultISR)))
		{
			return;
		}
		
        /*If VCONN OCS is present , kill the VCONN power good timer*/
        if(gasDPM[u8PortNum].u8PowerFaultISR & DPM_POWER_FAULT_VCONN_OCS)
        {
            /*Kill the VCONN Power fault timer*/
            PDTimer_Kill (gasDPM[u8PortNum].u8VCONNPowerGoodTimerID);
        
             /*Setting the u8VCONNPowerGoodTimerID to MAX_CONCURRENT_TIMERS to indicate that
            TimerID does not hold any valid timer IDs anymore*/
            gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
			
			HOOK_DEBUG_PORT_STR (u8PortNum, "PWR_FAULT: VCONN Power Fault");
        }
        if(gasDPM[u8PortNum].u8PowerFaultISR & ~DPM_POWER_FAULT_VCONN_OCS)
        {       
            /* Kill Power Good Timer */
            PDTimer_Kill (gasDPM[u8PortNum].u8VBUSPowerGoodTimerID);
        
            /*Setting the u8VBUSPowerGoodTimerID to MAX_CONCURRENT_TIMERS to indicate that
            TimerID does not hold any valid timer IDs anymore*/
            gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
			
			HOOK_DEBUG_PORT_STR (u8PortNum, "PWR_FAULT: VBUS Power Fault");
        
        }
    
		if(PE_GET_PD_CONTRACT(u8PortNum) == PE_IMPLICIT_CONTRACT)
		{
			/* Set it to Type C Error Recovery */
		  	gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ERROR_RECOVERY;
		  	gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ERROR_RECOVERY_ENTRY_SS;
						
			/* Assign an idle state wait for detach*/
			gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
			
		}
		else
		{          
            if(gasDPM[u8PortNum].u8PowerFaultISR & DPM_POWER_FAULT_VCONN_OCS)
            {           
                /*Increment the VCONN fault count*/
                gasDPM[u8PortNum].u8VCONNPowerFaultCount++;
            
            }
            if(gasDPM[u8PortNum].u8PowerFaultISR & ~DPM_POWER_FAULT_VCONN_OCS)
            {
                /*Increment the fault count*/
                gasDPM[u8PortNum].u8VBUSPowerFaultCount++;            
            }
			
			/* Send Hard reset*/
			PE_SendHardResetMsg(u8PortNum);
			
			/* Set Wait for HardReset Complete bit*/
			gasDPM[u8PortNum].u8HRCompleteWait = gasDPM[u8PortNum].u8PowerFaultISR;
			
		}
        
        /* Drive Fault PRT_CTL/OCS pin low for the MCU companion to detect OCS*/
		CONFIG_HOOK_DRIVE_PRTCTL_OCS(u8PortNum, CONFIG_DRIVE_PRTCTL_OCS__LOW);
        
		/*ISR flag is cleared by disabling the interrupt*/
		CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
		gasDPM[u8PortNum].u8PowerFaultISR = SET_TO_ZERO;
    	CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
	}
}

void DPM_VCONNPowerGood_TimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable)
{
	/* Set the timer Id to Max Value*/
 	gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
	
	/* Resetting the VCONN fault Count*/
	gasDPM[u8PortNum].u8VCONNPowerFaultCount = RESET_TO_ZERO;
}
/*************************************************************/
void DPM_SetPowerFaultISR(UINT8 u8PortNum, UINT8 u8FaultSt)
{
    /* Notify DPM about the power fault*/
    gasDPM[u8PortNum].u8PowerFaultISR |= u8FaultSt;
}
#endif 

void DPM_VBUSOnOffTimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable)
{   
    gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ERROR_RECOVERY;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ERROR_RECOVERY_ENTRY_SS;
    
    gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
    gasPolicy_Engine[u8PortNum].ePESubState = ePE_INVALIDSUBSTATE;
    
    gasPolicy_Engine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
}

void DPM_SrcReadyTimerCB (UINT8 u8PortNum, UINT8 u8DummyVariable)
{
    if(gasPolicy_Engine[u8PortNum].u8PEPortSts & PE_EXPLICIT_CONTRACT)
    {
        gasPolicy_Engine[u8PortNum].ePEState = ePE_SRC_HARD_RESET;
        gasPolicy_Engine[u8PortNum].ePESubState = ePE_SRC_HARD_RESET_ENTRY_SS;
    }
    
    else
    {
        DPM_VBUSOnOffTimerCB ( u8PortNum, u8DummyVariable);
    }
    
    gasPolicy_Engine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
}

void DPM_VCONNONTimerErrorCB (UINT8 u8PortNum , UINT8 u8DummyVariable)
{
  
    gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
    gasPolicy_Engine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
    
    if(gasDPM[u8PortNum].u8VCONNErrCounter > CONFIG_MAX_VCONN_FAULT_COUNT)
    {      
        /*Disable the receiver*/
        PRL_EnableRx (u8PortNum, FALSE);
        
        /*Kill all the Port timers*/
        PDTimer_KillPortTimers (u8PortNum);
        
        /*Disable VCONN by switching off the VCONN FETS which was enabled previously*/
        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);
        
        if (DPM_GET_CURRENT_POWER_ROLE(u8PortNum) == PD_ROLE_SOURCE)
        {		          
            /*Disable VBUS by driving to vSafe0V if port role is a source*/
            TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);
        
            /*Assign an idle state to wait for detach*/
            gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SRC_IDLE_SS;
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"VCONN_ON_ERROR: Entered SRC Powered OFF state");
        }
        else
        { 
            /*Assign an idle state to wait for detach*/
            gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SNK_IDLE_SS;
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"VCONN_ON_ERROR: Entered SNK Powered OFF state");
        }
        
        
        gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
        gasPolicy_Engine[u8PortNum].ePESubState = ePE_INVALIDSUBSTATE;
        
    }
    else
    {
        gasDPM[u8PortNum].u8VCONNErrCounter++;    
        PE_SendHardResetMsg(u8PortNum);    
    }    
}


void DPM_VCONNOFFErrorTimerCB (UINT8 u8PortNum , UINT8 u8DummyVariable)
{  
    /*Set it to Type C Error Recovery */
    gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ERROR_RECOVERY;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ERROR_RECOVERY_ENTRY_SS;
    
    gasPolicy_Engine[u8PortNum].u8PETimerID = MAX_CONCURRENT_TIMERS;
    /* Assign an idle state wait for detach*/
    gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
  
}

void DPM_ResetVCONNErrorCnt (UINT8 u8PortNum)
{  
    gasDPM[u8PortNum].u8VCONNErrCounter = 0;  
}

UINT8 DPM_IsHardResetInProgress(UINT8 u8PortNum)
{

    UINT8 u8HardResetProgressStatus = ((gasPolicy_Engine[u8PortNum].u8PEPortSts & \
                                        PE_HARDRESET_PROGRESS_MASK) >> PE_HARDRESET_PROGRESS_POS);
    
    return u8HardResetProgressStatus;

}
