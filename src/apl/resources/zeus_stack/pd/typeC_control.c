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

/*Default values given in the DOS to program the CC threshold registers*/
const UINT16 au16CCThrVal[] = { TYPEC_CC_THR0_VAL, 
                                TYPEC_CC_THR1_VAL, 
                                TYPEC_CC_THR2_VAL,
                                TYPEC_CC_THR3_VAL,
                                TYPEC_CC_THR4_VAL, 
                                TYPEC_CC_THR5_VAL,
                                TYPEC_CC_THR6_VAL, 
                                TYPEC_CC_THR7_VAL
                                  
                            };

void TypeC_InitPort (UINT8 u8PortNum)
{
	UINT16 u16Data;
    UINT8 u8MatchDebVal;
    UINT8 u8VBUSDebVal;
 	
	/*Setting CC Comparator OFF*/
    TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_DIS);
    
    /*Setting VBUS Comparator OFF*/
    TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_OFF);
 
    /*Setting PM V2I Enable bit to enable the current source*/
    UPD_RegByteSetBit (u8PortNum, UPD_TRIM_ZTC_BYTE_3, UPD_PM_V2I_ENABLE);
    
    /*Setting the MATCH_DB_UNITS bit in CC_HW_CTL register*/
    UPD_RegByteSetBit (u8PortNum, TYPEC_CC_HW_CTL_HIGH, TYPEC_MATCH_DB_UNITS);
    
    /*Setting the CC_SAMP_CLK bit as 0. Sampling period will be 100us*/
	UPD_RegWriteByte (u8PortNum, UPD_CC_SAMP_CLK, \
      (UINT8) (UPD_CC_SAMP_GEN_10_KS | UPD_CC_CLK_20_KHZ));
    
    /*Setting the VBUS_DB_UNITS bit in VBUS_CTL1 register*/
    UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL1_HIGH, TYPEC_VBUS_DB_UNITS);

    /*Setting the VBUS_SAMP_CLK as 0. Sampling period will be 100us*/
	UPD_RegWriteByte (u8PortNum, UPD_VBUS_SAMP_CLK,\
                     (UINT8)(UPD_VBUS_SAMP_GEN_10_KS | UPD_VBUS_CLK_20_KHZ));
         
	/*Enabling the CC Interrupts in CC_INT_EN register (TYPEC_CC_MATCH_VLD, TYPEC_CC1_MATCH_CHG and 
    TYPEC_CC2_MATCH_CHG interrupt)*/   
    UPD_RegByteSetBit (u8PortNum,  TYPEC_CC_INT_EN,\
                      (UINT8)(TYPEC_CC1_MATCH_CHG | TYPEC_CC2_MATCH_CHG | TYPEC_CC_MATCH_VLD));	
    
    /*Enable the VBUS interrupt (VBUS_MATCH_VLD interrupt) and VCONN OCS interrupt*/
    UPD_RegByteSetBit (u8PortNum, TYPEC_PWR_INT_EN,\
                       (TYPEC_VBUS_MATCH_VLD | TYPEC_VCONN_OVER_CURR_ERR));
    
    /*Setting the UPD350 high level interrupt register for CC interrupt, VBUS interrupt and Power 
    interrupt*/
	u16Data = ((UPD_RegReadWord(u8PortNum, UPDINTR_INT_EN)) | \
	  			(UPDINTR_CC_INT | UPDINTR_VBUS_INT | UPDINTR_PWR_INT | UPDINTR_PIO_INT)) ;
	UPD_RegWriteWord (u8PortNum, UPDINTR_INT_EN, u16Data);
		
	/*Clearing the TYPEC_MODE bit will set UPD350's Operating Mode as Companion mode */
    UPD_RegByteClearBit (u8PortNum, TYPEC_CC_HW_CTL_LOW, TYPEC_MODE);
    
    /*Setting the CC threshold registers for default values given in DOS*/
    UPD_RegisterWrite (u8PortNum, TYPEC_CC_THR_BASE, (UINT8 *)au16CCThrVal, BYTE_LEN_16);
    
    /*Setting the default threshold values in VBUS VSAFE0V Threshold register*/
	UPD_RegWriteWord (u8PortNum, TYPEC_VBUS_THR_VSAFE0V, (UINT16)TYPEC_VSAFE0V_VBUS_THR);
    
    /* Setting VSinkDisconnect value in VBUS THR0*/
    UPD_RegWriteWord (u8PortNum, TYPEC_VBUS_THR0, (UINT16)TYPEC_VSINKDISCONNECT_THR);
		
	/*Setting VBUS_BLK_EN bit in VBUS Control 2 Register*/
    UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL2, TYPEC_VBUS_DEB_BLK_EN);
 
	switch (gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK)
    {
      
#if INCLUDE_PD_SOURCE_ONLY
      
        case PD_ROLE_SOURCE:
		{     
          
            /*Setting Match debounce register value as 4 times the number of thresholds enabled for 
            debouncing*/
            u8MatchDebVal = 4*TYPEC_SRC_CCTHRES_CNT;
            
            /*Setting VBUS Debounce period in VBUS Debounce Register as 2 times the number of 
            thresholds enabled for debouncing */
            u8VBUSDebVal = 4*TYPEC_SRC_VBUSTHRES_CNT;         
            					
            /*Write CCx Debounce clear enable register, CCx Match Enable register, 
            CCx sample enable register*/            
            TypeC_SetCCDebounceVariable(u8PortNum, ((gasPortConfigurationData[u8PortNum].u32CfgData & \
                                       TYPEC_PORT_RPVAL_MASK) >> TYPEC_PORT_RPVAL_POS));
            
            /*Setting Port Role as DFP in TYPEC_CC_HW_CTL register*/
            TypeC_SetDataRole (u8PortNum,PD_ROLE_DFP);
                         
            /*Setting Rp Current Source as user given and Rd as Open disconnect in both CC1 and 
            CC2*/ 
            u16Data = ((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_RPVAL_MASK)\
                      >> TYPEC_PORT_RPVAL_POS);
            
            /*Setting the Power role as Source*/
            TypeC_SetPowerRole (u8PortNum, TYPEC_ROLE_SOURCE, (UINT8) u16Data);
            
            /*Settting the Current Rp value status in u8PortSts variable as user given Rp value*/
            gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_CURR_RPVAL_MASK;
            gasTypeCcontrol[u8PortNum].u8PortSts  |= (u16Data << TYPEC_CURR_RPVAL_POS);
            
            /*Setting the Initial State and Substate for Source*/
            gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SRC;
            gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SRC_INIT_VSAFE0V_SS;  
            
            break;
        }
            
#endif
/*INCLUDE_PD_SOURCE_ONLY*/

#if INCLUDE_PD_SINK_ONLY
			
		case PD_ROLE_SINK:
		{          
            /*Setting Match debounce register value as 4 times the number of thresholds enabled 
            for debouncing*/
            u8MatchDebVal = 4*TYPEC_SNK_CCTHRES_CNT;
            
            /*Setting VBUS Debounce period in VBUS Debounce Register as as 2 times the number of 
            thresholds enabled for debouncing */
            u8VBUSDebVal = 4*TYPEC_SNK_VBUSTHRES_CNT;
          
            /*Setting Port Role as UFP in TYPEC_CC_HW_CTL register */
            TypeC_SetDataRole (u8PortNum,PD_ROLE_UFP);
           
            /*Setting the Rd Value */ 
            TypeC_SetPowerRole (u8PortNum,TYPEC_ROLE_SINK, TYPEC_ROLE_SINK_RD);

            TypeC_SetCCDebounceVariable(u8PortNum, TYPEC_UFP); 
           
            /*Setting the Initial State and Substate for Sink*/
            gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SNK;
            gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_ENTRY_SS; 
            
            break;
         }
           
#endif
/*INCLUDE_PD_SINK_ONLY*/
			
		default:
		break;  
	}

    /*Setting Match debounce register */
    UPD_RegisterWrite (u8PortNum, TYPEC_MATCH_DEB, &u8MatchDebVal, BYTE_LEN_1);	
    
    /*Setting VBUS Debounce period in VBUS Debounce Register*/
    UPD_RegisterWrite (u8PortNum, TYPEC_VBUS_DEB, &u8VBUSDebVal, BYTE_LEN_1);
    
    /*Setting the CC Debounce register to detect both the sink and powered cable on CC1 and CC2*/
    TypeC_SetCCSampleEnable (u8PortNum,(TYPEC_ENABLE_CC1_SAMPLING | TYPEC_ENABLE_CC2_SAMPLING));
  
    /*Setting VCONN Debounce register for 2ms as given in DOS*/
    UPD_RegWriteByte (u8PortNum, TYPEC_VCONN_DEB, TYPEC_VCONN_DEBOUNCE);
     
    
    /*Setting VBUS Debounce enable clear register and VBUS Match Enable Register */
	u16Data = (TYPEC_VBUS_VSAFE0V_MATCH | TYPEC_VBUS_THRES0_MATCH | TYPEC_VBUS_THRES1_MATCH |\
                    TYPEC_VBUS_THRES2_MATCH | TYPEC_VBUS_THRES3_MATCH | TYPEC_VBUS_THRES4_MATCH);
	UPD_RegisterWrite (u8PortNum, TYPEC_VBUS_MATCH_EN, (UINT8*)&u16Data, BYTE_LEN_1);
	UPD_RegisterWrite (u8PortNum, TYPEC_VBUS_DBCLR_EN,	(UINT8*)&u16Data, BYTE_LEN_1);
    
	/*Setting VBUS Comparator ON*/
    TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_ON);
	
    /*Setting CC Comparator ON*/
    TypeC_ConfigCCComp (u8PortNum,TYPEC_CC_COMP_CTL_CC1_CC2);
    
    /*Setting the Power Module as per the port role*/
    if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK)== PD_ROLE_SOURCE)
    {
        /*Setting the VBUS to vSafe0V before entering the State machine*/
        TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);

        /*Setting the VBUS Discharge ON*/
        CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
    }
    else
    {
        /* Enable threshold to detect 5V*/
        TypeC_ConfigureVBUSThr(u8PortNum, PWRCTRL_VBUS_5V, TYPEC_CONFIG_NON_PWR_FAULT_THR);
        
        /*Disable the Sink circuitry to stop sinking the power from source*/
        CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(u8PortNum, PWRCTRL_DISABLE_SINK_HW);
      
    }
    
    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: TypeC Port initilization Done\r\n");             
    
}


