
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
#include "system.h"
#include "delay.h"
#include "button.h"
#include "compensator.h"
#include "initComp.h"
#include "printutils.h"
#include "proto24.h"
#include "interrupt_manager.h"
#include "pin_manager.h"

#define LOGGING_ENABLED

// these numbers are 10ms multiples: ie 100 means 1000ms 
#define LCD_TIME_INTERVAL     50

#if (defined TEST_ENABLED) && (defined LOGGING_ENABLED)
    #undef LOGGING_ENABLED
#endif // (defined TEST_ENABLED) && (defined LOGGING_ENABLED)


#ifdef LOGGING_ENABLED
#define LOG_TIME_INTERVAL     100
#endif // LOGGING_ENABLED

#ifdef TEST_ENABLED
extern void testApp(protocol_data_t *pProto);
#endif // TEST_ENABLED


typedef enum{
    PAGE_MIN,
    PAGE_VOLTAGES,
    PAGE_VIN_TEMP,
    PAGE_LOAD_BUCK,
    PAGE_LOAD_BOOST,
    PAGE_BUCK_FAULTS,
    PAGE_BOOST_FAULTS,
    PAGE_MAX
}page_num_t;

typedef struct{
    double     voltage_buck;
    double     voltage_boost;
    double     voltage_input;
    double     load_buck;
    double     step_load_buck;
    double     load_boost;
    double     step_load_boost;
    uint8_t    temperature;
    uint8_t    packet_counter;
    page_num_t page_number;
    uint8_t    fault_ocp_buck:1;
    uint8_t    fault_ovp_buck:1;
    uint8_t    fault_ocp_boost:1;
    uint8_t    fault_ovp_boost:1;
    uint8_t    fault_reg_buck:1;
    uint8_t    fault_reg_boost:1;
    uint8_t    :2;
} print_data_t;

static volatile bool lcd_timer_event = false;
volatile bool buck_event = false, boost_event = false;

void   mainLcdShow(print_data_t *pData);
void   mainDataExtract(protocol_data_t *pProto, print_data_t *pData);
double mainGetLoadBuck(uint8_t bits);
double mainGetLoadBoost(uint8_t bits);

#ifdef LOGGING_ENABLED
    static volatile bool log_timer_event = false;
    void   mainLogData(print_data_t    *pData);
    void   mainLogComm(protocol_data_t *pData);
#else // LOGGING_ENABLED
    #define mainLogData(...)
    #define mainLogComm(...)
#endif  // LOGGING_ENABLED


extern void BuckSoftStartInit(void);
extern void BoostSoftStartInit(void);  
extern volatile bool restartConverterFlag;

