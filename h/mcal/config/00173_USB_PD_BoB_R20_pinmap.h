/* ***********************************************************************************************
 * File:        00173_USB_PD_BoB_R20_pinmap.h                                                             
 * Author:      M91406                                                                         
 * Comments:    Hardware abstraction layer device pinout descriptor                                
 * Board ID:    00173_USB_PD_BoB                                                                       
 * HW Revision: R20                                                                   
 * Date:        05/30/2019                                                                             
 * Build:       0017                                                                       
 *                                                                                                 
 * Description:                                                                                    
 * This is a header file template adding signal labels for the hardware abstraction layer          
 * In this example user defined signals are directly associated to specific device pins.           
 * These associations have been created using the MS Excel macro-based code generation tool        
 * MyBoard_RXX_pinout.xlsm located in the h/hal/config directory of the project.                   
 *                                                                                                 
 * Note:                                                                                           
 * This file is the junction point between hardware and microcontroller abstraction layer.         
 * To better separate them from each other (e.g. for supporting CPU cards in hardware platforms),  
 * generic signal labels may be used in these declarations, which can be used to associate MCU     
 * device pins in MCAL to signals defined in HAL.                                                  
 *                                                                                     
 * EXAMPLE OF BOTH USE CASES                                                           
 *                                                                                     
 * a) Direct pin assignment using ONE header file in HAL                               
 *                                                                                     
 *  File:       MyBoard_RXX_pinmap.h                                                   
 * -----------------------------------------------------------------------             
 *                                                                                     
 *              #define CLKOUT  _LATB1                                                 
 *                                                                                     
 * Any usage of the label CLKOUT in user code will automatically be mapped to the      
 * specific device pin RB1. Thus board hardware and MCU itself become independent,     
 * exchangeable elements in the firmware and pin-out changes made won't affect         
 * the rest of the firmware.                                                           
 *                                                                                     
 * However, although this assignment simplifies the hardware abstraction, HAL and MCAL 
 * are not clearly separated as MCU specific registers are assigned here.              
 *                                                                                     
 *                                                                                     
 * b) Indirect pin assignment using TWO header files in HAL and MCAL                   
 *          
 *  File:       MyBoard_RXX_pinmap.h            MyController_pinmap.h                  
 * -----------------------------------------------------------------------             
 *          
 *              #define CLKOUT  TP08            #define TP08    _LATB1                 
 *     
 * Any usage of the label CLKOUT in user code will automatically be mapped to the          
 * specific device pin RB1. Thus board hardware, MCU adapter card and MCU itself become    
 * independent, exchangeable elements in the firmware and changes made here won't affect   
 * the rest of the firmware.                                                           
 *                                                                                     
 * This functional assignment scheme clearly separates HAL and MCAL, but adds more complexity  
 * to the structure. This scheme works best when working with CPU adapter cards like   
 * Microchip's Digital Power Plug-In Modules.                                          
 *                                                                                     
 *                                                                                     
 * ***********************************************************************************************/    
// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef __00173_USB_PD_BoB_R20_PINMAP_H__
#define __00173_USB_PD_BoB_R20_PINMAP_H__

#include <xc.h> // include processor files - each processor file is guarded 
#include <stdint.h> // Include standard integer types                       
#include <stdbool.h> // Include standard boolean types                      
#include "mcal/mcal.h" // Include local mcal layer header file        

/* @@PINMAP_VERSION
 * ***********************************************************************************************
 * Description:
 * This flag is a user defined flag helping to provide version information about the
 * pinmap file. This string can be used universally across the firmware to identify the
 * hardware version this firmware was written for.
 *
 * Please Note:
 * This label is not connected to the generic macro specified in the compiler settings
 * and need to maintained by the designer independently.
 * ***********************************************************************************************/

#define PINMAP_VERSION  "R20"

/* ***********************************************************************************************/

// Generated Content: Generic defines used to map device pins to board signals
#ifndef PINDIR_INPUT
    #define PINDIR_INPUT 1
#endif
#ifndef PINDIR_OUTPUT
    #define PINDIR_OUTPUT 0
#endif

#ifndef PINSTATE_HIGH
    #define PINSTATE_HIGH 1
#endif
#ifndef PINSTATE_LOW
    #define PINSTATE_LOW 0
#endif

#ifndef PINCFG_OPEN_DRAIN
    #define PINCFG_OPEN_DRAIN 1
#endif
#ifndef PINCFG_PUSH_PULL
    #define PINCFG_PUSH_PULL 0
#endif
#ifndef PINFUN_ANALOG
    #define PINFUN_ANALOG 1
#endif
#ifndef PINFUN_DIGITAL
    #define PINFUN_DIGITAL 0
#endif

#ifndef LED_ON
    #define LED_ON 0
#endif
#ifndef LED_OFF
    #define LED_OFF 1
#endif

// Device Pin #1 is RB14
#define BUCKH2_TRIS    TRISBbits.TRISB14 // GPIO direction register bit
#define BUCKH2_WR      LATBbits.LATB14 // GPIO port latch register bit
#define BUCKH2_RD      PORTBbits.RB14 // GPIO port register bit
#define BUCKH2_ODC     ODCBbits.ODCB14 // GPIO port open drain configuration register bit
#define BUCKH2_CNPU    CNPUBbits.CNPUB14 // GPIO port pull-up resistor register bit
#define BUCKH2_CNPD    CNPDBbits.CNPDB14 // GPIO port pull-down resistor register bit
#define BUCKH2_CNEN0   CNEN0Bbits.CNEN0B14 // GPIO port change notification Enable register bit
#define BUCKH2_CNSTAT  CNSTATBbits.CNSTATB14 // GPIO port change notification Status register bit
#define BUCKH2_CNEN1   CNEN1Bbits.CNEN1B14 // GPIO port change notification Edge Select Enable register bit
#define BUCKH2_CNF     CNFBbits.CNFB14 // GPIO port change notification flag bit register bit
#define BUCKH2_RP      46 // Number of Remappable Pin
#define BUCKH2_SET     { asm volatile ("bset _LATB, #14 \n"); }
#define BUCKH2_CLEAR   { asm volatile ("bclr _LATB, #14 \n"); }
#define BUCKH2_TOGGLE  { asm volatile ("btg  _LATB, #14 \n"); }
#define BUCKH2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BUCKH2_INIT_OUTPUT  {BUCKH2_WR = PINSTATE_LOW; BUCKH2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BUCKH2_INIT_INPUT   {BUCKH2_WR = PINSTATE_HIGH; BUCKH2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BUCKH2_PGx_CHANNEL  1 // PWM channel index
#define BUCKH2_PGx_PER      PG1PER // PWM channel period register
#define BUCKH2_PGx_PHASE    PG1PHASE // PWM channel phase register
#define BUCKH2_PGx_DC       PG1DC // PWM channel duty cycle register
#define BUCKH2_PGx_DCA      PG1DCA// PWM channel duty cycle A register
#define BUCKH2_PGx_DTH      PG1DTH // PWM channel rising edge dead time register
#define BUCKH2_PGx_DTL      PG1DTL // PWM channel falling edge dead time register
#define BUCKH2_PGx_OVRENH   PG1IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define BUCKH2_PGx_PENH     PG1IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define BUCKH2_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define BUCKH2_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define BUCKH2_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define BUCKH2_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register
#define BUCKH2_PWM_IF       _PWM1IF // interrupt flag bit
#define BUCKH2_PWM_IE       _PWM1IE // interrupt enable bit
#define BUCKH2_PWM_IP       _PWM1IP // interrupt priority register value (0-7) for this analog input
#define _BUCKH2_PWM_Interrupt _PWM1Interrupt // Interrupt Service Routine name declaration

// ToDo: User defined settings need to be incorporated into code generator
#define BUCKH2_ADC_TRGSRC_1 0b00100 //ADTRIGx_TRGSRC_PWM1_TRIG1
#define BUCKH2_ADC_TRGSRC_2 0b00101 //ADTRIGx_TRGSRC_PWM1_TRIG2

// Device Pin #2 is RB15
#define BUCKL2_TRIS    TRISBbits.TRISB15 // GPIO direction register bit
#define BUCKL2_WR      LATBbits.LATB15 // GPIO port latch register bit
#define BUCKL2_RD      PORTBbits.RB15 // GPIO port register bit
#define BUCKL2_ODC     ODCBbits.ODCB15 // GPIO port open drain configuration register bit
#define BUCKL2_CNPU    CNPUBbits.CNPUB15 // GPIO port pull-up resistor register bit
#define BUCKL2_CNPD    CNPDBbits.CNPDB15 // GPIO port pull-down resistor register bit
#define BUCKL2_CNEN0   CNEN0Bbits.CNEN0B15 // GPIO port change notification Enable register bit
#define BUCKL2_CNSTAT  CNSTATBbits.CNSTATB15 // GPIO port change notification Status register bit
#define BUCKL2_CNEN1   CNEN1Bbits.CNEN1B15 // GPIO port change notification Edge Select Enable register bit
#define BUCKL2_CNF     CNFBbits.CNFB15 // GPIO port change notification flag bit register bit
#define BUCKL2_RP      47 // Number of Remappable Pin
#define BUCKL2_SET     { asm volatile ("bset _LATB, #15 \n"); }
#define BUCKL2_CLEAR   { asm volatile ("bclr _LATB, #15 \n"); }
#define BUCKL2_TOGGLE  { asm volatile ("btg  _LATB, #15 \n"); }
#define BUCKL2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BUCKL2_INIT_OUTPUT  {BUCKL2_WR = PINSTATE_LOW; BUCKL2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BUCKL2_INIT_INPUT   {BUCKL2_WR = PINSTATE_HIGH; BUCKL2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BUCKL2_PGx_CHANNEL  1 // PWM channel index
#define BUCKL2_PGx_PER      PG1PER // PWM channel period register
#define BUCKL2_PGx_PHASE    PG1PHASE // PWM channel phase register
#define BUCKL2_PGx_DC       PG1DC // PWM channel duty cycle register
#define BUCKL2_PGx_DCA      PG1DCA// PWM channel duty cycle A register
#define BUCKL2_PGx_DTH      PG1DTH // PWM channel rising edge dead time register
#define BUCKL2_PGx_DTL      PG1DTL // PWM channel falling edge dead time register
#define BUCKL2_PGx_OVRENL   PG1IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define BUCKL2_PGx_PENL     PG1IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define BUCKL2_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define BUCKL2_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define BUCKL2_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define BUCKL2_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register

// Device Pin #3 is RC12
#define HUB_RST_TRIS    TRISCbits.TRISC12 // GPIO direction register bit
#define HUB_RST_WR      LATCbits.LATC12 // GPIO port latch register bit
#define HUB_RST_RD      PORTCbits.RC12 // GPIO port register bit
#define HUB_RST_ODC     ODCCbits.ODCC12 // GPIO port open drain configuration register bit
#define HUB_RST_CNPU    CNPUCbits.CNPUC12 // GPIO port pull-up resistor register bit
#define HUB_RST_CNPD    CNPDCbits.CNPDC12 // GPIO port pull-down resistor register bit
#define HUB_RST_CNEN0   CNEN0Cbits.CNEN0C12 // GPIO port change notification Enable register bit
#define HUB_RST_CNSTAT  CNSTATCbits.CNSTATC12 // GPIO port change notification Status register bit
#define HUB_RST_CNEN1   CNEN1Cbits.CNEN1C12 // GPIO port change notification Edge Select Enable register bit
#define HUB_RST_CNF     CNFCbits.CNFC12 // GPIO port change notification flag bit register bit
#define HUB_RST_RP      60 // Number of Remappable Pin
#define HUB_RST_SET     { asm volatile ("bset _LATC, #12 \n"); }
#define HUB_RST_CLEAR   { asm volatile ("bclr _LATC, #12 \n"); }
#define HUB_RST_TOGGLE  { asm volatile ("btg  _LATC, #12 \n"); }
#define HUB_RST_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define HUB_RST_INIT_OUTPUT  {HUB_RST_WR = PINSTATE_LOW; HUB_RST_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define HUB_RST_INIT_INPUT   {HUB_RST_WR = PINSTATE_HIGH; HUB_RST_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define HUB_RST_PGx_CHANNEL  8 // PWM channel index
#define HUB_RST_PGx_PER      PG8PER // PWM channel period register
#define HUB_RST_PGx_PHASE    PG8PHASE // PWM channel phase register
#define HUB_RST_PGx_DC       PG8DC // PWM channel duty cycle register
#define HUB_RST_PGx_DCA      PG8DCA// PWM channel duty cycle A register
#define HUB_RST_PGx_DTH      PG8DTH // PWM channel rising edge dead time register
#define HUB_RST_PGx_DTL      PG8DTL // PWM channel falling edge dead time register
#define HUB_RST_PGx_OVRENH   PG8IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define HUB_RST_PGx_PENH     PG8IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define HUB_RST_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define HUB_RST_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define HUB_RST_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define HUB_RST_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register
#define HUB_RST_PWM_IF       _PWM8IF // interrupt flag bit
#define HUB_RST_PWM_IE       _PWM8IE // interrupt enable bit
#define HUB_RST_PWM_IP       _PWM8IP // interrupt priority register value (0-7) for this analog input
#define _HUB_RST_PWM_Interrupt _PWM8Interrupt // Interrupt Service Routine name declaration

