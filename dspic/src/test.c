
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

/* Including header files */
#include <xc.h>
#include <float.h>
#include "delay.h"
#include "button.h"
#include "compensator.h"
#include "printutils.h"
#include "proto24.h"

#define SIZE_OF(X)      (sizeof(X)/sizeof(X[0]))
#define MIN(X,Y)        (((X)<(Y))?(X):(Y))
#define MIN3(X, Y, Z)   MIN(MIN(X,Y),Z)

#define abs_dbl(x)   ((x)>=0.0)?(x):(0.0 - (x))
#define abs_s16(x)   (((x)>=0)?(x):(0 - (x)))

typedef bool     (*pftest_t)(protocol_data_t *);
typedef uint16_t (*pfread_u16_t)(void);
typedef double   (*pfread_dbl_t)(void);


static bool testSerial         (protocol_data_t *pProto);
static bool testP24com         (protocol_data_t *pProto);
static bool testP24ledsUbutton (protocol_data_t *pProto);
static bool testP24btn1        (protocol_data_t *pProto);
static bool testP24btn2        (protocol_data_t *pProto);
static bool testNoLoad         (protocol_data_t *pProto);
static bool testFullLoad       (protocol_data_t *pProto);
static bool testStepLoad       (protocol_data_t *pProto);
static bool testThermal        (protocol_data_t *pProto);


static void testShowResults(uint16_t);
static bool _analizeSamples_dbl(pfread_dbl_t pFunc, double   min, double   max, double   dev, double   avg, double   err, uint16_t count);
static bool _analizeSamples_u16(pfread_u16_t pFunc, uint16_t min, uint16_t max, uint16_t dev, uint16_t avg, uint16_t err, uint16_t count);


pftest_t TestHandlers[] = {testSerial,
                                    testP24com,
                                    testP24ledsUbutton,
                                    testP24btn1,
                                    testP24btn2,
                                    testNoLoad,
                                    testFullLoad,
                                    testStepLoad,
                                    testThermal
                                   };

char    *TestStrings[] = {"PC comm",
                                   "PIC24 comm",
                                   "9 LEDs blinking / user button",
                                   "buck load button",
                                   "boost load button",
                                   "regulators without load",
                                   "regulators with full load",
                                   "regulators with stepping load",
                                   "thermal"
                                  };

uint16_t  TestTimes[]  = {60, 55, 50, 45, 40, 35, 30, 25, 20};

#define NUM_TESTS    MIN3(SIZE_OF(TestHandlers), SIZE_OF(TestStrings), SIZE_OF(TestTimes))

#define DELAY_ADJ_FACTOR      0.27
#define DELAY_MS_ADJUSTED(x)  __delay_ms((unsigned long)(x * DELAY_ADJ_FACTOR))


void testApp(protocol_data_t *pProto)
{
    uint16_t results = UINT16_MAX;
    uint8_t  i;
        
    PrintLcd(0,"DPSK TESTING... ");    
    PrintLcd(1,"                ");
    PrintSerial("=============================================================\n\r");
    PrintSerial("DURING TEST, DO NOT PRESS ANY BUTTONS ON DPSK,\n\r");
    PrintSerial("EXCEPT FOR THE EXPLICIT SITUATIONS\n\r");
    
    for(i = 0; i < NUM_TESTS; i++)
    {
        PrintSerial("***********************************************************\n\r");
        PrintSerial("%d/%d Testing %s - estimated remaining time %d s\n\r", i+1, NUM_TESTS, TestStrings[i], TestTimes[i]);
        if(TestHandlers[i](pProto))
        {
            PrintSerial(" Failed!\n\r");
        }
        else
        {
            PrintSerial(" PASSED\n\r");
            results &= ~(1<<i);
        }
    }
    PrintSerial("=============================================================\n\r");
    testShowResults(results);
    PrintSerial("THE END\n\r");
    PrintSerial("=============================================================\n\r");
    DELAY_MS_ADJUSTED(500);
}

