/*LICENSE ********************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 * ***************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "portable/dsPIC/ZeusStackConfig.h"
#include "include/stdinc.h"

#include "debug_uart.h"
#include <libpic30.h>

#include "thermal_power_management.h"
#include "apl/resources/c4swbb_control.h"
#include "apl/tasks/task_PowerControl.h"

// TODO: JMS - Need to get these included from task_PowerControl.h (resolve compile errors)
extern volatile C4SWBB_PWRCTRL_t c4swbb_1;
extern volatile C4SWBB_PWRCTRL_t c4swbb_2;

//#include "../Compensator/Compensation.h"

//volatile uint8_t port0_interrupt_flag = 0;
//volatile uint8_t port1_interrupt_flag = 0;

// *****************************************************************************
// *****************************************************************************
// Section: UPD350 I/O setup
// *****************************************************************************
// *****************************************************************************
void configure_upd350_gpio (void)
{
    uint8_t port_number;

    // UPD350 GPIO initialization for pins outside of stack control.
    for (port_number = 0; port_number < CONFIG_PD_PORT_COUNT; port_number++)
    {
        // Set up PIO9 as output to control the LED for each port.
        UPD_GPIOSetDirection(port_number, UPD_PIO9, UPD_GPIO_SETDIR_OUTPUT);
        UPD_GPIOSetBufferType(port_number, UPD_PIO9, UPD_GPIO_SETBUF_PUSHPULL);
        UPD_GPIOSetClearOutput(port_number, UPD_PIO9, UPD_GPIO_CLEAR);
        UPD_GPIOEnableDisable(port_number, UPD_PIO9, UPD_ENABLE_GPIO);
    }
}

void port_led_on(uint8_t u8PortNum)
{
    UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO9, UPD_GPIO_SET);
}
void port_led_off(uint8_t u8PortNum)
{
    UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO9, UPD_GPIO_CLEAR);
}


// *****************************************************************************
// *****************************************************************************
// Section: Port power control configuration
// *****************************************************************************
// *****************************************************************************
void hw_portpower_init(void)
{
    uint8_t port_number;
//    uint32_t reg_data;
        
    // Configure the UPD GPIO pins to be used for discharge
    // and port power switch enable set the pins low to disable the discharge circuit
    // and disable the PPS.  Here we assume that the discharge control and PPS are 
    // on the same GPIO on all UPD350 devices.
    for (port_number = 0; port_number < CONFIG_PD_PORT_COUNT; port_number++)
    {
        // Set up PIO2 as output defaulting low for PPS discharge control (active high)
        UPD_GPIOSetDirection(port_number, UPD_PIO2, UPD_GPIO_SETDIR_OUTPUT);
        UPD_GPIOSetBufferType(port_number, UPD_PIO2, UPD_GPIO_SETBUF_PUSHPULL);
        UPD_GPIOSetClearOutput(port_number, UPD_PIO2, UPD_GPIO_CLEAR);
        UPD_GPIOEnableDisable(port_number, UPD_PIO2, UPD_ENABLE_GPIO);
        
        // Set up PIO7 as output defaulting low for PPS Enable control (active high)
        UPD_GPIOSetDirection(port_number, UPD_PIO7, UPD_GPIO_SETDIR_OUTPUT);
        UPD_GPIOSetBufferType(port_number, UPD_PIO7, UPD_GPIO_SETBUF_PUSHPULL);
        UPD_GPIOSetClearOutput(port_number, UPD_PIO7, UPD_GPIO_CLEAR);
        UPD_GPIOEnableDisable(port_number, UPD_PIO7, UPD_ENABLE_GPIO);

        
//        // Set up the debounce register for PIO5 (the fault input from power switch)
//        // default is 10 * 1us
//        reg_data = 0x00000400;
//        UPD_RegisterWrite(port_number, 0x0070, (uint8_t *)&reg_data, BYTE_LEN_4);


    }
}

void hw_portpower_driveVBUS(uint8_t u8PortNum, uint16_t u16VBUS_Voltage)
{
   volatile C4SWBB_PWRCTRL_t *p_port_instance;
    
    switch (u8PortNum)
    {
        case 0:
            // Port 0
            p_port_instance = &c4swbb_1;
            break;
            
        case 1:
            // Port 1
            p_port_instance = &c4swbb_2;
            break;
            
        default:
            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: Invalid Port Number\r\n");
            return;
    }
        /*
     * Set up the port's buck converter to produce the proper voltage level
     */
    switch(u16VBUS_Voltage)
    {
        case PWRCTRL_VBUS_0V:
            //Drive 0V on VBUS line of "u8PortNum" Port
            p_port_instance->data.v_ref = C4SWBB_VOUT_REF_5V;
            p_port_instance->status.bits.autorun = false;
            p_port_instance->status.bits.enable = false;
            p_port_instance->status.bits.GO = 0;
            /* Clear the enable pin for the port power switch */
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO7, UPD_GPIO_CLEAR);

            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: 0V\r\n");
            break;

        case PWRCTRL_VBUS_5V:
            //Drive 5V on VBUS line of "u8PortNum" Port
            p_port_instance->data.v_ref = C4SWBB_VOUT_REF_5V;
            p_port_instance->status.bits.autorun = false;
            p_port_instance->status.bits.enable = true;
            p_port_instance->status.bits.GO = 1;
            /* Enable the port power switch */
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO7, UPD_GPIO_SET);
            
            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: 5V\r\n");
            break;

        case PWRCTRL_VBUS_9V:
            //Drive 9V on VBUS line of "u8PortNum" Port
            p_port_instance->data.v_ref = C4SWBB_VOUT_REF_9V;
            p_port_instance->status.bits.autorun = false;
            p_port_instance->status.bits.enable = true;
            p_port_instance->status.bits.GO = 1;
            /* Enable the port power switch */
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO7, UPD_GPIO_SET);

            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: 9V\r\n");
            break;

        case PWRCTRL_VBUS_15V:
            //Drive 15V on VBUS line of "u8PortNum" Port
            p_port_instance->data.v_ref = C4SWBB_VOUT_REF_15V;
            p_port_instance->status.bits.autorun = false;
            p_port_instance->status.bits.enable = true;
            p_port_instance->status.bits.GO = 1;
            /* Enable the port power switch */
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO7, UPD_GPIO_SET);

            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: 15V\r\n");
            break;

        case PWRCTRL_VBUS_20V:
            //Drive 20V on VBUS line of "u8PortNum" Port
            p_port_instance->data.v_ref = C4SWBB_VOUT_REF_20V;
            p_port_instance->status.bits.autorun = false;
            p_port_instance->status.bits.enable = true;
            p_port_instance->status.bits.GO = 1;
            /* Enable the port power switch */
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO7, UPD_GPIO_SET);

            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: 20V\r\n");
            break;

        default:
            HOOK_DEBUG_PORT_STR (u8PortNum,"Drive VBUS: Invalid Voltage Selection\r\n");
            break;

    }

}