// Device Pin #4 is RC13
#define HUB_PRTPWR2_TRIS    TRISCbits.TRISC13 // GPIO direction register bit
#define HUB_PRTPWR2_WR      LATCbits.LATC13 // GPIO port latch register bit
#define HUB_PRTPWR2_RD      PORTCbits.RC13 // GPIO port register bit
#define HUB_PRTPWR2_ODC     ODCCbits.ODCC13 // GPIO port open drain configuration register bit
#define HUB_PRTPWR2_CNPU    CNPUCbits.CNPUC13 // GPIO port pull-up resistor register bit
#define HUB_PRTPWR2_CNPD    CNPDCbits.CNPDC13 // GPIO port pull-down resistor register bit
#define HUB_PRTPWR2_CNEN0   CNEN0Cbits.CNEN0C13 // GPIO port change notification Enable register bit
#define HUB_PRTPWR2_CNSTAT  CNSTATCbits.CNSTATC13 // GPIO port change notification Status register bit
#define HUB_PRTPWR2_CNEN1   CNEN1Cbits.CNEN1C13 // GPIO port change notification Edge Select Enable register bit
#define HUB_PRTPWR2_CNF     CNFCbits.CNFC13 // GPIO port change notification flag bit register bit
#define HUB_PRTPWR2_RP      61 // Number of Remappable Pin
#define HUB_PRTPWR2_SET     { asm volatile ("bset _LATC, #13 \n"); }
#define HUB_PRTPWR2_CLEAR   { asm volatile ("bclr _LATC, #13 \n"); }
#define HUB_PRTPWR2_TOGGLE  { asm volatile ("btg  _LATC, #13 \n"); }
#define HUB_PRTPWR2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define HUB_PRTPWR2_INIT_OUTPUT  {HUB_PRTPWR2_WR = PINSTATE_LOW; HUB_PRTPWR2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define HUB_PRTPWR2_INIT_INPUT   {HUB_PRTPWR2_WR = PINSTATE_HIGH; HUB_PRTPWR2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define HUB_PRTPWR2_PGx_CHANNEL  8 // PWM channel index
#define HUB_PRTPWR2_PGx_PER      PG8PER // PWM channel period register
#define HUB_PRTPWR2_PGx_PHASE    PG8PHASE // PWM channel phase register
#define HUB_PRTPWR2_PGx_DC       PG8DC // PWM channel duty cycle register
#define HUB_PRTPWR2_PGx_DCA      PG8DCA// PWM channel duty cycle A register
#define HUB_PRTPWR2_PGx_DTH      PG8DTH // PWM channel rising edge dead time register
#define HUB_PRTPWR2_PGx_DTL      PG8DTL // PWM channel falling edge dead time register
#define HUB_PRTPWR2_PGx_OVRENL   PG8IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define HUB_PRTPWR2_PGx_PENL     PG8IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define HUB_PRTPWR2_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define HUB_PRTPWR2_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define HUB_PRTPWR2_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define HUB_PRTPWR2_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register

// Device Pin #5 is MCLR

// Device Pin #6 is RD13
#define SPI_CS2_TRIS    TRISDbits.TRISD13 // GPIO direction register bit
#define SPI_CS2_WR      LATDbits.LATD13 // GPIO port latch register bit
#define SPI_CS2_RD      PORTDbits.RD13 // GPIO port register bit
#define SPI_CS2_ODC     ODCDbits.ODCD13 // GPIO port open drain configuration register bit
#define SPI_CS2_CNPU    CNPUDbits.CNPUD13 // GPIO port pull-up resistor register bit
#define SPI_CS2_CNPD    CNPDDbits.CNPDD13 // GPIO port pull-down resistor register bit
#define SPI_CS2_CNEN0   CNEN0Dbits.CNEN0D13 // GPIO port change notification Enable register bit
#define SPI_CS2_CNSTAT  CNSTATDbits.CNSTATD13 // GPIO port change notification Status register bit
#define SPI_CS2_CNEN1   CNEN1Dbits.CNEN1D13 // GPIO port change notification Edge Select Enable register bit
#define SPI_CS2_CNF     CNFDbits.CNFD13 // GPIO port change notification flag bit register bit
#define SPI_CS2_RP      77 // Number of Remappable Pin
#define SPI_CS2_SET     { asm volatile ("bset _LATD, #13 \n"); }
#define SPI_CS2_CLEAR   { asm volatile ("bclr _LATD, #13 \n"); }
#define SPI_CS2_TOGGLE  { asm volatile ("btg  _LATD, #13 \n"); }
#define SPI_CS2_IS_ANALOG_INPUT false // Pin is/is not analog input 
#define SPI_CS2_INIT_OUTPUT  {SPI_CS2_WR = PINSTATE_LOW; SPI_CS2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SPI_CS2_INIT_INPUT   {SPI_CS2_WR = PINSTATE_HIGH; SPI_CS2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #7 is RC0
#define PPC_IRQ2_TRIS    TRISCbits.TRISC0 // GPIO direction register bit
#define PPC_IRQ2_WR      LATCbits.LATC0 // GPIO port latch register bit
#define PPC_IRQ2_RD      PORTCbits.RC0 // GPIO port register bit
#define PPC_IRQ2_ODC     ODCCbits.ODCC0 // GPIO port open drain configuration register bit
#define PPC_IRQ2_CNPU    CNPUCbits.CNPUC0 // GPIO port pull-up resistor register bit
#define PPC_IRQ2_CNPD    CNPDCbits.CNPDC0 // GPIO port pull-down resistor register bit
#define PPC_IRQ2_CNEN0   CNEN0Cbits.CNEN0C0 // GPIO port change notification Enable register bit
#define PPC_IRQ2_CNSTAT  CNSTATCbits.CNSTATC0 // GPIO port change notification Status register bit
#define PPC_IRQ2_CNEN1   CNEN1Cbits.CNEN1C0 // GPIO port change notification Edge Select Enable register bit
#define PPC_IRQ2_CNF     CNFCbits.CNFC0 // GPIO port change notification flag bit register bit
#define PPC_IRQ2_RP      48 // Number of Remappable Pin
#define PPC_IRQ2_SET     { asm volatile ("bset _LATC, #0 \n"); }
#define PPC_IRQ2_CLEAR   { asm volatile ("bclr _LATC, #0 \n"); }
#define PPC_IRQ2_TOGGLE  { asm volatile ("btg  _LATC, #0 \n"); }
#define PPC_IRQ2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define PPC_IRQ2_ANSEL   _ANSELC0 // analog/digital pin configuration register bit
#define PPC_IRQ2_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define PPC_IRQ2_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define PPC_IRQ2_ADC_AN_INPUT 12   // ANx input pin number
#define PPC_IRQ2_ADCBUF  ADCBUF12 // ADC buffer register for this input
#define PPC_IRQ2_ADC_ANIE ADIEHbits.IE12
#define PPC_IRQ2_ADC_ANEIE ADEIEHbits.EIEN12
#define PPC_IRQ2_ADC_IF   _ADCAN12IF // interrupt flag bit
#define PPC_IRQ2_ADC_IE   _ADCAN12IE // interrupt enable bit
#define PPC_IRQ2_ADC_IP   _ADCAN12IP // interrupt priority register value (0-7) for this analog input
#define PPC_IRQ2_ADC_RDY  _AN12RDY // ADC buffer ready bit
#define _PPC_IRQ2_ADC_Interrupt _ADCAN12Interrupt
#define PPC_IRQ2_INIT_ANALOG	{PPC_IRQ2_ANSEL = 1; PPC_IRQ2_WR = PINSTATE_HIGH; PPC_IRQ2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define PPC_IRQ2_INIT_OUTPUT  {PPC_IRQ2_WR = PINSTATE_LOW; PPC_IRQ2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PPC_IRQ2_INIT_INPUT   {PPC_IRQ2_WR = PINSTATE_HIGH; PPC_IRQ2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #8 is RA0
#define FB_IIN2_TRIS    TRISAbits.TRISA0 // GPIO direction register bit
#define FB_IIN2_WR      LATAbits.LATA0 // GPIO port latch register bit
#define FB_IIN2_RD      PORTAbits.RA0 // GPIO port register bit
#define FB_IIN2_ODC     ODCAbits.ODCA0 // GPIO port open drain configuration register bit
#define FB_IIN2_CNPU    CNPUAbits.CNPUA0 // GPIO port pull-up resistor register bit
#define FB_IIN2_CNPD    CNPDAbits.CNPDA0 // GPIO port pull-down resistor register bit
#define FB_IIN2_CNEN0   CNEN0Abits.CNEN0A0 // GPIO port change notification Enable register bit
#define FB_IIN2_CNSTAT  CNSTATAbits.CNSTATA0 // GPIO port change notification Status register bit
#define FB_IIN2_CNEN1   CNEN1Abits.CNEN1A0 // GPIO port change notification Edge Select Enable register bit
#define FB_IIN2_CNF     CNFAbits.CNFA0 // GPIO port change notification flag bit register bit
#define FB_IIN2_SET     { asm volatile ("bset _LATA, #0 \n"); }
#define FB_IIN2_CLEAR   { asm volatile ("bclr _LATA, #0 \n"); }
#define FB_IIN2_TOGGLE  { asm volatile ("btg  _LATA, #0 \n"); }
#define FB_IIN2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_IIN2_ANSEL   _ANSELA0 // analog/digital pin configuration register bit
#define FB_IIN2_ADCCORE 0 // index starts from zero, last index indicated shared adC core
#define FB_IIN2_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define FB_IIN2_ADC_AN_INPUT 0   // ANx input pin number
#define FB_IIN2_ADCBUF  ADCBUF0 // ADC buffer register for this input
#define FB_IIN2_ADC_ANIE ADIELbits.IE0
#define FB_IIN2_ADC_ANEIE ADEIELbits.EIEN0
#define FB_IIN2_ADC_IF   _ADCAN0IF // interrupt flag bit
#define FB_IIN2_ADC_IE   _ADCAN0IE // interrupt enable bit
#define FB_IIN2_ADC_IP   _ADCAN0IP // interrupt priority register value (0-7) for this analog input
#define FB_IIN2_ADC_RDY  _AN0RDY // ADC buffer ready bit
#define _FB_IIN2_ADC_Interrupt _ADCAN0Interrupt
#define FB_IIN2_INIT_ANALOG	 {FB_IIN2_ANSEL = 1; FB_IIN2_WR = PINSTATE_HIGH; FB_IIN2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_IIN2_INIT_OUTPUT  {FB_IIN2_WR = PINSTATE_LOW; FB_IIN2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_IIN2_INIT_INPUT   {FB_IIN2_WR = PINSTATE_HIGH; FB_IIN2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #9 is RA1
#define PPC_RST2_TRIS    TRISAbits.TRISA1 // GPIO direction register bit
#define PPC_RST2_WR      LATAbits.LATA1 // GPIO port latch register bit
#define PPC_RST2_RD      PORTAbits.RA1 // GPIO port register bit
#define PPC_RST2_ODC     ODCAbits.ODCA1 // GPIO port open drain configuration register bit
#define PPC_RST2_CNPU    CNPUAbits.CNPUA1 // GPIO port pull-up resistor register bit
#define PPC_RST2_CNPD    CNPDAbits.CNPDA1 // GPIO port pull-down resistor register bit
#define PPC_RST2_CNEN0   CNEN0Abits.CNEN0A1 // GPIO port change notification Enable register bit
#define PPC_RST2_CNSTAT  CNSTATAbits.CNSTATA1 // GPIO port change notification Status register bit
#define PPC_RST2_CNEN1   CNEN1Abits.CNEN1A1 // GPIO port change notification Edge Select Enable register bit
#define PPC_RST2_CNF     CNFAbits.CNFA1 // GPIO port change notification flag bit register bit
#define PPC_RST2_SET     { asm volatile ("bset _LATA, #1 \n"); }
#define PPC_RST2_CLEAR   { asm volatile ("bclr _LATA, #1 \n"); }
#define PPC_RST2_TOGGLE  { asm volatile ("btg  _LATA, #1 \n"); }
#define PPC_RST2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define PPC_RST2_ANSEL   _ANSELA1 // analog/digital pin configuration register bit
#define PPC_RST2_ADCCORE 1 // index starts from zero, last index indicated shared adC core
#define PPC_RST2_IS_ANALOG_INPUT true // AN input is routed to a dedicated or shared ACD core
#define PPC_RST2_ADC_AN_INPUT 1   // ANx input pin number
#define PPC_RST2_ADCBUF  ADCBUF1 // ADC buffer register for this input
#define PPC_RST2_ADC_ANIE ADIEHbits.IE1
#define PPC_RST2_ADC_ANEIE ADEIEHbits.EIEN1
#define PPC_RST2_ADC_IF   _ADCAN1IF // interrupt flag bit
#define PPC_RST2_ADC_IE   _ADCAN1IE // interrupt enable bit
#define PPC_RST2_ADC_IP   _ADCAN1IP // interrupt priority register value (0-7) for this analog input
#define PPC_RST2_ADC_RDY  _AN1RDY // ADC buffer ready bit
#define _PPC_RST2_ADC_Interrupt _ADCAN1Interrupt
#define PPC_RST2_INIT_ANALOG  {PPC_RST2_ANSEL = 1; PPC_RST2_WR = PINSTATE_HIGH; PPC_RST2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define PPC_RST2_INIT_OUTPUT  {PPC_RST2_WR = PINSTATE_LOW; PPC_RST2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PPC_RST2_INIT_INPUT   {PPC_RST2_WR = PINSTATE_HIGH; PPC_RST2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #10 is RA2
#define FB_IOUT2_TRIS    TRISAbits.TRISA2 // GPIO direction register bit
#define FB_IOUT2_WR      LATAbits.LATA2 // GPIO port latch register bit
#define FB_IOUT2_RD      PORTAbits.RA2 // GPIO port register bit
#define FB_IOUT2_ODC     ODCAbits.ODCA2 // GPIO port open drain configuration register bit
#define FB_IOUT2_CNPU    CNPUAbits.CNPUA2 // GPIO port pull-up resistor register bit
#define FB_IOUT2_CNPD    CNPDAbits.CNPDA2 // GPIO port pull-down resistor register bit
#define FB_IOUT2_CNEN0   CNEN0Abits.CNEN0A2 // GPIO port change notification Enable register bit
#define FB_IOUT2_CNSTAT  CNSTATAbits.CNSTATA2 // GPIO port change notification Status register bit
#define FB_IOUT2_CNEN1   CNEN1Abits.CNEN1A2 // GPIO port change notification Edge Select Enable register bit
#define FB_IOUT2_CNF     CNFAbits.CNFA2 // GPIO port change notification flag bit register bit
#define FB_IOUT2_SET     { asm volatile ("bset _LATA, #2 \n"); }
#define FB_IOUT2_CLEAR   { asm volatile ("bclr _LATA, #2 \n"); }
#define FB_IOUT2_TOGGLE  { asm volatile ("btg  _LATA, #2 \n"); }
#define FB_IOUT2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_IOUT2_ANSEL   _ANSELA2 // analog/digital pin configuration register bit
#define FB_IOUT2_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_IOUT2_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_IOUT2_ADC_AN_INPUT 9   // ANx input pin number
#define FB_IOUT2_ADCBUF  ADCBUF9 // ADC buffer register for this input
#define FB_IOUT2_ADC_ANIE ADIELbits.IE9
#define FB_IOUT2_ADC_ANEIE ADEIELbits.EIEN9
#define FB_IOUT2_ADC_IF   _ADCAN9IF // interrupt flag bit
#define FB_IOUT2_ADC_IE   _ADCAN9IE // interrupt enable bit
#define FB_IOUT2_ADC_IP   _ADCAN9IP // interrupt priority register value (0-7) for this analog input
#define FB_IOUT2_ADC_RDY  _AN9RDY // ADC buffer ready bit
#define _FB_IOUT2_ADC_Interrupt _ADCAN9Interrupt
#define FB_IOUT2_INIT_ANALOG	{FB_IOUT2_ANSEL = 1; FB_IOUT2_WR = PINSTATE_HIGH; FB_IOUT2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_IOUT2_INIT_OUTPUT  {FB_IOUT2_WR = PINSTATE_LOW; FB_IOUT2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_IOUT2_INIT_INPUT   {FB_IOUT2_WR = PINSTATE_HIGH; FB_IOUT2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #11 is RA3
#define TESTPOINT_TRIS    TRISAbits.TRISA3 // GPIO direction register bit
#define TESTPOINT_WR      LATAbits.LATA3 // GPIO port latch register bit
#define TESTPOINT_RD      PORTAbits.RA3 // GPIO port register bit
#define TESTPOINT_ODC     ODCAbits.ODCA3 // GPIO port open drain configuration register bit
#define TESTPOINT_CNPU    CNPUAbits.CNPUA3 // GPIO port pull-up resistor register bit
#define TESTPOINT_CNPD    CNPDAbits.CNPDA3 // GPIO port pull-down resistor register bit
#define TESTPOINT_CNEN0   CNEN0Abits.CNEN0A3 // GPIO port change notification Enable register bit
#define TESTPOINT_CNSTAT  CNSTATAbits.CNSTATA3 // GPIO port change notification Status register bit
#define TESTPOINT_CNEN1   CNEN1Abits.CNEN1A3 // GPIO port change notification Edge Select Enable register bit
#define TESTPOINT_CNF     CNFAbits.CNFA3 // GPIO port change notification flag bit register bit
#define TESTPOINT_SET     { asm volatile ("bset _LATA, #3 \n"); }
#define TESTPOINT_CLEAR   { asm volatile ("bclr _LATA, #3 \n"); }
#define TESTPOINT_TOGGLE  { asm volatile ("btg  _LATA, #3 \n"); }
#define TESTPOINT_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define TESTPOINT_ANSEL   _ANSELA3 // analog/digital pin configuration register bit
#define TESTPOINT_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define TESTPOINT_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define TESTPOINT_ADC_AN_INPUT 3   // ANx input pin number
#define TESTPOINT_ADCBUF  ADCBUF3 // ADC buffer register for this input
#define TESTPOINT_ADC_ANIE ADIELbits.IE3
#define TESTPOINT_ADC_ANEIE ADEIELbits.EIEN3
#define TESTPOINT_ADC_IF   _ADCAN3IF // interrupt flag bit
#define TESTPOINT_ADC_IE   _ADCAN3IE // interrupt enable bit
#define TESTPOINT_ADC_IP   _ADCAN3IP // interrupt priority register value (0-7) for this analog input
#define TESTPOINT_ADC_RDY  _AN3RDY // ADC buffer ready bit
#define _TESTPOINT_ADC_Interrupt _ADCAN3Interrupt
#define TESTPOINT_INIT_ANALOG	{TESTPOINT_ANSEL = 1; TESTPOINT_WR = PINSTATE_HIGH; TESTPOINT_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define TESTPOINT_INIT_OUTPUT  {TESTPOINT_WR = PINSTATE_LOW; TESTPOINT_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define TESTPOINT_INIT_INPUT   {TESTPOINT_WR = PINSTATE_HIGH; TESTPOINT_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #12 is RA4
#define FB_VOUT2_TRIS    TRISAbits.TRISA4 // GPIO direction register bit
#define FB_VOUT2_WR      LATAbits.LATA4 // GPIO port latch register bit
#define FB_VOUT2_RD      PORTAbits.RA4 // GPIO port register bit
#define FB_VOUT2_ODC     ODCAbits.ODCA4 // GPIO port open drain configuration register bit
#define FB_VOUT2_CNPU    CNPUAbits.CNPUA4 // GPIO port pull-up resistor register bit
#define FB_VOUT2_CNPD    CNPDAbits.CNPDA4 // GPIO port pull-down resistor register bit
#define FB_VOUT2_CNEN0   CNEN0Abits.CNEN0A4 // GPIO port change notification Enable register bit
#define FB_VOUT2_CNSTAT  CNSTATAbits.CNSTATA4 // GPIO port change notification Status register bit
#define FB_VOUT2_CNEN1   CNEN1Abits.CNEN1A4 // GPIO port change notification Edge Select Enable register bit
#define FB_VOUT2_CNF     CNFAbits.CNFA4 // GPIO port change notification flag bit register bit
#define FB_VOUT2_SET     { asm volatile ("bset _LATA, #4 \n"); }
#define FB_VOUT2_CLEAR   { asm volatile ("bclr _LATA, #4 \n"); }
#define FB_VOUT2_TOGGLE  { asm volatile ("btg  _LATA, #4 \n"); }
#define FB_VOUT2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_VOUT2_ANSEL   _ANSELA4 // analog/digital pin configuration register bit
#define FB_VOUT2_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_VOUT2_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_VOUT2_ADC_AN_INPUT 4   // ANx input pin number
#define FB_VOUT2_ADCBUF  ADCBUF4 // ADC buffer register for this input
#define FB_VOUT2_ADC_ANIE ADIELbits.IE4
#define FB_VOUT2_ADC_ANEIE ADEIELbits.EIEN4
#define FB_VOUT2_ADC_IF   _ADCAN4IF // interrupt flag bit
#define FB_VOUT2_ADC_IE   _ADCAN4IE // interrupt enable bit
#define FB_VOUT2_ADC_IP   _ADCAN4IP // interrupt priority register value (0-7) for this analog input
#define FB_VOUT2_ADC_RDY  _AN4RDY // ADC buffer ready bit
#define _FB_VOUT2_ADC_Interrupt _ADCAN4Interrupt
#define FB_VOUT2_INIT_ANALOG	{FB_VOUT2_ANSEL = 1; FB_VOUT2_WR = PINSTATE_HIGH; FB_VOUT2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_VOUT2_INIT_OUTPUT  {FB_VOUT2_WR = PINSTATE_LOW; FB_VOUT2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_VOUT2_INIT_INPUT   {FB_VOUT2_WR = PINSTATE_HIGH; FB_VOUT2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #13 is AVDD

