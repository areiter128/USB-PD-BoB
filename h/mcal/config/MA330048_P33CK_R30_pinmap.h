/*!MA33048_P33CK_R30_pinmap.h
 * ***********************************************************************************************
 * File:        MA33048_P33CK_R30_pinmap.h                                                             
 * Author:      M91406                                                                         
 * Comments:    Hardware abstraction layer device pinout descriptor                                
 * Board ID:    MA33048_P33CK                                                                       
 * Date:        05/22/2019                                                                             
 * Build:       0008                                                                       
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
#ifndef __MA33048_P33CK_R30_PINMAP_H__
#define __MA33048_P33CK_R30_PINMAP_H__

#include <xc.h> // include processor files - each processor file is guarded 
#include <stdint.h> // Include standard integer types                       
#include <stdbool.h> // Include standard boolean types                      
#include "mcal/mcal.h" // Include local mcal layer header file        

/*!PINMAP_VERSION
 * ***********************************************************************************************
 * Description:
 * This flag is a user defined flag helping to provide version information about the
 * pinmap file. This string can be used universally across the firmware to identify the
 * hardware version this firmaware was written for.
 *
 * Please Note:
 * His label is not connected to the generic macro specified in the compiler settings
 * and need to maintained by the designer independently.
 * ***********************************************************************************************/

#define PINMAP_VERSION  "R30"

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

#ifndef LED_ON
    #define LED_ON 0
#endif
#ifndef LED_OFF
    #define LED_OFF 1
#endif

