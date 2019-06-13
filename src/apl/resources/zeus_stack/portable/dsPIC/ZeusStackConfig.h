
/*******************************************************************************
  Zeus stack configuration

  Company:
    Microchip Technology Inc.

  File Name:
    ZeusStackConfig.h

  Summary:
    Zeus stack configuration header file

  Description:
    This header file contains the configuration parameters of zeus stack to configures the Power delivery modules
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************

Copyright © 2018 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
********************************************************************************

*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: File includes - USER_APPLICATION FILES CAN GO HERE
// *****************************************************************************
// *****************************************************************************


#include <stdbool.h>
#include <string.h>
#include "../../../pd_timer/upd_timer.h"
#include "../../../spi2/spi2.h"
#include "..\..\hook_functions.h"


/**********************************************************************
  Description:
    CONFIG_PD_PORT_COUNT refers to the number of Power delivery enabled
    ports
  Remarks:
   None
  Example:
  <code>
    \#define CONFIG_PD_PORT_COUNT 2     
 </code>
  **********************************************************************/
#define CONFIG_PD_PORT_COUNT	2	 	


// *****************************************************************************
// *****************************************************************************
// Section: INCLUDE/EXCLUDE AT COMPILE TIME
// *****************************************************************************
// *****************************************************************************


/**************************************************************************************************
	Description:
		Setting the INCLUDE_PD_3_0 as 1 enables the stack to include USB Power delivery 3.0 specification features like Collision Avoidance, Chuncking along with PD 2.0 features at the compile.User can set this 
		define to 0 to reduce code size of the stack if none of the PD enabled ports require PD 3.0 specific features and operates only at PD 2.0 specification.

	Remarks:
		None

	Example:

	<code>
	#define INCLUDE_PD_3_0	1(Include USB PD 3.0 specific features from Zeus Stack)

	#define INCLUDE_PD_3_0	0(Exclude USB PD 3.0 specific features from Zeus Stack)
	</code>

**************************************************************************************************/
#define INCLUDE_PD_3_0   1       

/**************************************************************************************************
	Description:
		Setting the INCLUDE_PD_SOURCE_ONLY as 1 enables the stack to include the USB PD Source functionality at the compile time.User can set this 
		define to 0 to reduce code size of the stack if none of the PD enabled ports are source configured.

	Remarks:
		None
		

	Example:
	    <code>
		#define INCLUDE_PD_SOURCE_ONLY	1(Include USB PD Source functionality in Zeus Stack )

		#define INCLUDE_PD_SOURCE_ONLY	1(Exclude USB PD Source functionality from Zeus Stack )
		</code>

**************************************************************************************************/
#define INCLUDE_PD_SOURCE_ONLY  1

/**************************************************************************************************
	Description:
		Setting the INCLUDE_PD_SINK_ONLY as 1 enables the stack to include the USB PD Sink functionality at the compile time.User can set this 
		define to 0 to reduce code size of the stack if none of the PD enabled ports are sink configured.

	Remarks:
		None

	Example:
	    <code>
		#define INCLUDE_PD_SOURCE_ONLY	1(Include USB PD Source functionality in Zeus Stack)

		#define INCLUDE_PD_SOURCE_ONLY	1(Exclude USB PD Source functionality from Zeus Stack)
		</code>

**************************************************************************************************/
#define INCLUDE_PD_SINK_ONLY  0

/**************************************************************************************************
	Description:
		Setting the INCLUDE_VCONN_SWAP_SUPPORT as 1 enables the stack to include the VCONN Swap functionality at the compile time.User can set this 
		define to 0 to reduce code size of the stack if none of the PD enabled ports requires VCONN Swap functionality.

	Remarks:
		None
		

	Example:
	    <code>
		#define INCLUDE_VCONN_SWAP_SUPPORT	1(Include VCONN Swap functionality in Zeus Stack )

		#define INCLUDE_VCONN_SWAP_SUPPORT	0(Exclude VCONN Swap functionality from Zeus Stack )
		</code>

**************************************************************************************************/

#define INCLUDE_VCONN_SWAP_SUPPORT  0

/**************************************************************************************************
	Description:
		Setting the INCLUDE_POWER_FAULT_HANDLING as 1 enables the stack to handle Power fault handling
		(Source & Sink OVP, Source OCS, Sink under voltage)as per Power Delivery specification R3.0 as applicable.

	Remarks:
		None

	Example:

	<code>
	#define INCLUDE_POWER_FAULT_HANDLING	1(Include Power Fault handling to Zeus Stack)

	#define INCLUDE_POWER_FAULT_HANDLING	0(Exclude Power Fault handling from Zeus Stack)
	</code>

**************************************************************************************************/
#define INCLUDE_POWER_FAULT_HANDLING          0

/**************************************************************************************************
	Description:
		Setting the INCLUDE_UPD_PIO_OVERRIDE_SUPPORT as 1 enables the stack to disable EN_VBUS instantly
		when it detects a Power fault. It uses PIO Override feature of UPD350 silicon
		
	Remarks:
		Applicable only if UPD350 PIO is used as EN_VBUS.
		Confined to INCLUDE_POWER_FAULT_HANDLING define.
		INCLUDE_POWER_FAULT_HANDLING should be declared as 1 for INCLUDE_UPD_PIO_OVERRIDE_SUPPORT
		define to be effective.

	Example:

	<code>
	#define INCLUDE_UPD_PIO_OVERRIDE_SUPPORT	1(Include UPD350 PIO Override support for Power fault to Zeus stack)

	#define INCLUDE_UPD_PIO_OVERRIDE_SUPPORT	0(Exclude UPD350 PIO Override support for Power fault from Zeus stack)
	</code>

**************************************************************************************************/

#define INCLUDE_UPD_PIO_OVERRIDE_SUPPORT      0


/**************************************************************************************************
	Description:
		Setting the INCLUDE_UPD301_SPECIFIC as 1 enables UPD301 specific inclusion.
		
	Remarks:
		It should be maintained 0 for Zeus stack

	Example:

	<code>
	#define INCLUDE_UPD301_SPECIFIC         1(Include UPD301 specific inclusion)

	#define INCLUDE_UPD301_SPECIFIC     	0(Exclude UPD301 specific inclusion)
	</code>

**************************************************************************************************/
#define INCLUDE_UPD301_SPECIFIC				  0


/**************************************************************************************************
	Description:
		Setting the INCLUDE_POWER_MANAGEMENT_CTRL as 1 enables the stack to include the functionalities 
        to put the UPD350 and the Companion MCU into low power mode when there are no alerts
        from connected UPD350s for CONFIG_PORT_UPD_IDLE_TIMEOUT_MS time
		
	Remarks:
        Define the followings CONFIG_HOOK_SET_MCU_IDLE() , CONFIG_HOOK_MCU_RESUME_FROM_IDLE() ,
        CONFIG_PORT_UPD_IDLE_TIMEOUT_MS if INCLUDE_POWER_MANAGEMENT_CTRL is set to one

	Example:

	<code>
	#define INCLUDE_POWER_MANAGEMENT_CTRL	1(Include power management feature for MCU and UPD350s)

	#define INCLUDE_POWER_MANAGEMENT_CTRL	0(Exclude power management feature for MCU and UPD350s)
	</code>

**************************************************************************************************/
#define INCLUDE_POWER_MANAGEMENT_CTRL         0


/**************************************************************************
  Description:
    INCLUDE_PDFU includes the PD Firmware Update state machine code for the
    compilation process.
  Remarks:
    For integrating the PD Firmware Update functionality, INCLUDE_PDFU
    macro shall be enabled in both Fixed and updatable application.
  Example:
    <code>
    \#define INCLUDE_PDFU    TRUE
    </code>
                                                                           
  **************************************************************************/
#define INCLUDE_PDFU 0        


// *****************************************************************************
// *****************************************************************************
// Section: HOOK CONFIGURATION
// *****************************************************************************
// *****************************************************************************
#define CONFIG_HOOK_PDO_REQUEST_POST_PROCESS_VALID(_u8_Port_Num, _u16_Max_Current, _u8_Pdo_Requested)    \
            hook_pdo_request_post_process_valid(_u8_Port_Num, _u16_Max_Current, _u8_Pdo_Requested)

/***********************************************************************************************************
  Function:
              CONFIG_HOOK_POLICY_ENGINE_PRE_PROCESS(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)
  Summary:
    This function is called before entering into the policy engine state
    machine
  Description:
    This function is called at the entry of PE_RunStateMachine() API before
    executing the policy engine state machine.New PD message received by
    the protocol layer is passed as argument in this function before
    processing it in the policy engine state machine.USER_APPLICATION can
    define this function if a change in default policy engine state machine
    behaviour is needed. Define relevant function that has one UINT8
    argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _u8DataBuf_ -   Pointer to a byte buffer containing PD message.
    _u8SOPType_ -   Sop Type of the message
    _u32Header_ -   32 bit header passed of which lower word is PD message
                    header and higher word is extended message header if
                    passed message is extended message.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_POLICY_ENGINE_PRE_PROCESS(_u8Port_Num_, _u8DataBuf_\\
    ,_u8SOPType_,_u32Header_)\\
    HookPolicyEnginePreProcess(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)
    
    void HookPolicyEnginePreProcess(UINT8 u8PortNum , UINT8 *u8DataBuf , UINT8 u8SOPType ,UINT32 u32Header);
    
    void HookPolicyEnginePreProcess(UINT8 u8PortNum , UINT8 *u8DataBuf , UINT8 u8SOPType ,UINT32 u32Header)
    {
    
        //any application related change or enhancement for the PE_RunStateMachine() API
    
    }
    </code>
  Remarks:
    User definition of this Hook function is optional                                                       
  ***********************************************************************************************************/
#define CONFIG_HOOK_POLICY_ENGINE_PRE_PROCESS(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)    \
            hook_policy_engine_pre_process(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)

/************************************************************************************************************
  Function:
          CONFIG_HOOK_POLICY_ENGINE_POST_PROCESS(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)
    
  Summary:
    This function is called before exiting from the policy engine state
    machine
  Description:
    This function is called at the exit of PE_RunStateMachine() API after
    executing the policy engine state machine. USER_APPLICATION can define
    this function if a change in default policy engine state machine
    behaviour is needed. Define relevant function that has one UINT8
    argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _u8DataBuf_ -   Pointer to a byte buffer containig PD message to be send
    _u8SOPType_ -   Sop Type of the message to be send
    _u32Header_ -   32 bit header of the PD message to be send.Lower word is
                    PD message header and higher word is extended message
                    header if passed message is extended message.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_POLICY_ENGINE_POST_PROCESS(_u8Port_Num_, _u8DataBuf_, \\
    _u8SOPType_,_u32Header_) \\
    HookPolicyEnginePostProcess(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_)
    
    void HookPolicyEnginePostProcess(UINT8 u8PortNum , UINT8 *u8DataBuf , UINT8 u8SOPType ,UINT32 u32Header);
    
    void HookPolicyEnginePostProcess(UINT8 u8PortNum , UINT8 *u8DataBuf , UINT8 u8SOPType ,UINT32 u32Header)
    {
    
    //any application related change or enhancement for the PE_RunStateMachine() API
    
    }
    </code>
  Remarks:
    User definition of this Hook function is optional                                                        
  ************************************************************************************************************/
#define CONFIG_HOOK_POLICY_ENGINE_POST_PROCESS(_u8Port_Num_, _u8DataBuf_, _u8SOPType_,_u32Header_) 			

/**************************************************************************
  Function:
            CONFIG_HOOK_DEVICE_POLICY_MANAGER_PRE_PROCESS(_u8port_num_)
  Summary:
    This function is called before entering into the DPM state machine
  Description:
    This function is called at the entry of DPM_StateMachine() API before
    executing the Type C state machine and policy engine state machine.
    USER_APPLICATION can define this function if a change is required in
    default device policy manager functionality. Define relevant function
    that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_DEVICE_POLICY_MANAGER_PRE_PROCESS(_u8port_num_) \\
                    HookDevicePolicyManagerPreProcess(_u8port_num_)
    
    void HookDevicePolicyManagerPreProcess(UINT8 u8PortNum);
    
    void HookDevicePolicyManagerPreProcess(UINT8 u8PortNum)
    {
    
        //any application related change or enhancement for the
        //DPM_StateMachine() API
    
    }
    </code>
  Remarks:
    User definition of this Hook function is optional                      
  **************************************************************************/
#define CONFIG_HOOK_DEVICE_POLICY_MANAGER_PRE_PROCESS(_u8port_num_) 	

/*************************************************************************************
  Function:
            CONFIG_HOOK_DEVICE_POLICY_MANAGER_POST_PROCESS(_u8port_num_)
  Summary:
    This function is called before exiting from the DPM state machine
  Description:
    This function is called at the exit of DPM_StateMachine() API after
    executing the Type C state machine and policy engine state machine.
    USER_APPLICATION can define this function if a change is required in
    default device policy manager functionality. Define relevant function
    that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_DEVICE_POLICY_MANAGER_POST_PROCESS(_u8port_num_) \\
                          HookDevicePolicyManagerPostProcess(_u8port_num_)
    
    void HookDevicePolicyManagerPostProcess(UINT8 u8PortNum);
    
    void HookDevicePolicyManagerPostProcess(UINT8 u8PortNum)
    {
    
        //any application related change or enhancement for the DPM_StateMachine() API
    
    }
    </code>

  Remarks:
    User definition of this Hook function is optional                                 
  *************************************************************************************/
#define CONFIG_HOOK_DEVICE_POLICY_MANAGER_POST_PROCESS(_u8port_num_) 	

/******************************************************************************************
  Function:
          CONFIG_HOOK_TYPE_C_MANANGEMENT_PRE_PROCESS(_u8port_num_)
    
  Summary:
    This function is called before entering into the Type C state machine
  Description:
    This function is called at the entry of TypeC_RunStateMachine() API
    before executing the TypeC state machine. USER_APPLICATION can define
    this function if a change in default Type C state machine behaviour is
    needed. Define relevant function that has one UINT8 argument without
    \return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_TYPE_C_MANANGEMENT_PRE_PROCESS(_u8port_num_)   \\
     HookTypeCManagementPreProcess(_u8port_num_)
    
    void HookTypeCManagementPreProcess(UINT8 u8PortNum);
    
    void HookTypeCManagementPreProcess(UINT8 u8PortNum)
    {
    
        //any application related change or enhancement for the TypeC_RunStateMachine() API
    
    }
    </code>
  Remarks:
    None                                                                                   
  ******************************************************************************************/
#define CONFIG_HOOK_TYPE_C_MANANGEMENT_PRE_PROCESS(_u8port_num_)		

/******************************************************************************************
  Function:
          CONFIG_HOOK_TYPE_C_MANANGEMENT_POST_PROCESS(_u8port_num_)
    
  Summary:
    This function is called before exiting from the Type C state machine
  Description:
    This function is called at the exit of TypeC_RunStateMachine() API
    after executing the TypeC state machine. USER_APPLICATION can define
    this function if a change in default TypeC state machine behaviour is
    needed. Define relevant function that has one UINT8 argument without
    \return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_TYPE_C_MANANGEMENT_POST_PROCESS(_u8port_num_)   \\
    HookTypeCManagementPostProcess(_u8port_num_)
    
    void HookTypeCManagementPostProcess(UINT8 u8PortNum);
    
    void HookTypeCManagementPostProcess(UINT8 u8PortNum)
    {
    
        //any application related change or enhancement for the TypeC_RunStateMachine() API
    
    }
    </code>
  Remarks:
    None                                                                                   
  ******************************************************************************************/
#define CONFIG_HOOK_TYPE_C_MANANGEMENT_POST_PROCESS(_u8port_num_)

/********************************************************************************************************************************************
  Function:
              CONFIG_HOOK_PRL_TX_MSG_PRE_PROCESS(_u8port_num_, _u8sop_type_, _u32header_, _pu8databuff_, _pfntxcallback_, _u32PkdPEstOn_TxStatus_)
    
  Summary:
    This function is called before processing the transmit message data
    from policy engine in protocol layer
  Description:
    This function is called at the entry of PRL_Tranmsit() API before
    processing the Message from Policy Engine. It has all the arguments
    passed to the API PRL_Transmit() by policy engine It is a placeholder
    for USER_APPLICATION to enhance the API.Define relevant function that
    has UINT8,UINT8,UINT32,UINT8 * ,PRLTxCallback and UINT32 arguments
    without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -                         Port number of the device. Value
                                           passed will be less than
                                           CONFIG_PD_PORT_COUNT
    _u8sop_type_ -                          Sop Type of the message
    _u32header_ -                           32 bit header passed of which
                                           lower word is PD message header &amp;
                                           higher word is extended message
                                           header if passed message is
                                           extended message.
    _pu8databuff_ -                         pointer to a byte buffer
                                           containig PD message
    _pfntxcallback_ -                       Pointer to callback function of
                                           type PRLTxCallback
    _u32PkdPEstOn_TxStatus_ -               argument to Tx callback function<p />
    Prototype of PRLTxCallback function -  void (*PRLTxCallback)(UINT8
                                           u8PortNum, UINT8 u8TxDonePEst,
                                           UINT8 u8TxDonePESubst, UINT8
                                           u8TxFailedPEst, UINT8
                                           u8TxFailedPESubst);
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_PRL_TX_MSG_PRE_PROCESS(_u8port_num_, _u8sop_type_, _u32header_,\\
       _pu8databuff_,_pfntxcallback_, _u32PkdPEstOn_TxStatus_) \\
        HookPRLTxMsgPreProcess(_u8port_num_, _u8sop_type_, _u32header_, _pu8databuff_,\\
        _pfntxcallback_,_u32PkdPEstOn_TxStatus_)
    
        void HookPRLTxMsgPreProcess(UINT8 u8PortNum, UINT8 u8SOPType, UINT32 u32Header, UINT8 *pu8DataBuffer,
                       PRLTxCallback pfnTxCallback, UINT32  u32PkdPEstOnTxStatus);
    
        void HookPRLTxMsgPreProcess(UINT8 u8PortNum, UINT8 u8SOPType, UINT32 u32Header, UINT8 *pu8DataBuffer,
                       PRLTxCallback pfnTxCallback, UINT32  u32PkdPEstOnTxStatus)
        {
            //any application related change or enhancement for the PRL_Tranmsit() API
        }
    
    </code>
  Remarks:
    None                                                                                                                                     
  ********************************************************************************************************************************************/
