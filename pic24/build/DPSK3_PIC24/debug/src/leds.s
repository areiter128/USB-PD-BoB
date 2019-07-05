	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\leds.c"
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
	.type	_INTERRUPT_GlobalDisable,@function
_INTERRUPT_GlobalDisable:
.LFB1:
	.file 1 "mcc_generated_files/interrupt_manager.h"
	.loc 1 136 0
	.set ___PA___,1
	.loc 1 137 0
	disi	#16383
	.loc 1 138 0
	return	
	.set ___PA___,0
.LFE1:
	.size	_INTERRUPT_GlobalDisable, .-_INTERRUPT_GlobalDisable
	.align	2
	.type	_INTERRUPT_GlobalEnable,@function
_INTERRUPT_GlobalEnable:
.LFB0:
	.loc 1 105 0
	.set ___PA___,1
	.loc 1 106 0
	disi	#0
	.loc 1 107 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_INTERRUPT_GlobalEnable, .-_INTERRUPT_GlobalEnable
	.align	2
	.global	_LedsInit	; export
	.type	_LedsInit,@function
_LedsInit:
.LFB2:
	.file 2 "src/leds.c"
	.loc 2 81 0
	.set ___PA___,1
	.loc 2 83 0
	rcall	_INTERRUPT_GlobalDisable
	clr	w2
	clr	w1
	bra	.L4
.L5:
	.loc 2 80 0
	add	w0,w2,w3
	.loc 2 87 0
	clr.b	w5
	mov	#_leds_status_array,w4
	mov.b	w5,[w4+w3]
	.loc 2 88 0
	mul.su	w1,#3,w4
	add	w0,w4,w3
	mov	#_leds_matrix,w4
	add	w4,w3,w3
	clr.b	[w3]
	inc	w0,w0
	.loc 2 85 0
	sub	w0,#3,[w15]
	.set ___BP___,66
	bra	nz,.L5
	inc	w1,w1
	add	w2,#3,w2
	.loc 2 84 0
	sub	w1,#3,[w15]
	.set ___BP___,33
	bra	z,.L6
.L4:
	.loc 2 81 0
	clr	w0
	bra	.L5
.L6:
	.loc 2 92 0
	bclr.b	_TRISBbits,#4
	.loc 2 93 0
	bclr.b	_TRISAbits,#4
	.loc 2 94 0
	bclr.b	_TRISAbits+1,#1
	.loc 2 96 0
	bclr.b	_TRISCbits,#3
	.loc 2 97 0
	bclr.b	_TRISCbits,#4
	.loc 2 98 0
	bclr.b	_TRISCbits,#5
	.loc 2 99 0
	bra	_INTERRUPT_GlobalEnable
	.loc 2 100 0
	.set ___PA___,0
.LFE2:
	.size	_LedsInit, .-_LedsInit
	.align	2
	.global	_LedOn	; export
	.type	_LedOn,@function
_LedOn:
.LFB3:
	.loc 2 103 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI0:
	mov.b	w0,w8
	.loc 2 104 0
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L7
	.loc 2 106 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 2 107 0
	ze	w8,w8
	mov.b	#1,w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	.loc 2 108 0
	rcall	_INTERRUPT_GlobalEnable
.L7:
	.loc 2 110 0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE3:
	.size	_LedOn, .-_LedOn
	.align	2
	.global	_LedOff	; export
	.type	_LedOff,@function
_LedOff:
.LFB4:
	.loc 2 113 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI1:
	mov.b	w0,w8
	.loc 2 114 0
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L9
	.loc 2 116 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 2 117 0
	ze	w8,w8
	clr.b	w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	.loc 2 118 0
	rcall	_INTERRUPT_GlobalEnable
.L9:
	.loc 2 120 0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE4:
	.size	_LedOff, .-_LedOff
	.align	2
	.global	_LedBlink	; export
	.type	_LedBlink,@function
_LedBlink:
.LFB5:
	.loc 2 123 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI2:
	mov.b	w0,w8
	.loc 2 124 0
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L11
	.loc 2 126 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 2 127 0
	ze	w8,w8
	mov.b	#2,w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	.loc 2 128 0
	rcall	_INTERRUPT_GlobalEnable