// Device Pin #28 is RB0
#define CLKI_TRIS    TRISBbits.TRISB0 // GPIO direction register bit
#define CLKI_WR      LATBbits.LATB0 // GPIO port latch register bit
#define CLKI_RD      PORTBbits.RB0 // GPIO port register bit
#define CLKI_ODC     ODCBbits.ODCB0 // GPIO port open drain configuration register bit
#define CLKI_CNPU    CNPUBbits.CNPUB0 // GPIO port pull-up resistor register bit
#define CLKI_CNPD    CNPDBbits.CNPDB0 // GPIO port pull-down resistor register bit
#define CLKI_CNEN0   CNEN0Bbits.CNEN0B0 // GPIO port change notification Enable register bit
#define CLKI_CNSTAT  CNSTATBbits.CNSTATB0 // GPIO port change notification Status register bit
#define CLKI_CNEN1   CNEN1Bbits.CNEN1B0 // GPIO port change notification Edge Select Enable register bit
#define CLKI_CNF     CNFBbits.CNFB0 // GPIO port change notification flag bit register bit
#define CLKI_RP      32 // Number of Remappable Pin
#define CLKI_SET     { asm volatile ("bset _LATB, #0 \n"); }
#define CLKI_CLEAR   { asm volatile ("bclr _LATB, #0 \n"); }
#define CLKI_TOGGLE  { asm volatile ("btg  _LATB, #0 \n"); }
#define CLKI_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define CLKI_ANSEL   _ANSELB0 // analog/digital pin configuration register bit
#define CLKI_ADCCORE  // index starts from zero, last index indicated shared adC core
#define CLKI_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define CLKI_ADC_AN_INPUT 5   // ANx input pin number
#define CLKI_ADCBUF  ADCBUF5 // ADC buffer register for this input
#define CLKI_ADC_ANIE ADIELbits.IE5
#define CLKI_ADC_ANEIE ADEIELbits.EIEN5
#define CLKI_ADC_IF   _ADCAN5IF // interrupt flag bit
#define CLKI_ADC_IE   _ADCAN5IE // interrupt enable bit
#define CLKI_ADC_IP   _ADCAN5IP // interrupt priority for this analog input
#define CLKI_ADC_RDY  _AN5RDY // ADC buffer ready bit
#define _CLKI_ADC_Interrupt _ADCAN5Interrupt
#define CLKI_INIT_ANALOG	{CLKI_ANSEL = 1; CLKI_WR = PINSTATE_HIGH; CLKI_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define CLKI_INIT_OUTPUT  {CLKI_WR = PINSTATE_LOW; CLKI_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define CLKI_INIT_INPUT   {CLKI_WR = PINSTATE_HIGH; CLKI_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #8 is RD15
#define DBGLED_TRIS    TRISDbits.TRISD15 // GPIO direction register bit
#define DBGLED_WR      LATDbits.LATD15 // GPIO port latch register bit
#define DBGLED_RD      PORTDbits.RD15 // GPIO port register bit
#define DBGLED_ODC     ODCDbits.ODCD15 // GPIO port open drain configuration register bit
#define DBGLED_CNPU    CNPUDbits.CNPUD15 // GPIO port pull-up resistor register bit
#define DBGLED_CNPD    CNPDDbits.CNPDD15 // GPIO port pull-down resistor register bit
#define DBGLED_CNEN0   CNEN0Dbits.CNEN0D15 // GPIO port change notification Enable register bit
#define DBGLED_CNSTAT  CNSTATDbits.CNSTATD15 // GPIO port change notification Status register bit
#define DBGLED_CNEN1   CNEN1Dbits.CNEN1D15 // GPIO port change notification Edge Select Enable register bit
#define DBGLED_CNF     CNFDbits.CNFD15 // GPIO port change notification flag bit register bit
#define DBGLED_RP      79 // Number of Remappable Pin
#define DBGLED_SET     { asm volatile ("bset _LATD, #15 \n"); }
#define DBGLED_CLEAR   { asm volatile ("bclr _LATD, #15 \n"); }
#define DBGLED_TOGGLE  { asm volatile ("btg  _LATD, #15 \n"); }
#define DBGLED_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define DBGLED_INIT_OUTPUT  {DBGLED_WR = PINSTATE_LOW; DBGLED_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define DBGLED_INIT_INPUT   {DBGLED_WR = PINSTATE_HIGH; DBGLED_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #21 is RD12
#define DBGPIN_TRIS    TRISDbits.TRISD12 // GPIO direction register bit
#define DBGPIN_WR      LATDbits.LATD12 // GPIO port latch register bit
#define DBGPIN_RD      PORTDbits.RD12 // GPIO port register bit
#define DBGPIN_ODC     ODCDbits.ODCD12 // GPIO port open drain configuration register bit
#define DBGPIN_CNPU    CNPUDbits.CNPUD12 // GPIO port pull-up resistor register bit
#define DBGPIN_CNPD    CNPDDbits.CNPDD12 // GPIO port pull-down resistor register bit
#define DBGPIN_CNEN0   CNEN0Dbits.CNEN0D12 // GPIO port change notification Enable register bit
#define DBGPIN_CNSTAT  CNSTATDbits.CNSTATD12 // GPIO port change notification Status register bit
#define DBGPIN_CNEN1   CNEN1Dbits.CNEN1D12 // GPIO port change notification Edge Select Enable register bit
#define DBGPIN_CNF     CNFDbits.CNFD12 // GPIO port change notification flag bit register bit
#define DBGPIN_RP      76 // Number of Remappable Pin
#define DBGPIN_SET     { asm volatile ("bset _LATD, #12 \n"); }
#define DBGPIN_CLEAR   { asm volatile ("bclr _LATD, #12 \n"); }
#define DBGPIN_TOGGLE  { asm volatile ("btg  _LATD, #12 \n"); }
#define DBGPIN_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define DBGPIN_INIT_OUTPUT  {DBGPIN_WR = PINSTATE_LOW; DBGPIN_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define DBGPIN_INIT_INPUT   {DBGPIN_WR = PINSTATE_HIGH; DBGPIN_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #17 is RA3
#define ECP03_TRIS    TRISAbits.TRISA3 // GPIO direction register bit
#define ECP03_WR      LATAbits.LATA3 // GPIO port latch register bit
#define ECP03_RD      PORTAbits.RA3 // GPIO port register bit
#define ECP03_ODC     ODCAbits.ODCA3 // GPIO port open drain configuration register bit
#define ECP03_CNPU    CNPUAbits.CNPUA3 // GPIO port pull-up resistor register bit
#define ECP03_CNPD    CNPDAbits.CNPDA3 // GPIO port pull-down resistor register bit
#define ECP03_CNEN0   CNEN0Abits.CNEN0A3 // GPIO port change notification Enable register bit
#define ECP03_CNSTAT  CNSTATAbits.CNSTATA3 // GPIO port change notification Status register bit
#define ECP03_CNEN1   CNEN1Abits.CNEN1A3 // GPIO port change notification Edge Select Enable register bit
#define ECP03_CNF     CNFAbits.CNFA3 // GPIO port change notification flag bit register bit
#define ECP03_SET     { asm volatile ("bset _LATA, #3 \n"); }
#define ECP03_CLEAR   { asm volatile ("bclr _LATA, #3 \n"); }
#define ECP03_TOGGLE  { asm volatile ("btg  _LATA, #3 \n"); }
#define ECP03_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP03_ANSEL   _ANSELA3 // analog/digital pin configuration register bit
#define ECP03_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP03_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP03_ADC_AN_INPUT 3   // ANx input pin number
#define ECP03_ADCBUF  ADCBUF3 // ADC buffer register for this input
#define ECP03_ADC_ANIE ADIELbits.IE3
#define ECP03_ADC_ANEIE ADEIELbits.EIEN3
#define ECP03_ADC_IF   _ADCAN3IF // interrupt flag bit
#define ECP03_ADC_IE   _ADCAN3IE // interrupt enable bit
#define ECP03_ADC_IP   _ADCAN3IP // interrupt priority for this analog input
#define ECP03_ADC_RDY  _AN3RDY // ADC buffer ready bit
#define _ECP03_ADC_Interrupt _ADCAN3Interrupt
#define ECP03_INIT_ANALOG	{ECP03_ANSEL = 1; ECP03_WR = PINSTATE_HIGH; ECP03_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP03_INIT_OUTPUT  {ECP03_WR = PINSTATE_LOW; ECP03_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP03_INIT_INPUT   {ECP03_WR = PINSTATE_HIGH; ECP03_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #27 is RC3
#define ECP04_TRIS    TRISCbits.TRISC3 // GPIO direction register bit
#define ECP04_WR      LATCbits.LATC3 // GPIO port latch register bit
#define ECP04_RD      PORTCbits.RC3 // GPIO port register bit
#define ECP04_ODC     ODCCbits.ODCC3 // GPIO port open drain configuration register bit
#define ECP04_CNPU    CNPUCbits.CNPUC3 // GPIO port pull-up resistor register bit
#define ECP04_CNPD    CNPDCbits.CNPDC3 // GPIO port pull-down resistor register bit
#define ECP04_CNEN0   CNEN0Cbits.CNEN0C3 // GPIO port change notification Enable register bit
#define ECP04_CNSTAT  CNSTATCbits.CNSTATC3 // GPIO port change notification Status register bit
#define ECP04_CNEN1   CNEN1Cbits.CNEN1C3 // GPIO port change notification Edge Select Enable register bit
#define ECP04_CNF     CNFCbits.CNFC3 // GPIO port change notification flag bit register bit
#define ECP04_RP      51 // Number of Remappable Pin
#define ECP04_SET     { asm volatile ("bset _LATC, #3 \n"); }
#define ECP04_CLEAR   { asm volatile ("bclr _LATC, #3 \n"); }
#define ECP04_TOGGLE  { asm volatile ("btg  _LATC, #3 \n"); }
#define ECP04_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP04_ANSEL   _ANSELC3 // analog/digital pin configuration register bit
#define ECP04_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP04_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP04_ADC_AN_INPUT 15   // ANx input pin number
#define ECP04_ADCBUF  ADCBUF15 // ADC buffer register for this input
#define ECP04_ADC_ANIE ADIELbits.IE15
#define ECP04_ADC_ANEIE ADEIELbits.EIEN15
#define ECP04_ADC_IF   _ADCAN15IF // interrupt flag bit
#define ECP04_ADC_IE   _ADCAN15IE // interrupt enable bit
#define ECP04_ADC_IP   _ADCAN15IP // interrupt priority for this analog input
#define ECP04_ADC_RDY  _AN15RDY // ADC buffer ready bit
#define _ECP04_ADC_Interrupt _ADCAN15Interrupt
#define ECP04_INIT_ANALOG	{ECP04_ANSEL = 1; ECP04_WR = PINSTATE_HIGH; ECP04_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP04_INIT_OUTPUT  {ECP04_WR = PINSTATE_LOW; ECP04_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP04_INIT_INPUT   {ECP04_WR = PINSTATE_HIGH; ECP04_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #48 is RB8
#define ECP05_TRIS    TRISBbits.TRISB8 // GPIO direction register bit
#define ECP05_WR      LATBbits.LATB8 // GPIO port latch register bit
#define ECP05_RD      PORTBbits.RB8 // GPIO port register bit
#define ECP05_ODC     ODCBbits.ODCB8 // GPIO port open drain configuration register bit
#define ECP05_CNPU    CNPUBbits.CNPUB8 // GPIO port pull-up resistor register bit
#define ECP05_CNPD    CNPDBbits.CNPDB8 // GPIO port pull-down resistor register bit
#define ECP05_CNEN0   CNEN0Bbits.CNEN0B8 // GPIO port change notification Enable register bit
#define ECP05_CNSTAT  CNSTATBbits.CNSTATB8 // GPIO port change notification Status register bit
#define ECP05_CNEN1   CNEN1Bbits.CNEN1B8 // GPIO port change notification Edge Select Enable register bit
#define ECP05_CNF     CNFBbits.CNFB8 // GPIO port change notification flag bit register bit
#define ECP05_RP      40 // Number of Remappable Pin
#define ECP05_SET     { asm volatile ("bset _LATB, #8 \n"); }
#define ECP05_CLEAR   { asm volatile ("bclr _LATB, #8 \n"); }
#define ECP05_TOGGLE  { asm volatile ("btg  _LATB, #8 \n"); }
#define ECP05_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP05_ANSEL   _ANSELB8 // analog/digital pin configuration register bit
#define ECP05_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP05_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP05_ADC_AN_INPUT 10   // ANx input pin number
#define ECP05_ADCBUF  ADCBUF10 // ADC buffer register for this input
#define ECP05_ADC_ANIE ADIELbits.IE10
#define ECP05_ADC_ANEIE ADEIELbits.EIEN10
#define ECP05_ADC_IF   _ADCAN10IF // interrupt flag bit
#define ECP05_ADC_IE   _ADCAN10IE // interrupt enable bit
#define ECP05_ADC_IP   _ADCAN10IP // interrupt priority for this analog input
#define ECP05_ADC_RDY  _AN10RDY // ADC buffer ready bit
#define _ECP05_ADC_Interrupt _ADCAN10Interrupt
#define ECP05_INIT_ANALOG	{ECP05_ANSEL = 1; ECP05_WR = PINSTATE_HIGH; ECP05_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP05_INIT_OUTPUT  {ECP05_WR = PINSTATE_LOW; ECP05_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP05_INIT_INPUT   {ECP05_WR = PINSTATE_HIGH; ECP05_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #33 is RB2
#define ECP06_TRIS    TRISBbits.TRISB2 // GPIO direction register bit
#define ECP06_WR      LATBbits.LATB2 // GPIO port latch register bit
#define ECP06_RD      PORTBbits.RB2 // GPIO port register bit
#define ECP06_ODC     ODCBbits.ODCB2 // GPIO port open drain configuration register bit
#define ECP06_CNPU    CNPUBbits.CNPUB2 // GPIO port pull-up resistor register bit
#define ECP06_CNPD    CNPDBbits.CNPDB2 // GPIO port pull-down resistor register bit
#define ECP06_CNEN0   CNEN0Bbits.CNEN0B2 // GPIO port change notification Enable register bit
#define ECP06_CNSTAT  CNSTATBbits.CNSTATB2 // GPIO port change notification Status register bit
#define ECP06_CNEN1   CNEN1Bbits.CNEN1B2 // GPIO port change notification Edge Select Enable register bit
#define ECP06_CNF     CNFBbits.CNFB2 // GPIO port change notification flag bit register bit
#define ECP06_RP      34 // Number of Remappable Pin
#define ECP06_SET     { asm volatile ("bset _LATB, #2 \n"); }
#define ECP06_CLEAR   { asm volatile ("bclr _LATB, #2 \n"); }
#define ECP06_TOGGLE  { asm volatile ("btg  _LATB, #2 \n"); }
#define ECP06_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP06_ANSEL   _ANSELB2 // analog/digital pin configuration register bit
#define ECP06_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP06_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP06_ADC_AN_INPUT A0   // ANx input pin number
#define ECP06_ADCBUF  ADCBUFA0 // ADC buffer register for this input
#define ECP06_ADC_ANIE ADIEHbits.IEA0
#define ECP06_ADC_ANEIE ADEIEHbits.EIENA0
#define ECP06_ADC_IF   _ADCANA0IF // interrupt flag bit
#define ECP06_ADC_IE   _ADCANA0IE // interrupt enable bit
#define ECP06_ADC_IP   _ADCANA0IP // interrupt priority for this analog input
#define ECP06_ADC_RDY  _ANA0RDY // ADC buffer ready bit
#define _ECP06_ADC_Interrupt _ADCANA0Interrupt
#define ECP06_INIT_ANALOG	{ECP06_ANSEL = 1; ECP06_WR = PINSTATE_HIGH; ECP06_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP06_INIT_OUTPUT  {ECP06_WR = PINSTATE_LOW; ECP06_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP06_INIT_INPUT   {ECP06_WR = PINSTATE_HIGH; ECP06_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #18 is RA4
#define ECP08_TRIS    TRISAbits.TRISA4 // GPIO direction register bit
#define ECP08_WR      LATAbits.LATA4 // GPIO port latch register bit
#define ECP08_RD      PORTAbits.RA4 // GPIO port register bit
#define ECP08_ODC     ODCAbits.ODCA4 // GPIO port open drain configuration register bit
#define ECP08_CNPU    CNPUAbits.CNPUA4 // GPIO port pull-up resistor register bit
#define ECP08_CNPD    CNPDAbits.CNPDA4 // GPIO port pull-down resistor register bit
#define ECP08_CNEN0   CNEN0Abits.CNEN0A4 // GPIO port change notification Enable register bit
#define ECP08_CNSTAT  CNSTATAbits.CNSTATA4 // GPIO port change notification Status register bit
#define ECP08_CNEN1   CNEN1Abits.CNEN1A4 // GPIO port change notification Edge Select Enable register bit
#define ECP08_CNF     CNFAbits.CNFA4 // GPIO port change notification flag bit register bit
#define ECP08_SET     { asm volatile ("bset _LATA, #4 \n"); }
#define ECP08_CLEAR   { asm volatile ("bclr _LATA, #4 \n"); }
#define ECP08_TOGGLE  { asm volatile ("btg  _LATA, #4 \n"); }
#define ECP08_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP08_ANSEL   _ANSELA4 // analog/digital pin configuration register bit
#define ECP08_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP08_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP08_ADC_AN_INPUT 4   // ANx input pin number
#define ECP08_ADCBUF  ADCBUF4 // ADC buffer register for this input
#define ECP08_ADC_ANIE ADIELbits.IE4
#define ECP08_ADC_ANEIE ADEIELbits.EIEN4
#define ECP08_ADC_IF   _ADCAN4IF // interrupt flag bit
#define ECP08_ADC_IE   _ADCAN4IE // interrupt enable bit
#define ECP08_ADC_IP   _ADCAN4IP // interrupt priority for this analog input
#define ECP08_ADC_RDY  _AN4RDY // ADC buffer ready bit
#define _ECP08_ADC_Interrupt _ADCAN4Interrupt
#define ECP08_INIT_ANALOG	{ECP08_ANSEL = 1; ECP08_WR = PINSTATE_HIGH; ECP08_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP08_INIT_OUTPUT  {ECP08_WR = PINSTATE_LOW; ECP08_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP08_INIT_INPUT   {ECP08_WR = PINSTATE_HIGH; ECP08_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #24 is RC6
#define ECP09_TRIS    TRISCbits.TRISC6 // GPIO direction register bit
#define ECP09_WR      LATCbits.LATC6 // GPIO port latch register bit
#define ECP09_RD      PORTCbits.RC6 // GPIO port register bit
#define ECP09_ODC     ODCCbits.ODCC6 // GPIO port open drain configuration register bit
#define ECP09_CNPU    CNPUCbits.CNPUC6 // GPIO port pull-up resistor register bit
#define ECP09_CNPD    CNPDCbits.CNPDC6 // GPIO port pull-down resistor register bit
#define ECP09_CNEN0   CNEN0Cbits.CNEN0C6 // GPIO port change notification Enable register bit
#define ECP09_CNSTAT  CNSTATCbits.CNSTATC6 // GPIO port change notification Status register bit
#define ECP09_CNEN1   CNEN1Cbits.CNEN1C6 // GPIO port change notification Edge Select Enable register bit
#define ECP09_CNF     CNFCbits.CNFC6 // GPIO port change notification flag bit register bit
#define ECP09_RP      54 // Number of Remappable Pin
#define ECP09_SET     { asm volatile ("bset _LATC, #6 \n"); }
#define ECP09_CLEAR   { asm volatile ("bclr _LATC, #6 \n"); }
#define ECP09_TOGGLE  { asm volatile ("btg  _LATC, #6 \n"); }
#define ECP09_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP09_ANSEL   _ANSELC6 // analog/digital pin configuration register bit
#define ECP09_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP09_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP09_ADC_AN_INPUT N1   // ANx input pin number
#define ECP09_ADCBUF  ADCBUFN1 // ADC buffer register for this input
#define ECP09_ADC_ANIE ADIEHbits.IEN1
#define ECP09_ADC_ANEIE ADEIEHbits.EIENN1
#define ECP09_ADC_IF   _ADCANN1IF // interrupt flag bit
#define ECP09_ADC_IE   _ADCANN1IE // interrupt enable bit
#define ECP09_ADC_IP   _ADCANN1IP // interrupt priority for this analog input
#define ECP09_ADC_RDY  _ANN1RDY // ADC buffer ready bit
#define _ECP09_ADC_Interrupt _ADCANN1Interrupt
#define ECP09_INIT_ANALOG	{ECP09_ANSEL = 1; ECP09_WR = PINSTATE_HIGH; ECP09_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP09_INIT_OUTPUT  {ECP09_WR = PINSTATE_LOW; ECP09_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP09_INIT_INPUT   {ECP09_WR = PINSTATE_HIGH; ECP09_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #47 is RB7
#define ECP10_TRIS    TRISBbits.TRISB7 // GPIO direction register bit
#define ECP10_WR      LATBbits.LATB7 // GPIO port latch register bit
#define ECP10_RD      PORTBbits.RB7 // GPIO port register bit
#define ECP10_ODC     ODCBbits.ODCB7 // GPIO port open drain configuration register bit
#define ECP10_CNPU    CNPUBbits.CNPUB7 // GPIO port pull-up resistor register bit
#define ECP10_CNPD    CNPDBbits.CNPDB7 // GPIO port pull-down resistor register bit
#define ECP10_CNEN0   CNEN0Bbits.CNEN0B7 // GPIO port change notification Enable register bit
#define ECP10_CNSTAT  CNSTATBbits.CNSTATB7 // GPIO port change notification Status register bit
#define ECP10_CNEN1   CNEN1Bbits.CNEN1B7 // GPIO port change notification Edge Select Enable register bit
#define ECP10_CNF     CNFBbits.CNFB7 // GPIO port change notification flag bit register bit
#define ECP10_RP      39 // Number of Remappable Pin
#define ECP10_SET     { asm volatile ("bset _LATB, #7 \n"); }
#define ECP10_CLEAR   { asm volatile ("bclr _LATB, #7 \n"); }
#define ECP10_TOGGLE  { asm volatile ("btg  _LATB, #7 \n"); }
#define ECP10_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP10_ANSEL   _ANSELB7 // analog/digital pin configuration register bit
#define ECP10_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP10_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP10_ADC_AN_INPUT 2   // ANx input pin number
#define ECP10_ADCBUF  ADCBUF2 // ADC buffer register for this input
#define ECP10_ADC_ANIE ADIELbits.IE2
#define ECP10_ADC_ANEIE ADEIELbits.EIEN2
#define ECP10_ADC_IF   _ADCAN2IF // interrupt flag bit
#define ECP10_ADC_IE   _ADCAN2IE // interrupt enable bit
#define ECP10_ADC_IP   _ADCAN2IP // interrupt priority for this analog input
#define ECP10_ADC_RDY  _AN2RDY // ADC buffer ready bit
#define _ECP10_ADC_Interrupt _ADCAN2Interrupt
#define ECP10_INIT_ANALOG	{ECP10_ANSEL = 1; ECP10_WR = PINSTATE_HIGH; ECP10_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP10_INIT_OUTPUT  {ECP10_WR = PINSTATE_LOW; ECP10_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP10_INIT_INPUT   {ECP10_WR = PINSTATE_HIGH; ECP10_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #15 is RA1
#define ECP11_TRIS    TRISAbits.TRISA1 // GPIO direction register bit
#define ECP11_WR      LATAbits.LATA1 // GPIO port latch register bit
#define ECP11_RD      PORTAbits.RA1 // GPIO port register bit
#define ECP11_ODC     ODCAbits.ODCA1 // GPIO port open drain configuration register bit
#define ECP11_CNPU    CNPUAbits.CNPUA1 // GPIO port pull-up resistor register bit
#define ECP11_CNPD    CNPDAbits.CNPDA1 // GPIO port pull-down resistor register bit
#define ECP11_CNEN0   CNEN0Abits.CNEN0A1 // GPIO port change notification Enable register bit
#define ECP11_CNSTAT  CNSTATAbits.CNSTATA1 // GPIO port change notification Status register bit
#define ECP11_CNEN1   CNEN1Abits.CNEN1A1 // GPIO port change notification Edge Select Enable register bit
#define ECP11_CNF     CNFAbits.CNFA1 // GPIO port change notification flag bit register bit
#define ECP11_SET     { asm volatile ("bset _LATA, #1 \n"); }
#define ECP11_CLEAR   { asm volatile ("bclr _LATA, #1 \n"); }
#define ECP11_TOGGLE  { asm volatile ("btg  _LATA, #1 \n"); }
#define ECP11_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP11_ANSEL   _ANSELA1 // analog/digital pin configuration register bit
#define ECP11_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP11_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP11_ADC_AN_INPUT A1   // ANx input pin number
#define ECP11_ADCBUF  ADCBUFA1 // ADC buffer register for this input
#define ECP11_ADC_ANIE ADIEHbits.IEA1
#define ECP11_ADC_ANEIE ADEIEHbits.EIENA1
#define ECP11_ADC_IF   _ADCANA1IF // interrupt flag bit
#define ECP11_ADC_IE   _ADCANA1IE // interrupt enable bit
#define ECP11_ADC_IP   _ADCANA1IP // interrupt priority for this analog input
#define ECP11_ADC_RDY  _ANA1RDY // ADC buffer ready bit
#define _ECP11_ADC_Interrupt _ADCANA1Interrupt
#define ECP11_INIT_ANALOG	{ECP11_ANSEL = 1; ECP11_WR = PINSTATE_HIGH; ECP11_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP11_INIT_OUTPUT  {ECP11_WR = PINSTATE_LOW; ECP11_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP11_INIT_INPUT   {ECP11_WR = PINSTATE_HIGH; ECP11_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #14 is RA0
#define ECP12_TRIS    TRISAbits.TRISA0 // GPIO direction register bit
#define ECP12_WR      LATAbits.LATA0 // GPIO port latch register bit
#define ECP12_RD      PORTAbits.RA0 // GPIO port register bit
#define ECP12_ODC     ODCAbits.ODCA0 // GPIO port open drain configuration register bit
#define ECP12_CNPU    CNPUAbits.CNPUA0 // GPIO port pull-up resistor register bit
#define ECP12_CNPD    CNPDAbits.CNPDA0 // GPIO port pull-down resistor register bit
#define ECP12_CNEN0   CNEN0Abits.CNEN0A0 // GPIO port change notification Enable register bit
#define ECP12_CNSTAT  CNSTATAbits.CNSTATA0 // GPIO port change notification Status register bit
#define ECP12_CNEN1   CNEN1Abits.CNEN1A0 // GPIO port change notification Edge Select Enable register bit
#define ECP12_CNF     CNFAbits.CNFA0 // GPIO port change notification flag bit register bit
#define ECP12_SET     { asm volatile ("bset _LATA, #0 \n"); }
#define ECP12_CLEAR   { asm volatile ("bclr _LATA, #0 \n"); }
#define ECP12_TOGGLE  { asm volatile ("btg  _LATA, #0 \n"); }
#define ECP12_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP12_ANSEL   _ANSELA0 // analog/digital pin configuration register bit
#define ECP12_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP12_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP12_ADC_AN_INPUT 0   // ANx input pin number
#define ECP12_ADCBUF  ADCBUF0 // ADC buffer register for this input
#define ECP12_ADC_ANIE ADIELbits.IE0
#define ECP12_ADC_ANEIE ADEIELbits.EIEN0
#define ECP12_ADC_IF   _ADCAN0IF // interrupt flag bit
#define ECP12_ADC_IE   _ADCAN0IE // interrupt enable bit
#define ECP12_ADC_IP   _ADCAN0IP // interrupt priority for this analog input
#define ECP12_ADC_RDY  _AN0RDY // ADC buffer ready bit
#define _ECP12_ADC_Interrupt _ADCAN0Interrupt
#define ECP12_INIT_ANALOG	{ECP12_ANSEL = 1; ECP12_WR = PINSTATE_HIGH; ECP12_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP12_INIT_OUTPUT  {ECP12_WR = PINSTATE_LOW; ECP12_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP12_INIT_INPUT   {ECP12_WR = PINSTATE_HIGH; ECP12_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #30 is RD11
#define ECP13_TRIS    TRISDbits.TRISD11 // GPIO direction register bit
#define ECP13_WR      LATDbits.LATD11 // GPIO port latch register bit
#define ECP13_RD      PORTDbits.RD11 // GPIO port register bit
#define ECP13_ODC     ODCDbits.ODCD11 // GPIO port open drain configuration register bit
#define ECP13_CNPU    CNPUDbits.CNPUD11 // GPIO port pull-up resistor register bit
#define ECP13_CNPD    CNPDDbits.CNPDD11 // GPIO port pull-down resistor register bit
#define ECP13_CNEN0   CNEN0Dbits.CNEN0D11 // GPIO port change notification Enable register bit
#define ECP13_CNSTAT  CNSTATDbits.CNSTATD11 // GPIO port change notification Status register bit
#define ECP13_CNEN1   CNEN1Dbits.CNEN1D11 // GPIO port change notification Edge Select Enable register bit
#define ECP13_CNF     CNFDbits.CNFD11 // GPIO port change notification flag bit register bit
#define ECP13_RP      75 // Number of Remappable Pin
#define ECP13_SET     { asm volatile ("bset _LATD, #11 \n"); }
#define ECP13_CLEAR   { asm volatile ("bclr _LATD, #11 \n"); }
#define ECP13_TOGGLE  { asm volatile ("btg  _LATD, #11 \n"); }
#define ECP13_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP13_ANSEL   _ANSELD11 // analog/digital pin configuration register bit
#define ECP13_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP13_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP13_ADC_AN_INPUT 19   // ANx input pin number
#define ECP13_ADCBUF  ADCBUF19 // ADC buffer register for this input
#define ECP13_ADC_ANIE ADIEHbits.IE19
#define ECP13_ADC_ANEIE ADEIEHbits.EIEN19
#define ECP13_ADC_IF   _ADCAN19IF // interrupt flag bit
#define ECP13_ADC_IE   _ADCAN19IE // interrupt enable bit
#define ECP13_ADC_IP   _ADCAN19IP // interrupt priority for this analog input
#define ECP13_ADC_RDY  _AN19RDY // ADC buffer ready bit
#define _ECP13_ADC_Interrupt _ADCAN19Interrupt
#define ECP13_INIT_ANALOG	{ECP13_ANSEL = 1; ECP13_WR = PINSTATE_HIGH; ECP13_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP13_INIT_OUTPUT  {ECP13_WR = PINSTATE_LOW; ECP13_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP13_INIT_INPUT   {ECP13_WR = PINSTATE_HIGH; ECP13_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #32 is RC7
#define ECP14_TRIS    TRISCbits.TRISC7 // GPIO direction register bit
#define ECP14_WR      LATCbits.LATC7 // GPIO port latch register bit
#define ECP14_RD      PORTCbits.RC7 // GPIO port register bit
#define ECP14_ODC     ODCCbits.ODCC7 // GPIO port open drain configuration register bit
#define ECP14_CNPU    CNPUCbits.CNPUC7 // GPIO port pull-up resistor register bit
#define ECP14_CNPD    CNPDCbits.CNPDC7 // GPIO port pull-down resistor register bit
#define ECP14_CNEN0   CNEN0Cbits.CNEN0C7 // GPIO port change notification Enable register bit
#define ECP14_CNSTAT  CNSTATCbits.CNSTATC7 // GPIO port change notification Status register bit
#define ECP14_CNEN1   CNEN1Cbits.CNEN1C7 // GPIO port change notification Edge Select Enable register bit
#define ECP14_CNF     CNFCbits.CNFC7 // GPIO port change notification flag bit register bit
#define ECP14_RP      55 // Number of Remappable Pin
#define ECP14_SET     { asm volatile ("bset _LATC, #7 \n"); }
#define ECP14_CLEAR   { asm volatile ("bclr _LATC, #7 \n"); }
#define ECP14_TOGGLE  { asm volatile ("btg  _LATC, #7 \n"); }
#define ECP14_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP14_ANSEL   _ANSELC7 // analog/digital pin configuration register bit
#define ECP14_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP14_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP14_ADC_AN_INPUT 16   // ANx input pin number
#define ECP14_ADCBUF  ADCBUF16 // ADC buffer register for this input
#define ECP14_ADC_ANIE ADIEHbits.IE16
#define ECP14_ADC_ANEIE ADEIEHbits.EIEN16
#define ECP14_ADC_IF   _ADCAN16IF // interrupt flag bit
#define ECP14_ADC_IE   _ADCAN16IE // interrupt enable bit
#define ECP14_ADC_IP   _ADCAN16IP // interrupt priority for this analog input
#define ECP14_ADC_RDY  _AN16RDY // ADC buffer ready bit
#define _ECP14_ADC_Interrupt _ADCAN16Interrupt
#define ECP14_INIT_ANALOG	{ECP14_ANSEL = 1; ECP14_WR = PINSTATE_HIGH; ECP14_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP14_INIT_OUTPUT  {ECP14_WR = PINSTATE_LOW; ECP14_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP14_INIT_INPUT   {ECP14_WR = PINSTATE_HIGH; ECP14_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #31 is RD10
#define ECP15_TRIS    TRISDbits.TRISD10 // GPIO direction register bit
#define ECP15_WR      LATDbits.LATD10 // GPIO port latch register bit
#define ECP15_RD      PORTDbits.RD10 // GPIO port register bit
#define ECP15_ODC     ODCDbits.ODCD10 // GPIO port open drain configuration register bit
#define ECP15_CNPU    CNPUDbits.CNPUD10 // GPIO port pull-up resistor register bit
#define ECP15_CNPD    CNPDDbits.CNPDD10 // GPIO port pull-down resistor register bit
#define ECP15_CNEN0   CNEN0Dbits.CNEN0D10 // GPIO port change notification Enable register bit
#define ECP15_CNSTAT  CNSTATDbits.CNSTATD10 // GPIO port change notification Status register bit
#define ECP15_CNEN1   CNEN1Dbits.CNEN1D10 // GPIO port change notification Edge Select Enable register bit
#define ECP15_CNF     CNFDbits.CNFD10 // GPIO port change notification flag bit register bit
#define ECP15_RP      74 // Number of Remappable Pin
#define ECP15_SET     { asm volatile ("bset _LATD, #10 \n"); }
#define ECP15_CLEAR   { asm volatile ("bclr _LATD, #10 \n"); }
#define ECP15_TOGGLE  { asm volatile ("btg  _LATD, #10 \n"); }
#define ECP15_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP15_ANSEL   _ANSELD10 // analog/digital pin configuration register bit
#define ECP15_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP15_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP15_ADC_AN_INPUT 18   // ANx input pin number
#define ECP15_ADCBUF  ADCBUF18 // ADC buffer register for this input
#define ECP15_ADC_ANIE ADIEHbits.IE18
#define ECP15_ADC_ANEIE ADEIEHbits.EIEN18
#define ECP15_ADC_IF   _ADCAN18IF // interrupt flag bit
#define ECP15_ADC_IE   _ADCAN18IE // interrupt enable bit
#define ECP15_ADC_IP   _ADCAN18IP // interrupt priority for this analog input
#define ECP15_ADC_RDY  _AN18RDY // ADC buffer ready bit
#define _ECP15_ADC_Interrupt _ADCAN18Interrupt
#define ECP15_INIT_ANALOG	{ECP15_ANSEL = 1; ECP15_WR = PINSTATE_HIGH; ECP15_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP15_INIT_OUTPUT  {ECP15_WR = PINSTATE_LOW; ECP15_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP15_INIT_INPUT   {ECP15_WR = PINSTATE_HIGH; ECP15_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #13 is RC0
#define ECP16_TRIS    TRISCbits.TRISC0 // GPIO direction register bit
#define ECP16_WR      LATCbits.LATC0 // GPIO port latch register bit
#define ECP16_RD      PORTCbits.RC0 // GPIO port register bit
#define ECP16_ODC     ODCCbits.ODCC0 // GPIO port open drain configuration register bit
#define ECP16_CNPU    CNPUCbits.CNPUC0 // GPIO port pull-up resistor register bit
#define ECP16_CNPD    CNPDCbits.CNPDC0 // GPIO port pull-down resistor register bit
#define ECP16_CNEN0   CNEN0Cbits.CNEN0C0 // GPIO port change notification Enable register bit
#define ECP16_CNSTAT  CNSTATCbits.CNSTATC0 // GPIO port change notification Status register bit
#define ECP16_CNEN1   CNEN1Cbits.CNEN1C0 // GPIO port change notification Edge Select Enable register bit
#define ECP16_CNF     CNFCbits.CNFC0 // GPIO port change notification flag bit register bit
#define ECP16_RP      48 // Number of Remappable Pin
#define ECP16_SET     { asm volatile ("bset _LATC, #0 \n"); }
#define ECP16_CLEAR   { asm volatile ("bclr _LATC, #0 \n"); }
#define ECP16_TOGGLE  { asm volatile ("btg  _LATC, #0 \n"); }
#define ECP16_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP16_ANSEL   _ANSELC0 // analog/digital pin configuration register bit
#define ECP16_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP16_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP16_ADC_AN_INPUT N0   // ANx input pin number
#define ECP16_ADCBUF  ADCBUFN0 // ADC buffer register for this input
#define ECP16_ADC_ANIE ADIEHbits.IEN0
#define ECP16_ADC_ANEIE ADEIEHbits.EIENN0
#define ECP16_ADC_IF   _ADCANN0IF // interrupt flag bit
#define ECP16_ADC_IE   _ADCANN0IE // interrupt enable bit
#define ECP16_ADC_IP   _ADCANN0IP // interrupt priority for this analog input
#define ECP16_ADC_RDY  _ANN0RDY // ADC buffer ready bit
#define _ECP16_ADC_Interrupt _ADCANN0Interrupt
#define ECP16_INIT_ANALOG	{ECP16_ANSEL = 1; ECP16_WR = PINSTATE_HIGH; ECP16_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP16_INIT_OUTPUT  {ECP16_WR = PINSTATE_LOW; ECP16_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP16_INIT_INPUT   {ECP16_WR = PINSTATE_HIGH; ECP16_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #23 is RC2
#define ECP17_TRIS    TRISCbits.TRISC2 // GPIO direction register bit
#define ECP17_WR      LATCbits.LATC2 // GPIO port latch register bit
#define ECP17_RD      PORTCbits.RC2 // GPIO port register bit
#define ECP17_ODC     ODCCbits.ODCC2 // GPIO port open drain configuration register bit
#define ECP17_CNPU    CNPUCbits.CNPUC2 // GPIO port pull-up resistor register bit
#define ECP17_CNPD    CNPDCbits.CNPDC2 // GPIO port pull-down resistor register bit
#define ECP17_CNEN0   CNEN0Cbits.CNEN0C2 // GPIO port change notification Enable register bit
#define ECP17_CNSTAT  CNSTATCbits.CNSTATC2 // GPIO port change notification Status register bit
#define ECP17_CNEN1   CNEN1Cbits.CNEN1C2 // GPIO port change notification Edge Select Enable register bit
#define ECP17_CNF     CNFCbits.CNFC2 // GPIO port change notification flag bit register bit
#define ECP17_RP      50 // Number of Remappable Pin
#define ECP17_SET     { asm volatile ("bset _LATC, #2 \n"); }
#define ECP17_CLEAR   { asm volatile ("bclr _LATC, #2 \n"); }
#define ECP17_TOGGLE  { asm volatile ("btg  _LATC, #2 \n"); }
#define ECP17_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP17_ANSEL   _ANSELC2 // analog/digital pin configuration register bit
#define ECP17_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP17_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP17_ADC_AN_INPUT 14   // ANx input pin number
#define ECP17_ADCBUF  ADCBUF14 // ADC buffer register for this input
#define ECP17_ADC_ANIE ADIELbits.IE14
#define ECP17_ADC_ANEIE ADEIELbits.EIEN14
#define ECP17_ADC_IF   _ADCAN14IF // interrupt flag bit
#define ECP17_ADC_IE   _ADCAN14IE // interrupt enable bit
#define ECP17_ADC_IP   _ADCAN14IP // interrupt priority for this analog input
#define ECP17_ADC_RDY  _AN14RDY // ADC buffer ready bit
#define _ECP17_ADC_Interrupt _ADCAN14Interrupt
#define ECP17_INIT_ANALOG	{ECP17_ANSEL = 1; ECP17_WR = PINSTATE_HIGH; ECP17_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP17_INIT_OUTPUT  {ECP17_WR = PINSTATE_LOW; ECP17_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP17_INIT_INPUT   {ECP17_WR = PINSTATE_HIGH; ECP17_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #22 is RC1
#define ECP18_TRIS    TRISCbits.TRISC1 // GPIO direction register bit
#define ECP18_WR      LATCbits.LATC1 // GPIO port latch register bit
#define ECP18_RD      PORTCbits.RC1 // GPIO port register bit
#define ECP18_ODC     ODCCbits.ODCC1 // GPIO port open drain configuration register bit
#define ECP18_CNPU    CNPUCbits.CNPUC1 // GPIO port pull-up resistor register bit
#define ECP18_CNPD    CNPDCbits.CNPDC1 // GPIO port pull-down resistor register bit
#define ECP18_CNEN0   CNEN0Cbits.CNEN0C1 // GPIO port change notification Enable register bit
#define ECP18_CNSTAT  CNSTATCbits.CNSTATC1 // GPIO port change notification Status register bit
#define ECP18_CNEN1   CNEN1Cbits.CNEN1C1 // GPIO port change notification Edge Select Enable register bit
#define ECP18_CNF     CNFCbits.CNFC1 // GPIO port change notification flag bit register bit
#define ECP18_RP      49 // Number of Remappable Pin
#define ECP18_SET     { asm volatile ("bset _LATC, #1 \n"); }
#define ECP18_CLEAR   { asm volatile ("bclr _LATC, #1 \n"); }
#define ECP18_TOGGLE  { asm volatile ("btg  _LATC, #1 \n"); }
#define ECP18_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP18_ANSEL   _ANSELC1 // analog/digital pin configuration register bit
#define ECP18_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP18_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP18_ADC_AN_INPUT 13   // ANx input pin number
#define ECP18_ADCBUF  ADCBUF13 // ADC buffer register for this input
#define ECP18_ADC_ANIE ADIELbits.IE13
#define ECP18_ADC_ANEIE ADEIELbits.EIEN13
#define ECP18_ADC_IF   _ADCAN13IF // interrupt flag bit
#define ECP18_ADC_IE   _ADCAN13IE // interrupt enable bit
#define ECP18_ADC_IP   _ADCAN13IP // interrupt priority for this analog input
#define ECP18_ADC_RDY  _AN13RDY // ADC buffer ready bit
#define _ECP18_ADC_Interrupt _ADCAN13Interrupt
#define ECP18_INIT_ANALOG	{ECP18_ANSEL = 1; ECP18_WR = PINSTATE_HIGH; ECP18_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP18_INIT_OUTPUT  {ECP18_WR = PINSTATE_LOW; ECP18_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP18_INIT_INPUT   {ECP18_WR = PINSTATE_HIGH; ECP18_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #16 is RA2
#define ECP19_TRIS    TRISAbits.TRISA2 // GPIO direction register bit
#define ECP19_WR      LATAbits.LATA2 // GPIO port latch register bit
#define ECP19_RD      PORTAbits.RA2 // GPIO port register bit
#define ECP19_ODC     ODCAbits.ODCA2 // GPIO port open drain configuration register bit
#define ECP19_CNPU    CNPUAbits.CNPUA2 // GPIO port pull-up resistor register bit
#define ECP19_CNPD    CNPDAbits.CNPDA2 // GPIO port pull-down resistor register bit
#define ECP19_CNEN0   CNEN0Abits.CNEN0A2 // GPIO port change notification Enable register bit
#define ECP19_CNSTAT  CNSTATAbits.CNSTATA2 // GPIO port change notification Status register bit
#define ECP19_CNEN1   CNEN1Abits.CNEN1A2 // GPIO port change notification Edge Select Enable register bit
#define ECP19_CNF     CNFAbits.CNFA2 // GPIO port change notification flag bit register bit
#define ECP19_SET     { asm volatile ("bset _LATA, #2 \n"); }
#define ECP19_CLEAR   { asm volatile ("bclr _LATA, #2 \n"); }
#define ECP19_TOGGLE  { asm volatile ("btg  _LATA, #2 \n"); }
#define ECP19_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP19_ANSEL   _ANSELA2 // analog/digital pin configuration register bit
#define ECP19_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP19_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP19_ADC_AN_INPUT 9   // ANx input pin number
#define ECP19_ADCBUF  ADCBUF9 // ADC buffer register for this input
#define ECP19_ADC_ANIE ADIELbits.IE9
#define ECP19_ADC_ANEIE ADEIELbits.EIEN9
#define ECP19_ADC_IF   _ADCAN9IF // interrupt flag bit
#define ECP19_ADC_IE   _ADCAN9IE // interrupt enable bit
#define ECP19_ADC_IP   _ADCAN9IP // interrupt priority for this analog input
#define ECP19_ADC_RDY  _AN9RDY // ADC buffer ready bit
#define _ECP19_ADC_Interrupt _ADCAN9Interrupt
#define ECP19_INIT_ANALOG	{ECP19_ANSEL = 1; ECP19_WR = PINSTATE_HIGH; ECP19_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP19_INIT_OUTPUT  {ECP19_WR = PINSTATE_LOW; ECP19_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP19_INIT_INPUT   {ECP19_WR = PINSTATE_HIGH; ECP19_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #29 is RB1
#define ECP20_TRIS    TRISBbits.TRISB1 // GPIO direction register bit
#define ECP20_WR      LATBbits.LATB1 // GPIO port latch register bit
#define ECP20_RD      PORTBbits.RB1 // GPIO port register bit
#define ECP20_ODC     ODCBbits.ODCB1 // GPIO port open drain configuration register bit
#define ECP20_CNPU    CNPUBbits.CNPUB1 // GPIO port pull-up resistor register bit
#define ECP20_CNPD    CNPDBbits.CNPDB1 // GPIO port pull-down resistor register bit
#define ECP20_CNEN0   CNEN0Bbits.CNEN0B1 // GPIO port change notification Enable register bit
#define ECP20_CNSTAT  CNSTATBbits.CNSTATB1 // GPIO port change notification Status register bit
#define ECP20_CNEN1   CNEN1Bbits.CNEN1B1 // GPIO port change notification Edge Select Enable register bit
#define ECP20_CNF     CNFBbits.CNFB1 // GPIO port change notification flag bit register bit
#define ECP20_RP      33 // Number of Remappable Pin
#define ECP20_SET     { asm volatile ("bset _LATB, #1 \n"); }
#define ECP20_CLEAR   { asm volatile ("bclr _LATB, #1 \n"); }
#define ECP20_TOGGLE  { asm volatile ("btg  _LATB, #1 \n"); }
#define ECP20_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP20_ANSEL   _ANSELB1 // analog/digital pin configuration register bit
#define ECP20_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP20_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP20_ADC_AN_INPUT 6   // ANx input pin number
#define ECP20_ADCBUF  ADCBUF6 // ADC buffer register for this input
#define ECP20_ADC_ANIE ADIELbits.IE6
#define ECP20_ADC_ANEIE ADEIELbits.EIEN6
#define ECP20_ADC_IF   _ADCAN6IF // interrupt flag bit
#define ECP20_ADC_IE   _ADCAN6IE // interrupt enable bit
#define ECP20_ADC_IP   _ADCAN6IP // interrupt priority for this analog input
#define ECP20_ADC_RDY  _AN6RDY // ADC buffer ready bit
#define _ECP20_ADC_Interrupt _ADCAN6Interrupt
#define ECP20_INIT_ANALOG	{ECP20_ANSEL = 1; ECP20_WR = PINSTATE_HIGH; ECP20_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP20_INIT_OUTPUT  {ECP20_WR = PINSTATE_LOW; ECP20_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP20_INIT_INPUT   {ECP20_WR = PINSTATE_HIGH; ECP20_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #49 is RB9
#define ECP23_TRIS    TRISBbits.TRISB9 // GPIO direction register bit
#define ECP23_WR      LATBbits.LATB9 // GPIO port latch register bit
#define ECP23_RD      PORTBbits.RB9 // GPIO port register bit
#define ECP23_ODC     ODCBbits.ODCB9 // GPIO port open drain configuration register bit
#define ECP23_CNPU    CNPUBbits.CNPUB9 // GPIO port pull-up resistor register bit
#define ECP23_CNPD    CNPDBbits.CNPDB9 // GPIO port pull-down resistor register bit
#define ECP23_CNEN0   CNEN0Bbits.CNEN0B9 // GPIO port change notification Enable register bit
#define ECP23_CNSTAT  CNSTATBbits.CNSTATB9 // GPIO port change notification Status register bit
#define ECP23_CNEN1   CNEN1Bbits.CNEN1B9 // GPIO port change notification Edge Select Enable register bit
#define ECP23_CNF     CNFBbits.CNFB9 // GPIO port change notification flag bit register bit
#define ECP23_RP      41 // Number of Remappable Pin
#define ECP23_SET     { asm volatile ("bset _LATB, #9 \n"); }
#define ECP23_CLEAR   { asm volatile ("bclr _LATB, #9 \n"); }
#define ECP23_TOGGLE  { asm volatile ("btg  _LATB, #9 \n"); }
#define ECP23_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP23_ANSEL   _ANSELB9 // analog/digital pin configuration register bit
#define ECP23_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP23_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP23_ADC_AN_INPUT 11   // ANx input pin number
#define ECP23_ADCBUF  ADCBUF11 // ADC buffer register for this input
#define ECP23_ADC_ANIE ADIELbits.IE11
#define ECP23_ADC_ANEIE ADEIELbits.EIEN11
#define ECP23_ADC_IF   _ADCAN11IF // interrupt flag bit
#define ECP23_ADC_IE   _ADCAN11IE // interrupt enable bit
#define ECP23_ADC_IP   _ADCAN11IP // interrupt priority for this analog input
#define ECP23_ADC_RDY  _AN11RDY // ADC buffer ready bit
#define _ECP23_ADC_Interrupt _ADCAN11Interrupt
#define ECP23_INIT_ANALOG	{ECP23_ANSEL = 1; ECP23_WR = PINSTATE_HIGH; ECP23_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP23_INIT_OUTPUT  {ECP23_WR = PINSTATE_LOW; ECP23_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP23_INIT_INPUT   {ECP23_WR = PINSTATE_HIGH; ECP23_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #36 is RC8
#define ECP24_TRIS    TRISCbits.TRISC8 // GPIO direction register bit
#define ECP24_WR      LATCbits.LATC8 // GPIO port latch register bit
#define ECP24_RD      PORTCbits.RC8 // GPIO port register bit
#define ECP24_ODC     ODCCbits.ODCC8 // GPIO port open drain configuration register bit
#define ECP24_CNPU    CNPUCbits.CNPUC8 // GPIO port pull-up resistor register bit
#define ECP24_CNPD    CNPDCbits.CNPDC8 // GPIO port pull-down resistor register bit
#define ECP24_CNEN0   CNEN0Cbits.CNEN0C8 // GPIO port change notification Enable register bit
#define ECP24_CNSTAT  CNSTATCbits.CNSTATC8 // GPIO port change notification Status register bit
#define ECP24_CNEN1   CNEN1Cbits.CNEN1C8 // GPIO port change notification Edge Select Enable register bit
#define ECP24_CNF     CNFCbits.CNFC8 // GPIO port change notification flag bit register bit
#define ECP24_RP      56 // Number of Remappable Pin
#define ECP24_SET     { asm volatile ("bset _LATC, #8 \n"); }
#define ECP24_CLEAR   { asm volatile ("bclr _LATC, #8 \n"); }
#define ECP24_TOGGLE  { asm volatile ("btg  _LATC, #8 \n"); }
#define ECP24_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP24_INIT_OUTPUT  {ECP24_WR = PINSTATE_LOW; ECP24_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP24_INIT_INPUT   {ECP24_WR = PINSTATE_HIGH; ECP24_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #52 is RC10
#define ECP25_TRIS    TRISCbits.TRISC10 // GPIO direction register bit
#define ECP25_WR      LATCbits.LATC10 // GPIO port latch register bit
#define ECP25_RD      PORTCbits.RC10 // GPIO port register bit
#define ECP25_ODC     ODCCbits.ODCC10 // GPIO port open drain configuration register bit
#define ECP25_CNPU    CNPUCbits.CNPUC10 // GPIO port pull-up resistor register bit
#define ECP25_CNPD    CNPDCbits.CNPDC10 // GPIO port pull-down resistor register bit
#define ECP25_CNEN0   CNEN0Cbits.CNEN0C10 // GPIO port change notification Enable register bit
#define ECP25_CNSTAT  CNSTATCbits.CNSTATC10 // GPIO port change notification Status register bit
#define ECP25_CNEN1   CNEN1Cbits.CNEN1C10 // GPIO port change notification Edge Select Enable register bit
#define ECP25_CNF     CNFCbits.CNFC10 // GPIO port change notification flag bit register bit
#define ECP25_RP      58 // Number of Remappable Pin
#define ECP25_SET     { asm volatile ("bset _LATC, #10 \n"); }
#define ECP25_CLEAR   { asm volatile ("bclr _LATC, #10 \n"); }
#define ECP25_TOGGLE  { asm volatile ("btg  _LATC, #10 \n"); }
#define ECP25_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP25_INIT_OUTPUT  {ECP25_WR = PINSTATE_LOW; ECP25_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP25_INIT_INPUT   {ECP25_WR = PINSTATE_HIGH; ECP25_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP25_PGx_CHANNEL  7 // PWM channel index
#define ECP25_PGx_PER      PG7PER // PWM channel period register
#define ECP25_PGx_PHASE    PG7PHASE // PWM channel phase register
#define ECP25_PGx_DC       PG7DC // PWM channel duty cycle register
#define ECP25_PGx_OVRENH   PG7IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP25_PGx_PENH     PG7IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP25_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP25_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define ECP25_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define ECP25_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register

