;LICENSE / DISCLAIMER
; **********************************************************************************
;  SDK Version: z-Domain Control Loop Designer v0.9.0.70
;  AGS Version: Assembly Generator Script v1.2.1 (10/18/19)
;  Author:      C14220
;  Date/Time:   10/24/2019 1:12:44 PM
; **********************************************************************************
;  3P3Z Control Library File (Single Bitshift-Scaling Mode)
; **********************************************************************************
	
;------------------------------------------------------------------------------
;file start
	.nolist
	.list
	
;------------------------------------------------------------------------------
;local inclusions.
	.section .data    ; place constant data in the data section
	
;------------------------------------------------------------------------------
; Define status flags bit positions
	.equ NPMZ16_STATUS_ENABLE,       15    ; bit position of the ENABLE control bit
	.equ NPMZ16_STATUS_INVERT_INPUT, 14    ; bit position of the INVERT_INPUT control bit
	.equ NPMZ16_STATUS_USAT,         1    ; bit position of the UPPER_SATURATION_FLAG status bit
	.equ NPMZ16_STATUS_LSAT,         0    ; bit position of the LOWER_SATURATION_FLAG status bit
	
;------------------------------------------------------------------------------
; Address offset declarations for data structure addressing
	.equ offStatus,                 0    ; status word at address-offset=0
	.equ offSourceRegister,         2    ; pointer to source memory address=2
	.equ offTargetRegister,         4    ; pointer to tasrget memory address=2
	.equ offControlReference,       6    ; pointer to control reference memory address=2
	.equ offACoefficients,          8    ; pointer to A-coefficients array start address=2
	.equ offBCoefficients,          10    ; pointer to B-coefficients array start address=2
	.equ offControlHistory,         12    ; pointer to control history array start address=2
	.equ offErrorHistory,           14    ; pointer to error history array start address=2
	.equ offACoeffArraySize,        16    ; size of the A-coefficients array
	.equ offBCoeffArraySize,        18    ; size of the B-coefficients array
	.equ offCtrlHistArraySize,      20    ; size of the control history array
	.equ offErrHistArraySize,       22    ; size of the error history array
	.equ offPreShift,               24    ; value of input value normalization bit-shift scaler
	.equ offPostShiftA,             26    ; value of A-term normalization bit-shift scaler
	.equ reserved_1,                28    ; (reserved)
	.equ reserved_2,                30    ; (reserved)
	.equ offInputOffset,            32    ; input source offset value
	.equ offMinOutput,              34    ; minimum clamping value of control output
	.equ offMaxOutput,              36    ; maximum clamping value of control output
	.equ offADCTriggerRegister,     38    ; pointer to ADC trigger register memory address
	.equ offADCTriggerOffset,       40    ; value of ADC trigger offset
	
;------------------------------------------------------------------------------
;local inclusions.
	.section .text    ; place code in the code section
	
;------------------------------------------------------------------------------
; Global function declaration
; This function calls the z-domain controller processing the latest data point input
;------------------------------------------------------------------------------
	
	.global _cha_vloop_Update
_cha_vloop_Update:    ; provide global scope to routine
	
;------------------------------------------------------------------------------
; Save working registers
	push.s    ; save shadowed working registers (w0...w3)
	push w4    ; save working registers used for MAC operations (w4, w6, w8, w10)
	push w6
	push w8
	push w10
	push w12    ; save working register used for status flag tracking
	
