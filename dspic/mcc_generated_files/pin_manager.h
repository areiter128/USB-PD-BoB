/**
  System Interrupts Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : 1.75.1
        Device            :  dsPIC33CK256MP505
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB             :  MPLAB X v5.05

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>
/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA0, high using LATA0.

  @Description
    Sets the GPIO pin, RA0, high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 high (1)
    IO_RA0_SetHigh();
    </code>

*/
#define IO_RA0_SetHigh()          _LATA0 = 1
/**
  @Summary
    Sets the GPIO pin, RA0, low using LATA0.

  @Description
    Sets the GPIO pin, RA0, low using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 low (0)
    IO_RA0_SetLow();
    </code>

*/
#define IO_RA0_SetLow()           _LATA0 = 0
/**
  @Summary
    Toggles the GPIO pin, RA0, using LATA0.

  @Description
    Toggles the GPIO pin, RA0, using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA0
    IO_RA0_Toggle();
    </code>

*/
#define IO_RA0_Toggle()           _LATA0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA0.

  @Description
    Reads the value of the GPIO pin, RA0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA0
    postValue = IO_RA0_GetValue();
    </code>

*/
#define IO_RA0_GetValue()         _RA0
/**
  @Summary
    Configures the GPIO pin, RA0, as an input.

  @Description
    Configures the GPIO pin, RA0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an input
    IO_RA0_SetDigitalInput();
    </code>

*/
#define IO_RA0_SetDigitalInput()  _TRISA0 = 1
/**
  @Summary
    Configures the GPIO pin, RA0, as an output.

  @Description
    Configures the GPIO pin, RA0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an output
    IO_RA0_SetDigitalOutput();
    </code>

*/
#define IO_RA0_SetDigitalOutput() _TRISA0 = 0
/**
  @Summary
    Sets the GPIO pin, RA3, high using LATA3.

  @Description
    Sets the GPIO pin, RA3, high using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA3 high (1)
    IO_RA3_SetHigh();
    </code>

*/
#define IO_RA3_SetHigh()          _LATA3 = 1
/**
  @Summary
    Sets the GPIO pin, RA3, low using LATA3.

  @Description
    Sets the GPIO pin, RA3, low using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA3 low (0)
    IO_RA3_SetLow();
    </code>

*/
#define IO_RA3_SetLow()           _LATA3 = 0
/**
  @Summary
    Toggles the GPIO pin, RA3, using LATA3.

  @Description
    Toggles the GPIO pin, RA3, using LATA3.

  @Preconditions
    The RA3 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA3
    IO_RA3_Toggle();
    </code>

*/
#define IO_RA3_Toggle()           _LATA3 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RA3.

  @Description
    Reads the value of the GPIO pin, RA3.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA3
    postValue = IO_RA3_GetValue();
    </code>

*/
#define IO_RA3_GetValue()         _RA3
/**
  @Summary
    Configures the GPIO pin, RA3, as an input.

  @Description
    Configures the GPIO pin, RA3, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA3 as an input
    IO_RA3_SetDigitalInput();
    </code>

*/
#define IO_RA3_SetDigitalInput()  _TRISA3 = 1
/**
  @Summary
    Configures the GPIO pin, RA3, as an output.

  @Description
    Configures the GPIO pin, RA3, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA3 as an output
    IO_RA3_SetDigitalOutput();
    </code>

*/
#define IO_RA3_SetDigitalOutput() _TRISA3 = 0
/**
  @Summary
    Sets the GPIO pin, RB13, high using LATB13.

  @Description
    Sets the GPIO pin, RB13, high using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 high (1)
    IO_RB13_SetHigh();
    </code>

*/
#define IO_RB13_SetHigh()          _LATB13 = 1
/**
  @Summary
    Sets the GPIO pin, RB13, low using LATB13.

  @Description
    Sets the GPIO pin, RB13, low using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB13 low (0)
    IO_RB13_SetLow();
    </code>

*/
#define IO_RB13_SetLow()           _LATB13 = 0
/**
  @Summary
    Toggles the GPIO pin, RB13, using LATB13.

  @Description
    Toggles the GPIO pin, RB13, using LATB13.

  @Preconditions
    The RB13 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB13
    IO_RB13_Toggle();
    </code>

*/
#define IO_RB13_Toggle()           _LATB13 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB13.

  @Description
    Reads the value of the GPIO pin, RB13.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB13
    postValue = IO_RB13_GetValue();
    </code>