void TypeC_RunStateMachine (UINT8 u8PortNum)
{

#ifdef CONFIG_HOOK_DEBUG_MSG
    UINT32 u32PDODebug = SET_TO_ZERO;
#endif
    
    UINT8 u8CC1_MatchISR = SET_TO_ZERO;
    UINT8 u8CC2_MatchISR  = SET_TO_ZERO;
    UINT8 u8IntStsISR = SET_TO_ZERO;
    
    TypeC_CCVBUSIntrHandler (u8PortNum);
    
    CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();

    u8CC1_MatchISR = gasTypeCcontrol[u8PortNum].u8CC1_MatchISR;
    u8CC2_MatchISR = gasTypeCcontrol[u8PortNum].u8CC2_MatchISR;
    u8IntStsISR = gasTypeCcontrol[u8PortNum].u8IntStsISR;

    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
    
    switch (gasTypeCcontrol[u8PortNum].u8TypeCState)
    {      
      /*-----------------------------------------TypeC Source States------------------------------*/
      
#if INCLUDE_PD_SOURCE_ONLY
      
        case TYPEC_UNATTACHED_SRC:
        {          
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		    {
                case TYPEC_UNATTACHED_SRC_INIT_VSAFE0V_SS:
                {
                    /* Check for VBUS VSafe0V for Voltage driven in TypeC Initialization */
                    if (TYPEC_VSAFE_0V_MATCH_VAL == UPD_RegReadByte(u8PortNum, TYPEC_VBUS_MATCH))
                    {
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_UNATTACHED_SRC_ENTRY_SS;
                        CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_DISABLE_VBUSDIS);
                    }
                    break;
                }
                
                case TYPEC_UNATTACHED_SRC_ENTRY_SS:
                {   
                     
                     /*Notify external DPM of Type Detach event through a user defined call back*/
                     CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_DETACH_EVENT);
                     
                    /* Disable the receiver*/
                    PRL_EnableRx (u8PortNum, FALSE);
                     
                    UINT16 u16Data = ((gasPortConfigurationData[u8PortNum].u32CfgData & \
                                      TYPEC_PORT_RPVAL_MASK) >> TYPEC_PORT_RPVAL_POS);
					 
					/*Reset the VBUS threshold for 5V detection*/
					TypeC_ConfigureVBUSThr(u8PortNum, PWRCTRL_VBUS_5V, TYPEC_CONFIG_NON_PWR_FAULT_THR);
					
					 /*Power down the CC comparator*/
					TypeC_ConfigCCComp(u8PortNum, TYPEC_CC_COMP_CTL_DIS);
                     
                    /*Check whether the current Rp value is same as the default Rp value*/
                    if(((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_CURR_RPVAL_MASK) \
                        >> TYPEC_CURR_RPVAL_POS)!= u16Data)
                    {   
                        
                        /*Setting the user given Rp value since it is changed by collision 
                        avoidance*/
                        TypeC_SetDefaultRpValue (u8PortNum);
                                                 
                        HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: RP Value of Source set to"\
                                             "User given Value\r\n");                       
                    }
					
					/*Set the CC Comparator to sample both CC1 and CC2*/
              		TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1_CC2); 
					
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_UNATTACHED_SRC: Entered UNATTACHED"\
                                         "SRC State\r\n");
		
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_UNATTACHED_SRC_INIT_SS;                    
                   
                    break;
                }
				
				case TYPEC_UNATTACHED_SRC_INIT_SS:
				{
                    /*DPM power fault handler resets SM by polling this state TYPEC_UNATTACHED_SRC_INIT_SS
                    in the hanlder for Src unattach.
                    Any module can reset its reset its SM by polling this state*/                       
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_UNATTACHED_SRC_IDLE_SS;
                    
					break;
				}
              
                /*Source waits in this substate for sink attachment*/
                case TYPEC_UNATTACHED_SRC_IDLE_SS:
                    break; 
                    
                default:
                    break;
                    
            } 
            break;                
        }  
            
        
        case TYPEC_ATTACHWAIT_SRC:
        {
          
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		    {
                /*This SubState is used to start a tCCDebounce timer for Sink attachment*/
                case TYPEC_ATTACHWAIT_SRC_DEB_SS:
                {
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHWAIT_SRC: Entered ATTACHWAIT "\
                                                                              "SRC State\r\n");
                    
                    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                                      (CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS),\
                                                      TypeC_SubStateChange_TimerCB, u8PortNum,\
                                                      TYPEC_ATTACHWAIT_SRC_TCC_TO_SS);
                   
				    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHWAIT_SRC_IDLE_SS;
                    
                    break;
                }   
                    
                    
                /*Source waits in this substate until the tCCDebounce timer timeouts*/
                case TYPEC_ATTACHWAIT_SRC_IDLE_SS:
                    break;
                
                /*Source enters this substate after the tCCDebounce timer timeouts*/
                case TYPEC_ATTACHWAIT_SRC_TCC_TO_SS:
                {
                  
                    /*VBUS should be at vSafe0V before transition to AttachedSRC State*/
                    /*Check for VBUS Absence before moving to Attached SRC state */
                    if ((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) == (TYPEC_VBUS_0V))
                    {
#ifdef CONFIG_HOOK_DEBUG_MSG
                        u32PDODebug = 0;
                        HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
#endif                       
                        if ((u8CC1_MatchISR == u8CC2_MatchISR))
                        {
                            /*Ra is present on both CC lines*/
                            if (u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCDebMatch)
                            {
                                gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_AUDIO_ACCESSORY; 
                            }
                            /*Rd is present on both CC lines*/
                            else
                            {
                                gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNORIENTED_DEBUG_ACCESSORY_SRC;
                            }              
                        }
                        /*Rd is present on either CC1 or CC2 line and Ra may be present on either CC1 or CC2 line*/
                        else
                        {
                             gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ATTACHED_SRC;
                             gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SRC_DRIVE_PWR_SS;      
                        }
                        
						CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_DISABLE_VBUSDIS);
                    }
                    break;
                }
                    
                default:
                    break;
             }
             break;
        }
            
        case TYPEC_ATTACHED_SRC:
        {
          
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState)
		    {   
                /*Source Drives VBUS and VCONN required in this substate*/
                case TYPEC_ATTACHED_SRC_DRIVE_PWR_SS:
                {
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHED_SRC: Entered ATTACHED"\
                                         "SRC State\r\n");
                    
                   /*Notify external DPM of Type Attach event through a user defined call back*/
                   CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_ATTACHED_SRC_DRIVE_PWR_EVENT);
                   
                    /*Drive VBus for vSafe5V*/
                    TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_5V);
                    
                    /*Start the VBUS ON timer for monitoring the time taken for 
                    power module to reach Vsafe5V*/
                    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID =PDTimer_Start (
                                                              (CONFIG_TYPEC_VBUS_ON_TIMER_MS),
                                                              DPM_VBUSOnOffTimerCB, u8PortNum,  
                                                              (UINT8) NULL);
					
					 /*Sink Attached in CC1 pin*/
					if(u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch)
					{
						UPD_RegByteClearBit (u8PortNum, TYPEC_CC_CTL1_HIGH, TYPEC_CC_COM_SEL); 
					}
					/*Sink attached in CC2*/
					else
					{
						UPD_RegByteSetBit (u8PortNum, TYPEC_CC_CTL1_HIGH, TYPEC_CC_COM_SEL);
					}
		   
                    /*Enable VCONN FETs if Powered cable is present*/
                    if (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_PWDCABLE_PRES_MASK)
                    {                                        
                        /*Powered cable attached in CC1*/
                        if (u8CC1_MatchISR > u8CC2_MatchISR)
                        {                    
                           
                            HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHED_SRC_VCONN_CC1: VCONN"\
                                                 "Enabled in CC1\r\n");                                                            
                        }
                        /*Powered cable attached in CC2*/
                        else
                        {
                             
                            HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHED_SRC_VCONN_CC2: VCONN"\
                                                 "Enabled in CC2\r\n");                                                
                        }
                        
                        /*Enable VCONN for powered cable attached in CC1 or CC2 line */
                        TypeC_EnabDisVCONN(u8PortNum, TYPEC_VCONN_ENABLE);
               
                    }

                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SRC_CHECK_VBUS_SS;
                   
                                     
                   break;
                }
                
                case TYPEC_ATTACHED_SRC_CHECK_VBUS_SS:
                {   
                    if((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) == (TYPEC_VBUS_5V))
                    {
                      
#ifdef CONFIG_HOOK_DEBUG_MSG
                        switch((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_CURR_RPVAL_MASK) >> TYPEC_CURR_RPVAL_POS)
                        {
                            case TYPEC_DFP_DEFAULT_CURRENT:
                            {
                                u32PDODebug = DPM_DEBUG_PDO_5V_9MA;
                                break;  
                            }

                            case TYPEC_DFP_1A5_CURRENT:
                            {
                                u32PDODebug = DPM_DEBUG_PDO_5V_1P5A;
                                break;  
                            }

                            case TYPEC_DFP_3A0_CURRENT:
                            {
                                u32PDODebug = DPM_DEBUG_PDO_5V_3A;
                                break;
                                
                            }
                            
                        }
						
						HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
#endif
                        
                        /*Kill the VBUS ON timer since Vsafe5V is reached*/
                        TypeC_KillTypeCTimer (u8PortNum);
                                                              
                        if (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_PWDCABLE_PRES_MASK)
                        {

                            /*Start the VCONN ON timer for monitoring the time taken for 
                            VCONN to reach its Min value*/
                            /*Failure to reach the VCONN Min will result in Error Recovery state*/
                            gasTypeCcontrol[u8PortNum].u8TypeC_TimerID =PDTimer_Start (
                                                         CONFIG_TYPEC_VCONNON_TIMEOUT_MS,
                                                          TypeC_VCONNONErrorTimerCB, u8PortNum,  
                                                          (UINT8) NULL);
                            
                            gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SRC_CHECK_VCONNON_SS; 

                        }
                        else
                        {

                            gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SRC_SET_PRL_SS;

                        }
                       
                    }
                    break;
                }
               
                case TYPEC_ATTACHED_SRC_CHECK_VCONNON_SS:
                {
                          
                    if(u8IntStsISR & TYPEC_VCONN_SOURCE_MASK)
                    {                      
                          /*Kill the VCONN ON timer since VCONN is turned ON*/
                          TypeC_KillTypeCTimer (u8PortNum); 
                          
                          gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SRC_SET_PRL_SS; 
                    
                    }              
                    break;
                }
                
                case TYPEC_ATTACHED_SRC_SET_PRL_SS:
                {                  
                     /*Sink Attached in CC1 pin*/
                      if(u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch)
                       {
                           CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_CC1_ORIENTATION);
                       }
                       /*Sink attached in CC2*/
                       else
                       {
                           CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_CC2_ORIENTATION);
                       }
               
                       /* Enabling PRL Rx*/
                       PRL_EnableRx(u8PortNum,true);                  
               
                       /*Test code for Collision avoidance*/
                       /*Real Scenario can be simulated by having a break point at this line */
                       /*TypeC_SetRpCollAvoidance(u8PortNum,TYPEC_SINK_TXOK);*/
                     
                       /*Notify external DPM of Type Attach event through a user defined call back*/
                       CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_ATTACH_EVENT);
                       
                       /* Enable Power Threshold for PWRCTRL_VBUS_5V */
                       TypeC_ConfigureVBUSThr(u8PortNum, PWRCTRL_VBUS_5V, TYPEC_CONFIG_PWR_FAULT_THR);
                     
                       gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SRC_RUN_SM_SS;
                       
                       break;
                  
                }
                             
                case TYPEC_ATTACHED_SRC_RUN_SM_SS:
				case TYPEC_ATTACHED_SRC_IDLE_SS:
                    break;
                    
                default:
                    break;
                
            }
            break;
      }
           
      case TYPEC_UNATTACH_WAIT_SRC:
      {
        
        switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		{   
            /*This SubState is used to start a tPDDeounce Software timer for sink detach event*/         
            case TYPEC_UNATTACH_WAIT_SRC_ENTRY_SS:
            {    
                
                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_UNATTACH_WAIT_SRC: Entered UNATTACHED WAIT"\
                                     "SRC State\r\n"); 
                
                /*Kill all the timers for a port before starting a Type C Debounce timer*/
                PDTimer_KillPortTimers(u8PortNum);
                
                /* Start a Debounce timer of tPDDebounce for detach event*/
                gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                                  (CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS),\
                                                  TypeC_SubStateChange_TimerCB, u8PortNum,\
                                                  TYPEC_UNATTACH_WAIT_SRC_TPD_TO_SS);
                
                gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACH_WAIT_SRC_IDLE_SS;
                
                break;
            }    
            
            /*Source enters this SubState after the tPDDeounce Software timer expires*/  
            case TYPEC_UNATTACH_WAIT_SRC_TPD_TO_SS:
            {    
                /*Disable VBUS by driving to vSafe0V*/
                TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);
                
               /*Start the VBUS OFF timer for monitoring the time taken for 
                power module to reach Vsafe0V*/
                gasTypeCcontrol[u8PortNum].u8TypeC_TimerID =PDTimer_Start (
                                                              (CONFIG_TYPEC_VBUS_OFF_TIMER_MS),
                                                              DPM_VBUSOnOffTimerCB, u8PortNum,  
                                                              (UINT8) NULL);
				
                CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
                 
                /*Enabling the VCONN Discharge if we are supplying VCONN or VCONN Req was ON*/
                if(((u8IntStsISR & TYPEC_VCONN_SOURCE_MASK) \
                   != TYPEC_VCONN_DISABLED) || (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN_ON_REQ_MASK))
                {                       
                    /*Disable VCONN by switching off the VCONN FETS*/
                    TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);
                    
                    /*Clearing the VCONN ON Request mask if VCONN has turned ON*/
                    gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
                    
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACH_WAIT_SRC_IDLE_SS;
                }
                else
                {
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACH_WAIT_SRC_CHECK_VBUS_0V_SS;
                }
                
                break;
            }
                                
            /*Source waits in this SubState until the tPDDeounce Software timer expires or the VCONN
            Discharge is completed*/    
            case TYPEC_UNATTACH_WAIT_SRC_IDLE_SS:
                break;
             
            /*Wait in this substate until the VBUS goes to 0V before moving into Unattached state*/
            case TYPEC_UNATTACH_WAIT_SRC_CHECK_VBUS_0V_SS:
            {
                if((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) == (TYPEC_VBUS_0V))
                {
#ifdef CONFIG_HOOK_DEBUG_MSG
                    u32PDODebug = 0;
                    HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
#endif
                    /*Kill the VBUS ON timer since Vsafe0V is reached*/
                    TypeC_KillTypeCTimer (u8PortNum);
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SRC_ENTRY_SS;
                    gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SRC;
                }
            }
              break;
                
            default:
                break;
        }
            break;
      }
        
        case TYPEC_UNORIENTED_DEBUG_ACCESSORY_SRC:      
            break;

#endif
/*INCLUDE_PD_SOURCE_ONLY*/
        
       /*-----------------------------------------TypeC Sink States-------------------------------*/
