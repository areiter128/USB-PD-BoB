;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Copyright(c) 2018 Microchip Technology Inc. and its subsidiaries.
; Subject to your compliance with these terms, you may use Microchip
; software and any derivatives exclusively with Microchip products. It
; is your responsibility to comply with third party license terms
; applicable to your use of third-party software (including open source
; software) that may accompany Microchip software.
; THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
; EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
; IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
; FOR A PARTICULAR PURPOSE.
; IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
; PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
; ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
; MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
; FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
; LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
; EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
; MICROCHIP FOR THIS SOFTWARE.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.include "xc.inc"
;#include "buck_dcdt.h"
#include "boost_dcdt.h"
    
.data   ; Tell assembler to add subsequent data to the data section

.text   ; Begin program instructions


;.global _INIT_AltRegContext1Setup
.global _INIT_AltRegContext2Setup

;  _INIT_AltRegContext1Setup:
;
;  CTXTSWP #0x1   ;Swap to Alternate W-Reg context #1
;
;  ; Note: w0 register will be used for compensator control reference parameter
;  ; Initialize Alternate Working Registers context #1
;  mov #_buckControlReference,    w0    ; Reference Voltage address
;  mov #ADCBUF13,                 w1    ; Address of the ADCBUF13 register  (Input)
;  mov #DAC1DATH,                 w2    ; Address of the DAC target register (Output)
;
;  ; w3, w4, w5 used for MAC/MPY instructions
;  mov #BUCK_COMP_2P2Z_POSTSCALER, w6
;  mov #BUCK_COMP_2P2Z_POSTSHIFT,  w7
;  mov #_buckVoltage,              w8 
;  mov #_buckABCoefficients,       w9
;  mov #_buckErrorControlHistory,  w10
;  mov #BUCK_COMP_2P2Z_MIN_CLAMP,  w11
;  mov #BUCK_COMP_2P2Z_MAX_CLAMP,  w12
;
;  CTXTSWP #0x0  ; Swap back to main register set
;
;  return        ; Exit Alt-WREG1 set-up function

  
  _INIT_AltRegContext2Setup:

  CTXTSWP #0x2   ;Swap to Alternate W-Reg context #2

  ; Note: w0 register will be used for compensator control reference parameter
  ; Initialize Alternate Working Registers context #2
  mov #_boostControlReference,   w0    ; Reference Voltage address
  mov #ADCBUF18,                 w1    ; Address of the ADCBUF18 register  (Input)
  mov #DAC2DATH,                 w2    ; Address of the DAC target register (Output)

  ; w3, w4, w5 used for MAC/MPY instructions
  mov #BOOST_COMP_2P2Z_POSTSCALER, w6
  mov #BOOST_COMP_2P2Z_POSTSHIFT,  w7
  mov #_boostVoltage,              w8
  mov #_boostABCoefficients,       w9
  mov #_boostErrorControlHistory,  w10
  mov #BOOST_COMP_2P2Z_MIN_CLAMP,  w11
  mov #BOOST_COMP_2P2Z_MAX_CLAMP,  w12

  CTXTSWP #0x0  ; Swap back to main register set
  return        ; Exit Alt-WREG2 set-up function

.end