.L11:
	.loc 2 130 0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE5:
	.size	_LedBlink, .-_LedBlink
	.align	2
	.global	_LedsMatrixTask	; export
	.type	_LedsMatrixTask,@function
_LedsMatrixTask:
.LFB6:
	.loc 2 134 0
	.set ___PA___,1
	.loc 2 154 0
	mov	#_led_columns_array,w2
	.loc 2 133 0
	add	w2,#12,w3
	mov	w2,w0
.L14:
	.loc 2 141 0
	mov	[w0],w1
	mov	[w0+2],w4
	com	w4,w4
	and	w4,[w1],[w1]
	add	w0,#4,w0
	.loc 2 139 0
	sub	w0,w3,[w15]
	.set ___BP___,66
	bra	nz,.L14
	.loc 2 145 0
	mov.b	_row_counter.4220,WREG
	ze	w0,w4
	sl	w4,#2,w4
	mov	#_led_rows_array,w3
	mov	[w3+w4],w1
	inc2	w4,w4
	mov	[w3+w4],w3
	ior	w3,[w1],[w1]
	.loc 2 147 0
	inc.b	w0,w0
	mov.b	WREG,_row_counter.4220
	.loc 2 148 0
	sub.b	w0,#2,[w15]
	.set ___BP___,50
	bra	leu,.L15
	.loc 2 149 0
	clr.b	_row_counter.4220
.L15:
	.loc 2 154 0
	mov	#_row_counter.4220,w4
	mov.b	[w4],w4
	ze	w4,w4
	mov	#_led_columns_array+2,w1
	clr	w0
.L18:
	mul.su	w4,#3,w6
	add	w0,w6,w3
	mov	#_leds_matrix,w5
	mov.b	[w5+w3],w5
	mov	[w2],w3
	cp0.b	w5
	.set ___BP___,50
	bra	z,.L16
	.loc 2 155 0
	mov	[w3],w5
	ior	w5,[w1],[w3]
	bra	.L17
.L16:
	.loc 2 157 0
	com	[w1],w5
	and	w5,[w3],[w3]
.L17:
	inc	w0,w0
	add	w2,#4,w2
	add	w1,#4,w1
	.loc 2 152 0
	sub	w0,#3,[w15]
	.set ___BP___,66
	bra	nz,.L18
	.loc 2 161 0
	sl	w4,#2,w2
	mov	#_led_rows_array,w1
	mov	[w1+w2],w0
	inc2	w2,w2
	mov	[w1+w2],w1
	com	w1,w1
	and	w1,[w0],[w0]
	.loc 2 162 0
	return	
	.set ___PA___,0
.LFE6:
	.size	_LedsMatrixTask, .-_LedsMatrixTask
	.align	2
	.global	_LedsBlinkTask	; export
	.type	_LedsBlinkTask,@function
_LedsBlinkTask:
.LFB7:
	.loc 2 166 0
	.set ___PA___,1
.LBB2:
	.loc 2 181 0
	mov	#_blink_toggle.4232,w7
	mov.b	[w7],w7
	clr	w2
	clr	w1
	bra	.L20
.L25:
	.loc 2 165 0
	add	w0,w2,w3
	.loc 2 173 0
	mov	#_leds_status_array,w4
	mov.b	[w4+w3],w6
	mov	#_leds_matrix,w3
	mul.su	w1,#3,w4
	.loc 2 175 0
	sub.b	w6,#1,[w15]
	.set ___BP___,29
	bra	z,.L22
	sub.b	w6,#2,[w15]
	.set ___BP___,71
	bra	nz,.L28
	bra	.L29
.L22:
	.loc 2 178 0
	add	w0,w4,w4
	mov.b	w6,[w3+w4]
	.loc 2 179 0
	bra	.L24
.L29:
	.loc 2 181 0
	add	w0,w4,w4
	mov.b	w7,[w3+w4]
	.loc 2 182 0
	bra	.L24
.L28:
	.loc 2 184 0
	add	w0,w4,w4
	add	w3,w4,w3
	clr.b	[w3]
.L24:
	.loc 2 185 0
	inc	w0,w0