#if INCLUDE_PD_SINK_ONLY
        
       case TYPEC_UNATTACHED_SNK:
       {          
           switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		   {             
                case TYPEC_UNATTACHED_SNK_ENTRY_SS: 
                {                    
                    PRL_EnableRx (u8PortNum,false);
                    
                    /*Notify external DPM of Type Detach event through a user defined call back*/
                    CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_DETACH_EVENT);
                   
                    HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC_UNATTACHED_SNK: Entered"\
                                        "UNATTACHED SNK State\r\n");
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_VSAFE0V_WAIT_SS;
                    break;
                }
                
                case TYPEC_UNATTACHED_SNK_VSAFE0V_WAIT_SS:
                {
                    if((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) == (TYPEC_VBUS_0V))
                    {
                      
#ifdef CONFIG_HOOK_DEBUG_MSG
                        u32PDODebug = 0;
                        HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
#endif 
                        /* Configure VBUS threshold to detect 5V*/
                        TypeC_ConfigureVBUSThr(u8PortNum, PWRCTRL_VBUS_5V, TYPEC_CONFIG_NON_PWR_FAULT_THR); 
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_INIT_SS; 
                    }
                    break;
                }
				
		   		case TYPEC_UNATTACHED_SNK_INIT_SS:
				{
                    /*DPM power fault handler resets SM by polling this state TYPEC_UNATTACHED_SNK_INIT_SS
                    in the hanlder for Sink unattach.
                    Any module can reset its reset its SM by polling this state*/
				  	gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_IDLE_SS;                    
					break;
				}
                                   
                /*Sink Waits in this Substate for Source attachment*/    
                case TYPEC_UNATTACHED_SNK_IDLE_SS:
                    break;
                    
                default:
                    break;           
            }          
            break;
       }
          
        case TYPEC_ATTACHWAIT_SNK:
        {
          
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		    {   
                /*This SubState is used to start a tCCDebounce Software timer for Source attachment*/ 
                case TYPEC_ATTACHWAIT_SNK_TCCDEB_SS:
                {                  
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHWAIT_SNK: Entered"\
                                         "ATTACHWAIT SNK State\r\n");                  
                    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                                      (CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS),\
                                                      TypeC_SubStateChange_TimerCB, u8PortNum,\
                                                      TYPEC_ATTACHWAIT_SNK_TCC_TO_SS);
                    
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHWAIT_SNK_IDLE_SS; 
                    
                    break;
                }
                   
                    
                /*Sink Waits in this substate until either the tCCDebounce or tPDDebounce timer 
                expires */
                case TYPEC_ATTACHWAIT_SNK_IDLE_SS:
                    break;
                    
                /*This SubState is used to start a tPDDebounce Software timer for Source detachment*/ 
                case TYPEC_ATTACHWAIT_SNK_TPDDEB_SS:
                {                  
                    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                                      (CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS),\
                                                      TypeC_StateChange_TimerCB, u8PortNum,\
                                                      TYPEC_UNATTACHED_SNK);
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHWAIT_SNK_IDLE_SS;
                    
                    break;
                }
                    
                
                /*Sink enters this substate after the tCCDebounce timer is expired */
                case TYPEC_ATTACHWAIT_SNK_TCC_TO_SS:
                {                  
                    /*Check for VBUS Presence before moving to Attached SNK state */
                    if((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) == (TYPEC_VBUS_5V))
                    {
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_ENTRY_SS;
                        gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ATTACHED_SNK;                    
                    }
                    
                    break;
                }
                   
                
                default:
                    break;  
             }
            break;
        }
            
        case TYPEC_ATTACHED_SNK:
        {          
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState )
		    {
                 /*Sink enables the CC Communication channel and notifies the external DPM
                 about the Type C Attached event this substate */
                case TYPEC_ATTACHED_SNK_ENTRY_SS:
                {
#ifdef CONFIG_HOOK_DEBUG_MSG
                    switch((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_CURR_RPVAL_MASK) >> TYPEC_CURR_RPVAL_POS)
                    {
                        case TYPEC_DFP_DEFAULT_CURRENT:
                        {
                            u32PDODebug = DPM_DEBUG_PDO_5V_9MA;
                            break;  
                        }
                        
                        case TYPEC_DFP_1A5_CURRENT:
                        {
                            u32PDODebug = DPM_DEBUG_PDO_5V_1P5A;
                            break;  
                        }
                        
                        case TYPEC_DFP_3A0_CURRENT:
                        {
                            u32PDODebug = DPM_DEBUG_PDO_5V_3A;
                            break;  
                        }
                    }
                    
#endif                 
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ATTACHED_SNK: Entered"\
                                         "ATTACHED SNK State\r\n");
#ifdef CONFIG_HOOK_DEBUG_MSG                    
                    HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
#endif                    
                    /*Source Attached in CC1 pin*/
					if (u8CC1_MatchISR > u8CC2_MatchISR)
					{
                        UPD_RegByteClearBit (u8PortNum, TYPEC_CC_CTL1_HIGH, TYPEC_CC_COM_SEL);
                        CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_CC1_ORIENTATION);
                        
					}
                    /*Source Attached in CC2 pin*/
					else
					{
						UPD_RegByteSetBit (u8PortNum, TYPEC_CC_CTL1_HIGH, TYPEC_CC_COM_SEL);
                        CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_CC2_ORIENTATION);
					}

                    /*Enable the Sink circuitry to start sinking the power from source*/
                    CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(u8PortNum, PWRCTRL_ENABLE_SINK_HW);
                                       
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_RUN_SM_SS; 
                    
					/* Enabling PRL Rx*/
					PRL_EnableRx (u8PortNum,true);
					
                    /*Testing Code*/
					/*This API will simulate the PRL layer which will call the below
					API while Starting a new AMS */ 					
                   /* TypeC_CheckRpValCollAvoidance(0);*/
                    
                   /*Notify external DPM of Type Attach event through a user defined call back*/
                   CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(u8PortNum, TYPEC_ATTACH_EVENT);
				   
				   /* Enable Power Threshold for PWRCTRL_VBUS_5V */
					TypeC_ConfigureVBUSThr(u8PortNum, PWRCTRL_VBUS_5V, TYPEC_CONFIG_PWR_FAULT_THR);
                   
                   break;
                }
                
                case TYPEC_ATTACHED_SNK_RUN_SM_SS:	
                    break;
                
                /*Sink enters this substate to start a tPDDeounce timer for source detach event*/
                case TYPEC_ATTACHED_SNK_TPDDEB_SS:
                {
                    /*Kill all the timers for a port before starting a Type C Debounce timer*/
                    PDTimer_KillPortTimers(u8PortNum);
                    
                    /* Start a Debounce timer of tPDDebounce for detach event*/
                    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                                       (CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS),\
                                                       TypeC_SubStateChange_TimerCB, u8PortNum,\
                                                       TYPEC_ATTACHED_SNK_TPD_TO_SS);
                    
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_IDLE_SS; 
                    
                    break;
                }
                   
                
                /*Sink enters this substate after the tPDDeounce timer is expired or VBUS drops below 
                VSinkDisconnect*/
                case TYPEC_ATTACHED_SNK_TPD_TO_SS:
                {    
                     
                    /*Disable the Sink circuitry to stop sinking the power from source*/
                    CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(u8PortNum, PWRCTRL_DISABLE_SINK_HW);
                     
                    if((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) != (TYPEC_VBUS_0V))
                    {
                        /*Enabling the VBUS discharge functionality for VBUS to go to Vsafe0V*/                  
                        CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
                    }

                    /*Enabling the VCONN Discharge if we are supplying VCONN or VCONN ON Req is set*/
                    if(((u8IntStsISR & TYPEC_VCONN_SOURCE_MASK) \
                       != TYPEC_VCONN_DISABLED) || \
                       (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN_ON_REQ_MASK))
                    {                       
                        /*Disable VCONN by switching off the VCONN FETS*/
                        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);
                        
                        /*Clearing the VCONN ON Request mask if VCONN has turned ON*/
                        gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
                        
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_IDLE_SS;
                    }
                    else
                    {
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_SET_UNATTACHED_SS;
                    }
                    break;
                    
                }
                
                case TYPEC_ATTACHED_SNK_SET_UNATTACHED_SS:
                {                                                             
                    gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SNK;
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_ENTRY_SS;
                    break;
                } 
                
                /*Sink waits in this substate until the tPDDeounce timer expires or until the VCONN 
                Discharge is completed*/
                case TYPEC_ATTACHED_SNK_IDLE_SS:                  
                    break;
                
                default:
                    break;  
            }
            break;
        }
        case TYPEC_DEBUG_ACCESSORY_SNK:         
            break;     

#endif
/*INCLUDE_PD_SINK_ONLY*/
          
        case TYPEC_ERROR_RECOVERY:
        {
         
            switch (gasTypeCcontrol[u8PortNum].u8TypeCSubState)
            {
                /*In this SubState, VBUS and VCONN are disabled.Pull down and Pull up resisters
                are set to open disconnect*/
                case TYPEC_ERROR_RECOVERY_ENTRY_SS:
                {
                  
                    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC_ERROR_RECOVERY: Entered"\
                                         "ERROR RECOVERY State\r\n"); 
                    
                    /* Disable the receiver*/
                    PRL_EnableRx (u8PortNum, FALSE);
                    
                    /*Setting CC Comparator OFF*/
                    TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_DIS);
                    
                    if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK)== PD_ROLE_SOURCE)
                    {                    
                        /*Disable VBUS by driving to vSafe0V*/
                        TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);
                    
                        CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);                       
                        
                        /*Setting the CC1 and CC2 line as Open Disconnect*/
                        TypeC_SetPowerRole (u8PortNum, PD_ROLE_SOURCE, TYPEC_ROLE_SOURCE_OPEN_DIS); 
                    
                    }
                    else
                    {
                        /*Disable the Sink circuitry to stop sinking the power from source*/
                        CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(u8PortNum, PWRCTRL_DISABLE_SINK_HW);
                        
                         /*Setting the CC1 and CC2 line as Open Disconnect*/
                        TypeC_SetPowerRole (u8PortNum,PD_ROLE_SINK, TYPEC_ROLE_SINK_OPEN_DIS);
                    
                    }
                    
                    /*Disable VCONN if the port sources the VCONN already or failed while trying to
                    source VCONN*/
                    if (((u8IntStsISR & TYPEC_VCONN_SOURCE_MASK) \
                        != TYPEC_VCONN_DISABLED) || (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN_ON_REQ_MASK))
                    {
                        /*Clearing the VCONN ON Request mask if VCONN has turned ON*/
                        gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;

                        /*Disable VCONN by switching off the VCONN FETS*/
                        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);
                    }
                  
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ERROR_RECOVERY_WAIT_FOR_VCONN_DIS_SS;
                 
                    break;
                }

                case TYPEC_ERROR_RECOVERY_WAIT_FOR_VCONN_DIS_SS:
                { 
                  
                    if(!(u8IntStsISR & TYPEC_VCONN_SOURCE_MASK))
                    {
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ERROR_RECOVERY_WAIT_FOR_VBUS_0V_SS;
                    
                    }
                    break;
                }
                
                case TYPEC_ERROR_RECOVERY_WAIT_FOR_VBUS_0V_SS:
                {
                    if(((u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK) \
                         == TYPEC_VBUS_0V))
                    {
                #ifdef CONFIG_HOOK_DEBUG_MSG
                        u32PDODebug = 0;
                        HOOK_DEBUG_BUF_UINT32( u8PortNum, "PDPWR", &u32PDODebug, 1, "\r\n");
                #endif                   
                        /*Setting VBUS Comparator OFF once the VBUS line goes off to 0V*/
                        TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_OFF);
                        
                        gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = PDTimer_Start ( \
                                  (CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS),\
                                  TypeC_SubStateChange_TimerCB, u8PortNum,\
                                  TYPEC_ERROR_RECOVERY_TO_SS);
                        
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ERROR_RECOVERY_IDLE_SS;
                    
                    }
                    break;
                }

                /*Device waits in this substate until the tErrorRecovery software timer expires*/
                case TYPEC_ERROR_RECOVERY_IDLE_SS:                  
                    break;

                /*Device enters this substate after the tErrorRecovery software timer is expired*/
                case TYPEC_ERROR_RECOVERY_TO_SS: 
                {    
                    
                    /*Resetting the Port Power Role*/
                    if ((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK) \
                        == PD_ROLE_SOURCE)
                    {                      
                        UINT8 u8Data;
                        
                        /*Setting Rp Current Source as user given and Rd as Open disconnect in both 
                        CC1 and CC2*/ 
                        u8Data = ((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_RPVAL_MASK) \
                                  >> TYPEC_PORT_RPVAL_POS);            
                        TypeC_SetPowerRole  (u8PortNum, TYPEC_ROLE_SOURCE, u8Data);
                        
                        gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SRC;
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SRC_ENTRY_SS; 
                    }
                    else
                    {
                        TypeC_SetPowerRole(u8PortNum,TYPEC_ROLE_SINK, TYPEC_ROLE_SINK_RD);                    
                        gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SNK;
                        gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_UNATTACHED_SNK_ENTRY_SS; 
                    }
                    
                    /*Setting CC Comparator ON*/
                    TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1_CC2);   
                    /*Setting VBUS Comparator ON*/
                    TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_ON);                         
                    break;                   
                }                    

                default:
                    break;  

            }
            break; 
        }
	  
        case TYPEC_AUDIO_ACCESSORY:
            break;
              
      default:
      break;
    }
  
}

