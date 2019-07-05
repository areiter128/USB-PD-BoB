
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

#ifndef LOADS_H
#define	LOADS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LOAD_0      (0)
#define LOAD_1      (1<<0)
#define LOAD_2      (1<<1)
#define LOAD_3      (1<<2)

// BUCK loads control definitions
#define LOAD_BUCK_OFF    LOAD_0
#define LOAD_BUCK_1      LOAD_1
#define LOAD_BUCK_2      LOAD_2
#define LOAD_BUCK_3      LOAD_3

// buck loads definitions based on resistor values
#define LOAD_BUCK_33R    LOAD_BUCK_1
#define LOAD_BUCK_8R25   LOAD_BUCK_2
#define LOAD_BUCK_6R65   LOAD_BUCK_3
#define LOAD_BUCK_6R6    (LOAD_BUCK_1 | LOAD_BUCK_2)
#define LOAD_BUCK_5R53   (LOAD_BUCK_1 | LOAD_BUCK_3)
#define LOAD_BUCK_3R68   (LOAD_BUCK_2 | LOAD_BUCK_3)
#define LOAD_BUCK_3R31   (LOAD_BUCK_1 | LOAD_BUCK_2 | LOAD_BUCK_3)

// buck: define load as power, based on 3.3V output
#define LOAD_BUCK_0W33   LOAD_BUCK_1
#define LOAD_BUCK_1W32   LOAD_BUCK_2
#define LOAD_BUCK_1W64   LOAD_BUCK_3
#define LOAD_BUCK_1W65   (LOAD_BUCK_1 | LOAD_BUCK_2)
#define LOAD_BUCK_1W97   (LOAD_BUCK_1 | LOAD_BUCK_3)
#define LOAD_BUCK_2W96   (LOAD_BUCK_2 | LOAD_BUCK_3)
#define LOAD_BUCK_3W29   (LOAD_BUCK_1 | LOAD_BUCK_2 | LOAD_BUCK_3)

// buck: define load as current, based on 3.3V output
#define LOAD_BUCK_100mA  LOAD_BUCK_1
#define LOAD_BUCK_400mA  LOAD_BUCK_2
#define LOAD_BUCK_496mA  LOAD_BUCK_3
#define LOAD_BUCK_500mA  (LOAD_BUCK_1 | LOAD_BUCK_2)
#define LOAD_BUCK_596mA  (LOAD_BUCK_1 | LOAD_BUCK_3)
#define LOAD_BUCK_896mA  (LOAD_BUCK_2 | LOAD_BUCK_3)
#define LOAD_BUCK_996mA  (LOAD_BUCK_1 | LOAD_BUCK_2 | LOAD_BUCK_3)


//BOOST loads control definitions
#define LOAD_BOOST_OFF  LOAD_0
#define LOAD_BOOST_1    LOAD_1
#define LOAD_BOOST_2    LOAD_2
#define LOAD_BOOST_3    LOAD_3

//boost loads definitions based on resistor values
#define LOAD_BOOST_499R   LOAD_BOOST_1
#define LOAD_BOOST_215R   LOAD_BOOST_2
#define LOAD_BOOST_150R   LOAD_BOOST_3
#define LOAD_BOOST_150R3  (LOAD_BOOST_1 | LOAD_BOOST_2)
#define LOAD_BOOST_115R3  (LOAD_BOOST_1 | LOAD_BOOST_3)
#define LOAD_BOOST_88R4   (LOAD_BOOST_2 | LOAD_BOOST_3)
#define LOAD_BOOST_75R1   (LOAD_BOOST_1 | LOAD_BOOST_2 | LOAD_BOOST_3)

//boost: define load as power, based on 15V output
#define LOAD_BOOST_0W45   LOAD_BOOST_1
#define LOAD_BOOST_1W05   LOAD_BOOST_2
#define LOAD_BOOST_1W50   LOAD_BOOST_3
#define LOAD_BOOST_1W49   (LOAD_BOOST_1 | LOAD_BOOST_2)
#define LOAD_BOOST_1W95   (LOAD_BOOST_1 | LOAD_BOOST_3)
#define LOAD_BOOST_2W55   (LOAD_BOOST_2 | LOAD_BOOST_3)
#define LOAD_BOOST_3W00   (LOAD_BOOST_1 | LOAD_BOOST_2 | LOAD_BOOST_3)

//boost: define load as current, based on 3.3V output
#define LOAD_BOOST_30mA   LOAD_BOOST_1
#define LOAD_BOOST_70mA   LOAD_BOOST_2
#define LOAD_BOOST_100mA  LOAD_BOOST_3
#define LOAD_BOOST_99mA   (LOAD_BOOST_1 | LOAD_BOOST_2)
#define LOAD_BOOST_130mA  (LOAD_BOOST_1 | LOAD_BOOST_3)
#define LOAD_BOOST_170mA  (LOAD_BOOST_2 | LOAD_BOOST_3)
#define LOAD_BOOST_200mA  (LOAD_BOOST_1 | LOAD_BOOST_2 | LOAD_BOOST_3)


typedef enum
{
    LOADS_THERM_SAFE,    // thermal conditions allow higher loads
    LOADS_THERM_ALERT,   // thermal conditions do not allow higher loads
    LOADS_SBUTTON_BUCK,  // short press buck
    LOADS_LBUTTON_BUCK,  // long press buck
    LOADS_SBUTTON_BOOST, // short press boost
    LOADS_LBUTTON_BOOST, // long press boost
} loads_event_t;


void     LoadsInit(void);
void     LoadsTask(void);
void     LoadsStateMachine(loads_event_t);
uint16_t LoadsGetStatus(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LOADS_H */