// Device Pin #11 is RD14
#define ECP26_TRIS    TRISDbits.TRISD14 // GPIO direction register bit
#define ECP26_WR      LATDbits.LATD14 // GPIO port latch register bit
#define ECP26_RD      PORTDbits.RD14 // GPIO port register bit
#define ECP26_ODC     ODCDbits.ODCD14 // GPIO port open drain configuration register bit
#define ECP26_CNPU    CNPUDbits.CNPUD14 // GPIO port pull-up resistor register bit
#define ECP26_CNPD    CNPDDbits.CNPDD14 // GPIO port pull-down resistor register bit
#define ECP26_CNEN0   CNEN0Dbits.CNEN0D14 // GPIO port change notification Enable register bit
#define ECP26_CNSTAT  CNSTATDbits.CNSTATD14 // GPIO port change notification Status register bit
#define ECP26_CNEN1   CNEN1Dbits.CNEN1D14 // GPIO port change notification Edge Select Enable register bit
#define ECP26_CNF     CNFDbits.CNFD14 // GPIO port change notification flag bit register bit
#define ECP26_RP      78 // Number of Remappable Pin
#define ECP26_SET     { asm volatile ("bset _LATD, #14 \n"); }
#define ECP26_CLEAR   { asm volatile ("bclr _LATD, #14 \n"); }
#define ECP26_TOGGLE  { asm volatile ("btg  _LATD, #14 \n"); }
#define ECP26_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP26_INIT_OUTPUT  {ECP26_WR = PINSTATE_LOW; ECP26_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP26_INIT_INPUT   {ECP26_WR = PINSTATE_HIGH; ECP26_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #53 is RC11
#define ECP27_TRIS    TRISCbits.TRISC11 // GPIO direction register bit
#define ECP27_WR      LATCbits.LATC11 // GPIO port latch register bit
#define ECP27_RD      PORTCbits.RC11 // GPIO port register bit
#define ECP27_ODC     ODCCbits.ODCC11 // GPIO port open drain configuration register bit
#define ECP27_CNPU    CNPUCbits.CNPUC11 // GPIO port pull-up resistor register bit
#define ECP27_CNPD    CNPDCbits.CNPDC11 // GPIO port pull-down resistor register bit
#define ECP27_CNEN0   CNEN0Cbits.CNEN0C11 // GPIO port change notification Enable register bit
#define ECP27_CNSTAT  CNSTATCbits.CNSTATC11 // GPIO port change notification Status register bit
#define ECP27_CNEN1   CNEN1Cbits.CNEN1C11 // GPIO port change notification Edge Select Enable register bit
#define ECP27_CNF     CNFCbits.CNFC11 // GPIO port change notification flag bit register bit
#define ECP27_RP      59 // Number of Remappable Pin
#define ECP27_SET     { asm volatile ("bset _LATC, #11 \n"); }
#define ECP27_CLEAR   { asm volatile ("bclr _LATC, #11 \n"); }
#define ECP27_TOGGLE  { asm volatile ("btg  _LATC, #11 \n"); }
#define ECP27_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP27_INIT_OUTPUT  {ECP27_WR = PINSTATE_LOW; ECP27_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP27_INIT_INPUT   {ECP27_WR = PINSTATE_HIGH; ECP27_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP27_PGx_CHANNEL  7 // PWM channel index
#define ECP27_PGx_PER      PG7PER // PWM channel period register
#define ECP27_PGx_PHASE    PG7PHASE // PWM channel phase register
#define ECP27_PGx_DC       PG7DC // PWM channel duty cycle register
#define ECP27_PGx_OVRENL   PG7IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP27_PGx_PENL     PG7IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP27_PGxUPDREQ    PG7STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP27_PGxTRIGA     PG7TRIGA // PWM channel ADC trigger A register
#define ECP27_PGxTRIGB     PG7TRIGB // PWM channel ADC trigger A register
#define ECP27_PGxTRIGC     PG7TRIGC // PWM channel ADC trigger A register

