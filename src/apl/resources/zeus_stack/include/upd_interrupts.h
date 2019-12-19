
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


#ifndef _UPD_INTERRUPTS_H_
#define _UPD_INTERRUPTS_H_

#include <stdinc.h>

void UPDIntr_AlertHandler (UINT8 u8PortNum);


#define UPDINTR_INT_STS         	UPD_SYSTEM_CSR_BASE_ADDR + 0x10
#define UPDINTR_INT_EN				UPD_SYSTEM_CSR_BASE_ADDR + 0x14

/* Bit defintion of UPDINTR_INT_STS register */

#define UPDINTR_GP_TIMER_INT            BIT (14)
#define UPDINTR_RDY_INT                 BIT (12)
#define UPDINTR_EXT_INT                 BIT (11)
#define UPDINTR_PWR_INT                 BIT (10)
#define UPDINTR_VBUS_INT                BIT (9)
#define UPDINTR_HPD_INT                 BIT (8)
#define UPDINTR_PSW_INT                 BIT (7)
#define UPDINTR_WDT_INT                 BIT (6)
#define UPDINTR_PPC_INT                 BIT (5)
#define UPDINTR_MAC_INT                 BIT (4)
#define UPDINTR_OCS_CMP_INT             BIT (3)
#define UPDINTR_PIO_OVERRIDE_INT        BIT (2)
#define UPDINTR_PIO_INT                 BIT (1)
#define UPDINTR_CC_INT                  BIT (0)




#endif