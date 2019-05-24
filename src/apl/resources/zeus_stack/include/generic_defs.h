
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

#ifndef PROJ_DEFS_H
#define	PROJ_DEFS_H

#include "ProjectVersion.h"

/* TRUE/FALSE defines */
#define FALSE                                     0
#define TRUE                                      1

/* Boolean */
#define BOOL                                      unsigned char

/* Unsigned integers */
#define UINT8                                     unsigned char
#define UINT16                                    unsigned short
#define UINT32                                    unsigned long


/* Signed Integer */
#define INT8                                      signed char
#define INT16                                     short
#define INT32                                     long

/* Signed character */
#define CHAR                                      char

/* Unsigned character */
#define UCHAR                                     unsigned char

/* Size of operator */
#define SIZEOF(x)                                 sizeof(x)

#define BIT(x)                                    ((uint32_t)1 << x)

/* Data Size */ 
#define BYTE_LEN_1			        			1
#define BYTE_LEN_2			        			2
#define BYTE_LEN_3			        			3
#define BYTE_LEN_4			        			4
#define BYTE_LEN_10                 			10
#define BYTE_LEN_16			        			16

#define BYTE_0									0
#define BYTE_1									1
   			
#define LOBYTE(u16Var)							((UINT8)(u16Var))
#define HIBYTE(u16Var)							((UINT8)((u16Var) >> 8) & 0xFF)
			
#define HIWORD(u32Var)							((UINT16)(((u32Var) >> 16) & 0xFFFF))
#define LOWORD(u32Var)							((UINT16)((u32Var) & 0xFFFF))


#define MAKE_UINT16(u8HiByte, u8LoByte)			(((UINT16)u8LoByte) | (((UINT16)u8HiByte) << 8))
#define MAKE_UINT32(u16HiWord, u16LoWord)		(((UINT32)u16LoWord) | (((UINT32)u16HiWord) << 16))

#define MAKE_UINT32_FROM_BYTES(u8LoWordLoByte, u8LoWordHiByte, u8HiWordLoByte, u8HiWordHiByte)	\
												(((UINT32)u8LoWordLoByte)					|	\
												(((UINT32)u8LoWordHiByte) << 8)				|	\
												(((UINT32)u8HiWordLoByte) << 16) 			|	\
												(((UINT32)u8HiWordHiByte) << 24u))
			
/* CLEAR & RESET VALUE */

#define CLR_VAL                                         0x00
#define RESET_TO_ZERO									0
#define SET_TO_ZERO									    0                                                
                                                  
#endif
                                                      