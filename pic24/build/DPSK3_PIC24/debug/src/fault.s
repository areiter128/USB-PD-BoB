	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\fault.c"
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
	.type	_FaultInput,@function
_FaultInput:
.LFB4:
	.file 1 "src/fault.c"
	.loc 1 112 0
	.set ___PA___,1
	.loc 1 113 0
	sub.b	w0,#1,[w15]
	.set ___BP___,29
	bra	z,.L4
	.set ___BP___,50
	bra	ltu,.L3
	sub.b	w0,#2,[w15]
	.set ___BP___,29
	bra	z,.L5
	sub.b	w0,#3,[w15]
	.set ___BP___,71
	bra	nz,.L8
	bra	.L11
.L4:
	.loc 1 115 0
	mov	_PORTCbits,w0
	lsr	w0,#7,w0
	bra	.L10
.L3:
	.loc 1 116 0
	mov	_PORTCbits,w0
	lsr	w0,#6,w0
	bra	.L10
.L11:
	.loc 1 117 0
	mov	_PORTBbits,w0
	bra	.L9
.L5:
	.loc 1 118 0
	mov	_PORTCbits,w0
.L9:
	lsr	w0,#9,w0
.L10:
	and.b	w0,#1,w0
	return	
.L8:
	.loc 1 119 0
	retlw	#0,w0
.LFE4:
	.size	_FaultInput, .-_FaultInput
	.align	2
	.type	_FaultClear,@function
_FaultClear:
.LFB5:
	.loc 1 124 0
	.set ___PA___,1
	.loc 1 125 0
	sub.b	w0,#1,[w15]
	.set ___BP___,29
	bra	z,.L15
	.set ___BP___,50
	bra	ltu,.L14
	sub.b	w0,#2,[w15]
	.set ___BP___,29
	bra	z,.L16
	sub.b	w0,#3,[w15]
	.set ___BP___,71
	bra	nz,.L12
	bra	.L18
.L15:
	.loc 1 128 0
	bclr.b	_LATBbits+1,#3
	.loc 1 129 0
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	.loc 1 131 0
	bset.b	_LATBbits+1,#3
	.loc 1 132 0
	return	
.L14:
	.loc 1 135 0
	bclr.b	_LATBbits+1,#2
	.loc 1 136 0
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	.loc 1 138 0
	bset.b	_LATBbits+1,#2
	.loc 1 139 0
	return	
.L18:
	.loc 1 142 0
	bclr.b	_LATBbits+1,#5
	.loc 1 143 0
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	.loc 1 145 0
	bset.b	_LATBbits+1,#5
	.loc 1 146 0
	return	
.L16:
	.loc 1 149 0
	bclr.b	_LATBbits+1,#4
	.loc 1 150 0
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	.loc 1 152 0
	bset.b	_LATBbits+1,#4
.L12:
	return	
.LFE5:
	.size	_FaultClear, .-_FaultClear
	.align	2
	.type	_INTERRUPT_GlobalDisable,@function
_INTERRUPT_GlobalDisable:
.LFB1:
	.file 2 "mcc_generated_files/interrupt_manager.h"
	.loc 2 136 0
	.set ___PA___,1
	.loc 2 137 0
	disi	#16383
	.loc 2 138 0
	return	
	.set ___PA___,0
.LFE1:
	.size	_INTERRUPT_GlobalDisable, .-_INTERRUPT_GlobalDisable
	.align	2
	.type	_INTERRUPT_GlobalEnable,@function
_INTERRUPT_GlobalEnable:
.LFB0:
	.loc 2 105 0
	.set ___PA___,1
	.loc 2 106 0
	disi	#0
	.loc 2 107 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_INTERRUPT_GlobalEnable, .-_INTERRUPT_GlobalEnable
	.align	2
	.global	_FaultInit	; export
	.type	_FaultInit,@function
_FaultInit:
.LFB2:
	.loc 1 54 0
	.set ___PA___,1
	.loc 1 56 0
	rcall	_INTERRUPT_GlobalDisable
	mov	#_fault_counters-2,w1
	clr	w0