int main(void)
{
   
    protocol_data_t proto24_data;
#ifndef TEST_ENABLED
    print_data_t    printout_data;
#endif //TEST_ENABLED

    INTERRUPT_GlobalDisable();
    SYSTEM_Initialize();
    
    COMPENSATOR_Initialize();       // Initializes both converters compensators
    
    // Set up Buck converter PWM / Slope Compensation DAC/CMP / SoftStart
    BuckSoftStartInit();
    ConverterBuckInit();
    
    // Set up Boost converter PWM / Slope Compensation DAC/CMP / SoftStart 
    BoostSoftStartInit();
    ConverterBoostInit(); 
    
    DACCTRL1Lbits.CLKSEL = 2;
    DAC3CONLbits.DACEN   = 1;          /* Turn ON DAC */
    //DAC3CONLbits.DACOEN  = 1;         
    DAC3DATH = 0;
    DACCTRL1Lbits.DACON  = 1;         
    
    
    INTERRUPT_GlobalEnable();       // Enable interrupts now

    ButtonInit();
    PrintSerialInit();
    PrintSerial("   MICROCHIP    \r\n");
    PrintSerial("dsPIC33CK256MP505\n\r");

    PrintLcdInit();    
    PrintLcd(0,"MICROCHIP  dsPIC");
    PrintLcd(1,"  33CK256MP505  ");

    __delay_ms(200); // due to heavy workload on ISR, delays take ~3.7 times longer than normal
    Proto24Init(&proto24_data);
    Proto24Send(PROTO_SYS_RESET);
    
    
#ifndef TEST_ENABLED
    __delay_ms(400); // due to heavy workload on ISR, delays take ~3.7 times longer than normal
    //initialize the printout data, to avoid garbage before any communication from pic24
    mainDataExtract(&proto24_data, &printout_data);
    printout_data.voltage_buck   = GetVoltageBuck();
    printout_data.voltage_boost  = GetVoltageBoost();
    printout_data.voltage_input  = GetVoltageInput();
    printout_data.packet_counter = 0;
    printout_data.page_number    = PAGE_VOLTAGES;

    while(1)
    {
        uint8_t button_event;
        if(Proto24Check(&proto24_data)) // each time something comes from the Pic24
        {
            mainDataExtract(&proto24_data, &printout_data);
        }
        
        if(lcd_timer_event)
        {
            lcd_timer_event = false;
            printout_data.voltage_buck  = GetVoltageBuck();
            printout_data.voltage_boost = GetVoltageBoost();
            printout_data.voltage_input = GetVoltageInput();
            printout_data.fault_reg_buck  = buck_event; 
            printout_data.fault_reg_boost = boost_event;
            mainLcdShow(&printout_data);
        }
        
        #ifdef LOGGING_ENABLED
        if(log_timer_event)
        {
            log_timer_event = false;
            mainLogData(&printout_data);
            mainLogComm(&proto24_data);
        }
        #endif // LOGGING_ENABLED

        button_event = ButtonEvent();
        if(button_event != BUTTON_OFF)
        {
            page_num_t pageNumber = printout_data.page_number;
            if(button_event == BUTTON_SHORT)
            {
                if(++pageNumber >= PAGE_MAX)
                    pageNumber = PAGE_MIN + 1;
            } else if(button_event == BUTTON_LONG)
            {
                if(--pageNumber <= PAGE_MIN)
                    pageNumber = PAGE_MAX - 1;
            }
            printout_data.page_number = pageNumber;
            mainLcdShow(&printout_data);
        }
    }
#else  // TEST_ENABLED
    testApp(&proto24_data);
    while(1);
#endif  // TEST_ENABLED
    return -1; //this is to avoid compilation warning, but should never get here
}

// LCD printing is done here
void mainLcdShow(print_data_t *pData)
{
    switch(pData->page_number)
    {
        case PAGE_VOLTAGES:
            PrintLcd(0, "Vbuck  =  %2.2f V   ", pData->voltage_buck);
            PrintLcd(1, "Vboost = %2.2f V    ", pData->voltage_boost);
        break;
        case PAGE_LOAD_BUCK:
        {
            double volt2 = pData->voltage_buck * pData->voltage_buck;
            PrintLcd(0, "P buck = %1.2f W    ", volt2 * pData->load_buck);
            PrintLcd(1, "step   = %1.2f W    ", volt2 * pData->step_load_buck);
        }
        break;
        case PAGE_LOAD_BOOST:
        {
            double volt2 = pData->voltage_boost * pData->voltage_boost;
            PrintLcd(0, "Pboost = %1.2f W    ", volt2 * pData->load_boost);
            PrintLcd(1, "step   = %1.2f W    ", volt2 * pData->step_load_boost);
        }
        break;
        case PAGE_VIN_TEMP:
            PrintLcd(0,"Vin  =  %2.2f V   ", pData->voltage_input);
            PrintLcd(1,"Temp = %d deg C   ", pData->temperature);
        break;
        case PAGE_BUCK_FAULTS:
            PrintLcd(0,"Buck faults:    ");
            PrintLcd(1,"OC %d OV %d REG %d ", pData->fault_ocp_buck,  pData->fault_ovp_buck, pData->fault_reg_buck);
        break;
        case PAGE_BOOST_FAULTS:
            PrintLcd(0,"Boost faults:   ");
            PrintLcd(1,"OC %d OV %d REG %d ", pData->fault_ocp_boost,  pData->fault_ovp_boost, pData->fault_reg_boost);
        break;
        default:
            PrintLcd(0,"Firmware error !");
            PrintLcd(1,"                ");
        break;
    }
}

// copy data from the protocol structure to the printing structure
void mainDataExtract(protocol_data_t *pProto, print_data_t *pData)
{
    pData->temperature     = pProto->temperature;
    pData->load_buck       = mainGetLoadBuck(pProto->load_status.buck_still);
    pData->step_load_buck  = mainGetLoadBuck(pProto->load_status.buck_blink);
    pData->load_boost      = mainGetLoadBoost(pProto->load_status.boost_still);
    pData->step_load_boost = mainGetLoadBoost(pProto->load_status.boost_blink);
    pData->fault_ocp_buck  = pProto->fault_status.fault_ocp_buck;
    pData->fault_ovp_buck  = pProto->fault_status.fault_ovp_buck;
    pData->fault_ocp_boost = pProto->fault_status.fault_ocp_boost;
    pData->fault_ovp_boost = pProto->fault_status.fault_ovp_boost;
    pData->packet_counter++;
}