// Device Pin #38 is RD9
#define ECP28_TRIS    TRISDbits.TRISD9 // GPIO direction register bit
#define ECP28_WR      LATDbits.LATD9 // GPIO port latch register bit
#define ECP28_RD      PORTDbits.RD9 // GPIO port register bit
#define ECP28_ODC     ODCDbits.ODCD9 // GPIO port open drain configuration register bit
#define ECP28_CNPU    CNPUDbits.CNPUD9 // GPIO port pull-up resistor register bit
#define ECP28_CNPD    CNPDDbits.CNPDD9 // GPIO port pull-down resistor register bit
#define ECP28_CNEN0   CNEN0Dbits.CNEN0D9 // GPIO port change notification Enable register bit
#define ECP28_CNSTAT  CNSTATDbits.CNSTATD9 // GPIO port change notification Status register bit
#define ECP28_CNEN1   CNEN1Dbits.CNEN1D9 // GPIO port change notification Edge Select Enable register bit
#define ECP28_CNF     CNFDbits.CNFD9 // GPIO port change notification flag bit register bit
#define ECP28_RP      73 // Number of Remappable Pin
#define ECP28_SET     { asm volatile ("bset _LATD, #9 \n"); }
#define ECP28_CLEAR   { asm volatile ("bclr _LATD, #9 \n"); }
#define ECP28_TOGGLE  { asm volatile ("btg  _LATD, #9 \n"); }
#define ECP28_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP28_INIT_OUTPUT  {ECP28_WR = PINSTATE_LOW; ECP28_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP28_INIT_INPUT   {ECP28_WR = PINSTATE_HIGH; ECP28_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #5 is RC14
#define ECP31_TRIS    TRISCbits.TRISC14 // GPIO direction register bit
#define ECP31_WR      LATCbits.LATC14 // GPIO port latch register bit
#define ECP31_RD      PORTCbits.RC14 // GPIO port register bit
#define ECP31_ODC     ODCCbits.ODCC14 // GPIO port open drain configuration register bit
#define ECP31_CNPU    CNPUCbits.CNPUC14 // GPIO port pull-up resistor register bit
#define ECP31_CNPD    CNPDCbits.CNPDC14 // GPIO port pull-down resistor register bit
#define ECP31_CNEN0   CNEN0Cbits.CNEN0C14 // GPIO port change notification Enable register bit
#define ECP31_CNSTAT  CNSTATCbits.CNSTATC14 // GPIO port change notification Status register bit
#define ECP31_CNEN1   CNEN1Cbits.CNEN1C14 // GPIO port change notification Edge Select Enable register bit
#define ECP31_CNF     CNFCbits.CNFC14 // GPIO port change notification flag bit register bit
#define ECP31_RP      62 // Number of Remappable Pin
#define ECP31_SET     { asm volatile ("bset _LATC, #14 \n"); }
#define ECP31_CLEAR   { asm volatile ("bclr _LATC, #14 \n"); }
#define ECP31_TOGGLE  { asm volatile ("btg  _LATC, #14 \n"); }
#define ECP31_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP31_INIT_OUTPUT  {ECP31_WR = PINSTATE_LOW; ECP31_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP31_INIT_INPUT   {ECP31_WR = PINSTATE_HIGH; ECP31_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP31_PGx_CHANNEL  6 // PWM channel index
#define ECP31_PGx_PER      PG6PER // PWM channel period register
#define ECP31_PGx_PHASE    PG6PHASE // PWM channel phase register
#define ECP31_PGx_DC       PG6DC // PWM channel duty cycle register
#define ECP31_PGx_OVRENH   PG6IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP31_PGx_PENH     PG6IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP31_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP31_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define ECP31_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define ECP31_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register