.L22:
	.loc 1 59 0
	clr.b	w3
	mov	#_fault_flags,w2
	mov.b	w3,[w2+w0]
	.loc 1 60 0
	clr	[++w1]
	inc	w0,w0
	.loc 1 57 0
	sub	w0,#4,[w15]
	.set ___BP___,75
	bra	nz,.L22
	.loc 1 64 0
	bset.b	_TRISCbits,#7
	.loc 1 65 0
	bset.b	_TRISCbits,#6
	.loc 1 66 0
	bset.b	_TRISCbits+1,#1
	.loc 1 67 0
	bset.b	_TRISBbits+1,#1
	.loc 1 70 0
	bset.b	_LATBbits+1,#3
	.loc 1 71 0
	bset.b	_LATBbits+1,#2
	.loc 1 72 0
	bset.b	_LATBbits+1,#5
	.loc 1 73 0
	bset.b	_LATBbits+1,#4
	.loc 1 74 0
	bclr.b	_TRISBbits+1,#2
	.loc 1 75 0
	bclr.b	_TRISBbits+1,#3
	.loc 1 76 0
	bclr.b	_TRISBbits+1,#4
	.loc 1 77 0
	bclr.b	_TRISBbits+1,#5
	.loc 1 78 0
	bra	_INTERRUPT_GlobalEnable
	.loc 1 79 0
	.set ___PA___,0
.LFE2:
	.size	_FaultInit, .-_FaultInit
	.align	2
	.global	_FaultCheck	; export
	.type	_FaultCheck,@function
_FaultCheck:
.LFB3:
	.loc 1 82 0
	.set ___PA___,1
	mov.d	w8,[w15++]
.LCFI0:
	.loc 1 82 0
	clr	w9
	.loc 1 83 0
	clr.b	w8
.L25:
	.loc 1 88 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 89 0
	mov	#_fault_flags,w0
	mov.b	[w0+w9],w0
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L24
	.loc 1 90 0
	mov	#1,w0
	sl	w0,w9,w0
	ior.b	w8,w0,w8
.L24:
	.loc 1 91 0
	rcall	_INTERRUPT_GlobalEnable
	inc	w9,w9
	.loc 1 86 0
	sub	w9,#4,[w15]
	.set ___BP___,75
	bra	nz,.L25
	.loc 1 94 0
	ze	w8,w9
	btst	w9,#0
	.set ___BP___,71
	bra	z,.L26
	.loc 1 95 0
	mov.b	#2,w0
	rcall	_LedBlink
	bra	.L27
.L26:
	.loc 1 96 0
	btst	w9,#1
	.set ___BP___,50
	bra	z,.L28
	.loc 1 97 0
	mov.b	#2,w0
	rcall	_LedOn
	bra	.L27
.L28:
	.loc 1 99 0
	mov.b	#2,w0
	rcall	_LedOff
.L27:
	.loc 1 101 0
	btst	w9,#2
	.set ___BP___,79
	bra	z,.L29
	.loc 1 102 0
	mov.b	#5,w0
	rcall	_LedBlink
	bra	.L30
.L29:
	.loc 1 103 0
	btst	w9,#3
	.set ___BP___,61
	bra	z,.L31
	.loc 1 104 0
	mov.b	#5,w0
	rcall	_LedOn
	bra	.L30
.L31:
	.loc 1 106 0
	mov.b	#5,w0
	rcall	_LedOff
.L30:
	.loc 1 109 0
	mov.b	w8,w0
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE3:
	.size	_FaultCheck, .-_FaultCheck
	.align	2
	.global	_FaultTask	; export
	.type	_FaultTask,@function
_FaultTask:
.LFB6:
	.loc 1 161 0
	.set ___PA___,1
	lnk	#2
.LCFI1:
	.loc 1 164 0
	clr.b	w0
	bra	.L38
.L37:
	.loc 1 167 0
	mov.b	[w15-2],w0
	rcall	_FaultInput
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L34
	.loc 1 170 0
	mov	#_fault_counters,w0
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	[w0+w1],w1
	cp0	w1
	.set ___BP___,50
	bra	z,.L35
	.loc 1 172 0
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	add	w0,w1,w1
	dec	[w1],[w1]
	.loc 1 173 0
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	[w0+w1],w0
	cp0	w0
	.set ___BP___,71
	bra	nz,.L36
	.loc 1 174 0
	mov.b	[w15-2],w0
	rcall	_FaultClear
	bra	.L36
