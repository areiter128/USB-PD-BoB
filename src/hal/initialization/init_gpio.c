/*!Software License Agreement
 * ***********************************************************************************************
 * © 2017 Microchip Technology Inc. and its subsidiaries.  You may use this software and any 
 * derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED 
 * OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP 
 * PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 * 
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR 
 * CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, 
 * HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
 * FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE 
 * PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 * 
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 
 * ***********************************************************************************************
 * 
 * File:   hal.h
 * Author: M91406
 *
 * Created on July 28, 2017, 11:04 AM
 * ***********************************************************************************************/

#include "hal/hal.h"

volatile uint16_t init_gpio(void) {
    
    // Initialize debugging functions
    DBGLED_INIT_OUTPUT; // DEBUG-LED - visible master core heartbeat
    
    // UART1 for debug messages
    UART_TX_INIT_OUTPUT;
    UART_RX_INIT_INPUT;

    // Set PPS for UART
//    __builtin_write_RPCON(0x0000); // unlock PPS
//    RPINR18bits.U1RXR = 0x003E;    //RC14->UART1:U1RX
//    RPOR15bits.RP63R = 0x0001;    //RC15->UART1:U1TX
//    __builtin_write_RPCON(0x0800); // lock PPS

    pps_UnlockIO();
    pps_RemapInput(UART_RX_RP, PPSIN_U1RX);
    pps_RemapOutput(UART_TX_RP, PPSOUT_U1TX);
    pps_LockIO();

    return(true);    
}