.LBE2:
	.loc 2 171 0
	sub	w0,#3,[w15]
	.set ___BP___,66
	bra	nz,.L25
	inc	w1,w1
	add	w2,#3,w2
	.loc 2 170 0
	sub	w1,#3,[w15]
	.set ___BP___,33
	bra	z,.L26
.L20:
	.loc 2 166 0
	clr	w0
	bra	.L25
.L26:
	.loc 2 189 0
	cp0.b	_blink_counter.4231
	.set ___BP___,39
	bra	nz,.L27
	.loc 2 191 0
	mov.b	#25,w0
	mov.b	WREG,_blink_counter.4231
	.loc 2 192 0
	btg.b	_blink_toggle.4232,#0
.L27:
	.loc 2 194 0
	dec.b	_blink_counter.4231
	.loc 2 195 0
	return	
	.set ___PA___,0
.LFE7:
	.size	_LedsBlinkTask, .-_LedsBlinkTask
	.section	.bss,bss
	.type	_leds_status_array,@object
	.size	_leds_status_array, 9
_leds_status_array:
	.skip	9
	.type	_leds_matrix,@object
	.size	_leds_matrix, 9
_leds_matrix:
	.skip	9
	.section	.nbss,bss,near
	.type	_blink_toggle.4232,@object
	.size	_blink_toggle.4232, 1
_blink_toggle.4232:
	.skip	1
	.type	_blink_counter.4231,@object
	.size	_blink_counter.4231, 1
_blink_counter.4231:
	.skip	1
	.section	.const,psv,page
	.align	2
	.type	_led_columns_array,@object
	.size	_led_columns_array, 12
_led_columns_array:
	.word	_LATC
	.word	8
	.word	_LATC
	.word	16
	.word	_LATC
	.word	32
	.align	2
	.type	_led_rows_array,@object
	.size	_led_rows_array, 12
_led_rows_array:
	.word	_LATB
	.word	16
	.word	_LATA
	.word	16
	.word	_LATA
	.word	512
	.section	.nbss,bss,near
	.type	_row_counter.4220,@object
	.size	_row_counter.4220, 1
_row_counter.4220:
	.skip	1
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
	.byte	0x4
	.4byte	.LCFI0-.LFB3
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x4
	.4byte	.LCFI1-.LFB4
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x4
	.4byte	.LCFI2-.LFB5
	.byte	0x13
	.sleb128 -3
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
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.align	4
.LEFDE14:
	.section	.text,code
