	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\buttons.c"
	.section	.text,code
	.align	2
	.type	__ButtonRead,@function
__ButtonRead:
	.set ___PA___,1
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L3
	sub.b	w0,#1,[w15]
	.set ___BP___,71
	bra	nz,.L6
	bra	.L8
.L3:
	mov	_PORTAbits,w0
	lsr	w0,#2,w0
	bra	.L7
.L8:
	mov	_PORTAbits,w0
	lsr	w0,#3,w0
.L7:
	and.b	w0,#1,w0
	return	
.L6:
	retlw	#1,w0
	.size	__ButtonRead, .-__ButtonRead
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
	.global	_ButtonsInit	; export
	.type	_ButtonsInit,@function
_ButtonsInit:
	.set ___PA___,1
	rcall	_INTERRUPT_GlobalDisable
	clr.b	w0
	mov	#_buttonArray,w1
	mov.b	w0,[w1]
	inc	w1,w1
	mov.b	w0,[w1]
	inc	w1,w1
	mov.b	w0,[w1]
	mov.b	#1,w1
	mov	#_buttonArray+3,w2
	mov.b	w1,[w2]
	inc	w2,w2
	mov.b	w0,[w2]
	inc	w2,w2
	mov.b	w0,[w2]
	inc	w2,w2
	mov.b	w0,[w2]
	inc	w2,w0
	mov.b	w1,[w0]
	bra	_INTERRUPT_GlobalEnable
	.set ___PA___,0
	.size	_ButtonsInit, .-_ButtonsInit
	.align	2
	.global	_ButtonEventBuck	; export
	.type	_ButtonEventBuck,@function
_ButtonEventBuck:
	.set ___PA___,1
	mov	w8,[w15++]
	rcall	_INTERRUPT_GlobalDisable
	mov	#_buttonArray+2,w1
	mov.b	[w1],w8
	clr.b	[w1]
	rcall	_INTERRUPT_GlobalEnable
	mov.b	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_ButtonEventBuck, .-_ButtonEventBuck
	.align	2
	.global	_ButtonEventBoost	; export
	.type	_ButtonEventBoost,@function
_ButtonEventBoost:
	.set ___PA___,1
	mov	w8,[w15++]
	rcall	_INTERRUPT_GlobalDisable
	mov	#_buttonArray+6,w1
	mov.b	[w1],w8
	clr.b	[w1]
	rcall	_INTERRUPT_GlobalEnable
	mov.b	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_ButtonEventBoost, .-_ButtonEventBoost
	.align	2
	.global	_ButtonsTask	; export
	.type	_ButtonsTask,@function
_ButtonsTask:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	#_scan.4210,w8
	mov.b	[w8],w8
	mov.b	w8,w0
	rcall	__ButtonRead
	ze	w8,w8
	sl	w8,#2,w8
	inc2	w8,w2
	mov	#_buttonArray+1,w1
	mov.b	[w1+w2],w3
	dec	w1,w2
	sub.b	w0,w3,[w15]
	.set ___BP___,72
	bra	nz,.L15
	add	w2,w8,w2
	clr.b	[w2]
	cp0.b	w0
	.set ___BP___,50
	bra	nz,.L16
	mov.b	[w1+w8],w3
	mov.b	#-107,w0
	sub.b	w3,w0,[w15]
	.set ___BP___,50
	bra	gtu,.L16
	mov.b	[w1+w8],w3
	add	w1,w8,w0
	inc.b	w3,[w0]
	mov.b	[w1+w8],w1
	mov.b	#-106,w0
	sub.b	w1,w0,[w15]
	.set ___BP___,72
	bra	nz,.L16
	mov.b	#2,w0
	mov.b	w0,[w2+2]
	bra	.L16
.L15:
	mov.b	[w2+w8],w4
	add	w2,w8,w3
	inc.b	w4,[w3]
	mov.b	[w2+w8],w2
	sub.b	w2,#3,[w15]
	.set ___BP___,72
	bra	nz,.L16
	add	w1,w8,w2
	mov.b	w0,[w2+2]
	clr.b	[w3]
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L17
	mov.b	[w1+w8],w1
	mov.b	#-107,w0
	sub.b	w1,w0,[w15]
	.set ___BP___,50
	bra	gtu,.L17
	mov.b	#1,w0
	mov.b	w0,[w3+2]
.L17:
	mov.b	_scan.4210,WREG
	ze	w0,w0
	sl	w0,#2,w0
	mov	#_buttonArray+1,w1
	add	w1,w0,w0
	clr.b	[w0]
.L16:
	inc.b	_scan.4210,WREG
	mov.b	WREG,_scan.4210
	sub.b	w0,#1,[w15]
	.set ___BP___,19
	bra	leu,.L14
	clr.b	_scan.4210
.L14:
	mov	[--w15],w8
	return	
	.set ___PA___,0
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



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