//returns 1/ohms, because the loads are in parallel
double mainGetLoadBuck(uint8_t bits)
{
    double retval = 0.0;
    if(bits & 4)
        retval = 1.0/6.65;
    if(bits & 2)
        retval = retval + 1.0/8.25;
    if(bits & 1)
        retval = retval + 1.0/33.0;
    return retval;
}

//returns 1/ohms
double mainGetLoadBoost(uint8_t bits)
{
    double retval = 0.0;
    if(bits & 4)
        retval = 1.0/150.0;
    if(bits & 2)
        retval = retval + 1.0/215.0;
    if(bits & 1)
        retval = retval + 1.0/499.0;
    return retval;
}

// get here by timer interrupt at each 10 ms
void  TMR1_CallBack(void)
{
    static uint16_t lcd_timer = 0;
    static uint8_t faultRestartCnt = 0;
#ifdef LOGGING_ENABLED
    static uint16_t log_timer = 0;
#endif // LOGGING_ENABLED
    Proto24Tick();
    ButtonTask();
       
    // Fault has been removed for X-duration (10ms increments)
    if(restartConverterFlag == true)
    {
        if(++faultRestartCnt == FAULT_RESTART_TIME)
        {    
            // Recall softstart 
            _CCT1IE = 0;
            BuckSoftStartInit();
            BoostSoftStartInit();
            PG1IOCONLbits.OVRENH = 0;
            PG1IOCONLbits.OVRENL = 0;
            PG2IOCONLbits.OVRENL = 0;
            _CCT1IE = 1;

            buck_event = false;
            boost_event = false;
            restartConverterFlag = 0;
        }
    }
    else
        faultRestartCnt = 0;
    
    if(++lcd_timer == LCD_TIME_INTERVAL)
    {
        lcd_timer = 0;
        lcd_timer_event = true;
    }
#ifdef LOGGING_ENABLED
    if(++log_timer == LOG_TIME_INTERVAL)
    {
        log_timer = 0;
        log_timer_event = true;
    }
#endif // LOGGING_ENABLED
    
}

#ifdef LOGGING_ENABLED
// serial logging / monitoring (115200 8N1)
void mainLogData(print_data_t *pData)
{
    double volt2;
    PrintSerial("==================================\n\r");
    PrintSerial("Packet count = %d\n\r", pData->packet_counter);
    PrintSerial("Vbuck  =  %2.2f V\n\r", pData->voltage_buck);
    PrintSerial("Vboost = %2.2f V\n\r", pData->voltage_boost);
    PrintSerial("Vinput =  %2.2f V\n\r", pData->voltage_input);
    PrintSerial("Temp   = %d deg C\n\r",  pData->temperature);
    volt2 = pData->voltage_buck * pData->voltage_buck;
    PrintSerial("P buck = %1.2f W, ", volt2 * pData->load_buck);
    PrintSerial("step = %1.2f W\n\r", volt2 * pData->step_load_buck);
    volt2 = pData->voltage_boost * pData->voltage_boost;
    PrintSerial("Pboost = %1.2f W, ", volt2 * pData->load_boost);
    PrintSerial("step = %1.2f W\n\r", volt2 * pData->step_load_boost);
    PrintSerial("Buck faults:  OCP %d, OVP %d, REG %d\n\r", pData->fault_ocp_buck,  pData->fault_ovp_buck, pData->fault_reg_buck);
    PrintSerial("Boost faults: OCP %d, OVP %d, REG %d\n\r", pData->fault_ocp_boost, pData->fault_ovp_boost, pData->fault_reg_boost);
}

void   mainLogComm(protocol_data_t *pData)
{
    uint8_t *pBin = (uint8_t *)pData;
    int i;
    PrintSerial("Raw PIC24 incoming data:");
    for(i = 0; i < sizeof(protocol_data_t); i++)
        PrintSerial(" %02x", pBin[i]);
    PrintSerial("\n\r");
}
#endif // LOGGING_ENABLED