.Letext0:
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 4 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.section	.debug_info,info
	.4byte	0x88a
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"src/leds.c"
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
	.4byte	0xe9
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x3
	.byte	0x31
	.4byte	0x10a
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
	.asciz	"tagTRISABITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x6bf
	.4byte	0x21e
	.uleb128 0x5
	.asciz	"TRISA0"
	.byte	0x4
	.2byte	0x6c0
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA1"
	.byte	0x4
	.2byte	0x6c1
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA2"
	.byte	0x4
	.2byte	0x6c2
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA3"
	.byte	0x4
	.2byte	0x6c3
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA4"
	.byte	0x4
	.2byte	0x6c4
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA7"
	.byte	0x4
	.2byte	0x6c6
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA8"
	.byte	0x4
	.2byte	0x6c7
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA9"
	.byte	0x4
	.2byte	0x6c8
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"TRISA10"
	.byte	0x4
	.2byte	0x6c9
	.4byte	0xfa
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"TRISABITS"
	.byte	0x4
	.2byte	0x6ca
	.4byte	0x149
	.uleb128 0x4
	.asciz	"tagTRISBBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x6ff
	.4byte	0x39d
	.uleb128 0x5
	.asciz	"TRISB0"
	.byte	0x4
	.2byte	0x700
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0x230
	.uleb128 0x4
	.asciz	"tagTRISCBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x757
	.4byte	0x498
	.uleb128 0x5
	.asciz	"TRISC0"
	.byte	0x4
	.2byte	0x758
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0xfa
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
	.4byte	0x3af
	.uleb128 0x7
	.byte	0x4
	.byte	0x2
	.byte	0x2f
	.4byte	0x4d1
	.uleb128 0x8
	.asciz	"port"
	.byte	0x2
	.byte	0x31
	.4byte	0x4d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.asciz	"mask"
	.byte	0x2
	.byte	0x32
	.4byte	0x4dc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x9
	.4byte	0x4d6
	.uleb128 0xa
	.byte	0x2
	.4byte	0xfa
	.uleb128 0x9
	.4byte	0xfa
	.uleb128 0x3
	.asciz	"led_row_t"
	.byte	0x2
	.byte	0x33
	.4byte	0x4aa
	.uleb128 0x7
	.byte	0x4
	.byte	0x2
	.byte	0x35
	.4byte	0x519
	.uleb128 0x8
	.asciz	"port"
	.byte	0x2
	.byte	0x37
	.4byte	0x4d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.asciz	"mask"
	.byte	0x2
	.byte	0x38
	.4byte	0x4dc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x3
	.asciz	"led_column_t"
	.byte	0x2
	.byte	0x39
	.4byte	0x4f2
	.uleb128 0xb
	.asciz	"INTERRUPT_GlobalDisable"
	.byte	0x1
	.byte	0x87
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0xb
	.asciz	"INTERRUPT_GlobalEnable"
	.byte	0x1
	.byte	0x68
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedsInit"
	.byte	0x2
	.byte	0x50
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x5a7
	.uleb128 0xd
	.asciz	"i"
	.byte	0x2
	.byte	0x52
	.4byte	0xda
	.uleb128 0xd
	.asciz	"j"
	.byte	0x2
	.byte	0x52
	.4byte	0xda
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedOn"
	.byte	0x2
	.byte	0x66
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x5ce
	.uleb128 0xe
	.4byte	.LASF0
	.byte	0x2
	.byte	0x66
	.4byte	0xda
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedOff"
	.byte	0x2
	.byte	0x70
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x5f6
	.uleb128 0xe
	.4byte	.LASF0
	.byte	0x2
	.byte	0x70
	.4byte	0xda
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedBlink"
	.byte	0x2
	.byte	0x7a
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x620
	.uleb128 0xe
	.4byte	.LASF0
	.byte	0x2
	.byte	0x7a
	.4byte	0xda
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedsMatrixTask"
	.byte	0x2
	.byte	0x85
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x672
	.uleb128 0xf
	.asciz	"row_counter"
	.byte	0x2
	.byte	0x87
	.4byte	0xda
	.byte	0x5
	.byte	0x3
	.4byte	_row_counter.4220
	.uleb128 0xd
	.asciz	"column_counter"
	.byte	0x2
	.byte	0x88
	.4byte	0xda
	.byte	0x0
	.uleb128 0xc
	.byte	0x1
	.asciz	"LedsBlinkTask"
	.byte	0x2
	.byte	0xa5
	.byte	0x1
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0x6f5
	.uleb128 0xf
	.asciz	"blink_counter"
	.byte	0x2
	.byte	0xa7
	.4byte	0xda
	.byte	0x5
	.byte	0x3
	.4byte	_blink_counter.4231
	.uleb128 0xf
	.asciz	"blink_toggle"
	.byte	0x2
	.byte	0xa8
	.4byte	0x6f5
	.byte	0x5
	.byte	0x3
	.4byte	_blink_toggle.4232
	.uleb128 0xd
	.asciz	"i"
	.byte	0x2
	.byte	0xa9
	.4byte	0xda
	.uleb128 0xd
	.asciz	"j"
	.byte	0x2
	.byte	0xa9
	.4byte	0xda
	.uleb128 0x10
	.4byte	.LBB2
	.4byte	.LBE2
	.uleb128 0xf
	.asciz	"status"
	.byte	0x2
	.byte	0xad
	.4byte	0xda
	.byte	0x1
	.byte	0x56
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x11
	.4byte	.LASF1
	.byte	0x4
	.2byte	0x6cb
	.4byte	0x70c
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.4byte	0x21e
	.uleb128 0x13
	.asciz	"LATA"
	.byte	0x4
	.2byte	0x6de
	.4byte	0x720
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.4byte	0xfa
	.uleb128 0x11
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x711
	.4byte	0x733
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.4byte	0x39d
	.uleb128 0x13
	.asciz	"LATB"
	.byte	0x4
	.2byte	0x72a
	.4byte	0x720
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x763
	.4byte	0x755
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.4byte	0x498
	.uleb128 0x13
	.asciz	"LATC"
	.byte	0x4
	.2byte	0x776
	.4byte	0x720
	.byte	0x1
	.byte	0x1
	.uleb128 0x14
	.4byte	0x4e1
	.4byte	0x779
	.uleb128 0x15
	.4byte	0x10a
	.byte	0x2
	.byte	0x0
	.uleb128 0xf
	.asciz	"led_rows_array"
	.byte	0x2
	.byte	0x3c
	.4byte	0x795
	.byte	0x5
	.byte	0x3
	.4byte	_led_rows_array
	.uleb128 0x9
	.4byte	0x769
	.uleb128 0x14
	.4byte	0x519
	.4byte	0x7aa
	.uleb128 0x15
	.4byte	0x10a
	.byte	0x2
	.byte	0x0
	.uleb128 0xf
	.asciz	"led_columns_array"
	.byte	0x2
	.byte	0x42
	.4byte	0x7c9
	.byte	0x5
	.byte	0x3
	.4byte	_led_columns_array
	.uleb128 0x9
	.4byte	0x79a
	.uleb128 0x14
	.4byte	0xda
	.4byte	0x7de
	.uleb128 0x15
	.4byte	0x10a
	.byte	0x8
	.byte	0x0
	.uleb128 0xf
	.asciz	"leds_status_array"
	.byte	0x2
	.byte	0x4d
	.4byte	0x7fd
	.byte	0x5
	.byte	0x3
	.4byte	_leds_status_array
	.uleb128 0x12
	.4byte	0x7ce
	.uleb128 0x14
	.4byte	0x6f5
	.4byte	0x818
	.uleb128 0x15
	.4byte	0x10a
	.byte	0x2
	.uleb128 0x15
	.4byte	0x10a
	.byte	0x2
	.byte	0x0
	.uleb128 0xf
	.asciz	"leds_matrix"
	.byte	0x2
	.byte	0x4e
	.4byte	0x831
	.byte	0x5
	.byte	0x3
	.4byte	_leds_matrix
	.uleb128 0x12
	.4byte	0x802
	.uleb128 0x11
	.4byte	.LASF1
	.byte	0x4
	.2byte	0x6cb
	.4byte	0x70c
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.asciz	"LATA"
	.byte	0x4
	.2byte	0x6de
	.4byte	0x720
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x711
	.4byte	0x733
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.asciz	"LATB"
	.byte	0x4
	.2byte	0x72a
	.4byte	0x720
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x763
	.4byte	0x755
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.asciz	"LATC"
	.byte	0x4
	.2byte	0x776
	.4byte	0x720
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
	.uleb128 0x13
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
	.uleb128 0x8
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
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
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
	.uleb128 0xe
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
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
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
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
	.uleb128 0x14
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
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
	.4byte	0x62
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x88e
	.4byte	0x578
	.asciz	"LedsInit"
	.4byte	0x5a7
	.asciz	"LedOn"
	.4byte	0x5ce
	.asciz	"LedOff"
	.4byte	0x5f6
	.asciz	"LedBlink"
	.4byte	0x620
	.asciz	"LedsMatrixTask"
	.4byte	0x672
	.asciz	"LedsBlinkTask"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0xa3
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x88e
	.4byte	0xda
	.asciz	"uint8_t"
	.4byte	0xfa
	.asciz	"uint16_t"
	.4byte	0x149
	.asciz	"tagTRISABITS"
	.4byte	0x21e
	.asciz	"TRISABITS"
	.4byte	0x230
	.asciz	"tagTRISBBITS"
	.4byte	0x39d
	.asciz	"TRISBBITS"
	.4byte	0x3af
	.asciz	"tagTRISCBITS"
	.4byte	0x498
	.asciz	"TRISCBITS"
	.4byte	0x4e1
	.asciz	"led_row_t"
	.4byte	0x519
	.asciz	"led_column_t"
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
.LASF3:
	.asciz	"TRISCbits"
.LASF0:
	.asciz	"led_id"
.LASF1:
	.asciz	"TRISAbits"
.LASF2:
	.asciz	"TRISBbits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