// Device Pin #37 is RC9
#define ECP32_TRIS    TRISCbits.TRISC9 // GPIO direction register bit
#define ECP32_WR      LATCbits.LATC9 // GPIO port latch register bit
#define ECP32_RD      PORTCbits.RC9 // GPIO port register bit
#define ECP32_ODC     ODCCbits.ODCC9 // GPIO port open drain configuration register bit
#define ECP32_CNPU    CNPUCbits.CNPUC9 // GPIO port pull-up resistor register bit
#define ECP32_CNPD    CNPDCbits.CNPDC9 // GPIO port pull-down resistor register bit
#define ECP32_CNEN0   CNEN0Cbits.CNEN0C9 // GPIO port change notification Enable register bit
#define ECP32_CNSTAT  CNSTATCbits.CNSTATC9 // GPIO port change notification Status register bit
#define ECP32_CNEN1   CNEN1Cbits.CNEN1C9 // GPIO port change notification Edge Select Enable register bit
#define ECP32_CNF     CNFCbits.CNFC9 // GPIO port change notification flag bit register bit
#define ECP32_RP      57 // Number of Remappable Pin
#define ECP32_SET     { asm volatile ("bset _LATC, #9 \n"); }
#define ECP32_CLEAR   { asm volatile ("bclr _LATC, #9 \n"); }
#define ECP32_TOGGLE  { asm volatile ("btg  _LATC, #9 \n"); }
#define ECP32_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP32_INIT_OUTPUT  {ECP32_WR = PINSTATE_LOW; ECP32_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP32_INIT_INPUT   {ECP32_WR = PINSTATE_HIGH; ECP32_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #6 is RC15
#define ECP33_TRIS    TRISCbits.TRISC15 // GPIO direction register bit
#define ECP33_WR      LATCbits.LATC15 // GPIO port latch register bit
#define ECP33_RD      PORTCbits.RC15 // GPIO port register bit
#define ECP33_ODC     ODCCbits.ODCC15 // GPIO port open drain configuration register bit
#define ECP33_CNPU    CNPUCbits.CNPUC15 // GPIO port pull-up resistor register bit
#define ECP33_CNPD    CNPDCbits.CNPDC15 // GPIO port pull-down resistor register bit
#define ECP33_CNEN0   CNEN0Cbits.CNEN0C15 // GPIO port change notification Enable register bit
#define ECP33_CNSTAT  CNSTATCbits.CNSTATC15 // GPIO port change notification Status register bit
#define ECP33_CNEN1   CNEN1Cbits.CNEN1C15 // GPIO port change notification Edge Select Enable register bit
#define ECP33_CNF     CNFCbits.CNFC15 // GPIO port change notification flag bit register bit
#define ECP33_RP      63 // Number of Remappable Pin
#define ECP33_SET     { asm volatile ("bset _LATC, #15 \n"); }
#define ECP33_CLEAR   { asm volatile ("bclr _LATC, #15 \n"); }
#define ECP33_TOGGLE  { asm volatile ("btg  _LATC, #15 \n"); }
#define ECP33_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP33_INIT_OUTPUT  {ECP33_WR = PINSTATE_LOW; ECP33_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP33_INIT_INPUT   {ECP33_WR = PINSTATE_HIGH; ECP33_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP33_PGx_CHANNEL  6 // PWM channel index
#define ECP33_PGx_PER      PG6PER // PWM channel period register
#define ECP33_PGx_PHASE    PG6PHASE // PWM channel phase register
#define ECP33_PGx_DC       PG6DC // PWM channel duty cycle register
#define ECP33_PGx_OVRENL   PG6IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP33_PGx_PENL     PG6IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP33_PGxUPDREQ    PG6STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP33_PGxTRIGA     PG6TRIGA // PWM channel ADC trigger A register
#define ECP33_PGxTRIGB     PG6TRIGB // PWM channel ADC trigger A register
#define ECP33_PGxTRIGC     PG6TRIGC // PWM channel ADC trigger A register

// Device Pin #44 is RD5
#define ECP34_TRIS    TRISDbits.TRISD5 // GPIO direction register bit
#define ECP34_WR      LATDbits.LATD5 // GPIO port latch register bit
#define ECP34_RD      PORTDbits.RD5 // GPIO port register bit
#define ECP34_ODC     ODCDbits.ODCD5 // GPIO port open drain configuration register bit
#define ECP34_CNPU    CNPUDbits.CNPUD5 // GPIO port pull-up resistor register bit
#define ECP34_CNPD    CNPDDbits.CNPDD5 // GPIO port pull-down resistor register bit
#define ECP34_CNEN0   CNEN0Dbits.CNEN0D5 // GPIO port change notification Enable register bit
#define ECP34_CNSTAT  CNSTATDbits.CNSTATD5 // GPIO port change notification Status register bit
#define ECP34_CNEN1   CNEN1Dbits.CNEN1D5 // GPIO port change notification Edge Select Enable register bit
#define ECP34_CNF     CNFDbits.CNFD5 // GPIO port change notification flag bit register bit
#define ECP34_RP      69 // Number of Remappable Pin
#define ECP34_SET     { asm volatile ("bset _LATD, #5 \n"); }
#define ECP34_CLEAR   { asm volatile ("bclr _LATD, #5 \n"); }
#define ECP34_TOGGLE  { asm volatile ("btg  _LATD, #5 \n"); }
#define ECP34_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP34_INIT_OUTPUT  {ECP34_WR = PINSTATE_LOW; ECP34_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP34_INIT_INPUT   {ECP34_WR = PINSTATE_HIGH; ECP34_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #50 is RC4
#define ECP35_TRIS    TRISCbits.TRISC4 // GPIO direction register bit
#define ECP35_WR      LATCbits.LATC4 // GPIO port latch register bit
#define ECP35_RD      PORTCbits.RC4 // GPIO port register bit
#define ECP35_ODC     ODCCbits.ODCC4 // GPIO port open drain configuration register bit
#define ECP35_CNPU    CNPUCbits.CNPUC4 // GPIO port pull-up resistor register bit
#define ECP35_CNPD    CNPDCbits.CNPDC4 // GPIO port pull-down resistor register bit
#define ECP35_CNEN0   CNEN0Cbits.CNEN0C4 // GPIO port change notification Enable register bit
#define ECP35_CNSTAT  CNSTATCbits.CNSTATC4 // GPIO port change notification Status register bit
#define ECP35_CNEN1   CNEN1Cbits.CNEN1C4 // GPIO port change notification Edge Select Enable register bit
#define ECP35_CNF     CNFCbits.CNFC4 // GPIO port change notification flag bit register bit
#define ECP35_RP      52 // Number of Remappable Pin
#define ECP35_SET     { asm volatile ("bset _LATC, #4 \n"); }
#define ECP35_CLEAR   { asm volatile ("bclr _LATC, #4 \n"); }
#define ECP35_TOGGLE  { asm volatile ("btg  _LATC, #4 \n"); }
#define ECP35_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP35_INIT_OUTPUT  {ECP35_WR = PINSTATE_LOW; ECP35_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP35_INIT_INPUT   {ECP35_WR = PINSTATE_HIGH; ECP35_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP35_PGx_CHANNEL  5 // PWM channel index
#define ECP35_PGx_PER      PG5PER // PWM channel period register
#define ECP35_PGx_PHASE    PG5PHASE // PWM channel phase register
#define ECP35_PGx_DC       PG5DC // PWM channel duty cycle register
#define ECP35_PGx_OVRENH   PG5IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP35_PGx_PENH     PG5IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP35_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP35_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define ECP35_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger A register
#define ECP35_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger A register