.L35:
	.loc 1 178 0
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	#200,w2
	mov	w2,[w0+w1]
	.loc 1 179 0
	mov.b	[w15-2],w1
	ze	w1,w0
	mov.b	#1,w2
	mov	#_fault_flags,w1
	mov.b	w2,[w1+w0]
	bra	.L36
.L34:
	.loc 1 184 0
	mov.b	[w15-2],w2
	ze	w2,w1
	mov	#_fault_flags,w2
	mov.b	w0,[w2+w1]
.L36:
	.loc 1 164 0
	mov.b	[w15-2],w0
	inc.b	w0,w0
.L38:
	mov.b	w0,[w15-2]
	mov.b	[w15-2],w1
	sub.b	w1,#3,[w15]
	.set ___BP___,91
	bra	leu,.L37
	.loc 1 187 0
	ulnk	
	return	
	.set ___PA___,0
.LFE6:
	.size	_FaultTask, .-_FaultTask
	.section	.nbss,bss,near
	.align	2
	.type	_fault_counters,@object
	.size	_fault_counters, 8
_fault_counters:
	.skip	8
	.section	.bss,bss
	.type	_fault_flags,@object
	.size	_fault_flags, 4
_fault_flags:
	.skip	4
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
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI0-.LFB3
	.byte	0x13
	.sleb128 -4
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.byte	0x4
	.4byte	.LCFI1-.LFB6
	.byte	0x13
	.sleb128 -3
	.byte	0xd
	.uleb128 0xe
	.byte	0x8e
	.uleb128 0x2
	.align	4
.LEFDE12:
	.section	.text,code
