
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

/*******************************************************************/
/******************* Global variables********************************/
/*******************************************************************/

DEVICE_POLICY_MANAGER gasDPM[CONFIG_PD_PORT_COUNT];

PolicyEngine_Status gasPolicy_Engine[CONFIG_PD_PORT_COUNT];

PDTIMER gasPDTimers[MAX_CONCURRENT_TIMERS];
 
/* PD_MAC global structs */

/* PRL State variables */
PROTOCOL_LAYER_STRUCT gasPRL [CONFIG_PD_PORT_COUNT];


//todo: Poornima allocate a fixed memory for this
/* PRL receiver Struct*/
PRL_RECVBUFF gasPRLRecvBuff [CONFIG_PD_PORT_COUNT];

#ifdef INCLUDE_PD_3_0
/* PRL extended message buffer for Tx & Rx*/
PRL_EXTMSG_BUFF gasExtendedMsgBuff [CONFIG_PD_PORT_COUNT];

/* PRL chunk state variable struct*/
PRL_CHUNK_STRUCT gasChunkSM [CONFIG_PD_PORT_COUNT];

#endif 

/* Disable ports at run time if UPD350 is absent*/
UINT8 gau8PortDisable [CONFIG_PD_PORT_COUNT];

#if INCLUDE_POWER_MANAGEMENT_CTRL
	/*State of the port whether IDLE or Active*/
    UINT8 gau8ISRPortState [CONFIG_PD_PORT_COUNT];
	/*Timer ID of IDLE Timer*/
    UINT8 gau8PortIdleTimerID [CONFIG_PD_PORT_COUNT];
    /*MCU Idle flag*/
    UINT8 gu8SetMCUidle;

#endif

#if (FALSE != INCLUDE_PDFU)    
    UINT8 gu8PDFUResBuffer[260] = {0};
#endif
/*******************************************************************/
/******************* Functions**************************************/
/*******************************************************************/

void PD_GenericInitialize (UINT8 u8PortNum)
{   
    /*Set as disabled for all ports*/
    gau8PortDisable[u8PortNum] = PORT_STATUS_DISABLED;

#if INCLUDE_POWER_MANAGEMENT_CTRL    
    /*Set UPD state as Active*/
    gau8ISRPortState[u8PortNum] = UPD_STATE_ACTIVE;
    
    /*Start idle timer */
    gau8PortIdleTimerID[u8PortNum] = PDTimer_Start(\
										CONFIG_PORT_UPD_IDLE_TIMEOUT_MS,\
										UPD_SetIdleCB,\
										u8PortNum, \
										NULL);
    /*Set MCU Idle flag as FALSE*/
    gu8SetMCUidle = UPD_MCU_ACTIVE;
#endif
}

void PD_InitializeInternalGlobals()
{
    for (UINT8 u8PortNum = 0; u8PortNum < CONFIG_PD_PORT_COUNT; u8PortNum++)
    {
        PD_GenericInitialize (u8PortNum);

        DPM_Init(u8PortNum);

        PE_InitPort(u8PortNum);
        
        #if (FALSE != INCLUDE_PDFU)
            PE_FwUpdtInitialize();
        #endif
    }
}