// Device Pin #43 is RD6
#define ECP36_TRIS    TRISDbits.TRISD6 // GPIO direction register bit
#define ECP36_WR      LATDbits.LATD6 // GPIO port latch register bit
#define ECP36_RD      PORTDbits.RD6 // GPIO port register bit
#define ECP36_ODC     ODCDbits.ODCD6 // GPIO port open drain configuration register bit
#define ECP36_CNPU    CNPUDbits.CNPUD6 // GPIO port pull-up resistor register bit
#define ECP36_CNPD    CNPDDbits.CNPDD6 // GPIO port pull-down resistor register bit
#define ECP36_CNEN0   CNEN0Dbits.CNEN0D6 // GPIO port change notification Enable register bit
#define ECP36_CNSTAT  CNSTATDbits.CNSTATD6 // GPIO port change notification Status register bit
#define ECP36_CNEN1   CNEN1Dbits.CNEN1D6 // GPIO port change notification Edge Select Enable register bit
#define ECP36_CNF     CNFDbits.CNFD6 // GPIO port change notification flag bit register bit
#define ECP36_RP      70 // Number of Remappable Pin
#define ECP36_SET     { asm volatile ("bset _LATD, #6 \n"); }
#define ECP36_CLEAR   { asm volatile ("bclr _LATD, #6 \n"); }
#define ECP36_TOGGLE  { asm volatile ("btg  _LATD, #6 \n"); }
#define ECP36_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP36_INIT_OUTPUT  {ECP36_WR = PINSTATE_LOW; ECP36_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP36_INIT_INPUT   {ECP36_WR = PINSTATE_HIGH; ECP36_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #61 is RB10
#define ECP37_TRIS    TRISBbits.TRISB10 // GPIO direction register bit
#define ECP37_WR      LATBbits.LATB10 // GPIO port latch register bit
#define ECP37_RD      PORTBbits.RB10 // GPIO port register bit
#define ECP37_ODC     ODCBbits.ODCB10 // GPIO port open drain configuration register bit
#define ECP37_CNPU    CNPUBbits.CNPUB10 // GPIO port pull-up resistor register bit
#define ECP37_CNPD    CNPDBbits.CNPDB10 // GPIO port pull-down resistor register bit
#define ECP37_CNEN0   CNEN0Bbits.CNEN0B10 // GPIO port change notification Enable register bit
#define ECP37_CNSTAT  CNSTATBbits.CNSTATB10 // GPIO port change notification Status register bit
#define ECP37_CNEN1   CNEN1Bbits.CNEN1B10 // GPIO port change notification Edge Select Enable register bit
#define ECP37_CNF     CNFBbits.CNFB10 // GPIO port change notification flag bit register bit
#define ECP37_RP      42 // Number of Remappable Pin
#define ECP37_SET     { asm volatile ("bset _LATB, #10 \n"); }
#define ECP37_CLEAR   { asm volatile ("bclr _LATB, #10 \n"); }
#define ECP37_TOGGLE  { asm volatile ("btg  _LATB, #10 \n"); }
#define ECP37_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP37_INIT_OUTPUT  {ECP37_WR = PINSTATE_LOW; ECP37_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP37_INIT_INPUT   {ECP37_WR = PINSTATE_HIGH; ECP37_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP37_PGx_CHANNEL  3 // PWM channel index
#define ECP37_PGx_PER      PG3PER // PWM channel period register
#define ECP37_PGx_PHASE    PG3PHASE // PWM channel phase register
#define ECP37_PGx_DC       PG3DC // PWM channel duty cycle register
#define ECP37_PGx_OVRENH   PG3IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP37_PGx_PENH     PG3IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP37_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP37_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define ECP37_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define ECP37_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register

// Device Pin #51 is RC5
#define ECP38_TRIS    TRISCbits.TRISC5 // GPIO direction register bit
#define ECP38_WR      LATCbits.LATC5 // GPIO port latch register bit
#define ECP38_RD      PORTCbits.RC5 // GPIO port register bit
#define ECP38_ODC     ODCCbits.ODCC5 // GPIO port open drain configuration register bit
#define ECP38_CNPU    CNPUCbits.CNPUC5 // GPIO port pull-up resistor register bit
#define ECP38_CNPD    CNPDCbits.CNPDC5 // GPIO port pull-down resistor register bit
#define ECP38_CNEN0   CNEN0Cbits.CNEN0C5 // GPIO port change notification Enable register bit
#define ECP38_CNSTAT  CNSTATCbits.CNSTATC5 // GPIO port change notification Status register bit
#define ECP38_CNEN1   CNEN1Cbits.CNEN1C5 // GPIO port change notification Edge Select Enable register bit
#define ECP38_CNF     CNFCbits.CNFC5 // GPIO port change notification flag bit register bit
#define ECP38_RP      53 // Number of Remappable Pin
#define ECP38_SET     { asm volatile ("bset _LATC, #5 \n"); }
#define ECP38_CLEAR   { asm volatile ("bclr _LATC, #5 \n"); }
#define ECP38_TOGGLE  { asm volatile ("btg  _LATC, #5 \n"); }
#define ECP38_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP38_INIT_OUTPUT  {ECP38_WR = PINSTATE_LOW; ECP38_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP38_INIT_INPUT   {ECP38_WR = PINSTATE_HIGH; ECP38_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP38_PGx_CHANNEL  5 // PWM channel index
#define ECP38_PGx_PER      PG5PER // PWM channel period register
#define ECP38_PGx_PHASE    PG5PHASE // PWM channel phase register
#define ECP38_PGx_DC       PG5DC // PWM channel duty cycle register
#define ECP38_PGx_OVRENL   PG5IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP38_PGx_PENL     PG5IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP38_PGxUPDREQ    PG5STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP38_PGxTRIGA     PG5TRIGA // PWM channel ADC trigger A register
#define ECP38_PGxTRIGB     PG5TRIGB // PWM channel ADC trigger A register
#define ECP38_PGxTRIGC     PG5TRIGC // PWM channel ADC trigger A register

// Device Pin #58 is RD2
#define ECP39_TRIS    TRISDbits.TRISD2 // GPIO direction register bit
#define ECP39_WR      LATDbits.LATD2 // GPIO port latch register bit
#define ECP39_RD      PORTDbits.RD2 // GPIO port register bit
#define ECP39_ODC     ODCDbits.ODCD2 // GPIO port open drain configuration register bit
#define ECP39_CNPU    CNPUDbits.CNPUD2 // GPIO port pull-up resistor register bit
#define ECP39_CNPD    CNPDDbits.CNPDD2 // GPIO port pull-down resistor register bit
#define ECP39_CNEN0   CNEN0Dbits.CNEN0D2 // GPIO port change notification Enable register bit
#define ECP39_CNSTAT  CNSTATDbits.CNSTATD2 // GPIO port change notification Status register bit
#define ECP39_CNEN1   CNEN1Dbits.CNEN1D2 // GPIO port change notification Edge Select Enable register bit
#define ECP39_CNF     CNFDbits.CNFD2 // GPIO port change notification flag bit register bit
#define ECP39_RP      66 // Number of Remappable Pin
#define ECP39_SET     { asm volatile ("bset _LATD, #2 \n"); }
#define ECP39_CLEAR   { asm volatile ("bclr _LATD, #2 \n"); }
#define ECP39_TOGGLE  { asm volatile ("btg  _LATD, #2 \n"); }
#define ECP39_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP39_INIT_OUTPUT  {ECP39_WR = PINSTATE_LOW; ECP39_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP39_INIT_INPUT   {ECP39_WR = PINSTATE_HIGH; ECP39_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #64 is RB13
#define ECP40_TRIS    TRISBbits.TRISB13 // GPIO direction register bit
#define ECP40_WR      LATBbits.LATB13 // GPIO port latch register bit
#define ECP40_RD      PORTBbits.RB13 // GPIO port register bit
#define ECP40_ODC     ODCBbits.ODCB13 // GPIO port open drain configuration register bit
#define ECP40_CNPU    CNPUBbits.CNPUB13 // GPIO port pull-up resistor register bit
#define ECP40_CNPD    CNPDBbits.CNPDB13 // GPIO port pull-down resistor register bit
#define ECP40_CNEN0   CNEN0Bbits.CNEN0B13 // GPIO port change notification Enable register bit
#define ECP40_CNSTAT  CNSTATBbits.CNSTATB13 // GPIO port change notification Status register bit
#define ECP40_CNEN1   CNEN1Bbits.CNEN1B13 // GPIO port change notification Edge Select Enable register bit
#define ECP40_CNF     CNFBbits.CNFB13 // GPIO port change notification flag bit register bit
#define ECP40_RP      45 // Number of Remappable Pin
#define ECP40_SET     { asm volatile ("bset _LATB, #13 \n"); }
#define ECP40_CLEAR   { asm volatile ("bclr _LATB, #13 \n"); }
#define ECP40_TOGGLE  { asm volatile ("btg  _LATB, #13 \n"); }
#define ECP40_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP40_INIT_OUTPUT  {ECP40_WR = PINSTATE_LOW; ECP40_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP40_INIT_INPUT   {ECP40_WR = PINSTATE_HIGH; ECP40_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP40_PGx_CHANNEL  2 // PWM channel index
#define ECP40_PGx_PER      PG2PER // PWM channel period register
#define ECP40_PGx_PHASE    PG2PHASE // PWM channel phase register
#define ECP40_PGx_DC       PG2DC // PWM channel duty cycle register
#define ECP40_PGx_OVRENL   PG2IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP40_PGx_PENL     PG2IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP40_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP40_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define ECP40_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define ECP40_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register

// Device Pin #62 is RB11
#define ECP41_TRIS    TRISBbits.TRISB11 // GPIO direction register bit
#define ECP41_WR      LATBbits.LATB11 // GPIO port latch register bit
#define ECP41_RD      PORTBbits.RB11 // GPIO port register bit
#define ECP41_ODC     ODCBbits.ODCB11 // GPIO port open drain configuration register bit
#define ECP41_CNPU    CNPUBbits.CNPUB11 // GPIO port pull-up resistor register bit
#define ECP41_CNPD    CNPDBbits.CNPDB11 // GPIO port pull-down resistor register bit
#define ECP41_CNEN0   CNEN0Bbits.CNEN0B11 // GPIO port change notification Enable register bit
#define ECP41_CNSTAT  CNSTATBbits.CNSTATB11 // GPIO port change notification Status register bit
#define ECP41_CNEN1   CNEN1Bbits.CNEN1B11 // GPIO port change notification Edge Select Enable register bit
#define ECP41_CNF     CNFBbits.CNFB11 // GPIO port change notification flag bit register bit
#define ECP41_RP      43 // Number of Remappable Pin
#define ECP41_SET     { asm volatile ("bset _LATB, #11 \n"); }
#define ECP41_CLEAR   { asm volatile ("bclr _LATB, #11 \n"); }
#define ECP41_TOGGLE  { asm volatile ("btg  _LATB, #11 \n"); }
#define ECP41_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP41_INIT_OUTPUT  {ECP41_WR = PINSTATE_LOW; ECP41_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP41_INIT_INPUT   {ECP41_WR = PINSTATE_HIGH; ECP41_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP41_PGx_CHANNEL  3 // PWM channel index
#define ECP41_PGx_PER      PG3PER // PWM channel period register
#define ECP41_PGx_PHASE    PG3PHASE // PWM channel phase register
#define ECP41_PGx_DC       PG3DC // PWM channel duty cycle register
#define ECP41_PGx_OVRENL   PG3IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP41_PGx_PENL     PG3IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP41_PGxUPDREQ    PG3STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP41_PGxTRIGA     PG3TRIGA // PWM channel ADC trigger A register
#define ECP41_PGxTRIGB     PG3TRIGB // PWM channel ADC trigger A register
#define ECP41_PGxTRIGC     PG3TRIGC // PWM channel ADC trigger A register

// Device Pin #63 is RB12
#define ECP42_TRIS    TRISBbits.TRISB12 // GPIO direction register bit
#define ECP42_WR      LATBbits.LATB12 // GPIO port latch register bit
#define ECP42_RD      PORTBbits.RB12 // GPIO port register bit
#define ECP42_ODC     ODCBbits.ODCB12 // GPIO port open drain configuration register bit
#define ECP42_CNPU    CNPUBbits.CNPUB12 // GPIO port pull-up resistor register bit
#define ECP42_CNPD    CNPDBbits.CNPDB12 // GPIO port pull-down resistor register bit
#define ECP42_CNEN0   CNEN0Bbits.CNEN0B12 // GPIO port change notification Enable register bit
#define ECP42_CNSTAT  CNSTATBbits.CNSTATB12 // GPIO port change notification Status register bit
#define ECP42_CNEN1   CNEN1Bbits.CNEN1B12 // GPIO port change notification Edge Select Enable register bit
#define ECP42_CNF     CNFBbits.CNFB12 // GPIO port change notification flag bit register bit
#define ECP42_RP      44 // Number of Remappable Pin
#define ECP42_SET     { asm volatile ("bset _LATB, #12 \n"); }
#define ECP42_CLEAR   { asm volatile ("bclr _LATB, #12 \n"); }
#define ECP42_TOGGLE  { asm volatile ("btg  _LATB, #12 \n"); }
#define ECP42_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP42_INIT_OUTPUT  {ECP42_WR = PINSTATE_LOW; ECP42_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP42_INIT_INPUT   {ECP42_WR = PINSTATE_HIGH; ECP42_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP42_PGx_CHANNEL  2 // PWM channel index
#define ECP42_PGx_PER      PG2PER // PWM channel period register
#define ECP42_PGx_PHASE    PG2PHASE // PWM channel phase register
#define ECP42_PGx_DC       PG2DC // PWM channel duty cycle register
#define ECP42_PGx_OVRENH   PG2IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP42_PGx_PENH     PG2IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP42_PGxUPDREQ    PG2STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP42_PGxTRIGA     PG2TRIGA // PWM channel ADC trigger A register
#define ECP42_PGxTRIGB     PG2TRIGB // PWM channel ADC trigger A register
#define ECP42_PGxTRIGC     PG2TRIGC // PWM channel ADC trigger A register

// Device Pin #59 is RD1
#define ECP43_TRIS    TRISDbits.TRISD1 // GPIO direction register bit
#define ECP43_WR      LATDbits.LATD1 // GPIO port latch register bit
#define ECP43_RD      PORTDbits.RD1 // GPIO port register bit
#define ECP43_ODC     ODCDbits.ODCD1 // GPIO port open drain configuration register bit
#define ECP43_CNPU    CNPUDbits.CNPUD1 // GPIO port pull-up resistor register bit
#define ECP43_CNPD    CNPDDbits.CNPDD1 // GPIO port pull-down resistor register bit
#define ECP43_CNEN0   CNEN0Dbits.CNEN0D1 // GPIO port change notification Enable register bit
#define ECP43_CNSTAT  CNSTATDbits.CNSTATD1 // GPIO port change notification Status register bit
#define ECP43_CNEN1   CNEN1Dbits.CNEN1D1 // GPIO port change notification Edge Select Enable register bit
#define ECP43_CNF     CNFDbits.CNFD1 // GPIO port change notification flag bit register bit
#define ECP43_RP      65 // Number of Remappable Pin
#define ECP43_SET     { asm volatile ("bset _LATD, #1 \n"); }
#define ECP43_CLEAR   { asm volatile ("bclr _LATD, #1 \n"); }
#define ECP43_TOGGLE  { asm volatile ("btg  _LATD, #1 \n"); }
#define ECP43_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP43_INIT_OUTPUT  {ECP43_WR = PINSTATE_LOW; ECP43_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP43_INIT_INPUT   {ECP43_WR = PINSTATE_HIGH; ECP43_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP43_PGx_CHANNEL  4 // PWM channel index
#define ECP43_PGx_PER      PG4PER // PWM channel period register
#define ECP43_PGx_PHASE    PG4PHASE // PWM channel phase register
#define ECP43_PGx_DC       PG4DC // PWM channel duty cycle register
#define ECP43_PGx_OVRENH   PG4IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP43_PGx_PENH     PG4IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP43_PGxUPDREQ    PG4STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP43_PGxTRIGA     PG4TRIGA // PWM channel ADC trigger A register
#define ECP43_PGxTRIGB     PG4TRIGB // PWM channel ADC trigger A register
#define ECP43_PGxTRIGC     PG4TRIGC // PWM channel ADC trigger A register

