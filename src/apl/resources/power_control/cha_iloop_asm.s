;LICENSE / DISCLAIMER
; **********************************************************************************
;  SDK Version: z-Domain Control Loop Designer v0.9.1.81
;  AGS Version: Assembly Generator Script v1.3.2 (01/17/2020)
;  Author:      M91406
;  Date/Time:   02/21/2020 1:13:23 AM
; **********************************************************************************
;  2P2Z Control Library File (Dual Bitshift-Scaling Mode)
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
	.equ NPMZ16_STATUS_SWAP_SOURCE,  13    ; bit position of the SWAP_SOURCE control bit
	.equ NPMZ16_STATUS_SWAP_TARGET,  12    ; bit position of the SWAP_TARGET control bit
	.equ NPMZ16_STATUS_USAT,         1    ; bit position of the UPPER_SATURATION_FLAG status bit
	.equ NPMZ16_STATUS_LSAT,         0    ; bit position of the LOWER_SATURATION_FLAG status bit
	
;------------------------------------------------------------------------------
; Address offset declarations for data structure addressing
	.equ offStatus,                 0    ; status word at address-offset = 0
	.equ offSourceRegister,         2    ; pointer to source memory address
	.equ offAltSourceRegister,      4    ; pointer to alternate source memory address
	.equ offTargetRegister,         6    ; pointer to target memory address
	.equ offAltTargetRegister,      8    ; pointer to alternate target memory address
	.equ offControlReference,       10    ; pointer to control reference memory address
	.equ offACoefficients,          12    ; pointer to A-coefficients array start address
	.equ offBCoefficients,          14    ; pointer to B-coefficients array start address
	.equ offControlHistory,         16    ; pointer to control history array start address
	.equ offErrorHistory,           18    ; pointer to error history array start address
	.equ offACoeffArraySize,        20    ; size of the A-coefficients array
	.equ offBCoeffArraySize,        22    ; size of the B-coefficients array
	.equ offCtrlHistArraySize,      24    ; size of the control history array
	.equ offErrHistArraySize,       26    ; size of the error history array
	.equ offPreShift,               28    ; value of input value normalization bit-shift scaler
	.equ offPostShiftA,             30    ; value of A-term normalization bit-shift scaler
	.equ offPostShiftB,             32    ; value of B-term normalization bit-shift scaler
	.equ reserved_1,                34    ; (reserved)
	.equ offInputOffset,            36    ; input source offset value
	.equ offMinOutput,              38    ; minimum clamping value of control output
	.equ offMaxOutput,              40    ; maximum clamping value of control output
	.equ offADCTriggerARegister,    42    ; pointer to ADC trigger #1 register memory address
	.equ offADCTriggerAOffset,      44    ; value of ADC trigger #1 offset
	.equ offADCTriggerBRegister,    46    ; pointer to ADC trigger #2 register memory address
	.equ offADCTriggerBOffset,      48    ; value of ADC trigger #2 offset
	.equ offPtrControlInput,        50    ; pointer to external data buffer of most recent control input
	.equ offPtrControlError,        52    ; pointer to external data buffer of most recent control error
	.equ offPtrControlOutput,       54    ; pointer to external data buffer of most recent control output
	.equ offPtrCascadedFunction,    56    ; pointer to external, cascaded function which will be called from controller
	.equ offPtrCascadedFunParam,    58    ; 16-bit wide function parameter or pointer to a parameter data structure of cascaded function
	
;------------------------------------------------------------------------------
;local inclusions.
	.section .text    ; place code in the code section
	
;------------------------------------------------------------------------------
; Global function declaration
; This function calls the z-domain controller processing the latest data point input
;------------------------------------------------------------------------------
	
	.global _cha_iloop_Update
_cha_iloop_Update:    ; provide global scope to routine
	push w12    ; save working register used for status flag tracking
	