*/
#define IO_RB13_GetValue()         _RB13
/**
  @Summary
    Configures the GPIO pin, RB13, as an input.

  @Description
    Configures the GPIO pin, RB13, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an input
    IO_RB13_SetDigitalInput();
    </code>

*/
#define IO_RB13_SetDigitalInput()  _TRISB13 = 1
/**
  @Summary
    Configures the GPIO pin, RB13, as an output.

  @Description
    Configures the GPIO pin, RB13, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB13 as an output
    IO_RB13_SetDigitalOutput();
    </code>

*/
#define IO_RB13_SetDigitalOutput() _TRISB13 = 0
/**
  @Summary
    Sets the GPIO pin, RB14, high using LATB14.

  @Description
    Sets the GPIO pin, RB14, high using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 high (1)
    IO_RB14_SetHigh();
    </code>

*/
#define IO_RB14_SetHigh()          _LATB14 = 1
/**
  @Summary
    Sets the GPIO pin, RB14, low using LATB14.

  @Description
    Sets the GPIO pin, RB14, low using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB14 low (0)
    IO_RB14_SetLow();
    </code>

*/
#define IO_RB14_SetLow()           _LATB14 = 0
/**
  @Summary
    Toggles the GPIO pin, RB14, using LATB14.

  @Description
    Toggles the GPIO pin, RB14, using LATB14.

  @Preconditions
    The RB14 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB14
    IO_RB14_Toggle();
    </code>

*/
#define IO_RB14_Toggle()           _LATB14 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB14.

  @Description
    Reads the value of the GPIO pin, RB14.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB14
    postValue = IO_RB14_GetValue();
    </code>

*/
#define IO_RB14_GetValue()         _RB14
/**
  @Summary
    Configures the GPIO pin, RB14, as an input.

  @Description
    Configures the GPIO pin, RB14, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an input
    IO_RB14_SetDigitalInput();
    </code>

*/
#define IO_RB14_SetDigitalInput()  _TRISB14 = 1
/**
  @Summary
    Configures the GPIO pin, RB14, as an output.

  @Description
    Configures the GPIO pin, RB14, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB14 as an output
    IO_RB14_SetDigitalOutput();
    </code>

*/
#define IO_RB14_SetDigitalOutput() _TRISB14 = 0
/**
  @Summary
    Sets the GPIO pin, RB15, high using LATB15.

  @Description
    Sets the GPIO pin, RB15, high using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 high (1)
    IO_RB15_SetHigh();
    </code>

*/
#define IO_RB15_SetHigh()          _LATB15 = 1
/**
  @Summary
    Sets the GPIO pin, RB15, low using LATB15.

  @Description
    Sets the GPIO pin, RB15, low using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB15 low (0)
    IO_RB15_SetLow();
    </code>

*/
#define IO_RB15_SetLow()           _LATB15 = 0
/**
  @Summary
    Toggles the GPIO pin, RB15, using LATB15.

  @Description
    Toggles the GPIO pin, RB15, using LATB15.

  @Preconditions
    The RB15 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB15
    IO_RB15_Toggle();
    </code>

*/
#define IO_RB15_Toggle()           _LATB15 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB15.

  @Description
    Reads the value of the GPIO pin, RB15.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB15
    postValue = IO_RB15_GetValue();
    </code>

*/
#define IO_RB15_GetValue()         _RB15
/**
  @Summary
    Configures the GPIO pin, RB15, as an input.

  @Description
    Configures the GPIO pin, RB15, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an input
    IO_RB15_SetDigitalInput();
    </code>

*/
#define IO_RB15_SetDigitalInput()  _TRISB15 = 1
/**
  @Summary
    Configures the GPIO pin, RB15, as an output.

  @Description
    Configures the GPIO pin, RB15, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB15 as an output
    IO_RB15_SetDigitalOutput();
    </code>

*/
#define IO_RB15_SetDigitalOutput() _TRISB15 = 0
/**
  @Summary
    Sets the GPIO pin, RB5, high using LATB5.

  @Description
    Sets the GPIO pin, RB5, high using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB5 high (1)
    TEST1_SetHigh();
    </code>

*/
#define TEST1_SetHigh()          _LATB5 = 1
/**
  @Summary
    Sets the GPIO pin, RB5, low using LATB5.

  @Description
    Sets the GPIO pin, RB5, low using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB5 low (0)
    TEST1_SetLow();
    </code>

*/
#define TEST1_SetLow()           _LATB5 = 0
/**
  @Summary
    Toggles the GPIO pin, RB5, using LATB5.

  @Description
    Toggles the GPIO pin, RB5, using LATB5.

  @Preconditions
    The RB5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB5
    TEST1_Toggle();
    </code>

*/
#define TEST1_Toggle()           _LATB5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB5.

  @Description
    Reads the value of the GPIO pin, RB5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB5
    postValue = TEST1_GetValue();
    </code>