// Device Pin #14 is AVSS

// Device Pin #15 is RC1
#define UART_TX_TRIS    TRISCbits.TRISC1 // GPIO direction register bit
#define UART_TX_WR      LATCbits.LATC1 // GPIO port latch register bit
#define UART_TX_RD      PORTCbits.RC1 // GPIO port register bit
#define UART_TX_ODC     ODCCbits.ODCC1 // GPIO port open drain configuration register bit
#define UART_TX_CNPU    CNPUCbits.CNPUC1 // GPIO port pull-up resistor register bit
#define UART_TX_CNPD    CNPDCbits.CNPDC1 // GPIO port pull-down resistor register bit
#define UART_TX_CNEN0   CNEN0Cbits.CNEN0C1 // GPIO port change notification Enable register bit
#define UART_TX_CNSTAT  CNSTATCbits.CNSTATC1 // GPIO port change notification Status register bit
#define UART_TX_CNEN1   CNEN1Cbits.CNEN1C1 // GPIO port change notification Edge Select Enable register bit
#define UART_TX_CNF     CNFCbits.CNFC1 // GPIO port change notification flag bit register bit
#define UART_TX_RP      49 // Number of Remappable Pin
#define UART_TX_SET     { asm volatile ("bset _LATC, #1 \n"); }
#define UART_TX_CLEAR   { asm volatile ("bclr _LATC, #1 \n"); }
#define UART_TX_TOGGLE  { asm volatile ("btg  _LATC, #1 \n"); }
#define UART_TX_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define UART_TX_ANSEL   _ANSELC1 // analog/digital pin configuration register bit
#define UART_TX_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define UART_TX_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define UART_TX_ADC_AN_INPUT 13   // ANx input pin number
#define UART_TX_ADCBUF  ADCBUF13 // ADC buffer register for this input
#define UART_TX_ADC_ANIE ADIELbits.IE13
#define UART_TX_ADC_ANEIE ADEIELbits.EIEN13
#define UART_TX_ADC_IF   _ADCAN13IF // interrupt flag bit
#define UART_TX_ADC_IE   _ADCAN13IE // interrupt enable bit
#define UART_TX_ADC_IP   _ADCAN13IP // interrupt priority register value (0-7) for this analog input
#define UART_TX_ADC_RDY  _AN13RDY // ADC buffer ready bit
#define _UART_TX_ADC_Interrupt _ADCAN13Interrupt
#define UART_TX_INIT_ANALOG	{UART_TX_ANSEL = 1; UART_TX_WR = PINSTATE_HIGH; UART_TX_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define UART_TX_INIT_OUTPUT  {UART_TX_WR = PINSTATE_LOW; UART_TX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_TX_INIT_INPUT   {UART_TX_WR = PINSTATE_HIGH; UART_TX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #16 is RC2
#define UART_RX_TRIS    TRISCbits.TRISC2 // GPIO direction register bit
#define UART_RX_WR      LATCbits.LATC2 // GPIO port latch register bit
#define UART_RX_RD      PORTCbits.RC2 // GPIO port register bit
#define UART_RX_ODC     ODCCbits.ODCC2 // GPIO port open drain configuration register bit
#define UART_RX_CNPU    CNPUCbits.CNPUC2 // GPIO port pull-up resistor register bit
#define UART_RX_CNPD    CNPDCbits.CNPDC2 // GPIO port pull-down resistor register bit
#define UART_RX_CNEN0   CNEN0Cbits.CNEN0C2 // GPIO port change notification Enable register bit
#define UART_RX_CNSTAT  CNSTATCbits.CNSTATC2 // GPIO port change notification Status register bit
#define UART_RX_CNEN1   CNEN1Cbits.CNEN1C2 // GPIO port change notification Edge Select Enable register bit
#define UART_RX_CNF     CNFCbits.CNFC2 // GPIO port change notification flag bit register bit
#define UART_RX_RP      50 // Number of Remappable Pin
#define UART_RX_SET     { asm volatile ("bset _LATC, #2 \n"); }
#define UART_RX_CLEAR   { asm volatile ("bclr _LATC, #2 \n"); }
#define UART_RX_TOGGLE  { asm volatile ("btg  _LATC, #2 \n"); }
#define UART_RX_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define UART_RX_ANSEL   _ANSELC2 // analog/digital pin configuration register bit
#define UART_RX_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define UART_RX_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define UART_RX_ADC_AN_INPUT 14   // ANx input pin number
#define UART_RX_ADCBUF  ADCBUF14 // ADC buffer register for this input
#define UART_RX_ADC_ANIE ADIELbits.IE14
#define UART_RX_ADC_ANEIE ADEIELbits.EIEN14
#define UART_RX_ADC_IF   _ADCAN14IF // interrupt flag bit
#define UART_RX_ADC_IE   _ADCAN14IE // interrupt enable bit
#define UART_RX_ADC_IP   _ADCAN14IP // interrupt priority register value (0-7) for this analog input
#define UART_RX_ADC_RDY  _AN14RDY // ADC buffer ready bit
#define _UART_RX_ADC_Interrupt _ADCAN14Interrupt
#define UART_RX_INIT_ANALOG	{UART_RX_ANSEL = 1; UART_RX_WR = PINSTATE_HIGH; UART_RX_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define UART_RX_INIT_OUTPUT  {UART_RX_WR = PINSTATE_LOW; UART_RX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_RX_INIT_INPUT   {UART_RX_WR = PINSTATE_HIGH; UART_RX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #17 is RC6
#define FB_TEMP2_TRIS    TRISCbits.TRISC6 // GPIO direction register bit
#define FB_TEMP2_WR      LATCbits.LATC6 // GPIO port latch register bit
#define FB_TEMP2_RD      PORTCbits.RC6 // GPIO port register bit
#define FB_TEMP2_ODC     ODCCbits.ODCC6 // GPIO port open drain configuration register bit
#define FB_TEMP2_CNPU    CNPUCbits.CNPUC6 // GPIO port pull-up resistor register bit
#define FB_TEMP2_CNPD    CNPDCbits.CNPDC6 // GPIO port pull-down resistor register bit
#define FB_TEMP2_CNEN0   CNEN0Cbits.CNEN0C6 // GPIO port change notification Enable register bit
#define FB_TEMP2_CNSTAT  CNSTATCbits.CNSTATC6 // GPIO port change notification Status register bit
#define FB_TEMP2_CNEN1   CNEN1Cbits.CNEN1C6 // GPIO port change notification Edge Select Enable register bit
#define FB_TEMP2_CNF     CNFCbits.CNFC6 // GPIO port change notification flag bit register bit
#define FB_TEMP2_RP      54 // Number of Remappable Pin
#define FB_TEMP2_SET     { asm volatile ("bset _LATC, #6 \n"); }
#define FB_TEMP2_CLEAR   { asm volatile ("bclr _LATC, #6 \n"); }
#define FB_TEMP2_TOGGLE  { asm volatile ("btg  _LATC, #6 \n"); }
#define FB_TEMP2_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_TEMP2_ANSEL   _ANSELC6 // analog/digital pin configuration register bit
#define FB_TEMP2_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_TEMP2_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_TEMP2_ADC_AN_INPUT 17   // ANx input pin number
#define FB_TEMP2_ADCBUF  ADCBUF17 // ADC buffer register for this input
#define FB_TEMP2_ADC_ANIE ADIEHbits.IEN1
#define FB_TEMP2_ADC_ANEIE ADEIEHbits.EIENN1
#define FB_TEMP2_ADC_IF   _ADCAN17IF // interrupt flag bit
#define FB_TEMP2_ADC_IE   _ADCAN17IE // interrupt enable bit
#define FB_TEMP2_ADC_IP   _ADCAN17IP // interrupt priority register value (0-7) for this analog input
#define FB_TEMP2_ADC_RDY  _AN17RDY // ADC buffer ready bit
#define _FB_TEMP2_ADC_Interrupt _ADCAN17Interrupt
#define FB_TEMP2_INIT_ANALOG	{FB_TEMP2_ANSEL = 1; FB_TEMP2_WR = PINSTATE_HIGH; FB_TEMP2_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_TEMP2_INIT_OUTPUT  {FB_TEMP2_WR = PINSTATE_LOW; FB_TEMP2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_TEMP2_INIT_INPUT   {FB_TEMP2_WR = PINSTATE_HIGH; FB_TEMP2_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #18 is VDD

