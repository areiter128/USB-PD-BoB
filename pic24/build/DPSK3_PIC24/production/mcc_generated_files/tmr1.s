	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\tmr1.c"
	.section	.text,code
	.align	2
	.global	_TMR1_Initialize	; export
	.type	_TMR1_Initialize,@function
_TMR1_Initialize:
	.set ___PA___,1
	clr	_TMR1
	mov	#2000,w0
	mov	w0,_PR1
	mov	#-32752,w0
	mov	w0,_T1CON
	bclr.b	_IFS0bits,#3
	bset.b	_IEC0bits,#3
	clr.b	_tmr1_obj
	return	
	.set ___PA___,0
	.size	_TMR1_Initialize, .-_TMR1_Initialize
	.align	2
	.global	_TMR1_Period16BitSet	; export
	.type	_TMR1_Period16BitSet,@function
_TMR1_Period16BitSet:
	.set ___PA___,1
	mov	w0,_PR1
	clr.b	_tmr1_obj
	return	
	.set ___PA___,0
	.size	_TMR1_Period16BitSet, .-_TMR1_Period16BitSet
	.align	2
	.global	_TMR1_Period16BitGet	; export
	.type	_TMR1_Period16BitGet,@function
_TMR1_Period16BitGet:
	.set ___PA___,1
	mov	_PR1,w0
	return	
	.set ___PA___,0
	.size	_TMR1_Period16BitGet, .-_TMR1_Period16BitGet
	.align	2
	.global	_TMR1_Counter16BitSet	; export
	.type	_TMR1_Counter16BitSet,@function
_TMR1_Counter16BitSet:
	.set ___PA___,1
	mov	w0,_TMR1
	clr.b	_tmr1_obj
	return	
	.set ___PA___,0
	.size	_TMR1_Counter16BitSet, .-_TMR1_Counter16BitSet
	.align	2
	.global	_TMR1_Counter16BitGet	; export
	.type	_TMR1_Counter16BitGet,@function
_TMR1_Counter16BitGet:
	.set ___PA___,1
	mov	_TMR1,w0
	return	
	.set ___PA___,0
	.size	_TMR1_Counter16BitGet, .-_TMR1_Counter16BitGet
	.align	2
	.weak	_TMR1_CallBack
	.type	_TMR1_CallBack,@function
_TMR1_CallBack:
	.set ___PA___,1
	return	
	.set ___PA___,0
	.size	_TMR1_CallBack, .-_TMR1_CallBack
	.section	.isr.text,code,keep
	.align	2
	.global	__T1Interrupt	; export
	.type	__T1Interrupt,@function
__T1Interrupt:
	.set ___PA___,1
	push	_RCOUNT
	mov.d	w0,[w15++]
	mov.d	w2,[w15++]
	mov.d	w4,[w15++]
	mov.d	w6,[w15++]
	rcall	_TMR1_CallBack
	inc	_tmr1_obj+2
	mov.b	#1,w0
	mov.b	WREG,_tmr1_obj
	bclr.b	_IFS0bits,#3
	mov.d	[--w15],w6
	mov.d	[--w15],w4
	mov.d	[--w15],w2
	mov.d	[--w15],w0
	pop	_RCOUNT
	retfie	
	.set ___PA___,0
	.size	__T1Interrupt, .-__T1Interrupt
	.section	.text,code
	.align	2
	.global	_TMR1_Start	; export
	.type	_TMR1_Start,@function
_TMR1_Start:
	.set ___PA___,1
	clr.b	_tmr1_obj
	bset.b	_IEC0bits,#3
	bset.b	_T1CONbits+1,#7
	return	
	.set ___PA___,0
	.size	_TMR1_Start, .-_TMR1_Start
	.align	2
	.global	_TMR1_Stop	; export
	.type	_TMR1_Stop,@function
_TMR1_Stop:
	.set ___PA___,1
	bclr.b	_T1CONbits+1,#7
	bclr.b	_IEC0bits,#3
	return	
	.set ___PA___,0
	.size	_TMR1_Stop, .-_TMR1_Stop
	.align	2
	.global	_TMR1_GetElapsedThenClear	; export
	.type	_TMR1_GetElapsedThenClear,@function
_TMR1_GetElapsedThenClear:
	.set ___PA___,1
	mov.b	_tmr1_obj,WREG
	.set ___BP___,39
	bra	z,.L11
	clr.b	_tmr1_obj
.L11:
	return	
	.size	_TMR1_GetElapsedThenClear, .-_TMR1_GetElapsedThenClear
	.align	2
	.global	_TMR1_SoftwareCounterGet	; export
	.type	_TMR1_SoftwareCounterGet,@function
_TMR1_SoftwareCounterGet:
	.set ___PA___,1
	mov	_tmr1_obj+2,w0
	return	
	.set ___PA___,0
	.size	_TMR1_SoftwareCounterGet, .-_TMR1_SoftwareCounterGet
	.align	2
	.global	_TMR1_SoftwareCounterClear	; export
	.type	_TMR1_SoftwareCounterClear,@function
_TMR1_SoftwareCounterClear:
	.set ___PA___,1
	clr	_tmr1_obj+2
	return	
	.set ___PA___,0
	.size	_TMR1_SoftwareCounterClear, .-_TMR1_SoftwareCounterClear
	.section	.nbss,bss,near
	.align	2
	.type	_tmr1_obj,@object
	.size	_tmr1_obj, 4
_tmr1_obj:
	.skip	4



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