void hw_portpower_enab_dis_VBUSDischarge(uint8_t u8PortNum, uint8_t u8EnableDisable)
{
    // Implement VBUS Discharge enable/disable hook function
    switch(u8EnableDisable)
    {
        case PWRCTRL_ENABLE_VBUSDIS:
        {
            // Enable the VBUS Discharge for "u8PortNum" Port
            // Set the discharge enable high
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO2, UPD_GPIO_SET);
            break;

        }
        case PWRCTRL_DISABLE_VBUSDIS:
        {
            // Disable the VBUS Discharge for "u8PortNum" Port
            // Set the discharge enable low
            UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO2, UPD_GPIO_CLEAR);
            break;

        }
        default:
        {
            break;
        }
    }
    
}    
        
void CRITICAL_SECTION_ENTER(void)
{
    // UPD350 is polled so no critical section needed
}

void CRITICAL_SECTION_EXIT(void)
{
    // UPD350 is polled so no critical section needed
}


void updalert_init(uint8_t *p_port_disable)
{
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    
    if (p_port_disable[0] == PORT_STATUS_ENABLED)
    {
        // PORT 0
        TRISDbits.TRISD1 = 1;  // INT1 for UPD350 IRQ
        //ANSELCbits.ANSC7 = 0;
        CNPUDbits.CNPUD1 = 1;
 
        // Do not use interrupts for UPD350 IRQ.  Process in main task loop.
        //RPINR0bits.INT1R = 52;  // RP52 INT1 external interrupt input, pin RC4

        //IFS1bits.INT1IF = 0;
        //INTCON2bits.INT1EP = 1; // Interrupt on falling edge.
        //IPC5bits.INT1IP = 4;    // Set Interrupt Priority
        //IEC1bits.INT1IE = 1;    // Ext interrupt enable
        
    }

#if (CONFIG_PD_PORT_COUNT > 1)
    if (p_port_disable[1] == PORT_STATUS_ENABLED)
    {   // PORT 1
        TRISCbits.TRISC0 = 1;  // INT2 for UPD350 IRQ
        //ANSELCbits.ANSC6 = 0;
        CNPUCbits.CNPUC0 = 1;
        
        // Do not use interrupts for UPD350 IRQ.  Process in main task loop.
        //RPINR1bits.INT2R = 60;  // RP60 INT2 external interrupt input, pin RC12

        //IFS1bits.INT2IF = 0;
        //INTCON2bits.INT2EP = 1; // Interrupt on falling edge.
        //IPC7bits.INT2IP = 4;    // Set Interrupt Priority
        //IEC1bits.INT2IE = 1;    // Ext interrupt enable
    }
#endif // CONFIG_PD_PORT_COUNT > 1    
}