#define CONFIG_HOOK_PRL_TX_MSG_PRE_PROCESS(_u8port_num_, _u8sop_type_, _u32header_, _pu8databuff_, _pfntxcallback_, _u32PkdPEstOn_TxStatus_)

/*****************************************************************************************************************************************
  Function:
          CONFIG_HOOK_PRL_TX_MSG_POST_PROCESS(_u8port_num_, _u8sop_type_, _u32header_, _pu8databuff_, _pfntxcallback_, _u32PkdPEstOn_TxStatus_)
    
  Summary:
    This function is called after processing the transmit message data from
    policy engine to UPD350 FIFO format
  Description:
    This function is called in PRL_Tranmsit() API after processing the
    message from Policy Engine into UPD350 FIFO format.Exactly,After
    filling the UPD350's TX_FIFO. It has all the arguments passed to the
    API PRL_Transmit() by policy engine It is a placeholder for
    USER_APPLICATION to enhance the API.Define relevant function that has
    UINT8,UINT8,UINT32,UINT8 * ,PRLTxCallback and UINT32 arguments without
    \return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -                         Port number of the device. Value
                                           passed will be less than
                                           CONFIG_PD_PORT_COUNT
    _u8sop_type_ -                          Sop Type of the message
    _u32header_ -                           32 bit header passed of which
                                           lower word is PD message header &amp;
                                           higher word is extended message
                                           header if passed message is
                                           extended message.
    _pu8databuff_ -                         pointer to a byte buffer
                                           containig PD message
    _pfntxcallback_ -                       Pointer to callback function of
                                           type PRLTxCallback
    _u32PkdPEstOn_TxStatus_ -               argument to Tx callback function<p />
    Prototype of PRLTxCallback function -  void (*PRLTxCallback)(UINT8
                                           u8PortNum, UINT8 u8TxDonePEst,
                                           UINT8 u8TxDonePESubst, UINT8
                                           u8TxFailedPEst, UINT8
                                           u8TxFailedPESubst);
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_PRL_TX_MSG_POST_PROCESS(_u8port_num_, _u8sop_type_, _u32header_,\\
        _pu8databuff_,pfntxcallback_, _u32PkdPEstOn_TxStatus_)\\
        HookPRLTxMsgPostProcess(_u8port_num_, _u8sop_type_, _u32header_,\\
        _pu8databuff_, _pfntxcallback_, _u32PkdPEstOn_TxStatus_)
    
        void HookPRLTxMsgPostProcess(UINT8 u8PortNum, UINT8 u8SOPType, UINT32 u32Header, UINT8 *pu8DataBuffer,
                       PRLTxCallback pfnTxCallback, UINT32  u32PkdPEstOnTxStatus);
    
        void HookPRLTxMsgPostProcess(UINT8 u8PortNum, UINT8 u8SOPType, UINT32 u32Header, UINT8 *pu8DataBuffer,
                       PRLTxCallback pfnTxCallback, UINT32  u32PkdPEstOnTxStatus)
        {
            //any application related change or enhancement for the PRL_Tranmsit() API
        }
    
    </code>
  Remarks:
    None                                                                                                                                  
  *****************************************************************************************************************************************/
#define CONFIG_HOOK_PRL_TX_MSG_POST_PROCESS(_u8port_num_, _u8sop_type_, _u32header_, _pu8databuff_, _pfntxcallback_, _u32PkdPEstOn_TxStatus_)

/**************************************************************************************
  Function:
          \#define CONFIG_HOOK_PRL_RX_MSG_PRE_PROCESS(_u8port_num_)
    
  Summary:
    This function is called before receiving the message from UPD350's
    RX_FIFO
  Description:
    The function is called at the entry of PRL_ReceiveMsg() API.It is a
    placeholder for USER_APPLICATION to enhance the API. Define relevant
    \function that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_PRL_RX_MSG_PRE_PROCESS(_u8port_num_)     \\
        HookPRLRxMsgPreProcess(_u8port_num_)
    
       void HookPRLRxMsgPreProcess(UINT8 u8Portnum);
    
       void HookPRLRxMsgPreProcess(UINT8 u8Portnum)
        {
            //any application related change or enhancement for the  PRL_ReceiveMsg API
        }
    
    </code>
  Remarks:
    None                                                                               
  **************************************************************************************/
#define CONFIG_HOOK_PRL_RX_MSG_PRE_PROCESS(_u8port_num_)

/**********************************************************************************
  Function:
          \#define CONFIG_HOOK_PRL_RX_MSG_POST_PROCESS(_u8port_num_)
    
  Summary:
    This function is called after receiving and processing the message from
    UPD350's RX_FIFO
  Description:
    The function is called at the exit of PRL_ReceiveMsg() API. It is a
    placeholder for USER_APPLICATION to enhance the API. Define relevant
    \function that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_PRL_RX_MSG_POST_PROCESS(_u8port_num_)   \\
    HookPRLRxMsgPostProcess(_u8port_num_)
    
    void HookPRLRxMsgPostProcess(UINT8 u8Portnum);
    
    void HookPRLRxMsgPostProcess(UINT8 u8Portnum)
    {
    
        //any application related change or enhancement for the  PRL_ReceiveMsg API
    
    }
    
    </code>
  Remarks:
    None                                                                           
  **********************************************************************************/
#define CONFIG_HOOK_PRL_RX_MSG_POST_PROCESS(_u8port_num_)

/************************************************************************************************
  Function:
          \#define CONFIG_HOOK_PRL_CHUNK_SM(_u8port_num_)
    
  Summary:
    This function is called before running the chunk state machine
  Description:
    The function is called at the entry of PRL_RunChunkStateMachine() API.
    It is a placeholder for USER_APPLICATION to enhance the API. Define
    relevant function that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_PRL_CHUNK_SM(_u8port_num_)  \\
        HookPRLChunkSM(_u8port_num_)
    
        void HookPRLChunkSM(UINT8 u8Portnum);
    
        void HookPRLChunkSM(UINT8 u8Portnum)
        {
            // any application related change or enhancement for the PRL_RunChunkStateMachine API
        }
    
    </code>
  Remarks:
    None                                                                                         
  ************************************************************************************************/
#define CONFIG_HOOK_PRL_CHUNK_SM(_u8port_num_)

/************************************************************************************
  Function:
          \#define CONFIG_HOOK_UPD_ALERT_ISR_ALL_PORT(_u8port_num_)
    
  Summary:
    This function is called before processing the UPD alert interrupt
  Description:
    The function is called at the entry of UPDIntr_AlertHandler() API. It
    is a placeholder for USER_APPLICATION to enhance the API. Define
    relevant function that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_UPD_ALERT_ISR_ALL_PORT(_u8port_num_)    \\
    HookUPDAlertISRAllPort(_u8port_num_)
    
    void HookUPDAlertISRAllPort(UINT8 u8Portnum);
    
    void HookUPDAlertISRAllPort(UINT8 u8Portnum)
    {
        // any application related change or enhancement for UPDIntr_AlertHandler API
    }
    
    </code>
  Remarks:
    None                                                                             
  ************************************************************************************/
#define CONFIG_HOOK_UPD_ALERT_ISR_ALL_PORT(_u8port_num_)				

/****************************************************************************************************
  Function:
                \#define CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(_u8port_num_, _u8pd_event_)
    
  Summary:
    Notifies the USER_APPLICATION about various PD events such as Type C
    Attach and Detach , Type C orientation .
  Description:
    This function is called by the various modules of Zeus Stack to notify
    the USER_APPLICATION about different PD events such as Type-C Attach
    and Detach , Type-C Orientation. USER_APPLICATION can define this hook
    \function if it wants external handling of the PD events. Define
    relevant function that has one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _u8pd_event_ -   Type of PD event occurred inside the stack. This
                    argument can take one of the following,<p />TYPEC_ATTACH_EVENT
                    \- Attach event is detected in Type C State<p />machine<p />TYPEC_DETACH_EVENT
                    \- Detach event is detected in Type C State<p />machine<p />TYPEC_CC1_ORIENTATION
                    \- Attach is detected in CC1 pin<p />TYPEC_CC2_ORIENTATION
                    \- Attach is detected in CC2 pin
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(_u8port_num_, _u8pd_event_) \\
    HookNotifyPDEvents(_u8port_num_, _u8pd_event_)
    
    void HookNotifyPDEvents(UINT8 u8Portnum, UINT8 u8PDEvents);
    
    void HookNotifyPDEvents(UINT8 u8Portnum, UINT8 u8PDEvents)
    {
    
         Switch(u8PDEvents)
        {
            case TYPEC_ATTACH_EVENT:
            {
                //USER_APPLICATION code for Type C attach event in "u8PortNum" Port
                break;
    
            }
            case TYPEC_DETACH_EVENT:
            {
                //USER_APPLICATION code for Type C detach event in "u8PortNum" Port
                break;
    
            }
            case TYPEC_CC1_ORIENTATION:
            {
                //USER_APPLICATION code for Type C attach event in CC1 of "u8PortNum" Port
                break;
    
            }
            case TYPEC_CC2_ORIENTATION:
            {
                //USER_APPLICATION code for Type C attach event in CC2 of "u8PortNum" Port
                break;
    
            }
            default:
            {
                break;
            }
    
        }
    
    }
    
    </code>
  Remarks:
    User definition of this Hook function is optional                                                
  ****************************************************************************************************/
#define CONFIG_HOOK_NOTIFY_PD_EVENTS_CB(_u8port_num_, _u8pd_event_)    \
        hook_notify_pd_events_cb(_u8port_num_, _u8pd_event_)

#define TYPEC_ATTACH_EVENT                  0
#define TYPEC_DETACH_EVENT                  1
#define TYPEC_CC1_ORIENTATION               2
#define TYPEC_CC2_ORIENTATION               3
#define TYPEC_ATTACHED_SRC_DRIVE_PWR_EVENT  4

/**************************************************************************************************
	Function:
		CONFIG_HOOK_UPDATE_CFG_GLOBALS(_CfgGlobals_)

	Summary :
		Updates the configuration parameters of stack at run time

	Description :
		This function is called to update the configuration parameters at run time during initialization of the stack. 
		This API must have a prototype of PORT_CONFIG_DATA as argument without any return type.
		
	Precondition :
		None.

	Parameters :
		_CfgGlobals_ - Holds the variable of the structure PORT_CONFIG_DATA

	Return :
		None.

	Example :

		<code>
		#define  CONFIG_HOOK_UPDATE_CFG_GLOBALS(_CfgGlobals_)            STRAPS_PowerRole_Set(_CfgGlobals_)

		void STRAPS_PowerRole_Set(PORT_CONFIG_DATA *PortConfigData);

		void STRAPS_PowerRole_Set(PORT_CONFIG_DATA *PortConfigData)
		{
			// Read Straps for enabled ports 1 to n
			
			if(gpio_get_pin_level(PA28) == PULL_UP)
			{
				// Configure Cfg variables for Source
				// Set Source Capabilities
			}
			
			else
			{
				// Configure Cfg variables for sink
				// Set Sink Capabilities
			}
			
			// Repeat the above steps upto port n

		}
		</code>

	Remarks:
		User definition of this Hook function is optional
**************************************************************************************************/
#define  CONFIG_HOOK_UPDATE_CFG_GLOBALS(CfgGlobals)  	

/**************************************************************************************************
	Function:
		CONFIG_HOOK_PORTS_ENABLE_DISABLE (_pu8PortsEnDis_)

	Summary :
		Update the port Enable/Disable parameters of stack at run time.

	Description :
		This function is called to update the port Enable/Disable parameters at run time during initialization of the stack
        and port Enable/Disable status can be read from this API.
        		
	Precondition :
		None.

	Parameters :
		PortsEnDis - Holds the array of port Enable/Disable variable

	Return :
		None.

	Example :

		<code>
		#define  CONFIG_HOOK_PORTS_ENABLE_DISABLE (_pu8PortsEnDis_)       Ports_EnableDisable(_pu8PortsEnDis_)

		void Ports_EnableDisable(UINT8 *u8PortEnDis);

		void Ports_EnableDisable(UINT8 *u8PortEnDis)
		{
			// if Port-0 to be enabled
            u8PortEnDis[0] = PORT_STATUS_ENABLED;

            // if Port-1 to be disabled
            u8PortEnDis[1] = PORT_STATUS_DISABLED;

		}
		</code>

	Remarks:
		User definition of this Hook function is optional
**************************************************************************************************/
#define  CONFIG_HOOK_PORTS_ENABLE_DISABLE(_pu8PortsEnDis_)       

// *****************************************************************************
// *****************************************************************************
// Section: DEBUG MESSAGES CONFIGURATION
// *****************************************************************************
// *****************************************************************************
#define CONFIG_HOOK_DEBUG_MSG 1

#if CONFIG_HOOK_DEBUG_MSG
        /***********************************************************************
          Function:
                  \#define CONFIG_HOOK_DEBUG_INIT()
            
          Summary:
            Initialization of debug module
          Description:
            This function is called during
            initialization of stack if CONFIG_HOOK_DEBUG_MSG is set to 1. Define
            relevant function that has no arguments without return type.
          Conditions:
            None.
          Return:
            None.
          Example:
            <code>
                \#define CONFIG_HOOK_DEBUG_INIT()          uart_init()
            
                void uart_init();
            
                void uart_init()
                {
                    //Initialzes the uart module to send and receive a character
                }
            
            </code>
          Remarks:
            User definition of this Hook function is optional                   
          ***********************************************************************/  
	#define CONFIG_HOOK_DEBUG_INIT()				                                

    /*************************************************************************
      Function:
              \#define CONFIG_HOOK_DEBUG_STRING(_str_)
        
      Summary:
        Initialization of debug module
      Description:
        This function is called by stack to send
        a character string to DEBUG_MODULE. This API will be called if
        CONFIG_HOOK_DEBUG_MSG is set to 1. Define relevant function that has
        CHAR pointer argument without return type.
      Conditions:
        None.
      Input:
        _str_ -  Pointer to the character buffer
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_STRING(_str_)       uart_write(_str_)
        
            void uart_write(char *chBuffer);
        
            void uart_write(char *chBuffer)
            {
                //Write character string to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                     
      *************************************************************************/ 
	#define CONFIG_HOOK_DEBUG_STRING(_str_)	hook_debug_print_string(_str_)	                                  

    /************************************************************************
      Function:
              \#define CONFIG_HOOK_DEBUG_CHAR(_char_)
        
      Summary:
        Send CHAR to DEBUG_MODULE
      Description:
        This function is called by stack to send a character to DEBUG_MODULE.
        This API will be called if CONFIG_HOOK_DEBUG_MSG is set to 1. Define
        relevant function that has CHAR argument without return type.
      Conditions:
        None.
      Input:
        chName -  Character to be sent to DEBUG_MODULE
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_CHAR(_char_)   uart_write(_char_)
        
            void uart_write(char chName);
        
            void uart_write(char chName)
            {
                //Write character to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                    
      ************************************************************************/ 
	#define CONFIG_HOOK_DEBUG_CHAR(_char_)	DEBUG_write(_char_)		                               

    /**************************************************************************
      Function:
              \#define CONFIG_HOOK_DEBUG_UINT8(_u8Val_)
        
      Summary:
        Send UINT8 to DEBUG_MODULE
      Description:
        This function is called by stack to send a
        UINT8 data to DEBUG_MODULE This API will be called if
        CONFIG_HOOK_DEBUG_MSG is set to 1. Define relevant function that has
        UINT8 argument without return type.
      Conditions:
        None.
      Input:
        u8Val -  UINT8 data to be sent to DEBUG_MODULE
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_UINT8(_u8Val_)     uart_write(_u8Val_)
        
            void uart_write(UINT8 u8Val);
        
            void uart_write(UINT8 u8Val)
            {
                //Convert UINT8 to character string and write to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                      
      **************************************************************************/ 
	#define CONFIG_HOOK_DEBUG_UINT8(_u8Val_)	hook_debug_u8(_u8Val_)	                               

    /*************************************************************************
      Function:
              \#define CONFIG_HOOK_DEBUG_UINT16(_u16Val_)
        
      Summary:
        Send UINT16 to DEBUG_MODULE
      Description:
        This function is called by stack to send
        a UINT16 data to DEBUG_MODULE This API will be called if
        CONFIG_HOOK_DEBUG_MSG is set to 1. Define relevant function that has
        UINT16 argument without return type.
      Conditions:
        None.
      Input:
        u16Val -  UINT16 data to be sent to DEBUG_MODULE
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_UINT16(_u16Val_)     uart_write(_u16Val_)
        
            void uart_write(UINT16 u16Val);
        
            void uart_write(UINT16 u16Val)
            {
                //Convert UINT16 to character string and write to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                     
      *************************************************************************/ 
	#define CONFIG_HOOK_DEBUG_UINT16(_u16Val_)	hook_debug_u16(_u16Val_)	                          

    /*************************************************************************
      Function:
              \#define CONFIG_HOOK_DEBUG_UINT32(_u32Val_)
        
      Summary:
        Send UINT32 to DEBUG_MODULE
      Description:
        This function is called by stack to send
        a UINT32 data to DEBUG_MODULE. This API will be called if
        CONFIG_HOOK_DEBUG_MSG is set to 1. Define relevant function that has a
        UINT32 argument without return type.
      Conditions:
        None.
      Input:
        u32Val -  UINT32 data to be sent to DEBUG_MODULE
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_UINT32(_u32Val_)    uart_write(_u32Val_)
        
            void uart_write(UINT32 u32Val);
        
            void uart_write(UINT32 u32Val)
            {
                //Convert UINT32 to character string and write to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                     
      *************************************************************************/ 
	#define CONFIG_HOOK_DEBUG_UINT32(_u32Val_)	hook_debug_u32(_u32Val_)	                            

    /**************************************************************************
      Function:
                \#define CONFIG_HOOK_DEBUG_INT32(_i32Val_)
        
      Summary:
        Send INT32 to DEBUG_MODULE
      Description:
        This function is called by stack to send
        a INT32 data to DEBUG_MODULE. This API will be called if
        CONFIG_HOOK_DEBUG_MSG is set to 1. Define relevant function that has
        INT32 argument without return type.
      Conditions:
        None.
      Input:
        i32Val -  INT32 data to be sent to DEBUG_MODULE
      Return:
        None.
      Example:
        <code>
            \#define CONFIG_HOOK_DEBUG_UINT16(_i32Val_)        uart_write(_i32Val_)
        
            void uart_write(INT32 i32Val);
        
            void uart_write(INT32 i32Val)
            {
                //Convert INT32 to character string and write to UART
            }
        
        </code>
      Remarks:
        User definition of this Hook function is optional                      
      **************************************************************************/ 
    #define CONFIG_HOOK_DEBUG_INT32(_i32Val_)	hook_debug_i32(_i32Val_)	                               

