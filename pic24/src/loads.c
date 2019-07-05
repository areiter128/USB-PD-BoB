
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
#include "loads.h"
#include "leds.h"
#include "interrupt_manager.h"
#include "pin_manager.h"
#include "proto_data.h"  // included for proto_ldst_t definition

typedef void (*sm_state_t)(loads_event_t, void *);

typedef struct {
    uint8_t volatile set_still;
    uint8_t volatile set_blink;
    sm_state_t       state;
} sm_data_t;

static void _fstate_S0(loads_event_t, void *);
static void _fstate_S1(loads_event_t, void *);
static void _fstate_S2(loads_event_t, void *);
static void _fstate_S3(loads_event_t, void *);
static void _fstate_B1(loads_event_t, void *);
static void _fstate_B2(loads_event_t, void *);
static void _fstate_B3(loads_event_t, void *);
static void _fstate_S0t(loads_event_t, void *);
static void _fstate_S1t(loads_event_t, void *);
static void _fstate_B1t(loads_event_t, void *);

const sm_state_t fstates[] = {
    _fstate_S0,
    _fstate_S1,
    _fstate_S2,
    _fstate_S3,
    _fstate_B1,
    _fstate_B2,
    _fstate_B3,
    _fstate_S0t,
    _fstate_S1t,
    _fstate_B1t
};

const uint8_t stills[] = {
    LOAD_0,                  //S0
    LOAD_1,                  //S1
    LOAD_1 | LOAD_2,         //S2
    LOAD_1 | LOAD_2 | LOAD_3,//S3
    LOAD_1,                  //B1
    LOAD_1 | LOAD_2,         //B2
    LOAD_1,                  //B3
    LOAD_0,                  //S0t
    LOAD_1,                  //S1t
    LOAD_1                   //B1t
};

const uint8_t blinks[] = {
    LOAD_0,                  //S0
    LOAD_0,                  //S1
    LOAD_0,                  //S2
    LOAD_0,                  //S3
    LOAD_2,                  //B1
    LOAD_3,                  //B2
    LOAD_2 | LOAD_3,         //B3
    LOAD_0,                  //S0t
    LOAD_0,                  //S1t
    LOAD_2,                  //B1t
};

#define ENTER_STATE(STATE) do{pdata->set_still = stills[STATE]; pdata->set_blink = blinks[STATE]; pdata->state = fstates[STATE]; }while(0)

enum{
    state_S0,
    state_S1,
    state_S2,
    state_S3,
    state_B1,
    state_B2,
    state_B3,
    state_S0t,
    state_S1t,
    state_B1t,
};

sm_data_t data_buck, data_boost;

static void _LoadSignal(void);

void LoadsInit(void)
{
    sm_data_t *pdata;
    NoInterrupts();
// BUCK
    pdata = &data_buck;
    ENTER_STATE(state_S0);
    LOAD_BUCK_PIN1_SetLow();
    LOAD_BUCK_PIN2_SetLow();
    LOAD_BUCK_PIN3_SetLow();

// BOOST
    pdata = &data_boost;
    ENTER_STATE(state_S0);
    LOAD_BOOST_PIN1_SetLow();
    LOAD_BOOST_PIN2_SetLow();
    LOAD_BOOST_PIN3_SetLow();
    Interrupts();

    _LoadSignal();
}

// drive loads for buck
static void _LoadSetBuck(uint8_t setting)
{
    if(setting & LOAD_BUCK_1)
        LOAD_BUCK_PIN1_SetHigh();
    else
        LOAD_BUCK_PIN1_SetLow();
    if(setting & LOAD_BUCK_2)
        LOAD_BUCK_PIN2_SetHigh();
    else
        LOAD_BUCK_PIN2_SetLow();
    if(setting & LOAD_BUCK_3)
        LOAD_BUCK_PIN3_SetHigh();
    else
        LOAD_BUCK_PIN3_SetLow();
}

// drive loads for boost
static void _LoadSetBoost(uint8_t setting)
{
    if(setting & LOAD_BOOST_1)
        LOAD_BOOST_PIN1_SetHigh();
    else
        LOAD_BOOST_PIN1_SetLow();
    if(setting & LOAD_BOOST_2)
        LOAD_BOOST_PIN2_SetHigh();
    else
        LOAD_BOOST_PIN2_SetLow();
    if(setting & LOAD_BOOST_3)
        LOAD_BOOST_PIN3_SetHigh();
    else
        LOAD_BOOST_PIN3_SetLow();
}

