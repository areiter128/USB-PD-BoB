;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; © 2018 Microchip Technology Inc.
;
; MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any 
;derivatives, exclusively with Microchip?s products. This software and any 
;accompanying information is for suggestion only.  It does not modify Microchip?s 
;standard warranty for its products.  You agree that you are solely responsible 
;for testing the software and determining its suitability.  Microchip has no 
;obligation to modify, test, certify, or support the software.

; THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS,
;IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF
;NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS 
;INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE 
;IN ANY APPLICATION.
 
;IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL 
;OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE 
;SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR 
;THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
;TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED 
;THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

;MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
.include "xc.inc"

.section .text._COMPENSATOR_AltWregInitialize, keep, code

.global _COMPENSATOR_AltWregInitialize
;*******************************************************************************
;Function: 	COMPENSATOR_AltWregInitialize
;Description:	Compensator Alternate working register set-up
;******************************************************************************/
_COMPENSATOR_AltWregInitialize:

push   w1	    ; Push W1,W2 onto the stack as when context changes, data no longer available
push   w2
  
ctxtswp w0	    ; Swap to Alternate W-Reg set associated to compensator

mov [w15-4], w4	    ; Fetch address of the compensator structure 
mov [w15-2], w5	    ; Controller type info (1=cascaded, 0=traditional)

btsc w5, #0x0    
mov [w4], w0	    ; Address of control reference is top of structure, non-cascaded will pass W0 directly
inc2 W4, W4    
	
mov [w4++], w1	    ; Load target input source
mov [w4++], w2	    ; Load compensator output target destination
		    		    
btsc w5, #0x0
mov [w4], w3	    ; For cascaded controller, address of array to store accumulated data within structure
inc2 w4, w4
    
mov [w4++], w6	    ; PostScaler
mov [w4++], w7	    ; PostShift
mov [w4++], w8	    ; Address of array for trigger data		    
mov [w4++], w9	    ; Address of ABCoefficients
mov [w4++], w10	    ; Address of control/error history
mov [w4++], w11	    ; Min Clamp
mov [w4++], w12	    ; Max Clamp		    
		    		   
btsc w5, #0x0	    ; For cascaded controller W13 must hold address of ACCAL
mov #ACCAL, w13		    		    
		    
ctxtswp #0x0	    ; Swap back to main register set
 
pop w2
pop w1
		    
return


.section .text._COMPENSATOR_UpdateParameters, keep, code

.global _COMPENSATOR_UpdateParameters
;*******************************************************************************
;Function: 	COMPENSATOR_UpdateParameters
;Description:	Modify Alternate working registers for different coefficients 		    
;******************************************************************************/
_COMPENSATOR_UpdateParameters:

push   w1	    ; Push W1 onto the stack as when context changes, data no longer available

bclr INTCON2, #15    
nop
nop    
    
ctxtswp w0	    ; Swap to Alternate 		    
mov [w15-2], w14    ; Address of structure with new Parameters
mov [w14++], w6	    ; New postscaler 
mov [w14++], w7     ; New postShift
mov w14, w9	    ; New A/B coefficients base address
     
ctxtswp #0x0	    ; Swap back to main register set

bset INTCON2, #15    
    
pop w1
		    
return		    
		    
		    
.end
