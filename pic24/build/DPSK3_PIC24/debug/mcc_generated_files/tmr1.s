	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\tmr1.c"
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
	.global	_TMR1_Initialize	; export
	.type	_TMR1_Initialize,@function
_TMR1_Initialize:
.LFB0:
	.file 1 "mcc_generated_files/tmr1.c"
	.loc 1 88 0
	.set ___PA___,1
	.loc 1 90 0
	clr	_TMR1
	.loc 1 92 0
	mov	#2000,w0
	mov	w0,_PR1
	.loc 1 94 0
	mov	#-32752,w0
	mov	w0,_T1CON
	.loc 1 97 0
	bclr.b	_IFS0bits,#3
	.loc 1 98 0
	bset.b	_IEC0bits,#3
	.loc 1 100 0
	clr.b	_tmr1_obj
	.loc 1 102 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_TMR1_Initialize, .-_TMR1_Initialize
	.align	2
	.global	_TMR1_Period16BitSet	; export
	.type	_TMR1_Period16BitSet,@function
_TMR1_Period16BitSet:
.LFB2:
	.loc 1 125 0
	.set ___PA___,1
	.loc 1 127 0
	mov	w0,_PR1
	.loc 1 129 0
	clr.b	_tmr1_obj
	.loc 1 130 0
	return	
	.set ___PA___,0
.LFE2:
	.size	_TMR1_Period16BitSet, .-_TMR1_Period16BitSet
	.align	2
	.global	_TMR1_Period16BitGet	; export
	.type	_TMR1_Period16BitGet,@function
_TMR1_Period16BitGet:
.LFB3:
	.loc 1 133 0
	.set ___PA___,1
	.loc 1 134 0
	mov	_PR1,w0
	.loc 1 135 0
	return	
	.set ___PA___,0
.LFE3:
	.size	_TMR1_Period16BitGet, .-_TMR1_Period16BitGet
	.align	2
	.global	_TMR1_Counter16BitSet	; export
	.type	_TMR1_Counter16BitSet,@function
_TMR1_Counter16BitSet:
.LFB4:
	.loc 1 138 0
	.set ___PA___,1
	.loc 1 140 0
	mov	w0,_TMR1
	.loc 1 142 0
	clr.b	_tmr1_obj
	.loc 1 143 0
	return	
	.set ___PA___,0
.LFE4:
	.size	_TMR1_Counter16BitSet, .-_TMR1_Counter16BitSet
	.align	2
	.global	_TMR1_Counter16BitGet	; export
	.type	_TMR1_Counter16BitGet,@function
_TMR1_Counter16BitGet:
.LFB5:
	.loc 1 146 0
	.set ___PA___,1
	.loc 1 147 0
	mov	_TMR1,w0
	.loc 1 148 0
	return	
	.set ___PA___,0
.LFE5:
	.size	_TMR1_Counter16BitGet, .-_TMR1_Counter16BitGet
	.align	2
	.weak	_TMR1_CallBack
	.type	_TMR1_CallBack,@function
_TMR1_CallBack:
.LFB6:
	.loc 1 152 0
	.set ___PA___,1
	.loc 1 154 0
	return	
	.set ___PA___,0
.LFE6:
	.size	_TMR1_CallBack, .-_TMR1_CallBack
	.section	.isr.text,code,keep
	.align	2
	.global	__T1Interrupt	; export
	.type	__T1Interrupt,@function
__T1Interrupt:
	.section	.isr.text,code,keep
.LFB1:
	.section	.isr.text,code,keep
	.loc 1 107 0
	.set ___PA___,1
	push	_RCOUNT
.LCFI0:
	mov.d	w0,[w15++]
.LCFI1:
	mov.d	w2,[w15++]
.LCFI2:
	mov.d	w4,[w15++]
.LCFI3:
	mov.d	w6,[w15++]
.LCFI4:
	.section	.isr.text,code,keep
	.loc 1 114 0
	rcall	_TMR1_CallBack
	.section	.isr.text,code,keep
	.loc 1 118 0
	inc	_tmr1_obj+2
	.section	.isr.text,code,keep
	.loc 1 119 0
	mov.b	#1,w0
	mov.b	WREG,_tmr1_obj
	.section	.isr.text,code,keep
	.loc 1 120 0
	bclr.b	_IFS0bits,#3
	.section	.isr.text,code,keep
	.loc 1 121 0
	mov.d	[--w15],w6
	mov.d	[--w15],w4
	mov.d	[--w15],w2
	mov.d	[--w15],w0
	pop	_RCOUNT
	retfie	
	.set ___PA___,0
.LFE1:
	.size	__T1Interrupt, .-__T1Interrupt
	.section	.text,code
	.align	2
	.global	_TMR1_Start	; export
	.type	_TMR1_Start,@function