// Device Pin #60 is RD0
#define ECP44_TRIS    TRISDbits.TRISD0 // GPIO direction register bit
#define ECP44_WR      LATDbits.LATD0 // GPIO port latch register bit
#define ECP44_RD      PORTDbits.RD0 // GPIO port register bit
#define ECP44_ODC     ODCDbits.ODCD0 // GPIO port open drain configuration register bit
#define ECP44_CNPU    CNPUDbits.CNPUD0 // GPIO port pull-up resistor register bit
#define ECP44_CNPD    CNPDDbits.CNPDD0 // GPIO port pull-down resistor register bit
#define ECP44_CNEN0   CNEN0Dbits.CNEN0D0 // GPIO port change notification Enable register bit
#define ECP44_CNSTAT  CNSTATDbits.CNSTATD0 // GPIO port change notification Status register bit
#define ECP44_CNEN1   CNEN1Dbits.CNEN1D0 // GPIO port change notification Edge Select Enable register bit
#define ECP44_CNF     CNFDbits.CNFD0 // GPIO port change notification flag bit register bit
#define ECP44_RP      64 // Number of Remappable Pin
#define ECP44_SET     { asm volatile ("bset _LATD, #0 \n"); }
#define ECP44_CLEAR   { asm volatile ("bclr _LATD, #0 \n"); }
#define ECP44_TOGGLE  { asm volatile ("btg  _LATD, #0 \n"); }
#define ECP44_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP44_INIT_OUTPUT  {ECP44_WR = PINSTATE_LOW; ECP44_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP44_INIT_INPUT   {ECP44_WR = PINSTATE_HIGH; ECP44_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP44_PGx_CHANNEL  4 // PWM channel index
#define ECP44_PGx_PER      PG4PER // PWM channel period register
#define ECP44_PGx_PHASE    PG4PHASE // PWM channel phase register
#define ECP44_PGx_DC       PG4DC // PWM channel duty cycle register
#define ECP44_PGx_OVRENL   PG4IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP44_PGx_PENL     PG4IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP44_PGxUPDREQ    PG4STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP44_PGxTRIGA     PG4TRIGA // PWM channel ADC trigger A register
#define ECP44_PGxTRIGB     PG4TRIGB // PWM channel ADC trigger A register
#define ECP44_PGxTRIGC     PG4TRIGC // PWM channel ADC trigger A register

// Device Pin #1 is RB14
#define ECP45_TRIS    TRISBbits.TRISB14 // GPIO direction register bit
#define ECP45_WR      LATBbits.LATB14 // GPIO port latch register bit
#define ECP45_RD      PORTBbits.RB14 // GPIO port register bit
#define ECP45_ODC     ODCBbits.ODCB14 // GPIO port open drain configuration register bit
#define ECP45_CNPU    CNPUBbits.CNPUB14 // GPIO port pull-up resistor register bit
#define ECP45_CNPD    CNPDBbits.CNPDB14 // GPIO port pull-down resistor register bit
#define ECP45_CNEN0   CNEN0Bbits.CNEN0B14 // GPIO port change notification Enable register bit
#define ECP45_CNSTAT  CNSTATBbits.CNSTATB14 // GPIO port change notification Status register bit
#define ECP45_CNEN1   CNEN1Bbits.CNEN1B14 // GPIO port change notification Edge Select Enable register bit
#define ECP45_CNF     CNFBbits.CNFB14 // GPIO port change notification flag bit register bit
#define ECP45_RP      46 // Number of Remappable Pin
#define ECP45_SET     { asm volatile ("bset _LATB, #14 \n"); }
#define ECP45_CLEAR   { asm volatile ("bclr _LATB, #14 \n"); }
#define ECP45_TOGGLE  { asm volatile ("btg  _LATB, #14 \n"); }
#define ECP45_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP45_INIT_OUTPUT  {ECP45_WR = PINSTATE_LOW; ECP45_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP45_INIT_INPUT   {ECP45_WR = PINSTATE_HIGH; ECP45_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP45_PGx_CHANNEL  1 // PWM channel index
#define ECP45_PGx_PER      PG1PER // PWM channel period register
#define ECP45_PGx_PHASE    PG1PHASE // PWM channel phase register
#define ECP45_PGx_DC       PG1DC // PWM channel duty cycle register
#define ECP45_PGx_OVRENH   PG1IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP45_PGx_PENH     PG1IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP45_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP45_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define ECP45_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define ECP45_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register

// Device Pin #3 is RC12
#define ECP46_TRIS    TRISCbits.TRISC12 // GPIO direction register bit
#define ECP46_WR      LATCbits.LATC12 // GPIO port latch register bit
#define ECP46_RD      PORTCbits.RC12 // GPIO port register bit
#define ECP46_ODC     ODCCbits.ODCC12 // GPIO port open drain configuration register bit
#define ECP46_CNPU    CNPUCbits.CNPUC12 // GPIO port pull-up resistor register bit
#define ECP46_CNPD    CNPDCbits.CNPDC12 // GPIO port pull-down resistor register bit
#define ECP46_CNEN0   CNEN0Cbits.CNEN0C12 // GPIO port change notification Enable register bit
#define ECP46_CNSTAT  CNSTATCbits.CNSTATC12 // GPIO port change notification Status register bit
#define ECP46_CNEN1   CNEN1Cbits.CNEN1C12 // GPIO port change notification Edge Select Enable register bit
#define ECP46_CNF     CNFCbits.CNFC12 // GPIO port change notification flag bit register bit
#define ECP46_RP      60 // Number of Remappable Pin
#define ECP46_SET     { asm volatile ("bset _LATC, #12 \n"); }
#define ECP46_CLEAR   { asm volatile ("bclr _LATC, #12 \n"); }
#define ECP46_TOGGLE  { asm volatile ("btg  _LATC, #12 \n"); }
#define ECP46_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP46_INIT_OUTPUT  {ECP46_WR = PINSTATE_LOW; ECP46_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP46_INIT_INPUT   {ECP46_WR = PINSTATE_HIGH; ECP46_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP46_PGx_CHANNEL  8 // PWM channel index
#define ECP46_PGx_PER      PG8PER // PWM channel period register
#define ECP46_PGx_PHASE    PG8PHASE // PWM channel phase register
#define ECP46_PGx_DC       PG8DC // PWM channel duty cycle register
#define ECP46_PGx_OVRENH   PG8IOCONLbits.OVRENH // PWM channel IO config register override high control bit
#define ECP46_PGx_PENH     PG8IOCONLbits.PENH // PWM channel IO config register pin enable high control bit
#define ECP46_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP46_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define ECP46_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define ECP46_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register

// Device Pin #2 is RB15
#define ECP47_TRIS    TRISBbits.TRISB15 // GPIO direction register bit
#define ECP47_WR      LATBbits.LATB15 // GPIO port latch register bit
#define ECP47_RD      PORTBbits.RB15 // GPIO port register bit
#define ECP47_ODC     ODCBbits.ODCB15 // GPIO port open drain configuration register bit
#define ECP47_CNPU    CNPUBbits.CNPUB15 // GPIO port pull-up resistor register bit
#define ECP47_CNPD    CNPDBbits.CNPDB15 // GPIO port pull-down resistor register bit
#define ECP47_CNEN0   CNEN0Bbits.CNEN0B15 // GPIO port change notification Enable register bit
#define ECP47_CNSTAT  CNSTATBbits.CNSTATB15 // GPIO port change notification Status register bit
#define ECP47_CNEN1   CNEN1Bbits.CNEN1B15 // GPIO port change notification Edge Select Enable register bit
#define ECP47_CNF     CNFBbits.CNFB15 // GPIO port change notification flag bit register bit
#define ECP47_RP      47 // Number of Remappable Pin
#define ECP47_SET     { asm volatile ("bset _LATB, #15 \n"); }
#define ECP47_CLEAR   { asm volatile ("bclr _LATB, #15 \n"); }
#define ECP47_TOGGLE  { asm volatile ("btg  _LATB, #15 \n"); }
#define ECP47_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP47_INIT_OUTPUT  {ECP47_WR = PINSTATE_LOW; ECP47_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP47_INIT_INPUT   {ECP47_WR = PINSTATE_HIGH; ECP47_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP47_PGx_CHANNEL  1 // PWM channel index
#define ECP47_PGx_PER      PG1PER // PWM channel period register
#define ECP47_PGx_PHASE    PG1PHASE // PWM channel phase register
#define ECP47_PGx_DC       PG1DC // PWM channel duty cycle register
#define ECP47_PGx_OVRENL   PG1IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP47_PGx_PENL     PG1IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP47_PGxUPDREQ    PG1STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP47_PGxTRIGA     PG1TRIGA // PWM channel ADC trigger A register
#define ECP47_PGxTRIGB     PG1TRIGB // PWM channel ADC trigger A register
#define ECP47_PGxTRIGC     PG1TRIGC // PWM channel ADC trigger A register

// Device Pin #4 is RC13
#define ECP48_TRIS    TRISCbits.TRISC13 // GPIO direction register bit
#define ECP48_WR      LATCbits.LATC13 // GPIO port latch register bit
#define ECP48_RD      PORTCbits.RC13 // GPIO port register bit
#define ECP48_ODC     ODCCbits.ODCC13 // GPIO port open drain configuration register bit
#define ECP48_CNPU    CNPUCbits.CNPUC13 // GPIO port pull-up resistor register bit
#define ECP48_CNPD    CNPDCbits.CNPDC13 // GPIO port pull-down resistor register bit
#define ECP48_CNEN0   CNEN0Cbits.CNEN0C13 // GPIO port change notification Enable register bit
#define ECP48_CNSTAT  CNSTATCbits.CNSTATC13 // GPIO port change notification Status register bit
#define ECP48_CNEN1   CNEN1Cbits.CNEN1C13 // GPIO port change notification Edge Select Enable register bit
#define ECP48_CNF     CNFCbits.CNFC13 // GPIO port change notification flag bit register bit
#define ECP48_RP      61 // Number of Remappable Pin
#define ECP48_SET     { asm volatile ("bset _LATC, #13 \n"); }
#define ECP48_CLEAR   { asm volatile ("bclr _LATC, #13 \n"); }
#define ECP48_TOGGLE  { asm volatile ("btg  _LATC, #13 \n"); }
#define ECP48_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP48_INIT_OUTPUT  {ECP48_WR = PINSTATE_LOW; ECP48_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP48_INIT_INPUT   {ECP48_WR = PINSTATE_HIGH; ECP48_TRIS = PINDIR_INPUT;} // initialization macro for digital input
#define ECP48_PGx_CHANNEL  8 // PWM channel index
#define ECP48_PGx_PER      PG8PER // PWM channel period register
#define ECP48_PGx_PHASE    PG8PHASE // PWM channel phase register
#define ECP48_PGx_DC       PG8DC // PWM channel duty cycle register
#define ECP48_PGx_OVRENL   PG8IOCONLbits.OVRENL // PWM channel IO config register override low control bit
#define ECP48_PGx_PENL     PG8IOCONLbits.PENL // PWM channel IO config register pin enable low control bit
#define ECP48_PGxUPDREQ    PG8STATbits.UPDREQ // PWM channel ADC trigger A register
#define ECP48_PGxTRIGA     PG8TRIGA // PWM channel ADC trigger A register
#define ECP48_PGxTRIGB     PG8TRIGB // PWM channel ADC trigger A register
#define ECP48_PGxTRIGC     PG8TRIGC // PWM channel ADC trigger A register

