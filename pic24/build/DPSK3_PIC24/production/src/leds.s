	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\leds.c"
	.section	.text,code
	.align	2
	.type	_INTERRUPT_GlobalDisable,@function
_INTERRUPT_GlobalDisable:
	.set ___PA___,1
	disi	#16383
	return	
	.set ___PA___,0
	.size	_INTERRUPT_GlobalDisable, .-_INTERRUPT_GlobalDisable
	.align	2
	.type	_INTERRUPT_GlobalEnable,@function
_INTERRUPT_GlobalEnable:
	.set ___PA___,1
	disi	#0
	return	
	.set ___PA___,0
	.size	_INTERRUPT_GlobalEnable, .-_INTERRUPT_GlobalEnable
	.align	2
	.global	_LedsInit	; export
	.type	_LedsInit,@function
_LedsInit:
	.set ___PA___,1
	lnk	#2
	rcall	_INTERRUPT_GlobalDisable
	clr.b	w0
	bra	.L9
.L7:
	clr.b	w0
	bra	.L8
.L6:
	mov.b	[w15-2],w0
	mov.b	[w15-1],w1
	mov.b	#3,w2
	mul.b	WREG2
	ze	w1,w1
	add	w2,w1,w1
	clr.b	w2
	mov	#_leds_status_array,w0
	mov.b	w2,[w0+w1]
	mov.b	[w15-2],w1
	ze	w1,w0
	mov.b	[w15-1],w2
	ze	w2,w2
	mul.su	w0,#3,w0
	add	w2,w0,w0
	mov	#_leds_matrix,w1
	add	w1,w0,w0
	clr.b	[w0]
	mov.b	[w15-1],w0
	inc.b	w0,w0
.L8:
	mov.b	w0,[w15-1]
	mov.b	[w15-1],w0
	sub.b	w0,#2,[w15]
	.set ___BP___,91
	bra	leu,.L6
	mov.b	[w15-2],w0
	inc.b	w0,w0
.L9:
	mov.b	w0,[w15-2]
	mov.b	[w15-2],w1
	sub.b	w1,#2,[w15]
	.set ___BP___,91
	bra	leu,.L7
	bclr.b	_TRISBbits,#4
	bclr.b	_TRISAbits,#4
	bclr.b	_TRISAbits+1,#1
	bclr.b	_TRISCbits,#3
	bclr.b	_TRISCbits,#4
	bclr.b	_TRISCbits,#5
	rcall	_INTERRUPT_GlobalEnable
	ulnk	
	return	
	.set ___PA___,0
	.size	_LedsInit, .-_LedsInit
	.align	2
	.global	_LedOn	; export
	.type	_LedOn,@function
_LedOn:
	.set ___PA___,1
	mov	w8,[w15++]
	mov.b	w0,w8
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L10
	rcall	_INTERRUPT_GlobalDisable
	ze	w8,w8
	mov.b	#1,w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	rcall	_INTERRUPT_GlobalEnable
.L10:
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_LedOn, .-_LedOn
	.align	2
	.global	_LedOff	; export
	.type	_LedOff,@function
_LedOff:
	.set ___PA___,1
	mov	w8,[w15++]
	mov.b	w0,w8
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L12
	rcall	_INTERRUPT_GlobalDisable
	ze	w8,w8
	clr.b	w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	rcall	_INTERRUPT_GlobalEnable
.L12:
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_LedOff, .-_LedOff
	.align	2
	.global	_LedBlink	; export
	.type	_LedBlink,@function
_LedBlink:
	.set ___PA___,1
	mov	w8,[w15++]
	mov.b	w0,w8
	sub.b	w8,#8,[w15]
	.set ___BP___,61
	bra	gtu,.L14
	rcall	_INTERRUPT_GlobalDisable
	ze	w8,w8
	mov.b	#2,w1
	mov	#_leds_status_array,w0
	mov.b	w1,[w0+w8]
	rcall	_INTERRUPT_GlobalEnable
.L14:
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_LedBlink, .-_LedBlink
	.align	2
	.global	_LedsMatrixTask	; export
	.type	_LedsMatrixTask,@function
_LedsMatrixTask:
	.set ___PA___,1
	lnk	#2
	clr.b	w0
	mov.b	w0,[w15-2]
	bra	.L17
.L18:
	mov.b	[w15-2],w1
	ze	w1,w0
	sl	w0,#2,w0
	mov	#_led_columns_array,w1
	mov	[w1+w0],w0
	mov.b	[w15-2],w3
	ze	w3,w2
	sl	w2,#2,w2
	inc2	w2,w2
	mov	[w1+w2],w1
	com	w1,w1
	and	w1,[w0],[w0]
	mov.b	[w15-2],w4
	inc.b	w4,w4
	mov.b	w4,[w15-2]
