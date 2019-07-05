;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; © 2015 Microchip Technology Inc.
;
; MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any
; derivatives created by any person or entity by or on your behalf, exclusively
; with Microchip?s products.  Microchip and its licensors retain all ownership
; and intellectual property rights in the accompanying software and in all
; derivatives here to.
;
; This software and any accompanying information is for suggestion only.  It
; does not modify Microchip?s standard warranty for its products.  You agree
; that you are solely responsible for testing the software and determining its
; suitability.  Microchip has no obligation to modify, test, certify, or
; support the software.
;
; THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
; EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
; WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
; PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS,
; COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
;
; IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT
; (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY,
; INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
; EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
; ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF
; MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
; TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
; CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
; FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
;
; MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
; TERMS.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Local inclusions.
	.nolist
	.list

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;        .section .libdsp, code		; use this section type when used as hidden library file
        .section .text				; use this section type for debugging

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ; structure defined offsets

 .equ delay,2
 .equ triggerRegister,4
 .equ periodRegister,6

; _SMPS_ControllerCascadeUpdate_HW_Accel:

; Prototype:

; void SMPS_ControllerCascadeUpdate_HW_Accel(void);
;
;  Operation:
;                                                Wcp0   Wcp1   ( s + Wcz1 )   Wcp2   ( s + Wcz2 ) 
;  Calculate the transfer function Hc(s) = Kdc X ---- X ---- X ------------ X ---- X ------------ = Hc1(s) X Hc2(s) X Hc3(s)
;                                                 S     Wcz1   ( s + Wcp1 )   Wcz2   ( s + Wcp2 )
;
;           u(s)         Wcp1   Wcp2   Wcp0
;  Hc1(s) = ---- = Kdc X ---- X ---- X ----
;     	    e(s)         Wcz1   Wcz2    s 
;
;	         y(s)   ( s + Wcz1 )
;  Hc2(s) = ---- = ------------
;	         u(s)   ( s + Wcp1 )
;
;	         z(s)   ( s + Wcz2 )
;  Hc3(s) = ---- = ------------
;	         y(s)   ( s + Wcp2 )
;
;   2P2Z Compensator Function:
;   u[n] = B10*e[n] + B11*e[n-1] + A11*u[n-1] 
;   y[n] = B20*u[n] + B21*u[n-1] + A21*y[n-1]
;   z[n] = B30*y[n] + B31*y[n-1] + A31*z[n-1]
;
;
;  where:
;
;   xABCoefficients[0]  = B10
;   xABCoefficients[1]  = B11
;   xABCoefficients[2]  = A11
;   xABCoefficients[3]  = B20
;   xABCoefficients[4]  = B21
;   xABCoefficients[5]  = A21
;   xABCoefficients[6]  = B30
;   xABCoefficients[7]	= B31
;   xABCoefficients[8]	= A31
 
;   xErrorControlHistory[0] = e[n-1]
;   xErrorControlHistory[1] = u[n-1]
;	xErrorControlHistory[2] = y[n-1]
;   xErrorControlHistory[3] = z[n-1]

;   where 'x' is for the converter name

;   Function call inputs:
;   none
;   Note 1: 
;   w0 is used to read in the converter voltage reference value just prior to the library function
;   call.  After the input error has been calculated, it may be used freely within the library.  This 
;   is done so that at least one working register is available inside the ISR at all times.  If registers 
;   w13 and w14 are not preloaded with any data, then two more registers would be available by the user
;   at all times.

;   Note 2:
;   (A-Coefficients)/(B-Coefficients) are preloaded into their respective array. The postShift,
;   postScalar, min/max clamping values, source register address, and target register address
;   are all preloaded into their respective Alt-W registers at system initialization. See resource 
;   usage definition below.
;
;   Alternate Working Register System resource usage:
;
;       w0  = Control Reference value
;       w1  = Address of the Source Register (Input)  - ADCBUFx
;       w2  = Address of the Target Register (Output) - PDCx/CMPxDAC
;       w3  = Address of Result array structure [ACCAL1 ACCAH1 ACCAU1 ACCAL2 ACCAH2 ACCAU2 ACCAU3 ACCAH3 ACCAL3]
;       w4  = Misc operands
;       w5  = Misc operands
;       w6  = postScalar
;       w7  = postShift
;       w8  = Library options structure pointer
;       w9  = ACoefficients/BCoefficients array base address { B10, B11, A11, B20, B21, A21, B30, B31, A31 }
;       w10 = ErrorHistory/ControlHistory array base address { e[n-1], u[n-1], y[n-1], z[n-1] }
;       w11 = minclamp
;       w12 = maxClamp
;       w13 = Address of ACCAL register
;       w14 = Misc operands
;
;   Note 3:
;   The library comes with the option of configuring the TRIGx value in real time.
;   The options that are included are duty cycle on time trigger (On-Time Trigger) and
;   duty cycle off time trigger (Off-Time Trigger).  The following two equations show
;   how these values are computed:
;
;   On-Time Trigger:  TRIGx = PDCx  + Delay
;                             ----
;                              2
;
;;  Off-Time Trigger: TRIGx = PDCx  +  (PTPER - PDCx) + Delay
;                                       ------------
;                                            2
;
;   In order to make use of this library option, the library options structure must be initialized.
;   Please refer to the smps_control.h file for further details.
;
;   Note 4:
;   This function requires CORCON register to be setup in a certain state in order to operate correctly. 
;   Due to this requirement, this function will save the CORCON register on the stack in the beginning of 
;   the function and restore it before the function returns.  After saving the CORCON register, this 
;   function writes to all bits of the CORCON register. Thus, for the brief duration when this function is
;   executing, the state of CORCON register may be different from its state as set by the function caller. 
;   This may change the CPU core behaviour with respect to exception processing latency, DO loop termination, 
;   CPU interrupt priority level and DSP-engine behaviour.
;............................................................................


.global _SMPS_ControllerCascadeUpdate_HW_Accel        ; Provide global scope to routine

  _SMPS_ControllerCascadeUpdate_HW_Accel:

    push    CORCON     ; Save CORCON, modified for fractional computation 1.31 saturation
					   
    push ACCAL
    push ACCAH
    push ACCAU
   
    mov  #0xE0, w4    			; Load literal value 0x00E0 CORCON register: 0b 0000 0000 1110 0000
    mov  w4, _CORCON

    mov [w0], w4
    sub w4, [w1], [w10]			; [w10] = Control Reference - measured output  ([w10] = w0 - [w1])
   ; mov [w1],[w10]
    
    clr  a, [w9]+=6, w4, [w10], w5	; ACCA = EMPTY, Single instruction to load w4/w5 and then move pointers
								; w4 = B10, w9 = B20, w5 = [w10] = recent error
   
    ; Load ACCA for 1st stage from previous cycles calculation
    mov [w3++],[w13++]  		; Load ACCA bits 15:0, 1st stage 
    mov [w3++],[w13++]     		; Load ACCA bits 31:16, 1st stage 
    mov [w3++], [w13--]    		; Load ACCA bits 39:32, 1st stage 
	    
	; Cascade Stage-1 critical path
    mac w4*w5, a, [w9]+=6, w4		; ACCA = B10 * e[n] + Previously ACCA stored results, 
								; w4 = B20, w9 = B30
    sac.r a, w5       			; w5 = Rnd(ACCAH) 

    ; Save control output to control history 
    mov w5, [w10+2]    			; w5 = u[n] (becomes u[n-1] for next calculation)
      
    ; Load ACCA for 2nd stage from previous cycles calculation
    mov [w3++],[--w13]  		; Load ACCA bits 15:0, 2nd stage 
    mov [w3++],[++w13]     		; Load ACCA bits 31:16, 2nd stage 
    mov [w3++], [++w13]    		; Load ACCA bits 39:32, 2nd stage
	
    ; Cascade Stage-2 critical path  
    mac w4*w5, a , [w9]-=6, w4		; ACCA = B20*u[n] + previously stored ACCB results
								; w4 = B30, w9 = B20, w10 = y[n-1]
    
    sac.r a, w5   			; w5 = Rnd(ACCBH)
	
    ; Save control output to control history 
    mov w5, [w10+4]			; w5 = y[n] (becomes y[n-1] for next calculation)
   
    ; Load ACCA for 3rd stage from previous cycles calculation
    mov [w3++], [w13--]	 		; Load ACCA bits 39:32, 3rd stage
    mov [w3++], [w13--]	 		; Load ACCA bits 31:16, 3rd stage
    mov [w3], [w13]		 	; Load ACCA bits 15:0, 3rd stage
    
    ; Cascade Stage-3 critical path
    mac w4*w5, a, [w9]-=4, w4		; ACCA = B30 * y[n] + Previously ACCA stored results, 
					; w9 = B11, 
  	
    sac.r a, #0, w4    			; w5 = Rnd(ACCAH) - this is the control output
    
    ; Normalization applied after 3rd stage
    
    mov w4, [w10+6]  			; w4 = z[n] (becomes z[n-1] for next calculation)

    mpy   w4*w6, a  			; Multiply control output with postscaler
    
    sftac a, w7       			; w7 = Normalization shift value to compensate coefficient scaling
					; ACC = ACC>>PostShift or ACC = ACC<<PostShift depending on sign of value
	
    sac.r a, w4 	 		; w4 = Rnd(ACCAH) again after normalization
    
    ;mov w4, [w10+6]  			; w4 = z[n] (becomes z[n-1] for next calculation)
    
    ; Clamp to minimum if needed
    cpsgt w4, w11     			; Check if u[n] > minClamp.  If true, the next instruction is discarded and a Nop() is executed
								; If not true, execute next instruction
    mov.w w11, w4     			; Update u[n] with minClamp value

    ; Clamp to maximum if needed
    cpslt w4, w12    			; Check if u[n] < maxClamp. If true, the next instruction is discarded and a Nop() is executed
								; If not true, execute next instruction
    mov.w w12, w4    			; Update u[n] with maxClamp value

    mov w4, [w2]    			; Update the target register (Output):  [w2] = PDCx/CMPxDAC
    
    ; ------------------------------- End of Critical Path ------------------------------------------ ;
	
    ; Trigger options check:
    btsc [w8], #0               ; Check if trigger On-Time is ENABLED
    bra triggerOnTime           ; if so, go to TriggerOnTime function, else skip

    btsc [w8], #1               ; Check if trigger Off-Time is ENABLED
    bra triggerOffTime	        ; if so, go to TriggerOffTime function
	
    bra controlHistoryUpdate    ; else go directly to next iteration calculations
	
 triggerOffTime:

      mov [w8 + #periodRegister], w14    ;  Load address of time base to working register
      mov [w14], w14                     ;  Move the contents of the address (PTPER)
      sub w14, w4, w14                   ;  Subtract duty cycle from time base and store result
      asr w14, #1, w14                   ;  Right shift result previous results by literal value
      add w14, w4, w14                   ;  Duty cycle + 50% off time
      mov [w8 + #delay], w5              ;  Move delay value
      add w14, w5, w14                   ;  Add delay to account for gate drive delay
      mov [w8 + #triggerRegister], w5    ;  Load address of target register
      mov w14, [w5]                      ;  Update the Trigger target register

      bra controlHistoryUpdate
	  
 triggerOnTime:

      asr w4, #1, w14                    ; Right-shift PDCx by literal and store value in w14
      mov [w8 + #delay], w5              ; Load delay value to register w5
      add w14, w5, w14                   ; Add delay to account for gate drive delay
      mov [w8 + #triggerRegister], w5    ; Load address of target register
      mov w14, [w5]                      ; Update the Trigger target register	  
	  
   ; End of trigger options
   
 controlHistoryUpdate:

    ; Cascade Stage-1 control history update
    clr  a, [w9]+=2, w4, [w10]+=2, w5			; ACCA = EMPTY
							; w4 = B11, w5 = e[n-1], w9 = A11, w10 = u[n-1]
 	
    mac  w4*w5, a, [w9]+=4, w4, [w10]+=2, w5     	; ACCA = B11 * e[n-1]
							; w4 = A11, w5 = u[n-1], w9 = B21, w10 = y[n-1]

    mac  w4*w5, a, [w9]+=2, w4      			; ACCA = B11 * e[n-1] + A11 * u[n-1] 
							; w4 = B21, w5 = u[n-1] , w9 = A21, w10 = y[n-1]
    
    sub w3, #16, w3					; W3 points back to stage1 ACCAL1
 
 	; Load accumalator results of 1st stage to array	
    mov [w13++], [w3++]           					; Load ACCA bits: 15:0
    mov [w13++], [w3++]           					; Load ACCA bits: 31:16
    mov [w13--], [w3++]          					; Load ACCA bits: 39:32
    
    ; Cascade Stage-2 control history update
    mpy  w4*w5, a, [w9]+=4, w4, [w10]+=2, w5     	; ACCA = B21 * u[n-1]
							; w4 = A21, w5 = y[n-1], w9 = B31, w10 = z[n-1]

    mac  w4*w5, a, [w9]+=2, w4      			; ACCA = B21 * u[n-1] + A21 * y[n-1]
							; w4 = B31, w5 = y[n-1], w9 = A31, w10 = z[n-1]	

    ; Load accumalator results of 2nd stage to array												
    mov [--w13], [w3++]          				; Load ACCA bits: 15:0
    mov [++w13], [w3++]           		    		; Load ACCA bits: 31:16
    mov [++w13], [w3++]           		    		; Load ACCA bits: 39:32

    ; Cascade Stage-3 control history update										 	
    mpy  w4*w5, a, [w9]-=6, w4, [w10]-=6, w5     	; ACCA = B31 * y[n-1]
							; w4 = A31, w5 = z[n-1], w9 = A21, w10 = e[n-1]

    mac  w4*w5, a, [w9]-=6, w4               	 	; ACCA = B31 * y[n-1] + A31 * z[n-1]
							; w4 = A21, w5 = z[n-1], w9 = A11, w10 = e[n-1]	

    ; Decrement w9 back to base element
    sub w9, #4, w9

    ; Load accumalator results of 3rd stage to array
    mov [w13--],[w3++]	 		 		; Load ACCA bits 39:32
    mov [w13--],[w3++]	 		 		; Load ACCA bits 31:16
    mov [w13],[w3]	 			 	; Load ACCA bits 15:0

    sub w3, #16, w3					; W3 points back to stage1 ACCAL1
	
    pop ACCAU
    pop ACCAH
    pop ACCAL
    
    pop CORCON	            				; Restore CORCON
   
    return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

      .end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; EOF
      