;------------------------------------------------------------------------------
; Check status word for Enable/Disable flag and bypass computation, if disabled
	mov [w0 + #offStatus], w12
	btss w12, #NPMZ16_STATUS_ENABLE
	bra CHA_VLOOP_BYPASS_LOOP
	
;------------------------------------------------------------------------------
; Save working registers
	push CORCON    ; save CPU configuration register
	
;------------------------------------------------------------------------------
; Configure DSP for fractional operation with normal saturation (Q1.31 format)
	mov #0x00E4, w4
	mov w4, _CORCON
	
;------------------------------------------------------------------------------
; Setup pointers to A-Term data arrays
	mov [w0 + #offACoefficients], w8    ; load pointer to first index of A coefficients array
	
;------------------------------------------------------------------------------
; Load pointer to first element of control history array
	mov [w0 + #offControlHistory], w10    ; load pointer address into wreg
	
;------------------------------------------------------------------------------
; Compute compensation filter term
	clr a, [w8]+=2, w4, [w10]+=2, w6    ; clear accumulator A and prefetch first operands
	mac w4*w6, a, [w8]+=2, w4, [w10]+=2, w6    ; multiply control output (n-1) from the delay line with coefficient A1
	mac w4*w6, a, [w8]+=2, w4, [w10]+=2, w6    ; multiply control output (n-2) from the delay line with coefficient A2
	mac w4*w6, a    ; multiply & accumulate last control output with coefficient of the delay line (no more prefetch)
	
;------------------------------------------------------------------------------
; Setup pointer to first element of error history array
	mov [w0 + #offErrorHistory], w10    ; load pointer address into wreg
	
;------------------------------------------------------------------------------
; Update error history (move error one tick along the delay line)
	mov [w10 + #4], w6    ; move entry (n-3) into buffer
	mov w6, [w10 + #6]    ; move buffered value one tick down the delay line
	mov [w10 + #2], w6    ; move entry (n-2) into buffer
	mov w6, [w10 + #4]    ; move buffered value one tick down the delay line
	mov [w10 + #0], w6    ; move entry (n-1) into buffer
	mov w6, [w10 + #2]    ; move buffered value one tick down the delay line
	
;------------------------------------------------------------------------------
; Read data from input source and calculate error input to transfer function
	mov [w0 + #offSourceRegister], w2    ; load pointer to input source register
	mov [w2], w1    ; move value from input source into working register
	mov [w0 + #offControlReference], w2    ; move pointer to control reference into working register
	subr w1, [w2], w1    ; calculate error (= reference - input)
	mov [w0 + #offPreShift], w2    ; move error input scaler into working register
	sl w1, w2, w1    ; normalize error result to fractional number format
	
;------------------------------------------------------------------------------
; Setup pointers to B-Term data arrays
	mov [w0 + #offBCoefficients], w8    ; load pointer to first index of B coefficients array
	mov w1, [w10]    ; add most recent error input to history array
	
;------------------------------------------------------------------------------
; Compute compensation filter term
	movsac a, [w8]+=2, w4, [w10]+=2, w6    ; leave contents accumulator A untouched and prefetch first operands
	mac w4*w6, a, [w8]+=2, w4, [w10]+=2, w6    ; multiply & accumulate error input (n-0) from the delay line with coefficient B0 and prefetch next operands
	mac w4*w6, a, [w8]+=2, w4, [w10]+=2, w6    ; multiply & accumulate error input (n-1) from the delay line with coefficient B1 and prefetch next operands
	mac w4*w6, a, [w8]+=2, w4, [w10]+=2, w6    ; multiply & accumulate error input (n-2) from the delay line with coefficient B2 and prefetch next operands
	mac w4*w6, a    ; multiply & accumulate last control output with coefficient of the delay line (no more prefetch)
	
;------------------------------------------------------------------------------
; Backward normalization of recent result
	mov [w0 + #offPostShiftA], w6
	sftac a, w6
	sac.r a, w4    ; store most recent accumulator result in working register
	
;------------------------------------------------------------------------------
; Controller Anti-Windup (control output value clamping)
	
; Check for upper limit violation
	mov [w0 + #offMaxOutput], w6    ; load upper limit value
	cpslt w4, w6    ; compare values and skip next instruction if control output is within operating range (control output < upper limit)
	bra CHA_VLOOP_CLAMP_MAX_OVERRIDE    ; jump to override label if control output > upper limit
	bclr w12, #NPMZ16_STATUS_USAT    ; clear upper limit saturation flag bit
	bra CHA_VLOOP_CLAMP_MAX_EXIT    ; jump to exit
	CHA_VLOOP_CLAMP_MAX_OVERRIDE:
	mov w6, w4    ; override controller output
	bset w12, #NPMZ16_STATUS_USAT    ; set upper limit saturation flag bit
	CHA_VLOOP_CLAMP_MAX_EXIT:
	
; Check for lower limit violation
	mov [w0 + #offMinOutput], w6    ; load lower limit value
	cpsgt w4, w6    ; compare values and skip next instruction if control output is within operating range (control output > lower limit)
	bra CHA_VLOOP_CLAMP_MIN_OVERRIDE    ; jump to override label if control output < lower limit
	bclr w12, #NPMZ16_STATUS_LSAT    ; clear lower limit saturation flag bit
	bra CHA_VLOOP_CLAMP_MIN_EXIT    ; jump to exit
	CHA_VLOOP_CLAMP_MIN_OVERRIDE:
	mov w6, w4    ; override controller output
	bset w12, #NPMZ16_STATUS_LSAT    ; set lower limit saturation flag bit
	CHA_VLOOP_CLAMP_MIN_EXIT:
	
;------------------------------------------------------------------------------
; Write control output value to target
	mov [w0 + #offTargetRegister], w8    ; move pointer to target in to working register
	mov w4, [w8]    ; move control output into target address
	
;------------------------------------------------------------------------------
; Load pointer to first element of control history array
	mov [w0 + #offControlHistory], w10    ; load pointer address into wreg
	
;------------------------------------------------------------------------------
; Update control output history
	mov [w10 + #2], w6    ; move entry (n-2) one tick down the delay line
	mov w6, [w10 + #4]
	mov [w10 + #0], w6    ; move entry (n-1) one tick down the delay line
	mov w6, [w10 + #2]
	mov w4, [w10]    ; add most recent control output to history
	
;------------------------------------------------------------------------------
; Update status flag bitfield
	mov w12, [w0 + #offStatus]
	
;------------------------------------------------------------------------------
; Restore working registers
	pop CORCON    ; restore CPU configuration registers
	
;------------------------------------------------------------------------------
; Enable/Disable bypass branch target
	CHA_VLOOP_BYPASS_LOOP:
	
;------------------------------------------------------------------------------
; Restore working registers
	pop.s    ; restore shadowed working registers (w0...w3)
	pop w4    ; restore working registers used for MAC operations w4, w6, w8, w10)
	pop w6
	pop w8
	pop w10
	pop w12    ; restore working register used for status flag tracking
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; Global function declaration _cha_vloop_Reset
; This function clears control and error histories enforcing a reset
;------------------------------------------------------------------------------
	
	.global _cha_vloop_Reset
_cha_vloop_Reset:
	
;------------------------------------------------------------------------------
; Clear control history array
	push w0    ; Set pointer to the base address of control history array
	mov  [w0 + #offControlHistory], w0
	clr [w0++]    ; Clear next address of control history array
	clr [w0++]    ; Clear next address of control history array
	clr [w0]    ; Clear last address of control history array
	pop w0
	
;------------------------------------------------------------------------------
; Clear error history array
	push w0    ; Set pointer to the base address of error history array
	mov [w0 + #offErrorHistory], w0
	clr [w0++]    ; Clear next address of error history array
	clr [w0++]    ; Clear next address of error history array
	clr [w0++]    ; Clear next address of error history array
	clr [w0]    ; Clear last address of error history array
	pop w0
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; Global function declaration _cha_vloop_Precharge
; This function loads user-defined default values into control and error histories
;------------------------------------------------------------------------------
	
	.global _cha_vloop_Precharge
_cha_vloop_Precharge:
	
;------------------------------------------------------------------------------
; Charge error history array with defined value
	push w0    ; Set pointer to the base address of error history array
	push w1
	mov  [w0 + #offErrorHistory], w0
	mov w1, [w0++]    ; Load user value into next address of error history array
	mov w1, [w0++]    ; Load user value into next address of error history array
	mov w1, [w0++]    ; Load user value into next address of error history array
	mov w1, [w0]    ; Load user value into last address of error history array
	pop w1
	pop w0
	
;------------------------------------------------------------------------------
; Charge control history array with defined value
	push w0    ; Set pointer to the base address of control history array
	push w2
	mov  [w0 + #offControlHistory], w0
	mov w2, [w0++]    ; Load user value into next address of control history array
	mov w2, [w0++]    ; Load user value into next address of control history array
	mov w2, [w0]    ; Load user value into last address of control history array
	pop w2
	pop w0
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; End of file
	.end
;------------------------------------------------------------------------------
	