	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\mcc.c"
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
	.global	_OSCILLATOR_Initialize	; export
	.type	_OSCILLATOR_Initialize,@function
_OSCILLATOR_Initialize:
.LFB3:
	.file 1 "mcc_generated_files/mcc.c"
	.loc 1 82 0
	.set ___PA___,1
	.loc 1 84 0
	mov	#12288,w0
	mov	w0,_CLKDIV
	.loc 1 86 0
	clr	_OSCTUN
	.loc 1 88 0
	mov	#1,w0
	mov	#154,w2
	mov	#120,w1
	mov	#_OSCCON+1,w3
	mov.b	w1,[w3]
	mov.b	w2,[w3]
	mov.b	w0,[w3]
	.loc 1 89 0
	mov	#87,w2
	mov	#70,w1
	mov	#_OSCCON,w3
	mov.b	w1,[w3]
	mov.b	w2,[w3]
	mov.b	w0,[w3]
.L2:
	.loc 1 91 0
	btst.b	_OSCCONbits,#0
	.set ___BP___,91
	bra	nz,.L2
	.loc 1 92 0
	return	
	.set ___PA___,0
.LFE3:
	.size	_OSCILLATOR_Initialize, .-_OSCILLATOR_Initialize
	.align	2
	.global	_SYSTEM_Initialize	; export
	.type	_SYSTEM_Initialize,@function
_SYSTEM_Initialize:
.LFB2:
	.loc 1 72 0
	.set ___PA___,1
	.loc 1 73 0
	rcall	_PIN_MANAGER_Initialize
	.loc 1 74 0
	rcall	_OSCILLATOR_Initialize
	.loc 1 75 0
	rcall	_INTERRUPT_Initialize
	.loc 1 76 0
	rcall	_ADC1_Initialize
	.loc 1 77 0
	rcall	_UART1_Initialize
	.loc 1 78 0
	bra	_TMR1_Initialize
	.loc 1 79 0
	.set ___PA___,0
.LFE2:
	.size	_SYSTEM_Initialize, .-_SYSTEM_Initialize
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
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE2:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.section	.debug_info,info
	.4byte	0x38c
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"mcc_generated_files/mcc.c"
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
	.4byte	0xf8
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x2
	.byte	0x31
	.4byte	0x119
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
	.byte	0x2
	.byte	0x3
	.2byte	0xc63
	.4byte	0x200
	.uleb128 0x5
	.asciz	"OSWEN"
	.byte	0x3
	.2byte	0xc64
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"SOSCEN"
	.byte	0x3
	.2byte	0xc65
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"CF"
	.byte	0x3
	.2byte	0xc67
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LOCK"
	.byte	0x3
	.2byte	0xc69
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"IOLOCK"
	.byte	0x3
	.2byte	0xc6a
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"CLKLOCK"
	.byte	0x3
	.2byte	0xc6b
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"NOSC"
	.byte	0x3
	.2byte	0xc6c
	.4byte	0x109
	.byte	0x2
	.byte	0x3
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"COSC"
	.byte	0x3
	.2byte	0xc6e
	.4byte	0x109
	.byte	0x2
	.byte	0x3
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.byte	0x2
	.byte	0x3
	.2byte	0xc70
	.4byte	0x282
	.uleb128 0x5
	.asciz	"NOSC0"
	.byte	0x3
	.2byte	0xc72
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"NOSC1"
	.byte	0x3
	.2byte	0xc73
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"NOSC2"
	.byte	0x3
	.2byte	0xc74
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"COSC0"
	.byte	0x3
	.2byte	0xc76
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"COSC1"
	.byte	0x3
	.2byte	0xc77
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"COSC2"
	.byte	0x3
	.2byte	0xc78
	.4byte	0x109
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.byte	0x2
	.byte	0x3
	.2byte	0xc62
	.4byte	0x296
	.uleb128 0x7
	.4byte	0x158
	.uleb128 0x7
	.4byte	0x200
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagOSCCONBITS"
	.byte	0x2
	.byte	0x3
	.2byte	0xc61
	.4byte	0x2b6
	.uleb128 0x9
	.4byte	0x282
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.asciz	"OSCCONBITS"
	.byte	0x3
	.2byte	0xc7b
	.4byte	0x296
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"short unsigned int"
	.uleb128 0xb
	.byte	0x1
	.asciz	"OSCILLATOR_Initialize"
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.uleb128 0xb
	.byte	0x1
	.asciz	"SYSTEM_Initialize"
	.byte	0x1
	.byte	0x47
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.uleb128 0xc
	.4byte	.LASF0
	.byte	0x3
	.2byte	0xc7c
	.4byte	0x333
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0x2b6
	.uleb128 0xe
	.asciz	"CLKDIV"
	.byte	0x3
	.2byte	0xc83
	.4byte	0x349
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0x109
	.uleb128 0xe
	.asciz	"OSCTUN"
	.byte	0x3
	.2byte	0xc9c
	.4byte	0x349
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.4byte	.LASF0
	.byte	0x3
	.2byte	0xc7c
	.4byte	0x333
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"CLKDIV"
	.byte	0x3
	.2byte	0xc83
	.4byte	0x349
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"OSCTUN"
	.byte	0x3
	.2byte	0xc9c
	.4byte	0x349
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
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x5
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
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.4byte	0x3e
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x390
	.4byte	0x2df
	.asciz	"OSCILLATOR_Initialize"
	.4byte	0x304
	.asciz	"SYSTEM_Initialize"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x48
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x390
	.4byte	0xe9
	.asciz	"uint8_t"
	.4byte	0x109
	.asciz	"uint16_t"
	.4byte	0x296
	.asciz	"tagOSCCONBITS"
	.4byte	0x2b6
	.asciz	"OSCCONBITS"
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
	.asciz	"OSCCONbits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words
; Configuration word @ 0x0000abfe
	.section	.config_JTAGEN, code, address(0xabfe), keep
__config_JTAGEN:
	.pword	16255
; Configuration word @ 0x0000abfc
	.section	.config_IESO, code, address(0xabfc), keep
__config_IESO:
	.pword	63583

	.set ___PA___,0
	.end