*/
#define TEST1_GetValue()         _RB5
/**
  @Summary
    Configures the GPIO pin, RB5, as an input.

  @Description
    Configures the GPIO pin, RB5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB5 as an input
    TEST1_SetDigitalInput();
    </code>

*/
#define TEST1_SetDigitalInput()  _TRISB5 = 1
/**
  @Summary
    Configures the GPIO pin, RB5, as an output.

  @Description
    Configures the GPIO pin, RB5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB5 as an output
    TEST1_SetDigitalOutput();
    </code>

*/
#define TEST1_SetDigitalOutput() _TRISB5 = 0
/**
  @Summary
    Sets the GPIO pin, RB7, high using LATB7.

  @Description
    Sets the GPIO pin, RB7, high using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB7 high (1)
    IO_RB7_SetHigh();
    </code>

*/
#define IO_RB7_SetHigh()          _LATB7 = 1
/**
  @Summary
    Sets the GPIO pin, RB7, low using LATB7.

  @Description
    Sets the GPIO pin, RB7, low using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB7 low (0)
    IO_RB7_SetLow();
    </code>

*/
#define IO_RB7_SetLow()           _LATB7 = 0
/**
  @Summary
    Toggles the GPIO pin, RB7, using LATB7.

  @Description
    Toggles the GPIO pin, RB7, using LATB7.

  @Preconditions
    The RB7 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB7
    IO_RB7_Toggle();
    </code>

*/
#define IO_RB7_Toggle()           _LATB7 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RB7.

  @Description
    Reads the value of the GPIO pin, RB7.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB7
    postValue = IO_RB7_GetValue();
    </code>

*/
#define IO_RB7_GetValue()         _RB7
/**
  @Summary
    Configures the GPIO pin, RB7, as an input.

  @Description
    Configures the GPIO pin, RB7, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB7 as an input
    IO_RB7_SetDigitalInput();
    </code>

*/
#define IO_RB7_SetDigitalInput()  _TRISB7 = 1
/**
  @Summary
    Configures the GPIO pin, RB7, as an output.

  @Description
    Configures the GPIO pin, RB7, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB7 as an output
    IO_RB7_SetDigitalOutput();
    </code>

*/
#define IO_RB7_SetDigitalOutput() _TRISB7 = 0
/**
  @Summary
    Sets the GPIO pin, RC0, high using LATC0.

  @Description
    Sets the GPIO pin, RC0, high using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC0 high (1)
    channel_AN12_SetHigh();
    </code>

*/
#define channel_AN12_SetHigh()          _LATC0 = 1
/**
  @Summary
    Sets the GPIO pin, RC0, low using LATC0.

  @Description
    Sets the GPIO pin, RC0, low using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC0 low (0)
    channel_AN12_SetLow();
    </code>

*/
#define channel_AN12_SetLow()           _LATC0 = 0
/**
  @Summary
    Toggles the GPIO pin, RC0, using LATC0.

  @Description
    Toggles the GPIO pin, RC0, using LATC0.

  @Preconditions
    The RC0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC0
    channel_AN12_Toggle();
    </code>

*/
#define channel_AN12_Toggle()           _LATC0 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC0.

  @Description
    Reads the value of the GPIO pin, RC0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC0
    postValue = channel_AN12_GetValue();
    </code>