.L17:
	mov.b	[w15-2],w0
	sub.b	w0,#2,[w15]
	.set ___BP___,91
	bra	leu,.L18
	mov.b	_row_counter.4220,WREG
	ze	w0,w3
	sl	w3,#2,w3
	mov	#_led_rows_array,w2
	mov	[w2+w3],w1
	inc2	w3,w3
	mov	[w2+w3],w2
	ior	w2,[w1],[w1]
	inc.b	w0,w0
	mov.b	WREG,_row_counter.4220
	sub.b	w0,#2,[w15]
	.set ___BP___,50
	bra	leu,.L19
	clr.b	_row_counter.4220
.L19:
	clr.b	w1
	mov.b	w1,[w15-2]
	mov	#_row_counter.4220,w2
	mov.b	[w2],w2
	ze	w2,w2
	bra	.L20
.L23:
	mov.b	[w15-2],w4
	ze	w4,w3
	mul.su	w2,#3,w0
	add	w3,w0,w0
	mov	#_leds_matrix,w1
	mov.b	[w1+w0],w0
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L21
	mov.b	[w15-2],w1
	ze	w1,w0
	sl	w0,#2,w0
	mov	#_led_columns_array,w1
	mov	[w1+w0],w0
	mov.b	[w15-2],w4
	ze	w4,w3
	sl	w3,#2,w3
	inc2	w3,w3
	mov	[w1+w3],w1
	ior	w1,[w0],[w0]
	bra	.L22
.L21:
	mov.b	[w15-2],w1
	ze	w1,w0
	sl	w0,#2,w0
	mov	#_led_columns_array,w1
	mov	[w1+w0],w0
	mov.b	[w15-2],w4
	ze	w4,w3
	sl	w3,#2,w3
	inc2	w3,w3
	mov	[w1+w3],w1
	com	w1,w1
	and	w1,[w0],[w0]
.L22:
	mov.b	[w15-2],w0
	inc.b	w0,w0
	mov.b	w0,[w15-2]
.L20:
	mov.b	[w15-2],w1
	sub.b	w1,#2,[w15]
	.set ___BP___,91
	bra	leu,.L23
	mov	#_row_counter.4220,w2
	mov.b	[w2],w2
	ze	w2,w2
	sl	w2,#2,w2
	mov	#_led_rows_array,w1
	mov	[w1+w2],w0
	inc2	w2,w2
	mov	[w1+w2],w1
	com	w1,w1
	and	w1,[w0],[w0]
	ulnk	
	return	
	.set ___PA___,0
	.size	_LedsMatrixTask, .-_LedsMatrixTask
	.align	2
	.global	_LedsBlinkTask	; export
	.type	_LedsBlinkTask,@function
_LedsBlinkTask:
	.set ___PA___,1
	lnk	#2
	clr.b	w0
	mov.b	w0,[w15-2]
	mov	#_blink_toggle.4232,w1
	mov.b	[w1],w1
	bra	.L25
.L32:
	clr.b	w0
	bra	.L35
.L31:
	mov.b	[w15-2],w0
	mov.b	[w15-1],w3
	mov.b	#3,w2
	mul.b	WREG2
	ze	w3,w3
	add	w2,w3,w3
	mov	#_leds_status_array,w0
	mov.b	[w0+w3],w0
	sub.b	w0,#1,[w15]
	.set ___BP___,29
	bra	z,.L28
	sub.b	w0,#2,[w15]
	.set ___BP___,71
	bra	nz,.L34
	bra	.L36
.L28:
	mov.b	[w15-2],w3
	ze	w3,w2
	mov.b	[w15-1],w4
	ze	w4,w4
	mul.su	w2,#3,w2
	add	w4,w2,w2
	mov	#_leds_matrix,w3
	mov.b	w0,[w3+w2]
	bra	.L30
.L36:
	mov.b	[w15-2],w0
	ze	w0,w2
	mov.b	[w15-1],w4
	ze	w4,w4
	mul.su	w2,#3,w2
	add	w4,w2,w0
	mov	#_leds_matrix,w2
	mov.b	w1,[w2+w0]
	bra	.L30
.L34:
	mov.b	[w15-2],w3
	ze	w3,w2
	mov.b	[w15-1],w4
	ze	w4,w4
	mul.su	w2,#3,w2
	add	w4,w2,w0
	mov	#_leds_matrix,w2
	add	w2,w0,w0
	clr.b	[w0]
.L30:
	mov.b	[w15-1],w0
	inc.b	w0,w0
.L35:
	mov.b	w0,[w15-1]
	mov.b	[w15-1],w0
	sub.b	w0,#2,[w15]
	.set ___BP___,91
	bra	leu,.L31
	mov.b	[w15-2],w0
	inc.b	w0,w0
	mov.b	w0,[w15-2]
.L25:
	mov.b	[w15-2],w3
	sub.b	w3,#2,[w15]
	.set ___BP___,91
	bra	leu,.L32
	cp0.b	_blink_counter.4231
	.set ___BP___,39
	bra	nz,.L33
	mov.b	#25,w0
	mov.b	WREG,_blink_counter.4231
	btg.b	_blink_toggle.4232,#0
.L33:
	dec.b	_blink_counter.4231
	ulnk	
	return	
	.set ___PA___,0
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



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