_TMR1_Start:
.LFB7:
	.loc 1 157 0
	.set ___PA___,1
	.loc 1 159 0
	clr.b	_tmr1_obj
	.loc 1 162 0
	bset.b	_IEC0bits,#3
	.loc 1 165 0
	bset.b	_T1CONbits+1,#7
	.loc 1 166 0
	return	
	.set ___PA___,0
.LFE7:
	.size	_TMR1_Start, .-_TMR1_Start
	.align	2
	.global	_TMR1_Stop	; export
	.type	_TMR1_Stop,@function
_TMR1_Stop:
.LFB8:
	.loc 1 169 0
	.set ___PA___,1
	.loc 1 171 0
	bclr.b	_T1CONbits+1,#7
	.loc 1 174 0
	bclr.b	_IEC0bits,#3
	.loc 1 175 0
	return	
	.set ___PA___,0
.LFE8:
	.size	_TMR1_Stop, .-_TMR1_Stop
	.align	2
	.global	_TMR1_GetElapsedThenClear	; export
	.type	_TMR1_GetElapsedThenClear,@function
_TMR1_GetElapsedThenClear:
.LFB9:
	.loc 1 178 0
	.set ___PA___,1
	.loc 1 181 0
	mov.b	_tmr1_obj,WREG
	.loc 1 183 0
	.set ___BP___,39
	bra	z,.L11
	.loc 1 185 0
	clr.b	_tmr1_obj
.L11:
	.loc 1 188 0
	return	
.LFE9:
	.size	_TMR1_GetElapsedThenClear, .-_TMR1_GetElapsedThenClear
	.align	2
	.global	_TMR1_SoftwareCounterGet	; export
	.type	_TMR1_SoftwareCounterGet,@function
_TMR1_SoftwareCounterGet:
.LFB10:
	.loc 1 191 0
	.set ___PA___,1
	.loc 1 193 0
	mov	_tmr1_obj+2,w0
	return	
	.set ___PA___,0
.LFE10:
	.size	_TMR1_SoftwareCounterGet, .-_TMR1_SoftwareCounterGet
	.align	2
	.global	_TMR1_SoftwareCounterClear	; export
	.type	_TMR1_SoftwareCounterClear,@function
_TMR1_SoftwareCounterClear:
.LFB11:
	.loc 1 196 0
	.set ___PA___,1
	.loc 1 197 0
	clr	_tmr1_obj+2
	.loc 1 198 0
	return	
	.set ___PA___,0
.LFE11:
	.size	_TMR1_SoftwareCounterClear, .-_TMR1_SoftwareCounterClear
	.section	.nbss,bss,near
	.align	2
	.type	_tmr1_obj,@object
	.size	_tmr1_obj, 4
_tmr1_obj:
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
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
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI1-.LFB1
	.byte	0x13
	.sleb128 -5
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0x13
	.sleb128 -7
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0x13
	.sleb128 -9
	.byte	0x4
	.4byte	.LCFI4-.LCFI3
	.byte	0x13
	.sleb128 -11
	.byte	0x86
	.uleb128 0x9
	.byte	0x84
	.uleb128 0x7
	.byte	0x82
	.uleb128 0x5
	.byte	0x80
	.uleb128 0x3
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
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.align	4
.LEFDE20:
.LSFDE22:
	.4byte	.LEFDE22-.LASFDE22
