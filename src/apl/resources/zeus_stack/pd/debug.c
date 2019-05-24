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

#ifdef CONFIG_HOOK_DEBUG_MSG

void HookDebugBufferInt32 (INT32 *pi32Buffer, UINT32 u32TotalCount)
{
    for (UINT32 u32Count = 0; u32Count < u32TotalCount; u32Count++)
    {
        CONFIG_HOOK_DEBUG_INT32 (pi32Buffer[u32Count]);        
    }
}
void HookDebugBufferUint32 (UINT32 *pu32Buffer, UINT32 u32TotalCount)
{
    for (UINT32 u32Count = 0; u32Count < u32TotalCount; u32Count++)
    {
        CONFIG_HOOK_DEBUG_UINT32 (pu32Buffer[u32Count]);
    }
}
void HookDebugBufferUint16 (UINT16 *pu16Buffer, UINT32 u32TotalCount)
{
    for (UINT32 u32Count = 0; u32Count < u32TotalCount; u32Count++)
    {
        CONFIG_HOOK_DEBUG_UINT16 (pu16Buffer[u32Count]);
    }
}
void HookDebugBufferUint8 (UINT8 *pu8Buffer, UINT32 u32TotalCount)
{
    for (UINT32 u32Count = 0; u32Count < u32TotalCount; u32Count++)
    {
        CONFIG_HOOK_DEBUG_UINT8 (pu8Buffer[u32Count]);
    }
}
#endif
