/*LICENSE *********************************************************************
 *
 * Software License Agreement
 *
 * Copyright � 2016 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED ìAS ISî WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/
 
#ifndef _APPLICATION_LAYER_DEFINES_H_
#define _APPLICATION_LAYER_DEFINES_H_

#include <stdint.h>
#include "stdbool.h"
#include "stddef.h"

/* ***************************************************************************************
 *	Generic Macros
 * **************************************************************************************/

#define WDT_RESET		asm volatile ("CRLWDT\n")
#define PWRSAV_IDLE		asm volatile ("PWRSAV #1\n")
#define PWRSAV_SLEEP	asm volatile ("PWRSAV #0\n")
#define CPU_RESET		asm volatile ("RESET\n")

#ifdef (CTXTSTAT)
  #define ALTWREG_SWAP(x)    asm volatile ( "PUSH.W W0 \n CTXTSWP #" + x + "POP.W W0 \n" )
#endif

#endif  /* _APPLICATION_LAYER_DEFINES_H_ */