*/
#define channel_AN12_GetValue()         _RC0
/**
  @Summary
    Configures the GPIO pin, RC0, as an input.

  @Description
    Configures the GPIO pin, RC0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC0 as an input
    channel_AN12_SetDigitalInput();
    </code>

*/
#define channel_AN12_SetDigitalInput()  _TRISC0 = 1
/**
  @Summary
    Configures the GPIO pin, RC0, as an output.

  @Description
    Configures the GPIO pin, RC0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC0 as an output
    channel_AN12_SetDigitalOutput();
    </code>

*/
#define channel_AN12_SetDigitalOutput() _TRISC0 = 0
/**
  @Summary
    Sets the GPIO pin, RC1, high using LATC1.

  @Description
    Sets the GPIO pin, RC1, high using LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC1 high (1)
    channel_AN13_SetHigh();
    </code>

*/
#define channel_AN13_SetHigh()          _LATC1 = 1
/**
  @Summary
    Sets the GPIO pin, RC1, low using LATC1.

  @Description
    Sets the GPIO pin, RC1, low using LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC1 low (0)
    channel_AN13_SetLow();
    </code>

*/
#define channel_AN13_SetLow()           _LATC1 = 0
/**
  @Summary
    Toggles the GPIO pin, RC1, using LATC1.

  @Description
    Toggles the GPIO pin, RC1, using LATC1.

  @Preconditions
    The RC1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC1
    channel_AN13_Toggle();
    </code>

*/
#define channel_AN13_Toggle()           _LATC1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC1.

  @Description
    Reads the value of the GPIO pin, RC1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC1
    postValue = channel_AN13_GetValue();
    </code>

*/
#define channel_AN13_GetValue()         _RC1
/**
  @Summary
    Configures the GPIO pin, RC1, as an input.

  @Description
    Configures the GPIO pin, RC1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC1 as an input
    channel_AN13_SetDigitalInput();
    </code>

*/
#define channel_AN13_SetDigitalInput()  _TRISC1 = 1
/**
  @Summary
    Configures the GPIO pin, RC1, as an output.

  @Description
    Configures the GPIO pin, RC1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC1 as an output
    channel_AN13_SetDigitalOutput();
    </code>

*/
#define channel_AN13_SetDigitalOutput() _TRISC1 = 0
/**
  @Summary
    Sets the GPIO pin, RC4, high using LATC4.

  @Description
    Sets the GPIO pin, RC4, high using LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC4 high (1)
    LCD_SDI_SetHigh();
    </code>

*/
#define LCD_SDI_SetHigh()          _LATC4 = 1
/**
  @Summary
    Sets the GPIO pin, RC4, low using LATC4.

  @Description
    Sets the GPIO pin, RC4, low using LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC4 low (0)
    LCD_SDI_SetLow();
    </code>

*/
#define LCD_SDI_SetLow()           _LATC4 = 0
/**
  @Summary
    Toggles the GPIO pin, RC4, using LATC4.

  @Description
    Toggles the GPIO pin, RC4, using LATC4.

  @Preconditions
    The RC4 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC4
    LCD_SDI_Toggle();
    </code>

*/
#define LCD_SDI_Toggle()           _LATC4 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC4.

  @Description
    Reads the value of the GPIO pin, RC4.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC4
    postValue = LCD_SDI_GetValue();
    </code>

*/
#define LCD_SDI_GetValue()         _RC4
/**
  @Summary
    Configures the GPIO pin, RC4, as an input.

  @Description
    Configures the GPIO pin, RC4, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC4 as an input
    LCD_SDI_SetDigitalInput();
    </code>

*/
#define LCD_SDI_SetDigitalInput()  _TRISC4 = 1
/**
  @Summary
    Configures the GPIO pin, RC4, as an output.

  @Description
    Configures the GPIO pin, RC4, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC4 as an output
    LCD_SDI_SetDigitalOutput();
    </code>

*/
#define LCD_SDI_SetDigitalOutput() _TRISC4 = 0
/**
  @Summary
    Sets the GPIO pin, RC5, high using LATC5.

  @Description
    Sets the GPIO pin, RC5, high using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC5 high (1)
    LCD_SCL_SetHigh();
    </code>

*/
#define LCD_SCL_SetHigh()          _LATC5 = 1
/**
  @Summary
    Sets the GPIO pin, RC5, low using LATC5.

  @Description
    Sets the GPIO pin, RC5, low using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC5 low (0)
    LCD_SCL_SetLow();
    </code>

*/
#define LCD_SCL_SetLow()           _LATC5 = 0
/**
  @Summary
    Toggles the GPIO pin, RC5, using LATC5.

  @Description
    Toggles the GPIO pin, RC5, using LATC5.

  @Preconditions
    The RC5 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC5
    LCD_SCL_Toggle();
    </code>

*/
#define LCD_SCL_Toggle()           _LATC5 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC5.

  @Description
    Reads the value of the GPIO pin, RC5.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC5
    postValue = LCD_SCL_GetValue();
    </code>

