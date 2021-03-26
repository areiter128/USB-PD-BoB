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

#define PWRCTRL_VBUS_0V		0
#define PWRCTRL_VBUS_5V		5000
#define PWRCTRL_VBUS_9V		9000
#define PWRCTRL_VBUS_15V	15000
#define PWRCTRL_VBUS_20V	20000

void configure_upd350_gpio (void);
void port_led_on(uint8_t u8PortNum);
void port_led_off(uint8_t u8PortNum);

void hw_portpower_init(uint8_t port_number);
void hw_portpower_driveVBUS(uint8_t u8PortNum,uint16_t u16VBUS_Volatge, uint16_t u16Current);
void hw_configure_discharge_output (void);
void hw_portpower_enab_dis_VBUSDischarge(uint8_t u8PortNum, uint8_t u8EnableDisable);
void CRITICAL_SECTION_ENTER(void);
void CRITICAL_SECTION_EXIT(void);

void updalert_init(uint8_t u8PortNum);
uint8_t upd_irq_asserted(uint8_t port_num);

void updreset_init(uint8_t u8PortNum);
void updreset_thru_gpio(uint8_t u8PortNum);


uint8_t hw_spi_init( void );
void hw_spi_cs_set (uint8_t u8Portnum, uint8_t EnDis);
//void hw_spi_cs_low (uint8_t u8Portnum);
//void hw_spi_cs_high(uint8_t u8Portnum);
void SPI_Write(uint8_t *pu8WriteBuffer, uint16_t u16Writelength);
void SPI_Read(uint8_t *pu8ReadBuffer, uint16_t u16Writelength);

void hook_policy_engine_pre_process(uint8_t u8PortNum, uint8_t *u8DataBuf, uint8_t u8SOPType, uint8_t u32Header);
uint8_t hook_pdo_request_post_process_valid(uint8_t port_num, uint16_t max_current, uint8_t pdo_requested);
void hook_notify_pd_events_cb(uint8_t port_num, uint8_t event);

uint8_t dsPIC_HandlePowerFault(uint8_t u8PortNum, uint8_t u8PwrFaultSts);

void hook_memcpy(uint8_t *dest, uint8_t *src, uint32_t cp_size);

uint16_t hook_function_get_temperature_in_c(void);

#if CONFIG_HOOK_DEBUG_MSG
void hook_debug_print_string (char *str);
void hook_debug_u8(uint8_t u8val);
void hook_debug_u16(uint16_t u16val);
void hook_debug_u32(uint32_t u32val);
void hook_debug_i32(int32_t i32val);
#endif

/* define PORT*/
#define PORT0 		0
#define PORT1		1


#ifdef	__cplusplus
}
#endif

#endif	/* HOOK_FUNCTIONS_H */