// Device Pin #19 is VSS

// Device Pin #20 is RC3
#define LED_AUX_CTRL_TRIS    TRISCbits.TRISC3 // GPIO direction register bit
#define LED_AUX_CTRL_WR      LATCbits.LATC3 // GPIO port latch register bit
#define LED_AUX_CTRL_RD      PORTCbits.RC3 // GPIO port register bit
#define LED_AUX_CTRL_ODC     ODCCbits.ODCC3 // GPIO port open drain configuration register bit
#define LED_AUX_CTRL_CNPU    CNPUCbits.CNPUC3 // GPIO port pull-up resistor register bit
#define LED_AUX_CTRL_CNPD    CNPDCbits.CNPDC3 // GPIO port pull-down resistor register bit
#define LED_AUX_CTRL_CNEN0   CNEN0Cbits.CNEN0C3 // GPIO port change notification Enable register bit
#define LED_AUX_CTRL_CNSTAT  CNSTATCbits.CNSTATC3 // GPIO port change notification Status register bit
#define LED_AUX_CTRL_CNEN1   CNEN1Cbits.CNEN1C3 // GPIO port change notification Edge Select Enable register bit
#define LED_AUX_CTRL_CNF     CNFCbits.CNFC3 // GPIO port change notification flag bit register bit
#define LED_AUX_CTRL_RP      51 // Number of Remappable Pin
#define LED_AUX_CTRL_SET     { asm volatile ("bset _LATC, #3 \n"); }
#define LED_AUX_CTRL_CLEAR   { asm volatile ("bclr _LATC, #3 \n"); }
#define LED_AUX_CTRL_TOGGLE  { asm volatile ("btg  _LATC, #3 \n"); }
#define LED_AUX_CTRL_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define LED_AUX_CTRL_ANSEL   _ANSELC3 // analog/digital pin configuration register bit
#define LED_AUX_CTRL_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define LED_AUX_CTRL_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define LED_AUX_CTRL_ADC_AN_INPUT 15   // ANx input pin number
#define LED_AUX_CTRL_ADCBUF  ADCBUF15 // ADC buffer register for this input
#define LED_AUX_CTRL_ADC_ANIE ADIELbits.IE15
#define LED_AUX_CTRL_ADC_ANEIE ADEIELbits.EIEN15
#define LED_AUX_CTRL_ADC_IF   _ADCAN15IF // interrupt flag bit
#define LED_AUX_CTRL_ADC_IE   _ADCAN15IE // interrupt enable bit
#define LED_AUX_CTRL_ADC_IP   _ADCAN15IP // interrupt priority register value (0-7) for this analog input
#define LED_AUX_CTRL_ADC_RDY  _AN15RDY // ADC buffer ready bit
#define _LED_AUX_CTRL_ADC_Interrupt _ADCAN15Interrupt
#define LED_AUX_CTRL_INIT_ANALOG	{LED_AUX_CTRL_ANSEL = 1; LED_AUX_CTRL_WR = PINSTATE_HIGH; LED_AUX_CTRL_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define LED_AUX_CTRL_INIT_OUTPUT  {LED_AUX_CTRL_WR = PINSTATE_LOW; LED_AUX_CTRL_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define LED_AUX_CTRL_INIT_INPUT   {LED_AUX_CTRL_WR = PINSTATE_HIGH; LED_AUX_CTRL_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #21 is RB0
#define FB_VBAT_TRIS    TRISBbits.TRISB0 // GPIO direction register bit
#define FB_VBAT_WR      LATBbits.LATB0 // GPIO port latch register bit
#define FB_VBAT_RD      PORTBbits.RB0 // GPIO port register bit
#define FB_VBAT_ODC     ODCBbits.ODCB0 // GPIO port open drain configuration register bit
#define FB_VBAT_CNPU    CNPUBbits.CNPUB0 // GPIO port pull-up resistor register bit
#define FB_VBAT_CNPD    CNPDBbits.CNPDB0 // GPIO port pull-down resistor register bit
#define FB_VBAT_CNEN0   CNEN0Bbits.CNEN0B0 // GPIO port change notification Enable register bit
#define FB_VBAT_CNSTAT  CNSTATBbits.CNSTATB0 // GPIO port change notification Status register bit
#define FB_VBAT_CNEN1   CNEN1Bbits.CNEN1B0 // GPIO port change notification Edge Select Enable register bit
#define FB_VBAT_CNF     CNFBbits.CNFB0 // GPIO port change notification flag bit register bit
#define FB_VBAT_RP      32 // Number of Remappable Pin
#define FB_VBAT_SET     { asm volatile ("bset _LATB, #0 \n"); }
#define FB_VBAT_CLEAR   { asm volatile ("bclr _LATB, #0 \n"); }
#define FB_VBAT_TOGGLE  { asm volatile ("btg  _LATB, #0 \n"); }
#define FB_VBAT_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_VBAT_ANSEL   _ANSELB0 // analog/digital pin configuration register bit
#define FB_VBAT_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_VBAT_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_VBAT_ADC_AN_INPUT 5   // ANx input pin number
#define FB_VBAT_ADCBUF  ADCBUF5 // ADC buffer register for this input
#define FB_VBAT_ADC_ANIE ADIELbits.IE5
#define FB_VBAT_ADC_ANEIE ADEIELbits.EIEN5
#define FB_VBAT_ADC_IF   _ADCAN5IF // interrupt flag bit
#define FB_VBAT_ADC_IE   _ADCAN5IE // interrupt enable bit
#define FB_VBAT_ADC_IP   _ADCAN5IP // interrupt priority register value (0-7) for this analog input
#define FB_VBAT_ADC_RDY  _AN5RDY // ADC buffer ready bit
#define _FB_VBAT_ADC_Interrupt _ADCAN5Interrupt
#define FB_VBAT_INIT_ANALOG	 {FB_VBAT_ANSEL = 1; FB_VBAT_WR = PINSTATE_HIGH; FB_VBAT_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_VBAT_INIT_OUTPUT  {FB_VBAT_WR = PINSTATE_LOW; FB_VBAT_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_VBAT_INIT_INPUT   {FB_VBAT_WR = PINSTATE_HIGH; FB_VBAT_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #22 is RB1
#define FB_TEMP1_TRIS    TRISBbits.TRISB1 // GPIO direction register bit
#define FB_TEMP1_WR      LATBbits.LATB1 // GPIO port latch register bit
#define FB_TEMP1_RD      PORTBbits.RB1 // GPIO port register bit
#define FB_TEMP1_ODC     ODCBbits.ODCB1 // GPIO port open drain configuration register bit
#define FB_TEMP1_CNPU    CNPUBbits.CNPUB1 // GPIO port pull-up resistor register bit
#define FB_TEMP1_CNPD    CNPDBbits.CNPDB1 // GPIO port pull-down resistor register bit
#define FB_TEMP1_CNEN0   CNEN0Bbits.CNEN0B1 // GPIO port change notification Enable register bit
#define FB_TEMP1_CNSTAT  CNSTATBbits.CNSTATB1 // GPIO port change notification Status register bit
#define FB_TEMP1_CNEN1   CNEN1Bbits.CNEN1B1 // GPIO port change notification Edge Select Enable register bit
#define FB_TEMP1_CNF     CNFBbits.CNFB1 // GPIO port change notification flag bit register bit
#define FB_TEMP1_RP      33 // Number of Remappable Pin
#define FB_TEMP1_SET     { asm volatile ("bset _LATB, #1 \n"); }
#define FB_TEMP1_CLEAR   { asm volatile ("bclr _LATB, #1 \n"); }
#define FB_TEMP1_TOGGLE  { asm volatile ("btg  _LATB, #1 \n"); }
#define FB_TEMP1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_TEMP1_ANSEL   _ANSELB1 // analog/digital pin configuration register bit
#define FB_TEMP1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_TEMP1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_TEMP1_ADC_AN_INPUT 6   // ANx input pin number
#define FB_TEMP1_ADCBUF  ADCBUF6 // ADC buffer register for this input
#define FB_TEMP1_ADC_ANIE ADIELbits.IE6
#define FB_TEMP1_ADC_ANEIE ADEIELbits.EIEN6
#define FB_TEMP1_ADC_IF   _ADCAN6IF // interrupt flag bit
#define FB_TEMP1_ADC_IE   _ADCAN6IE // interrupt enable bit
#define FB_TEMP1_ADC_IP   _ADCAN6IP // interrupt priority register value (0-7) for this analog input
#define FB_TEMP1_ADC_RDY  _AN6RDY // ADC buffer ready bit
#define _FB_TEMP1_ADC_Interrupt _ADCAN6Interrupt
#define FB_TEMP1_INIT_ANALOG	{FB_TEMP1_ANSEL = 1; FB_TEMP1_WR = PINSTATE_HIGH; FB_TEMP1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_TEMP1_INIT_OUTPUT  {FB_TEMP1_WR = PINSTATE_LOW; FB_TEMP1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_TEMP1_INIT_INPUT   {FB_TEMP1_WR = PINSTATE_HIGH; FB_TEMP1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #23 is RD10
#define FB_IOUT1_TRIS    TRISDbits.TRISD10 // GPIO direction register bit
#define FB_IOUT1_WR      LATDbits.LATD10 // GPIO port latch register bit
#define FB_IOUT1_RD      PORTDbits.RD10 // GPIO port register bit
#define FB_IOUT1_ODC     ODCDbits.ODCD10 // GPIO port open drain configuration register bit
#define FB_IOUT1_CNPU    CNPUDbits.CNPUD10 // GPIO port pull-up resistor register bit
#define FB_IOUT1_CNPD    CNPDDbits.CNPDD10 // GPIO port pull-down resistor register bit
#define FB_IOUT1_CNEN0   CNEN0Dbits.CNEN0D10 // GPIO port change notification Enable register bit
#define FB_IOUT1_CNSTAT  CNSTATDbits.CNSTATD10 // GPIO port change notification Status register bit
#define FB_IOUT1_CNEN1   CNEN1Dbits.CNEN1D10 // GPIO port change notification Edge Select Enable register bit
#define FB_IOUT1_CNF     CNFDbits.CNFD10 // GPIO port change notification flag bit register bit
#define FB_IOUT1_RP      74 // Number of Remappable Pin
#define FB_IOUT1_SET     { asm volatile ("bset _LATD, #10 \n"); }
#define FB_IOUT1_CLEAR   { asm volatile ("bclr _LATD, #10 \n"); }
#define FB_IOUT1_TOGGLE  { asm volatile ("btg  _LATD, #10 \n"); }
#define FB_IOUT1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_IOUT1_ANSEL   _ANSELD10 // analog/digital pin configuration register bit
#define FB_IOUT1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_IOUT1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_IOUT1_ADC_AN_INPUT 18   // ANx input pin number
#define FB_IOUT1_ADCBUF  ADCBUF18 // ADC buffer register for this input
#define FB_IOUT1_ADC_ANIE ADIEHbits.IE18
#define FB_IOUT1_ADC_ANEIE ADEIEHbits.EIEN18
#define FB_IOUT1_ADC_IF   _ADCAN18IF // interrupt flag bit
#define FB_IOUT1_ADC_IE   _ADCAN18IE // interrupt enable bit
#define FB_IOUT1_ADC_IP   _ADCAN18IP // interrupt priority register value (0-7) for this analog input
#define FB_IOUT1_ADC_RDY  _AN18RDY // ADC buffer ready bit
#define _FB_IOUT1_ADC_Interrupt _ADCAN18Interrupt
#define FB_IOUT1_INIT_ANALOG	{FB_IOUT1_ANSEL = 1; FB_IOUT1_WR = PINSTATE_HIGH; FB_IOUT1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_IOUT1_INIT_OUTPUT  {FB_IOUT1_WR = PINSTATE_LOW; FB_IOUT1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_IOUT1_INIT_INPUT   {FB_IOUT1_WR = PINSTATE_HIGH; FB_IOUT1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #24 is RC7
#define FB_VOUT1_TRIS    TRISCbits.TRISC7 // GPIO direction register bit
#define FB_VOUT1_WR      LATCbits.LATC7 // GPIO port latch register bit
#define FB_VOUT1_RD      PORTCbits.RC7 // GPIO port register bit
#define FB_VOUT1_ODC     ODCCbits.ODCC7 // GPIO port open drain configuration register bit
#define FB_VOUT1_CNPU    CNPUCbits.CNPUC7 // GPIO port pull-up resistor register bit
#define FB_VOUT1_CNPD    CNPDCbits.CNPDC7 // GPIO port pull-down resistor register bit
#define FB_VOUT1_CNEN0   CNEN0Cbits.CNEN0C7 // GPIO port change notification Enable register bit
#define FB_VOUT1_CNSTAT  CNSTATCbits.CNSTATC7 // GPIO port change notification Status register bit
#define FB_VOUT1_CNEN1   CNEN1Cbits.CNEN1C7 // GPIO port change notification Edge Select Enable register bit
#define FB_VOUT1_CNF     CNFCbits.CNFC7 // GPIO port change notification flag bit register bit
#define FB_VOUT1_RP      55 // Number of Remappable Pin
#define FB_VOUT1_SET     { asm volatile ("bset _LATC, #7 \n"); }
#define FB_VOUT1_CLEAR   { asm volatile ("bclr _LATC, #7 \n"); }
#define FB_VOUT1_TOGGLE  { asm volatile ("btg  _LATC, #7 \n"); }
#define FB_VOUT1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_VOUT1_ANSEL   _ANSELC7 // analog/digital pin configuration register bit
#define FB_VOUT1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define FB_VOUT1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define FB_VOUT1_ADC_AN_INPUT 16   // ANx input pin number
#define FB_VOUT1_ADCBUF  ADCBUF16 // ADC buffer register for this input
#define FB_VOUT1_ADC_ANIE ADIEHbits.IE16
#define FB_VOUT1_ADC_ANEIE ADEIEHbits.EIEN16
#define FB_VOUT1_ADC_IF   _ADCAN16IF // interrupt flag bit
#define FB_VOUT1_ADC_IE   _ADCAN16IE // interrupt enable bit
#define FB_VOUT1_ADC_IP   _ADCAN16IP // interrupt priority register value (0-7) register value (0-7) for this analog input
#define FB_VOUT1_ADC_RDY  _AN16RDY // ADC buffer ready bit
#define _FB_VOUT1_ADC_Interrupt _ADCAN16Interrupt
#define FB_VOUT1_INIT_ANALOG  {FB_VOUT1_ANSEL = 1; FB_VOUT1_WR = PINSTATE_HIGH; FB_VOUT1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_VOUT1_INIT_OUTPUT  {FB_VOUT1_WR = PINSTATE_LOW; FB_VOUT1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_VOUT1_INIT_INPUT   {FB_VOUT1_WR = PINSTATE_HIGH; FB_VOUT1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #25 is RB2
#define FB_IIN1_TRIS    TRISBbits.TRISB2 // GPIO direction register bit
#define FB_IIN1_WR      LATBbits.LATB2 // GPIO port latch register bit
#define FB_IIN1_RD      PORTBbits.RB2 // GPIO port register bit
#define FB_IIN1_ODC     ODCBbits.ODCB2 // GPIO port open drain configuration register bit
#define FB_IIN1_CNPU    CNPUBbits.CNPUB2 // GPIO port pull-up resistor register bit
#define FB_IIN1_CNPD    CNPDBbits.CNPDB2 // GPIO port pull-down resistor register bit
#define FB_IIN1_CNEN0   CNEN0Bbits.CNEN0B2 // GPIO port change notification Enable register bit
#define FB_IIN1_CNSTAT  CNSTATBbits.CNSTATB2 // GPIO port change notification Status register bit
#define FB_IIN1_CNEN1   CNEN1Bbits.CNEN1B2 // GPIO port change notification Edge Select Enable register bit
#define FB_IIN1_CNF     CNFBbits.CNFB2 // GPIO port change notification flag bit register bit
#define FB_IIN1_RP      34 // Number of Remappable Pin
#define FB_IIN1_SET     { asm volatile ("bset _LATB, #2 \n"); }
#define FB_IIN1_CLEAR   { asm volatile ("bclr _LATB, #2 \n"); }
#define FB_IIN1_TOGGLE  { asm volatile ("btg  _LATB, #2 \n"); }
#define FB_IIN1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define FB_IIN1_ANSEL   _ANSELB2 // analog/digital pin configuration register bit
#define FB_IIN1_ADCCORE 1 // index starts from zero, last index indicated shared adC core
#define FB_IIN1_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define FB_IIN1_ADC_AN_INPUT 1   // ANx input pin number
#define FB_IIN1_ADCBUF  ADCBUF1 // ADC buffer register for this input
#define FB_IIN1_ADC_ANIE ADIEHbits.IE1
#define FB_IIN1_ADC_ANEIE ADEIEHbits.EIEN1
#define FB_IIN1_ADC_IF   _ADCAN1IF // interrupt flag bit
#define FB_IIN1_ADC_IE   _ADCAN1IE // interrupt enable bit
#define FB_IIN1_ADC_IP   _ADCAN1IP // interrupt priority register value (0-7) for this analog input
#define FB_IIN1_ADC_RDY  _AN1RDY // ADC buffer ready bit
#define _FB_IIN1_ADC_Interrupt _ADCAN1Interrupt
#define FB_IIN1_INIT_ANALOG	 {FB_IIN1_ANSEL = 1; FB_IIN1_WR = PINSTATE_HIGH; FB_IIN1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define FB_IIN1_INIT_OUTPUT  {FB_IIN1_WR = PINSTATE_LOW; FB_IIN1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define FB_IIN1_INIT_INPUT   {FB_IIN1_WR = PINSTATE_HIGH; FB_IIN1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #26 is RB3
#define PGED_TRIS    TRISBbits.TRISB3 // GPIO direction register bit
#define PGED_WR      LATBbits.LATB3 // GPIO port latch register bit
#define PGED_RD      PORTBbits.RB3 // GPIO port register bit
#define PGED_ODC     ODCBbits.ODCB3 // GPIO port open drain configuration register bit
#define PGED_CNPU    CNPUBbits.CNPUB3 // GPIO port pull-up resistor register bit
#define PGED_CNPD    CNPDBbits.CNPDB3 // GPIO port pull-down resistor register bit
#define PGED_CNEN0   CNEN0Bbits.CNEN0B3 // GPIO port change notification Enable register bit
#define PGED_CNSTAT  CNSTATBbits.CNSTATB3 // GPIO port change notification Status register bit
#define PGED_CNEN1   CNEN1Bbits.CNEN1B3 // GPIO port change notification Edge Select Enable register bit
#define PGED_CNF     CNFBbits.CNFB3 // GPIO port change notification flag bit register bit
#define PGED_RP      35 // Number of Remappable Pin
#define PGED_SET     { asm volatile ("bset _LATB, #3 \n"); }
#define PGED_CLEAR   { asm volatile ("bclr _LATB, #3 \n"); }
#define PGED_TOGGLE  { asm volatile ("btg  _LATB, #3 \n"); }
#define PGED_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define PGED_ANSEL   _ANSELB3 // analog/digital pin configuration register bit
#define PGED_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define PGED_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define PGED_ADC_AN_INPUT 8   // ANx input pin number
#define PGED_ADCBUF  ADCBUF8 // ADC buffer register for this input
#define PGED_ADC_ANIE ADIELbits.IE8
#define PGED_ADC_ANEIE ADEIELbits.EIEN8
#define PGED_ADC_IF   _ADCAN8IF // interrupt flag bit
#define PGED_ADC_IE   _ADCAN8IE // interrupt enable bit
#define PGED_ADC_IP   _ADCAN8IP // interrupt priority register value (0-7) for this analog input
#define PGED_ADC_RDY  _AN8RDY // ADC buffer ready bit
#define _PGED_ADC_Interrupt _ADCAN8Interrupt
#define PGED_INIT_ANALOG  {PGED_ANSEL = 1; PGED_WR = PINSTATE_HIGH; PGED_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define PGED_INIT_OUTPUT  {PGED_WR = PINSTATE_LOW; PGED_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PGED_INIT_INPUT   {PGED_WR = PINSTATE_HIGH; PGED_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #27 is RB4
#define PGEC_TRIS    TRISBbits.TRISB4 // GPIO direction register bit
#define PGEC_WR      LATBbits.LATB4 // GPIO port latch register bit
#define PGEC_RD      PORTBbits.RB4 // GPIO port register bit
#define PGEC_ODC     ODCBbits.ODCB4 // GPIO port open drain configuration register bit
#define PGEC_CNPU    CNPUBbits.CNPUB4 // GPIO port pull-up resistor register bit
#define PGEC_CNPD    CNPDBbits.CNPDB4 // GPIO port pull-down resistor register bit
#define PGEC_CNEN0   CNEN0Bbits.CNEN0B4 // GPIO port change notification Enable register bit
#define PGEC_CNSTAT  CNSTATBbits.CNSTATB4 // GPIO port change notification Status register bit
#define PGEC_CNEN1   CNEN1Bbits.CNEN1B4 // GPIO port change notification Edge Select Enable register bit
#define PGEC_CNF     CNFBbits.CNFB4 // GPIO port change notification flag bit register bit
#define PGEC_RP      36 // Number of Remappable Pin
#define PGEC_SET     { asm volatile ("bset _LATB, #4 \n"); }
#define PGEC_CLEAR   { asm volatile ("bclr _LATB, #4 \n"); }
#define PGEC_TOGGLE  { asm volatile ("btg  _LATB, #4 \n"); }
#define PGEC_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define PGEC_INIT_OUTPUT  {PGEC_WR = PINSTATE_LOW; PGEC_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PGEC_INIT_INPUT   {PGEC_WR = PINSTATE_HIGH; PGEC_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #28 is RC8
#define SPI_CLK_TRIS    TRISCbits.TRISC8 // GPIO direction register bit
#define SPI_CLK_WR      LATCbits.LATC8 // GPIO port latch register bit
#define SPI_CLK_RD      PORTCbits.RC8 // GPIO port register bit
#define SPI_CLK_ODC     ODCCbits.ODCC8 // GPIO port open drain configuration register bit
#define SPI_CLK_CNPU    CNPUCbits.CNPUC8 // GPIO port pull-up resistor register bit
#define SPI_CLK_CNPD    CNPDCbits.CNPDC8 // GPIO port pull-down resistor register bit
#define SPI_CLK_CNEN0   CNEN0Cbits.CNEN0C8 // GPIO port change notification Enable register bit
#define SPI_CLK_CNSTAT  CNSTATCbits.CNSTATC8 // GPIO port change notification Status register bit
#define SPI_CLK_CNEN1   CNEN1Cbits.CNEN1C8 // GPIO port change notification Edge Select Enable register bit
#define SPI_CLK_CNF     CNFCbits.CNFC8 // GPIO port change notification flag bit register bit
#define SPI_CLK_RP      56 // Number of Remappable Pin
#define SPI_CLK_SET     { asm volatile ("bset _LATC, #8 \n"); }
#define SPI_CLK_CLEAR   { asm volatile ("bclr _LATC, #8 \n"); }
#define SPI_CLK_TOGGLE  { asm volatile ("btg  _LATC, #8 \n"); }
#define SPI_CLK_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SPI_CLK_INIT_OUTPUT  {SPI_CLK_WR = PINSTATE_LOW; SPI_CLK_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SPI_CLK_INIT_INPUT   {SPI_CLK_WR = PINSTATE_HIGH; SPI_CLK_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #29 is RC9
#define SPI_MISO_TRIS    TRISCbits.TRISC9 // GPIO direction register bit
#define SPI_MISO_WR      LATCbits.LATC9 // GPIO port latch register bit
#define SPI_MISO_RD      PORTCbits.RC9 // GPIO port register bit
#define SPI_MISO_ODC     ODCCbits.ODCC9 // GPIO port open drain configuration register bit
#define SPI_MISO_CNPU    CNPUCbits.CNPUC9 // GPIO port pull-up resistor register bit
#define SPI_MISO_CNPD    CNPDCbits.CNPDC9 // GPIO port pull-down resistor register bit
#define SPI_MISO_CNEN0   CNEN0Cbits.CNEN0C9 // GPIO port change notification Enable register bit
#define SPI_MISO_CNSTAT  CNSTATCbits.CNSTATC9 // GPIO port change notification Status register bit
#define SPI_MISO_CNEN1   CNEN1Cbits.CNEN1C9 // GPIO port change notification Edge Select Enable register bit
#define SPI_MISO_CNF     CNFCbits.CNFC9 // GPIO port change notification flag bit register bit
#define SPI_MISO_RP      57 // Number of Remappable Pin
#define SPI_MISO_SET     { asm volatile ("bset _LATC, #9 \n"); }
#define SPI_MISO_CLEAR   { asm volatile ("bclr _LATC, #9 \n"); }
#define SPI_MISO_TOGGLE  { asm volatile ("btg  _LATC, #9 \n"); }
#define SPI_MISO_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SPI_MISO_INIT_OUTPUT  {SPI_MISO_WR = PINSTATE_LOW; SPI_MISO_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SPI_MISO_INIT_INPUT   {SPI_MISO_WR = PINSTATE_HIGH; SPI_MISO_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #30 is RD8
#define SPI_MOSI_TRIS    TRISDbits.TRISD8 // GPIO direction register bit
#define SPI_MOSI_WR      LATDbits.LATD8 // GPIO port latch register bit
#define SPI_MOSI_RD      PORTDbits.RD8 // GPIO port register bit
#define SPI_MOSI_ODC     ODCDbits.ODCD8 // GPIO port open drain configuration register bit
#define SPI_MOSI_CNPU    CNPUDbits.CNPUD8 // GPIO port pull-up resistor register bit
#define SPI_MOSI_CNPD    CNPDDbits.CNPDD8 // GPIO port pull-down resistor register bit
#define SPI_MOSI_CNEN0   CNEN0Dbits.CNEN0D8 // GPIO port change notification Enable register bit
#define SPI_MOSI_CNSTAT  CNSTATDbits.CNSTATD8 // GPIO port change notification Status register bit
#define SPI_MOSI_CNEN1   CNEN1Dbits.CNEN1D8 // GPIO port change notification Edge Select Enable register bit
#define SPI_MOSI_CNF     CNFDbits.CNFD8 // GPIO port change notification flag bit register bit
#define SPI_MOSI_RP      72 // Number of Remappable Pin
#define SPI_MOSI_SET     { asm volatile ("bset _LATD, #8 \n"); }
#define SPI_MOSI_CLEAR   { asm volatile ("bclr _LATD, #8 \n"); }
#define SPI_MOSI_TOGGLE  { asm volatile ("btg  _LATD, #8 \n"); }
#define SPI_MOSI_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SPI_MOSI_INIT_OUTPUT  {SPI_MOSI_WR = PINSTATE_LOW; SPI_MOSI_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SPI_MOSI_INIT_INPUT   {SPI_MOSI_WR = PINSTATE_HIGH; SPI_MOSI_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #31 is VSS