.Letext0:
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 4 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.section	.debug_info,info
	.4byte	0x9b6
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"src/fault.c"
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
	.byte	0x3
	.byte	0x2b
	.4byte	0xea
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x3
	.byte	0x31
	.4byte	0x10b
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
	.asciz	"tagTRISBBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x6ff
	.4byte	0x2b7
	.uleb128 0x5
	.asciz	"TRISB0"
	.byte	0x4
	.2byte	0x700
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB1"
	.byte	0x4
	.2byte	0x701
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB2"
	.byte	0x4
	.2byte	0x702
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB3"
	.byte	0x4
	.2byte	0x703
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB4"
	.byte	0x4
	.2byte	0x704
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB5"
	.byte	0x4
	.2byte	0x705
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB6"
	.byte	0x4
	.2byte	0x706
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB7"
	.byte	0x4
	.2byte	0x707
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB8"
	.byte	0x4
	.2byte	0x708
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB9"
	.byte	0x4
	.2byte	0x709
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB10"
	.byte	0x4
	.2byte	0x70a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB11"
	.byte	0x4
	.2byte	0x70b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB12"
	.byte	0x4
	.2byte	0x70c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB13"
	.byte	0x4
	.2byte	0x70d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB14"
	.byte	0x4
	.2byte	0x70e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISB15"
	.byte	0x4
	.2byte	0x70f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"TRISBBITS"
	.byte	0x4
	.2byte	0x710
	.4byte	0x14a
	.uleb128 0x4
	.asciz	"tagPORTBBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x715
	.4byte	0x406
	.uleb128 0x5
	.asciz	"RB0"
	.byte	0x4
	.2byte	0x716
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB1"
	.byte	0x4
	.2byte	0x717
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB2"
	.byte	0x4
	.2byte	0x718
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB3"
	.byte	0x4
	.2byte	0x719
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB4"
	.byte	0x4
	.2byte	0x71a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB5"
	.byte	0x4
	.2byte	0x71b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB6"
	.byte	0x4
	.2byte	0x71c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB7"
	.byte	0x4
	.2byte	0x71d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB8"
	.byte	0x4
	.2byte	0x71e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB9"
	.byte	0x4
	.2byte	0x71f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB10"
	.byte	0x4
	.2byte	0x720
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB11"
	.byte	0x4
	.2byte	0x721
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB12"
	.byte	0x4
	.2byte	0x722
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB13"
	.byte	0x4
	.2byte	0x723
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB14"
	.byte	0x4
	.2byte	0x724
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RB15"
	.byte	0x4
	.2byte	0x725
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"PORTBBITS"
	.byte	0x4
	.2byte	0x726
	.4byte	0x2c9
	.uleb128 0x4
	.asciz	"tagLATBBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x72b
	.4byte	0x574
	.uleb128 0x5
	.asciz	"LATB0"
	.byte	0x4
	.2byte	0x72c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB1"
	.byte	0x4
	.2byte	0x72d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB2"
	.byte	0x4
	.2byte	0x72e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB3"
	.byte	0x4
	.2byte	0x72f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB4"
	.byte	0x4
	.2byte	0x730
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB5"
	.byte	0x4
	.2byte	0x731
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB6"
	.byte	0x4
	.2byte	0x732
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB7"
	.byte	0x4
	.2byte	0x733
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB8"
	.byte	0x4
	.2byte	0x734
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB9"
	.byte	0x4
	.2byte	0x735
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB10"
	.byte	0x4
	.2byte	0x736
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB11"
	.byte	0x4
	.2byte	0x737
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB12"
	.byte	0x4
	.2byte	0x738
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB13"
	.byte	0x4
	.2byte	0x739
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB14"
	.byte	0x4
	.2byte	0x73a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB15"
	.byte	0x4
	.2byte	0x73b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"LATBBITS"
	.byte	0x4
	.2byte	0x73c
	.4byte	0x418
	.uleb128 0x4
	.asciz	"tagTRISCBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x757
	.4byte	0x66e
	.uleb128 0x5
	.asciz	"TRISC0"
	.byte	0x4
	.2byte	0x758
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC1"
	.byte	0x4
	.2byte	0x759
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC2"
	.byte	0x4
	.2byte	0x75a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC3"
	.byte	0x4
	.2byte	0x75b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC4"
	.byte	0x4
	.2byte	0x75c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC5"
	.byte	0x4
	.2byte	0x75d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC6"
	.byte	0x4
	.2byte	0x75e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC7"
	.byte	0x4
	.2byte	0x75f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC8"
	.byte	0x4
	.2byte	0x760
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISC9"
	.byte	0x4
	.2byte	0x761
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"TRISCBITS"
	.byte	0x4
	.2byte	0x762
	.4byte	0x585
	.uleb128 0x4
	.asciz	"tagPORTCBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x767
	.4byte	0x74b
	.uleb128 0x5
	.asciz	"RC0"
	.byte	0x4
	.2byte	0x768
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC1"
	.byte	0x4
	.2byte	0x769
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC2"
	.byte	0x4
	.2byte	0x76a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC3"
	.byte	0x4
	.2byte	0x76b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC4"
	.byte	0x4
	.2byte	0x76c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC5"
	.byte	0x4
	.2byte	0x76d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC6"
	.byte	0x4
	.2byte	0x76e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC7"
	.byte	0x4
	.2byte	0x76f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC8"
	.byte	0x4
	.2byte	0x770
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RC9"
	.byte	0x4
	.2byte	0x771
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"PORTCBITS"
	.byte	0x4
	.2byte	0x772
	.4byte	0x680
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"short unsigned int"
	.uleb128 0x7
	.asciz	"FaultInput"
	.byte	0x1
	.byte	0x6f
	.byte	0x1
	.4byte	0x7a2
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x7a2
	.uleb128 0x8
	.4byte	.LASF0
	.byte	0x1
	.byte	0x6f
	.4byte	0xdb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x9
	.asciz	"FaultClear"
	.byte	0x1
	.byte	0x7b
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x7d6
	.uleb128 0x8
	.4byte	.LASF0
	.byte	0x1
	.byte	0x7b
	.4byte	0xdb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0xa
	.asciz	"INTERRUPT_GlobalDisable"
	.byte	0x2
	.byte	0x87
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0xa
	.asciz	"INTERRUPT_GlobalEnable"
	.byte	0x2
	.byte	0x68
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0xb
	.byte	0x1
	.asciz	"FaultInit"
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x848
	.uleb128 0xc
	.asciz	"i"
	.byte	0x1
	.byte	0x37
	.4byte	0xdb
	.byte	0x0
	.uleb128 0xd
	.byte	0x1
	.asciz	"FaultCheck"
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.4byte	0xdb
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x88b
	.uleb128 0xe
	.asciz	"faultStatus"
	.byte	0x1
	.byte	0x53
	.4byte	0xdb
	.byte	0x1
	.byte	0x58
	.uleb128 0xf
	.4byte	.LASF0
	.byte	0x1
	.byte	0x53
	.4byte	0xdb
	.byte	0x0
	.uleb128 0xb
	.byte	0x1
	.asciz	"FaultTask"
	.byte	0x1
	.byte	0xa0
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x8b5
	.uleb128 0xe
	.asciz	"i"
	.byte	0x1
	.byte	0xa2
	.4byte	0x8b5
	.byte	0x2
	.byte	0x91
	.sleb128 -2
	.byte	0x0
	.uleb128 0x10
	.4byte	0xdb
	.uleb128 0x11
	.4byte	.LASF1
	.byte	0x4
	.2byte	0x711
	.4byte	0x8c8
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x2b7
	.uleb128 0x11
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x727
	.4byte	0x8db
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x406
	.uleb128 0x11
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x73d
	.4byte	0x8ee
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x574
	.uleb128 0x11
	.4byte	.LASF4
	.byte	0x4
	.2byte	0x763
	.4byte	0x901
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x66e
	.uleb128 0x11
	.4byte	.LASF5
	.byte	0x4
	.2byte	0x773
	.4byte	0x914
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.4byte	0x74b
	.uleb128 0x12
	.4byte	0x7a2
	.4byte	0x929
	.uleb128 0x13
	.4byte	0x10b
	.byte	0x3
	.byte	0x0
	.uleb128 0xe
	.asciz	"fault_flags"
	.byte	0x1
	.byte	0x32
	.4byte	0x942
	.byte	0x5
	.byte	0x3
	.4byte	_fault_flags
	.uleb128 0x10
	.4byte	0x919
	.uleb128 0x12
	.4byte	0xfb
	.4byte	0x957
	.uleb128 0x13
	.4byte	0x10b
	.byte	0x3
	.byte	0x0
	.uleb128 0xe
	.asciz	"fault_counters"
	.byte	0x1
	.byte	0x33
	.4byte	0x947
	.byte	0x5
	.byte	0x3
	.4byte	_fault_counters
	.uleb128 0x11
	.4byte	.LASF1
	.byte	0x4
	.2byte	0x711
	.4byte	0x8c8
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x727
	.4byte	0x8db
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x73d
	.4byte	0x8ee
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF4
	.byte	0x4
	.2byte	0x763
	.4byte	0x901
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF5
	.byte	0x4
	.2byte	0x773
	.4byte	0x914
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
	.uleb128 0x7
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x8
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x0
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
	.uleb128 0xb
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
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x39
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x9ba
	.4byte	0x821
	.asciz	"FaultInit"
	.4byte	0x848
	.asciz	"FaultCheck"
	.4byte	0x88b
	.asciz	"FaultTask"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0xc0
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x9ba
	.4byte	0xdb
	.asciz	"uint8_t"
	.4byte	0xfb
	.asciz	"uint16_t"
	.4byte	0x14a
	.asciz	"tagTRISBBITS"
	.4byte	0x2b7
	.asciz	"TRISBBITS"
	.4byte	0x2c9
	.asciz	"tagPORTBBITS"
	.4byte	0x406
	.asciz	"PORTBBITS"
	.4byte	0x418
	.asciz	"tagLATBBITS"
	.4byte	0x574
	.asciz	"LATBBITS"
	.4byte	0x585
	.asciz	"tagTRISCBITS"
	.4byte	0x66e
	.asciz	"TRISCBITS"
	.4byte	0x680
	.asciz	"tagPORTCBITS"
	.4byte	0x74b
	.asciz	"PORTCBITS"
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
.LASF4:
	.asciz	"TRISCbits"
.LASF0:
	.asciz	"fault_id"
.LASF2:
	.asciz	"PORTBbits"
.LASF5:
	.asciz	"PORTCbits"
.LASF3:
	.asciz	"LATBbits"
.LASF1:
	.asciz	"TRISBbits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
