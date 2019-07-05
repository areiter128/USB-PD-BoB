	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\fault.c"
	.section	.text,code
	.align	2
	.type	_FaultInput,@function
_FaultInput:
	.set ___PA___,1
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
	bra	.L10
.L4:
	mov	_PORTCbits,w0
	lsr	w0,#7,w0
	bra	.L9
.L3:
	mov	_PORTCbits,w0
	lsr	w0,#6,w0
	bra	.L9
.L10:
	mov	_PORTCbits,w0
	lsr	w0,#8,w0
	bra	.L9
.L5:
	mov	_PORTCbits,w0
	lsr	w0,#9,w0
.L9:
	and.b	w0,#1,w0
	return	
.L8:
	retlw	#0,w0
	.size	_FaultInput, .-_FaultInput
	.align	2
	.type	_FaultClear,@function
_FaultClear:
	.set ___PA___,1
	sub.b	w0,#1,[w15]
	.set ___BP___,29
	bra	z,.L14
	.set ___BP___,50
	bra	ltu,.L13
	sub.b	w0,#2,[w15]
	.set ___BP___,29
	bra	z,.L15
	sub.b	w0,#3,[w15]
	.set ___BP___,71
	bra	nz,.L11
	bra	.L17
.L14:
	bclr.b	_LATBbits+1,#3
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	bset.b	_LATBbits+1,#3
	return	
.L13:
	bclr.b	_LATBbits+1,#2
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	bset.b	_LATBbits+1,#2
	return	
.L17:
	bclr.b	_LATBbits+1,#5
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	bset.b	_LATBbits+1,#5
	return	
.L15:
	bclr.b	_LATBbits+1,#4
	mov	#800,w0
	mov	#0,w1
	rcall	___delay32
	bset.b	_LATBbits+1,#4
.L11:
	return	
	.size	_FaultClear, .-_FaultClear
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
	.global	_FaultInit	; export
	.type	_FaultInit,@function
_FaultInit:
	.set ___PA___,1
	lnk	#2
	rcall	_INTERRUPT_GlobalDisable
	clr.b	w0
	bra	.L23
.L22:
	mov.b	[w15-2],w1
	ze	w1,w0
	clr.b	w2
	mov	#_fault_flags,w1
	mov.b	w2,[w1+w0]
	mov.b	[w15-2],w1
	ze	w1,w0
	add	w0,w0,w0
	mov	#_fault_counters,w1
	add	w1,w0,w0
	clr	[w0]
	mov.b	[w15-2],w0
	inc.b	w0,w0
.L23:
	mov.b	w0,[w15-2]
	mov.b	[w15-2],w1
	sub.b	w1,#3,[w15]
	.set ___BP___,91
	bra	leu,.L22
	bset.b	_TRISCbits,#7
	bset.b	_TRISCbits,#6
	bset.b	_TRISCbits+1,#1
	bset.b	_TRISBbits+1,#1
	bset.b	_LATBbits+1,#3
	bset.b	_LATBbits+1,#2
	bset.b	_LATBbits+1,#5
	bset.b	_LATBbits+1,#4
	bclr.b	_TRISBbits+1,#2
	bclr.b	_TRISBbits+1,#3
	bclr.b	_TRISBbits+1,#4
	bclr.b	_TRISBbits+1,#5
	rcall	_INTERRUPT_GlobalEnable
	ulnk	
	return	
	.set ___PA___,0
	.size	_FaultInit, .-_FaultInit
	.align	2
	.global	_FaultCheck	; export
	.type	_FaultCheck,@function
_FaultCheck:
	.set ___PA___,1
	lnk	#2
	clr.b	w0
	mov.b	w0,[w15-2]
	bra	.L34
.L27:
	rcall	_INTERRUPT_GlobalDisable
	mov.b	[w15-1],w0
	ze	w0,w0
	mov	#_fault_flags,w1
	mov.b	[w1+w0],w0
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L26
	mov.b	[w15-2],w1
	mov.b	[w15-1],w0
	ze	w0,w0
	mov	#1,w2
	sl	w2,w0,w0
	ior.b	w1,w0,w0
	mov.b	w0,[w15-2]
.L26:
	rcall	_INTERRUPT_GlobalEnable
	mov.b	[w15-1],w0
	inc.b	w0,w0
.L34:
	mov.b	w0,[w15-1]
	mov.b	[w15-1],w0
	sub.b	w0,#3,[w15]
	.set ___BP___,91
	bra	leu,.L27
	mov.b	[w15-2],w1
	ze	w1,w0
	btst	w0,#0
	.set ___BP___,71
	bra	z,.L28
	mov.b	#2,w0
	rcall	_LedBlink
	bra	.L29
.L28:
	mov.b	[w15-2],w1
	ze	w1,w0
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L30
	mov.b	#2,w0
	rcall	_LedOn
	bra	.L29
.L30:
	mov.b	#2,w0
	rcall	_LedOff
.L29:
	mov.b	[w15-2],w1
	ze	w1,w0
	btst	w0,#2
	.set ___BP___,79
	bra	z,.L31
	mov.b	#5,w0
	rcall	_LedBlink
	bra	.L32
.L31:
	mov.b	[w15-2],w1
	ze	w1,w0
	btst	w0,#3
	.set ___BP___,61
	bra	z,.L33
	mov.b	#5,w0
	rcall	_LedOn
	bra	.L32
.L33:
	mov.b	#5,w0
	rcall	_LedOff
.L32:
	mov.b	[w15-2],w0
	ulnk	
	return	
	.set ___PA___,0
	.size	_FaultCheck, .-_FaultCheck
	.align	2
	.global	_FaultTask	; export
	.type	_FaultTask,@function
_FaultTask:
	.set ___PA___,1
	lnk	#2
	clr.b	w0
	bra	.L41
.L40:
	mov.b	[w15-2],w0
	rcall	_FaultInput
	cp0.b	w0
	.set ___BP___,50
	bra	z,.L37
	mov	#_fault_counters,w0
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	[w0+w1],w1
	cp0	w1
	.set ___BP___,50
	bra	z,.L38
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	add	w0,w1,w1
	dec	[w1],[w1]
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	[w0+w1],w0
	cp0	w0
	.set ___BP___,71
	bra	nz,.L39
	mov.b	[w15-2],w0
	rcall	_FaultClear
	bra	.L39
.L38:
	mov.b	[w15-2],w2
	ze	w2,w1
	add	w1,w1,w1
	mov	#200,w2
	mov	w2,[w0+w1]
	mov.b	[w15-2],w1
	ze	w1,w0
	mov.b	#1,w2
	mov	#_fault_flags,w1
	mov.b	w2,[w1+w0]
	bra	.L39
.L37:
	mov.b	[w15-2],w2
	ze	w2,w1
	mov	#_fault_flags,w2
	mov.b	w0,[w2+w1]
.L39:
	mov.b	[w15-2],w0
	inc.b	w0,w0
.L41:
	mov.b	w0,[w15-2]
	mov.b	[w15-2],w1
	sub.b	w1,#3,[w15]
	.set ___BP___,91
	bra	leu,.L40
	ulnk	
	return	
	.set ___PA___,0
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



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