void TypeC_SetCCDebounceVariable(UINT8 u8PortNum, UINT8 u8Pwrrole)
{
    UINT8 u8CCDebMatch = gasTypeCcontrol[u8PortNum].u8CCDebMatch;
    UINT8 u8CCSrcSnkMatch = gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch;
    
    switch (u8Pwrrole)
    {
      
        case TYPEC_UFP:
        {
          /* UFP_DFP_DEF (CC_THR0) ,UFP_DFP_1A5(CC_THR2), UFP_DFP_3A0 (CC_THR4) */ 
            u8CCDebMatch = (TYPEC_CC_THRES0_MATCH | TYPEC_CC_THRES2_MATCH \
                                                       | TYPEC_CC_THRES4_MATCH | TYPEC_CC_THRES7_MATCH); 
            /*u8CCSrcSnkMatch variable will be set depending on the type of Source Rp attached
            TypeC_DecodeSourceRpValue(u8PortNum); function*/
            break;
        }
        case TYPEC_DFP_DEFAULT_CURRENT:
        {
          
            /*DFP_ACT_DEF(CC_THR0),DFP_UFP_DEF(CC_THR5)*/
            u8CCDebMatch = (TYPEC_CC_THRES0_MATCH | TYPEC_CC_THRES5_MATCH); 
            
            /*u8CCSrcSnkMatch is useful for finding which CC line has Sink attachment*/
            u8CCSrcSnkMatch = (TYPEC_CC_THRES5_MATCH); 
            break;
        }
        
        case TYPEC_DFP_1A5_CURRENT:
        {
            /*DFP_ACT_1A5(CC_THR1),DFP_UFP_1A5(CC_THR5)*/
            u8CCDebMatch = (TYPEC_CC_THRES1_MATCH | TYPEC_CC_THRES5_MATCH);
            
            /*u8CCSrcSnkMatch is useful for finding which CC line has Sink attachment*/
            u8CCSrcSnkMatch = (TYPEC_CC_THRES5_MATCH); 
            break;
        }
        
        case TYPEC_DFP_3A0_CURRENT:
        {
            /*DFP_ACT_3A0 (CC_THR3),DFP_UFP_3A0 (CC_THR6)*/
            u8CCDebMatch = (TYPEC_CC_THRES3_MATCH | TYPEC_CC_THRES6_MATCH);
            
            /*u8CCSrcSnkMatch is useful for finding which CC line has Sink attachment*/
            u8CCSrcSnkMatch = (TYPEC_CC_THRES6_MATCH); 
            break;
        }
        
        default:
            break; 
    }
    
    gasTypeCcontrol[u8PortNum].u8CCDebMatch = u8CCDebMatch;
    gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch = u8CCSrcSnkMatch;

}

void TypeC_HandleISR (UINT8 u8PortNum, UINT16 u16InterruptStatus)
{
    UINT8 u8Data;
    UINT16 u16Data;
    UINT8 vbus_match_valid_received = 0;
    
    UINT8 u8IntStsISR = gasTypeCcontrol[u8PortNum].u8IntStsISR;
     
    /*Check for CC Change interrupt*/
	if (u16InterruptStatus & UPDINTR_CC_INT)
	{			       
        UPD_RegisterReadISR (u8PortNum, TYPEC_CC_INT_STS, &u8Data, BYTE_LEN_1);
         
		if (u8Data & TYPEC_CC_MATCH_VLD)
		{
            /*Clearing the CC Match valid interrupt */
            /*This Interrupt is usually ocurred while switching on the CC Comparator
            and Comparator has finished one round of sampling*/
			UPD_RegisterWriteISR (u8PortNum, TYPEC_CC_INT_STS, &u8Data, BYTE_LEN_1);
            
           /*Setting the CC Match Valid interrupt as CC interrupt for the firmware to handle.
           This is done to detect the detach event while Comparator goes from OFF state to ON state
           when the firmware is in attached state such as Collision avoidance and VCONN discharge*/
                       
		}
		if(u8Data & (TYPEC_CC1_MATCH_CHG | TYPEC_CC2_MATCH_CHG))
		{   			
            /*Clearing the CC Change status interrupt */
            UPD_RegisterReadISR (u8PortNum, TYPEC_CC_CHG_STS, (UINT8 *)&u16Data, BYTE_LEN_2);           
			UPD_RegisterWriteISR (u8PortNum, TYPEC_CC_CHG_STS, (UINT8 *)&u16Data, BYTE_LEN_2);
              			
		}
        
        /*Setting the CC interrupt flag in "u8IntStsISR" variable*/
        u8IntStsISR |= TYPEC_CCINT_STATUS_MASK;
        UPD_RegisterReadISR( u8PortNum, TYPEC_CC_MATCH, (UINT8 *)&u16Data, BYTE_LEN_2); 
        
        /*For Source Port*/
        if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK) == PD_ROLE_SOURCE)
        {             
            /*For a source port, a bit in CC Match register will be "cleared" , if a 
            match of the particular bit occurs. Hence the CC match register is negated while
            storing*/
            gasTypeCcontrol[u8PortNum].u8CC1_MatchISR = (UINT8)~LOBYTE(u16Data);			
            gasTypeCcontrol[u8PortNum].u8CC2_MatchISR = (UINT8)~HIBYTE(u16Data);           
        }
        /*For Sink Port*/
        else
        {   
            gasTypeCcontrol[u8PortNum].u8CC1_MatchISR = (UINT8)LOBYTE(u16Data);;			
            gasTypeCcontrol[u8PortNum].u8CC2_MatchISR = (UINT8)HIBYTE(u16Data);            
        }
	}
    
    /*Check for power interrupt*/
	if(u16InterruptStatus & UPDINTR_PWR_INT)
	{   
        /*Reading the power interrupt status register*/
        UPD_RegisterReadISR (u8PortNum, TYPEC_PWR_INT_STS, &u8Data, BYTE_LEN_1); 
        
        /* JMS - Added this check to determine if VBUS Match Valid has been set.
         * If so, we set a flag to run the VBUS match processing in the next step
         * in this function 
         */
        if (u8Data & TYPEC_VBUS_MATCH_VLD)
        {
            HOOK_DEBUG_PORT_STR (u8PortNum,"PWR_INT: VBUS_MATCH_VLD\r\n"); 
            vbus_match_valid_received = 1;
        }
        #if INCLUDE_POWER_FAULT_HANDLING
        /*Checking for VCONN over current error*/
        if(u8Data & TYPEC_VCONN_OVER_CURR_ERR)
        {
            /*VCONN FETS will be disabled automatically upon this error*/
            /*So Setting VCONN source as VCONN Disabled*/
            /*Setting the VCONN source bit in u8IntStsISR variable as VCONN disabled */
            u8IntStsISR &= ~TYPEC_VCONN_SOURCE_MASK; 
            
            /* Inform DPM about the power fault*/
            gasDPM[u8PortNum].u8PowerFaultISR |= DPM_POWER_FAULT_VCONN_OCS;
    
        }
        #endif
        
        /*Clearing the Power interrupt*/
		          
		UPD_RegisterWriteISR (u8PortNum, TYPEC_PWR_INT_STS, &u8Data, BYTE_LEN_1);
	}
    /*Check for VBUS Change interrupt*/
    /* JMS - Add a check for the flag from the previous 'if' block test for VBUS 
     * Match Valid 
     */
	if(vbus_match_valid_received || (u16InterruptStatus & UPDINTR_VBUS_INT))
	{
        UPD_RegisterReadISR (u8PortNum, TYPEC_VBUS_MATCH, &u8Data, BYTE_LEN_1);
        
        UINT8 u8HandleUV = FALSE;

        if (TYPEC_VSAFE_0V_MATCH_VAL == u8Data)
        {
            /*Setting the VBUS Status flag as 0V in u8IntStsISR variable*/
            u8IntStsISR &= ~TYPEC_VBUS_PRESENCE_MASK;
                                        
            /*Disabling the VBUS discharge functionality as vSafe0V is reached*/                  
            CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_DISABLE_VBUSDIS);
            
            if(PD_ROLE_SOURCE == (gasPortConfigurationData[u8PortNum].u32CfgData \
                     & TYPEC_PORT_TYPE_MASK))
            {
                // JMS - Only run UV handler if a VBUS change is detected.
                // (Don't run on VBUS Match Valid)
                if (u16InterruptStatus & UPDINTR_VBUS_INT)
                {
                    u8HandleUV = TRUE;
                }
            }
			else
			{
				/* Verifies whether VBUS Drop is due to Source detach*/
	            if((TYPEC_ATTACHED_SNK == gasTypeCcontrol[u8PortNum].u8TypeCState) &&
	                  (!DPM_IsHardResetInProgress(u8PortNum)))
	            {
	                /*Setting the flag that VBUS has gone below VSinkDisconnect*/
	                u8IntStsISR |= TYPEC_VSINKDISCONNECT_STATUS_MASK;
                    
	            }
						
			}
		
        }
        if (TYPEC_MAX_VSAFE_0V_MATCH_VAL == u8Data)
        {
            if(PD_ROLE_SOURCE == (gasPortConfigurationData[u8PortNum].u32CfgData \
                     & TYPEC_PORT_TYPE_MASK))
            {
                u8HandleUV = TRUE;
            }
            else
            {
                /* Verifies whether VBUS Drop is due to Source detach*/
                if((TYPEC_ATTACHED_SNK == gasTypeCcontrol[u8PortNum].u8TypeCState) &&
                      (!DPM_IsHardResetInProgress(u8PortNum)))
                {
                    /*Setting the flag that VBUS has gone below VSinkDisconnect*/
                    u8IntStsISR |= TYPEC_VSINKDISCONNECT_STATUS_MASK;
                    
                    /*Enabling the VBUS discharge functionality for VBUS to go to Vsafe0V*/                  
                    CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
                }
            
            }
        }

        if (TYPEC_VBUS_SNKDISCNT_MATCH_VAL == u8Data)
        {
            
            if(PD_ROLE_SINK == (gasPortConfigurationData[u8PortNum].u32CfgData \
                     & TYPEC_PORT_TYPE_MASK))
            {
                /* Verifies whether VBUS Drop is due to Source detach*/
               if((TYPEC_VBUS_5V == (gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VBUS_PRESENCE_MASK))
                    || ((TYPEC_ATTACHED_SNK == gasTypeCcontrol[u8PortNum].u8TypeCState) &&
				   (TYPEC_ATTACHED_SNK_RUN_SM_SS != gasTypeCcontrol[u8PortNum].u8TypeCSubState)))
               {
                   /*u8HandleUV is FALSE*/
               }
               else
               {
                    u8HandleUV = TRUE;
               }
            }
            else
            {
                u8HandleUV = TRUE;
            }
        }

        if (TRUE == u8HandleUV)
        {
            
            #if INCLUDE_POWER_FAULT_HANDLING

            u16Data = 0;

            /* Read the sample En to determine whether undervoltage is enabled */
            UPD_RegisterReadISR (u8PortNum, TYPEC_VBUS_SAMP_EN, (UINT8 *)&u16Data, BYTE_LEN_1);

            /* Verifying whether undervoltage is enabled */
            if (TYPEC_UNDER_VOLT_THR3_MATCH & u16Data)
            {
               /* undervoltage is considered if VBUS not lowered as part of Over voltage*/
               if (!gasDPM[u8PortNum].u8HRCompleteWait)
               {
                    gasDPM[u8PortNum].u8PowerFaultISR |= DPM_POWER_FAULT_UV;
                    
                    /*Notify Power Fault & drive VBUS low if needed*/
                    CONFIG_HOOK_NOTIFY_POWER_FAULT_FROM_ISR(u8PortNum,\
                                                    &gasDPM[u8PortNum].u8PowerFaultISR);

                }
            }            
            #endif /* endif for INCLUDE_POWER_FAULT_HANDLING*/            
        }
        else if (u8Data & TYPEC_VBUS_OVERVOLT_MATCH_BIT)
        {
            /* Over voltage is checked before desired voltage as TYPEC_VBUS_MATCH_OVER_V 
                checks for only over votage bit being set are not*/
            #if INCLUDE_POWER_FAULT_HANDLING
            gasDPM[u8PortNum].u8PowerFaultISR |= DPM_POWER_FAULT_OVP;
                
             /*Notify Power Fault & drive VBUS low if needed*/
             CONFIG_HOOK_NOTIFY_POWER_FAULT_FROM_ISR(u8PortNum,\
                                                        &gasDPM[u8PortNum].u8PowerFaultISR);
                
            #endif /* endif for INCLUDE_POWER_FAULT_HANDLING*/
        }
        else if((u8Data == TYPEC_VBUS_DESIRED_V_MATCH_VAL) || \
                        (u8Data == TYPEC_VBUS_DESIRED_N_UNDER_MATCH_VAL))
        {
            #if INCLUDE_UPD301_SPECIFIC
            if (PORT0 == u8PortNum)
            {
				if (UPD301_WAIT_FOR_VBUSEFF_TIMER == gu8PwrFaultDACCorrectStISR)
				{
					gu8PwrFaultDACCorrectStISR = UPD301_VALID_VBUS;
				}
            }
            #endif
            u8IntStsISR &= ~TYPEC_VBUS_PRESENCE_MASK;
            UPD_RegisterReadISR (u8PortNum, TYPEC_VBUS_THR1, (UINT8 *)&u16Data, BYTE_LEN_2);
            u16Data = TYPEC_GET_VOLTAGE_FRM_VBUS_THR(u16Data);

            /* PDO voltage for which VBUS Threshold was configured is determined */
            if (u16Data <= (PWRCTRL_VBUS_5V * TYPEC_DESIRED_MIN_PDO_VOLTAGE_FACTOR))  
            {
                /*Setting the VBUS Status flag as 5V in u8IntStsISR variable*/
                u8IntStsISR |= TYPEC_VBUS_5V;
            }
            else if (u16Data <= (PWRCTRL_VBUS_9V * TYPEC_DESIRED_MIN_PDO_VOLTAGE_FACTOR))  
            {
                /*Setting the VBUS Status flag as 9V in u8IntStsISR variable*/
                u8IntStsISR |= TYPEC_VBUS_9V;
            }
            else if (u16Data <= (PWRCTRL_VBUS_15V * TYPEC_DESIRED_MIN_PDO_VOLTAGE_FACTOR))  
            {
                /*Setting the VBUS Status flag as 20V in u8IntStsISR variable*/
                u8IntStsISR |= TYPEC_VBUS_15V;
            }
            else if (u16Data <= (PWRCTRL_VBUS_20V * TYPEC_DESIRED_MIN_PDO_VOLTAGE_FACTOR))  
            {
                /*Setting the VBUS Status flag as 20V in u8IntStsISR variable*/
                u8IntStsISR |= TYPEC_VBUS_20V;
            }

            if(PD_ROLE_SOURCE == DPM_GET_CURRENT_POWER_ROLE(u8PortNum))
            {              
                 /*Disabling the VBUS discharge functionality as desired voltage is reached
                only if port role is source*/                  
                CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_DISABLE_VBUSDIS);
              
            }            
                    
        }

        /*Clearing the VBUS Change status interrupt*/
        UPD_RegisterReadISR (u8PortNum, TYPEC_VBUS_CHG_STS, &u8Data, BYTE_LEN_1);
        UPD_RegisterWriteISR (u8PortNum, TYPEC_VBUS_CHG_STS, &u8Data, BYTE_LEN_1);
        
        HOOK_DEBUG_PORT_STR (u8PortNum,"VBUS_INT: EXIT VBUS_MATCH_CHG\r\n"); 
    }
    
    gasTypeCcontrol[u8PortNum].u8IntStsISR = u8IntStsISR;
}

