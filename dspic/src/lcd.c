
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

#include <xc.h>
#include "delay.h"
#include "pin_manager.h"

//******************************************************/
//		LCD DEFINES
//******************************************************/

#define LCD_RS_COMMAND     LCD_RS_SetLow
#define LCD_RS_DATA        LCD_RS_SetHigh

#define LCD_CS_nSELECTED   LCD_CS_SetHigh
#define LCD_CS_SELECTED    LCD_CS_SetLow


//******************************************************/
//		LCD Prototypes
//******************************************************/

//extern void LCD_Init(void);
void lcd_clear(void);
void lcd_goto(uint8_t x, uint8_t y);
void lcd_putchar(const char c);
void lcd_putstr(const char *s);
void lcd_putcmd(uint8_t Command);
void lcd_putline(uint8_t l, const char *s);
void lcd_backlight_on(void);
void lcd_backlight_off(void);


//----------------------------------------------------------------------------



//******************************************************/
//		LCD_cmds Defines
//******************************************************/
// Command set for the LCD LCD driver used by the Newhaven NHD-C0216CZ-FSW-FBW

#define LCD_CLEAR       0x01
#define LCD_HOME        0x02

#define CURSOR_nSHIFT   0x00
#define CURSOR_SHIFT    0x01
#define DATA_DECREMENT  0x00
#define DATA_INCREMENT  0x02
#define LCD_ENTRY_MODE  0x04

#define CURSOR_OFF      0x00
#define CURSOR_ON       0x02
#define BLINK_OFF       0x00
#define BLINK_ON        0x01
#define LCD_DISPLAY_OFF 0x08
#define LCD_DISPLAY_ON  0x0C


#define FUNCTION_nIS    0x00
#define FUNCTION_IS     0x01
#define FUNCTION_1_HIGH 0x00
#define FUNCTION_2_HIGH 0x04
#define FUNCTION_1_LINE 0x00
#define FUNCTION_2_LINE 0x08
#define FUNCTION_4BITS  0x00
#define FUNCTION_8BITS  0x10

#define LCD_FUNCTION    0x20

#define LCD_CGRAM_ADDRESS(adr) (0x40 | (adr & 0x3F))
#define LCD_DDRAM_ADDRESS(adr) (0x80 | (adr & 0x7F))

//** Second Instruction Page (IS)
#define BIAS_1_5      0x00
#define BIAS_1_4      0x08
#define FREQ_CNTRL(f) (f&0x07)
#define LCD_OSC_FREQ  0x10


#define LCD_ICON_ADDRESS(adr) (0x40 | (adr & 0x0F))

#define nICON           0x00
#define ICON            0x08
#define nBOOST          0x00
#define BOOSTLCD        0x04
#define CONTRAST(c)    (c&0x03)
#define LCD_PWR_CONTROL 0x50

#define FOLLOWER_GAIN(g) (g&0x07)
#define LCD_FOLLOWER_OFF   0x60
#define LCD_FOLLOWER_ON    0x68

#define LCD_CONTRAST(c) (0x70 | (c & 0x0F))

#define LCD_BUSY_FLAG_MASK 0x80
#define LCD_ADDRESS_MASK   0x7F

#define LCD_ADDRESS_LINE_1 0x00
#define LCD_ADDRESS_LINE_2 0x40


const int8_t line_address[] = {LCD_ADDRESS_LINE_1,LCD_ADDRESS_LINE_2};

///////////////////////////////////////////////////////////////////////////////
// Function:             SPI_TX
//
// PreCondition: 	LCD must be setup.
//
// Side Effects: 	Writes to screen
//
///////////////////////////////////////////////////////////////////////////////
// @ingroup  		LCD
//
// @brief    		This function writes to the LCD screen.
//
// @note    			Send byte via spi to the lcd
//
///////////////////////////////////////////////////////////////////////////////
void SPI_TX(uint8_t Command)
{
  uint8_t mask;

   for(mask = 0x80; mask != 0; mask >>= 1)
   {
     LCD_SCL_SetLow();
     Nop();
     __delay_us(1);
     if(Command & mask) LCD_SDI_SetHigh();
     else LCD_SDI_SetLow();
     LCD_SCL_SetHigh();
     Nop();
     __delay_us(1);
    }
    LCD_CS_nSELECTED();
    __delay_us(50);
}