uint8_t upd_irq_asserted(uint8_t port_num)
{
    uint8_t irq_asserted = 0;
    
    switch (port_num)
    {
        case 0:
            // Check UPD350 IRQ for Port 0
            if (PORTDbits.RD1 == 0)
            {
                irq_asserted = 1;
            }    
            break;
            
        case 1:
            // Check UPD350 IRQ for Port 1
            if (PORTCbits.RC0 == 0)
            {
                irq_asserted = 1;
            }    
            break;
            
        default:
            break;   
    }
    
    return (irq_asserted);
}

void updreset_init(void)
{
    //Initialization of MCU GPIOs connected to UPD350 reset lines
    //PORT 0
    TRISBbits.TRISB10 = 0;
    //PORT 1
    TRISAbits.TRISA1 = 0;
    

    // Assert hard reset at startup.
    LATBbits.LATB10 = 0;
    LATAbits.LATA1 = 0;
    
    // TODO: how_to_do_delay_function? __delay_ms(100);
    
    //Make the gpio line high as default
    LATBbits.LATB10 = 1;
    LATAbits.LATA1 = 1;
}

void updreset_thru_gpio(void)
{
    // Assert hard reset at startup.
    LATBbits.LATB10 = 0;
    LATAbits.LATA1 = 0;
     
    // TODO: how_to_do_delay_function? __delay_ms(100);
    
    //Make the gpio line high as default
    LATBbits.LATB10 = 1;
    LATAbits.LATA1 = 1;

}


void hw_spi_init( void )
{
    //Microcontroller SPI module init
    SPI2_Initialize();
}

void hw_spi_cs_low (uint8_t u8Portnum)
{
    if (u8Portnum == 0)
    {
        //Set pin level low for respective GPIO that is connected to the UPD350 SPI CS pin
        LATBbits.LATB7 = 0;
    }
    else if (u8Portnum == 1)
    {
        //Set pin level low for respective GPIO that is connected to the UPD350 SPI CS pin
        LATDbits.LATD13 = 0;
    }

}

void hw_spi_cs_high (uint8_t u8Portnum)
{
    if (u8Portnum == 0)
    {
        //Set pin level high for respective GPIO that is connected to the UPD350 SPI CS pin
        LATBbits.LATB7 = 1;
    }
    else if (u8Portnum == 1)
    {
        //Set pin level high for respective GPIO that is connected to the UPD350 SPI CS pin
        LATDbits.LATD13 = 1;
    }
}

void SPI_Write(uint8_t *pu8WriteBuffer, uint16_t u16Writelength)
{
    SPI2_Exchange8bitBuffer(pu8WriteBuffer, u16Writelength, NULL);
}

void SPI_Read(uint8_t *pu8ReadBuffer, uint16_t u16Writelength)
{
    SPI2_Exchange8bitBuffer(NULL, u16Writelength, pu8ReadBuffer);
}

//void __attribute__((__interrupt__,no_auto_psv)) _INT1Interrupt(void)
//{
//    IFS1bits.INT1IF = 0;
//    //***User Area Begin->code: INT1 - External Interrupt 1***
//    // INT1 is the interrupt for UPD PORT 0.  Set flag to indicate that 
//    // the interrupt has occurred so that the main loop will process.
//    /* Check if Port0 Interrupt*/
//    port0_interrupt_flag = 1;
//    //UPDIntr_AlertHandler (0);
//}    
//
//void __attribute__((__interrupt__,no_auto_psv)) _INT2Interrupt(void)
//{
//    IFS1bits.INT2IF = 0;
//    //***User Area Begin->code: INT2 - External Interrupt 2***
//    // INT2 is the interrupt for UPD PORT 1.  Set flag to indicate that 
//    // the interrupt has occurred so that the main loop will process.
//    /* Check if Port 1 Interrupt*/
//    port1_interrupt_flag = 1;
//    //UPDIntr_AlertHandler (1);
//}    

