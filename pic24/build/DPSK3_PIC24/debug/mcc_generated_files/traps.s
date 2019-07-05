	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\traps.c"
	.section	.debug_abbrev,info
.Ldebug_abbrev0:
	.section	.debug_info,info
.Ldebug_info0:
	.section	.debug_line,info
.Ldebug_line0:
	.section	.text,code
.Ltext0:
	.section	.text,code
	.align	2
	.type	_use_failsafe_stack,@function
_use_failsafe_stack:
.LFB1:
	.file 1 "mcc_generated_files/traps.c"
	.loc 1 81 0
	.set ___PA___,0
	.loc 1 83 0
	mov	#_failsafe_stack.4181,w0
; 83 "mcc_generated_files/traps.c" 1
		mov    w0, W15
	
	.loc 1 91 0
	add	w0,#24,w0
	mov	w0,_SPLIM
	.loc 1 93 0
	return	
	.set ___PA___,0
.LFE1:
	.size	_use_failsafe_stack, .-_use_failsafe_stack
	.align	2
	.weak	_TRAPS_halt_on_error
	.type	_TRAPS_halt_on_error,@function
_TRAPS_halt_on_error:
.LFB0:
	.loc 1 66 0
	.set ___PA___,1
	.loc 1 67 0
	mov	w0,_TRAPS_error_code
	.loc 1 69 0
	.pword 0xda4000
.L3:
	bra	.L3
.LFE0:
	.size	_TRAPS_halt_on_error, .-_TRAPS_halt_on_error
	.section	.isr.text,code,keep
	.align	2
	.global	__OscillatorFail	; export
	.type	__OscillatorFail,@function
__OscillatorFail:
	.section	.isr.text,code,keep
.LFB2:
	.section	.isr.text,code,keep
	.loc 1 97 0
	.set ___PA___,1
	push	_RCOUNT
.LCFI0:
	.section	.isr.text,code,keep
	.loc 1 98 0
	bclr.b	_INTCON1bits,#1
	.section	.isr.text,code,keep
	.loc 1 99 0
	clr	w0
	rcall	_TRAPS_halt_on_error
.LFE2:
	.size	__OscillatorFail, .-__OscillatorFail
	.section	.isr.text,code,keep
	.align	2
	.global	__StackError	; export
	.type	__StackError,@function
__StackError:
	.section	.isr.text,code,keep
.LFB3:
	.section	.isr.text,code,keep
	.loc 1 103 0
	.set ___PA___,1
	push	_RCOUNT
.LCFI1:
	.section	.isr.text,code,keep
	.loc 1 108 0
	rcall	_use_failsafe_stack
	.section	.isr.text,code,keep
	.loc 1 109 0
	bclr.b	_INTCON1bits,#2
	.section	.isr.text,code,keep
	.loc 1 110 0
	mov	#1,w0
	rcall	_TRAPS_halt_on_error
.LFE3:
	.size	__StackError, .-__StackError
	.section	.isr.text,code,keep
	.align	2
	.global	__AddressError	; export
	.type	__AddressError,@function
__AddressError:
	.section	.isr.text,code,keep
.LFB4:
	.section	.isr.text,code,keep
	.loc 1 114 0
	.set ___PA___,1
	push	_RCOUNT
.LCFI2:
	.section	.isr.text,code,keep
	.loc 1 115 0
	bclr.b	_INTCON1bits,#3
	.section	.isr.text,code,keep
	.loc 1 116 0
	mov	#2,w0
	rcall	_TRAPS_halt_on_error
.LFE4:
	.size	__AddressError, .-__AddressError
	.section	.isr.text,code,keep
	.align	2
	.global	__MathError	; export
	.type	__MathError,@function
__MathError:
	.section	.isr.text,code,keep
.LFB5:
	.section	.isr.text,code,keep
	.loc 1 120 0
	.set ___PA___,1
	push	_RCOUNT
.LCFI3:
	.section	.isr.text,code,keep
	.loc 1 121 0
	bclr.b	_INTCON1bits,#4
	.section	.isr.text,code,keep
	.loc 1 122 0
	mov	#3,w0
	rcall	_TRAPS_halt_on_error
