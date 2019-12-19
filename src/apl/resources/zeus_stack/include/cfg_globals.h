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

#ifndef _CFG_GLOBALS_H_
#define _CFG_GLOBALS_H_

/* JMS - Modified to set the Unconstrained Power bit (bit 27) for the first PDO */
#define PE_SRC_PDO_GENERATION(n,x) \
  ((x == 1) ? (((uint32_t) 1) << 27) : (((uint32_t) 0) << 27) )| \
  (((uint32_t)CONFIG_PORT_##n##_SOURCE_PDO_##x##_USB_COM) << 26) | \
  ((((uint32_t)CONFIG_PORT_##n##_SOURCE_PDO_##x##_VOLTAGE)/50) << 10) |\
  (((uint32_t)CONFIG_PORT_##n##_SOURCE_PDO_##x##_CURRENT)/10) 

/* JMS - Define a PDO generator for rollback mode (all currents / 2)*/
#define PE_SRC_ROLLBACK_PDO_GENERATION(n,x) \
  ((x == 1) ? (((uint32_t) 1) << 27) : (((uint32_t) 0) << 27) )| \
  (((uint32_t)CONFIG_PORT_##n##_SOURCE_PDO_##x##_USB_COM) << 26) | \
  ((((uint32_t)CONFIG_PORT_##n##_SOURCE_PDO_##x##_VOLTAGE)/50) << 10) |\
  (((uint32_t)((CONFIG_PORT_##n##_SOURCE_PDO_##x##_CURRENT) / 2)) / 10) 
 
#define PE_PDO_GENERATION_DISABLED(n,x)    (uint32_t)0

#define PE_PORT_SRC_PDO_GENERATION(n) \
            (PE_SRC_PDO_GENERATION(n,1)), \
            (PE_SRC_PDO_GENERATION(n,2)), \
            (PE_SRC_PDO_GENERATION(n,3)), \
            (PE_SRC_PDO_GENERATION(n,4)), \
            (PE_SRC_PDO_GENERATION(n,5)), \
            (PE_SRC_PDO_GENERATION(n,6)),\
            (PE_SRC_PDO_GENERATION(n,7))

/* JMS - Define a PDO generator for rollback mode */
#define PE_PORT_SRC_ROLLBACK_PDO_GENERATION(n) \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,1)), \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,2)), \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,3)), \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,4)), \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,5)), \
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,6)),\
            (PE_SRC_ROLLBACK_PDO_GENERATION(n,7))

    
#define PE_PORT_SRC_PDO_GENERATION_DISABLED(n)  (PE_PDO_GENERATION_DISABLED(n,1)),\
                                                (PE_PDO_GENERATION_DISABLED(n,2)),\
                                                (PE_PDO_GENERATION_DISABLED(n,3)),\
                                                (PE_PDO_GENERATION_DISABLED(n,4)),\
                                                (PE_PDO_GENERATION_DISABLED(n,5)),\
                                                (PE_PDO_GENERATION_DISABLED(n,6)),\
                                                (PE_PDO_GENERATION_DISABLED(n,7))
                                            

#define PE_PORT_SRC_NUM_PDO(n)      ((uint8_t)CONFIG_PORT_##n##_SOURCE_NUM_OF_PDOS) 
                                                     
#define PE_SRC_PORT_FIXED_PDO(x)  PE_PORT_SRC_PDO_GENERATION(x),PE_PORT_SRC_NUM_PDO(x)
  
#define PE_PORT_NOT_AS_SOURCE_OR_DISABLED(x)  PE_PORT_SRC_PDO_GENERATION_DISABLED(x),(uint8_t)0
                                                      
#define PE_SNK_PDO_GENERATION(n,x) \
 ((uint32_t)CONFIG_PORT_##n##_SINK_HIGHER_CAPABILITY << 28) | \
 (((uint32_t)CONFIG_PORT_##n##_SINK_PDO_##x##_USB_COM) << 26) | \
  ((((uint32_t)CONFIG_PORT_##n##_SINK_PDO_##x##_VOLTAGE)/50) << 10) |\
  (((uint32_t)CONFIG_PORT_##n##_SINK_PDO_##x##_CURRENT)/10) 
  
    
#define PE_PORT_SNK_PDO_GENERATION(n) \
            (PE_SNK_PDO_GENERATION(n,1)), \
            (PE_SNK_PDO_GENERATION(n,2)), \
            (PE_SNK_PDO_GENERATION(n,3)), \
            (PE_SNK_PDO_GENERATION(n,4)), \
            (PE_SNK_PDO_GENERATION(n,5)), \
            (PE_SNK_PDO_GENERATION(n,6)),\
            (PE_SNK_PDO_GENERATION(n,7))

    
#define PE_PORT_SNK_PDO_GENERATION_DISABLED(n)  (PE_PDO_GENERATION_DISABLED(n,1)),\
                                              (PE_PDO_GENERATION_DISABLED(n,2)),\
                                              (PE_PDO_GENERATION_DISABLED(n,3)),\
                                                (PE_PDO_GENERATION_DISABLED(n,4)),\
                                                (PE_PDO_GENERATION_DISABLED(n,5)),\
                                                  (PE_PDO_GENERATION_DISABLED(n,6)),\
                                                    (PE_PDO_GENERATION_DISABLED(n,7))
                                            

#define PE_PORT_SNK_NUM_PDO(n)    ((uint8_t)CONFIG_PORT_##n##_SINK_NUM_OF_PDOS) 
                                                     
#define PE_SNK_PORT_FIXED_PDO(x)  PE_PORT_SNK_PDO_GENERATION(x),PE_PORT_SNK_NUM_PDO(x)
  
#define PE_PORT_NOT_AS_SINK_OR_DISABLED(x)  PE_PORT_SNK_PDO_GENERATION_DISABLED(x),((uint8_t)0)
                                                      


#define TYPEC_CONFIG_DATA(n) ((((uint32_t)CONFIG_PORT_##n##_RP_CURRENT_VALUE) << TYPEC_PORT_RPVAL_POS)|((uint32_t)CONFIG_PORT_##n##_POWER_ROLE))

#if INCLUDE_POWER_FAULT_HANDLING
    /* Obtains VBUS PIO*/                                                     
    #define UPD_EN_VBUS_PIO_MNG(n)		(CONFIG_PORT_##n##_EN_VBUS_UPD_PIO)
    /* Obtains PRT_CTL/OCS PIO */                                                     
    #define UPD_PRT_CTL_OCS_PIO_MNG(n)	(CONFIG_PORT_##n##_PRT_CTL_OCS_UPD_PIO)
    /* defines for obtaining PIO number*/
    #define UPD_PIO_MNG_CONFIG(n) UPD_EN_VBUS_PIO_MNG(n),UPD_PRT_CTL_OCS_PIO_MNG(n)
#else
    #define UPD_PIO_MNG_CONFIG(n)
#endif


//Functions
void PD_InitializeConfigGlobals();


#endif