// Device Pin #32 is VDD

// Device Pin #33 is RB5
#define SDA2_TRIS    TRISBbits.TRISB5 // GPIO direction register bit
#define SDA2_WR      LATBbits.LATB5 // GPIO port latch register bit
#define SDA2_RD      PORTBbits.RB5 // GPIO port register bit
#define SDA2_ODC     ODCBbits.ODCB5 // GPIO port open drain configuration register bit
#define SDA2_CNPU    CNPUBbits.CNPUB5 // GPIO port pull-up resistor register bit
#define SDA2_CNPD    CNPDBbits.CNPDB5 // GPIO port pull-down resistor register bit
#define SDA2_CNEN0   CNEN0Bbits.CNEN0B5 // GPIO port change notification Enable register bit
#define SDA2_CNSTAT  CNSTATBbits.CNSTATB5 // GPIO port change notification Status register bit
#define SDA2_CNEN1   CNEN1Bbits.CNEN1B5 // GPIO port change notification Edge Select Enable register bit
#define SDA2_CNF     CNFBbits.CNFB5 // GPIO port change notification flag bit register bit
#define SDA2_RP      37 // Number of Remappable Pin
#define SDA2_SET     { asm volatile ("bset _LATB, #5 \n"); }
#define SDA2_CLEAR   { asm volatile ("bclr _LATB, #5 \n"); }
#define SDA2_TOGGLE  { asm volatile ("btg  _LATB, #5 \n"); }
#define SDA2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SDA2_INIT_OUTPUT  {SDA2_WR = PINSTATE_LOW; SDA2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SDA2_INIT_INPUT   {SDA2_WR = PINSTATE_HIGH; SDA2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define SDA2_PGx_CHANNEL  6 // PWM channel index
#define SDA2_PGx_PER      PG6PER // PWM channel period register
#define SDA2_PGx_PHASE    PG6PHASE // PWM channel phase register
#define SDA2_PGx_DC       PG6DC // PWM channel duty cycle register
#define SDA2_PGx_DCA      PG6DCA// PWM channel duty cycle A register
#define SDA2_PGx_DTH      PG6DTH // PWM channel rising edge dead time register
#define SDA2_PGx_DTL      PG6DTL // PWM channel falling edge dead time register
#define SDA2_PGx_OVRENL   PG6IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define SDA2_PGx_PENL     PG6IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define SDA2_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define SDA2_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define SDA2_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define SDA2_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register

