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

#ifndef _INT_GLOBALS_H_
#define _INT_GLOBALS_H_

#include <stdinc.h>

extern DEVICE_POLICY_MANAGER gasDPM[CONFIG_PD_PORT_COUNT];

extern PolicyEngine_Status gasPolicy_Engine[CONFIG_PD_PORT_COUNT];

extern TYPEC_CONTROL  gasTypeCcontrol[CONFIG_PD_PORT_COUNT];

extern PORT_CONFIG_DATA gasPortConfigurationData[CONFIG_PD_PORT_COUNT];
extern PORT_CONFIG_DATA gasPortNormalConfigurationData[CONFIG_PD_PORT_COUNT];
extern PORT_CONFIG_DATA gasPortRollbackConfigurationData[CONFIG_PD_PORT_COUNT];

extern PROTOCOL_LAYER_STRUCT gasPRL [CONFIG_PD_PORT_COUNT];

extern PRL_RECVBUFF gasPRLRecvBuff [CONFIG_PD_PORT_COUNT];

#ifdef INCLUDE_PD_3_0

extern PRL_EXTMSG_BUFF gasExtendedMsgBuff [CONFIG_PD_PORT_COUNT];

extern PRL_CHUNK_STRUCT gasChunkSM [CONFIG_PD_PORT_COUNT];

#endif 

extern PDTIMER gasPDTimers[MAX_CONCURRENT_TIMERS];

extern UINT8 gau8PortDisable [CONFIG_PD_PORT_COUNT];


#if INCLUDE_POWER_MANAGEMENT_CTRL
extern UINT8 gau8ISRPortState [CONFIG_PD_PORT_COUNT];

extern UINT8 gau8PortIdleTimerID [CONFIG_PD_PORT_COUNT];

extern UINT8 gu8SetMCUidle;
#endif

#if (FALSE != INCLUDE_PDFU)    
    extern UINT8 gu8PDFUResBuffer[260];
#endif
    
//Functions
UINT8 PD_Init();

void PD_Run();

UINT8 PD_SPIRegresTest();

void WaitUntilSPITestRegister(UINT8 u8PortNum);

void PD_InitializeInternalGlobals();

#endif