void TypeC_ConfigCCComp(UINT8 u8PortNum ,UINT8 u8ConfigVal)
{     
    UINT8 u8Data;
    UINT8 u8Desired_DBState;
    
     /*Enabling the Corresponding lines for the CC Debouncer Sampling */  
     UPD_RegisterRead (u8PortNum, TYPEC_CC_CTL1_HIGH, &u8Data, BYTE_LEN_1);
     
     /*Clearing the CC Comparator sampling bits before setting a particular configuration*/
     u8Data &= ~TYPEC_CC_COMP_CTL;
     u8Data |= u8ConfigVal;
     UPD_RegisterWrite (u8PortNum, TYPEC_CC_CTL1_HIGH, &u8Data, BYTE_LEN_1);
     
    /*Set CC Comparator OFF*/
    if(u8ConfigVal == TYPEC_CC_COMP_CTL_DIS)
    {  
        /* Wait until the CC Debouncer goes to inactive state  */ 
        u8Desired_DBState = TYPEC_CC_DB_ACTIVE;             
    }
    else
    {
        /* Wait until the CC Debouncer goes to Active state  */
        u8Desired_DBState = FALSE;      
    }
    
    do
    {
        UPD_RegisterRead (u8PortNum, TYPEC_CC_HW_CTL_HIGH, &u8Data, BYTE_LEN_1);
        
    }while((u8Data & TYPEC_CC_DB_ACTIVE) == u8Desired_DBState); 
    
}
void TypeC_SetVBUSCompONOFF(UINT8 u8PortNum,UINT8 u8ConfigVal)
{
    UINT8 u8Data;
    UINT8 u8Desired_DBState;
      
    /*Set VBUS Comparator OFF*/
    if(u8ConfigVal == TYPEC_VBUSCOMP_OFF)
    {
        /*Disabling the VBUS Debouncer */
        UPD_RegByteClearBit (u8PortNum, TYPEC_VBUS_CTL1_LOW, TYPEC_VBUS_DET);

        /* Wait until the VBUS Debouncer goes to inactive state  */
        u8Desired_DBState = TYPEC_VBUS_DB_ACTIVE;           
    }
    /*Set VBUS Comparator ON*/
    else
    {
        /* Setting the VBUS Comparator Control ON*/
        UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL1_LOW, TYPEC_VBUS_DET);
        
        /* Wait until VBUS Comparator goes to active state */
        u8Desired_DBState = FALSE; 
    }
    
    do
    {
        UPD_RegisterRead (u8PortNum, TYPEC_VBUS_CTL1_LOW, &u8Data, BYTE_LEN_1);
        
    }while((u8Data & TYPEC_VBUS_DB_ACTIVE)  == u8Desired_DBState);
}

void TypeC_SetCCSampleEnable (UINT8 u8PortNum, UINT8 u8CCEnablePins)
{
    if (u8CCEnablePins & TYPEC_ENABLE_CC1_SAMPLING)
    {
        /*Setting the CC1_DBCLR_EN, CC1_SAMP_EN to enable debouncing for specific CC thresholds*/
        UPD_RegisterWrite (u8PortNum, TYPEC_CC1_DBCLR_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);   
        UPD_RegisterWrite (u8PortNum, TYPEC_CC1_MATCH_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);
        UPD_RegisterWrite (u8PortNum, TYPEC_CC1_SAMP_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);

    }
    if (u8CCEnablePins & TYPEC_ENABLE_CC2_SAMPLING)
    {    
        /*Setting the CC2_DBCLR_EN,CC2_SAMP_EN to sample for specific CC thresholds*/
        UPD_RegisterWrite (u8PortNum, TYPEC_CC2_DBCLR_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);
        UPD_RegisterWrite (u8PortNum, TYPEC_CC2_MATCH_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);
        UPD_RegisterWrite (u8PortNum, TYPEC_CC2_SAMP_EN, &gasTypeCcontrol[u8PortNum].u8CCDebMatch,\
                           BYTE_LEN_1);
    }    
}


void TypeC_SetPowerRole(UINT8 u8PortNum,UINT8 u8PowerRole, UINT8 u8ConfigVal)
{  
     UINT16 u16CCControlReg1Val;
     
     /* Register Read added to avoid over writting the register CC_CTL1 register */
     UPD_RegisterRead (u8PortNum, TYPEC_CC_CTL1, (UINT8 *)&u16CCControlReg1Val, BYTE_LEN_2);
     
     /*Clearing the Existing Pull Down and Pull up resisor values*/
     u16CCControlReg1Val &= TYPEC_CC1_CC2_RP_MASK;
     u16CCControlReg1Val &= TYPEC_CC1_CC2_PD_MASK;  
     
     if (u8PowerRole == PD_ROLE_SINK)
     {                   
        /*Setting the given config value as pull down resistor */
        u16CCControlReg1Val |= (( u8ConfigVal << TYPEC_CC1_PULL_DOWN_POS) \
                                 | (u8ConfigVal << TYPEC_CC2_PULL_DOWN_POS));
        
        /*Setting the pull up resistor as open disconnect*/
        u16CCControlReg1Val |=(TYPEC_CC_RP_DIS);
     }
     else if (u8PowerRole == PD_ROLE_SOURCE)
     {        
        /*Setting the given config value as pull up resistor */
        u16CCControlReg1Val |= (( u8ConfigVal << TYPEC_CC1_RP_VAL_POS) \
                               | (u8ConfigVal << TYPEC_CC2_RP_VAL_POS));
        
        /*Setting the pull down resistor as open disconnect*/
        u16CCControlReg1Val |= (TYPEC_CC1_PULL_DOWN_OPEN|TYPEC_CC2_PULL_DOWN_OPEN);
     }
     
    /*Writing the CC control register directly because it wont affect the CC comparator Sample 
    operation as it would have been turned down at this time*/
    /*Setting the Rd and Rp Value*/ 
    UPD_RegisterWrite (u8PortNum, TYPEC_CC_CTL1, (UINT8 *)&u16CCControlReg1Val, BYTE_LEN_2);

}

void TypeC_SetDataRole (UINT8 u8PortNum,UINT8 u8DataRole)
{
    /* Setting Port Role in TYPEC_CC_HW_CTL register */
    if (u8DataRole == PD_ROLE_UFP)
    {      
        UPD_RegByteClearBit (u8PortNum, TYPEC_CC_HW_CTL_LOW, TYPEC_DEV_ROLE);
    }
    else if (u8DataRole == PD_ROLE_DFP)
    {
        UPD_RegByteSetBit (u8PortNum, TYPEC_CC_HW_CTL_LOW, TYPEC_DEV_ROLE);
    }  
}
                               
void TypeC_EnabDisVCONN (UINT8 u8PortNum, UINT8 u8EnableDisable)
{
    UINT8 u8Data;
    
    if (u8EnableDisable == TYPEC_VCONN_DISABLE)
    {     
        gasTypeCcontrol[u8PortNum].u8PortSts |= TYPEC_VCONN_DISCHARGE_ON_MASK;

        /*Disable VCONN by switching off the VCONN FETS*/
        UPD_RegByteClearBit (u8PortNum, TYPEC_VBUS_CTL1, TYPEC_VCONN_FETS);

        /*Disable the VCONN OCS monitoring in VBUS_CTL1 register*/
        UPD_RegByteClearBit (u8PortNum, TYPEC_VBUS_CTL1_LOW, TYPEC_VCONN_OCS_ENABLE);

        /*Setting CC Comparator OFF*/
        TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_DIS);

        /*Setting the CC threshold 0 register to 41d which is a VCONN discharge threshold */
        UPD_RegWriteWord (u8PortNum, TYPEC_CC_THR0, TYPEC_CC_THR_VAL_VCONN_DIS);

        UPD_RegisterRead (u8PortNum, TYPEC_CC_CTL1_LOW, &u8Data, BYTE_LEN_1);

        gasTypeCcontrol[u8PortNum].u8CCDebMatch = (TYPEC_CC_THRES0_MATCH); 

        /*Poll the variable to see which CC pin was VCONN Source*/
        if ((gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VCONN_SOURCE_MASK) == (TYPEC_VCONN_SOURCE_CC1))
        {
            /*CC1 is the source of VCONN*/
            u8Data &= ~TYPEC_CC1_PULL_DOWN;
            u8Data |= (TYPEC_CC1_PULL_DOWN_RA) ; 
             
            /*Setting Ra Pull down on either CC1 or CC2 based on VCONN Source pin*/
            UPD_RegisterWrite (u8PortNum, TYPEC_CC_CTL1_LOW, &u8Data, BYTE_LEN_1);

            /*Setting the Rp value as "current source disabled" in CC1*/   
            UPD_RegByteClearBit (u8PortNum, TYPEC_CC_CTL1_HIGH, (TYPEC_CC1_RP_VAL));

            TypeC_SetCCSampleEnable (u8PortNum,TYPEC_ENABLE_CC1_SAMPLING);
           
        }
        else
        {
            /*CC2 is the source of VCONN*/
            u8Data &= ~TYPEC_CC2_PULL_DOWN;
            u8Data |= (TYPEC_CC2_PULL_DOWN_RA); 

            /*Setting Ra Pull down on either CC1 or CC2 based on VCONN Source pin*/
            UPD_RegisterWrite (u8PortNum, TYPEC_CC_CTL1_LOW, &u8Data, BYTE_LEN_1);

            /*Setting the Rp value as "current source disabled" in CC2*/   
            UPD_RegByteClearBit (u8PortNum, TYPEC_CC_CTL1_HIGH, (TYPEC_CC2_RP_VAL));

            TypeC_SetCCSampleEnable (u8PortNum,TYPEC_ENABLE_CC2_SAMPLING);

        }
           
        /*Setting CC Comparator to sample both the CC1 and CC2*/
        TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1_CC2);

        HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: VCONN DISCHARGE initiated\r\n");
        
    }
    else
    {   
        #if INCLUDE_POWER_FAULT_HANDLING
        /*Start the VCONN power good timer if VCONN OCS fault counter is not zero*/
        if(gasDPM[u8PortNum].u8VCONNPowerFaultCount!= 0)
        {
            PDTimer_Kill (gasDPM[u8PortNum].u8VCONNPowerGoodTimerID);
            gasDPM[u8PortNum].u8VCONNPowerGoodTimerID = PDTimer_Start (CONFIG_DPM_POWER_GOOD_TIMER_MS,\
                                                      DPM_VCONNPowerGood_TimerCB, u8PortNum, NULL);
                  
        }
        #endif
            
        UINT8 u8VCONN1Enable =FALSE;
        
        UINT8 u8CCRead = UPD_RegReadByte (u8PortNum, TYPEC_CC_CTL1_HIGH);
               
        if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK) == PD_ROLE_SOURCE)
        {       
            /*Powered cable attached in CC1 when CC1 is greater than CC2*/
            /*Powered cable attached in CC1 when PD Communication is enabled in CC2*/
            if (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) \
                && (gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_PWDCABLE_PRES_MASK)) || (u8CCRead & TYPEC_CC_COM_SEL))
            {
                u8VCONN1Enable = TRUE;
            }
        }       
        else
        {
            /*Powered cable attached in CC1*/
            if (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR < gasTypeCcontrol[u8PortNum].u8CC2_MatchISR)
            {
                u8VCONN1Enable = TRUE;
            }
        
        }
                
        /*Powered cable attached in CC1*/
        if (u8VCONN1Enable)
        {    

            gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
            gasTypeCcontrol[u8PortNum].u8PortSts |= TYPEC_VCONN1_ON_REQ;
                                       
            /*Enable VCONN FET in CC1*/
            UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL1, TYPEC_VCONN1_ENABLE);
          
        }
        /*Powered cable attached in CC2*/
        else
        {     
            gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
            gasTypeCcontrol[u8PortNum].u8PortSts |= TYPEC_VCONN2_ON_REQ;

            /*Enable VCONN FET in CC1*/
            UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL1, TYPEC_VCONN2_ENABLE);
        }
       
        /*Enable the VCONN OCS monitoring in VBUS_CTL1 register*/
        UPD_RegByteSetBit (u8PortNum, TYPEC_VBUS_CTL1_LOW, TYPEC_VCONN_OCS_ENABLE);
    } 
}
 