//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_goto
//
// PreCondition: 	None
//
// Side Effects: 	Moves cursor.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// @ingroup  		LCD
//
// @brief    		This function points to an LCD position.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void lcd_goto(uint8_t x,uint8_t y)
{
    lcd_putcmd(LCD_DDRAM_ADDRESS((line_address[y] + x)));
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_clear
//
// PreCondition: 	None
//
// Side Effects: 	Clears LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function clears the LCD screen.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void lcd_clear(void)
{
    lcd_putcmd(LCD_CLEAR);   //clear
    __delay_us(20);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putline
//
// PreCondition: 	None
//
// Side Effects: 	None
///
///
// @ingroup  		LCD
//
// @brief    		This function sends an LCD message.
//
// @note    		Sends LCD message and line location
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putline(uint8_t l, const char *buffer)
{
    lcd_putcmd(line_address[l]);
    lcd_putstr(buffer);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putstr
//
// PreCondition: 	None
//
// Side Effects: 	Writes message to LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function writes a string to the LCD.
//
// @note    		Write data to LCD up to null
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putstr(const char *s)
{
    while(*s)              
    {
	lcd_putchar(*s++); 
    }
}

/////////////////////////////////////////////////////////////////////////////
// Function:         LCD_Init
//
// PreCondition: 	None
//
// Side Effects: 	Sets up LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function initialises the LCD.
//
// @note    		None
//
//////////////////////////////////////////////////////////////////////////////
void LcdInit(void)
{
   LCD_RST_SetLow();  // RESET
   __delay_ms(25);
   LCD_RST_SetHigh();  // end reset
  
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
 
   __delay_ms(25);

   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_1_LINE | FUNCTION_nIS);   //function set

   // Enter the second page of instructions
   lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_IS);   //function set
   lcd_putcmd(LCD_OSC_FREQ | BIAS_1_5 | FREQ_CNTRL(4));   //internal osc frequency
   lcd_putcmd(LCD_PWR_CONTROL | nICON | BOOSTLCD | CONTRAST(2));   //power control
   lcd_putcmd(LCD_FOLLOWER_ON | FOLLOWER_GAIN(5));   //follower control
   lcd_putcmd(LCD_CONTRAST(0));   //contrast
   // leave second instruction page
   
   //lcd_putcmd(LCD_FUNCTION | FUNCTION_8BITS | FUNCTION_1_HIGH | FUNCTION_2_LINE | FUNCTION_nIS);   //function set
   lcd_putcmd(LCD_DISPLAY_ON | CURSOR_OFF | BLINK_OFF);           //display on
   lcd_putcmd(LCD_ENTRY_MODE | CURSOR_nSHIFT | DATA_INCREMENT);   //entry mode
   lcd_putcmd(LCD_CLEAR);   //clear

   __delay_ms(150);
}


/////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putcmd
//
// PreCondition: 	None
//
// Side Effects: 	Sends command to the LCD.
//
//
// @ingroup  		LCD
//
// @brief    		This function sends a command to the LCD.
//
// @note    		Send comand byte to the lcd
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putcmd(uint8_t Command)
{		
   LCD_CS_SELECTED();
   LCD_RS_COMMAND();
   SPI_TX(Command);
}

//////////////////////////////////////////////////////////////////////////////
// Function:             lcd_putchar
//
// PreCondition: 	None
//
// Side Effects: 	Puts character on LCD
//
//
// @ingroup  		LCD
//
// @brief    		This function puts a character onto the screen.
//
// @note    		Write data to the lcd
//
//////////////////////////////////////////////////////////////////////////////
void lcd_putchar(const char c)
{
   LCD_CS_SELECTED();
   LCD_RS_DATA();
   SPI_TX(c);
}
//----------------------------------------------------------------------------

void LcdType(uint8_t line_number, const char *string)// line number and string
{
    lcd_goto(0, line_number);
    lcd_putstr(string);
}

