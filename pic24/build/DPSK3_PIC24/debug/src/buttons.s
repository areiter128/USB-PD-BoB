	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\buttons.c"
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
	.type	__ButtonRead,@function
__ButtonRead:
.LFB3:
	.file 1 "src/buttons.c"
	.loc 1 69 0
	.set ___PA___,1
	.loc 1 70 0
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L3
	sub.b	w0,#1,[w15]
	.set ___BP___,71
	bra	nz,.L6
	bra	.L8
.L3:
	.loc 1 72 0
	mov	_PORTAbits,w0
	lsr	w0,#2,w0
	bra	.L7
.L8:
	.loc 1 73 0
	mov	_PORTAbits,w0
	lsr	w0,#3,w0
.L7:
	and.b	w0,#1,w0
	return	
.L6:
	.loc 1 74 0
	retlw	#1,w0
.LFE3:
	.size	__ButtonRead, .-__ButtonRead
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
	.global	_ButtonsInit	; export
	.type	_ButtonsInit,@function
_ButtonsInit:
.LFB2:
	.loc 1 54 0
	.set ___PA___,1
	.loc 1 55 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 56 0
	clr.b	w0
	mov	#_buttonArray,w1
	mov.b	w0,[w1]
	.loc 1 57 0
	inc	w1,w1
	mov.b	w0,[w1]
	.loc 1 58 0
	inc	w1,w1
	mov.b	w0,[w1]
	.loc 1 59 0
	mov.b	#1,w1
	mov	#_buttonArray+3,w2
	mov.b	w1,[w2]
	.loc 1 61 0
	inc	w2,w2
	mov.b	w0,[w2]
	.loc 1 62 0
	inc	w2,w2
	mov.b	w0,[w2]
	.loc 1 63 0
	inc	w2,w2
	mov.b	w0,[w2]
	.loc 1 64 0
	inc	w2,w0
	mov.b	w1,[w0]
	.loc 1 65 0
	bra	_INTERRUPT_GlobalEnable
	.loc 1 66 0
	.set ___PA___,0
.LFE2:
	.size	_ButtonsInit, .-_ButtonsInit
	.align	2
	.global	_ButtonEventBuck	; export
	.type	_ButtonEventBuck,@function
_ButtonEventBuck:
.LFB4:
	.loc 1 79 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI0:
	.loc 1 81 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 82 0
	mov	#_buttonArray+2,w1
	mov.b	[w1],w8
	.loc 1 83 0
	clr.b	[w1]
	.loc 1 84 0
	rcall	_INTERRUPT_GlobalEnable
	.loc 1 86 0
	mov.b	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE4:
	.size	_ButtonEventBuck, .-_ButtonEventBuck
	.align	2
	.global	_ButtonEventBoost	; export
	.type	_ButtonEventBoost,@function
_ButtonEventBoost:
.LFB5:
	.loc 1 89 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI1:
	.loc 1 91 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 92 0
	mov	#_buttonArray+6,w1
	mov.b	[w1],w8
	.loc 1 93 0
	clr.b	[w1]
	.loc 1 94 0
	rcall	_INTERRUPT_GlobalEnable
	.loc 1 96 0
	mov.b	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE5:
	.size	_ButtonEventBoost, .-_ButtonEventBoost
	.align	2
	.global	_ButtonsTask	; export
	.type	_ButtonsTask,@function