*/
#define LCD_SCL_GetValue()         _RC5
/**
  @Summary
    Configures the GPIO pin, RC5, as an input.

  @Description
    Configures the GPIO pin, RC5, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC5 as an input
    LCD_SCL_SetDigitalInput();
    </code>

*/
#define LCD_SCL_SetDigitalInput()  _TRISC5 = 1
/**
  @Summary
    Configures the GPIO pin, RC5, as an output.

  @Description
    Configures the GPIO pin, RC5, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC5 as an output
    LCD_SCL_SetDigitalOutput();
    </code>

*/
#define LCD_SCL_SetDigitalOutput() _TRISC5 = 0
/**
  @Summary
    Sets the GPIO pin, RC8, high using LATC8.

  @Description
    Sets the GPIO pin, RC8, high using LATC8.

  @Preconditions
    The RC8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC8 high (1)
    LCD_RST_SetHigh();
    </code>

*/
#define LCD_RST_SetHigh()          _LATC8 = 1
/**
  @Summary
    Sets the GPIO pin, RC8, low using LATC8.

  @Description
    Sets the GPIO pin, RC8, low using LATC8.

  @Preconditions
    The RC8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC8 low (0)
    LCD_RST_SetLow();
    </code>

*/
#define LCD_RST_SetLow()           _LATC8 = 0
/**
  @Summary
    Toggles the GPIO pin, RC8, using LATC8.

  @Description
    Toggles the GPIO pin, RC8, using LATC8.

  @Preconditions
    The RC8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC8
    LCD_RST_Toggle();
    </code>

*/
#define LCD_RST_Toggle()           _LATC8 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC8.

  @Description
    Reads the value of the GPIO pin, RC8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC8
    postValue = LCD_RST_GetValue();
    </code>

*/
#define LCD_RST_GetValue()         _RC8
/**
  @Summary
    Configures the GPIO pin, RC8, as an input.

  @Description
    Configures the GPIO pin, RC8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC8 as an input
    LCD_RST_SetDigitalInput();
    </code>

*/
#define LCD_RST_SetDigitalInput()  _TRISC8 = 1
/**
  @Summary
    Configures the GPIO pin, RC8, as an output.

  @Description
    Configures the GPIO pin, RC8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC8 as an output
    LCD_RST_SetDigitalOutput();
    </code>

*/
#define LCD_RST_SetDigitalOutput() _TRISC8 = 0
/**
  @Summary
    Sets the GPIO pin, RC9, high using LATC9.

  @Description
    Sets the GPIO pin, RC9, high using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC9 high (1)
    LCD_RS_SetHigh();
    </code>

*/
#define LCD_RS_SetHigh()          _LATC9 = 1
/**
  @Summary
    Sets the GPIO pin, RC9, low using LATC9.

  @Description
    Sets the GPIO pin, RC9, low using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RC9 low (0)
    LCD_RS_SetLow();
    </code>

*/
#define LCD_RS_SetLow()           _LATC9 = 0
/**
  @Summary
    Toggles the GPIO pin, RC9, using LATC9.

  @Description
    Toggles the GPIO pin, RC9, using LATC9.

  @Preconditions
    The RC9 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RC9
    LCD_RS_Toggle();
    </code>

*/
#define LCD_RS_Toggle()           _LATC9 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RC9.

  @Description
    Reads the value of the GPIO pin, RC9.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RC9
    postValue = LCD_RS_GetValue();
    </code>

*/
#define LCD_RS_GetValue()         _RC9
/**
  @Summary
    Configures the GPIO pin, RC9, as an input.

  @Description
    Configures the GPIO pin, RC9, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC9 as an input
    LCD_RS_SetDigitalInput();
    </code>

*/
#define LCD_RS_SetDigitalInput()  _TRISC9 = 1
/**
  @Summary
    Configures the GPIO pin, RC9, as an output.

  @Description
    Configures the GPIO pin, RC9, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RC9 as an output
    LCD_RS_SetDigitalOutput();
    </code>

*/
#define LCD_RS_SetDigitalOutput() _TRISC9 = 0
/**
  @Summary
    Sets the GPIO pin, RD1, high using LATD1.

  @Description
    Sets the GPIO pin, RD1, high using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD1 high (1)
    BUTTON_SetHigh();
    </code>

*/
#define BUTTON_SetHigh()          _LATD1 = 1
/**
  @Summary
    Sets the GPIO pin, RD1, low using LATD1.

  @Description
    Sets the GPIO pin, RD1, low using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD1 low (0)
    BUTTON_SetLow();
    </code>

*/
#define BUTTON_SetLow()           _LATD1 = 0
/**
  @Summary
    Toggles the GPIO pin, RD1, using LATD1.

  @Description
    Toggles the GPIO pin, RD1, using LATD1.

  @Preconditions
    The RD1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD1
    BUTTON_Toggle();
    </code>

*/
#define BUTTON_Toggle()           _LATD1 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD1.

  @Description
    Reads the value of the GPIO pin, RD1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD1
    postValue = BUTTON_GetValue();
    </code>