.LFE5:
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
	.section	.debug_frame,info
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.byte	0
	.uleb128 0x1
	.sleb128 2
	.byte	0x25
	.byte	0x12
	.uleb128 0xf
	.sleb128 -2
	.byte	0x9
	.uleb128 0x25
	.uleb128 0xf
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE10:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.file 4 "mcc_generated_files/traps.h"
	.section	.debug_info,info
	.4byte	0x393
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"mcc_generated_files/traps.c"
	.ascii	"C:\\\\_dsmps\\\\DPSK3\\\\Troubleshooting\\\\__src__\\\\dpsk3-firmwar"
	.asciz	"e\\\\pic24"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.asciz	"signed char"
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.asciz	"long int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.asciz	"long long int"
	.uleb128 0x3
	.asciz	"uint8_t"
	.byte	0x2
	.byte	0x2b
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x2
	.byte	0x31
	.4byte	0x11b
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"unsigned int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.asciz	"long unsigned int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.asciz	"long long unsigned int"
	.uleb128 0x4
	.asciz	"tagINTCON1BITS"
	.byte	0x2
	.byte	0x3
	.byte	0xdc
	.4byte	0x1d9
	.uleb128 0x5
	.asciz	"OSCFAIL"
	.byte	0x3
	.byte	0xde
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"STKERR"
	.byte	0x3
	.byte	0xdf
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"ADDRERR"
	.byte	0x3
	.byte	0xe0
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"MATHERR"
	.byte	0x3
	.byte	0xe1
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"NSTDIS"
	.byte	0x3
	.byte	0xe3
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x3
	.asciz	"INTCON1BITS"
	.byte	0x3
	.byte	0xe4
	.4byte	0x15a
	.uleb128 0x6
	.byte	0x2
	.byte	0x4
	.byte	0x36
	.4byte	0x23d
	.uleb128 0x7
	.asciz	"TRAPS_OSC_FAIL"
	.sleb128 0
	.uleb128 0x7
	.asciz	"TRAPS_STACK_ERR"
	.sleb128 1
	.uleb128 0x7
	.asciz	"TRAPS_ADDRESS_ERR"
	.sleb128 2
	.uleb128 0x7
	.asciz	"TRAPS_MATH_ERR"
	.sleb128 3
	.byte	0x0
	.uleb128 0x8
	.asciz	"use_failsafe_stack"
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.4byte	0x27f
	.uleb128 0x9
	.asciz	"failsafe_stack"
	.byte	0x1
	.byte	0x52
	.4byte	0x27f
	.byte	0x5
	.byte	0x3
	.4byte	_failsafe_stack.4181
	.byte	0x0
	.uleb128 0xa
	.4byte	0xeb
	.4byte	0x28f
	.uleb128 0xb
	.4byte	0x11b
	.byte	0x1f
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"TRAPS_halt_on_error"
	.byte	0x1
	.byte	0x41
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x2c5
	.uleb128 0xd
	.asciz	"code"
	.byte	0x1
	.byte	0x41
	.4byte	0x10b
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0xe
	.byte	0x1
	.asciz	"_OscillatorFail"
	.byte	0x1
	.byte	0x60
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"_StackError"
	.byte	0x1
	.byte	0x66
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"_AddressError"
	.byte	0x1
	.byte	0x71
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"_MathError"
	.byte	0x1
	.byte	0x77
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.uleb128 0xf
	.asciz	"SPLIM"
	.byte	0x3
	.byte	0x57
	.4byte	0x345
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x10b
	.uleb128 0x11
	.4byte	.LASF0
	.byte	0x3
	.byte	0xe5
	.4byte	0x357
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x1d9
	.uleb128 0x9
	.asciz	"TRAPS_error_code"
	.byte	0x1
	.byte	0x3a
	.4byte	0x10b
	.byte	0x5
	.byte	0x3
	.4byte	_TRAPS_error_code
	.uleb128 0xf
	.asciz	"SPLIM"
	.byte	0x3
	.byte	0x57
	.4byte	0x345
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF0
	.byte	0x3
	.byte	0xe5
	.4byte	0x357
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.section	.debug_abbrev,info
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xd
	.uleb128 0xb
	.uleb128 0xc
	.uleb128 0xb
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x6b
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x397
	.4byte	0x28f
	.asciz	"TRAPS_halt_on_error"
	.4byte	0x2c5
	.asciz	"_OscillatorFail"
	.4byte	0x2e4
	.asciz	"_StackError"
	.4byte	0x2ff
	.asciz	"_AddressError"
	.4byte	0x31c
	.asciz	"_MathError"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x4a
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x397
	.4byte	0xeb
	.asciz	"uint8_t"
	.4byte	0x10b
	.asciz	"uint16_t"
	.4byte	0x15a
	.asciz	"tagINTCON1BITS"
	.4byte	0x1d9
	.asciz	"INTCON1BITS"
	.4byte	0x0
	.section	.debug_aranges,info
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_str,info
.LASF0:
	.asciz	"INTCON1bits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