_ButtonsTask:
.LFB6:
	.loc 1 101 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI2:
	.loc 1 103 0
	mov	#_scan.4210,w8
	mov.b	[w8],w8
	mov.b	w8,w0
	rcall	__ButtonRead
	.loc 1 104 0
	ze	w8,w8
	sl	w8,#2,w8
	inc2	w8,w2
	mov	#_buttonArray+1,w1
	mov.b	[w1+w2],w3
	dec	w1,w2
	.loc 1 106 0
	sub.b	w0,w3,[w15]
	.set ___BP___,72
	bra	nz,.L15
	.loc 1 108 0
	add	w2,w8,w2
	clr.b	[w2]
	.loc 1 109 0
	cp0.b	w0
	.set ___BP___,50
	bra	nz,.L16
	mov.b	[w1+w8],w3
	mov.b	#-107,w0
	sub.b	w3,w0,[w15]
	.set ___BP___,50
	bra	gtu,.L16
	.loc 1 111 0
	mov.b	[w1+w8],w3
	add	w1,w8,w0
	inc.b	w3,[w0]
	.loc 1 112 0
	mov.b	[w1+w8],w1
	mov.b	#-106,w0
	sub.b	w1,w0,[w15]
	.set ___BP___,72
	bra	nz,.L16
	.loc 1 113 0
	mov.b	#2,w0
	mov.b	w0,[w2+2]
	bra	.L16
.L15:
	.loc 1 118 0
	mov.b	[w2+w8],w4
	add	w2,w8,w3
	inc.b	w4,[w3]
	.loc 1 119 0
	mov.b	[w2+w8],w2
	sub.b	w2,#3,[w15]
	.set ___BP___,72
	bra	nz,.L16
	.loc 1 121 0
	add	w1,w8,w2
	mov.b	w0,[w2+2]
	.loc 1 122 0
	clr.b	[w3]
	.loc 1 123 0
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L17
	mov.b	[w1+w8],w1
	mov.b	#-107,w0
	sub.b	w1,w0,[w15]
	.set ___BP___,50
	bra	gtu,.L17
	.loc 1 125 0
	mov.b	#1,w0
	mov.b	w0,[w3+2]
.L17:
	.loc 1 127 0
	mov.b	_scan.4210,WREG
	ze	w0,w0
	sl	w0,#2,w0
	mov	#_buttonArray+1,w1
	add	w1,w0,w0
	clr.b	[w0]
.L16:
	.loc 1 130 0
	inc.b	_scan.4210,WREG
	mov.b	WREG,_scan.4210
	sub.b	w0,#1,[w15]
	.set ___BP___,19
	bra	leu,.L14
	clr.b	_scan.4210
.L14:
	.loc 1 131 0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE6:
	.size	_ButtonsTask, .-_ButtonsTask
	.section	.bss,bss
	.type	_buttonArray,@object
	.size	_buttonArray, 8
_buttonArray:
	.skip	8
	.section	.nbss,bss,near
	.type	_scan.4210,@object
	.size	_scan.4210, 1
_scan.4210:
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
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.byte	0x4
	.4byte	.LCFI0-.LFB4
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
	.4byte	.LCFI1-.LFB5
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
	.byte	0x4
	.4byte	.LCFI2-.LFB6
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE12:
	.section	.text,code