;------------------------------------------------------------------------------
; Check status word for Enable/Disable flag and bypass computation, if disabled
	mov [w0 + #offStatus], w12
	btss w12, #NPMZ16_STATUS_ENABLE
	bra CHA_ILOOP_BYPASS_LOOP
	
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
	mac w4*w6, a    ; multiply & accumulate last control output with coefficient of the delay line (no more prefetch)
	
;------------------------------------------------------------------------------
; Backward normalization of recent result
	mov [w0 + #offPostShiftA], w6
	sftac a, w6
	
;------------------------------------------------------------------------------
; Read data from input source and calculate error input to transfer function
	mov [w0 + #offSourceRegister], w2    ; load pointer to input source register
	mov [w2], w1    ; move value from input source into working register
	mov [w0 + #offPtrControlInput], w2    ; load pointer address of target buffer of most recent controller input from data structure
	mov w1, [w2]    ; copy most recent controller input value to given data buffer target
	mov [w0 + #offControlReference], w2    ; move pointer to control reference into working register
	subr w1, [w2], w1    ; calculate error (=reference - input)
	mov [w0 + #offPreShift], w2    ; move error input scaler into working register
	sl w1, w2, w1    ; normalize error result to fractional number format
	
;------------------------------------------------------------------------------
; Setup pointers to B-Term data arrays
	mov [w0 + #offBCoefficients], w8    ; load pointer to first index of B coefficients array
	
;------------------------------------------------------------------------------
; Setup pointer to first element of error history array
	mov [w0 + #offErrorHistory], w10    ; load pointer address into wreg
	
;------------------------------------------------------------------------------
; Update error history (move error one tick along the delay line)
	mov [w10 + #2], w6    ; move entry (n-2) into buffer
	mov w6, [w10 + #4]    ; move buffered value one tick down the delay line
	mov [w10 + #0], w6    ; move entry (n-1) into buffer
	mov w6, [w10 + #2]    ; move buffered value one tick down the delay line
	mov w1, [w10]    ; add most recent error input to history array
	
;------------------------------------------------------------------------------
; Compute B-Term of the compensation filter
	clr b, [w8]+=2, w4, [w10]+=2, w6    ; clear accumulator B and prefetch first operands
	mac w4*w6, b, [w8]+=2, w4, [w10]+=2, w6    ; multiply & accumulate error input (n-0) from the delay line with coefficient B0 and prefetch next operands
	mac w4*w6, b, [w8]+=2, w4, [w10]+=2, w6    ; multiply & accumulate error input (n-1) from the delay line with coefficient B1 and prefetch next operands
	mac w4*w6, b    ; multiply & accumulate last error input with coefficient of the delay line (no more prefetch)
	
;------------------------------------------------------------------------------
; Backward normalization of recent result
	mov [w0 + #offPostShiftB], w6
	sftac b, w6
	add a    ; add accumulator b to accumulator a
	sac.r a, w4    ; store most recent accumulator result in working register
	
;------------------------------------------------------------------------------
; Controller Anti-Windup (control output value clamping)
	
; Check for upper limit violation
	mov [w0 + #offMaxOutput], w6    ; load upper limit value
	cpslt w4, w6    ; compare values and skip next instruction if control output is within operating range (control output < upper limit)
	mov w6, w4    ; override controller output
	
; Check for lower limit violation
	mov [w0 + #offMinOutput], w6    ; load lower limit value
	cpsgt w4, w6    ; compare values and skip next instruction if control output is within operating range (control output > lower limit)
	mov w6, w4    ; override controller output
	
;------------------------------------------------------------------------------
; Write control output value to target
	mov [w0 + #offTargetRegister], w8    ; move pointer to target in to working register
	mov w4, [w8]    ; move control output into target address
	
;------------------------------------------------------------------------------
; Load pointer to first element of control history array
	mov [w0 + #offControlHistory], w10    ; load pointer address into wreg
	
;------------------------------------------------------------------------------
; Update control output history
	mov [w10 + #0], w6    ; move entry (n-1) one tick down the delay line
	mov w6, [w10 + #2]
	mov w4, [w10]    ; add most recent control output to history
	
;------------------------------------------------------------------------------
; Enable/Disable bypass branch target with dummy read of source buffer
	goto CHA_ILOOP_EXIT_LOOP    ; when enabled, step over dummy read and go straight to EXIT
	CHA_ILOOP_BYPASS_LOOP:    ; Enable/Disable bypass branch target to perform dummy read of source to clear the source buffer
	mov [w0 + #offSourceRegister], w2    ; load pointer to input source register
	mov [w2], w1    ; move value from input source into working register
	mov [w0 + #offPtrControlInput], w2    ; load pointer address of target buffer of most recent controller input from data structure
	mov w1, [w2]    ; copy most recent controller input value to given data buffer target
	CHA_ILOOP_EXIT_LOOP:    ; Exit control loop branch target
	
;------------------------------------------------------------------------------
; Call next function of cascade
	mov [w0 + #offPtrCascadedFunction], w1    ; load functoin pointer
	mov [w0 + #offPtrCascadedFunParam], w0    ; load single parameter or pointer to parameter data structure
	call w1    ; call function
	pop w12    ; restore working register used for status flag tracking
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; Global function declaration _cha_iloop_Reset
; This function clears control and error histories enforcing a reset
;------------------------------------------------------------------------------
	
	.global _cha_iloop_Reset
_cha_iloop_Reset:
	
;------------------------------------------------------------------------------
; Clear control history array
	push w0    ; Set pointer to the base address of control history array
	mov  [w0 + #offControlHistory], w0
	clr [w0++]    ; Clear next address of control history array
	clr [w0]    ; Clear last address of control history array
	pop w0
	
;------------------------------------------------------------------------------
; Clear error history array
	push w0    ; Set pointer to the base address of error history array
	mov [w0 + #offErrorHistory], w0
	clr [w0++]    ; Clear next address of error history array
	clr [w0++]    ; Clear next address of error history array
	clr [w0]    ; Clear last address of error history array
	pop w0
	
;------------------------------------------------------------------------------
; End of routine
	return
;------------------------------------------------------------------------------
	
;------------------------------------------------------------------------------
; Global function declaration _cha_iloop_Precharge
; This function loads user-defined default values into control and error histories
;------------------------------------------------------------------------------
	
	.global _cha_iloop_Precharge
_cha_iloop_Precharge:
	
;------------------------------------------------------------------------------
; Charge error history array with defined value
	push w0    ; Set pointer to the base address of error history array
	push w1
	mov  [w0 + #offErrorHistory], w0
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
	