*/
#define BUTTON_GetValue()         _RD1
/**
  @Summary
    Configures the GPIO pin, RD1, as an input.

  @Description
    Configures the GPIO pin, RD1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD1 as an input
    BUTTON_SetDigitalInput();
    </code>

*/
#define BUTTON_SetDigitalInput()  _TRISD1 = 1
/**
  @Summary
    Configures the GPIO pin, RD1, as an output.

  @Description
    Configures the GPIO pin, RD1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD1 as an output
    BUTTON_SetDigitalOutput();
    </code>

*/
#define BUTTON_SetDigitalOutput() _TRISD1 = 0
/**
  @Summary
    Sets the GPIO pin, RD10, high using LATD10.

  @Description
    Sets the GPIO pin, RD10, high using LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD10 high (1)
    channel_AN18_SetHigh();
    </code>

*/
#define channel_AN18_SetHigh()          _LATD10 = 1
/**
  @Summary
    Sets the GPIO pin, RD10, low using LATD10.

  @Description
    Sets the GPIO pin, RD10, low using LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD10 low (0)
    channel_AN18_SetLow();
    </code>

*/
#define channel_AN18_SetLow()           _LATD10 = 0
/**
  @Summary
    Toggles the GPIO pin, RD10, using LATD10.

  @Description
    Toggles the GPIO pin, RD10, using LATD10.

  @Preconditions
    The RD10 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD10
    channel_AN18_Toggle();
    </code>

*/
#define channel_AN18_Toggle()           _LATD10 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD10.

  @Description
    Reads the value of the GPIO pin, RD10.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD10
    postValue = channel_AN18_GetValue();
    </code>

*/
#define channel_AN18_GetValue()         _RD10
/**
  @Summary
    Configures the GPIO pin, RD10, as an input.

  @Description
    Configures the GPIO pin, RD10, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD10 as an input
    channel_AN18_SetDigitalInput();
    </code>

*/
#define channel_AN18_SetDigitalInput()  _TRISD10 = 1
/**
  @Summary
    Configures the GPIO pin, RD10, as an output.

  @Description
    Configures the GPIO pin, RD10, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD10 as an output
    channel_AN18_SetDigitalOutput();
    </code>

*/
#define channel_AN18_SetDigitalOutput() _TRISD10 = 0
/**
  @Summary
    Sets the GPIO pin, RD8, high using LATD8.

  @Description
    Sets the GPIO pin, RD8, high using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD8 high (1)
    LCD_CS_SetHigh();
    </code>

*/
#define LCD_CS_SetHigh()          _LATD8 = 1
/**
  @Summary
    Sets the GPIO pin, RD8, low using LATD8.

  @Description
    Sets the GPIO pin, RD8, low using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RD8 low (0)
    LCD_CS_SetLow();
    </code>

*/
#define LCD_CS_SetLow()           _LATD8 = 0
/**
  @Summary
    Toggles the GPIO pin, RD8, using LATD8.

  @Description
    Toggles the GPIO pin, RD8, using LATD8.

  @Preconditions
    The RD8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RD8
    LCD_CS_Toggle();
    </code>

*/
#define LCD_CS_Toggle()           _LATD8 ^= 1
/**
  @Summary
    Reads the value of the GPIO pin, RD8.

  @Description
    Reads the value of the GPIO pin, RD8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RD8
    postValue = LCD_CS_GetValue();
    </code>

*/
#define LCD_CS_GetValue()         _RD8
/**
  @Summary
    Configures the GPIO pin, RD8, as an input.

  @Description
    Configures the GPIO pin, RD8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD8 as an input
    LCD_CS_SetDigitalInput();
    </code>

*/
#define LCD_CS_SetDigitalInput()  _TRISD8 = 1
/**
  @Summary
    Configures the GPIO pin, RD8, as an output.

  @Description
    Configures the GPIO pin, RD8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RD8 as an output
    LCD_CS_SetDigitalOutput();
    </code>

*/
#define LCD_CS_SetDigitalOutput() _TRISD8 = 0

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the dsPIC33CK256MP505
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize(void);

#endif