static void testShowResults(uint16_t results)
{
    uint8_t i, errors = 0;
    PrintSerial("RESULTS 0x%04X\n\r", results);
    for(i = 0; i < NUM_TESTS; i++)
    {
        char *testResult;
        if(results & (1<<i)) {
            errors++;
            testResult = "FAILED";
        } else {
            testResult = "PASSED";
        }
        PrintSerial("Test no. %d - %s - %s\n\r", i + 1, testResult, TestStrings[i]);
    }
    if(errors)
        PrintSerial("%d tests failed\n\r", errors);
    else
        PrintSerial("***** SUCCESS! *****\n\r");
}

static bool _waitSpecificKey(char *pString, uint16_t timeout)
{
    // ret 'true'  for timeout 
    // ret 'false' for success
    bool ret_code = true;
    timeout = timeout >> 4; // divide it by 16
    do
    {
        DELAY_MS_ADJUSTED(16);
        if(!UART1_ReceiveBufferIsEmpty())
        {
            char ch = (char)UART1_Read();
            char *ptr;
            for(ptr = pString; '\0' != *ptr; ptr++)
            {
                if(*ptr == ch)
                {
                    ret_code = false;
                    break;
                }
            }
        }
        if(false == ret_code)
            break;
    } while(timeout--);
    return ret_code;
}


static bool testSerial(protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    PrintSerial("Press 'y' or 'Y' to continue (timeout 5s) ");
    ret_code = _waitSpecificKey("yY", 5000);
    return ret_code;
}

static bool testP24ledsUbutton(protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    uint8_t timeout_counter = 200; // it takes around 10s
    uint8_t btn_count = 0;
    PrintSerial(" if ALL 9 LEDs are blinking, ");
    PrintSerial("press user button 3 times (timeout 10s) ");
    Proto24Init(pProto);
    Proto24Send(PROTO_SYS_RESET);
    DELAY_MS_ADJUSTED(600);
    Proto24Send(PROTO_TEST_ON);

    while(timeout_counter--)
    {
        DELAY_MS_ADJUSTED(50);
        Proto24Check(pProto);
        if(BUTTON_SHORT == ButtonEvent())
        {
            btn_count++;
            PrintSerial(".");
                if(btn_count > 2)
                {
                    ret_code = false;
                    break;
                }
        }
    }
    Proto24Send(PROTO_TEST_OFF);
    DELAY_MS_ADJUSTED(50);
    return ret_code;
}

static bool testP24btn1(protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    uint8_t timeout_counter = 100; // it takes around 5s
//    Proto24Init(pProto);
//    Proto24Send(PROTO_SYS_RESET);
//    DELAY_MS_ADJUSTED(600);
    PrintSerial("press BUCK LOAD button 3 times (timeout 5s) ");

    while(timeout_counter--)
    {
        DELAY_MS_ADJUSTED(50);
        Proto24Check(pProto);
        if(pProto->load_status.buck_still == 7)
        {
            PrintSerial(" pressed 3 times ");
            ret_code = false;
            break;
        }
    }
  //  Proto24Send(PROTO_SYS_RESET);
  //  DELAY_MS_ADJUSTED(100);
    return ret_code;
}

static bool testP24btn2(protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    uint8_t timeout_counter = 100; // it takes around 5s
    Proto24Init(pProto);
 //   Proto24Send(PROTO_SYS_RESET);
 //   DELAY_MS_ADJUSTED(600);
    PrintSerial("press BOOST LOAD button 3 times (timeout 5s) ");

    while(timeout_counter--)
    {
        DELAY_MS_ADJUSTED(50);
        Proto24Check(pProto);
        if(pProto->load_status.boost_still == 7)
        {
            PrintSerial(" pressed 3 times ");
            ret_code = false;
            break;
        }
    }
    Proto24Send(PROTO_SYS_RESET);
    DELAY_MS_ADJUSTED(100);
    return ret_code;
}