#else
	#define CONFIG_HOOK_DEBUG_INIT()				
	#define CONFIG_HOOK_DEBUG_STRING(_str_)		
	#define CONFIG_HOOK_DEBUG_CHAR(_char_)			
	#define CONFIG_HOOK_DEBUG_UINT8(_u8Val_)		
	#define CONFIG_HOOK_DEBUG_UINT16(_u16Val_)			
	#define CONFIG_HOOK_DEBUG_UINT32(_u32Val_)
    #define CONFIG_HOOK_DEBUG_INT32(_i32Val_)	
#endif


// *****************************************************************************
// *****************************************************************************
// Section: Timeout configuration
// *****************************************************************************
// *****************************************************************************

/**************************************************************************************************
	Description:
	CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS refers to the tCCDebounce timeout specified in the USB Type C Specification.Default value of CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS is set as 150 milliseconds

	Remarks:
	CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB Type C Compliant

	Example:
	<code>
	#define CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS		MILLISECONDS_TO_TICKS(150)
	</code>

**************************************************************************************************/
#define CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS			MILLISECONDS_TO_TICKS(150)
/**************************************************************************************************
	Description:
	CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS refers to the tPDDebounce timeout specified in the USB Type C Specification.Default value of CONFIG_TYPEC_TCCDEBOUNCE_TIMEOUT_MS is set as 10 milliseconds

	Remarks:
	CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB Type C Compliant

	Example:
	<code>
	#define CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS		MILLISECONDS_TO_TICKS(10)
	</code>

**************************************************************************************************/
#define CONFIG_TYPEC_TPDEBOUNCE_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(10)
			       
/**************************************************************************************************
	Description:
	CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS refers to the tErrorRecovery timeout specified in the USB Type C Specification.Default value of CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS is set as 25 milliseconds

	Remarks:
	CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB Type C Compliant

	Example:
	<code>
	#define CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS		MILLISECONDS_TO_TICKS(25)
	</code>
**************************************************************************************************/
#define CONFIG_TYPEC_ERRORRECOVERY_TIMEOUT_MS         MILLISECONDS_TO_TICKS(500)

/**************************************************************************************************
	Description:
	CONFIG_TYPEC_VCONNDISCHARGE_TIMEOUT_MS refers to the tVCONNDischarge timeout specified in the USB Type C Specification.Default value of CONFIG_TYPEC_VCONNDISCHARGE_TIMEOUT_MS is set as 35 milliseconds

	Remarks:
	CONFIG_TYPEC_VCONNDISCHARGE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB Type C Compliant

	Example:
	<code>
	#define CONFIG_TYPEC_VCONNDISCHARGE_TIMEOUT_MS		MILLISECONDS_TO_TICKS(35)
	</code>
**************************************************************************************************/
#define CONFIG_TYPEC_VCONNDISCHARGE_TIMEOUT_MS        MILLISECONDS_TO_TICKS(35)  

/**************************************************************************************************
	Description:
	CONFIG_PE_SOURCECAPABILITY_TIMEOUT_MS refers to the SourceCapabilityTimer specified in the USB-PD Specification.Default value of CONFIG_PE_SOURCECAPABILITY_TIMEOUT_MS is set as 200 milliseconds

	Remarks:
	CONFIG_PE_SOURCECAPABILITY_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SOURCECAPABILITY_TIMEOUT_MS		MILLISECONDS_TO_TICKS(150)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SOURCECAPABILITY_TIMEOUT_MS          MILLISECONDS_TO_TICKS(150)

/**************************************************************************************************
Description:
CONFIG_TYPEC_VBUS_ON_TIMER_MS refers to the tVBUSON specified in the USB-TypeC Specification.Default value of CONFIG_TYPEC_VBUS_ON_TIMER_MS is set as 275 milliseconds

Remarks:
CONFIG_TYPEC_VBUS_ON_TIMER_MS can be configured depending on the microcontroller platform for the device to be  USB-TypeC Compliant

Example:
<code>
#define CONFIG_TYPEC_VBUS_ON_TIMER_MS			        MILLISECONDS_TO_TICKS(275)
</code>
**************************************************************************************************/
#define CONFIG_TYPEC_VBUS_ON_TIMER_MS			        MILLISECONDS_TO_TICKS(275)

/**************************************************************************************************
Description:
CONFIG_TYPEC_VBUS_OFF_TIMER_MS refers to the tVBUSOFF specified in the USB-TypeC Specification.Default value of CONFIG_TYPEC_VBUS_OFF_TIMER_MS is set as 650 milliseconds

Remarks:
CONFIG_TYPEC_VBUS_OFF_TIMER_MS can be configured depending on the microcontroller platform for the device to be USB-TypeC Compliant

Example:
<code>
#define CONFIG_TYPEC_VBUS_OFF_TIMER_MS                MILLISECONDS_TO_TICKS(650)
</code>
**************************************************************************************************/
#define CONFIG_TYPEC_VBUS_OFF_TIMER_MS                MILLISECONDS_TO_TICKS(650)            

/**************************************************************************************************
Description:
CONFIG_SRC_READY_TIMER_MS refers to the tSrcReady specified in the PD 3.0 Specification.Default value of CONFIG_SRC_READY_TIMER_MS is set as 285 milliseconds

Remarks:
CONFIG_SRC_READY_TIMER_MS can be configured depending on the microcontroller platform for the device to be USB-TypeC Compliant

Example:
<code>
#define CONFIG_SRC_READY_TIMER_MS                MILLISECONDS_TO_TICKS(285)
</code>
**************************************************************************************************/   
#define CONFIG_SRC_READY_TIMER_MS                     MILLISECONDS_TO_TICKS(285)

/**************************************************************************************************
Description:
CONFIG_TYPEC_VCONNON_TIMEOUT_MS refers to the tVCONNON specified in the USB-Type C Specification.Default value of CONFIG_TYPEC_VCONNON_TIMEOUT_MS is set as 2 milliseconds

Remarks:
CONFIG_TYPEC_VCONNON_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB-Type C

Example:
<code>
#define CONFIG_TYPEC_VCONNON_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(10)
</code>
**************************************************************************************************/
#define CONFIG_TYPEC_VCONNON_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(10)
    
/**************************************************************************************************
Description:
CONFIG_PE_VCONNON_TIMEOUT_MS refers to the tVCONNSourceOn specified in the USB PD Specification.Default value of CONFIG_PE_VCONNON_TIMEOUT_MS is set as 100 milliseconds

Remarks:
CONFIG_PE_VCONNON_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD

Example:
<code>
#define CONFIG_PE_VCONNON_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(100)
</code>
**************************************************************************************************/
#define CONFIG_PE_VCONNON_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(100)

/**************************************************************************************************
Description:
CONFIG_PE_VCONNON_SELF_TIMEOUT_MS refers to the tVCONNSourceOn specified in the USB PD Specification.Default value of CONFIG_PE_VCONNON_TIMEOUT_MS is set as 100 milliseconds

Remarks:
CONFIG_PE_VCONNON_SELF_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD

Example:
<code>
#define CONFIG_PE_VCONNON_SELF_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(150)
</code>
**************************************************************************************************/
#define CONFIG_PE_VCONNON_SELF_TIMEOUT_MS			    MILLISECONDS_TO_TICKS(150)

/**************************************************************************************************
Description:
CONFIG_TYPEC_VCONNOFF_TIMEOUT_MS refers to the tVCONNOFF specified in the USB-Type C Specification.Default value of CONFIG_TYPEC_VCONNOFF_TIMEOUT_MS is set as 25 milliseconds

Remarks:
CONFIG_TYPEC_VCONNOFF_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB-Type C

Example:
<code>
#define CONFIG_TYPEC_VCONNOFF_TIMEOUT_MS               MILLISECONDS_TO_TICKS(25)
</code>
**************************************************************************************************/
#define CONFIG_TYPEC_VCONNOFF_TIMEOUT_MS               MILLISECONDS_TO_TICKS(25)
    
/**************************************************************************************************
Description:
CONFIG_PE_VCONNOFF_TIMEOUT_MS refers to the tVCONNOFF specified in the USB-Type C Specification.Default value of CONFIG_PE_VCONNOFF_TIMEOUT_MS is set as 35 milliseconds

Remarks:
CONFIG_PE_VCONNOFF_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB-Type C

Example:
<code>
#define CONFIG_PE_VCONNOFF_TIMEOUT_MS               MILLISECONDS_TO_TICKS(35)
</code>
**************************************************************************************************/
#define CONFIG_PE_VCONNOFF_TIMEOUT_MS               MILLISECONDS_TO_TICKS(35)

/**************************************************************************************************
	Description:
	CONFIG_PE_NORESPONSE_TIMEOUT_SECS refers to the NoResponseTimer specified in the USB-PD Specification.Default value of CONFIG_PE_NORESPONSE_TIMEOUT_SECS is set as 5.5 seconds

	Remarks:
	CONFIG_PE_NORESPONSE_TIMEOUT_SECS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_NORESPONSE_TIMEOUT_SECS		MILLISECONDS_TO_TICKS(5500)
	</code>
**************************************************************************************************/
#define CONFIG_PE_NORESPONSE_TIMEOUT_SECS               MILLISECONDS_TO_TICKS(5500)
/**************************************************************************************************
	Description:
	CONFIG_PE_SENDERRESPONSE_TIMEOUT_MS refers to the SenderResponseTimer specified in the USB-PD Specification.Default value of CONFIG_PE_SENDERRESPONSE_TIMEOUT_MS is set as 26 milliseconds

	Remarks:
	CONFIG_PE_SENDERRESPONSE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SENDERRESPONSE_TIMEOUT_MS            MILLISECONDS_TO_TICKS(26)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SENDERRESPONSE_TIMEOUT_MS            MILLISECONDS_TO_TICKS(26)
/**************************************************************************************************
	Description:
	CONFIG_PE_SINKWAITCAP_TIMEOUT_MS refers to the SinkWaitCapTimer specified in the USB-PD Specification.Default value of CONFIG_PE_SINKWAITCAP_TIMEOUT_MS is set as 465 milliseconds

	Remarks:
	CONFIG_PE_SINKWAITCAP_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SINKWAITCAP_TIMEOUT_MS               MILLISECONDS_TO_TICKS(465)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SINKWAITCAP_TIMEOUT_MS               MILLISECONDS_TO_TICKS(465)
/**************************************************************************************************
	Description:
	CONFIG_PE_PSTRANSITION_TIMEOUT_MS refers to the PSTransitionTimer specified in the USB-PD Specification.Default value of CONFIG_PE_PSTRANSITION_TIMEOUT_MS is set as 500 milliseconds

	Remarks:
	CONFIG_PE_PSTRANSITION_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_PSTRANSITION_TIMEOUT_MS              MILLISECONDS_TO_TICKS(500)
	</code>
**************************************************************************************************/
#define CONFIG_PE_PSTRANSITION_TIMEOUT_MS              MILLISECONDS_TO_TICKS(500)
/**************************************************************************************************
	Description:
	CONFIG_PE_SINKREQUEST_TIMEOUT_MS refers to the SinkRequestTimer specified in the USB-PD Specification.Default value of CONFIG_PE_SINKREQUEST_TIMEOUT_MS is set as 100 milliseconds

	Remarks:
	CONFIG_PE_SINKREQUEST_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SINKREQUEST_TIMEOUT_MS               MILLISECONDS_TO_TICKS(100)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SINKREQUEST_TIMEOUT_MS               MILLISECONDS_TO_TICKS(100)
/**************************************************************************************************
	Description:
	CONFIG_PE_VDMRESPONSE_TIMEOUT_MS refers to the VDMResponseTimer specified in the USB-PD Specification.Default value of CONFIG_PE_VDMRESPONSE_TIMEOUT_MS is set as 28 milliseconds

	Remarks:
	CONFIG_PE_VDMRESPONSE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_VDMRESPONSE_TIMEOUT_MS              MILLISECONDS_TO_TICKS(28)
	</code>
**************************************************************************************************/
#define CONFIG_PE_VDMRESPONSE_TIMEOUT_MS              MILLISECONDS_TO_TICKS(28)
/**************************************************************************************************
    Description:
	CONFIG_PE_PSHARDRESET_TIMEOUT_MS refers to the PSHardResetTimer specified in the USB-PD Specification.Default value of CONFIG_PE_PSHARDRESET_TIMEOUT_MS is set as 28 milliseconds

	Remarks:
	CONFIG_PE_PSHARDRESET_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_PSHARDRESET_TIMEOUT_MS             MILLISECONDS_TO_TICKS(28)
	</code>
**************************************************************************************************/
#define CONFIG_PE_PSHARDRESET_TIMEOUT_MS             MILLISECONDS_TO_TICKS(28)
/**************************************************************************************************
	Description:
	CONFIG_PE_SRCRECOVER_TIMEOUT_MS refers to the tSrcRecover specified in the USB-PD Specification.Default value of CONFIG_PE_SRCRECOVER_TIMEOUT_MS is set as 800 milliseconds

	Remarks:
	CONFIG_PE_SRCRECOVER_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SRCRECOVER_TIMEOUT_MS               MILLISECONDS_TO_TICKS(800)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SRCRECOVER_TIMEOUT_MS               MILLISECONDS_TO_TICKS(800)

/**************************************************************************************************
	Description:
	CONFIG_PE_SRCTRANSISTION_TIMEOUT_MS refers to the tSrcTransistionTimer specified in the USB-PD Specification.

	Remarks:
	CONFIG_DPM_POWER_GOOD_TIMER_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PE_SRCTRANSISTION_TIMEOUT_MS             MILLISECONDS_TO_TICKS(30)
	</code>
**************************************************************************************************/
#define CONFIG_PE_SRCTRANSISTION_TIMEOUT_MS	      MILLISECONDS_TO_TICKS(28)

