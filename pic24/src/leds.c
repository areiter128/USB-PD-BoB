
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
#include <stdbool.h>
#include "leds.h"
#include "interrupt_manager.h"

#define BLINK_RATE 25 // 25 * 5ms * 2 = 250ms blink period

// if these are changed, don't forget to update LedsInit function
#define R1_PORT  LATB
#define R2_PORT  LATA
#define R3_PORT  LATA

#define R1_MASK  (uint16_t)(1<<4)
#define R2_MASK  (uint16_t)(1<<4)
#define R3_MASK  (uint16_t)(1<<9)

#define C1_PORT  LATC
#define C2_PORT  LATC
#define C3_PORT  LATC

#define C1_MASK  (uint16_t)(1<<3)
#define C2_MASK  (uint16_t)(1<<4)
#define C3_MASK  (uint16_t)(1<<5)

typedef struct
{
   uint16_t * const port;
   const uint16_t  mask;
} led_row_t;

typedef struct
{
   uint16_t * const port;
   const uint16_t  mask;
} led_column_t;


static const led_row_t led_rows_array[] = {
                                           {(uint16_t * const)&R1_PORT, R1_MASK},
                                           {(uint16_t * const)&R2_PORT, R2_MASK},
                                           {(uint16_t * const)&R3_PORT, R3_MASK}
                                        };

static const led_column_t led_columns_array[] = {
                                           {(uint16_t * const)&C1_PORT, C1_MASK},
                                           {(uint16_t * const)&C2_PORT, C2_MASK},
                                           {(uint16_t * const)&C3_PORT, C3_MASK}
                                        };

/* status for each LED */
#define LED_OFF    0
#define LED_FULL   1
#define LED_BLINK  2

static volatile uint8_t leds_status_array[9];
static volatile bool leds_matrix[3][3];

void LedsInit(void)
{
    volatile uint8_t i, j;
    NoInterrupts();
    for(i = 0; i < 3; i++)
        for(j = 0; j < 3; j++)
        {
            leds_status_array[i * 3 + j] = 0; // everything is off
            leds_matrix[i][j] = 0;
        }
    
    // rows
    TRISBbits.TRISB4 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA9 = 0;
    // columns
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    TRISCbits.TRISC5 = 0;
    Interrupts();
}

void LedOn(uint8_t led_id)
{
    if(led_id < LED_MAX)
    {
        NoInterrupts();
        leds_status_array[led_id] = LED_FULL;
        Interrupts();
    }
}

void LedOff(uint8_t led_id)
{
    if(led_id < LED_MAX)
    {
        NoInterrupts();
        leds_status_array[led_id] = LED_OFF;
        Interrupts();
    }
}

void LedBlink(uint8_t led_id)
{
    if(led_id < LED_MAX)
    {
        NoInterrupts();
        leds_status_array[led_id] = LED_BLINK;
        Interrupts();
    }
}

// called at each 5 ms
void LedsMatrixTask(void)
{
    static uint8_t row_counter = 0;
    volatile uint8_t column_counter;
    
    // turn the LEDs off before changing the active row
    for(column_counter = 0; column_counter < 3; column_counter++)
    {
        *(led_columns_array[column_counter].port) &= ~(led_columns_array[column_counter].mask); // set to 0 logic
    }
    
    // deactivate the row
    *(led_rows_array[row_counter].port) |= (led_rows_array[row_counter].mask);  //set to 1 logic
     
    row_counter++;
    if(row_counter >= 3)
        row_counter = 0;
    
    // turn the LEDs on accordingly status matrix before activating row
    for(column_counter = 0; column_counter < 3; column_counter++)
    {
        if(leds_matrix[row_counter][column_counter])
            *(led_columns_array[column_counter].port) |=  (led_columns_array[column_counter].mask); // set to 1 logic
        else
            *(led_columns_array[column_counter].port) &= ~(led_columns_array[column_counter].mask); // set to 0 logic
    }
    
    // activate the row
    *(led_rows_array[row_counter].port) &= ~(led_rows_array[row_counter].mask); // set to 0 logic
}

// called at each 5ms
void LedsBlinkTask(void)
{
    static uint8_t blink_counter = 0;
    static bool    blink_toggle = 0;
    volatile uint8_t i, j;
    for(i = 0; i < 3; i++)
      for(j = 0; j < 3; j++)
    {
        uint8_t status = leds_status_array[i * 3 + j];

        switch(status)
        {
            case LED_FULL:
                leds_matrix[i][j] = 1;
                break;
            case LED_BLINK:
                leds_matrix[i][j] = blink_toggle;
                break;
            default:
                leds_matrix[i][j] = 0;
                break;
        }
    }
    
    if(blink_counter == 0)
    {
        blink_counter = BLINK_RATE;
        blink_toggle = !blink_toggle;
    }
    blink_counter--;
}