// Device Pin #42 is RD7
#define ECP50_TRIS    TRISDbits.TRISD7 // GPIO direction register bit
#define ECP50_WR      LATDbits.LATD7 // GPIO port latch register bit
#define ECP50_RD      PORTDbits.RD7 // GPIO port register bit
#define ECP50_ODC     ODCDbits.ODCD7 // GPIO port open drain configuration register bit
#define ECP50_CNPU    CNPUDbits.CNPUD7 // GPIO port pull-up resistor register bit
#define ECP50_CNPD    CNPDDbits.CNPDD7 // GPIO port pull-down resistor register bit
#define ECP50_CNEN0   CNEN0Dbits.CNEN0D7 // GPIO port change notification Enable register bit
#define ECP50_CNSTAT  CNSTATDbits.CNSTATD7 // GPIO port change notification Status register bit
#define ECP50_CNEN1   CNEN1Dbits.CNEN1D7 // GPIO port change notification Edge Select Enable register bit
#define ECP50_CNF     CNFDbits.CNFD7 // GPIO port change notification flag bit register bit
#define ECP50_RP      71 // Number of Remappable Pin
#define ECP50_SET     { asm volatile ("bset _LATD, #7 \n"); }
#define ECP50_CLEAR   { asm volatile ("bclr _LATD, #7 \n"); }
#define ECP50_TOGGLE  { asm volatile ("btg  _LATD, #7 \n"); }
#define ECP50_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP50_INIT_OUTPUT  {ECP50_WR = PINSTATE_LOW; ECP50_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP50_INIT_INPUT   {ECP50_WR = PINSTATE_HIGH; ECP50_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #35 is RB4
#define ECP51_TRIS    TRISBbits.TRISB4 // GPIO direction register bit
#define ECP51_WR      LATBbits.LATB4 // GPIO port latch register bit
#define ECP51_RD      PORTBbits.RB4 // GPIO port register bit
#define ECP51_ODC     ODCBbits.ODCB4 // GPIO port open drain configuration register bit
#define ECP51_CNPU    CNPUBbits.CNPUB4 // GPIO port pull-up resistor register bit
#define ECP51_CNPD    CNPDBbits.CNPDB4 // GPIO port pull-down resistor register bit
#define ECP51_CNEN0   CNEN0Bbits.CNEN0B4 // GPIO port change notification Enable register bit
#define ECP51_CNSTAT  CNSTATBbits.CNSTATB4 // GPIO port change notification Status register bit
#define ECP51_CNEN1   CNEN1Bbits.CNEN1B4 // GPIO port change notification Edge Select Enable register bit
#define ECP51_CNF     CNFBbits.CNFB4 // GPIO port change notification flag bit register bit
#define ECP51_RP      36 // Number of Remappable Pin
#define ECP51_SET     { asm volatile ("bset _LATB, #4 \n"); }
#define ECP51_CLEAR   { asm volatile ("bclr _LATB, #4 \n"); }
#define ECP51_TOGGLE  { asm volatile ("btg  _LATB, #4 \n"); }
#define ECP51_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP51_INIT_OUTPUT  {ECP51_WR = PINSTATE_LOW; ECP51_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP51_INIT_INPUT   {ECP51_WR = PINSTATE_HIGH; ECP51_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #39 is RD8
#define ECP52_TRIS    TRISDbits.TRISD8 // GPIO direction register bit
#define ECP52_WR      LATDbits.LATD8 // GPIO port latch register bit
#define ECP52_RD      PORTDbits.RD8 // GPIO port register bit
#define ECP52_ODC     ODCDbits.ODCD8 // GPIO port open drain configuration register bit
#define ECP52_CNPU    CNPUDbits.CNPUD8 // GPIO port pull-up resistor register bit
#define ECP52_CNPD    CNPDDbits.CNPDD8 // GPIO port pull-down resistor register bit
#define ECP52_CNEN0   CNEN0Dbits.CNEN0D8 // GPIO port change notification Enable register bit
#define ECP52_CNSTAT  CNSTATDbits.CNSTATD8 // GPIO port change notification Status register bit
#define ECP52_CNEN1   CNEN1Dbits.CNEN1D8 // GPIO port change notification Edge Select Enable register bit
#define ECP52_CNF     CNFDbits.CNFD8 // GPIO port change notification flag bit register bit
#define ECP52_RP      72 // Number of Remappable Pin
#define ECP52_SET     { asm volatile ("bset _LATD, #8 \n"); }
#define ECP52_CLEAR   { asm volatile ("bclr _LATD, #8 \n"); }
#define ECP52_TOGGLE  { asm volatile ("btg  _LATD, #8 \n"); }
#define ECP52_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define ECP52_INIT_OUTPUT  {ECP52_WR = PINSTATE_LOW; ECP52_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP52_INIT_INPUT   {ECP52_WR = PINSTATE_HIGH; ECP52_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #12 is RD13
#define ECP54_TRIS    TRISDbits.TRISD13 // GPIO direction register bit
#define ECP54_WR      LATDbits.LATD13 // GPIO port latch register bit
#define ECP54_RD      PORTDbits.RD13 // GPIO port register bit
#define ECP54_ODC     ODCDbits.ODCD13 // GPIO port open drain configuration register bit
#define ECP54_CNPU    CNPUDbits.CNPUD13 // GPIO port pull-up resistor register bit
#define ECP54_CNPD    CNPDDbits.CNPDD13 // GPIO port pull-down resistor register bit
#define ECP54_CNEN0   CNEN0Dbits.CNEN0D13 // GPIO port change notification Enable register bit
#define ECP54_CNSTAT  CNSTATDbits.CNSTATD13 // GPIO port change notification Status register bit
#define ECP54_CNEN1   CNEN1Dbits.CNEN1D13 // GPIO port change notification Edge Select Enable register bit
#define ECP54_CNF     CNFDbits.CNFD13 // GPIO port change notification flag bit register bit
#define ECP54_RP      77 // Number of Remappable Pin
#define ECP54_SET     { asm volatile ("bset _LATD, #13 \n"); }
#define ECP54_CLEAR   { asm volatile ("bclr _LATD, #13 \n"); }
#define ECP54_TOGGLE  { asm volatile ("btg  _LATD, #13 \n"); }
#define ECP54_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP54_ANSEL   _ANSELD13 // analog/digital pin configuration register bit
#define ECP54_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP54_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP54_ADC_AN_INPUT N2   // ANx input pin number
#define ECP54_ADCBUF  ADCBUFN2 // ADC buffer register for this input
#define ECP54_ADC_ANIE ADIEHbits.IEN2
#define ECP54_ADC_ANEIE ADEIEHbits.EIENN2
#define ECP54_ADC_IF   _ADCANN2IF // interrupt flag bit
#define ECP54_ADC_IE   _ADCANN2IE // interrupt enable bit
#define ECP54_ADC_IP   _ADCANN2IP // interrupt priority for this analog input
#define ECP54_ADC_RDY  _ANN2RDY // ADC buffer ready bit
#define _ECP54_ADC_Interrupt _ADCANN2Interrupt
#define ECP54_INIT_ANALOG	{ECP54_ANSEL = 1; ECP54_WR = PINSTATE_HIGH; ECP54_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP54_INIT_OUTPUT  {ECP54_WR = PINSTATE_LOW; ECP54_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP54_INIT_INPUT   {ECP54_WR = PINSTATE_HIGH; ECP54_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #34 is RB3
#define ECP56_TRIS    TRISBbits.TRISB3 // GPIO direction register bit
#define ECP56_WR      LATBbits.LATB3 // GPIO port latch register bit
#define ECP56_RD      PORTBbits.RB3 // GPIO port register bit
#define ECP56_ODC     ODCBbits.ODCB3 // GPIO port open drain configuration register bit
#define ECP56_CNPU    CNPUBbits.CNPUB3 // GPIO port pull-up resistor register bit
#define ECP56_CNPD    CNPDBbits.CNPDB3 // GPIO port pull-down resistor register bit
#define ECP56_CNEN0   CNEN0Bbits.CNEN0B3 // GPIO port change notification Enable register bit
#define ECP56_CNSTAT  CNSTATBbits.CNSTATB3 // GPIO port change notification Status register bit
#define ECP56_CNEN1   CNEN1Bbits.CNEN1B3 // GPIO port change notification Edge Select Enable register bit
#define ECP56_CNF     CNFBbits.CNFB3 // GPIO port change notification flag bit register bit
#define ECP56_RP      35 // Number of Remappable Pin
#define ECP56_SET     { asm volatile ("bset _LATB, #3 \n"); }
#define ECP56_CLEAR   { asm volatile ("bclr _LATB, #3 \n"); }
#define ECP56_TOGGLE  { asm volatile ("btg  _LATB, #3 \n"); }
#define ECP56_IS_ANALOG_INPUT  1 // Pin is/is not analog input 
#define ECP56_ANSEL   _ANSELB3 // analog/digital pin configuration register bit
#define ECP56_ADCCORE  // index starts from zero, last index indicated shared adC core
#define ECP56_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core
#define ECP56_ADC_AN_INPUT 8   // ANx input pin number
#define ECP56_ADCBUF  ADCBUF8 // ADC buffer register for this input
#define ECP56_ADC_ANIE ADIELbits.IE8
#define ECP56_ADC_ANEIE ADEIELbits.EIEN8
#define ECP56_ADC_IF   _ADCAN8IF // interrupt flag bit
#define ECP56_ADC_IE   _ADCAN8IE // interrupt enable bit
#define ECP56_ADC_IP   _ADCAN8IP // interrupt priority for this analog input
#define ECP56_ADC_RDY  _AN8RDY // ADC buffer ready bit
#define _ECP56_ADC_Interrupt _ADCAN8Interrupt
#define ECP56_INIT_ANALOG	{ECP56_ANSEL = 1; ECP56_WR = PINSTATE_HIGH; ECP56_TRIS = PINDIR_INPUT;} // initialization macro for analog input
#define ECP56_INIT_OUTPUT  {ECP56_WR = PINSTATE_LOW; ECP56_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define ECP56_INIT_INPUT   {ECP56_WR = PINSTATE_HIGH; ECP56_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #46 is RB6
#define SCL_TRIS    TRISBbits.TRISB6 // GPIO direction register bit
#define SCL_WR      LATBbits.LATB6 // GPIO port latch register bit
#define SCL_RD      PORTBbits.RB6 // GPIO port register bit
#define SCL_ODC     ODCBbits.ODCB6 // GPIO port open drain configuration register bit
#define SCL_CNPU    CNPUBbits.CNPUB6 // GPIO port pull-up resistor register bit
#define SCL_CNPD    CNPDBbits.CNPDB6 // GPIO port pull-down resistor register bit
#define SCL_CNEN0   CNEN0Bbits.CNEN0B6 // GPIO port change notification Enable register bit
#define SCL_CNSTAT  CNSTATBbits.CNSTATB6 // GPIO port change notification Status register bit
#define SCL_CNEN1   CNEN1Bbits.CNEN1B6 // GPIO port change notification Edge Select Enable register bit
#define SCL_CNF     CNFBbits.CNFB6 // GPIO port change notification flag bit register bit
#define SCL_RP      38 // Number of Remappable Pin
#define SCL_SET     { asm volatile ("bset _LATB, #6 \n"); }
#define SCL_CLEAR   { asm volatile ("bclr _LATB, #6 \n"); }
#define SCL_TOGGLE  { asm volatile ("btg  _LATB, #6 \n"); }
#define SCL_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define SCL_INIT_OUTPUT  {SCL_WR = PINSTATE_LOW; SCL_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SCL_INIT_INPUT   {SCL_WR = PINSTATE_HIGH; SCL_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #45 is RB5
#define SDA_TRIS    TRISBbits.TRISB5 // GPIO direction register bit
#define SDA_WR      LATBbits.LATB5 // GPIO port latch register bit
#define SDA_RD      PORTBbits.RB5 // GPIO port register bit
#define SDA_ODC     ODCBbits.ODCB5 // GPIO port open drain configuration register bit
#define SDA_CNPU    CNPUBbits.CNPUB5 // GPIO port pull-up resistor register bit
#define SDA_CNPD    CNPDBbits.CNPDB5 // GPIO port pull-down resistor register bit
#define SDA_CNEN0   CNEN0Bbits.CNEN0B5 // GPIO port change notification Enable register bit
#define SDA_CNSTAT  CNSTATBbits.CNSTATB5 // GPIO port change notification Status register bit
#define SDA_CNEN1   CNEN1Bbits.CNEN1B5 // GPIO port change notification Edge Select Enable register bit
#define SDA_CNF     CNFBbits.CNFB5 // GPIO port change notification flag bit register bit
#define SDA_RP      37 // Number of Remappable Pin
#define SDA_SET     { asm volatile ("bset _LATB, #5 \n"); }
#define SDA_CLEAR   { asm volatile ("bclr _LATB, #5 \n"); }
#define SDA_TOGGLE  { asm volatile ("btg  _LATB, #5 \n"); }
#define SDA_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define SDA_INIT_OUTPUT  {SDA_WR = PINSTATE_LOW; SDA_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define SDA_INIT_INPUT   {SDA_WR = PINSTATE_HIGH; SDA_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #54 is RD4
#define UART_RX_TRIS    TRISDbits.TRISD4 // GPIO direction register bit
#define UART_RX_WR      LATDbits.LATD4 // GPIO port latch register bit
#define UART_RX_RD      PORTDbits.RD4 // GPIO port register bit
#define UART_RX_ODC     ODCDbits.ODCD4 // GPIO port open drain configuration register bit
#define UART_RX_CNPU    CNPUDbits.CNPUD4 // GPIO port pull-up resistor register bit
#define UART_RX_CNPD    CNPDDbits.CNPDD4 // GPIO port pull-down resistor register bit
#define UART_RX_CNEN0   CNEN0Dbits.CNEN0D4 // GPIO port change notification Enable register bit
#define UART_RX_CNSTAT  CNSTATDbits.CNSTATD4 // GPIO port change notification Status register bit
#define UART_RX_CNEN1   CNEN1Dbits.CNEN1D4 // GPIO port change notification Edge Select Enable register bit
#define UART_RX_CNF     CNFDbits.CNFD4 // GPIO port change notification flag bit register bit
#define UART_RX_RP      68 // Number of Remappable Pin
#define UART_RX_SET     { asm volatile ("bset _LATD, #4 \n"); }
#define UART_RX_CLEAR   { asm volatile ("bclr _LATD, #4 \n"); }
#define UART_RX_TOGGLE  { asm volatile ("btg  _LATD, #4 \n"); }
#define UART_RX_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define UART_RX_INIT_OUTPUT  {UART_RX_WR = PINSTATE_LOW; UART_RX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_RX_INIT_INPUT   {UART_RX_WR = PINSTATE_HIGH; UART_RX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #55 is RD3
#define UART_TX_TRIS    TRISDbits.TRISD3 // GPIO direction register bit
#define UART_TX_WR      LATDbits.LATD3 // GPIO port latch register bit
#define UART_TX_RD      PORTDbits.RD3 // GPIO port register bit
#define UART_TX_ODC     ODCDbits.ODCD3 // GPIO port open drain configuration register bit
#define UART_TX_CNPU    CNPUDbits.CNPUD3 // GPIO port pull-up resistor register bit
#define UART_TX_CNPD    CNPDDbits.CNPDD3 // GPIO port pull-down resistor register bit
#define UART_TX_CNEN0   CNEN0Dbits.CNEN0D3 // GPIO port change notification Enable register bit
#define UART_TX_CNSTAT  CNSTATDbits.CNSTATD3 // GPIO port change notification Status register bit
#define UART_TX_CNEN1   CNEN1Dbits.CNEN1D3 // GPIO port change notification Edge Select Enable register bit
#define UART_TX_CNF     CNFDbits.CNFD3 // GPIO port change notification flag bit register bit
#define UART_TX_RP      67 // Number of Remappable Pin
#define UART_TX_SET     { asm volatile ("bset _LATD, #3 \n"); }
#define UART_TX_CLEAR   { asm volatile ("bclr _LATD, #3 \n"); }
#define UART_TX_TOGGLE  { asm volatile ("btg  _LATD, #3 \n"); }
#define UART_TX_IS_ANALOG_INPUT  0 // Pin is/is not analog input 
#define UART_TX_INIT_OUTPUT  {UART_TX_WR = PINSTATE_LOW; UART_TX_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output
#define UART_TX_INIT_INPUT   {UART_TX_WR = PINSTATE_HIGH; UART_TX_TRIS = PINDIR_INPUT;} // initialization macro for digital input

// Device Pin #7 is MCLR

// Device Pin #9 is VSS

// Device Pin #10 is VDD

// Device Pin #19 is AVDD

// Device Pin #20 is AVss

// Device Pin #25 is VDD

// Device Pin #26 is VSS

// Device Pin #40 is VSS

// Device Pin #41 is VDD

// Device Pin #56 is VSS

// Device Pin #57 is VDD


#endif	/* __MA33048_P33CK_R30_PINMAP_H__ */