void TypeC_VCONNDis_On_IntrHandler(UINT8 u8PortNum)
{
          
    /*Clearing the CC interrupt status in u8IntStsISR variable at the start of this function to 
    make this ISR safe as after TypeC_Reset_VCONNDIS_Settings function call,
    Interrupt will immediatley be fired*/  
    gasTypeCcontrol[u8PortNum].u8IntStsISR &= ~TYPEC_CCINT_STATUS_MASK;
    
    /*Setting the VCONN source bit in u8IntStsISR variable as VCONN disabled */
    gasTypeCcontrol[u8PortNum].u8IntStsISR &= ~TYPEC_VCONN_SOURCE_MASK;
    
    /*VCONN discharge complete can occur while the sink is still attached or detached for source port*/
    /*VCONN discharge complete can occur while the source is still attached or detached for sink port*/
    
    /*Detach Event occured during this VCONN Discharge process will be handled since the 
    TypeC_Reset_VCONNDIS_Settings function will again restart the CC Comparator*/
    TypeC_Reset_VCONNDIS_Settings(u8PortNum);
    gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_DISCHARGE_ON_MASK; 
       
}

void TypeC_VCONN_ON_IntrHandler(UINT8 u8PortNum)
{
    if(gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK)
    {
        /*VCONN Enabled in CC1 and Sink Attached in CC2*/
        if((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN1_ON_REQ) && \
            (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == 0x00 ) && 
              (gasTypeCcontrol[u8PortNum].u8CC2_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch ))
        {
            
            /*Setting the u8IntStsISR variable that CC1 is the VCONN source*/
            gasTypeCcontrol[u8PortNum].u8IntStsISR |= TYPEC_VCONN_SOURCE_CC1;
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: VCONN Enabled in CC1\r\n");  
          
        }
		 /*VCONN Enabled in CC2 and Sink Attached in CC1*/
        else if ((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN2_ON_REQ) && \
            (gasTypeCcontrol[u8PortNum].u8CC2_MatchISR == 0x00 ) &&
            (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch ))
        {
        
            /*Setting the u8IntStsISR variable that CC2 is the VCONN source*/
            gasTypeCcontrol[u8PortNum].u8IntStsISR |= TYPEC_VCONN_SOURCE_CC2;
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: VCONN Enabled in CC2\r\n");  
        }
            
    }
    else
    {    /*VCONN Enabled in CC1 and Source Attached in CC2*/
        if((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN1_ON_REQ) && \
            (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == TYPEC_SNK_CCTHRES_VCONN_ON) &&
            ((gasTypeCcontrol[u8PortNum].u8CC2_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch)))
        {
         
             /*Setting the u8IntStsISR variable that CC1 is the VCONN source*/
            gasTypeCcontrol[u8PortNum].u8IntStsISR |= TYPEC_VCONN_SOURCE_CC1;
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: VCONN Enabled in CC1\r\n");  
        }
         /*VCONN Enabled in CC2 and Source Attached in CC1*/
        else if((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN2_ON_REQ) && \
            (gasTypeCcontrol[u8PortNum].u8CC2_MatchISR == TYPEC_SNK_CCTHRES_VCONN_ON) &&
             (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch))
        {
        
             /*Setting the u8IntStsISR variable that CC2 is the VCONN source*/
            gasTypeCcontrol[u8PortNum].u8IntStsISR |= TYPEC_VCONN_SOURCE_CC2;          
            
            HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: VCONN Enabled in CC2\r\n");  
        }
    
    }    
    /*Handle only the CC interrupt for VCONN_ON event.CC interrupts for detach 
    event or others should be handled in either SrcIntr Handler or SnkIntr Handler function*/
    if(gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VCONN_SOURCE_MASK)
    {
         /*Clearing the VCONN ON Request mask if VCONN has turned ON*/
         gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK; 

         /*Clearing the CC Interupt flag since CC change is because of the VCONN ON event*/
         gasTypeCcontrol[u8PortNum].u8IntStsISR &= ~TYPEC_CCINT_STATUS_MASK;
    
    }
}

void TypeC_CCVBUSIntrHandler (UINT8 u8PortNum)
{     
    CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
    
    /*Handling the state changes for CC and VBUS interrupts in foreground and not in ISR to 
    avoid variable corruption*/
    
    if (gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VSINKDISCONNECT_STATUS_MASK)
    {
        /*Voltage dropped to vSinkDisconnect in Attached Sink State before the Source CC detach 
        event occured*/
        /*VSinkDisconnect event occured after the CC detach event is not processed
        which is a violation of specification*/
        /*This is done for easy handling*/
        if((TYPEC_ATTACHED_SNK_RUN_SM_SS == gasTypeCcontrol[u8PortNum].u8TypeCSubState))
        {
            gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_TPD_TO_SS;
        }
        
        /*Clearing the VsinkDisconnect interrupt Status set*/
        gasTypeCcontrol[u8PortNum].u8IntStsISR &= ~TYPEC_VSINKDISCONNECT_STATUS_MASK;
         
    }    
    if (gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_CCINT_STATUS_MASK)
    {        
        HOOK_DEBUG_PORT_STR(gasTypeCcontrol[u8PortNum].u8CC1_MatchISR,"TYPEC: TYPEC: CC1 register\r\n");
        HOOK_DEBUG_PORT_STR(gasTypeCcontrol[u8PortNum].u8CC2_MatchISR,"TYPEC: TYPEC: CC2 register\r\n");
                 
        if(gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN_DISCHARGE_ON_MASK)
        {
            TypeC_VCONNDis_On_IntrHandler(u8PortNum);
        }   
        else if(gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_VCONN_ON_REQ_MASK)
        {
            TypeC_VCONN_ON_IntrHandler(u8PortNum);
        }
        
        if(gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_CCINT_STATUS_MASK)
        {
            switch (gasTypeCcontrol[u8PortNum].u8TypeCState)
            {            
                case TYPEC_UNATTACHED_SRC:
                case TYPEC_ATTACHWAIT_SRC:
                case TYPEC_ATTACHED_SRC:   
                {            
                    TypeC_SrcIntrHandler(u8PortNum); 
                    break;
                }                   
                case TYPEC_UNATTACH_WAIT_SRC:
                {     
                  
                    /*Setting the Substate to verify whether VBUS has reached to 0V before moving into 
                    unattached state */
                    /*This condition occurs when VCONN Discharge is completed*/
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  =  TYPEC_UNATTACH_WAIT_SRC_CHECK_VBUS_0V_SS;                  
                    break;
                }                   
                case TYPEC_UNATTACHED_SNK:
                case TYPEC_ATTACHWAIT_SNK:
                case TYPEC_ATTACHED_SNK:
                {                          
#if INCLUDE_PD_SINK_ONLY
                    TypeC_SnkIntrHandler(u8PortNum);
#endif //INCLUDE_PD_SINK_ONLY
                   break;
                }                  
                case TYPEC_AUDIO_ACCESSORY:
                case TYPEC_UNORIENTED_DEBUG_ACCESSORY_SRC:
                {                
                    /*Only the CC Detach is expected in both the above states.Hence CC interrupt leads 
                    to unattached state*/
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  =  TYPEC_UNATTACHED_SRC_ENTRY_SS;
                    gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_UNATTACHED_SRC;
                    break; 
                }
                                
            }
            /*Clearing the CC interrupt status in u8IntStsISR variable*/
            gasTypeCcontrol[u8PortNum].u8IntStsISR &= ~TYPEC_CCINT_STATUS_MASK;        
        }
		        
    }
    CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
}

#if INCLUDE_PD_SOURCE_ONLY
void TypeC_SrcIntrHandler (UINT8 u8PortNum)
{
 	 
    /*Assigning the structure variables to local variables to reduce the code size as
    accessing the structure members takes lot of code*/  
  
    UINT8 u8TypeCState = gasTypeCcontrol[u8PortNum].u8TypeCState;
    UINT8 u8TypeCSubState = gasTypeCcontrol[u8PortNum].u8TypeCSubState;
        
	switch (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR ^ gasTypeCcontrol[u8PortNum].u8CC2_MatchISR)
	{
        /*Only Powered Cable is present*/
		case TYPEC_PWD_CABLE_ATT_DEF:
		case TYPEC_PWD_CABLE_ATT_1A5:
		case TYPEC_PWD_CABLE_ATT_3A0:
		{	
            /*Setting the Powered cable presence in u8PortSts variable*/
            gasTypeCcontrol[u8PortNum].u8PortSts |= TYPEC_PWDCABLE_PRES_MASK;
            
			DPM_ResetVCONNErrorCnt (u8PortNum);
            HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Only Powered Cable is Present in CC");
            HOOK_DEBUG_PORT_STR (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) ? 1 : 2),"\r\n"); 
            
            /*Move to TYPEC_UNATTACH_WAIT_SRC state if current state is TYPEC_ATTACHED_SRC*/
            if (u8TypeCState == TYPEC_ATTACHED_SRC)
            {
                u8TypeCState = TYPEC_UNATTACH_WAIT_SRC;
                u8TypeCSubState = TYPEC_UNATTACH_WAIT_SRC_ENTRY_SS;            
            } 
            else if (u8TypeCState == TYPEC_ATTACHWAIT_SRC)
            {
                /*Kill the TCC debounce timer running already*/
                TypeC_KillTypeCTimer(u8PortNum);
                
                /*Move to TYPEC_UNATTACHED_SRC state if current state is  TYPEC_ATTACHWAIT_SRC*/
                u8TypeCState = TYPEC_UNATTACHED_SRC;
                u8TypeCSubState  = TYPEC_UNATTACHED_SRC_ENTRY_SS;                             
            }
            break;
		}
		
		
        /*Only Sink Device is Present*/
		case TYPEC_UFP_ATT_DEF:
        case TYPEC_UFP_ATT_3A0:
		{
            if(u8TypeCState != ((UINT8) TYPEC_ATTACHED_SRC))
            {              
                /*Clearing the Powered cable presence in u16PortSts variable*/
                gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_PWDCABLE_PRES_MASK;
                    
                /*Setting the state for tCCDebounce*/
                u8TypeCState = TYPEC_ATTACHWAIT_SRC; 
                u8TypeCSubState  = TYPEC_ATTACHWAIT_SRC_DEB_SS;
                                
                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Only Sink is Present in CC");
                HOOK_DEBUG_PORT_STR (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) ? 1 : 2),"\r\n");
               
            } 
            break;
            
		}
		
		
        /*Both Powered cable and sink is Present*/
		case (TYPEC_PWD_CABLE_ATT_DEF ^ TYPEC_UFP_ATT_DEF):
		case (TYPEC_PWD_CABLE_ATT_1A5 ^ TYPEC_UFP_ATT_1A5):
		case (TYPEC_PWD_CABLE_ATT_3A0 ^ TYPEC_UFP_ATT_3A0):
		{
          
            /*Setting the Powered cable presence in u8PortSts variable*/
            gasTypeCcontrol[u8PortNum].u8PortSts |= TYPEC_PWDCABLE_PRES_MASK;
          
            HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Sink is Present in CC");
            HOOK_DEBUG_PORT_STR (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) ? 2 : 1),"\r\n");
            
            HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Powered Cable is Persent in CC");
            HOOK_DEBUG_PORT_STR (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) ? 1 : 2),"\r\n");
            
            if(u8TypeCState == TYPEC_UNATTACHED_SRC)
            {             
                /*Setting the state for tCCDebounce*/
                u8TypeCState = TYPEC_ATTACHWAIT_SRC;
                u8TypeCSubState = TYPEC_ATTACHWAIT_SRC_DEB_SS;
                
            } 
            break;
		}
		
		
		case TYPEC_CC1CC2_EQ:
		{           
            /*Audio Adapter Accessory is Present*/         
            if (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == gasTypeCcontrol[u8PortNum].u8CCDebMatch)
			{   
                 /*Consider the CC Sample values as valid Audio accessory attach only at the 
                unattached state*/
                /*This avoids unwanted transistion in attached state*/
                if(u8TypeCState == TYPEC_UNATTACHED_SRC)
                {                
                    HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: AUDIO ACCESSORY is present\r\n");
                    
                    /*Setting the state for tCCDebounce*/
                    u8TypeCState = TYPEC_ATTACHWAIT_SRC;
                    u8TypeCSubState  = TYPEC_ATTACHWAIT_SRC_DEB_SS;
                
                }
			    
				
			}
            /*No Devices are Present*/
			else if (!gasTypeCcontrol[u8PortNum].u8CC1_MatchISR)
			{             
                /*Clearing the Powered cable presence in u8PortSts variable*/
                gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_PWDCABLE_PRES_MASK;
                
				DPM_ResetVCONNErrorCnt (u8PortNum);
                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: No Devices are present\r\n");
                
                if(u8TypeCState == TYPEC_ATTACHWAIT_SRC)
                {
                    /*Kill the TCC debounce timer running already*/
                     TypeC_KillTypeCTimer(u8PortNum);
                    
                    /*Move to TYPEC_UNATTACHED_SRC state  if current state is 
                    TYPEC_ATTACHWAIT_SRC*/
                    u8TypeCState = TYPEC_UNATTACHED_SRC;
                    u8TypeCSubState  = TYPEC_UNATTACHED_SRC_ENTRY_SS;                              
                }
                else if (u8TypeCState == TYPEC_ATTACHED_SRC)
                {
                    /*Move to TYPEC_UNATTACH_WAIT_SRC state if current state is 
                    TYPEC_ATTACHED_SRC*/
                    u8TypeCState = TYPEC_UNATTACH_WAIT_SRC;
                    u8TypeCSubState = TYPEC_UNATTACH_WAIT_SRC_ENTRY_SS; 
                }               
                
			}			
            /*Debug Accessory is Present*/
			else
			{    
                  /*Consider the CC Sample values as valid Debug accessory attach only at the 
                unattached state*/
                /*This avoids unwanted transistion in attached state*/              
                if(u8TypeCState == TYPEC_UNATTACHED_SRC)
                {
                  
                    HOOK_DEBUG_PORT_STR(u8PortNum,"TYPEC: DEBUG ACCESSORY is present\r\n");
                    /*Setting the state for tCCDebounce	*/
                    u8TypeCState = TYPEC_ATTACHWAIT_SRC;
                    u8TypeCSubState  = TYPEC_ATTACHWAIT_SRC_DEB_SS;

                }
			} 
            break;
		}		
        
		default:
		break;			
	}    
    gasTypeCcontrol[u8PortNum].u8TypeCState = u8TypeCState;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState = u8TypeCSubState;
         
}

