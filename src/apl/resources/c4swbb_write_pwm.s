;LICENSE / DISCLAIMER
; **********************************************************************************
;  Version:     v1.0 (10/22/19)
;  Author:      M91406
;  Date/Time:   10/23/2019 1:15:54 PM
; **********************************************************************************
;  4-SWITCH BUCK/BOOST CONVERTER PWM DISTRIBUTION MODULE
; **********************************************************************************
;  This assembly module distributes a single, linear control loop output	
;  onto two PWM duty cycle register of buck and boost leg of  4-switch 
;  buck/boost converter.
;------------------------------------------------------------------------------
;file start
	.nolist
	.list
	
;------------------------------------------------------------------------------
;local inclusions.
	.section .data    ; place constant data in the data section
	
;------------------------------------------------------------------------------
; Define status flags bit positions
	.equ PWMDIST_STATUS_ENABLE,     15    ; bit position of the ENABLE control bit
	.equ PWMDIST_TRIGA_ENABLE,      14    ; bit position of the ENABLE_TRIGA_PLACEMENT control bit
	.equ PWMDIST_TRIGB_ENABLE,      13    ; bit position of the ENABLE_TRIGB_PLACEMENT control bit
	
;------------------------------------------------------------------------------
; Address offset declarations for data structure addressing
    .equ offStatus,                 0    ; status word
    .equ offPtrSource,              2    ; pointer to source memory address
	.equ offPtrTargetA,             4    ; pointer to target A memory address
	.equ offPtrTargetB,             6    ; pointer to target B memory address
	.equ offMinLimitA,              8    ; minimum value of target A
	.equ offMaxLimitA,              10   ; maximum value of target A
	.equ offMinLimitB,              12   ; minimum value of target B
	.equ offMaxLimitB,              14   ; maximum value of target B
	.equ offPtrADCTrigRegA,         16    ; pointer to ADC trigger A register memory address
	.equ offADCTrigOffsetA,         18    ; value of ADC trigger A offset
	.equ offPtrADCTrigRegB,         20    ; pointer to ADC trigger B register memory address
	.equ offADCTrigOffsetB,         22    ; value of ADC trigger B offset
    
;------------------------------------------------------------------------------
;local inclusions.
	.section .text    ; place code in the code section
	
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
; Global Function Declaration
; This function calls the 4-switch buck/boost PWM distribution module
;------------------------------------------------------------------------------
;------------------------------------------------------------------------------

	.global _c4swbb_pwm_update
_c4swbb_pwm_update:    ; provide global scope to routine
	
;------------------------------------------------------------------------------
; Save working registers
;	push.s    ; save shadowed working registers (w0...w3)
;	push w4   ; save working registers used for operations (w4, w7, w8, w9)
;	push w7
;	push w8
;	push w9
;	push w12  ; save working register used for status flag tracking
    
;------------------------------------------------------------------------------
; Check status word for Enable/Disable flag and bypass computation, if disabled
	mov [w0 + #offStatus], w12
	btss w12, #PWMDIST_STATUS_ENABLE
	bra C4SWBB_PWM_UPDATE_BYPASS
	
;------------------------------------------------------------------------------
; Write control output value to target A
    mov [w0 + offPtrSource], w1     ; load pointer to input data into wreg
    mov [w1], w7                    ; load data of source into wreg
    mov w7, w8                      ; move source to target A register

    mov [w0 + offMinLimitA], w1     ; move minimum data limit of target A into wreg
    mov [w0 + offMaxLimitA], w2     ; move maximum data limit of target A into wreg
    mov [w0 + offMinLimitB], w3     ; move minimum data limit of target B into wreg
    mov [w0 + offMaxLimitB], w4     ; move maximum data limit of target B into wreg
    
    ; Clamp buck leg duty cycle to specified limits
	cpslt w8, w2                    ; compare values and skip next instruction if source is within buck leg duty cycle range (source < upper buck limit)
    mov w2, w8                      ; overwrite target A value with buck leg maximum
    cpsgt w8, w1                    ; compare values and skip next instruction if source is within buck leg duty cycle range (source > lower buck limit)
    mov w1, w8                      ; overwrite target A value with buck leg minimum

    ; Push overhead to boost leg duty cycle 
    sub w7, w8, w9                  ; subtract target A from source, store result in target B
    add w3, w9, w9                  ; add boost leg minimum to target B
    
    ; Clamp boost leg duty cycle to specified limits
    cpslt w9, w4                    ; compare values and skip next instruction if source is within boost leg duty cycle range (source - target A < upper boost limit)
    mov w4, w9                      ; overwrite target B value with buck leg maximum
    cpsgt w9, w3                    ; compare values and skip next instruction if source is within boost leg duty cycle range (source - target A > lower boost limit)
    mov w3, w9                      ; overwrite target B value with buck leg minimum
    
    ; write distributed values into target registers A and B
    mov [w0 + offPtrTargetA], w1    ; load pointer to target A into wreg
    mov [w0 + offPtrTargetB], w2    ; load pointer to target B into wreg
    mov w8, [w1]                    ; write value to target A (buck PWM module)
    mov w9, [w2]                    ; write value to target B (boost PWM module)
	
    
;------------------------------------------------------------------------------
; Update ADC trigger A position
	btss w12, #PWMDIST_TRIGA_ENABLE
	bra C4SWBB_PWM_UPDATE_BYPASS
    
	asr w8, #1, w7
	mov [w0 + #offADCTrigOffsetA], w8
	add w7, w8, w7
	mov [w0 + #offPtrADCTrigRegA], w8
	mov w7, [w8]
    
    C4SWBB_TRIGA_UPDATE_BYPASS:
;------------------------------------------------------------------------------
; Update ADC trigger B position
    
    btss w12, #PWMDIST_TRIGB_ENABLE
    bra C4SWBB_TRIGB_UPDATE_BYPASS
    
	asr w9, #1, w7
	mov [w0 + #offADCTrigOffsetB], w9
	add w7, w9, w7
	mov [w0 + #offPtrADCTrigRegB], w9
	mov w7, [w9]

    C4SWBB_TRIGB_UPDATE_BYPASS:
;------------------------------------------------------------------------------
; Enable/Disable bypass branch target
	C4SWBB_PWM_UPDATE_BYPASS:
	
;------------------------------------------------------------------------------
; Restore working registers
;	pop.s    ; restore shadowed working registers (w1...w3)
;	pop w4   ; restore working registers used for MAC operations w4, w7, w8, w9)
;	pop w7
;	pop w8
;	pop w9
;	pop w12  ; restore working register used for status flag tracking
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; End of file
	.end
;------------------------------------------------------------------------------
    