/**************************************************************************************************
	Description:
	CONFIG_PRL_CHUNKSENDERREQUEST_TIMEOUT_MS refers to the ChunkSenderRequestTimer specified in the USB-PD Specification.Default value of CONFIG_PRL_CHUNKSENDERREQUEST_TIMEOUT_MS is set as 26 milliseconds

	Remarks:
	CONFIG_PRL_CHUNKSENDERREQUEST_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PRL_CHUNKSENDERREQUEST_TIMEOUT_MS		MILLISECONDS_TO_TICKS(26)
	</code>
**************************************************************************************************/
#define CONFIG_PRL_CHUNKSENDERREQUEST_TIMEOUT_MS		MILLISECONDS_TO_TICKS(26)
/**************************************************************************************************
	Description:
	CONFIG_PRL_CHUNKSENDERRESPONSE_TIMEOUT_MS refers to the ChunkSenderResponseTimer specified in the USB-PD Specification.Default value of CONFIG_PRL_CHUNKSENDERRESPONSE_TIMEOUT_MS is set as 26 milliseconds

	Remarks:
	CONFIG_PRL_CHUNKSENDERRESPONSE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PRL_CHUNKSENDERRESPONSE_TIMEOUT_MS    MILLISECONDS_TO_TICKS(26)
	</code>
**************************************************************************************************/
#define CONFIG_PRL_CHUNKSENDERRESPONSE_TIMEOUT_MS    MILLISECONDS_TO_TICKS(26)

/**************************************************************************************************
	Description:
	CONFIG_PRL_SINKTX_TIMEOUT_MS refers to the SinkTxTimer specified in the USB-PD Specification.Default value of CONFIG_PRL_SINKTX_TIMEOUT_MS is set as 16 milliseconds

	Remarks:
	CONFIG_PRL_SINKTX_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PRL_SINKTX_TIMEOUT_MS				    MILLISECONDS_TO_TICKS(16)
	</code>
**************************************************************************************************/
#define CONFIG_PRL_SINKTX_TIMEOUT_MS				    MILLISECONDS_TO_TICKS(16)

/**************************************************************************************************
	Description:
	CONFIG_PRL_BIST_CONTMODE_TIMEOUT_MS refers to the BISTContModeTimer specified in the USB-PD Specification.
	Default value of CONFIG_PRL_BIST_CONTMODE_TIMEOUT_MS is set as 45 milliseconds.

	Remarks:
	CONFIG_PRL_BIST_CONTMODE_TIMEOUT_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_PRL_BIST_CONTMODE_TIMEOUT_MS			MILLISECONDS_TO_TICKS(45)
	</code>
**************************************************************************************************/
#define CONFIG_PRL_BIST_CONTMODE_TIMEOUT_MS			MILLISECONDS_TO_TICKS(45)

/**************************************************************************************************
	Description:
	For power Source it is time that a power source must consistently provide power without a power fault
	to determine the power is good and a fault condition does not exist.
	For power sink it is the time that after the has sink has established a contract and is consistently
	drawing power from VBUS without a power fault to determine that power is good and a fault condition does not exist.

	Remarks:
	CONFIG_DPM_POWER_GOOD_TIMER_MS can be configured depending on the microcontroller platform for the device to be USB PD Compliant

	Example:
	<code>
	#define CONFIG_DPM_POWER_GOOD_TIMER_MS			MILLISECONDS_TO_TICKS(10000)
	</code>
**************************************************************************************************/
#define CONFIG_DPM_POWER_GOOD_TIMER_MS			MILLISECONDS_TO_TICKS(10000)
    
/**************************************************************************************************
	Description:
	If there is changes in VDD33 in UPD301, it will affect the VBUS being driven in the Port0.
    It will take some time for the corrected DAC output with respect to changed VDD33
    to get effective on VBUS line and UPD301 to detect the same.
    CONFIG_UPD301_VBUS_EFFECTIVE_TIMER_MS is delaying this purpose; the maximum time FW
    will wait for the corrected DAC output to be effective on the VBUS.
    

	Remarks:
	CONFIG_UPD301_VBUS_EFFECTIVE_TIMER_MS is confined to INCLUDE_UPD301_SPECIFIC define.
	
	Example:
	<code>
	#define CONFIG_UPD301_VBUS_EFFECTIVE_TIMER_MS			MILLISECONDS_TO_TICKS(15)
	</code>
**************************************************************************************************/
#define CONFIG_UPD301_VBUS_EFFECTIVE_TIMER_MS			MILLISECONDS_TO_TICKS(15)    

// *****************************************************************************
// *****************************************************************************
// Section: PDTimer configuration
// *****************************************************************************
// *****************************************************************************
/***********************************************************************
  Function:
            CONFIG_HOOK_HW_PDTIMER_INIT()
    
  Summary:
    Initializes and starts the hardware timer module.
  Description:
    This function initializes and starts the hardware timer module. Zeus
    Stack requires a single dedicated hardware timer module for its
    functionality. Define relevant function that has no argument without
    \return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_HW_PDTIMER_INIT()       hw_timer_init()
    
    void hw_timer_init(void);
    
    void hw_timer_init(void)
    {
        //Initializes and starts the microcontroller timer module
    }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                  
  ***********************************************************************/			      
#define CONFIG_HOOK_HW_PDTIMER_INIT()   PD_TMR_Initialize()          

/**************************************************************************************************
	Description :
	CONFIG_PDTIMER_INTERRUPT_RATE refers to the frequency of interrupt set in the hardware timer dedicated for zeus stack.In other words it is the resolution of the hardware timer.
	CONFIG_PDTIMER_INTERRUPT_RATE can be configured depending on the resolution of the hardware timer available

	Remarks :
	Resolution of the hardware timer has to be atleast 1ms.Tested resolution values of hardware timer are 500us,1ms(Corresponding CONFIG_PDTIMER_INTERRUPT_RATE values are 2000,1000)
	 
	Example :
	<code>
	# define CONFIG_PDTIMER_INTERRUPT_RATE 1000  (1000 interrupts per seconnd, with interrupt interval or resolution of 1ms)
	</code>
**************************************************************************************************/
#define CONFIG_PDTIMER_INTERRUPT_RATE	1000

/**************************************************************************************************
	Description :
	CONFIG_PORT_UPD_IDLE_TIMEOUT_MS is the amount of time waited by the power management control to
    put UPD350 into idle mode if no interrupt is received from it during that time

	Remarks :
	None

	Example :
	<code>
	#define CONFIG_PORT_UPD_IDLE_TIMEOUT_MS	  MILLISECONDS_TO_TICKS(15000)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_UPD_IDLE_TIMEOUT_MS 	MILLISECONDS_TO_TICKS(15000)

/**************************************************************************************************
	Description :
	CONFIG_HOOK_SET_MCU_IDLE() is the function defined by the user to put the companion MCU into 
    idle mode when all the connected UPD350s are in idle mode

	Remarks :
	None

	Example :
	<code>
	#define CONFIG_HOOK_SET_MCU_IDLE()	  SetMCUIdle()
	</code>
**************************************************************************************************/
#define CONFIG_HOOK_SET_MCU_IDLE()            	

/**************************************************************************************************
	Description :
	CONFIG_HOOK_MCU_RESUME_FROM_IDLE() is the function defined by the user to wake up the companion MCU 
    from idle mode if interrupt is received from any of the connected UPD350s

	Remarks :
	None

	Example :
	<code>
	#define CONFIG_HOOK_MCU_RESUME_FROM_IDLE()	  MCUResumeFromIdle()
	</code>
**************************************************************************************************/
#define CONFIG_HOOK_MCU_RESUME_FROM_IDLE()    

/**************************************************************************************************
	Description :
	CONFIG_16_BIT_PDTIMEOUT can be defined as either 1 or 0 to set the timeout variable in Zeus Stack to unsigned 16bit or unsigned 32bit correspondingly.
	When set as 1,maximum timeout that can be set will be 65535 ticks.(Ticks = Resolution of the Hardware timer used). When set as 0 , maximum timeout that can be set will be 4294967296 ticks.
	Default value of CONFIG_16_BIT_PDTIMEOUT is set as 1. With Hardware timer resolution set as 1ms , Zeus stack will be capable of handling timeouts upto 65.535 Seconds.

	Remarks :
	None

	Example :
	<code>
	#define CONFIG_16_BIT_PDTIMEOUT	1 (Sets timeout variable inside the PDStack unsigned 16bit)
	#define CONFIG_16_BIT_PDTIMEOUT	0 (Sets timeout variable inside the PDStack unsigned 32bit)
	</code>
**************************************************************************************************/
#define CONFIG_16_BIT_PDTIMEOUT     1

// *****************************************************************************
// *****************************************************************************
// Section: Port power control configuration
// *****************************************************************************
// *****************************************************************************

/*Initialization function of Hardware Module used for Port Power Control*/
#define PWRCTRL_VBUS_0V		0
#define PWRCTRL_VBUS_5V		5000
#define PWRCTRL_VBUS_9V		9000
#define PWRCTRL_VBUS_15V	15000
#define PWRCTRL_VBUS_20V	20000

/*Defines to be used for variable in u8EnaDisVBUSDIS PWRCTRL_SetVBUSDischarge API */
#define PWRCTRL_ENABLE_VBUSDIS      1
#define PWRCTRL_DISABLE_VBUSDIS     0
    
/*Defines to be used for variable in u8EnaDisVBUSDIS PWRCTRL_SetVBUSDischarge API */
#define PWRCTRL_ENABLE_SINK_HW      1
#define PWRCTRL_DISABLE_SINK_HW     0

/*****************************************************************************
  Function:
          CONFIG_HOOK_HW_PORTPWR_INIT()
  Summary:
    Initializes all the hardware modules related to port power
    functionality
  Description:
    This function initializes the hardware modules related to port power
    functionality. Implementation of this function depends on the type of
    DC-DC Converter used. Port power(VBUS) of all ports must be set to 0V
    in this API. Define relevant function that has no argument without
    \return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_HW_PORTPWR_INIT()       hw_portpower_init()
    
    void hw_portpower_init(void);
    
    void hw_portpower_init(void)
    {
        //Initializes the hardware modules related to port power functionality
    }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                        
  *****************************************************************************/
#define CONFIG_HOOK_HW_PORTPWR_INIT()  hw_portpower_init()

/****************************************************************************
  Function:
              CONFIG_HOOK_PORTPWR_DRIVE_VBUS(_u8Port_Num_, _u8VBUSVolatge_)
    
  Summary:
    Drives the VBUS line of a given Type C port to a particular voltage
  Description:
    This function is used to drive the VBUS line of a given Type C port to
    a particular voltage.Implementation of this function depends on the
    type of DC-DC Converter used. Define relevant function that has
    UINT8,UINT8 arguments without return type.
  Conditions:
    None.
  Input:
    _u8Port_Num_ -     Port number of the device. Value passed will be less
                       than CONFIG_PD_PORT_COUNT
    _u8VBUSVolatge_ -  VBUS Voltage level to be driven. Data type of this
                       parameter must be UINT8. Value of this argument must
                       be one of the following,<p />PWRCTRL_VBUS_0V \- 0V to
                       be driven in VBUS line<p />PWRCTRL_VBUS_5V \- 5V to
                       be driven in VBUS line<p />PWRCTRL_VBUS_9V \- 9V to
                       be driven in VBUS line<p />PWRCTRL_VBUS_15V \- 15V to
                       be driven in VBUS line<p />PWRCTRL_VBUS_20V \- 20V to
                       be driven in VBUS line
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_PORTPWR_DRIVE_VBUS(_u8Port_Num_, _u8VBUSVolatge_) \\
                      hw_portpower_driveVBUS(_u8Port_Num_, _u8VBUSVolatge_)
    
    void hw_portpower_driveVBUS(UINT8 u8PortNum,UINT8 u8VBUS_Volatge);
    
    void hw_portpower_driveVBUS(UINT8 u8PortNum,UINT8 u8VBUS_Volatge)
    {
    
        Switch(u8VBUS_Volatge)
        {
            case PWRCTRL_VBUS_0V:
            {
                //Drive 0V in VBUS line of "u8PortNum" Port
                break;
    
            }
            case PWRCTRL_VBUS_5V:
            {
                //Drive 5V in VBUS line of "u8PortNum" Port
                break;
    
            }
            case PWRCTRL_VBUS_9V:
            {
                //Drive 9V in VBUS line of "u8PortNum" Port
                break;
    
            }
            case PWRCTRL_VBUS_15V:
            {
                //Drive 15V in VBUS line of "u8PortNum" Port
                break;
    
            }
            case PWRCTRL_VBUS_20V:
            {
                //Drive 20V in VBUS line of "u8PortNum" Port
                break;
    
            }
            default:
            {
                break;
            }
    
        }
    
    
    }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                       
  ****************************************************************************/
#define CONFIG_HOOK_PORTPWR_DRIVE_VBUS(_u8Port_Num_, _u8VBUSVoltage_)	 hw_portpower_driveVBUS(_u8Port_Num_, _u8VBUSVoltage_)

/*******************************************************************************************
  Function:
                CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE( _u8Port_Num_,_u8EnableDisable_)
    
  Summary:
    Enables or disables VBUS Discharge functionality for a given Port
  Description:
    This function is used to enable or disable the VBUS Discharge
    functionality for a given Port .Implementation of this function depends
    on the type of DC-DC Converter used. Define relevant function that has
    UINT8,UINT8 arguments without return type.
  Conditions:
   CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE is called in ISR handler.
    This function must be very short, otherwise response time to the interrupt
    will take longer time.
  Input:
    _u8Port_Num_ -       Port number of the device. Value passed will be
                         less than CONFIG_PD_PORT_COUNT
    _u8EnableDisable_ -  Flag indicating whether to enable/disable VBUS
                         Discharge. Data type of this parameter must be
                         UINT8.<p />Value of this argument must be one of
                         the following,<p />PWRCTRL_ENABLE_VBUSDIS \- Enable
                         the VBUS Discharge for a given port<p />PWRCTRL_DISABLE_VBUSDIS
                         \- Disable the VBUS Discharge for a given port
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE(_u8Port_Num, _u8EnableDisable)   \\
                          hw_portpower_enab_dis_VBUSDischarge(_u8Port_Num, _u8EnableDisable)
    
    void hw_portpower_enab_dis_VBUSDischarge(UINT8 u8PortNum,UINT8 u8EnableDisable);
    
    void hw_portpower_enab_dis_VBUSDischarge(UINT8 u8PortNum,UINT8 u8EnableDisable)
    {
         Switch(u8EnableDisable)
        {
            case PWRCTRL_ENABLE_VBUSDIS:
            {
                //Enable the VBUS Discharge for "u8PortNum" Port
                break;
    
            }
            case PWRCTRL_DISABLE_VBUSDIS:
            {
                //Disable the VBUS Discharge for "u8PortNum" Port
                break;
    
            }
            default:
            {
                break;
            }
        }
    
    
    }
    </code>

  Remarks:
    User definition of this Hook function is mandatory.Passing of the Compliance test "TD.4.2.1" (Source Connect Sink) in "USB_Type_C_Functional_Test_Specification" depends on the VBUS Discharge circuitry used.
	Typical VBUS Discharge time from any higher voltage to 0V is around 10ms                                  
  *******************************************************************************************/
#define CONFIG_HOOK_PORTPWR_EN_DIS_VBUSDISCHARGE(_u8Port_Num, _u8EnableDisable_)  \
            hw_portpower_enab_dis_VBUSDischarge(_u8Port_Num, _u8EnableDisable_)
/*******************************************************************************************
  Function:
	CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(_u8Port_Num, _u8EnableDisable_)

  Summary:
	Enables or disables sink hardware circuitry which sinks the VBUS voltage for a given Port
  Description:
	  This function is used to enable or disable sink hardware circuitry which sinks the 
	  VBUS voltage for a given Port .Implementation of this function depends
	  on the type of Sink circuitary used. Define relevant function that has
	  UINT8,UINT8 arguments without return type.
  Conditions:
	None.
  Input:
	_u8Port_Num_ -       Port number of the device. Value passed will be
					     less than CONFIG_PD_PORT_COUNT
	_u8EnableDisable_ -  Flag indicating whether to enable/disable sink hardware circuitry.
					     Data type of this parameter must be UINT8.<p />
						 Value of this argument must be one of
					     the following,<p />PWRCTRL_ENABLE_SINK_HW \- Enable
					     the Sink circuitary for a given port<p />PWRCTRL_DISABLE_SINK_HW
						 \- Disable the Sink circuitary for a given port
  Return:
	None.
  Example:
	  <code>
		  \#define CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(_u8Port_Num, _u8EnableDisable_)  \\
		  hw_SinkCircuitary_enab_dis_(_u8Port_Num, _u8EnableDisable_)

		void hw_SinkCircuitary_enab_dis_(UINT8 u8PortNum,UINT8 u8EnableDisable);

		void hw_SinkCircuitary_enab_dis_(UINT8 u8PortNum,UINT8 u8EnableDisable)
		{
			Switch(u8EnableDisable)
			{
				case PWRCTRL_ENABLE_SINK_HW:
				{
					//Enable the Sink circuitary for "u8PortNum" Port
					break;

				}
				case PWRCTRL_DISABLE_SINK_HW:
				{
					//Disable the Sink circuitary for "u8PortNum" Port
					break;
				}
				default:
				{
					break;
				}
			}
		}

	  </code>

  Remarks:
	  User definition of this Hook function is mandatory.
  *******************************************************************************************/
