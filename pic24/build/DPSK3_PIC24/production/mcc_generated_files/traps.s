	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\traps.c"
	.section	.text,code
	.align	2
	.type	_use_failsafe_stack,@function
_use_failsafe_stack:
	.set ___PA___,0
	mov	#_failsafe_stack.4181,w0
; 83 "mcc_generated_files/traps.c" 1
		mov    w0, W15
	
	add	w0,#24,w0
	mov	w0,_SPLIM
	return	
	.set ___PA___,0
	.size	_use_failsafe_stack, .-_use_failsafe_stack
	.align	2
	.weak	_TRAPS_halt_on_error
	.type	_TRAPS_halt_on_error,@function
_TRAPS_halt_on_error:
	.set ___PA___,1
	mov	w0,_TRAPS_error_code
.L3:
	bra	.L3
	.size	_TRAPS_halt_on_error, .-_TRAPS_halt_on_error
	.section	.isr.text,code,keep
	.align	2
	.global	__OscillatorFail	; export
	.type	__OscillatorFail,@function
__OscillatorFail:
	.set ___PA___,1
	push	_RCOUNT
	bclr.b	_INTCON1bits,#1
	clr	w0
	rcall	_TRAPS_halt_on_error
	.size	__OscillatorFail, .-__OscillatorFail
	.section	.isr.text,code,keep
	.align	2
	.global	__StackError	; export
	.type	__StackError,@function
__StackError:
	.set ___PA___,1
	push	_RCOUNT
	rcall	_use_failsafe_stack
	bclr.b	_INTCON1bits,#2
	mov	#1,w0
	rcall	_TRAPS_halt_on_error
	.size	__StackError, .-__StackError
	.section	.isr.text,code,keep
	.align	2
	.global	__AddressError	; export
	.type	__AddressError,@function
__AddressError:
	.set ___PA___,1
	push	_RCOUNT
	bclr.b	_INTCON1bits,#3
	mov	#2,w0
	rcall	_TRAPS_halt_on_error
	.size	__AddressError, .-__AddressError
	.section	.isr.text,code,keep
	.align	2
	.global	__MathError	; export
	.type	__MathError,@function
__MathError:
	.set ___PA___,1
	push	_RCOUNT
	bclr.b	_INTCON1bits,#4
	mov	#3,w0
	rcall	_TRAPS_halt_on_error
	.size	__MathError, .-__MathError
	.section	.bss,bss
	.type	_failsafe_stack.4181,@object
	.size	_failsafe_stack.4181, 32
_failsafe_stack.4181:
	.skip	32
	.section	.ndata,data,near
	.align	2
	.type	_TRAPS_error_code,@object
	.size	_TRAPS_error_code, 2
_TRAPS_error_code:
	.word	-1



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
