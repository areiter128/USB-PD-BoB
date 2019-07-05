	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\adc1.c"
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
	.global	_ADC1_Initialize	; export
	.type	_ADC1_Initialize,@function
_ADC1_Initialize:
	.set ___PA___,1
	mov	#-32540,w0
	mov	w0,_AD1CON1
	mov	#1028,w0
	mov	w0,_AD1CON2
	mov	#5169,w0
	mov	w0,_AD1CON3
	clr	_AD1CHS
	mov	#16,w0
	mov	w0,_AD1CSSL
	mov	_AD1CON2bits,w0
	lsr	w0,#2,w0
	and.b	w0,#15,w0
	mov.b	WREG,_adc1_obj
	bset.b	_IEC0bits+1,#5
	return	
	.set ___PA___,0
	.size	_ADC1_Initialize, .-_ADC1_Initialize
	.align	2
	.global	_ADC1_Start	; export
	.type	_ADC1_Start,@function
_ADC1_Start:
	.set ___PA___,1
	bset.b	_AD1CON1bits,#1
	return	
	.set ___PA___,0
	.size	_ADC1_Start, .-_ADC1_Start
	.align	2
	.global	_ADC1_Stop	; export
	.type	_ADC1_Stop,@function
_ADC1_Stop:
	.set ___PA___,1
	bclr.b	_AD1CON1bits,#1
	return	
	.set ___PA___,0
	.size	_ADC1_Stop, .-_ADC1_Stop
	.align	2
	.global	_ADC1_ConversionResultBufferGet	; export
	.type	_ADC1_ConversionResultBufferGet,@function
_ADC1_ConversionResultBufferGet:
	.set ___PA___,1
	mov	#_adc1_obj,w3
	mov.b	[w3],w3
	ze	w3,w3
	mov	#_ADC1BUF0,w2
	mov	w0,w1
	clr	w0
.L7:
	mov	[w2++],[w1++]
	inc	w0,w0
	sub	w0,w3,[w15]
	.set ___BP___,90
	bra	le,.L7
	return	
	.set ___PA___,0
	.size	_ADC1_ConversionResultBufferGet, .-_ADC1_ConversionResultBufferGet
	.align	2
	.global	_ADC1_ConversionResultGet	; export
	.type	_ADC1_ConversionResultGet,@function
_ADC1_ConversionResultGet:
	.set ___PA___,1
	mov	_ADC1BUF0,w0
	return	
	.set ___PA___,0
	.size	_ADC1_ConversionResultGet, .-_ADC1_ConversionResultGet
	.align	2
	.global	_ADC1_IsConversionComplete	; export
	.type	_ADC1_IsConversionComplete,@function
_ADC1_IsConversionComplete:
	.set ___PA___,1
	mov	_AD1CON1bits,w0
	and.b	w0,#1,w0
	return	
	.set ___PA___,0
	.size	_ADC1_IsConversionComplete, .-_ADC1_IsConversionComplete
	.align	2
	.global	_ADC1_ChannelSelect	; export
	.type	_ADC1_ChannelSelect,@function
_ADC1_ChannelSelect:
	.set ___PA___,1
	mov	w0,_AD1CHS
	return	
	.set ___PA___,0
	.size	_ADC1_ChannelSelect, .-_ADC1_ChannelSelect
	.section	.isr.text,code,keep
	.align	2
	.global	__ADC1Interrupt	; export
	.type	__ADC1Interrupt,@function
__ADC1Interrupt:
	.set ___PA___,1
	mov.d	w0,[w15++]
	mov.d	w2,[w15++]
	push	_PSVPAG
	mov	#__const_psvpage,w0
	mov	w0,_PSVPAG
	mov	_ADC1BUF0,w2
	mov	_adc_average,w0
	mov	_adc_average+2,w1
	add	w2,w0,w0
	addc	w1,#0,w1
	mov	w0,_adc_average
	mov	w1,_adc_average+2
	mov	_adc_counter.4380,w2
	inc	w2,w2
	mov	w2,_adc_counter.4380
	mov	#2048,w3
	sub	w2,w3,[w15]
	.set ___BP___,62
	bra	nz,.L12
	clr	_adc_counter.4380
	mov	w0,_adc_value
	mov	w1,_adc_value+2
	clr	_adc_average
	clr	_adc_average+2
	mov.b	#1,w0
	mov.b	WREG,_adc_ready
.L12:
	bclr.b	_IFS0bits+1,#5
	pop	_PSVPAG
	mov.d	[--w15],w2
	mov.d	[--w15],w0
	retfie	
	.set ___PA___,0
	.size	__ADC1Interrupt, .-__ADC1Interrupt
	.section	.text,code
	.align	2
	.global	_ADC1_ReadAvg	; export
	.type	_ADC1_ReadAvg,@function
_ADC1_ReadAvg:
	.set ___PA___,1
	lnk	#4
	cp0.b	_adc_ready
	.set ___BP___,61
	bra	z,.L14
	rcall	_INTERRUPT_GlobalDisable
	mov	_adc_value,w0
	mov	_adc_value+2,w1
	clr.b	_adc_ready
	mov	w0,[w15-4]
	mov	w1,[w15-2]
	rcall	_INTERRUPT_GlobalEnable
	mov	[w15-4],w0
	mov	[w15-2],w1
	sl	w1,#5,w2
	lsr	w0,#11,w0
	ior	w2,w0,w0
	lsr	w1,#11,w1
	mov	w0,_retval.4384
.L14:
	mov	_retval.4384,w0
	ulnk	
	return	
	.set ___PA___,0
	.size	_ADC1_ReadAvg, .-_ADC1_ReadAvg
	.section	.nbss,bss,near
	.type	_adc_ready,@object
	.size	_adc_ready, 1
_adc_ready:
	.skip	1
	.align	2
	.type	_adc_value,@object
	.size	_adc_value, 4
_adc_value:
	.skip	4
	.align	2
	.type	_retval.4384,@object
	.size	_retval.4384, 2
_retval.4384:
	.skip	2
	.align	2
	.type	_adc_average,@object
	.size	_adc_average, 4
_adc_average:
	.skip	4
	.align	2
	.type	_adc_counter.4380,@object
	.size	_adc_counter.4380, 2
_adc_counter.4380:
	.skip	2
	.align	2
	.type	_adc1_obj,@object
	.size	_adc1_obj, 1
_adc1_obj:
	.skip	1



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