void TypeC_Reset_VCONNDIS_Settings (UINT8 u8PortNum)
{
    
    HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: VCONN DISCHARGE COMPLETED\r\n");
    
    /*Power down the CC comparator*/
    TypeC_ConfigCCComp(u8PortNum, TYPEC_CC_COMP_CTL_DIS);
    
    /*Resetting the CC Threshold 0 register to default value*/
    UPD_RegWriteWord (u8PortNum, TYPEC_CC_THR0, TYPEC_CC_THR0_VAL);    
    
    if((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK) == PD_ROLE_SOURCE)
    {
        /*Setting the user given Rp value for source since it is changed to open disconnect
        while VCONN Discharge*/
        TypeC_SetDefaultRpValue (u8PortNum);
    }
    else
    {
        TypeC_SetCCDebounceVariable(u8PortNum, TYPEC_UFP);
          
        /*Reset only the Rd value for the CC pin in which VCONN was sourced*/
        TypeC_SetPowerRole(u8PortNum,TYPEC_ROLE_SINK, TYPEC_ROLE_SINK_RD);
        
        /*Resetting the CC Debounce clear enable,CC Match Enable,CC Sample Enable register*/
        TypeC_SetCCSampleEnable (u8PortNum, (TYPEC_ENABLE_CC1_SAMPLING | TYPEC_ENABLE_CC2_SAMPLING));
    }
  
    /*Set the CC Comparator to sample both CC1 and CC2*/
    TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1_CC2); 
}

void TypeC_SetDefaultRpValue (UINT8 u8PortNum)
{
    UINT16 u16Data;    
    
    u16Data = ((gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_RPVAL_MASK) \
              >> TYPEC_PORT_RPVAL_POS);
    
    /*Setting Rp Current Source as user given and Rd as Open disconnect in both CC1 and CC2*/ 
    TypeC_SetPowerRole (u8PortNum, TYPEC_ROLE_SOURCE, (UINT8) u16Data);
  
    /*Setting the u8CCDebMatch and u8CCSrcSnkMatch variable accordingly as per Rp Value*/
    TypeC_SetCCDebounceVariable(u8PortNum, (UINT8) u16Data);
     
    /*Resetting the CC Debounce clear enable,CC Match Enable,CC Sample Enable register*/
    TypeC_SetCCSampleEnable (u8PortNum, (TYPEC_ENABLE_CC1_SAMPLING | TYPEC_ENABLE_CC2_SAMPLING));
   
    
    /*Setting user given Rp Value as Current Rp Value in CurrentRpVal bit of u8PortSts variable*/
    gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_CURR_RPVAL_MASK;
    gasTypeCcontrol[u8PortNum].u8PortSts  |= (u16Data << TYPEC_CURR_RPVAL_POS);

}

#endif
/*INCLUDE_PD_SOURCE_ONLY*/

#if INCLUDE_PD_SINK_ONLY

void TypeC_SnkIntrHandler (UINT8 u8PortNum)
{
  
    /*Assigning the structure variables to local variables to reduce the code size as
    accessing the structure members takes lot of code*/   
    UINT8 u8TypeCState = gasTypeCcontrol[u8PortNum].u8TypeCState;
    UINT8 u8TypeCSubState = gasTypeCcontrol[u8PortNum].u8TypeCSubState;
    
	switch (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR ^ gasTypeCcontrol[u8PortNum].u8CC2_MatchISR)	
	{
		case TYPEC_DFP_DEF_ATT:
		case TYPEC_DFP_1A5_ATT:
		case TYPEC_DFP_3A0_ATT:
		{    
            /*Decode and store the Rp value of Source attached*/ 
            TypeC_DecodeSourceRpValue(u8PortNum);
                       
            if (u8TypeCState == TYPEC_ATTACHWAIT_SNK)
            {
                    /*Kill the TPD Debounce timer running for last detach event or
                    Kill the TCC Debounce timer running for previous attach event*/
                    TypeC_KillTypeCTimer(u8PortNum);
                    
            }
            else if ((u8TypeCState == TYPEC_ATTACHED_SNK) && (u8TypeCSubState == ((UINT8)TYPEC_ATTACHED_SNK_RUN_SM_SS)))
            {
                 break;
            }
            else
            {
                 /*Attach event has occured within the TPD Debounce timeout of previous Detach event
                 So in this case moving to the Attach wait state and also killing the 
                 TPD Debounce timer which is active currently*/
                 if((u8TypeCState == TYPEC_ATTACHED_SNK) && (u8TypeCSubState != ((UINT8)TYPEC_ATTACHED_SNK_RUN_SM_SS)))
                 {
                    /*Kill the TPD Debounce timer running previously for detach event*/
                    TypeC_KillTypeCTimer(u8PortNum);
                 
                 }
                 
                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Source is Persent in CC");
                HOOK_DEBUG_PORT_STR (((gasTypeCcontrol[u8PortNum].u8CC1_MatchISR > gasTypeCcontrol[u8PortNum].u8CC2_MatchISR) ? 1 : 2),"\r\n");
                                                             
            }

            /*Disable the Protocol layer receiver function since moving to Attach wait state*/
            PRL_EnableRx (u8PortNum,false);

            /*Setting the state as TYPEC_ATTACHWAIT_SNK for Tcc Debounce and VBUS presence 
            check*/
            u8TypeCState = TYPEC_ATTACHWAIT_SNK;
            u8TypeCSubState  = TYPEC_ATTACHWAIT_SNK_TCCDEB_SS;
            break;
		}
                  
        case TYPEC_NO_THRESHOLD:
        {          
            /*Valid Detach event happens only when both the CC1 and CC2 are 0*/  
            if(gasTypeCcontrol[u8PortNum].u8CC1_MatchISR == 0)
            {

                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: NO DEVICES ARE PRESENT\r\n");
                DPM_ResetVCONNErrorCnt (u8PortNum);	

                if (u8TypeCState == TYPEC_ATTACHWAIT_SNK)
                {
                    /*Kill the TCC Debounce timer running previously attach event*/
                    TypeC_KillTypeCTimer(u8PortNum);
                    u8TypeCSubState  = TYPEC_ATTACHWAIT_SNK_TPDDEB_SS;
                }
                /*Source detach occurs before the VBUS drops below VSinkdisconnect */
                else if ((u8TypeCState == TYPEC_ATTACHED_SNK) && \
                         (u8TypeCSubState == TYPEC_ATTACHED_SNK_RUN_SM_SS))
                {
                     /*Go to TYPEC_ATTACHED_SNK_TPDDEB_SS substate for starting tPDDebounce*/
                     u8TypeCSubState  = TYPEC_ATTACHED_SNK_TPDDEB_SS;
                }
                /*This condition occurs if VCONN Discharge is enabled in Attached Sink State
                or Source detach occurs after VBUS drops below VSinkdisconnect*/
                else if (u8TypeCState == TYPEC_ATTACHED_SNK)
                {
                    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = TYPEC_ATTACHED_SNK_SET_UNATTACHED_SS;
                }
            }
             
            break;
        }
            		
		default:
		break;
	}
    
    gasTypeCcontrol[u8PortNum].u8TypeCState = u8TypeCState;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState = u8TypeCSubState;

}

void TypeC_DecodeSourceRpValue(UINT8 u8PortNum)
{   
    /*Assigning the structure variables to local variables to reduce the code size as
    accessing the structure members takes lot of code*/
    UINT8 u8PortSts =  gasTypeCcontrol[u8PortNum].u8PortSts;
    
    UINT8 u8CCSrcSnkMatch = gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch;
    
    /*Clearing the Current Rp Value of Source*/    
    u8PortSts &= ~TYPEC_CURR_RPVAL_MASK;
     
    switch (gasTypeCcontrol[u8PortNum].u8CC1_MatchISR ^ gasTypeCcontrol[u8PortNum].u8CC2_MatchISR)	
	{
		case TYPEC_DFP_DEF_ATT:
        {
            /*Setting the Current Rp Value of Source as Default Current*/
            u8PortSts |= (TYPEC_RP_DEFAULT_CURRENT << TYPEC_CURR_RPVAL_POS);
            
            u8CCSrcSnkMatch = TYPEC_DFP_DEF_ATT;
            break;
        }
        
		case TYPEC_DFP_1A5_ATT:
        {
              /*Setting the Current Rp Value of Source as 1.5A@5V */
             u8PortSts |= (TYPEC_RP_CURRENT_15 << TYPEC_CURR_RPVAL_POS); 
             
             u8CCSrcSnkMatch = TYPEC_DFP_1A5_ATT;
             break;
          
        }
        
		case TYPEC_DFP_3A0_ATT:
		{
            /*Setting the Current Rp Value of Source as 3.0A@5V */
            u8PortSts |= (TYPEC_RP_CURRENT_30 << TYPEC_CURR_RPVAL_POS);
            
            u8CCSrcSnkMatch = TYPEC_DFP_3A0_ATT;
             
             /*Call the Collision avoidance API provided by the PRL if only the Collision avoidance
             Status is set*/
             if(u8PortSts & TYPEC_COLLISION_AVOIDANCE_ACT)
             {
                 /*Clear the Collision avoidance Status variable*/
                 u8PortSts &= ~TYPEC_COLLISION_AVOIDANCE_ACT;
                   
                /*Calling the callback API provided by the protocol layer here*/
                PRL_CommitPendingTxOnCAISR (u8PortNum);
                HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Collision Avoidance Callback API called\r\n");
                                     
             }
             break;
        }
         
    }
    
    gasTypeCcontrol[u8PortNum].u8PortSts = u8PortSts; 
    gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch = u8CCSrcSnkMatch;
    
}
#endif
/*INCLUDE_PD_SINK_ONLY*/


/*Change the Rp Value only for the CC pin in which source is connected*/
void TypeC_SetRpCollAvoidance (UINT8 u8PortNum, UINT8 u8RpValue)
{
    
    /*Setting the CC Comparator OFF*/
    TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_DIS);  
  
    /*Rp value as 1.5A@5V */
    if(u8RpValue == TYPEC_SINK_TXNG)
    {
        gasTypeCcontrol[u8PortNum].u8CCDebMatch = (TYPEC_CC_THRES1_MATCH | TYPEC_CC_THRES5_MATCH);
        gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch = (TYPEC_CC_THRES5_MATCH);
        
        /*Setting the current Rp value as TYPEC_RP_CURRENT_15 in u8PortSts variable*/
        gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_CURR_RPVAL_MASK;
        gasTypeCcontrol[u8PortNum].u8PortSts |= (TYPEC_RP_CURRENT_15 << TYPEC_CURR_RPVAL_POS);
        
        /*Setting the Rp Value as SinkTxNG*/
        TypeC_SetPowerRole (u8PortNum, TYPEC_ROLE_SOURCE, TYPEC_ROLE_SOURCE_15);
    
    }
    /*Rp value as 3.0A@5V */
    else
    {
        gasTypeCcontrol[u8PortNum].u8CCDebMatch = (TYPEC_CC_THRES3_MATCH | TYPEC_CC_THRES6_MATCH);
        gasTypeCcontrol[u8PortNum].u8CCSrcSnkMatch = (TYPEC_CC_THRES6_MATCH);
        
        /*Setting the current Rp value as TYPEC_RP_CURRENT_30 in u8PortSts variable*/
        gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_CURR_RPVAL_MASK;
        gasTypeCcontrol[u8PortNum].u8PortSts |= (TYPEC_RP_CURRENT_30 << TYPEC_CURR_RPVAL_POS);
        
        /*Setting the Rp Value as SinkTxOk*/
        TypeC_SetPowerRole (u8PortNum, TYPEC_ROLE_SOURCE, TYPEC_ROLE_SOURCE_30);
    }
    
    /*Enabling the CC Sampling in the sink attached CC pin if both sink and powered cable 
    are attached*/   
    /*Sink Attached in CC1 since VCONN is enabled in CC2*/
    if (((gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VCONN_SOURCE_MASK)) == TYPEC_VCONN_SOURCE_CC2)
    {      
        TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1);
        
        /*Changing the CC Sampling value as per the Rp value set*/
        TypeC_SetCCSampleEnable (u8PortNum, TYPEC_ENABLE_CC1_SAMPLING);
    }
    /*Sink Attached in CC2 since VCONN is enabled in CC1*/
    else if(((gasTypeCcontrol[u8PortNum].u8IntStsISR & TYPEC_VCONN_SOURCE_MASK)) == TYPEC_VCONN_SOURCE_CC1)
    {        
        TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC2);
        
        /*Changing the CC Sampling value as per the Rp value set*/
        TypeC_SetCCSampleEnable (u8PortNum, TYPEC_ENABLE_CC2_SAMPLING);    
    }
    /*Enabling the CC Sampling in both the CC pins if only sink is attached*/
    else
    {
        TypeC_ConfigCCComp (u8PortNum, TYPEC_CC_COMP_CTL_CC1_CC2);
        
        /*Changing the CC Sampling value as per the Rp value set*/
        TypeC_SetCCSampleEnable (u8PortNum, (TYPEC_ENABLE_CC1_SAMPLING | TYPEC_ENABLE_CC2_SAMPLING));
    }
    
}

