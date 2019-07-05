	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\temperature.c"
	.section	.text,code
	.align	2
	.global	_TemperatureCheck	; export
	.type	_TemperatureCheck,@function
_TemperatureCheck:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w0,w8
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
	cp0.b	_stateThermalShutDown.4359
	.set ___BP___,50
	bra	z,.L2
	clr	w1
	mov.b	#69,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	gtu,.L3
	clr.b	_stateThermalShutDown.4359
	bra	.L9
.L2:
	mov.b	#79,w1
	sub.b	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L4
	mov.b	#1,w1
	mov	#_stateThermalShutDown.4359,w2
	mov.b	w1,[w2]
	mov	#1,w1
	bra	.L3
.L4:
	cp0.b	_stateThermalWarning.4360
	.set ___BP___,50
	bra	z,.L5
	clr	w1
	mov.b	#54,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	gtu,.L3
	clr.b	_stateThermalWarning.4360
	mov	#2,w1
	bra	.L3
.L5:
	clr	w1
	mov.b	#55,w2
	sub.b	w0,w2,[w15]
	.set ___BP___,33
	bra	leu,.L3
.L9:
	mov.b	#1,w1
	mov	#_stateThermalWarning.4360,w2
	mov.b	w1,[w2]
	mov	#3,w1
.L3:
	mov.b	w0,[w8]
	mov	w1,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
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



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