// drive LEDs
static void _LoadSignal(void)
{
    if(data_buck.set_blink & LOAD_BUCK_1)
        LedBlink(LED_BUCK_LOAD_1);
    else if(data_buck.set_still & LOAD_BUCK_1)
        LedOn(LED_BUCK_LOAD_1);
    else
        LedOff(LED_BUCK_LOAD_1);

    if(data_buck.set_blink & LOAD_BUCK_2)
        LedBlink(LED_BUCK_LOAD_2);
    else if(data_buck.set_still & LOAD_BUCK_2)
        LedOn(LED_BUCK_LOAD_2);
    else
        LedOff(LED_BUCK_LOAD_2);

    if(data_buck.set_blink & LOAD_BUCK_3)
        LedBlink(LED_BUCK_LOAD_3);
    else if(data_buck.set_still & LOAD_BUCK_3)
        LedOn(LED_BUCK_LOAD_3);
    else
        LedOff(LED_BUCK_LOAD_3);

    if(data_boost.set_blink & LOAD_BOOST_1)
        LedBlink(LED_BOOST_LOAD_1);
    else if(data_boost.set_still & LOAD_BOOST_1)
        LedOn(LED_BOOST_LOAD_1);
    else
        LedOff(LED_BOOST_LOAD_1);

    if(data_boost.set_blink & LOAD_BOOST_2)
        LedBlink(LED_BOOST_LOAD_2);
    else if(data_boost.set_still & LOAD_BOOST_2)
        LedOn(LED_BOOST_LOAD_2);
    else
        LedOff(LED_BOOST_LOAD_2);

    if(data_boost.set_blink & LOAD_BOOST_3)
        LedBlink(LED_BOOST_LOAD_3);
    else if(data_boost.set_still & LOAD_BOOST_3)
        LedOn(LED_BOOST_LOAD_3);
    else
        LedOff(LED_BOOST_LOAD_3);
}

// this is called every 5ms
void LoadsTask(void)
{
    //100Hz on-off toggling of the loads
    static bool toggle_bit = 0;
    if(toggle_bit)
    {
        _LoadSetBuck(data_buck.set_still   | data_buck.set_blink);
        _LoadSetBoost(data_boost.set_still | data_boost.set_blink);
        toggle_bit = 0;
    }
    else
    {
        _LoadSetBuck(data_buck.set_still   & ~data_buck.set_blink);
        _LoadSetBoost(data_boost.set_still & ~data_boost.set_blink);
        toggle_bit = 1;
    }
}

uint16_t LoadsGetStatus(void)
{
    proto_ldst_t temp16;
    NoInterrupts();
    temp16.buck_still  = data_buck.set_still;
    temp16.buck_blink  = data_buck.set_blink;
    temp16.boost_still = data_boost.set_still;
    temp16.boost_blink = data_boost.set_blink;
    Interrupts();
    return temp16.u16;
}

void LoadsStateMachine(loads_event_t event)
{ // operates over shared variables, so disabling interrupts is needed
    switch(event)
    {
        case LOADS_THERM_SAFE:
        case LOADS_THERM_ALERT:
            NoInterrupts();
            data_buck.state(event, &data_buck);
            Interrupts();
            NoInterrupts();
            data_boost.state(event,&data_boost);
            Interrupts();
            break;
        case LOADS_SBUTTON_BUCK:
        case LOADS_LBUTTON_BUCK:
            NoInterrupts();
            data_buck.state(event, &data_buck);
            Interrupts();
            break;
        case LOADS_SBUTTON_BOOST:
        case LOADS_LBUTTON_BOOST:
            NoInterrupts();
            data_boost.state(event, &data_boost);
            Interrupts();
            break;
        default: break;
    }
    _LoadSignal();
}

/**
 * S0 static 0 - all off
 * S1 static 1 - L1 on
 * S2 static 2 - L12 on
 * S3 static 3 - L123 on
 * S0t static 0 - all off - thermal triggered
 * S1t static 1 - L1 on   - thermal triggered
 * 
 * B1 blinking 1 - L1 on, L2 stepping
 * B2 blinking 2 - L12 on, L3 stepping
 * B3 blinking 3 - L1 on, L23 stepping
 * B1t blinking 1 - L1 on, L2 stepping - thermal triggered
 * 
 * Sx -> Bx   triggered by LBUTTON
 * Bx -> Sx   triggered by LBUTTON
 * Sx advance triggered by SBUTTON
 * Bx advance triggered by SBUTTON
 * Sx -> Sxt  triggered by THRM_ALERT
 * Bx -> Bxt  triggered by THRM_ALERT
 * Sxt -> Sx  triggered by THRM_SAFE
 * Bxt -> Bx  triggered by THRM_SAFE

 *  */

static void _fstate_S0(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S1); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B1); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_S0t); break;
        default: break;
    }
}

static void _fstate_S1(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S2); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B1); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_S1t); break;
        default: break;
    }
}

static void _fstate_S2(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S3); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B2); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_S1t); break;
        default: break;
    }
}

static void _fstate_S3(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S0); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B3); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_S1t); break;
        default: break;
    }
}

static void _fstate_B1(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_B2); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_S1); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_B1t); break;
        default: break;
    }
}

static void _fstate_B2(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_B3); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_S2); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_B1t); break;
        default: break;
    }
}

static void _fstate_B3(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_B1); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_S3); break;
        case LOADS_THERM_ALERT:   ENTER_STATE(state_B1t); break;
        default: break;
    }
}

static void _fstate_S0t(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S1t); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B1t); break;
        case LOADS_THERM_SAFE:    ENTER_STATE(state_S0); break;
        default: break;
    }
}

static void _fstate_S1t(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_SBUTTON_BUCK:
        case LOADS_SBUTTON_BOOST: ENTER_STATE(state_S0t); break;
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_B1t); break;
        case LOADS_THERM_SAFE:    ENTER_STATE(state_S1); break;
        default: break;
    }
}

static void _fstate_B1t(loads_event_t event, void *ptr)
{
    sm_data_t *pdata = (sm_data_t *)ptr;
    switch(event)
    {
        case LOADS_LBUTTON_BUCK:
        case LOADS_LBUTTON_BOOST: ENTER_STATE(state_S1t); break;
        case LOADS_THERM_SAFE:    ENTER_STATE(state_B1); break;
        default: break;
    }
}