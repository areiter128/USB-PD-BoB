/* 
 * File:   hook_functions.h
 * Author: C41076
 *
 * Created on April 16, 2018, 2:59 PM
 */

#ifndef HOOK_FUNCTIONS_H
#define	HOOK_FUNCTIONS_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void configure_upd350_gpio (void);
void hw_portpower_init(void);
void hw_portpower_driveVBUS(uint8_t u8PortNum,uint16_t u16VBUS_Volatge);
void hw_configure_discharge_output (void);
void hw_portpower_enab_dis_VBUSDischarge(uint8_t u8PortNum, uint8_t u8EnableDisable);
void CRITICAL_SECTION_ENTER(void);
void CRITICAL_SECTION_EXIT(void);

void updalert_init(uint8_t *p_port_disable);
uint8_t upd_irq_asserted(uint8_t port_num);

void updreset_init(void);
void updreset_thru_gpio(void);


void hw_spi_init( void );
void hw_spi_cs_low (uint8_t u8Portnum);
void hw_spi_cs_high(uint8_t u8Portnum);
void SPI_Write(uint8_t *pu8WriteBuffer, uint16_t u16Writelength);
void SPI_Read(uint8_t *pu8ReadBuffer, uint16_t u16Writelength);

uint8_t dsPIC_HandlePowerFault(uint8_t u8PortNum, uint8_t u8PwrFaultSts);

void hook_debug_print_string (char *str);
void hook_debug_u8(uint8_t u8val);
void hook_debug_u16(uint16_t u16val);
void hook_debug_u32(uint32_t u32val);
void hook_debug_i32(int32_t i32val);

/* define PORT*/
#define PORT0 		0
#define PORT1		1


#ifdef	__cplusplus
}
#endif

#endif	/* HOOK_FUNCTIONS_H */

