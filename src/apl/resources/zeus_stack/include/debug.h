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

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdinc.h>

#ifdef CONFIG_HOOK_DEBUG_MSG

    #define HOOK_DEBUG_PORT_STR(_portNum_,_str_)                   {CONFIG_HOOK_DEBUG_INT32(_portNum_);\
                                                                    CONFIG_HOOK_DEBUG_STRING(_str_);}

    #define HOOK_DEBUG_BUF_UINT8(_prtNum_,_str1_,_u8Buf_,_u32Len_,_str2_)  {CONFIG_HOOK_DEBUG_INT32(_prtNum_);\
                                                                            CONFIG_HOOK_DEBUG_STRING(_str1_);\
                                                                            HookDebugBufferUint8(_u8Buf_,_u32Len_);\
                                                                            CONFIG_HOOK_DEBUG_STRING(_str2_);}

    #define HOOK_DEBUG_BUF_UINT16(_prtNum_,_str1_,_u16Buf_,_u32Len_,_str2_)  {CONFIG_HOOK_DEBUG_INT32(_prtNum_);\
                                                                             CONFIG_HOOK_DEBUG_STRING(_str1_);\
                                                                            HookDebugBufferUint16(_u16Buf_,_u32Len_);\
                                                                            CONFIG_HOOK_DEBUG_STRING(_str2_);}

    #define HOOK_DEBUG_BUF_UINT32(_prtNum_,_str1_,_u32Buf_,_u32Len_,_str2_)  {CONFIG_HOOK_DEBUG_INT32(_prtNum_);\
                                                                     CONFIG_HOOK_DEBUG_STRING(_str1_);\
                                                                    HookDebugBufferUint32(_u32Buf_,_u32Len_);\
                                                                    CONFIG_HOOK_DEBUG_STRING(_str2_);}

    #define HOOK_DEBUG_BUF_INT32(_prtNum_,_str1_,_i32Buf_,_u32Len_,_str2_)  {CONFIG_HOOK_DEBUG_INT32(_prtNum_);\
                                                                     CONFIG_HOOK_DEBUG_STRING(_str1_);\
                                                                    HookDebugBufferInt32(_i32Buf_,_u32Len_);\
                                                                    CONFIG_HOOK_DEBUG_STRING(_str2_);}
#else

    #define HOOK_DEBUG_PORT_STR(_portNum_,_str_) 

    #define HOOK_DEBUG_BUF_UINT8(_prtNum_,_str1_,_u8Buf_,_u32Len_,_str2_)  

    #define HOOK_DEBUG_BUF_UINT16(_prtNum_,_str1_,_u16Buf_,_u32Len_,_str2_) 

    #define HOOK_DEBUG_BUF_UINT32(_prtNum_,_str1_,_u32Buf_,_u32Len_,_str2_)

    #define HOOK_DEBUG_BUF_INT8(_prtNum_,_str1_,_i8Buf_,_u32Len_,_str2_) 

#endif


#ifdef CONFIG_HOOK_DEBUG_MSG
	void HookDebugBufferInt32 (INT32 *pi32Buffer, UINT32 u32TotalCount);
	void HookDebugBufferUint32 (UINT32 *pu32Buffer, UINT32 u32TotalCount);
	void HookDebugBufferUint16 (UINT16 *pu16Buffer, UINT32 u32TotalCount);
	void HookDebugBufferUint8 (UINT8 *pu8Buffer, UINT32 u32TotalCount);
#endif

#endif