#if INCLUDE_POWER_FAULT_HANDLING
/**************************************************************/
uint8_t dsPIC_HandlePowerFault(uint8_t u8PortNum, uint8_t u8PwrFaultSts)
{
  	UINT8 u8VBUSMatch, u8Faultcleared = 0, u8Return = DPM_HANDLE_PWR_FAULT;
    if (PD_ROLE_SOURCE == (gasPortConfigurationData[u8PortNum].u32CfgData & TYPEC_PORT_TYPE_MASK))
    {
        if((DPM_POWER_FAULT_UV & u8PwrFaultSts) || (DPM_POWER_FAULT_OVP & u8PwrFaultSts))
		{
            LOG_PRINT2(LOG_DEBUG,"FAULT Port %d 0x%02X\r\n", u8PortNum, u8PwrFaultSts);
			/* Read the VBUS Match */
			UPD_RegisterRead (u8PortNum, TYPEC_VBUS_MATCH, &u8VBUSMatch, BYTE_LEN_1);	
			if ((!(TYPEC_VBUS_MATCH_OVER_V & u8VBUSMatch)) && (DPM_POWER_FAULT_OVP & u8PwrFaultSts))
			{
			  	u8Faultcleared  = DPM_POWER_FAULT_OVP;
			}
			
			if(((u8VBUSMatch == TYPEC_VBUS_MATCH_DESIRED_V) || (u8VBUSMatch == TYPEC_VBUS_MATCH_DESIRED_N_UNDER_V))
			   			&& (DPM_POWER_FAULT_UV & u8PwrFaultSts))
			{
			  	u8Faultcleared  = DPM_POWER_FAULT_UV;
			}
			
			if (u8Faultcleared)
			{
			  	/* set return value false, Power fault will not be handled*/
			  	u8Return = DPM_NEGLECT_PWR_FAULT;
				/*ISR flag is cleared by disabling the interrupt*/
				CONFIG_HOOK_DISABLE_GLOBAL_INTERRUPT();
				gasDPM[u8PortNum].u8PowerFaultISR &= ~u8Faultcleared;
				CONFIG_HOOK_ENABLE_GLOBAL_INTERRUPT();
			}
			else
			{
			  	/*Drive EN_VBUS low since power fault still persists*/
            	UPD_GPIOSetClearOutput(u8PortNum, UPD_PIO4, UPD_GPIO_CLEAR);
            
			}
		}
    }
	return u8Return;
}
#endif

void hook_policy_engine_pre_process(uint8_t u8PortNum, uint8_t *u8DataBuf, uint8_t u8SOPType, uint8_t u32Header)
{
    /* Run operations that occur before running the Policy Engine state machine */
    
}

uint8_t hook_pdo_request_post_process_valid(uint8_t port_num, uint16_t max_current, uint8_t pdo_requested)
{
    return (check_power_budget(port_num, max_current, pdo_requested));
}

void hook_notify_pd_events_cb(uint8_t port_num, uint8_t event)
{
    switch(event)
    {
        case TYPEC_DETACH_EVENT:
            /* if we get a detach event on a port, zero out the power used by the port */
            port_max_power[port_num] = 0;
            reset_port_pdos(port_num);
            break;
            
        default:
            break;
    }
}

uint16_t hook_function_get_temperature_in_c(void)
{
    // TODO: Get the actual temperature from the system
    // For now return 30C to keep the thermal management code happy
    return(30);
}

#if CONFIG_HOOK_DEBUG_MSG
// Debug hook functions

void hook_debug_print_string (char *str)
{
    DEBUG_print((char *)str);
}

void hook_debug_u8(uint8_t u8val)
{
    char temp_str[8];
    sprintf(temp_str, " 0x%02X ", u8val);
    DEBUG_print(temp_str);
}
void hook_debug_u16(uint16_t u16val)
{
    char temp_str[10];
    sprintf(temp_str, " 0x%04X ", u16val);
    DEBUG_print(temp_str);
}
void hook_debug_u32(uint32_t u32val)
{
    char temp_str[14];
    sprintf(temp_str, " 0x%08lX ", (uint32_t)u32val);
    DEBUG_print(temp_str);
}
void hook_debug_i32(int32_t i32val)
{
    char temp_str[15];
    sprintf(temp_str, " %ld ", i32val);
    DEBUG_print(temp_str);
}


#endif
