
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

#ifndef PROTO_DATA_H
#define	PROTO_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif


/* PROTOCOL API  - shared across both architectures: DSPIC and PIC24*/

// P24 -> DSPIC - 4 bytes
typedef union {
    struct {
        uint8_t buck_still:3;
        uint8_t :1;
        uint8_t buck_blink:3;
        uint8_t :1;
        uint8_t boost_still:3;
        uint8_t :1;
        uint8_t boost_blink:3;
        uint8_t :1;
    }  __attribute__ ((packed));
    uint16_t u16;
} proto_ldst_t;

typedef union {
    struct {
        uint8_t fault_ocp_buck:1;
        uint8_t fault_ovp_buck:1;
        uint8_t fault_ocp_boost:1;
        uint8_t fault_ovp_boost:1;
        uint8_t :4;
    }  __attribute__ ((packed));
    uint8_t u8;
} proto_flts_t;

typedef union {
    struct {
        uint8_t        temperature;
        proto_flts_t   fault_status;
        proto_ldst_t   load_status;
    } __attribute__ ((packed));
    uint8_t byte_array[sizeof(uint8_t) + sizeof(proto_flts_t) + sizeof(proto_ldst_t)]; 
} protocol_data_t;

// DSPIC -> P24 - 1 byte
enum{
    PROTO_NO_EVENT,
    PROTO_SHORT_BUCK,
    PROTO_SHORT_BOOST,
    PROTO_LONG_BUCK,
    PROTO_LONG_BOOST,
    PROTO_SYS_RESET,
    PROTO_TEST_ON,
    PROTO_TEST_OFF,
};
typedef uint8_t protocol_event_t;

//=====================================================
//   | SOF |  DATA[LEN] |
//   |  1  |     LEN    |

#define PROTO_SOF           0x55
#define PROTO_DSP_P24_LEN   sizeof(protocol_event_t)
#define PROTO_P24_DSP_LEN   sizeof(protocol_data_t)


#ifdef	__cplusplus
}
#endif

#endif	/* PROTO_DATA_H */