// Device Pin #34 is RB6
#define SCL2_TRIS    TRISBbits.TRISB6 // GPIO direction register bit
#define SCL2_WR      LATBbits.LATB6 // GPIO port latch register bit
#define SCL2_RD      PORTBbits.RB6 // GPIO port register bit
#define SCL2_ODC     ODCBbits.ODCB6 // GPIO port open drain configuration register bit
#define SCL2_CNPU    CNPUBbits.CNPUB6 // GPIO port pull-up resistor register bit
#define SCL2_CNPD    CNPDBbits.CNPDB6 // GPIO port pull-down resistor register bit
#define SCL2_CNEN0   CNEN0Bbits.CNEN0B6 // GPIO port change notification Enable register bit
#define SCL2_CNSTAT  CNSTATBbits.CNSTATB6 // GPIO port change notification Status register bit
#define SCL2_CNEN1   CNEN1Bbits.CNEN1B6 // GPIO port change notification Edge Select Enable register bit
#define SCL2_CNF     CNFBbits.CNFB6 // GPIO port change notification flag bit register bit
#define SCL2_RP      38 // Number of Remappable Pin
#define SCL2_SET     { asm volatile ("bset _LATB, #6 \n"); }
#define SCL2_CLEAR   { asm volatile ("bclr _LATB, #6 \n"); }
#define SCL2_TOGGLE  { asm volatile ("btg  _LATB, #6 \n"); }
#define SCL2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define SCL2_INIT_OUTPUT  {SCL2_WR = PINSTATE_LOW; SCL2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SCL2_INIT_INPUT   {SCL2_WR = PINSTATE_HIGH; SCL2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define SCL2_PGx_CHANNEL  6 // PWM channel index
#define SCL2_PGx_PER      PG6PER // PWM channel period register
#define SCL2_PGx_PHASE    PG6PHASE // PWM channel phase register
#define SCL2_PGx_DC       PG6DC // PWM channel duty cycle register
#define SCL2_PGx_DCA      PG6DCA// PWM channel duty cycle A register
#define SCL2_PGx_DTH      PG6DTH // PWM channel rising edge dead time register
#define SCL2_PGx_DTL      PG6DTL // PWM channel falling edge dead time register
#define SCL2_PGx_OVRENH   PG6IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define SCL2_PGx_PENH     PG6IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define SCL2_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define SCL2_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define SCL2_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define SCL2_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register
#define SCL2_PWM_IF       _PWM6IF // interrupt flag bit
#define SCL2_PWM_IE       _PWM6IE // interrupt enable bit
#define SCL2_PWM_IP       _PWM6IP // interrupt priority register value (0-7) for this analog input
#define _SCL2_PWM_Interrupt _PWM6Interrupt // Interrupt Service Routine name declaration

// Device Pin #35 is RB7
#define SPI_CS1_TRIS    TRISBbits.TRISB7 // GPIO direction register bit
#define SPI_CS1_WR      LATBbits.LATB7 // GPIO port latch register bit
#define SPI_CS1_RD      PORTBbits.RB7 // GPIO port register bit
#define SPI_CS1_ODC     ODCBbits.ODCB7 // GPIO port open drain configuration register bit
#define SPI_CS1_CNPU    CNPUBbits.CNPUB7 // GPIO port pull-up resistor register bit
#define SPI_CS1_CNPD    CNPDBbits.CNPDB7 // GPIO port pull-down resistor register bit
#define SPI_CS1_CNEN0   CNEN0Bbits.CNEN0B7 // GPIO port change notification Enable register bit
#define SPI_CS1_CNSTAT  CNSTATBbits.CNSTATB7 // GPIO port change notification Status register bit
#define SPI_CS1_CNEN1   CNEN1Bbits.CNEN1B7 // GPIO port change notification Edge Select Enable register bit
#define SPI_CS1_CNF     CNFBbits.CNFB7 // GPIO port change notification flag bit register bit
#define SPI_CS1_RP      39 // Number of Remappable Pin
#define SPI_CS1_SET     { asm volatile ("bset _LATB, #7 \n"); }
#define SPI_CS1_CLEAR   { asm volatile ("bclr _LATB, #7 \n"); }
#define SPI_CS1_TOGGLE  { asm volatile ("btg  _LATB, #7 \n"); }
#define SPI_CS1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define SPI_CS1_ANSEL   _ANSELB7 // analog/digital pin configuration register bit
#define SPI_CS1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define SPI_CS1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define SPI_CS1_ADC_AN_INPUT 2   // ANx input pin number
#define SPI_CS1_ADCBUF  ADCBUF2 // ADC buffer register for this input
#define SPI_CS1_ADC_ANIE ADIELbits.IE2
#define SPI_CS1_ADC_ANEIE ADEIELbits.EIEN2
#define SPI_CS1_ADC_IF   _ADCAN2IF // interrupt flag bit
#define SPI_CS1_ADC_IE   _ADCAN2IE // interrupt enable bit
#define SPI_CS1_ADC_IP   _ADCAN2IP // interrupt priority register value (0-7) for this analog input
#define SPI_CS1_ADC_RDY  _AN2RDY // ADC buffer ready bit
#define _SPI_CS1_ADC_Interrupt _ADCAN2Interrupt
#define SPI_CS1_INIT_ANALOG	{SPI_CS1_ANSEL = 1; SPI_CS1_WR = PINSTATE_HIGH; SPI_CS1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define SPI_CS1_INIT_OUTPUT  {SPI_CS1_WR = PINSTATE_LOW; SPI_CS1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SPI_CS1_INIT_INPUT   {SPI_CS1_WR = PINSTATE_HIGH; SPI_CS1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #36 is RB8
#define SCL1_TRIS    TRISBbits.TRISB8 // GPIO direction register bit
#define SCL1_WR      LATBbits.LATB8 // GPIO port latch register bit
#define SCL1_RD      PORTBbits.RB8 // GPIO port register bit
#define SCL1_ODC     ODCBbits.ODCB8 // GPIO port open drain configuration register bit
#define SCL1_CNPU    CNPUBbits.CNPUB8 // GPIO port pull-up resistor register bit
#define SCL1_CNPD    CNPDBbits.CNPDB8 // GPIO port pull-down resistor register bit
#define SCL1_CNEN0   CNEN0Bbits.CNEN0B8 // GPIO port change notification Enable register bit
#define SCL1_CNSTAT  CNSTATBbits.CNSTATB8 // GPIO port change notification Status register bit
#define SCL1_CNEN1   CNEN1Bbits.CNEN1B8 // GPIO port change notification Edge Select Enable register bit
#define SCL1_CNF     CNFBbits.CNFB8 // GPIO port change notification flag bit register bit
#define SCL1_RP      40 // Number of Remappable Pin
#define SCL1_SET     { asm volatile ("bset _LATB, #8 \n"); }
#define SCL1_CLEAR   { asm volatile ("bclr _LATB, #8 \n"); }
#define SCL1_TOGGLE  { asm volatile ("btg  _LATB, #8 \n"); }
#define SCL1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define SCL1_ANSEL   _ANSELB8 // analog/digital pin configuration register bit
#define SCL1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define SCL1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define SCL1_ADC_AN_INPUT 10   // ANx input pin number
#define SCL1_ADCBUF  ADCBUF10 // ADC buffer register for this input
#define SCL1_ADC_ANIE ADIELbits.IE10
#define SCL1_ADC_ANEIE ADEIELbits.EIEN10
#define SCL1_ADC_IF   _ADCAN10IF // interrupt flag bit
#define SCL1_ADC_IE   _ADCAN10IE // interrupt enable bit
#define SCL1_ADC_IP   _ADCAN10IP // interrupt priority register value (0-7) for this analog input
#define SCL1_ADC_RDY  _AN10RDY // ADC buffer ready bit
#define _SCL1_ADC_Interrupt _ADCAN10Interrupt
#define SCL1_INIT_ANALOG  {SCL1_ANSEL = 1; SCL1_WR = PINSTATE_HIGH; SCL1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define SCL1_INIT_OUTPUT  {SCL1_WR = PINSTATE_LOW; SCL1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SCL1_INIT_INPUT   {SCL1_WR = PINSTATE_HIGH; SCL1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #37 is RB9
#define SDA1_TRIS    TRISBbits.TRISB9 // GPIO direction register bit
#define SDA1_WR      LATBbits.LATB9 // GPIO port latch register bit
#define SDA1_RD      PORTBbits.RB9 // GPIO port register bit
#define SDA1_ODC     ODCBbits.ODCB9 // GPIO port open drain configuration register bit
#define SDA1_CNPU    CNPUBbits.CNPUB9 // GPIO port pull-up resistor register bit
#define SDA1_CNPD    CNPDBbits.CNPDB9 // GPIO port pull-down resistor register bit
#define SDA1_CNEN0   CNEN0Bbits.CNEN0B9 // GPIO port change notification Enable register bit
#define SDA1_CNSTAT  CNSTATBbits.CNSTATB9 // GPIO port change notification Status register bit
#define SDA1_CNEN1   CNEN1Bbits.CNEN1B9 // GPIO port change notification Edge Select Enable register bit
#define SDA1_CNF     CNFBbits.CNFB9 // GPIO port change notification flag bit register bit
#define SDA1_RP      41 // Number of Remappable Pin
#define SDA1_SET     { asm volatile ("bset _LATB, #9 \n"); }
#define SDA1_CLEAR   { asm volatile ("bclr _LATB, #9 \n"); }
#define SDA1_TOGGLE  { asm volatile ("btg  _LATB, #9 \n"); }
#define SDA1_IS_ANALOG_INPUT true // Pin is/is not analog input 
#define SDA1_ANSEL   _ANSELB9 // analog/digital pin configuration register bit
#define SDA1_ADCCORE 2 // index starts from zero, last index indicated shared adC core
#define SDA1_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core
#define SDA1_ADC_AN_INPUT 11   // ANx input pin number
#define SDA1_ADCBUF  ADCBUF11 // ADC buffer register for this input
#define SDA1_ADC_ANIE ADIELbits.IE11
#define SDA1_ADC_ANEIE ADEIELbits.EIEN11
#define SDA1_ADC_IF   _ADCAN11IF // interrupt flag bit
#define SDA1_ADC_IE   _ADCAN11IE // interrupt enable bit
#define SDA1_ADC_IP   _ADCAN11IP // interrupt priority register value (0-7) for this analog input
#define SDA1_ADC_RDY  _AN11RDY // ADC buffer ready bit
#define _SDA1_ADC_Interrupt _ADCAN11Interrupt
#define SDA1_INIT_ANALOG	{SDA1_ANSEL = 1; SDA1_WR = PINSTATE_HIGH; SDA1_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define SDA1_INIT_OUTPUT  {SDA1_WR = PINSTATE_LOW; SDA1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SDA1_INIT_INPUT   {SDA1_WR = PINSTATE_HIGH; SDA1_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #38 is RC4
#define BUCKH1_TRIS    TRISCbits.TRISC4 // GPIO direction register bit
#define BUCKH1_WR      LATCbits.LATC4 // GPIO port latch register bit
#define BUCKH1_RD      PORTCbits.RC4 // GPIO port register bit
#define BUCKH1_ODC     ODCCbits.ODCC4 // GPIO port open drain configuration register bit
#define BUCKH1_CNPU    CNPUCbits.CNPUC4 // GPIO port pull-up resistor register bit
#define BUCKH1_CNPD    CNPDCbits.CNPDC4 // GPIO port pull-down resistor register bit
#define BUCKH1_CNEN0   CNEN0Cbits.CNEN0C4 // GPIO port change notification Enable register bit
#define BUCKH1_CNSTAT  CNSTATCbits.CNSTATC4 // GPIO port change notification Status register bit
#define BUCKH1_CNEN1   CNEN1Cbits.CNEN1C4 // GPIO port change notification Edge Select Enable register bit
#define BUCKH1_CNF     CNFCbits.CNFC4 // GPIO port change notification flag bit register bit
#define BUCKH1_RP      52 // Number of Remappable Pin
#define BUCKH1_SET     { asm volatile ("bset _LATC, #4 \n"); }
#define BUCKH1_CLEAR   { asm volatile ("bclr _LATC, #4 \n"); }
#define BUCKH1_TOGGLE  { asm volatile ("btg  _LATC, #4 \n"); }
#define BUCKH1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BUCKH1_INIT_OUTPUT  {BUCKH1_WR = PINSTATE_LOW; BUCKH1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BUCKH1_INIT_INPUT   {BUCKH1_WR = PINSTATE_HIGH; BUCKH1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BUCKH1_PGx_CHANNEL  5 // PWM channel index
#define BUCKH1_PGx_PER      PG5PER // PWM channel period register
#define BUCKH1_PGx_PHASE    PG5PHASE // PWM channel phase register
#define BUCKH1_PGx_DC       PG5DC // PWM channel duty cycle register
#define BUCKH1_PGx_DCA      PG5DCA// PWM channel duty cycle A register
#define BUCKH1_PGx_DTH      PG5DTH // PWM channel rising edge dead time register
#define BUCKH1_PGx_DTL      PG5DTL // PWM channel falling edge dead time register
#define BUCKH1_PGx_OVRENH   PG5IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define BUCKH1_PGx_PENH     PG5IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define BUCKH1_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define BUCKH1_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define BUCKH1_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger B register
#define BUCKH1_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger C register
#define BUCKH1_PWM_IF       _PWM5IF // interrupt flag bit
#define BUCKH1_PWM_IE       _PWM5IE // interrupt enable bit
#define BUCKH1_PWM_IP       _PWM5IP // interrupt priority register value (0-7) for this analog input
#define _BUCKH1_PWM_Interrupt _PWM5Interrupt // Interrupt Service Routine name declaration