UINT8 TypeC_CheckRpValCollAvoidance(UINT8 u8PortNum)
{
     
     HOOK_DEBUG_PORT_STR (u8PortNum,"TYPEC: Check Rp Value API called from PRL\r\n");
     
     /*Return TYPEC_SINK_TXNG if the current Rp Value set by source is TYPEC_SINK_TXNG 1.5A Rp*/
     UINT8 u8RpStatus = TYPEC_SINK_TXNG;
    
    /*Setting the collsion avoidance active bit in u8PortSts variable*/
     gasTypeCcontrol[u8PortNum].u8PortSts  |= (TYPEC_COLLISION_AVOIDANCE_ACT);
    
     /*Return True if the current Rp Value set by source is TYPEC_SINK_TXOK*/
     if(((gasTypeCcontrol[u8PortNum].u8PortSts & TYPEC_CURR_RPVAL_MASK) \
         >> TYPEC_CURR_RPVAL_POS) == TYPEC_RP_CURRENT_30)
     {
        /*Clear the Collision avoidance Status variable*/
        gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_COLLISION_AVOIDANCE_ACT;
        u8RpStatus = TYPEC_SINK_TXOK;       
     
     }     
     return u8RpStatus;
 
}


void TypeC_KillTypeCTimer (UINT8 u8PortNum)
{
    PDTimer_Kill (gasTypeCcontrol[u8PortNum].u8TypeC_TimerID);
    
    /*Setting the u8PETimerID to MAX_CONCURRENT_TIMERS to indicate that
    TimerID does not hold any valid timer IDs anymore*/
    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = MAX_CONCURRENT_TIMERS;
    
}

/**************************************************************/

void TypeC_VBUSDrive(UINT8 u8PortNum, UINT16 u16Voltage)
{	
  	/* After driving the VBUS only Power Fault configuration are done
		Thus, TYPEC_CONFIG_NON_PWR_FAULT_THR passed */
    TypeC_ConfigureVBUSThr(u8PortNum, u16Voltage, TYPEC_CONFIG_NON_PWR_FAULT_THR);
	
    CONFIG_HOOK_PORTPWR_DRIVE_VBUS (u8PortNum, u16Voltage);  
}

/**************************************************************/
void TypeC_ConfigureVBUSThr(UINT8 u8PortNum, UINT16 u16Voltage, UINT8 u8PowerFaultThrConfig)
{
  	UINT16 u16PrevVolt = DPM_GetVBUSVoltage(u8PortNum);
	UINT8 u8SampleEn = 0;
	
	/*Setting the VBUS Comparator OFF*/
	TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_OFF);

	
	/* **************************Power Fault threshold configuration**************************/
	#if INCLUDE_POWER_FAULT_HANDLING
	if ((u8PowerFaultThrConfig) && (PWRCTRL_VBUS_0V != u16Voltage))
	{
            /* if fault has occured start the Power Good Timer */
            if (gasDPM[u8PortNum].u8VBUSPowerFaultCount > SET_TO_ZERO)
            {
                PDTimer_Kill (gasDPM[u8PortNum].u8VBUSPowerGoodTimerID);
                gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = PDTimer_Start (CONFIG_DPM_POWER_GOOD_TIMER_MS,\
                                                              TypeC_PowerGood_TimerCB, u8PortNum, NULL);
            }
            
            /* Over voltage threshold is set in TypeC_ConfigureVBUSThr */	
			UINT16 au16VBUSThrVal[] = {	TYPEC_GET_OVER_VOLTAGE_VBUS_THR(u16Voltage),
										TYPEC_GET_UNDER_VOLTAGE_VBUS_THR(u16Voltage)
										};
			
			/*Setting the default threshold values in VBUS threshold X(0-4) registers*/ 
			UPD_RegisterWrite (u8PortNum, TYPEC_VBUS_THR2, (UINT8 *)au16VBUSThrVal, sizeof(au16VBUSThrVal));  
			
			/*Enable the VBUS sample */
			u8SampleEn = (TYPEC_VSAFE0V_MAX_THR_MATCH | TYPEC_VSINKDISCONNECT_THR0_MATCH | \
                                TYPEC_DESIRED_MIN_V_THR1_MATCH | TYPEC_OVER_VOLT_THR2_MATCH| \
                                  TYPEC_UNDER_VOLT_THR3_MATCH);
			
			#if INCLUDE_UPD_PIO_OVERRIDE_SUPPORT
				/* Enable PIO override for over voltage*/
				UPD_RegByteSetBit (u8PortNum, UPD_PIO_OVR_EN, UPD_PIO_OVR_0);
			#endif
	}
	else
	#endif /*INCLUDE_POWER_FAULT_HANDLING*/
	/*****************************VBUS threshould configuration for all voltages ****************/  
	{
        #if INCLUDE_POWER_FAULT_HANDLING
        #if INCLUDE_UPD_PIO_OVERRIDE_SUPPORT
            if (PWRCTRL_VBUS_0V != u16Voltage)
            {
                /* Set the PIO override enable on VBUS_EN
                    to override the VBUS_EN to low on detecting  OCS event*/
                UPD_RegByteSetBit (u8PortNum, UPD_PIO_OVR_EN,  UPD_PIO_OVR_1);
                
            }
        #endif /*endif of INCLUDE_UPD_PIO_OVERRIDE_SUPPORT*/
        #endif /*endif of INCLUDE_POWER_FAULT_HANDLING*/
            
      UINT16 u16MinVoltageThr =0;
      UINT16 u16MaxVoltageThr = 0;
      
	  switch(u16Voltage)
	  {
		case PWRCTRL_VBUS_0V:
		{
            /* Corresponding VSafe0V VBUS sample enable */
            u8SampleEn = TYPEC_VSAFE0V_MAX_THR_MATCH;
			
            if(PD_ROLE_SOURCE == DPM_GET_CURRENT_POWER_ROLE(u8PortNum))
            {
                /* Enable VBUS discharge only if the port role is source*/
                CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);
            
            }            
                
			#if INCLUDE_UPD_PIO_OVERRIDE_SUPPORT
				/* clear the PIO override enable for Over voltage*/
				UPD_RegByteClearBit (u8PortNum, UPD_PIO_OVR_EN, (UPD_PIO_OVR_0 | UPD_PIO_OVR_1));
			#endif
				
			break; 
		} /* end of PWRCTRL_VBUS_0V*/
		
		case PWRCTRL_VBUS_5V:
		{
            /* Minimum valid Vsafe5V threshold is configured in u16MinVoltageThr*/
            /* Maximum Vsafe5V threshold is configured in u16MaxVoltageThr*/
            if(PD_ROLE_SOURCE == DPM_GET_CURRENT_POWER_ROLE(u8PortNum))
            {
                u16MinVoltageThr = TYPEC_DESIRED_MIN_SRC_VSAFE5V_VBUS_THR;
                u16MaxVoltageThr = TYPEC_DESIRED_MAX_SRC_VSAFE5V_VBUS_THR;
            }
            else
            {
                u16MinVoltageThr = TYPEC_DESIRED_MIN_SNK_VSAFE5V_VBUS_THR;
                u16MaxVoltageThr = TYPEC_DESIRED_MAX_SNK_VSAFE5V_VBUS_THR;  
            }
            break;
				
		}/* end of PWRCTRL_VBUS_5V*/
		
	  	default:
		{
			/* Minimum valid PDO voltage configured in u16MinVoltageThr*/
            /* Maximum PDO voltage threshold is configured in u16MaxVoltageThr*/
			u16MinVoltageThr = TYPEC_GET_DESIRED_MIN_VBUS_THR(u16Voltage);
            u16MaxVoltageThr = TYPEC_GET_DESIRED_MAX_VBUS_THR(u16Voltage);
			break;
		}/* end of default*/
        
	  }/* end of switch*/
      
      if (PWRCTRL_VBUS_0V != u16Voltage)
      {
        /* Minimum valid voltage is configured to VBUS Threshold 1*/
        UPD_RegWriteWord (u8PortNum, TYPEC_VBUS_THR1, u16MinVoltageThr);

        if (u16PrevVolt > u16Voltage)
        {
            if(PD_ROLE_SOURCE == DPM_GET_CURRENT_POWER_ROLE(u8PortNum))
            {
               /* Enable VBUS discharge only if the port role is source*/
                CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE (u8PortNum, PWRCTRL_ENABLE_VBUSDIS);            
            }
            
            /* Set Threshold 1 to previous voltage*/
            UPD_RegWriteWord (u8PortNum, TYPEC_VBUS_THR4, u16MaxVoltageThr);
            
            /* Corresponding VBUS sample enable */
            u8SampleEn = (TYPEC_VSAFE0V_MAX_THR_MATCH | TYPEC_VSINKDISCONNECT_THR0_MATCH |
                            TYPEC_DESIRED_MIN_V_THR1_MATCH | TYPEC_PREV_V_DROP_CHK_THR4_MATCH);
        }
        else
        {
           /* Corresponding VBUS sample enable */
           u8SampleEn = (TYPEC_VSAFE0V_MAX_THR_MATCH | TYPEC_VSINKDISCONNECT_THR0_MATCH |
                      TYPEC_DESIRED_MIN_V_THR1_MATCH);
        }
      }
      
	} /* end of u8PowerFaultThrConfig else*/
				
	/*Enabling VBUS sample*/
	UPD_RegWriteByte (u8PortNum, TYPEC_VBUS_SAMP_EN, u8SampleEn);
	
	/*Setting the VBUS Comparator ON*/
	TypeC_SetVBUSCompONOFF (u8PortNum, TYPEC_VBUSCOMP_ON);
}
/************************************************************************/								   
	
#if INCLUDE_POWER_FAULT_HANDLING

								   
void TypeC_PowerGood_TimerCB (UINT8 u8PortNum, UINT8 u8TypeCState)
{
	/* Set the timer Id to Max Cont Value*/
 	gasDPM[u8PortNum].u8VBUSPowerGoodTimerID = MAX_CONCURRENT_TIMERS;
	
	/* Reset the fault Count*/
	gasDPM[u8PortNum].u8VBUSPowerFaultCount = RESET_TO_ZERO;
}


#endif /*INCLUDE_POWER_FAULT_HANDLING endif*/

/*********************************************************************/
/*Generic timer call back routine for device policy manager*/
void TypeC_SubStateChange_TimerCB (UINT8 u8PortNum, UINT8 u8TypeCSubState)
{	
	gasTypeCcontrol[u8PortNum].u8TypeCSubState  = u8TypeCSubState;
    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = MAX_CONCURRENT_TIMERS;
}


void TypeC_StateChange_TimerCB (UINT8 u8PortNum, UINT8 u8TypeCState)
{
    gasTypeCcontrol[u8PortNum].u8TypeCState = u8TypeCState;
    gasTypeCcontrol[u8PortNum].u8TypeCSubState  = 0;
    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = MAX_CONCURRENT_TIMERS;
  
}

void TypeC_VCONNONErrorTimerCB (UINT8 u8PortNum , UINT8 u8DummyVariable)
{
    
    gasTypeCcontrol[u8PortNum].u8PortSts &= ~TYPEC_VCONN_ON_REQ_MASK;
    
    if(gasDPM[u8PortNum].u8VCONNErrCounter > CONFIG_MAX_VCONN_FAULT_COUNT)
    {   
        gasDPM[u8PortNum].u8VCONNErrCounter = 0;
        
        /*Disable VBUS by driving to vSafe0V*/
        TypeC_VBUSDrive (u8PortNum, PWRCTRL_VBUS_0V);
        
        /*Disable VCONN by switching off the VCONN FETS which was enabled previously*/
        TypeC_EnabDisVCONN (u8PortNum, TYPEC_VCONN_DISABLE);
        
        /* Assign an idle state wait for detach*/
        gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ATTACHED_SRC_IDLE_SS;       
        gasPolicy_Engine[u8PortNum].ePEState = ePE_INVALIDSTATE;
        gasPolicy_Engine[u8PortNum].ePESubState = ePE_INVALIDSUBSTATE;
        
        HOOK_DEBUG_PORT_STR(u8PortNum,"VCONN_ON_ERROR: Entered SRC Powered OFF state");
    }
    else
    {
    
         gasDPM[u8PortNum].u8VCONNErrCounter++;
    
        /* Set it to Type C Error Recovery */
        gasTypeCcontrol[u8PortNum].u8TypeCState = TYPEC_ERROR_RECOVERY;
        gasTypeCcontrol[u8PortNum].u8TypeCSubState = TYPEC_ERROR_RECOVERY_ENTRY_SS;
    }
    
    gasTypeCcontrol[u8PortNum].u8TypeC_TimerID = MAX_CONCURRENT_TIMERS;
   
}

/**********************************************************************/