#define CONFIG_HOOK_PORTPWR_ENABDIS_SINK_HW(_u8Port_Num, _u8EnableDisable_)	            

// *****************************************************************************
// *****************************************************************************
// Section: VSAFE5V lower & higher level defines
// *****************************************************************************
// *****************************************************************************
/**************************************************************************************************
	Description:
		CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE is maxmimum voltage acceptable for VSafe5V expressed 
		terms of millivolts for source. The voltage will be considered as valid Vsafe5V only if it is
        equal to or greater than CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE & less than
        CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE. CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V will be
        considered as overvoltage for Vsafe5V  incase of source.
        
        Valid Vsafe5V condition:
        CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE > Valid Vsafe5V <= CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE
        
        Overvoltage condition:
        Vsafe5V >= CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V

	Remarks:
		It is mandatory to define CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE.
        It must be defined in such a way that following condition is met.
        CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE < CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V.

	Example:
		<code>
		#define CONFIG_VSAFE5V_DESIRED_MAX_VOLTAGE			5500
		(</code>
**************************************************************************************************/
	
#define CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE 		5500

/**************************************************************************************************
	Description:
		CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE is minimum voltage acceptable for VSafe5V expressed 
		terms of millivolts for source. The voltage will be considered as valid Vsafe5V only if it is
        equal to or greater than CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE & less than 
        CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE. 

        Valid Vsafe5V condition:
        CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE > Valid Vsafe5V <= CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE

	Remarks:
		It is mandatory to define CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE.
        It must be defined in such a way that following condition is met.
        CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE > CONFIG_VSINKDISCONNECT_VOLTAGE.

	Example:
		<code>
		#define CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE			4750
		(</code>
**************************************************************************************************/

#define CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE 		4750
/**************************************************************************************************
	Description:
		CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE is maxmimum voltage acceptable for VSafe5V expressed 
		terms of millivolts for sink. The voltage will be considered as valid Vsafe5V only if it is
        equal to or greater than CONFIG_NK_VSAFE5V_DESIRED_MIN_VOLTAGE & less than
        CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE. CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V will be
        considered as overvoltage for Vsafe5V  incase of sink.

        Valid Vsafe5V condition:
        CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE > Valid Vsafe5V <= CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE
        
        Overvoltage condition:
        Vsafe5V >= CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V

	Remarks:
		It is mandatory to define CONFIG_SRC_VSAFE5V_DESIRED_MAX_VOLTAGE.
        It must be defined in such a way that following condition is met.
        CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE < CONFIG_OVER_VOLTAGE_FACTOR * PWRCTRL_VBUS_5V.

	Example:
		<code>
		#define CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE			5500
		(</code>
**************************************************************************************************/
	
#define CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE 5500

/**************************************************************************************************
	Description:
		CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE is minimum voltage acceptable for VSafe5V expressed 
		terms of millivolts for Sink. The voltage will be considered as valid Vsafe5V only if it is
        equal to or greater than CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE & less than
        CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE. 

	Valid Vsafe5V condition:
        CONFIG_SNK_VSAFE5V_DESIRED_MAX_VOLTAGE > Valid Vsafe5V <= CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE

	Remarks:
		It is mandatory to define CONFIG_SRC_VSAFE5V_DESIRED_MIN_VOLTAGE.
        It must be defined in such a way that following condition is met.
        CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE > CONFIG_VSINKDISCONNECT_VOLTAGE.
       

	Example:
		<code>
		#define CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE			4400
		(</code>
**************************************************************************************************/

#define CONFIG_SNK_VSAFE5V_DESIRED_MIN_VOLTAGE 4400


/**************************************************************************************************
	Description:
		CONFIG_VSINKDISCONNECT_VOLTAGE is the vSinkDisconnect mentioned in Type c specification.
        For Source Vsafe5V, CONFIG_VSINKDISCONNECT_VOLTAGE will be considered as undervoltage.
        For Sink, if the voltage is below CONFIG_VSINKDISCONNECT_VOLTAGE,
        it is considered as VBUS disconnect.

       Sink: 
       If Voltage <= CONFIG_VSINKDISCONNECT_VOLTAGE -> Sink disconnected
       
       Source:
       If Voltage <= CONFIG_VSINKDISCONNECT_VOLTAGE -> Source undervoltage

	Remarks:
		It is mandatory to define CONFIG_VSINKDISCONNECT_VOLTAGE.

	Example:
		<code>
		#define CONFIG_VSINKDISCONNECT_VOLTAGE			3670
		(</code>
**************************************************************************************************/

#define CONFIG_VSINKDISCONNECT_VOLTAGE 3670

	
// *****************************************************************************
// *****************************************************************************
// Section: Over voltage & under voltage configuration for Power faults
// *****************************************************************************
// *****************************************************************************
/**************************************************************************************************
	Description:
		CONFIG_OVER_VOLTAGE_FACTOR is percentange of PDO voltage to be considered as
		Over Voltage for that PDO.

	Remarks:
		if 110% of the PDO voltage has to be considered as overvoltage for that PDO voltage,
		then define CONFIG_OVER_VOLTAGE_FACTOR as 1.15.
		CONFIG_OVER_VOLTAGE_FACTOR must be defined when INCLUDE_POWER_FAULT_HANDLING is defined.

	Example:
		<code>
		#define CONFIG_OVER_VOLTAGE_FACTOR			1.15
		(CONFIG_PORT_0_SOURCE_PDO_1_VOLTAGE is 5000, then for PDO 1 Over voltage is 5750mV)
		</code>
**************************************************************************************************/
#define CONFIG_OVER_VOLTAGE_FACTOR					1.15

/**************************************************************************************************
	Description:
		CONFIG_UNDER_VOLTAGE_FACTOR is percentange of PDO voltage to be considered as
		under Voltage for that PDO.

	Remarks:
		if 85% of the PDO voltage has to be considered as undervoltage for that PDO voltage,
		then define CONFIG_UNDER_VOLTAGE_FACTOR as 0.85.
		CONFIG_UNDER_VOLTAGE_FACTOR must be defined when INCLUDE_POWER_FAULT_HANDLING is defined.

	Example:
		<code>
		#define CONFIG_UNDER_VOLTAGE_FACTOR			0.85

		</code>
**************************************************************************************************/
#define CONFIG_UNDER_VOLTAGE_FACTOR					0.85

/**************************************************************************************************
	Description:
		CONFIG_MAX_POWER_FAULT_COUNT is the maximum number of power fault conditions that can occur
		before the source or sink enters the latched off states of Sink Powered Off or Source Power Off.

	Remarks:
		None.

	Example:
		<code>
		#define CONFIG_MAX_POWER_FAULT_COUNT			3
		</code>
**************************************************************************************************/
#define CONFIG_MAX_POWER_FAULT_COUNT				3	

/**************************************************************************************************
	Description:
		CONFIG_MAX_VCONN_FAULT_COUNT is the maximum number of VCONN fault conditions that can occur
		before the source or sink enters the latched off states of Sink Powered Off or Source Power Off.

	Remarks:
		None.

	Example:
		<code>
		#define CONFIG_MAX_VCONN_FAULT_COUNT			3
		</code>
**************************************************************************************************/
#define CONFIG_MAX_VCONN_FAULT_COUNT  3


// *****************************************************************************
// *****************************************************************************
// Section: Port Specific configurations for CONFIG_PD_PORT_COUNT ports
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Port0 basic configurations
// *****************************************************************************
// *****************************************************************************        

/**************************************************************************************************
	Description:
		CONFIG_PORT_n_POWER_ROLE refers to the power role of nth port .n can take values between 0 and CONFIG_PD_PORT_COUNT-1.Setting the value to 1 configures the nth port as 
	sink and 0 as source

	Remarks:
		None

	Example:
		<code>
		#define CONFIG_PORT_0_POWER_ROLE	1 (Configuring the Port 0 as Source)

		#define CONFIG_PORT_0_POWER_ROLE	0 (Configuring the Port 0 as Sink)
		</code>
**************************************************************************************************/
#define  CONFIG_PORT_0_POWER_ROLE   1

/**************************************************************************************************
	Description:
		CONFIG_PORT_n_DATA_ROLE refers to the data role of nth port .n can take values between 0 and CONFIG_PD_PORT_COUNT-1.Setting the value to 1 configures the nth port as
	UFP and 0 as DFP

	Remarks:
		None

	Example:
		<code>
		#define CONFIG_PORT_0_DATA_ROLE	 1 (Configuring the Port 0 as DFP)

		#define CONFIG_PORT_0_DATA_ROLE	 0 (Configuring the Port 0 as UFP)
		</code>
**************************************************************************************************/
#define  CONFIG_PORT_0_DATA_ROLE    1

/**************************************************************************************************
	Description:
		CONFIG_PORT_n_RP_CURRENT_VALUE refers to the Rp Value of nth port .n can take values between 0 and CONFIG_PD_PORT_COUNT-1.

	Remarks:
		Set the Rp Value of the Sink enabled port to Disabled configuration

	Example:
		<code>
		#define CONFIG_PORT_0_RP_CURRENT_VALUE	 0 (Configuring the Port 0 Rp Value as Disabled)
		#define CONFIG_PORT_0_RP_CURRENT_VALUE	 1 (Configuring the Port 0 Rp Value as DEFAULT)
		#define CONFIG_PORT_0_RP_CURRENT_VALUE	 2 (Configuring the Port 0 Rp Value as CURRENT_15)
		#define CONFIG_PORT_0_RP_CURRENT_VALUE	 3 (Configuring the Port 0 Rp Value as CURRENT_30)
		</code>
**************************************************************************************************/
#define  CONFIG_PORT_0_RP_CURRENT_VALUE      2        		            /* 0- RP_DISABLED(To be set for Sink), 1- DEFAULT_CURRENT ,2- CURRENT_15 ,3- CURRENT_30 */