// ToDo: User defined settings need to be incorporated into code generator
#define BUCKH1_ADC_TRGSRC_1 0b01100 //ADTRIGx_TRGSRC_PWM5_TRIG1
#define BUCKH1_ADC_TRGSRC_2 0b01101 //ADTRIGx_TRGSRC_PWM5_TRIG2


// Device Pin #39 is RC5
#define BUCKL1_TRIS    TRISCbits.TRISC5 // GPIO direction register bit
#define BUCKL1_WR      LATCbits.LATC5 // GPIO port latch register bit
#define BUCKL1_RD      PORTCbits.RC5 // GPIO port register bit
#define BUCKL1_ODC     ODCCbits.ODCC5 // GPIO port open drain configuration register bit
#define BUCKL1_CNPU    CNPUCbits.CNPUC5 // GPIO port pull-up resistor register bit
#define BUCKL1_CNPD    CNPDCbits.CNPDC5 // GPIO port pull-down resistor register bit
#define BUCKL1_CNEN0   CNEN0Cbits.CNEN0C5 // GPIO port change notification Enable register bit
#define BUCKL1_CNSTAT  CNSTATCbits.CNSTATC5 // GPIO port change notification Status register bit
#define BUCKL1_CNEN1   CNEN1Cbits.CNEN1C5 // GPIO port change notification Edge Select Enable register bit
#define BUCKL1_CNF     CNFCbits.CNFC5 // GPIO port change notification flag bit register bit
#define BUCKL1_RP      53 // Number of Remappable Pin
#define BUCKL1_SET     { asm volatile ("bset _LATC, #5 \n"); }
#define BUCKL1_CLEAR   { asm volatile ("bclr _LATC, #5 \n"); }
#define BUCKL1_TOGGLE  { asm volatile ("btg  _LATC, #5 \n"); }
#define BUCKL1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BUCKL1_INIT_OUTPUT  {BUCKL1_WR = PINSTATE_LOW; BUCKL1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BUCKL1_INIT_INPUT   {BUCKL1_WR = PINSTATE_HIGH; BUCKL1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BUCKL1_PGx_CHANNEL  5 // PWM channel index
#define BUCKL1_PGx_PER      PG5PER // PWM channel period register
#define BUCKL1_PGx_PHASE    PG5PHASE // PWM channel phase register
#define BUCKL1_PGx_DC       PG5DC // PWM channel duty cycle register
#define BUCKL1_PGx_DCA      PG5DCA// PWM channel duty cycle A register
#define BUCKL1_PGx_DTH      PG5DTH // PWM channel rising edge dead time register
#define BUCKL1_PGx_DTL      PG5DTL // PWM channel falling edge dead time register
#define BUCKL1_PGx_OVRENL   PG5IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define BUCKL1_PGx_PENL     PG5IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define BUCKL1_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define BUCKL1_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define BUCKL1_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger A register
#define BUCKL1_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger A register

// Device Pin #40 is RC10
#define BOOSTH1_TRIS    TRISCbits.TRISC10 // GPIO direction register bit
#define BOOSTH1_WR      LATCbits.LATC10 // GPIO port latch register bit
#define BOOSTH1_RD      PORTCbits.RC10 // GPIO port register bit
#define BOOSTH1_ODC     ODCCbits.ODCC10 // GPIO port open drain configuration register bit
#define BOOSTH1_CNPU    CNPUCbits.CNPUC10 // GPIO port pull-up resistor register bit
#define BOOSTH1_CNPD    CNPDCbits.CNPDC10 // GPIO port pull-down resistor register bit
#define BOOSTH1_CNEN0   CNEN0Cbits.CNEN0C10 // GPIO port change notification Enable register bit
#define BOOSTH1_CNSTAT  CNSTATCbits.CNSTATC10 // GPIO port change notification Status register bit
#define BOOSTH1_CNEN1   CNEN1Cbits.CNEN1C10 // GPIO port change notification Edge Select Enable register bit
#define BOOSTH1_CNF     CNFCbits.CNFC10 // GPIO port change notification flag bit register bit
#define BOOSTH1_RP      58 // Number of Remappable Pin
#define BOOSTH1_SET     { asm volatile ("bset _LATC, #10 \n"); }
#define BOOSTH1_CLEAR   { asm volatile ("bclr _LATC, #10 \n"); }
#define BOOSTH1_TOGGLE  { asm volatile ("btg  _LATC, #10 \n"); }
#define BOOSTH1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BOOSTH1_INIT_OUTPUT  {BOOSTH1_WR = PINSTATE_LOW; BOOSTH1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BOOSTH1_INIT_INPUT   {BOOSTH1_WR = PINSTATE_HIGH; BOOSTH1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BOOSTH1_PGx_CHANNEL  7 // PWM channel index
#define BOOSTH1_PGx_PER      PG7PER // PWM channel period register
#define BOOSTH1_PGx_PHASE    PG7PHASE // PWM channel phase register
#define BOOSTH1_PGx_DC       PG7DC // PWM channel duty cycle register
#define BOOSTH1_PGx_DCA      PG7DCA// PWM channel duty cycle A register
#define BOOSTH1_PGx_DTH      PG7DTH // PWM channel rising edge dead time register
#define BOOSTH1_PGx_DTL      PG7DTL // PWM channel falling edge dead time register
#define BOOSTH1_PGx_OVRENH   PG7IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define BOOSTH1_PGx_PENH     PG7IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define BOOSTH1_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define BOOSTH1_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define BOOSTH1_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define BOOSTH1_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register
#define BOOSTH1_PWM_IF       _PWM7IF // interrupt flag bit
#define BOOSTH1_PWM_IE       _PWM7IE // interrupt enable bit
#define BOOSTH1_PWM_IP       _PWM7IP // interrupt priority register value (0-7) for this analog input
#define _BOOSTH1_PWM_Interrupt _PWM7Interrupt // Interrupt Service Routine name declaration

// ToDo: User defined settings need to be incorporated into code generator
#define BOOSTH1_ADC_TRGSRC_1 0b10000 //ADTRIGx_TRGSRC_PWM7_TRIG1
#define BOOSTH1_ADC_TRGSRC_2 0b10001 //ADTRIGx_TRGSRC_PWM7_TRIG2

// Device Pin #41 is RC11
#define BOOSTL1_TRIS    TRISCbits.TRISC11 // GPIO direction register bit
#define BOOSTL1_WR      LATCbits.LATC11 // GPIO port latch register bit
#define BOOSTL1_RD      PORTCbits.RC11 // GPIO port register bit
#define BOOSTL1_ODC     ODCCbits.ODCC11 // GPIO port open drain configuration register bit
#define BOOSTL1_CNPU    CNPUCbits.CNPUC11 // GPIO port pull-up resistor register bit
#define BOOSTL1_CNPD    CNPDCbits.CNPDC11 // GPIO port pull-down resistor register bit
#define BOOSTL1_CNEN0   CNEN0Cbits.CNEN0C11 // GPIO port change notification Enable register bit
#define BOOSTL1_CNSTAT  CNSTATCbits.CNSTATC11 // GPIO port change notification Status register bit
#define BOOSTL1_CNEN1   CNEN1Cbits.CNEN1C11 // GPIO port change notification Edge Select Enable register bit
#define BOOSTL1_CNF     CNFCbits.CNFC11 // GPIO port change notification flag bit register bit
#define BOOSTL1_RP      59 // Number of Remappable Pin
#define BOOSTL1_SET     { asm volatile ("bset _LATC, #11 \n"); }
#define BOOSTL1_CLEAR   { asm volatile ("bclr _LATC, #11 \n"); }
#define BOOSTL1_TOGGLE  { asm volatile ("btg  _LATC, #11 \n"); }
#define BOOSTL1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BOOSTL1_INIT_OUTPUT  {BOOSTL1_WR = PINSTATE_LOW; BOOSTL1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BOOSTL1_INIT_INPUT   {BOOSTL1_WR = PINSTATE_HIGH; BOOSTL1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BOOSTL1_PGx_CHANNEL  7 // PWM channel index
#define BOOSTL1_PGx_PER      PG7PER // PWM channel period register
#define BOOSTL1_PGx_PHASE    PG7PHASE // PWM channel phase register
#define BOOSTL1_PGx_DC       PG7DC // PWM channel duty cycle register
#define BOOSTL1_PGx_DCA      PG7DCA// PWM channel duty cycle A register
#define BOOSTL1_PGx_DTH      PG7DTH // PWM channel rising edge dead time register
#define BOOSTL1_PGx_DTL      PG7DTL // PWM channel falling edge dead time register
#define BOOSTL1_PGx_OVRENL   PG7IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define BOOSTL1_PGx_PENL     PG7IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define BOOSTL1_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define BOOSTL1_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define BOOSTL1_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define BOOSTL1_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register

// Device Pin #42 is VSS

// Device Pin #43 is VDD

