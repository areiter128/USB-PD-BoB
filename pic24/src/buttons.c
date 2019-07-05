
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
#include "buttons.h"
#include "interrupt_manager.h"
#include "pin_manager.h"

#define BUTTON_BUCK_PIN  BUTTON_BUCK_GetValue()
#define BUTTON_BOOST_PIN BUTTON_BOOST_GetValue()

// defined buttons ids
#define BUTTON_BUCK      0
#define BUTTON_BOOST     1

#define NUM_BUTTONS      2
#define BUTTON_PRESSED   0 // low level active button
#define BUTTON_RELEASED  1
#define SCAN_PERIOD      ( 5 * NUM_BUTTONS)   // 5ms
#define DEBOUNCE_TIME    (30 / SCAN_PERIOD)   // 30ms
#define LONG_PRESS_TIME  (1500 / SCAN_PERIOD) //1500ms !!max 2.5seconds !!

typedef struct
{
  uint8_t        debouncer; // debouncing timer
  uint8_t        timer;     // long press timer
  uint8_t        event;     // event to be passed to the calling function
  bool           state;     // previous state
} button_data_t;

static volatile button_data_t buttonArray[NUM_BUTTONS];

void ButtonsInit(void)
{
    NoInterrupts();
    buttonArray[BUTTON_BUCK].debouncer = 0;
    buttonArray[BUTTON_BUCK].timer     = 0;
    buttonArray[BUTTON_BUCK].event     = 0;
    buttonArray[BUTTON_BUCK].state     = BUTTON_RELEASED;

    buttonArray[BUTTON_BOOST].debouncer = 0;
    buttonArray[BUTTON_BOOST].timer     = 0;
    buttonArray[BUTTON_BOOST].event     = 0;
    buttonArray[BUTTON_BOOST].state     = BUTTON_RELEASED;
    Interrupts();
}

static bool _ButtonRead(uint8_t id)
{
    switch(id)
    {
        case BUTTON_BUCK:  return BUTTON_BUCK_PIN;
        case BUTTON_BOOST: return BUTTON_BOOST_PIN;
        default: return BUTTON_RELEASED;
    }
}

uint8_t ButtonEventBuck(void)
{
  uint8_t ret;
  NoInterrupts();
  ret = buttonArray[BUTTON_BUCK].event;
  buttonArray[BUTTON_BUCK].event = BUTTON_OFF;
  Interrupts();
  return ret;
}

uint8_t ButtonEventBoost(void)
{
  uint8_t ret;
  NoInterrupts();
  ret = buttonArray[BUTTON_BOOST].event;
  buttonArray[BUTTON_BOOST].event = BUTTON_OFF;
  Interrupts();
  return ret;
}


// called each 5 ms
void ButtonsTask(void)
{
  static uint8_t scan = 0;
  bool input_state = _ButtonRead(scan);
  bool last_state = buttonArray[scan].state;

  if(input_state == last_state)
  {
      buttonArray[scan].debouncer = 0; // (re)start debouncing counter
      if((input_state == BUTTON_PRESSED) && (buttonArray[scan].timer < LONG_PRESS_TIME))
      {
          buttonArray[scan].timer++;
          if(buttonArray[scan].timer == LONG_PRESS_TIME)
              buttonArray[scan].event = BUTTON_LONG;
      }
  }
  else
  {
      buttonArray[scan].debouncer++; // increment debouncing counter
      if(buttonArray[scan].debouncer == DEBOUNCE_TIME)
      {
          buttonArray[scan].state = input_state; //debounce time passed, then accept the new state
          buttonArray[scan].debouncer = 0;
          if((input_state == BUTTON_RELEASED) && (buttonArray[scan].timer < LONG_PRESS_TIME))
          {
              buttonArray[scan].event = BUTTON_SHORT;
          }
          buttonArray[scan].timer = 0;
      }
  }
  scan++; if(scan >= NUM_BUTTONS) scan = 0;
}