// *****************************************************************************
// *****************************************************************************
// Section: Port configuration
// *****************************************************************************
// *****************************************************************************

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_NUM_OF_PDOS refers to the number PDOs supported by the nth source port. 
	n can take values between 0 and CONFIG_PD_PORT_COUNT - 1

	Remarks:
	CONFIG_PORT_n_SOURCE_NUM_OF_PDOS can be configured from 1 to 7.

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_NUM_OF_PDOS		4
	</code> 
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_NUM_OF_PDOS      2 /* 4*/     

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_1_USB_COM refers to the USB communication enable bit in PDO1 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_1_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_1_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_1_USB_COM      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_1_CURRENT refers to the maximum current value in PDO1 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_1_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/         
#define CONFIG_PORT_0_SOURCE_PDO_1_CURRENT  3000

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_1_VOLTAGE refers to the voltage supported in PDO1 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_1_VOLTAGE		5000 (Voltage supported is configured as 5V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_1_VOLTAGE  5000  

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_2_USB_COM refers to the USB communication enable bit in PDO2 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_2_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_2_USB_COM		0
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_2_USB_COM  0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_2_CURRENT refers to the maximum current value in PDO2 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_2_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/         
#define CONFIG_PORT_0_SOURCE_PDO_2_CURRENT  3000

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_2_VOLTAGE refers to the voltage supported in PDO2 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_2_VOLTAGE		9000 (Voltage supported is configured as 9V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_2_VOLTAGE  9000

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_3_USB_COM refers to the USB communication enable bit in PDO3 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_3_USB_COM can be configured as 0 or 1.

	Remarks:
	NA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_3_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_3_USB_COM  0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_3_CURRENT refers to the maximum current value in PDO3 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_3_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/         
#define CONFIG_PORT_0_SOURCE_PDO_3_CURRENT  2500

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_3_VOLTAGE refers to the voltage supported in PDO3 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_3_VOLTAGE		15000 (Voltage supported is configured as 15V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_3_VOLTAGE  15000

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_4_USB_COM refers to the USB communication enable bit in PDO4 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_4_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_4_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_4_USB_COM  0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_4_CURRENT refers to the maximum current value in PDO4 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_4_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/         
#define CONFIG_PORT_0_SOURCE_PDO_4_CURRENT  2250

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_4_VOLTAGE refers to the voltage supported in PDO4 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_4_VOLTAGE		20000 (Voltage supported is configured as 20V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_4_VOLTAGE  20000

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_5_USB_COM refers to the USB communication enable bit in PDO5 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_5_USB_COM can be configured as 0 or 1.

	Remarks:
	NA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_5_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_5_USB_COM      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_5_CURRENT refers to the maximum current value in PDO5 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_5_CURRENT		0 (Maximum current value is configured as 0A)
	</code>
**************************************************************************************************/     
#define CONFIG_PORT_0_SOURCE_PDO_5_CURRENT      0          

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_5_VOLTAGE refers to the voltage supported in PDO5 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_5_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_5_VOLTAGE     0          

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_6_USB_COM refers to the USB communication enable bit in PDO6 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_6_USB_COM can be configured as 0 or 1.

	Remarks:
	NA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_6_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_6_USB_COM      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_6_CURRENT refers to the maximum current value in PDO6 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_6_CURRENT		0 (Maximum current value is configured as 0A)
	</code>
**************************************************************************************************/     
#define CONFIG_PORT_0_SOURCE_PDO_6_CURRENT      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_6_VOLTAGE refers to the voltage supported in PDO6 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_6_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_6_VOLTAGE      0

/********************* PDO-7 ********************************/
/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_7_USB_COM refers to the USB communication enable bit in PDO7 of nth source port,
	CONFIG_PORT_n_SOURCE_PDO_7_USB_COM can be configured as 0 or 1.

	Remarks:
	NA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_7_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_7_USB_COM  0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_7_CURRENT refers to the maximum current value in PDO7 of nth source port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_7_CURRENT		0 (Maximum current value is configured as 0A)
	</code>
**************************************************************************************************/     
#define CONFIG_PORT_0_SOURCE_PDO_7_CURRENT      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SOURCE_PDO_7_VOLTAGE refers to the voltage supported in PDO7 of nth source port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SOURCE_PDO_7_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SOURCE_PDO_7_VOLTAGE      0


/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_NUM_OF_PDOS refers to the number PDOs supported by the nth sink port. 
	n can take values between 0 and CONFIG_PD_PORT_COUNT - 1

	Remarks:
	CONFIG_PORT_n_SINK_NUM_OF_PDOS can be configured from 1 to 7.

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_NUM_OF_PDOS		4
	</code> 
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_NUM_OF_PDOS      0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_HIGHER_CAPABILITY refers to the Higher Capability bit in PDO of nth sink port. 
	n can take values between 0 and CONFIG_PD_PORT_COUNT - 1. CONFIG_PORT_n_SINK_HIGHER_CAPABILITY can 
	be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_HIGHER_CAPABILITY		1
	</code> 
**************************************************************************************************/           
#define CONFIG_PORT_0_SINK_HIGHER_CAPABILITY     0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_1_USB_COM refers to the USB communication enable bit in PDO1 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_1_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_1_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_1_USB_COM    0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_1_VOLTAGE refers to the voltage supported in PDO1 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_1_VOLTAGE		5000 (Voltage supported is configured as 5V)
	</code>
**************************************************************************************************/                   
#define CONFIG_PORT_0_SINK_PDO_1_VOLTAGE    0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_1_CURRENT refers to the maximum current value in PDO1 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_1_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_1_CURRENT    0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_2_USB_COM refers to the USB communication enable bit in PDO2 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_2_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_2_USB_COM		0
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_2_USB_COM    0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_2_VOLTAGE refers to the voltage supported in PDO2 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_2_VOLTAGE		9000 (Voltage supported is configured as 9V)
	</code>
**************************************************************************************************/                  
#define CONFIG_PORT_0_SINK_PDO_2_VOLTAGE    0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_2_CURRENT refers to the maximum current value in PDO2 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_2_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_2_CURRENT      0                  

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_3_USB_COM refers to the USB communication enable bit in PDO3 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_3_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_3_USB_COM		0
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_3_USB_COM        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_3_VOLTAGE refers to the voltage supported in PDO3 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_3_VOLTAGE		15000 (Voltage supported is configured as 15V)
	</code>
**************************************************************************************************/                    
#define CONFIG_PORT_0_SINK_PDO_3_VOLTAGE        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_3_CURRENT refers to the maximum current value in PDO3 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_3_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_3_CURRENT         0                  

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_4_USB_COM refers to the USB communication enable bit in PDO4 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_4_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_4_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_4_USB_COM        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_4_VOLTAGE refers to the voltage supported in PDO3 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_4_VOLTAGE		20000 (Voltage supported is configured as 20V)
	</code>
**************************************************************************************************/                   
#define CONFIG_PORT_0_SINK_PDO_4_VOLTAGE        0                     

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_4_CURRENT refers to the maximum current value in PDO4 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_4_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_4_CURRENT        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_5_USB_COM refers to the USB communication enable bit in PDO5 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_5_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_5_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_5_USB_COM        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_5_VOLTAGE refers to the voltage supported in PDO5 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_5_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/                   
#define CONFIG_PORT_0_SINK_PDO_5_VOLTAGE        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_5_CURRENT refers to the maximum current value in PDO5 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_5_CURRENT		3000 (Maximum current value is configured as 3A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_5_CURRENT        0                       

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_6_USB_COM refers to the USB communication enable bit in PDO6 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_6_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_6_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_6_USB_COM        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_6_VOLTAGE refers to the voltage supported in PDO6 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_6_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/                   
#define CONFIG_PORT_0_SINK_PDO_6_VOLTAGE        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_6_CURRENT refers to the maximum current value in PDO6 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_6_CURRENT		0 (Maximum current value is configured as 0A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_6_CURRENT        0                        

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_7_USB_COM refers to the USB communication enable bit in PDO7 of nth sink port,
	CONFIG_PORT_n_SINK_PDO_7_USB_COM can be configured as 0 or 1.

	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_7_USB_COM		1
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_7_USB_COM        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_7_VOLTAGE refers to the voltage supported in PDO7 of nth sink port

	Remarks:
	Units are in mV

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_7_VOLTAGE		0 (Voltage supported is configured as 0V)
	</code>
**************************************************************************************************/                   
#define CONFIG_PORT_0_SINK_PDO_7_VOLTAGE        0

/**************************************************************************************************
	Description:
	CONFIG_PORT_n_SINK_PDO_7_CURRENT refers to the maximum current value in PDO7 of nth sink port

	Remarks:
	Units are in mA

	Example:
	<code>
	#define CONFIG_PORT_n_SINK_PDO_7_CURRENT		0 (Maximum current value is configured as 0A)
	</code>
**************************************************************************************************/
#define CONFIG_PORT_0_SINK_PDO_7_CURRENT        0                         

// *****************************************************************************
// *****************************************************************************
// Section: Port 1 configuration (see comments above for details)
// *****************************************************************************
// *****************************************************************************

#define CONFIG_PORT_1_POWER_ROLE                1
#define CONFIG_PORT_1_DATA_ROLE                 1
#define CONFIG_PORT_1_RP_CURRENT_VALUE          2        		            /* 0- RP_DISABLED(To be set for Sink), 1- DEFAULT_CURRENT ,2- CURRENT_15 ,3- CURRENT_30 */
#define CONFIG_PORT_1_SOURCE_NUM_OF_PDOS        2      
#define CONFIG_PORT_1_SOURCE_PDO_1_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_1_CURRENT      3000
#define CONFIG_PORT_1_SOURCE_PDO_1_VOLTAGE      5000  
#define CONFIG_PORT_1_SOURCE_PDO_2_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_2_CURRENT      3000
#define CONFIG_PORT_1_SOURCE_PDO_2_VOLTAGE      9000
#define CONFIG_PORT_1_SOURCE_PDO_3_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_3_CURRENT      2500
#define CONFIG_PORT_1_SOURCE_PDO_3_VOLTAGE      15000
#define CONFIG_PORT_1_SOURCE_PDO_4_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_4_CURRENT      2250
#define CONFIG_PORT_1_SOURCE_PDO_4_VOLTAGE      20000
#define CONFIG_PORT_1_SOURCE_PDO_5_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_5_CURRENT      0          
#define CONFIG_PORT_1_SOURCE_PDO_5_VOLTAGE      0          
#define CONFIG_PORT_1_SOURCE_PDO_6_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_6_CURRENT      0
#define CONFIG_PORT_1_SOURCE_PDO_6_VOLTAGE      0
#define CONFIG_PORT_1_SOURCE_PDO_7_USB_COM      0
#define CONFIG_PORT_1_SOURCE_PDO_7_CURRENT      0
#define CONFIG_PORT_1_SOURCE_PDO_7_VOLTAGE      0

#define CONFIG_PORT_1_SINK_NUM_OF_PDOS          0
#define CONFIG_PORT_1_SINK_HIGHER_CAPABILITY    0
#define CONFIG_PORT_1_SINK_PDO_1_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_1_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_1_CURRENT        0
#define CONFIG_PORT_1_SINK_PDO_2_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_2_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_2_CURRENT        0                  
#define CONFIG_PORT_1_SINK_PDO_3_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_3_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_3_CURRENT        0                  
#define CONFIG_PORT_1_SINK_PDO_4_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_4_VOLTAGE        0                     
#define CONFIG_PORT_1_SINK_PDO_4_CURRENT        0
#define CONFIG_PORT_1_SINK_PDO_5_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_5_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_5_CURRENT        0                       
#define CONFIG_PORT_1_SINK_PDO_6_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_6_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_6_CURRENT        0                        
#define CONFIG_PORT_1_SINK_PDO_7_USB_COM        0
#define CONFIG_PORT_1_SINK_PDO_7_VOLTAGE        0
#define CONFIG_PORT_1_SINK_PDO_7_CURRENT        0                         

/****************************************************************************/


/**************************************************************************************************
	Description:
	CONFIG_PORT_CONFIGURATION_DATA is used to update the Port configuration structure at the compile time.
	Port configuration structure holds the following as members variables in the given order : Type C Configuration data , 
	Source PDOs , Source PDO Count , Sink PDOs , Sink PDO count.TYPEC_CONFIG_DATA macro will take the data from already
	configured Type C Macros to from the data according to the "Type C Configuration data" member variable in the structure.
	PE_SRC_PORT_FIXED_PDO or PE_SNK_PORT_FIXED_PDO will form the PDO from the already
	configured PDO Macros to from the data according to the member variables "Source PDOs" ,"Source PDO Count" in the structure.
	PE_PORT_NOT_AS_SINK_OR_DISABLED macro notifies that the port is source only and does not have any sink PDOs.
	PE_PORT_NOT_AS_SOURCE_OR_DISABLED macro notifies that the port is sink only and does not have any source PDOs.Use the Macros only in the 
	predefined order as given in the example.


	Remarks:
	None

	Example:
	<code>
	#define CONFIG_PORT_CONFIGURATION_DATA			TYPEC_CONFIG_DATA(0),\
													PE_SRC_PORT_FIXED_PDO(0), \
													PE_PORT_NOT_AS_SINK_OR_DISABLED(0), \
													...............Port 1..............\
													.................Port 2...............\
													TYPEC_CONFIG_DATA(CONFIG_PD_PORT_COUNT - 1), \
													PE_SRC_PORT_FIXED_PDO(CONFIG_PD_PORT_COUNT - 1), \
													PE_PORT_NOT_AS_SINK_OR_DISABLED(CONFIG_PD_PORT_COUNT - 1)


	</code>
**************************************************************************************************/                                         
#define CONFIG_PORT_CONFIGURATION_DATA  { \
                                            TYPEC_CONFIG_DATA(0), \
                                            {PE_PORT_SRC_PDO_GENERATION(0)}, \
                                            PE_PORT_SRC_NUM_PDO(0), \
                                            UPD_PIO_MNG_CONFIG(0)\
                                        } \
                                        , \
                                        {   \
                                            TYPEC_CONFIG_DATA(1), \
                                            {PE_PORT_SRC_PDO_GENERATION(1)}, \
                                            PE_PORT_SRC_NUM_PDO(1), \
                                            UPD_PIO_MNG_CONFIG(1)\
                                        }

#define CONFIG_PORT_ROLLBACK_CONFIGURATION_DATA  { \
                                            TYPEC_CONFIG_DATA(0), \
                                            {PE_PORT_SRC_ROLLBACK_PDO_GENERATION(0)}, \
                                            PE_PORT_SRC_NUM_PDO(0), \
                                            UPD_PIO_MNG_CONFIG(0)\
                                        } \
                                        , \
                                        {   \
                                            TYPEC_CONFIG_DATA(1), \
                                            {PE_PORT_SRC_ROLLBACK_PDO_GENERATION(1)}, \
                                            PE_PORT_SRC_NUM_PDO(1), \
                                            UPD_PIO_MNG_CONFIG(1)\
                                        }

// *****************************************************************************
// *****************************************************************************
// Section: PIO configurations
// *****************************************************************************
// *****************************************************************************
											  
/**************************************************************************************************
	Description:
	CONFIG_PORT_n_EN_VBUS_UPD_PIO refers to the PIO number of EN_VBUS pin for the nth Port.
	n can take values between 0 and CONFIG_PD_PORT_COUNT - 1.

	Remarks:
	Confined to INCLUDE_POWER_FAULT_HANDLING define.

	Example:
	<code>
	#define CONFIG_PORT_0_EN_VBUS_UPD_PIO		2
	</code>
**************************************************************************************************/
											  
#define CONFIG_PORT_n_EN_VBUS_UPD_PIO                   
#define CONFIG_PORT_0_EN_VBUS_UPD_PIO   7
#define CONFIG_PORT_1_EN_VBUS_UPD_PIO   7

											  
/**************************************************************************************************
	Description:
	CONFIG_PORT_n_PRT_CTL_OCS_UPD_PIO refers to the PIO number of PRT_CTL/OCS pin for the nth Port.
	n can take values between 0 and CONFIG_PD_PORT_COUNT - 1.

	Remarks:
	Confined to INCLUDE_POWER_FAULT_HANDLING define.

	Example:
	<code>
	#define CONFIG_PORT_0_PRT_CTL_OCS_UPD_PIO		9
	</code>
**************************************************************************************************/
											  
											  
#define CONFIG_PORT_n_PRT_CTL_OCS_UPD_PIO               
#define CONFIG_PORT_0_PRT_CTL_OCS_UPD_PIO    3
#define CONFIG_PORT_1_PRT_CTL_OCS_UPD_PIO    3           

											  
/*********************************************************************************
  Function:
                CONFIG_HOOK_PIO_HANDLER_ISR(_u8PortNum_, _u16PIOsts_)
  Summary:
    ISR handler for PIO interrupt
  Description:
    This function is hook in the PIO ISR handler.

  Conditions:
    The Hook is called inside a ISR handler. Its definition should not enable or 
    disable interrupt or clear the PIO Status caused the interrupt.

 Input:
    _u8Port_Num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _u16PIOsts_ - Pio Interrupt Staus caused the PIO interrupt.

  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_PIO_HANDLER_ISR(_u8PortNum_, _u16PIOsts_)()   

        void PIO_Handler(UINT8 u8PortNum, UINT16 u16PIOStatus);

        void PIO_Handler(UINT8 u8PortNum, UINT16 u16PIOStatus)
        {
            // PIO interrupt related handling
        }

    </code>
  Remarks:
    User definition of this Hook function is optional.
  *********************************************************************************/

								  
#define CONFIG_HOOK_PIO_HANDLER_ISR(_u8PortNum_, _u16PIOsts_) 
                                              
/*********************************************************************************
  Function:
                CONFIG_HOOK_NOTIFY_POWER_FAULT(_u8PortNum_, _pu8PwrFaultsts_)
  Summary:
    Power Fault Notification.

  Description:
    This function is hook in DPM Power Fault handler notificing Power fault.

  Conditions:
    None.

 Input:
    _u8Port_Num_    -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _pu8PwrFaultsts_ - Pointer to Powerfault status for the port. The value *_pu8PwrFaultsts_
                        can be interpreted from following value.
                        DPM_POWER_FAULT_OVP			    BIT(0)
                        DPM_POWER_FAULT_UV				BIT(1)
                        DPM_POWER_FAULT_VBUS_OCS		BIT(2)
                        DPM_POWER_FAULT_VCONN_OCS	    BIT(3)
                        This pointer can be modified to disable the occured power fault.

  Return:
    UINT8 is the return value. Depending on the return value occured Power fault is handled.
    It can take following values
	for Zeus stack to handle occured power fault return TRUE 
    for Zeus stack to neglect the Power fault occured return FALSE
    Note that returning FALSE will not reset the Power fault flag being set. It will 
    just ignore Powerfault handling for that instance alone.

  Example:
    <code>
        \#define CONFIG_HOOK_NOTIFY_POWER_FAULT(_u8PortNum_, _pu8PwrFaultsts_)  

        UINT8 UPD301_HandlePowerFault(UINT8 u8PortNum, UINT8 *pu8PwrFaultSts);

        UINT8 UPD301_HandlePowerFault(UINT8 u8PortNum, UINT8 *pu8PwrFaultSts)
        {
            Return DPM_HANDLE_PWR_FAULT(TRUE) to handle occured power fault.
            Return DPM_NEGLECT_PWR_FAULT(FALSE) to neglect the Power fault occured.
        }

    </code>
  Remarks:
    User definition of this Hook function is optional.
  *********************************************************************************/
                                              
#define CONFIG_HOOK_NOTIFY_POWER_FAULT(_u8PortNum_, _pu8PwrFaultsts_)
                                              
/*********************************************************************************
  Function:
                CONFIG_HOOK_NOTIFY_POWER_FAULT_FROM_ISR(_u8PortNum_, _pu8PwrFaultsts_)
  Summary:
    Power Fault notification from ISR to drive VBUS_EN low if needed on a power fault

  Description:
    This function is hook in ISR where the Power Fault (OVP, UV and OCS) is detected
    and it is mainly to cutoff the VBUS_EN as soon as possible on detecting the fault.
    This hook is disable EN_VBUS to cutoff the power due to power fault
    or trigger any VBUS correction mechanism if needed or evaluate the Power fault whether 
    occured power fault is valid or not and nullify the Power fault variable incase it is not valid.

   Conditions:
    The Hook is called inside a ISR handler it should as short as possible.

 Input:
    _u8Port_Num_    -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
    _pu8PwrFaultsts_ - Pointer to Powerfault status for the port. The value *_pu8PwrFaultsts_
                        can be interpreted from following value.
                        DPM_POWER_FAULT_OVP			    BIT(0)
                        DPM_POWER_FAULT_UV				BIT(1)
                        DPM_POWER_FAULT_VBUS_OCS		BIT(2)
                        DPM_POWER_FAULT_VCONN_OCS	    BIT(3)
                        Pointer can be modified to disable the occured power fault.

  Return:
    None.

  Example:
    <code>
        \#define CONFIG_HOOK_NOTIFY_POWER_FAULT_FROM_ISR(_u8PortNum_, _pu8PwrFaultsts_)  

        void UPD301_HandlePowerFault(UINT8 u8PortNum, UINT8 *pu8PwrFaultSts);

        void UPD301_HandlePowerFault(UINT8 u8PortNum, UINT8 *pu8PwrFaultSts)
        {
           Drive VBUS_EN low or cut off the power if necessary on a power fault. 
        }

    </code>
  Remarks:
    User definition of this Hook function is optional. 
  *********************************************************************************/
                                              
#define CONFIG_HOOK_NOTIFY_POWER_FAULT_FROM_ISR(_u8PortNum_, _u8PwrFaultsts_)	dsPIC_HandlePowerFault(_u8PortNum_, _u8PwrFaultsts_)

/*********************************************************************************
  Function:
                CONFIG_HOOK_PRTCTL_OCS_INIT(_u8PortNum_)
  Summary:
    Hook to initalise PRT_CTL/OCS pin

  Description:
    The PRT_CTL/OCS pin can be intialised in this hook.

  Conditions:
    None

  Input:
    _u8Port_Num_    -  Port number of the device. Value passed will be less
                        than CONFIG_PD_PORT_COUNT.

  Return:
    None.

  Example:
    <code>
        \#define CONFIG_HOOK_PRTCTL_OCS_INIT(_u8PortNum_)  

        void UPD301_ConfigPrtCtlforOCSdet (UINT8 u8PortNum

        void UPD301_ConfigPrtCtlforOCSdet (UINT8 u8PortNum)
        {
            Initialise the PRT_CTL/OCS pin to interrupt mode
            For example, to Falling edge configuration with CONFIG_OCS_DEBOUNCE_US debounce
        }

    </code>
  Remarks:
    User definition of this Hook function is optional. 
  *********************************************************************************/
                                              
#define CONFIG_HOOK_PRTCTL_OCS_INIT(_u8PortNum_)

/*********************************************************************************
  Function:
                CONFIG_HOOK_DRIVE_PRTCTL_OCS(_u8PortNum_, _u8DriveSt_)
  Summary:
    Hook to drive the PRT_CTL/OCS low or reset the configuration for OCS detection

  Description:
    This Hook is drive PRT_CTL/OCS low on detecting a Power fault to indicate the 
    occurence of power fault and reset the pin to detect OCS back once power fault is reoccured.

   Conditions:
    The Hook is called inside a ISR handler it should as short as possible.

 Input:
    _u8Port_Num_    -  Port number of the device. Value passed will be less
                        than CONFIG_PD_PORT_COUNT
    _u8DriveSt_     -  CONFIG_DRIVE_PRTCTL_OCS_LOW(0) - drive the PRT_CTL/OCS low
                        CONFIG_RESET_PRTCTL_OCS_TO_DET(1) - Configure the PRT_CTL/OCS for OCS detection
  Return:
    None.

  Example:
    <code>
        \#define CONFIG_HOOK_DRIVE_PRTCTL_OCS(_u8PortNum_, _u8DriveSt_) 

        void UPD301_ConfigPrtCtlOCSdetPIO (UINT8 u8PortNum, UINT8 u8PIONum);

        void UPD301_ConfigPrtCtlOCSdetPIO (UINT8 u8PortNum, UINT8 u8PIONum)
        {
           depending on the _u8DriveSt_ value configure the PRT_CTL/OCS pin
        }

    </code>
  Remarks:
    User definition of this Hook function is optional. 
  *********************************************************************************/

#define CONFIG_HOOK_DRIVE_PRTCTL_OCS(_u8PortNum_, _u8DriveSt_)

/* defines for u8FaultIndication in CONFIG_HOOK_DRIVE_PRTCTL_OCS u8FaultIndication API*/                                             
#define CONFIG_DRIVE_PRTCTL_OCS__LOW        0
#define CONFIG_RESET_PRTCTL_OCS_TO_DET      1
/* Debounce configured for PRT_CTL/OCS */                                             
#define CONFIG_OCS_DEBOUNCE_US              36                                             

// *****************************************************************************
// *****************************************************************************
// Section: MCU INTERRUPT CONFIGURATION
// *****************************************************************************
// *****************************************************************************
/*********************************************************************************
  Function:
                CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT()
  Summary:
    Disables the global interrupt.
  Description:
    This function is called when entering into a critical section. It must
    provide an implementation to disable the interrupts globally. This
    \function must be very short, otherwise response time to the interrupt
    will take longer time. Define relevant function that has no arguments
    without return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT()   CRITICAL_SECTION_ENTER()
    
        void CRITICAL_SECTION_ENTER(void);
    
        void CRITICAL_SECTION_ENTER()
        {
          //Disable global interrupts
        }
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                            
  *********************************************************************************/
#define CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT()  CRITICAL_SECTION_ENTER()
  
/*******************************************************************************
  Function:
            CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT()
  Summary:
    Enables the global interrupt.
  Description:
    This function is called when exiting from critical section. It must
    provide an implementation to enable the interrupts globally. This
    \function must be very short, otherwise response time to the interrupt
    will take longer time. Define relevant function that has no arguments
    without return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT()   CRITICAL_SECTION_EXIT()
    
        void CRITICAL_SECTION_EXIT(void);
    
        void CRITICAL_SECTION_EXIT()
        {
            //Enable global interrupts
        }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                          
  *******************************************************************************/                           
#define CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT()    CRITICAL_SECTION_EXIT()               
/*Status of ports whether disabled or enabled*/
#define PORT_STATUS_DISABLED        0x01
#define PORT_STATUS_ENABLED         0x00

/**************************************************************************
  Function:
              CONFIG_HOOK_HW_UPDALERTGPIO_INIT(_pu8PortDisable_)
    
  Summary:
    Initializes the MCU GPIOs that are connected to the alert line of all
    UPD350s for interrupt notification
  Description:
    This function initializes the MCU GPIOs that are connected to the alert
    line of all UPD350s for interrupt notification. It is recommended to
    configure MCU GPIOs interrupt in edge level detection since the UPD350
    keeps the alert line in low state until the interrupt is cleared.
    Define relevant function that has no arguments without return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_HW_UPDALERTGPIO_INIT(_pu8PortDisable_)      updalert_init(_pu8PortDisable_)
    
        void updalert_init(_pu8PortDisable_);
    
        void updalert_init(_pu8PortDisable_)
        {
            
			if(_pu8PortDisable_[0] == PORT_STATUS_ENABLED)
			{
				//Initializes the MCU GPIOs that are connected to Port 0 UPD350
			}
			if(_pu8PortDisable_[1] == PORT_STATUS_ENABLED)
			{
				//Initializes the MCU GPIOs that are connected to Port 1 UPD350s
			}
        }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                     
  **************************************************************************/
#define CONFIG_HOOK_HW_UPDALERTGPIO_INIT(_pu8PortDisable_)		updalert_init(_pu8PortDisable_)	

// *****************************************************************************
// *****************************************************************************
// Section: Reset UPD350 through MCU GPIO initialization
// *****************************************************************************
// *****************************************************************************
/**************************************************************************
  Function:
                CONFIG_HOOK_HW_UPDRESETGPIO_INIT()
  Summary:
    Initializes the MCU GPIOs that are connected to the reset line of all
    UPD350s
  Description:
    This function initializes the MCU GPIOs that are connected to the reset
    line of all UPD350s. It is recommended to connect a single GPIO to the
    reset line of all UPD350s. Default line state of configured MCU GPIO
    must be high. Define relevant function that has no arguments without
    \return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_HW_UPDRESETGPIO_INIT()      updreset_init()
    
    void updreset_init(void);
    
    void updreset_init(void)
    {
        //Initialization of MCU GPIOs connected to UPD350 reset lines
        //Make the gpio line high as default
    }
    </code>
  Remarks:
    User definition of this Hook function is optional                      
  **************************************************************************/
#define CONFIG_HOOK_HW_UPDRESETGPIO_INIT() updreset_init()

/**********************************************************************
  Function:
                CONFIG_HOOK_UPDRESET_THRU_GPIO()
  Summary:
    Resets all the connected UPD350s through its reset line
  Description:
    This function resets all the connected UPD350s. Define relevant
    \function that has no arguments without return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
    \#define CONFIG_HOOK_UPDRESET_THRU_GPIO()      updreset_thru_gpio()
    
    void updreset_thru_gpio(void);
    
    void updreset_thru_gpio(void)
    {
        //Enable pull down
    
       // Wait for xxx uS
    
       // Enable pull up
    }
    </code>
  Remarks:
    User definition of this Hook function is optional                  
  **********************************************************************/
#define CONFIG_HOOK_UPDRESET_THRU_GPIO()  updreset_thru_gpio()

// *****************************************************************************
// *****************************************************************************
// Section: Structure packing
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**************************************************************************************************
  Summary:
    Structure packing to align the bytes in data memory based on the compiler.

  Description:
		Generally packed structures will be used to save space & align the bytes in data memory based on the compiler.
	If this pre-processor is defined then all used PD stack “C” structures will be replaced with keyword for compilation.
	If this pre-processor is not defined then it will be default compilation rules based on the compiler.

  Remarks:
    Need to be packed always based on type of microcontroller.
	
  Example:
  <code>
	#define CONFIG_STRUCT_PACKED_START   __attribute__((__packed__)) 
  </code>
**************************************************************************************************/
#define CONFIG_STRUCT_PACKED_START
/**************************************************************************************************
Summary:
Structure packing to align the bytes in data memory based on the compiler.

Description:
Generally packed structures will be used to save space & align the bytes in data memory based on the compiler.
If this pre-processor is defined then all used PD stack “C” structures will be replaced with keyword for compilation.
If this pre-processor is not defined then it will be default compilation rules based on the compiler.

Remarks:
Need to be packed always based on type of microcontroller.

Example:
<code>

</code>
**************************************************************************************************/
#define CONFIG_STRUCT_PACKED_END
// *****************************************************************************
// *****************************************************************************
// Section: SPI Interface Configuration
// *****************************************************************************
// *****************************************************************************

/**************************************************************************
  Function:
            CONFIG_HOOK_HW_SPI_INIT()
    
  Summary:
    Initialize SPI module related initialization with respect to the
    hardware
  Description:
    This function is called during initialization of stack. Define relevant
    \function that has no arguments without return type.
  Conditions:
    None.
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_HW_SPI_INIT()      hw_spi_init()
    
        void hw_spi_init( void );
    
        void hw_spi_init( void )
        {
            //Microcontroller SPI module init
        }
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                     
  **************************************************************************/
#define CONFIG_HOOK_HW_SPI_INIT()  hw_spi_init()

/*************************************************************************************************
  Function:
              CONFIG_HOOK_HW_SPI_CS_LOW(_u8Port_Num_)
    
  Summary:
    Drives SPI chip select level as low with respect to the port number
    given in the argument of this function
  Description:
    This function is called before starting read/write operations of UPD350
    registers with respect to the port. Define relevant function that has
    one UINT8 argument with out return type.
  Conditions:
    None.
  Input:
    _u8Port_Num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
    
        \#define CONFIG_HOOK_HW_SPI_CS_LOW(_u8Port_Num_)      hw_spi_cs_low (_u8Port_Num_)
    
        void hw_spi_cs_low(UINT8 u8Portnum);
    
        void hw_spi_cs_low (UINT8 u8Portnum)
        {
            if (u8Portnum == 0)
            {
                //Set pin level low for respective GPIO that is connected to the UPD350 SPI CS pin
            }
            if (u8Portnum == 1)
            {
                //Set pin level low for respective GPIO that is connected to the UPD350 SPI CS pin
            }
        }
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                                            
  *************************************************************************************************/
#define CONFIG_HOOK_HW_SPI_CS_LOW(_u8Port_num_)  hw_spi_cs_low(_u8Port_num_)

/**********************************************************************************************
  Function:
                CONFIG_HOOK_HW_SPI_CS_HIGH(_u8Port_num_)
    
  Summary:
    Drives SPI chip select as high with respect to the port number given in
    the argument of this function
  Description:
    This function is called after finishing read/write operations of UPD350
    registers with respect to the port. Define relevant function that has
    one UINT8 argument without return type.
  Conditions:
    None.
  Input:
    _u8Port_num_ -  Port number of the device. Value passed will be less
                    than CONFIG_PD_PORT_COUNT
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_HW_SPI_CS_HIGH(_u8Port_num_)      hw_spi_cs_high (_u8Port_num)
    
        void hw_spi_cs_high(UINT8 u8Portnum);
    
        void hw_spi_cs_high (UINT8 u8Portnum)
        {
            if (u8Portnum == 0)
            {
                //Set pin level high for respective GPIO that is connected to the UPD350 CS pin
            }
            if (u8Portnum == 1)
            {
                //Set pin level high for respective GPIO that is connected to the UPD350 CS pin
            }
        }
    
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                                         
  **********************************************************************************************/
#define CONFIG_HOOK_HW_SPI_CS_HIGH(_u8Port_num_)    hw_spi_cs_high (_u8Port_num_)

/*********************************************************************************************
  Function:
                CONFIG_HOOK_HW_SPI_WRITE_TRANSFER(_pu8write_buf_,_u16write_len_)
    
  Summary:
    SPI Write transfer
  Description:
    This function is called to write UPD350 registers with respect to the
    port. Define relevant function that has UINT8*, UINT16 arguments
    without return type.
  Conditions:
    None.
  Input:
    _pu8write_buf_ -  Stack will pass the pointer to the buffer where data
                      to be written on the SPI bus. Data type of the pointer
                      buffer must be UINT8*
    _u16write_len_ -  Stack will pass the Number of bytes to be written on
                      the SPI bus. Data type of this parameter must be
                      UINT16
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_HW_SPI_WRITE_TRANSFER(_pu8write_buf_,_u16write_len_)   \\
                                                    SPI_Write (_pu8write_buf_, _u16write_len_)
    
        void SPI_Write(UINT8 *pu8WriteBuffer, UINT16 u16Writelength);
    
        void SPI_Write(UINT8 *pu8WriteBuffer, UINT16 u16Writelength)
        {
            for(UINT16 u16Txcount = 0; u16Txcount \< u16Writelength ;u16Txcount++)
            {
                //Write data bytes to SPI bus
            }
        }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                                        
  *********************************************************************************************/
#define CONFIG_HOOK_HW_SPI_WRITE_TRANSFER(_pu8write_buf_,_u16write_len_)  SPI_Write (_pu8write_buf_, _u16write_len_)

/***************************************************************************************
  Function:
          CONFIG_HOOK_HW_SPI_READ_TRANSFER(_pu8read_buf_, _u16read_len_)
    
  Summary:
    SPI Read transfer
  Description:
    This function is called to read UPD350 registers with respect to the
    port. Define relevant function that has UINT8*,UINT16 arguments without
    \return type.
  Conditions:
    None.
  Input:
    _pu8read_buf_ -  Stack will pass the pointer to the buffer where data to
                     be read on the SPI bus. Data type of the pointer buffer
                     must be UINT8*
    _u16read_len_ -  Stack will pass the number of bytes to be read on the
                     SPI bus. Data type of this parameter must be UINT16
  Return:
    None.
  Example:
    <code>
        \#define CONFIG_HOOK_HW_SPI_READ_TRANSFER(_pu8read_buf_, _u16read_len_)  \\
                                                 SPI_Read (_pu8read_buf_, _u16read_len_)
    
        void SPI_Read (UINT8 *pu8ReadBuffer, UINT16 u16Readlength)
    
        void SPI_Read (UINT8 *pu8ReadBuffer, UINT16 u16Readlength)
        {
            for(UINT16 u16Rxcount = 0; u16Rxcount \< u16Readlength; u16Rxcount++)
            {
                //Read data from SPI bus
             }
        }
    </code>
  Remarks:
    User definition of this Hook function is mandatory                                  
  ***************************************************************************************/
#define CONFIG_HOOK_HW_SPI_READ_TRANSFER(_pu8read_buf_, _u16read_len_)   \
            SPI_Read (_pu8read_buf_, _u16read_len_)                   
                                           
/************************************************************************
  Function:
          \#define CONFIG_HOOK_MEMCMP(_OBJ1_, _OBJ2_, _LEN_)
  Summary:
    Compare two memory regions
  Description:
    This function is called to compare two memory regions _OBJ1_ &amp;
    _OBJ2_ with specified length _LEN_. USER_APPLICATION must define this
    \function based on compiler of MCU.
  Conditions:
    None.
  Input:
    _OBJ1_ -  This is the pointer to block of Memory region 1
    _OBJ2_ -  This is the pointer to block of Memory region 2
    _LEN_ -   This is the number of bytes to be compared.
  Return:
    \Returns 0 if two memory regions are same.
  Example:
    <code>
    \#define CONFIG_HOOK_MEMCMP(_OBJ1_, _OBJ2_, _LEN_)  \\
                                           memcmp(_OBJ1_, _OBJ2_, _LEN_)
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                   
  ************************************************************************/
#define CONFIG_HOOK_MEMCMP(_OBJ1_, _OBJ2_, _LEN_)  memcmp(_OBJ1_, _OBJ2_, _LEN_)                                 

/**************************************************************************
  Function:
            \#define CONFIG_HOOK_MEMCPY(_DEST_, _SRC_, _LEN_)
    
  Summary:
    Copies one memory area to another memory area
  Description:
    This function is called to copy _LEN_ bytes from _SRC_ memory area to
    _DEST_ memory area. USER_APPLICATION must define this function based on
    compiler of MCU. The memory areas must not overlap.
  Conditions:
    None.
  Input:
    _DEST_ -  This is the pointer to block of destination memory region
    _SRC_ -   This is the pointer to block of source memory region
    _LEN_ -   This is the number of bytes to be copied.
  Return:
    \Returns a pointer to _DEST_.
  Example:
    <code>
    \#define CONFIG_HOOK_MEMCPY(_DEST_, _SRC_, _LEN_)  \\
                                      memcpy(_DEST_, _SRC_, _LEN_)
    
    //This function definition can be compiler defined or user defined
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory                     
  **************************************************************************/
#define CONFIG_HOOK_MEMCPY(_DEST_, _SRC_, _LEN_)  memcpy(_DEST_, _SRC_, _LEN_)                                    


         
                                                                                          
/**************************************************************************
  Description:
    CONFIG_PDFU_SUPPORTED is set to 0 if firmware is not updatable during
    Run time.
    
    Otherwise shall be set to 1. It is used by the PD Firmware Update
    state-machine during Enumeration phase. This information is shared with
    the PDFU Initiator as part of GET_FW_ID command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_PDFU_SUPPORTED TRUE
    </code>
                                                                           
  **************************************************************************/                                                                                            

#define CONFIG_PDFU_SUPPORTED 0               

/************************************************************************
  Description:
    CONFIG_PDFU_VIA_USBPD_SUPPORTED Set to 1 to indicate support for PDFU
    via USB PD Firmware Update flow.Otherwise shall be set to 0.
    
    It is used by the PD Firmware Update state-machine during Enumeration
    phase. This information is shared with the PDFU Initiator as part of
    GET_FW_ID command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_PDFU_VIA_USBPD_SUPPORTED TRUE
    </code>
                                                                         
  ************************************************************************/                                                                                           
#define CONFIG_PDFU_VIA_USBPD_SUPPORTED     

/************************************************************************
  Description:
    CONFIG_HWMAJOR_VERSION defines Hardware Minor Version details of the
    product. It is used by the PD Firmware Update state-machine during
    Enumeration phase. This information is shared with the PDFU Initiator
    as part of GET_FW_ID command's response.
  Remarks:
    This is a 4-bit entity. (Valid values are 0 to 16)
    
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_HWMINOR_VERSION 0x00
    </code>
                                                                         
  ************************************************************************/                                                                                           
#define CONFIG_HWMINOR_VERSION       

/************************************************************************
  Description:
    CONFIG_HWMAJOR_VERSION defines Hardware Major Version details of the
    product. It is used by the PD Firmware Update state-machine during
    Enumeration phase. This information is shared with the PDFU Initiator
    as part of GET_FW_ID command's response.
  Remarks:
    This is a 4-bit entity. (Valid values are 0 to 16)
    
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_HWMAJOR_VERSION 0x00
    </code>
                                                                         
  ************************************************************************/                                                                                            
#define CONFIG_HWMAJOR_VERSION       

/************************************************************************
  Description:
    CONFIG_SILICON_VERSION UPD301 Silicon Base Version.
    
    It is used by the PD Firmware Update state-machine during Enumeration
    phase. This information is shared with the PDFU Initiator as part of
    GET_FW_ID command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_SILICON_VERSION 0x01u
    </code>
                                                                         
  ************************************************************************/                                                                                           
#define CONFIG_SILICON_VERSION       
                                                                                          
/************************************************************************
  Description:
    CONFIG_PRODUCT_VID UPD301 product Vendor Identifier value.
    
    
    
    It is used by the PD Firmware Update state-machine during Enumeration
    phase. This information is shared with the PDFU Initiator as part of
    GET_FW_ID command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_PRODUCT_VID 0x0424u
    </code>
                                                                         
  ************************************************************************/
#define CONFIG_PRODUCT_VID          
                                                                                          
/************************************************************************
  Description:
    CONFIG_PRODUCT_PID UPD301 is the Product Identifier value.
    
    
    
    It is used by the PD Firmware Update state-machine during Enumeration
    phase. This information is shared with the PDFU Initiator as part of
    GET_FW_ID command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_PRODUCT_PID 0x301Au
    </code>
                                                                         
  ************************************************************************/
#define CONFIG_PRODUCT_PID          
                                                                                          
/***********************************************************************************
  Description:
    CONFIG_MAX_FIRMWARE_IMAGESIZE defines the ROM size allocated for the
    Updatable application. PDFU Initiator shall flash entire size during
    every re-flash operation. Flashing lesser or more than this Size
    results in error response.
  Remarks:
    Choose Firmware Image size in such a way that integral multiple of 256.
    
    The definition of this function is mandatory when INCLUDE_PDFU is
    TRUE
  Example:
    <code>
      \#define CONFIG_MAX_FIRMWARE_IMAGESIZE 38*1024 for 38KB Updatable application.
    
    </code>
                                                                                    
  ***********************************************************************************/
#define CONFIG_MAX_FIRMWARE_IMAGESIZE
                                                                                          
/**************************************************************************
  Description:
    CONFIG_UPDATABLE_IMAGEBANK_INDEX specifies the Image bank index for
    which firmware upgrade is requested. (or) in other words it corresponds
    to the image bank index of the Updatable application as mentioned by
    Architecture 2.
    
    This information is used during the Reconfiguration phase to determine
    what application is currently executing and whether application
    switching to Fixed Application is required or not.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_UPDATABLE_IMAGEBANK_INDEX   0x03u
    </code>
                                                                           
  **************************************************************************/                                                                                          
#define CONFIG_UPDATABLE_IMAGEBANK_INDEX   


/*****************************************************************************
  Description:
    CONFIG_RECONFIG_PHASE_WAITTIME specifies the Wait time required for the
    Reconfigure state , i.e. the PDFU_Initiate request processing takes
    "Wait time" ms, and next request can be issued by the PDFU_Initiator
    after the specified wait time.
    
    This information is shared with the PDFU Initiator as part of
    PDFU_INITIATE command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_RECONFIG_PHASE_WAITTIME   0x03u //3ms wait time required
    </code>
                                                                              
  *****************************************************************************/                                                                                            
#define CONFIG_RECONFIG_PHASE_WAITTIME     

/****************************************************************************************************
  Description:
    CONFIG_TRANSFER_PHASE_WAITTIME Species the Wait time required during
    the Transfer state , i.e. the PDFU Data request processing takes "Wait
    time" ms, and next PDFU_DATA request to be issued by the initiator
    after the specified wait time.
    
    
    
    This information is shared with the PDFU Initiator as part of PDFU_DATA
    command's response.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_TRANSFER_PHASE_WAITTIME   0x03u //3ms required for processing PDFU_DATA request
    </code>
                                                                                                     
  ****************************************************************************************************/                                                                                           
#define CONFIG_TRANSFER_PHASE_WAITTIME   

/*************************************************************************
  Description:
    CONFIG_VALIDATION_PHASE_WAITTIME specifies the wait time macro for the
    Validation state ,i.e. the PDFU_Validate command's processing takes
    "Wait time" ms, and next request can be issued by the Initiator after
    the specified wait time.
  Remarks:
    The user definition of this macro is mandatory when INCLUDE_PDFU is
    TRUE.
  Example:
    <code>
      \#define CONFIG_VALIDATION_PHASE_WAITTIME   0x03u
    </code>
                                                                          
  *************************************************************************/                                                                                           
#define CONFIG_VALIDATION_PHASE_WAITTIME    

/**************************************************************************
  Function:
                \#define CONFIG_HOOK_GETCURRENT_IMAGEBANK()
  Summary:
    To Return the Index of the Image Bank which is currently executing.
    
    \Example:
    
    \1. 0x00 - Corresponds to Bootloader Application
    
    \2. 0x01 - Corresponds to Fixed Application
    
    \3. 0x02 - Corresponds to Updatable Application
  Description:
    This function is called to get the Index of the Image Bank which is
    currently executing. Zeus Stack follows "Architecture 2 - Fixed base
    application with updatable application image" In which the Fixed
    Application is Image Bank 1 and Updatable Application is Image Bank 2.
  Conditions:
    This function is invoked by the PD Firmware Update State-machine during
    the Enumeration Phase (On reception PDFU_GET_FW_ID Command).
    
    
  Return:
    \Returns Byte Value -That is the index of the Image Bank.
    
    IMAGE_BANK_BOOTLOADER 0x01
    
    IMAGE_BANK_FIXED_APP 0x02
    
    IMAGE_BANK_UPDATABLE_APP 0x03
  Example:
    <code>
    \#define CONFIG_HOOK_GETCURRENT_IMAGEBANK()  getCurrentImageBank()
    
    UINT8 getCurrentImageBank(void)
    {
       \return u8ImageBankIndex;
    
    }
    
    </code>
  Remarks:
    The User definition of the function is mandatory in both Fixed and
    Updatable application when INCLUDE_PDFU is TRUE.                 
  **************************************************************************/

#define CONFIG_HOOK_GETCURRENT_IMAGEBANK()  

/****************************************************************************************
  Function:
              \#define CONFIG_HOOK_PROGRAM_FWBLOCK( _OBJ1_,_LEN_)
  Summary:
    Validate the Data block and program the data to the Memory, and return
    the Status of the Programming Operation.
  Description:
    This Function is invoked during the Transfer Phase on the Successful
    reception event of every PDFU DATA packet. This function is responsible
    for Updating the Firmware data to the memory, and identifying any
    errors during the Firmware flash.
  Conditions:
    Only during the Policy Engine State -Reconfigure Phase or Transfer
    Phase this function will be invoked.
  Input:
    _OBJ1_ -  UINT8 Pointer to PDFU_DATA packet payload Buffer.<p /><p />_OBJ1_[0]
              \- Reserved field \- Contains PD FW Version.<p />_OBJ1_[1] \-
              Reserved field \- Contains Msg Type which is PDFU_DATA\-0x83.<p />_OBJ1_[2]
              \- LSB of Data Block Index.<p />_OBJ1_[3] \- MSB of Data Block
              Index<p />_OBJ1_[4..260] \- Firmware Image data upto 256
              bytes.<p /><p />Where, the Data block index is used to
              calculate the Physical memory address to which the current
              data block corresponds to.<p /><p />
    _LEN_ -   16 bit parameter \- Indicates the length of the Firmware data
              contained in the packet.
  Return:
    \Returns ePE_PDFU_RESPONSE_CODE Type Return Value - The Status of the
    Program Operation.
    
      * ePE_FWUP_OK &#45; Upon successful flash operation.
      * ePE_FWUP_errVERIFY &#45; When verification of the flash operation
        failed.
      * ePE_FWUP_errADDRESS &#45; when data block index is out of range.
  Example:
    <code>
    \#define CONFIG_HOOK_PROGRAM_FWBLOCK(_OBJ1_, _LEN_)     (PDFW_ProcessPDFUDataRequest)
    
    </code>
    ePE_PDFU_RESPONSE_CODE PDFW_ProcessPDFUDataRequest( UINT8
    \*u8RequestBuffer, UINT16 u16RequestLength)
    
    {
    
    UINT16 u16DataBlockIndex = *((UINT16*)&amp;u8RequestBuffer[2]);
    
    
    
    u32ProgAddr = CalculateAddress(u16DataBlockIndex);
    
    
    
    if( u32ProgAddr \< 0xFFFFu )
    
    {
    
    
    
    ProgramMemoryCB(u32ProgAddr, &amp;u8RequestBuffer[4u],
    u16RequestLength);
    
    
    
    ReadMemoryCB(u32ProgAddr, &amp;u8ResponseBuffer[0u], u16RequestLength);
    
    
    
    //Compare data written and read*&#47;
    
    if (CONFIG_HOOK_MEMCMP(&amp;u8ResponseBuffer[0], &amp;u8RequestBuffer[4],
    u16RequestLength) == 0)
    
    {
    
    //Set the status as OK*&#47;
    
    u8Status = ePE_FWUP_OK;
    
    }
    
    else
    
    {
    
    //Verification Stage failure*&#47;
    
    u8Status = ePE_FWUP_errVERIFY;
    
    }
    
    }
    
    else
    
    {
    
    u8Status = ePE_FWUP_errADDRESS;
    
    }
    
    
    
    \return u8Status;
    
    }
    <code>
    
    </code>
  Remarks:
    \ \ 
    
    User definition of this Hook function is mandatory when
    INCLUDE_PDFU is TRUE.                                                          
  ****************************************************************************************/

#define CONFIG_HOOK_PROGRAM_FWBLOCK(_OBJ1_,_LEN_)

/**************************************************************************************************
  Function:
                \#define CONFIG_HOOK_VALIDATE_FIRMWARE(_OBJ1_,_LEN_)
  Summary:
    To validate the Flashed Binary using a User defined validation method
    and return the Status of the Firmware Validation Operation.
  Description:
    This Function is invoked during the validation phase on reception of
    every PDFU Validation Request.
    
    This function is responsible for Validating the Firmware data in the
    memory. The Function shall return the progress status of the Validation
    on every invocation. If the Status indicates "On going" then the
    Validation command will be responded with the configured Wait time.
    
    
    
    Validation Method can be any Custom method as required by the User.
  Conditions:
      * Multiple invocations of the function is possible from PDFU
        Validation phase.
    
    Until the Validation process is complete, for every request of
    PDFU_VALIDATION command this function will be invoked.
    
    
    
    The definition of this function shall include 1) Starting the
    Validation process on the First call, 2) Returning the Status of the
    Validation process during subsequent invocation of the function.
  Return:
    \Returns the UINT8 Status of the Validation Operation.
      * PE_FWUP_VALIDATION_SUCCESSFUL 0x00u
      * PE_FWUP_VALIDATION_INPROGRESS 0x01u
      * PE_FWUP_VALIDATION_FAILURE 0x02u
  Example:
    <code>
    \#define CONFIG_HOOK_VALIDATE_FIRMWARE() (PDFW_ProcessPDFUDataRequest)
    
    UINT8 PDFW_ProcessPDFUValidateRequest(void)
    {
    //
    
    The definition of this function shall include
    1) Starting the Validation process on the First call,
    2) Returning the Status of the Validation process during subsequent invocation of the function.
    
    \*&#47;
    }
    
    </code>
  Remarks:
    User definition of this Hook function is mandatory when INCLUDE_PDFU is
    TRUE                                                                                           
  **************************************************************************************************/

#define CONFIG_HOOK_VALIDATE_FIRMWARE()  

/**************************************************************************
  Function:
                    \#define CONFIG_HOOK_BOOT_FIXEDAPPLICATION()
  Summary:
    CONFIG_HOOK_BOOT_FIXEDAPPLICATION shall perform necessary operation to
    switch from Updatable application to Fixed application.
  Description:
    Re-flash of the Updatable_Application image bank while currently
    executing in the Updatable_Application image bank, requires switch to
    Fixed application for performing the upgrade.
    
    The application switching may include invalidating the
    Updatable_Application signatures (and/or) jump/reset for fresh boot
    from Fixed application.
  Conditions:
    This function is invoked by the PD Firmware Update State-machine during
    the Reconfiguration phase(On reception PDFU_INITIATE Command), when the
    Updatable application is currently running.
  Return:
    No Return Value. During execution of this function the control shall be
    switched to the Fixed application.
  Example:
    <code>
    \#define CONFIG_HOOK_BOOT_FIXEDAPPLICATION()   Boot_Fixed_Application()
    
    void Boot_Fixed_Application(void)
    {
    </code>
    <c> UPD301_EraseUpdatableAppSignature(); //Invalidate the Updatable app
    sign</c>
    <code>
        UPD301_Reset() //Reset to boot from Fixed app
    }
    </code>
  Remarks:
    User definition of this Hook function is mandatory in the Updatable
    application when INCLUDE_PDFU is TRUE                            
  **************************************************************************/

#define CONFIG_HOOK_BOOT_FIXEDAPPLICATION() 

 /***********************************************************************************
   Function:
                         \#define CONFIG_HOOK_BOOT_UPDATABLE_APPLICATION()
   Summary:
     CONFIG_HOOK_BOOT_UPDATABLE_APPLICATION shall perform necessary
     operation to boot from the updatable application after a PDFU is
     successfully completed.
   Description:
     As the flashing operation is executed from the Fixed application, once
     the PDFU process is complete it is necessary to switch to the newly
     upgraded updatable application.
     
     
     
     This function definition shall implement necessary operations to safely
     exit the fixed application and boot from the updatable application.
     
     The application switching may include setting the valid
     Updatable_Application signatures (and) jump/reset for fresh boot from
     Updatable application.
   Conditions:
     This function is invoked by the PD Firmware Update State-machine during
     the Manifestation phase(On reception PDFU_INITIATE Command), when the
     Fixed application is currently running.
   Return:
     No Return Value. During execution of this function the control shall be
     switched to the Updatable application.
   Example:
     <code>
     \#define CONFIG_HOOK_BOOT_UPDATABLE_APPLICATION()   Boot_Updatable_Application()
     
     void Boot_Updatable_Application(void)
     {
         UPD301_Reset() //Reset to boot from Fixed app
     }
     </code>
   Remarks:
     User definition of this Hook function is mandatory in the Fixed
     application when INCLUDE_PDFU is TRUE                                     
   ***********************************************************************************/ 

#define CONFIG_HOOK_BOOT_UPDATABLE_APPLICATION()              
                                                  
   /**************************************************************************
     Function:
             \#define CONFIG_HOOK_IS_PDFU_ALLOWED_NOW()
     Description:
       CONFIG_HOOK_IS_PDFU_ALLOWED_NOW specifies if PD Firmware Update can be
       currently allowed, based on the priority of the application tasks
       currently executing.
       
       
       
       \1. When the PD Firmware Update is allowed, the PDFU Initiator can
       perform firmware upgrade by the PDFU Sequence
       
       \2. When the PD Firmware Update is not allowed, the PDFU Initiator is
       responded with the error code during the Reconfiguration phase.
       
       
       
       \Example scenario of When PDFU cannot be allowed:
       
       Assuming a product with firmware update capability through CC and I2C
       as well. In an example, if the firmware upgrade through I2C is already
       in progress, then PDFU through CC interface shall not be allowed. To
       handle such situations, this macro shall return the current status of
       allowability of firmware upgrade.
     Conditions:
       This function is invoked by the PD Firmware Update State-machine during
       the Reconfiguration Phase (On reception PDFU_INITIATE Command).
     Remarks:
       Shall return the run time status whether PDFU is allowed now or not.
     Return:
       UINT8 value
       
       
       
       0x00 - PDFU Not Allowed.
       
       0x01 - PDFU Allowed.
       
       
     Example:
       <code>
       \#define CONFIG_HOOK_IS_PDFU_ALLOWED_NOW   isPdfuAllowedNow()
       
       UINT8 isPdfuAllowedNow(void)
       {
           \return u8PdfuAllow;
       }
       </code>
                                                                              
     **************************************************************************/
#define CONFIG_HOOK_IS_PDFU_ALLOWED_NOW()   
                                                  
/**************************************************************************************************


    Description:
        CONFIG_HOOK_ASSIGN_PDFU_BUFFER is the address of the buffer.The size of the Assigned buffer is expected to be 260 Bytes, which will be used for Storing the Response
        message data.


    Example:
    <code>
      \#define CONFIG_HOOK_ASSIGN_PDFU_BUFFER  (UINT32)&gu8PDFUResBuffer[0]

   </code>

    Remarks:
		Buffer Shall be of 260 Bytes.
        User definition is mandatory when INCLUDE_PDFU is TRUE
**************************************************************************************************/

#define CONFIG_HOOK_ASSIGN_PDFU_BUFFER  

/**************************************************************************************************


    Description:
        CONFIG_HOOK_FUNCTION_GET_TEMPERATURE calls the system specific function to get the temperature
        in degrees C.


    Example:
    <code>
      \#define CONFIG_HOOK_FUNCTION_GET_TEMPERATURE  hook_function_get_temperature_in_c()

   </code>

    Remarks:
		Buffer Shall be of 260 Bytes.
        User definition is mandatory when INCLUDE_PDFU is TRUE
**************************************************************************************************/
#define CONFIG_HOOK_FUNCTION_GET_TEMPERATURE_IN_C() hook_function_get_temperature_in_c()