// Device Pin #44 is RD1
#define PPC_IRQ1_TRIS    TRISDbits.TRISD1 // GPIO direction register bit
#define PPC_IRQ1_WR      LATDbits.LATD1 // GPIO port latch register bit
#define PPC_IRQ1_RD      PORTDbits.RD1 // GPIO port register bit
#define PPC_IRQ1_ODC     ODCDbits.ODCD1 // GPIO port open drain configuration register bit
#define PPC_IRQ1_CNPU    CNPUDbits.CNPUD1 // GPIO port pull-up resistor register bit
#define PPC_IRQ1_CNPD    CNPDDbits.CNPDD1 // GPIO port pull-down resistor register bit
#define PPC_IRQ1_CNEN0   CNEN0Dbits.CNEN0D1 // GPIO port change notification Enable register bit
#define PPC_IRQ1_CNSTAT  CNSTATDbits.CNSTATD1 // GPIO port change notification Status register bit
#define PPC_IRQ1_CNEN1   CNEN1Dbits.CNEN1D1 // GPIO port change notification Edge Select Enable register bit
#define PPC_IRQ1_CNF     CNFDbits.CNFD1 // GPIO port change notification flag bit register bit
#define PPC_IRQ1_RP      65 // Number of Remappable Pin
#define PPC_IRQ1_SET     { asm volatile ("bset _LATD, #1 \n"); }
#define PPC_IRQ1_CLEAR   { asm volatile ("bclr _LATD, #1 \n"); }
#define PPC_IRQ1_TOGGLE  { asm volatile ("btg  _LATD, #1 \n"); }
#define PPC_IRQ1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define PPC_IRQ1_INIT_OUTPUT  {PPC_IRQ1_WR = PINSTATE_LOW; PPC_IRQ1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PPC_IRQ1_INIT_INPUT   {PPC_IRQ1_WR = PINSTATE_HIGH; PPC_IRQ1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define PPC_IRQ1_PGx_CHANNEL  4 // PWM channel index
#define PPC_IRQ1_PGx_PER      PG4PER // PWM channel period register
#define PPC_IRQ1_PGx_PHASE    PG4PHASE // PWM channel phase register
#define PPC_IRQ1_PGx_DC       PG4DC // PWM channel duty cycle register
#define PPC_IRQ1_PGx_DCA      PG4DCA// PWM channel duty cycle A register
#define PPC_IRQ1_PGx_DTH      PG4DTH // PWM channel rising edge dead time register
#define PPC_IRQ1_PGx_DTL      PG4DTL // PWM channel falling edge dead time register
#define PPC_IRQ1_PGx_OVRENH   PG4IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define PPC_IRQ1_PGx_PENH     PG4IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define PPC_IRQ1_PGxUPDREQ    PG4STATbits.UPDREQ // PWM channel ADC trigger A register
#define PPC_IRQ1_PGxTRIGA     PG4TRIGA // PWM channel ADC trigger A register
#define PPC_IRQ1_PGxTRIGB     PG4TRIGB // PWM channel ADC trigger A register
#define PPC_IRQ1_PGxTRIGC     PG4TRIGC // PWM channel ADC trigger A register
#define PPC_IRQ1_PWM_IF       _PWM4IF // interrupt flag bit
#define PPC_IRQ1_PWM_IE       _PWM4IE // interrupt enable bit
#define PPC_IRQ1_PWM_IP       _PWM4IP // interrupt priority register value (0-7) for this analog input
#define _PPC_IRQ1_PWM_Interrupt _PWM4Interrupt // Interrupt Service Routine name declaration

// Device Pin #45 is RB10
#define PPC_RST1_TRIS    TRISBbits.TRISB10 // GPIO direction register bit
#define PPC_RST1_WR      LATBbits.LATB10 // GPIO port latch register bit
#define PPC_RST1_RD      PORTBbits.RB10 // GPIO port register bit
#define PPC_RST1_ODC     ODCBbits.ODCB10 // GPIO port open drain configuration register bit
#define PPC_RST1_CNPU    CNPUBbits.CNPUB10 // GPIO port pull-up resistor register bit
#define PPC_RST1_CNPD    CNPDBbits.CNPDB10 // GPIO port pull-down resistor register bit
#define PPC_RST1_CNEN0   CNEN0Bbits.CNEN0B10 // GPIO port change notification Enable register bit
#define PPC_RST1_CNSTAT  CNSTATBbits.CNSTATB10 // GPIO port change notification Status register bit
#define PPC_RST1_CNEN1   CNEN1Bbits.CNEN1B10 // GPIO port change notification Edge Select Enable register bit
#define PPC_RST1_CNF     CNFBbits.CNFB10 // GPIO port change notification flag bit register bit
#define PPC_RST1_RP      42 // Number of Remappable Pin
#define PPC_RST1_SET     { asm volatile ("bset _LATB, #10 \n"); }
#define PPC_RST1_CLEAR   { asm volatile ("bclr _LATB, #10 \n"); }
#define PPC_RST1_TOGGLE  { asm volatile ("btg  _LATB, #10 \n"); }
#define PPC_RST1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define PPC_RST1_INIT_OUTPUT  {PPC_RST1_WR = PINSTATE_LOW; PPC_RST1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define PPC_RST1_INIT_INPUT   {PPC_RST1_WR = PINSTATE_HIGH; PPC_RST1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define PPC_RST1_PGx_CHANNEL  3 // PWM channel index
#define PPC_RST1_PGx_PER      PG3PER // PWM channel period register
#define PPC_RST1_PGx_PHASE    PG3PHASE // PWM channel phase register
#define PPC_RST1_PGx_DC       PG3DC // PWM channel duty cycle register
#define PPC_RST1_PGx_DCA      PG3DCA// PWM channel duty cycle A register
#define PPC_RST1_PGx_DTH      PG3DTH // PWM channel rising edge dead time register
#define PPC_RST1_PGx_DTL      PG3DTL // PWM channel falling edge dead time register
#define PPC_RST1_PGx_OVRENH   PG3IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define PPC_RST1_PGx_PENH     PG3IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define PPC_RST1_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define PPC_RST1_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define PPC_RST1_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define PPC_RST1_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register
#define PPC_RST1_PWM_IF       _PWM3IF // interrupt flag bit
#define PPC_RST1_PWM_IE       _PWM3IE // interrupt enable bit
#define PPC_RST1_PWM_IP       _PWM3IP // interrupt priority register value (0-7) for this analog input
#define _PPC_RST1_PWM_Interrupt _PWM3Interrupt // Interrupt Service Routine name declaration

// Device Pin #46 is RB11
#define HUB_PRTPWR1_TRIS    TRISBbits.TRISB11 // GPIO direction register bit
#define HUB_PRTPWR1_WR      LATBbits.LATB11 // GPIO port latch register bit
#define HUB_PRTPWR1_RD      PORTBbits.RB11 // GPIO port register bit
#define HUB_PRTPWR1_ODC     ODCBbits.ODCB11 // GPIO port open drain configuration register bit
#define HUB_PRTPWR1_CNPU    CNPUBbits.CNPUB11 // GPIO port pull-up resistor register bit
#define HUB_PRTPWR1_CNPD    CNPDBbits.CNPDB11 // GPIO port pull-down resistor register bit
#define HUB_PRTPWR1_CNEN0   CNEN0Bbits.CNEN0B11 // GPIO port change notification Enable register bit
#define HUB_PRTPWR1_CNSTAT  CNSTATBbits.CNSTATB11 // GPIO port change notification Status register bit
#define HUB_PRTPWR1_CNEN1   CNEN1Bbits.CNEN1B11 // GPIO port change notification Edge Select Enable register bit
#define HUB_PRTPWR1_CNF     CNFBbits.CNFB11 // GPIO port change notification flag bit register bit
#define HUB_PRTPWR1_RP      43 // Number of Remappable Pin
#define HUB_PRTPWR1_SET     { asm volatile ("bset _LATB, #11 \n"); }
#define HUB_PRTPWR1_CLEAR   { asm volatile ("bclr _LATB, #11 \n"); }
#define HUB_PRTPWR1_TOGGLE  { asm volatile ("btg  _LATB, #11 \n"); }
#define HUB_PRTPWR1_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define HUB_PRTPWR1_INIT_OUTPUT  {HUB_PRTPWR1_WR = PINSTATE_LOW; HUB_PRTPWR1_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define HUB_PRTPWR1_INIT_INPUT   {HUB_PRTPWR1_WR = PINSTATE_HIGH; HUB_PRTPWR1_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define HUB_PRTPWR1_PGx_CHANNEL  3 // PWM channel index
#define HUB_PRTPWR1_PGx_PER      PG3PER // PWM channel period register
#define HUB_PRTPWR1_PGx_PHASE    PG3PHASE // PWM channel phase register
#define HUB_PRTPWR1_PGx_DC       PG3DC // PWM channel duty cycle register
#define HUB_PRTPWR1_PGx_DCA      PG3DCA// PWM channel duty cycle A register
#define HUB_PRTPWR1_PGx_DTH      PG3DTH // PWM channel rising edge dead time register
#define HUB_PRTPWR1_PGx_DTL      PG3DTL // PWM channel falling edge dead time register
#define HUB_PRTPWR1_PGx_OVRENL   PG3IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define HUB_PRTPWR1_PGx_PENL     PG3IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define HUB_PRTPWR1_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define HUB_PRTPWR1_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define HUB_PRTPWR1_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define HUB_PRTPWR1_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register

// Device Pin #47 is RB12
#define BOOSTH2_TRIS    TRISBbits.TRISB12 // GPIO direction register bit
#define BOOSTH2_WR      LATBbits.LATB12 // GPIO port latch register bit
#define BOOSTH2_RD      PORTBbits.RB12 // GPIO port register bit
#define BOOSTH2_ODC     ODCBbits.ODCB12 // GPIO port open drain configuration register bit
#define BOOSTH2_CNPU    CNPUBbits.CNPUB12 // GPIO port pull-up resistor register bit
#define BOOSTH2_CNPD    CNPDBbits.CNPDB12 // GPIO port pull-down resistor register bit
#define BOOSTH2_CNEN0   CNEN0Bbits.CNEN0B12 // GPIO port change notification Enable register bit
#define BOOSTH2_CNSTAT  CNSTATBbits.CNSTATB12 // GPIO port change notification Status register bit
#define BOOSTH2_CNEN1   CNEN1Bbits.CNEN1B12 // GPIO port change notification Edge Select Enable register bit
#define BOOSTH2_CNF     CNFBbits.CNFB12 // GPIO port change notification flag bit register bit
#define BOOSTH2_RP      44 // Number of Remappable Pin
#define BOOSTH2_SET     { asm volatile ("bset _LATB, #12 \n"); }
#define BOOSTH2_CLEAR   { asm volatile ("bclr _LATB, #12 \n"); }
#define BOOSTH2_TOGGLE  { asm volatile ("btg  _LATB, #12 \n"); }
#define BOOSTH2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BOOSTH2_INIT_OUTPUT  {BOOSTH2_WR = PINSTATE_LOW; BOOSTH2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BOOSTH2_INIT_INPUT   {BOOSTH2_WR = PINSTATE_HIGH; BOOSTH2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BOOSTH2_PGx_CHANNEL  2 // PWM channel index
#define BOOSTH2_PGx_PER      PG2PER // PWM channel period register
#define BOOSTH2_PGx_PHASE    PG2PHASE // PWM channel phase register
#define BOOSTH2_PGx_DC       PG2DC // PWM channel duty cycle register
#define BOOSTH2_PGx_DCA      PG2DCA// PWM channel duty cycle A register
#define BOOSTH2_PGx_DTH      PG2DTH // PWM channel rising edge dead time register
#define BOOSTH2_PGx_DTL      PG2DTL // PWM channel falling edge dead time register
#define BOOSTH2_PGx_OVRENH   PG2IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define BOOSTH2_PGx_PENH     PG2IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define BOOSTH2_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define BOOSTH2_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define BOOSTH2_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define BOOSTH2_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register
#define BOOSTH2_PWM_IF       _PWM2IF // interrupt flag bit
#define BOOSTH2_PWM_IE       _PWM2IE // interrupt enable bit
#define BOOSTH2_PWM_IP       _PWM2IP // interrupt priority register value (0-7) for this analog input
#define _BOOSTH2_PWM_Interrupt _PWM2Interrupt // Interrupt Service Routine name declaration

// ToDo: User defined settings need to be incorporated into code generator
#define BOOSTH2_ADC_TRGSRC_1 0b00110 //ADTRIGx_TRGSRC_PWM2_TRIG1
#define BOOSTH2_ADC_TRGSRC_2 0b00111 //ADTRIGx_TRGSRC_PWM2_TRIG2

// Device Pin #48 is RB13
#define BOOSTL2_TRIS    TRISBbits.TRISB13 // GPIO direction register bit
#define BOOSTL2_WR      LATBbits.LATB13 // GPIO port latch register bit
#define BOOSTL2_RD      PORTBbits.RB13 // GPIO port register bit
#define BOOSTL2_ODC     ODCBbits.ODCB13 // GPIO port open drain configuration register bit
#define BOOSTL2_CNPU    CNPUBbits.CNPUB13 // GPIO port pull-up resistor register bit
#define BOOSTL2_CNPD    CNPDBbits.CNPDB13 // GPIO port pull-down resistor register bit
#define BOOSTL2_CNEN0   CNEN0Bbits.CNEN0B13 // GPIO port change notification Enable register bit
#define BOOSTL2_CNSTAT  CNSTATBbits.CNSTATB13 // GPIO port change notification Status register bit
#define BOOSTL2_CNEN1   CNEN1Bbits.CNEN1B13 // GPIO port change notification Edge Select Enable register bit
#define BOOSTL2_CNF     CNFBbits.CNFB13 // GPIO port change notification flag bit register bit
#define BOOSTL2_RP      45 // Number of Remappable Pin
#define BOOSTL2_SET     { asm volatile ("bset _LATB, #13 \n"); }
#define BOOSTL2_CLEAR   { asm volatile ("bclr _LATB, #13 \n"); }
#define BOOSTL2_TOGGLE  { asm volatile ("btg  _LATB, #13 \n"); }
#define BOOSTL2_IS_ANALOG_INPUT  false // Pin is/is not analog input 
#define BOOSTL2_INIT_OUTPUT  {BOOSTL2_WR = PINSTATE_LOW; BOOSTL2_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define BOOSTL2_INIT_INPUT   {BOOSTL2_WR = PINSTATE_HIGH; BOOSTL2_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define BOOSTL2_PGx_CHANNEL  2 // PWM channel index
#define BOOSTL2_PGx_PER      PG2PER // PWM channel period register
#define BOOSTL2_PGx_PHASE    PG2PHASE // PWM channel phase register
#define BOOSTL2_PGx_DC       PG2DC // PWM channel duty cycle register
#define BOOSTL2_PGx_DCA      PG2DCA// PWM channel duty cycle A register
#define BOOSTL2_PGx_DTH      PG2DTH // PWM channel rising edge dead time register
#define BOOSTL2_PGx_DTL      PG2DTL // PWM channel falling edge dead time register
#define BOOSTL2_PGx_OVRENL   PG2IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define BOOSTL2_PGx_PENL     PG2IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define BOOSTL2_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define BOOSTL2_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define BOOSTL2_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define BOOSTL2_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register



#endif	/* __00173_USB_PD_BoB_R20_PINMAP_H__ */
