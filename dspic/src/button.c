
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
#include "pin_manager.h"
#include "button.h"

#define BUTTON_PIN       BUTTON_GetValue()

#define BUTTON_PRESSED   0 // low level active button
#define BUTTON_RELEASED  1
#define SCAN_PERIOD      (10)   // 10ms
#define DEBOUNCE_TIME    (20 / SCAN_PERIOD)   // 20ms
#define LONG_PRESS_TIME  (1500 / SCAN_PERIOD) //1500ms !!max 2.5seconds !!

typedef struct
{
  uint8_t        debouncer; // debouncing timer
  uint8_t        timer;     // long press timer
  uint8_t        event;     // event to be passed to the calling function
  bool           state;     // previous state
} button_data_t;

static volatile button_data_t buttonData;

void ButtonInit(void)
{
    // button setup
    buttonData.debouncer = 0;
    buttonData.timer     = 0;
    buttonData.event     = 0;
    buttonData.state     = BUTTON_RELEASED;
}


uint8_t ButtonEvent(void)
{
  uint8_t ret;
  ret = buttonData.event;
  buttonData.event = BUTTON_OFF;
  return ret;
}


// called each 10 ms
void ButtonTask(void)
{
  bool input_state = BUTTON_PIN;
  bool last_state = buttonData.state;

  if(input_state == last_state)
  {
      buttonData.debouncer = 0; // (re)start debouncing counter
      if((input_state == BUTTON_PRESSED) && (buttonData.timer < LONG_PRESS_TIME))
      {
          buttonData.timer++;
          if(buttonData.timer == LONG_PRESS_TIME)
              buttonData.event = BUTTON_LONG;
      }
  }
  else
  {
      buttonData.debouncer++; // increment debouncing counter
      if(buttonData.debouncer == DEBOUNCE_TIME)
      {
          buttonData.state = input_state; //debounce time passed, then accept the new state
          buttonData.debouncer = 0;
          if((input_state == BUTTON_RELEASED) && (buttonData.timer < LONG_PRESS_TIME))
          {
              buttonData.event = BUTTON_SHORT;
          }
          buttonData.timer = 0;
      }
  }
}