static bool testNoLoad         (protocol_data_t *pProto)
{
    bool ret_code; // true means failed
    (void) pProto;
    /*                       pFunc,        min,  max,  dev,  avg,  err,  count */
    ret_code = 0;
    PrintSerial("\n\rinput voltage: ");
    if(_analizeSamples_dbl(GetVoltageInput, 6.0, 14.0, 2.0, 9.0, 0.6, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck voltage:  ");
    if(_analizeSamples_dbl(GetVoltageBuck, 3.0, 3.5, 1.0, 3.3, 0.2, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost voltage: ");
    if(_analizeSamples_dbl(GetVoltageBoost, 14.4, 15.4, 1.0, 15.0, 0.3, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck DAC:      ");
    if(_analizeSamples_u16(GetDacBuck, 0, 300, 200, 50, 40, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost DAC:     ");
    if(_analizeSamples_u16(GetDacBoost, 800, 1800, 300, 1500, 400, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\r");
    return ret_code;
}

static bool testFullLoad         (protocol_data_t *pProto)
{
    bool ret_code; // true means failed
    Proto24Init(pProto);
    Proto24Send(PROTO_SYS_RESET);    DELAY_MS_ADJUSTED(600);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(500);

    ret_code = 0;
    /*                       pFunc,        min,  max,  dev,  avg,  err,  count */
    PrintSerial("\n\rinput voltage: ");
    if(_analizeSamples_dbl(GetVoltageInput, 6.0, 14.0, 2.0, 9.0, 0.6, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck voltage:  ");
    if(_analizeSamples_dbl(GetVoltageBuck, 3.0, 3.5, 1.0, 3.3, 0.2, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost voltage: ");
    if(_analizeSamples_dbl(GetVoltageBoost, 14.4, 15.4, 1.0, 15.0, 0.3, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck DAC:      ");
    if(_analizeSamples_u16(GetDacBuck, 2000, 2600, 300, 2400, 100, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost DAC:     ");
    if(_analizeSamples_u16(GetDacBoost, 2000, 2900, 300, 2500, 300, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\r");
    Proto24Send(PROTO_SYS_RESET);   DELAY_MS_ADJUSTED(500);
    return ret_code;
}

static bool testStepLoad         (protocol_data_t *pProto)
{
    bool ret_code; // true means failed
    Proto24Init(pProto);
    Proto24Send(PROTO_SYS_RESET);    DELAY_MS_ADJUSTED(1000);
    Proto24Send(PROTO_LONG_BUCK);    DELAY_MS_ADJUSTED(500);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_LONG_BOOST);   DELAY_MS_ADJUSTED(500);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(500);

    ret_code = 0;
    /*                      pFunc,        min,  max,  dev,  avg,  err,  count */
    PrintSerial("\n\rinput voltage: ");
    if(_analizeSamples_dbl(GetVoltageInput, 6.0, 14.0, 2.0, 9.0, 0.6, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck voltage:  ");
    if(_analizeSamples_dbl(GetVoltageBuck, 3.0, 3.5, 1.0, 3.3, 0.2, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost voltage: ");
    if(_analizeSamples_dbl(GetVoltageBoost, 14.4, 15.4, 1.0, 15.0, 0.3, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rbuck DAC:      ");
    if(_analizeSamples_u16(GetDacBuck, 0, 2700, 2700, 1300, 600, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\rboost DAC:     ");
    if(_analizeSamples_u16(GetDacBoost, 800, 2900, 1200, 2200, 500, 100))
    {   PrintSerial(" !");  ret_code |= 1;  }
    PrintSerial("\n\r");
    Proto24Send(PROTO_SYS_RESET);    DELAY_MS_ADJUSTED(500);
    return ret_code;
}



static bool _analizeSamples_dbl(pfread_dbl_t pFunc, double min, double max, double dev, double avg, double err, uint16_t count)
{
    bool ret_code = true; // true means failed
    double min_val, max_val, avg_val;
    uint16_t samples = 0;
    
    min_val =  FLT_MAX;
    max_val = -FLT_MAX;
    avg_val = 0;

    while(count--)
    {
        double val;
        DELAY_MS_ADJUSTED(11);
        val = pFunc();
        if(val < min_val)
            min_val = val;
        if(val > max_val)
            max_val = val;
        avg_val = avg_val + val;
        samples++;
    }
    avg_val = avg_val / samples;
    PrintSerial("min=%2.3f, max=%2.3f, dev=%2.3f, avg=%2.3f", min_val, max_val, max_val-min_val, avg_val);
    
    if(max_val <= max)
    {
        if(min_val >= min)
        {
            if((max_val - min_val) <= dev)
            {
                if(abs_dbl(avg_val - avg) <= err)
                {
                    ret_code = false;
                }
            }
        }
    }
    return ret_code;
}

static bool _analizeSamples_u16(pfread_u16_t pFunc, uint16_t min, uint16_t max, uint16_t dev, uint16_t avg, uint16_t err, uint16_t count)
{
    bool ret_code = true; // true means failed
    uint16_t min_val, max_val;
    uint32_t avg_val;
    uint16_t samples = 0;
    
    min_val = UINT16_MAX;
    max_val = 0;
    avg_val = 0;

    while(count--)
    {
        uint16_t val;
        DELAY_MS_ADJUSTED(11);
        val = pFunc();
        if(val < min_val)
            min_val = val;
        if(val > max_val)
            max_val = val;
        avg_val = avg_val + val;
        samples++;
    }
    avg_val = avg_val / samples;
    PrintSerial("min=%d, max=%d, dev=%d, avg=%d", min_val, max_val, max_val-min_val, (int)avg_val);
    
    if(max_val <= max)
    {
        if(min_val >= min)
        {
            if((max_val - min_val) <= dev)
            {
                int16_t s16_temp = avg_val - avg;
                if(abs_s16(s16_temp) <= (int16_t)err)
                {
                    ret_code = false;
                }
            }
        }
    }
    return ret_code;
}


static bool testP24com(protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    uint8_t timeout_counter = 100; // it takes around 5s
    uint8_t rx_count = 0;
    Proto24Init(pProto);
    Proto24Send(PROTO_SYS_RESET);

    while(timeout_counter--)
    {
        DELAY_MS_ADJUSTED(50);
        if(Proto24Check(pProto)) // each time something comes from the Pic24
        {
            rx_count++;
        }
    }
    PrintSerial("received %d packets", rx_count);
    if(rx_count > 3)
        ret_code = false;
    return ret_code;
}

static uint8_t _readTemperature(protocol_data_t *pProto)
{
    uint8_t temperature = 255; // undefined temp
    uint8_t timeout_counter = 15; // 1.5 seconds timeout
    
    while(timeout_counter--)
    {
        DELAY_MS_ADJUSTED(100);
        if(Proto24Check(pProto))
        {
            temperature = pProto->temperature;
            break;
        }
    }
    return temperature;
}

static bool testThermal        (protocol_data_t *pProto)
{
    bool ret_code = true; // true means failed
    uint8_t temp0 = 0, temp1 = 0, temp2 = 0;
    
    temp0 = _readTemperature(pProto);
    if(temp0 == 255)
        goto exit;
    PrintSerial("initial temperature = %d deg C", temp0);
    if(temp0 > 40)
    {
        PrintSerial("\n\rWARNING! Board is too hot, temperature test may fail. ");
        PrintSerial("Cool it down and repeat the test.");
    }

    Proto24Init(pProto);
    Proto24Send(PROTO_SYS_RESET);    DELAY_MS_ADJUSTED(600);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BUCK);   DELAY_MS_ADJUSTED(200);
    Proto24Send(PROTO_SHORT_BOOST);  DELAY_MS_ADJUSTED(500);

    temp1 = _readTemperature(pProto);
    if(temp1 == 255)
        goto exit;

    PrintSerial("\n\rtemperature 1 = %d deg C\n\r", temp1);
    PrintSerial("... heating 15s ...\n\r");
    DELAY_MS_ADJUSTED(15000);
    temp2 = _readTemperature(pProto);
    if(temp2 == 255)
        goto exit;

    PrintSerial("temperature 2 = %d deg C\n\r", temp2);
    if((temp2 - temp1) >= 5)
        ret_code = false;
exit:
    Proto24Send(PROTO_SYS_RESET);    DELAY_MS_ADJUSTED(500);
    return ret_code;
}
