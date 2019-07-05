	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\pin_manager.c"
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
	.global	_PIN_MANAGER_Initialize	; export
	.type	_PIN_MANAGER_Initialize,@function
_PIN_MANAGER_Initialize:
.LFB0:
	.file 1 "mcc_generated_files/pin_manager.c"
	.loc 1 58 0
	.set ___PA___,1
	.loc 1 62 0
	clr	_LATA
	.loc 1 63 0
	mov	#96,w0
	mov	w0,_LATB
	.loc 1 64 0
	clr	_LATC
	.loc 1 69 0
	mov	#1823,w0
	mov	w0,_TRISA
	.loc 1 70 0
	mov	#16319,w0
	mov	w0,_TRISB
	.loc 1 71 0
	mov	#1016,w0
	mov	w0,_TRISC
	.loc 1 76 0
	clr	_CNPU1
	.loc 1 77 0
	mov	#26624,w0
	mov	w0,_CNPU2
	.loc 1 82 0
	clr	_ODCA
	.loc 1 83 0
	clr	_ODCB
	.loc 1 84 0
	clr	_ODCC
	.loc 1 89 0
	mov	#1996,w0
	mov	w0,_AD1PCFG
	.loc 1 95 0
	mov	#191,w0
	and	_OSCCON,WREG
	mov	#70,w2
	mov	#87,w3
	mov	#_OSCCON,w1
	mov.b	w2,[w1]
	mov.b	w3,[w1]
	mov.b	w0,[w1]
	.loc 1 97 0
	mov	#-32,w0
	mov	_RPINR18bits,w4
	and	w0,w4,w1
	ior	#5,w1
	mov	w1,_RPINR18bits
	.loc 1 98 0
	and	_RPOR3bits,WREG
	ior	#3,w0
	mov	w0,_RPOR3bits
	.loc 1 100 0
	mov	_OSCCON,w0
	bset	w0,#6
	mov	#_OSCCON,w1
	mov.b	w2,[w1]
	mov.b	w3,[w1]
	mov.b	w0,[w1]
	.loc 1 102 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_PIN_MANAGER_Initialize, .-_PIN_MANAGER_Initialize
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.section	.debug_info,info
	.4byte	0x5f5
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"mcc_generated_files/pin_manager.c"
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
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x3
	.byte	0x31
	.4byte	0x112
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
	.byte	0x2
	.2byte	0xa6a
	.4byte	0x184
	.uleb128 0x5
	.asciz	"U1RXR"
	.byte	0x2
	.2byte	0xa6b
	.4byte	0x102
	.byte	0x2
	.byte	0x5
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR"
	.byte	0x2
	.2byte	0xa6d
	.4byte	0x102
	.byte	0x2
	.byte	0x5
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.byte	0x2
	.byte	0x2
	.2byte	0xa6f
	.4byte	0x265
	.uleb128 0x5
	.asciz	"U1RXR0"
	.byte	0x2
	.2byte	0xa70
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1RXR1"
	.byte	0x2
	.2byte	0xa71
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1RXR2"
	.byte	0x2
	.2byte	0xa72
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1RXR3"
	.byte	0x2
	.2byte	0xa73
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1RXR4"
	.byte	0x2
	.2byte	0xa74
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR0"
	.byte	0x2
	.2byte	0xa76
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR1"
	.byte	0x2
	.2byte	0xa77
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR2"
	.byte	0x2
	.2byte	0xa78
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR3"
	.byte	0x2
	.2byte	0xa79
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"U1CTSR4"
	.byte	0x2
	.2byte	0xa7a
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.byte	0x2
	.byte	0x2
	.2byte	0xa69
	.4byte	0x279
	.uleb128 0x7
	.4byte	0x151
	.uleb128 0x7
	.4byte	0x184
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagRPINR18BITS"
	.byte	0x2
	.byte	0x2
	.2byte	0xa68
	.4byte	0x29a
	.uleb128 0x9
	.4byte	0x265
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.asciz	"RPINR18BITS"
	.byte	0x2
	.2byte	0xa7d
	.4byte	0x279
	.uleb128 0x4
	.byte	0x2
	.byte	0x2
	.2byte	0xb44
	.4byte	0x2de
	.uleb128 0x5
	.asciz	"RP6R"
	.byte	0x2
	.2byte	0xb45
	.4byte	0x102
	.byte	0x2
	.byte	0x5
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R"
	.byte	0x2
	.2byte	0xb47
	.4byte	0x102
	.byte	0x2
	.byte	0x5
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x4
	.byte	0x2
	.byte	0x2
	.2byte	0xb49
	.4byte	0x3b0
	.uleb128 0x5
	.asciz	"RP6R0"
	.byte	0x2
	.2byte	0xb4a
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP6R1"
	.byte	0x2
	.2byte	0xb4b
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP6R2"
	.byte	0x2
	.2byte	0xb4c
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP6R3"
	.byte	0x2
	.2byte	0xb4d
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP6R4"
	.byte	0x2
	.2byte	0xb4e
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R0"
	.byte	0x2
	.2byte	0xb50
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R1"
	.byte	0x2
	.2byte	0xb51
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R2"
	.byte	0x2
	.2byte	0xb52
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R3"
	.byte	0x2
	.2byte	0xb53
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RP7R4"
	.byte	0x2
	.2byte	0xb54
	.4byte	0x102
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.byte	0x2
	.byte	0x2
	.2byte	0xb43
	.4byte	0x3c4
	.uleb128 0x7
	.4byte	0x2ae
	.uleb128 0x7
	.4byte	0x2de
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagRPOR3BITS"
	.byte	0x2
	.byte	0x2
	.2byte	0xb42
	.4byte	0x3e3
	.uleb128 0x9
	.4byte	0x3b0
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.asciz	"RPOR3BITS"
	.byte	0x2
	.2byte	0xb57
	.4byte	0x3c4
	.uleb128 0xb
	.byte	0x1
	.asciz	"PIN_MANAGER_Initialize"
	.byte	0x1
	.byte	0x39
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0xc
	.asciz	"CNPU1"
	.byte	0x2
	.byte	0xb0
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0x102
	.uleb128 0xc
	.asciz	"CNPU2"
	.byte	0x2
	.byte	0xc6
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISA"
	.byte	0x2
	.2byte	0x6be
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATA"
	.byte	0x2
	.2byte	0x6de
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCA"
	.byte	0x2
	.2byte	0x6ee
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISB"
	.byte	0x2
	.2byte	0x6fe
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATB"
	.byte	0x2
	.2byte	0x72a
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCB"
	.byte	0x2
	.2byte	0x740
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISC"
	.byte	0x2
	.2byte	0x756
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATC"
	.byte	0x2
	.2byte	0x776
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCC"
	.byte	0x2
	.2byte	0x786
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"AD1PCFG"
	.byte	0x2
	.2byte	0x838
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF0
	.byte	0x2
	.2byte	0xa7e
	.4byte	0x4e8
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0x29a
	.uleb128 0xf
	.4byte	.LASF1
	.byte	0x2
	.2byte	0xb58
	.4byte	0x4fb
	.byte	0x1
	.byte	0x1
	.uleb128 0xd
	.4byte	0x3e3
	.uleb128 0xe
	.asciz	"OSCCON"
	.byte	0x2
	.2byte	0xc60
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"CNPU1"
	.byte	0x2
	.byte	0xb0
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xc
	.asciz	"CNPU2"
	.byte	0x2
	.byte	0xc6
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISA"
	.byte	0x2
	.2byte	0x6be
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATA"
	.byte	0x2
	.2byte	0x6de
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCA"
	.byte	0x2
	.2byte	0x6ee
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISB"
	.byte	0x2
	.2byte	0x6fe
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATB"
	.byte	0x2
	.2byte	0x72a
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCB"
	.byte	0x2
	.2byte	0x740
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"TRISC"
	.byte	0x2
	.2byte	0x756
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"LATC"
	.byte	0x2
	.2byte	0x776
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"ODCC"
	.byte	0x2
	.2byte	0x786
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"AD1PCFG"
	.byte	0x2
	.2byte	0x838
	.4byte	0x42a
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF0
	.byte	0x2
	.2byte	0xa7e
	.4byte	0x4e8
	.byte	0x1
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF1
	.byte	0x2
	.2byte	0xb58
	.4byte	0x4fb
	.byte	0x1
	.byte	0x1
	.uleb128 0xe
	.asciz	"OSCCON"
	.byte	0x2
	.2byte	0xc60
	.4byte	0x42a
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
	.uleb128 0xf
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
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x29
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x5f9
	.4byte	0x3f5
	.asciz	"PIN_MANAGER_Initialize"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x5d
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x5f9
	.4byte	0x102
	.asciz	"uint16_t"
	.4byte	0x279
	.asciz	"tagRPINR18BITS"
	.4byte	0x29a
	.asciz	"RPINR18BITS"
	.4byte	0x3c4
	.asciz	"tagRPOR3BITS"
	.4byte	0x3e3
	.asciz	"RPOR3BITS"
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
	.asciz	"RPINR18bits"
.LASF1:
	.asciz	"RPOR3bits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
