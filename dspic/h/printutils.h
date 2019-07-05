
/**********************************************************************
Copyright(c) 2018 Microchip Technology Inc. and its subsidiaries.
Subject to your compliance with these terms, you may use Microchip
software and any derivatives exclusively with Microchip products. It
is your responsibility to comply with third party license terms
applicable to your use of third-party software (including open source
software) that may accompany Microchip software.
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
FOR A PARTICULAR PURPOSE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THIS SOFTWARE.
**********************************************************************/

#ifndef PRINTUTILS_H
#define	PRINTUTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "uart1.h"
#include "lcd.h"
#include "delay.h"
#include <stdio.h>

#define PRINT_LCD_ENABLED    1
#define PRINT_SERIAL_ENABLED 1

// the string sent to PrinSerial macro, including formatting, must not exceed this size    
#define __print_serial_size 64
#define __print_lcd_size    32


static inline void UartSendText(char *pstring)
{
    while (*pstring != '\0')
    {
        while(UART1_TransmitBufferIsFull())
            ;
        UART1_Write(*pstring++);
    }
}

#if PRINT_SERIAL_ENABLED
  #define PrintSerialInit()  do{  UartSendText("\n\r"); } while(0)
  #define PrintSerial(...)   do{char __print_utils_string[__print_serial_size]; sprintf(__print_utils_string, __VA_ARGS__); UartSendText(__print_utils_string); } while(0)
#else // PRINT_SERIAL_ENABLED
  #define PrintSerialInit(BAUDRATE)
  #define PrintSerial(...)
#endif //PRINT_SERIAL_ENABLED


#if PRINT_LCD_ENABLED
  #define PrintLcdInit(   )         do{LcdInit(); } while(0)
  #define PrintLcd(LINE, ...)       do{char __print_utils_string[__print_lcd_size]; sprintf(__print_utils_string, __VA_ARGS__); LcdType(LINE, __print_utils_string); } while(0)
#else // PRINT_LCD_ENABLED
  #define PrintLcdInit()
  #define PrintLcd(...)
#endif //PRINT_LCD_ENABLED

    
#ifdef	__cplusplus
}
#endif

#endif	/* PRINTUTILS_H */

