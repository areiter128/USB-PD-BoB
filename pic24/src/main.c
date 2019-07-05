
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

#include "mcc.h"
#include "delay.h"
#include "leds.h"
#include "fault.h"
#include "loads.h"
#include "buttons.h"
#include "temperature.h"
#include "protocol.h"


extern void SysReset(void);

int main(void)
{
    volatile bool  test_mode = false;
    
    SYSTEM_Initialize(); // initialize the device
    LedsInit();          // init the leds matrix
    ButtonsInit();       // init buttons
    LoadsInit();         // init loads control
    FaultInit();         // init the fault detect
    TemperatureInit();   // temperature reading init
    ProtocolInit();      // protocol init
    __delay_ms(500);
    
    
    while (1)
    {
        volatile uint8_t          buttonEvent, temperature;
        volatile protocol_event_t proto_event;
        volatile protocol_data_t  proto_data;
        volatile therm_event_t    therm_event;

        therm_event = TemperatureCheck(&temperature);
        proto_data.temperature = temperature;
        proto_data.load_status.u16 = (test_mode)? 0 : LoadsGetStatus();
        proto_data.fault_status.u8 = (test_mode)? 0 : FaultCheck();
        proto_event = ProtocolCheck(&proto_data);

        //protocol events
        switch(proto_event)
        {
            case PROTO_SHORT_BUCK:  LoadsStateMachine(LOADS_SBUTTON_BUCK);  break;
            case PROTO_SHORT_BOOST: LoadsStateMachine(LOADS_SBUTTON_BOOST); break;
            case PROTO_LONG_BUCK:   LoadsStateMachine(LOADS_LBUTTON_BUCK);  break;
            case PROTO_LONG_BOOST:  LoadsStateMachine(LOADS_LBUTTON_BOOST); break;
            case PROTO_SYS_RESET:   ProtocolClose(); __delay_ms(500); SysReset(); break;
            case PROTO_TEST_ON:     LoadsInit(); test_mode = true;  do{uint8_t i; for(i = 0; i < LED_MAX; i++) LedBlink(i); }while(0); break;
            case PROTO_TEST_OFF:    LoadsInit(); test_mode = false; do{uint8_t i; for(i = 0; i < LED_MAX; i++) LedOff(i);   }while(0); break;
            default: break;
        }

        if(test_mode == false)
        {
            // thermal events
            if(therm_event == THERM_SAFE)
            {
                LedOff(LED_THERMAL_ERROR);
                LoadsStateMachine(LOADS_THERM_SAFE);
            }
            else if(therm_event == THERM_ALERT)
            {
                LedBlink(LED_THERMAL_ERROR);
                LoadsStateMachine(LOADS_THERM_ALERT);
            }
            else if(therm_event == THERM_WARNING)
            {
                LedOn(LED_THERMAL_ERROR);
                LoadsStateMachine(LOADS_THERM_SAFE);
            }

            //button events
            buttonEvent = ButtonEventBuck();
            if(buttonEvent == BUTTON_SHORT)
                LoadsStateMachine(LOADS_SBUTTON_BUCK);
            else if(buttonEvent == BUTTON_LONG)
                LoadsStateMachine(LOADS_LBUTTON_BUCK);
            buttonEvent = ButtonEventBoost();
            if(buttonEvent == BUTTON_SHORT)
                LoadsStateMachine(LOADS_SBUTTON_BOOST);
            else if(buttonEvent == BUTTON_LONG)
                LoadsStateMachine(LOADS_LBUTTON_BOOST);
        }
    }
    return -1;
}

void  TMR1_CallBack(void)
{
    static uint8_t nTick = 0;
        
    switch(nTick)
    {   // every 1.0 ms call
        case 0: LedsMatrixTask(); break;
        case 1: ButtonsTask();    break;
        case 2: FaultTask();      break;
        case 3: LedsBlinkTask();  break;
        case 4: LoadsTask();      break;
        default: nTick = 0;       break;
    }
    nTick++;
    if(nTick >= 5) nTick = 0;
    
    ProtocolTick();
    
}