.LASFDE22:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	4
.LEFDE22:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.section	.debug_info,info
	.4byte	0x79b
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"mcc_generated_files/tmr1.c"
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
	.asciz	"tagIFS0BITS"
	.byte	0x2
	.byte	0x2
	.byte	0xf5
	.4byte	0x25c
	.uleb128 0x5
	.asciz	"INT0IF"
	.byte	0x2
	.byte	0xf6
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"IC1IF"
	.byte	0x2
	.byte	0xf7
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"OC1IF"
	.byte	0x2
	.byte	0xf8
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T1IF"
	.byte	0x2
	.byte	0xf9
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"IC2IF"
	.byte	0x2
	.byte	0xfb
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"OC2IF"
	.byte	0x2
	.byte	0xfc
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T2IF"
	.byte	0x2
	.byte	0xfd
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T3IF"
	.byte	0x2
	.byte	0xfe
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"SPF1IF"
	.byte	0x2
	.byte	0xff
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPI1IF"
	.byte	0x2
	.2byte	0x100
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1RXIF"
	.byte	0x2
	.2byte	0x101
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1TXIF"
	.byte	0x2
	.2byte	0x102
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"AD1IF"
	.byte	0x2
	.2byte	0x103
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"IFS0BITS"
	.byte	0x2
	.2byte	0x104
	.4byte	0x14a
	.uleb128 0x8
	.asciz	"tagIEC0BITS"
	.byte	0x2
	.byte	0x2
	.2byte	0x143
	.4byte	0x389
	.uleb128 0x6
	.asciz	"INT0IE"
	.byte	0x2
	.2byte	0x144
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"IC1IE"
	.byte	0x2
	.2byte	0x145
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"OC1IE"
	.byte	0x2
	.2byte	0x146
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T1IE"
	.byte	0x2
	.2byte	0x147
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"IC2IE"
	.byte	0x2
	.2byte	0x149
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"OC2IE"
	.byte	0x2
	.2byte	0x14a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T2IE"
	.byte	0x2
	.2byte	0x14b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T3IE"
	.byte	0x2
	.2byte	0x14c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPF1IE"
	.byte	0x2
	.2byte	0x14d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPI1IE"
	.byte	0x2
	.2byte	0x14e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1RXIE"
	.byte	0x2
	.2byte	0x14f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1TXIE"
	.byte	0x2
	.2byte	0x150
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"AD1IE"
	.byte	0x2
	.2byte	0x151
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"IEC0BITS"
	.byte	0x2
	.2byte	0x152
	.4byte	0x26d
	.uleb128 0x9
	.byte	0x2
	.byte	0x2
	.2byte	0x34f
	.4byte	0x418
	.uleb128 0x6
	.asciz	"TCS"
	.byte	0x2
	.2byte	0x351
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TSYNC"
	.byte	0x2
	.2byte	0x352
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TCKPS"
	.byte	0x2
	.2byte	0x354
	.4byte	0xfb
	.byte	0x2
	.byte	0x2
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TGATE"
	.byte	0x2
	.2byte	0x355
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TSIDL"
	.byte	0x2
	.2byte	0x357
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TON"
	.byte	0x2
	.2byte	0x359
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.byte	0x2
	.byte	0x2
	.2byte	0x35b
	.4byte	0x44c
	.uleb128 0x6
	.asciz	"TCKPS0"
	.byte	0x2
	.2byte	0x35d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TCKPS1"
	.byte	0x2
	.2byte	0x35e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.byte	0x2
	.2byte	0x34e
	.4byte	0x460
	.uleb128 0xb
	.4byte	0x39a
	.uleb128 0xb
	.4byte	0x418
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagT1CONBITS"
	.byte	0x2
	.byte	0x2
	.2byte	0x34d
	.4byte	0x47f
	.uleb128 0xc
	.4byte	0x44c
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"T1CONBITS"
	.byte	0x2
	.2byte	0x361
	.4byte	0x460
	.uleb128 0x4
	.asciz	"_TMR_OBJ_STRUCT"
	.byte	0x4
	.byte	0x1
	.byte	0x46
	.4byte	0x4d1
	.uleb128 0xd
	.asciz	"timerElapsed"
	.byte	0x1
	.byte	0x49
	.4byte	0x4d1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xd
	.asciz	"count"
	.byte	0x1
	.byte	0x4c
	.4byte	0xc6
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x3
	.asciz	"TMR_OBJ"
	.byte	0x1
	.byte	0x4e
	.4byte	0x491
	.uleb128 0xe
	.byte	0x1
	.asciz	"TMR1_Initialize"
	.byte	0x1
	.byte	0x57
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0xf
	.byte	0x1
	.asciz	"TMR1_Period16BitSet"
	.byte	0x1
	.byte	0x7c
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0x53f
	.uleb128 0x10
	.asciz	"value"
	.byte	0x1
	.byte	0x7c
	.4byte	0xfb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x11
	.byte	0x1
	.asciz	"TMR1_Period16BitGet"
	.byte	0x1
	.byte	0x84
	.byte	0x1
	.4byte	0xfb
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.uleb128 0xf
	.byte	0x1
	.asciz	"TMR1_Counter16BitSet"
	.byte	0x1
	.byte	0x89
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x59e
	.uleb128 0x10
	.asciz	"value"
	.byte	0x1
	.byte	0x89
	.4byte	0xfb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x11
	.byte	0x1
	.asciz	"TMR1_Counter16BitGet"
	.byte	0x1
	.byte	0x91
	.byte	0x1
	.4byte	0xfb
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"TMR1_CallBack"
	.byte	0x1
	.byte	0x97
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.uleb128 0x12
	.byte	0x1
	.asciz	"_T1Interrupt"
	.byte	0x1
	.byte	0x6a
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"TMR1_Start"
	.byte	0x1
	.byte	0x9c
	.byte	0x1
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"TMR1_Stop"
	.byte	0x1
	.byte	0xa8
	.byte	0x1
	.4byte	.LFB8
	.4byte	.LFE8
	.byte	0x1
	.byte	0x5f
	.uleb128 0x13
	.byte	0x1
	.asciz	"TMR1_GetElapsedThenClear"
	.byte	0x1
	.byte	0xb1
	.byte	0x1
	.4byte	0x4d1
	.4byte	.LFB9
	.4byte	.LFE9
	.byte	0x1
	.byte	0x5f
	.4byte	0x672
	.uleb128 0x14
	.asciz	"status"
	.byte	0x1
	.byte	0xb3
	.4byte	0x4d1
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x11
	.byte	0x1
	.asciz	"TMR1_SoftwareCounterGet"
	.byte	0x1
	.byte	0xbe
	.byte	0x1
	.4byte	0xc6
	.4byte	.LFB10
	.4byte	.LFE10
	.byte	0x1
	.byte	0x5f
	.uleb128 0xe
	.byte	0x1
	.asciz	"TMR1_SoftwareCounterClear"
	.byte	0x1
	.byte	0xc3
	.byte	0x1
	.4byte	.LFB11
	.4byte	.LFE11
	.byte	0x1
	.byte	0x5f
	.uleb128 0x15
	.4byte	.LASF0
	.byte	0x2
	.2byte	0x105
	.4byte	0x6d4
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	0x25c
	.uleb128 0x15
	.4byte	.LASF1
	.byte	0x2
	.2byte	0x153
	.4byte	0x6e7
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	0x389
	.uleb128 0x17
	.asciz	"TMR1"
	.byte	0x2
	.2byte	0x348
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	0xfb
	.uleb128 0x17
	.asciz	"PR1"
	.byte	0x2
	.2byte	0x34a
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"T1CON"
	.byte	0x2
	.2byte	0x34c
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.4byte	.LASF2
	.byte	0x2
	.2byte	0x362
	.4byte	0x72c
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.4byte	0x47f
	.uleb128 0x14
	.asciz	"tmr1_obj"
	.byte	0x1
	.byte	0x50
	.4byte	0x4da
	.byte	0x5
	.byte	0x3
	.4byte	_tmr1_obj
	.uleb128 0x15
	.4byte	.LASF0
	.byte	0x2
	.2byte	0x105
	.4byte	0x6d4
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.4byte	.LASF1
	.byte	0x2
	.2byte	0x153
	.4byte	0x6e7
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"TMR1"
	.byte	0x2
	.2byte	0x348
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"PR1"
	.byte	0x2
	.2byte	0x34a
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x17
	.asciz	"T1CON"
	.byte	0x2
	.2byte	0x34c
	.4byte	0x6fb
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.4byte	.LASF2
	.byte	0x2
	.2byte	0x362
	.4byte	0x72c
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
	.uleb128 0x7
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
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
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
	.uleb128 0x11
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x17
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
	.4byte	0x11b
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x79f
	.4byte	0x4e9
	.asciz	"TMR1_Initialize"
	.4byte	0x508
	.asciz	"TMR1_Period16BitSet"
	.4byte	0x53f
	.asciz	"TMR1_Period16BitGet"
	.4byte	0x566
	.asciz	"TMR1_Counter16BitSet"
	.4byte	0x59e
	.asciz	"TMR1_Counter16BitGet"
	.4byte	0x5c6
	.asciz	"TMR1_CallBack"
	.4byte	0x5e3
	.asciz	"_T1Interrupt"
	.4byte	0x5fe
	.asciz	"TMR1_Start"
	.4byte	0x618
	.asciz	"TMR1_Stop"
	.4byte	0x631
	.asciz	"TMR1_GetElapsedThenClear"
	.4byte	0x672
	.asciz	"TMR1_SoftwareCounterGet"
	.4byte	0x69d
	.asciz	"TMR1_SoftwareCounterClear"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x94
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x79f
	.4byte	0xfb
	.asciz	"uint16_t"
	.4byte	0x14a
	.asciz	"tagIFS0BITS"
	.4byte	0x25c
	.asciz	"IFS0BITS"
	.4byte	0x26d
	.asciz	"tagIEC0BITS"
	.4byte	0x389
	.asciz	"IEC0BITS"
	.4byte	0x460
	.asciz	"tagT1CONBITS"
	.4byte	0x47f
	.asciz	"T1CONBITS"
	.4byte	0x491
	.asciz	"_TMR_OBJ_STRUCT"
	.4byte	0x4da
	.asciz	"TMR_OBJ"
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
.LASF2:
	.asciz	"T1CONbits"
.LASF0:
	.asciz	"IFS0bits"
.LASF1:
	.asciz	"IEC0bits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