.Letext0:
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 4 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.section	.debug_info,info
	.4byte	0x42a
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"src/buttons.c"
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
	.4byte	0xec
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x3
	.byte	0x31
	.4byte	0x10d
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
	.asciz	"tagPORTABITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x6cf
	.4byte	0x206
	.uleb128 0x5
	.asciz	"RA0"
	.byte	0x4
	.2byte	0x6d0
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA1"
	.byte	0x4
	.2byte	0x6d1
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA2"
	.byte	0x4
	.2byte	0x6d2
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA3"
	.byte	0x4
	.2byte	0x6d3
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA4"
	.byte	0x4
	.2byte	0x6d4
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA7"
	.byte	0x4
	.2byte	0x6d6
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA8"
	.byte	0x4
	.2byte	0x6d7
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA9"
	.byte	0x4
	.2byte	0x6d8
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"RA10"
	.byte	0x4
	.2byte	0x6d9
	.4byte	0xfd
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"PORTABITS"
	.byte	0x4
	.2byte	0x6da
	.4byte	0x14c
	.uleb128 0x7
	.byte	0x4
	.byte	0x1
	.byte	0x2b
	.4byte	0x265
	.uleb128 0x8
	.asciz	"debouncer"
	.byte	0x1
	.byte	0x2d
	.4byte	0xdd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.asciz	"timer"
	.byte	0x1
	.byte	0x2e
	.4byte	0xdd
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x8
	.asciz	"event"
	.byte	0x1
	.byte	0x2f
	.4byte	0xdd
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x8
	.asciz	"state"
	.byte	0x1
	.byte	0x30
	.4byte	0x265
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.byte	0x0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x3
	.asciz	"button_data_t"
	.byte	0x1
	.byte	0x31
	.4byte	0x218
	.uleb128 0x9
	.asciz	"_ButtonRead"
	.byte	0x1
	.byte	0x44
	.byte	0x1
	.4byte	0x265
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x2b2
	.uleb128 0xa
	.asciz	"id"
	.byte	0x1
	.byte	0x44
	.4byte	0xdd
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0xb
	.asciz	"INTERRUPT_GlobalDisable"
	.byte	0x2
	.byte	0x87
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0xb
	.asciz	"INTERRUPT_GlobalEnable"
	.byte	0x2
	.byte	0x68
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0xc
	.byte	0x1
	.asciz	"ButtonsInit"
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.uleb128 0xd
	.byte	0x1
	.asciz	"ButtonEventBuck"
	.byte	0x1
	.byte	0x4e
	.byte	0x1
	.4byte	0xdd
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x34d
	.uleb128 0xe
	.asciz	"ret"
	.byte	0x1
	.byte	0x50
	.4byte	0xdd
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xd
	.byte	0x1
	.asciz	"ButtonEventBoost"
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.4byte	0xdd
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0x383
	.uleb128 0xe
	.asciz	"ret"
	.byte	0x1
	.byte	0x5a
	.4byte	0xdd
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0xf
	.byte	0x1
	.asciz	"ButtonsTask"
	.byte	0x1
	.byte	0x64
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0x3de
	.uleb128 0xe
	.asciz	"scan"
	.byte	0x1
	.byte	0x66
	.4byte	0xdd
	.byte	0x5
	.byte	0x3
	.4byte	_scan.4210
	.uleb128 0xe
	.asciz	"input_state"
	.byte	0x1
	.byte	0x67
	.4byte	0x265
	.byte	0x1
	.byte	0x50
	.uleb128 0xe
	.asciz	"last_state"
	.byte	0x1
	.byte	0x68
	.4byte	0x265
	.byte	0x1
	.byte	0x53
	.byte	0x0
	.uleb128 0x10
	.4byte	.LASF0
	.byte	0x4
	.2byte	0x6db
	.4byte	0x3ec
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	0x206
	.uleb128 0x12
	.4byte	0x26e
	.4byte	0x401
	.uleb128 0x13
	.4byte	0x10d
	.byte	0x1
	.byte	0x0
	.uleb128 0xe
	.asciz	"buttonArray"
	.byte	0x1
	.byte	0x33
	.4byte	0x41a
	.byte	0x5
	.byte	0x3
	.4byte	_buttonArray
	.uleb128 0x11
	.4byte	0x3f1
	.uleb128 0x10
	.4byte	.LASF0
	.byte	0x4
	.2byte	0x6db
	.4byte	0x3ec
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
	.uleb128 0xa
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
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
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
	.4byte	0x57
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x42e
	.4byte	0x2fd
	.asciz	"ButtonsInit"
	.4byte	0x318
	.asciz	"ButtonEventBuck"
	.4byte	0x34d
	.asciz	"ButtonEventBoost"
	.4byte	0x383
	.asciz	"ButtonsTask"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x58
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x42e
	.4byte	0xdd
	.asciz	"uint8_t"
	.4byte	0xfd
	.asciz	"uint16_t"
	.4byte	0x14c
	.asciz	"tagPORTABITS"
	.4byte	0x206
	.asciz	"PORTABITS"
	.4byte	0x26e
	.asciz	"button_data_t"
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
	.asciz	"PORTAbits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
