	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\temperature.c"
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
	.global	_TemperatureCheck	; export
	.type	_TemperatureCheck,@function
_TemperatureCheck:
.LFB0:
	.file 1 "src/temperature.c"
	.loc 1 32 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI0:
	mov	w0,w8
	.loc 1 36 0
	rcall	_ADC1_ReadAvg
	clr	w1
	rcall	___floatunsisf
	mov	#13107,w2
	mov	#16467,w3
	rcall	___mulsf3
	mov	#0,w2
	mov	#14976,w3
	rcall	___mulsf3
	mov	#0,w2
	mov	#16128,w3
	rcall	___subsf3
	mov	#55050,w2
	mov	#15395,w3
	rcall	___divsf3
	rcall	___fixunssfsi
	.loc 1 38 0
	cp0.b	_stateThermalShutDown.4359
	.set ___BP___,50
	bra	z,.L2
	.loc 1 35 0
	clr	w1
	.loc 1 40 0
	mov.b	#69,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	gtu,.L3
	.loc 1 42 0
	clr.b	_stateThermalShutDown.4359
	bra	.L9
.L2:
	.loc 1 49 0
	mov.b	#79,w1
	sub.b	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L4
	.loc 1 51 0
	mov.b	#1,w1
	mov	#_stateThermalShutDown.4359,w2
	mov.b	w1,[w2]
	.loc 1 52 0
	mov	#1,w1
	bra	.L3
.L4:
	.loc 1 56 0
	cp0.b	_stateThermalWarning.4360
	.set ___BP___,50
	bra	z,.L5
	.loc 1 35 0
	clr	w1
	.loc 1 58 0
	mov.b	#54,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	gtu,.L3
	.loc 1 60 0
	clr.b	_stateThermalWarning.4360
	.loc 1 61 0
	mov	#2,w1
	bra	.L3
.L5:
	.loc 1 35 0
	clr	w1
	.loc 1 66 0
	mov.b	#55,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	leu,.L3
.L9:
	.loc 1 68 0
	mov.b	#1,w1
	mov	#_stateThermalWarning.4360,w2
	mov.b	w1,[w2]
	.loc 1 69 0
	mov	#3,w1
.L3:
	.loc 1 75 0
	mov.b	w0,[w8]
	.loc 1 77 0
	mov	w1,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE0:
	.size	_TemperatureCheck, .-_TemperatureCheck
	.section	.nbss,bss,near
	.type	_stateThermalWarning.4360,@object
	.size	_stateThermalWarning.4360, 1
_stateThermalWarning.4360:
	.skip	1
	.type	_stateThermalShutDown.4359,@object
	.size	_stateThermalShutDown.4359, 1
_stateThermalShutDown.4359:
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE0:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 3 "h/temperature.h"
	.section	.debug_info,info
	.4byte	0x261
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"src/temperature.c"
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
	.4byte	0xf0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
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
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"short unsigned int"
	.uleb128 0x4
	.byte	0x2
	.byte	0x3
	.byte	0x38
	.4byte	0x19c
	.uleb128 0x5
	.asciz	"THERM_NO_CHANGE"
	.sleb128 0
	.uleb128 0x5
	.asciz	"THERM_ALERT"
	.sleb128 1
	.uleb128 0x5
	.asciz	"THERM_SAFE"
	.sleb128 2
	.uleb128 0x5
	.asciz	"THERM_WARNING"
	.sleb128 3
	.byte	0x0
	.uleb128 0x3
	.asciz	"therm_event_t"
	.byte	0x3
	.byte	0x3d
	.4byte	0x156
	.uleb128 0x6
	.byte	0x1
	.asciz	"TemperatureCheck"
	.byte	0x1
	.byte	0x1f
	.byte	0x1
	.4byte	0x19c
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.4byte	0x255
	.uleb128 0x7
	.asciz	"pTemperature"
	.byte	0x1
	.byte	0x1f
	.4byte	0x255
	.byte	0x1
	.byte	0x58
	.uleb128 0x8
	.asciz	"stateThermalShutDown"
	.byte	0x1
	.byte	0x21
	.4byte	0x25b
	.byte	0x5
	.byte	0x3
	.4byte	_stateThermalShutDown.4359
	.uleb128 0x8
	.asciz	"stateThermalWarning"
	.byte	0x1
	.byte	0x22
	.4byte	0x25b
	.byte	0x5
	.byte	0x3
	.4byte	_stateThermalWarning.4360
	.uleb128 0x8
	.asciz	"ret"
	.byte	0x1
	.byte	0x23
	.4byte	0x19c
	.byte	0x1
	.byte	0x51
	.uleb128 0x8
	.asciz	"temperature"
	.byte	0x1
	.byte	0x24
	.4byte	0xe1
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x9
	.byte	0x2
	.4byte	0xe1
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
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
	.uleb128 0x5
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x23
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x265
	.4byte	0x1b1
	.asciz	"TemperatureCheck"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x265
	.4byte	0xe1
	.asciz	"uint8_t"
	.4byte	0x19c
	.asciz	"therm_event_t"
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
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
