	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\main.c"
	.section	.text,code
	.align	2
	.global	_main	; export
	.type	_main,@function
_main:
	.set ___PA___,1
	lnk	#10
	mov	w8,[w15++]
	clr.b	w0
	mov.b	w0,[w15-12]
	rcall	_SYSTEM_Initialize
	rcall	_LedsInit
	rcall	_ButtonsInit
	rcall	_LoadsInit
	rcall	_FaultInit
	rcall	_ADC1_Initialize
	rcall	_ProtocolInit
	mov	#4608,w0
	mov	#122,w1
	rcall	___delay32
.L27:
	sub	w15,#10,w0
	rcall	_TemperatureCheck
	mov	w0,[w15-8]
	mov.b	[w15-10],w1
	mov.b	w1,[w15-6]
	clr	w0
	mov.b	[w15-12],w1
	cp0.b	w1
	.set ___BP___,71
	bra	nz,.L3
	rcall	_LoadsGetStatus
.L3:
	mov	w0,[w15-4]
	clr.b	w0
	mov.b	[w15-12],w1
	cp0.b	w1
	.set ___BP___,71
	bra	nz,.L4
	rcall	_FaultCheck
.L4:
	mov.b	w0,[w15-5]
	sub	w15,#6,w0
	rcall	_ProtocolCheck
	mov.b	w0,[w15-9]
	mov.b	[w15-9],w0
	ze	w0,w0
	clr	w1
	sub	w0,#1,w0
	subb	w1,#0,w1
	sub	w0,#6,[w15]
	subb	w1,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L5
	bra	w0
	.align	2
	.set	___PA___,0
.L13:
	bra	.L6
	bra	.L7
	bra	.L8
	bra	.L9
	bra	.L10
	bra	.L11
	bra	.L12
	.set	___PA___,1
.L6:
	mov	#2,w0
	bra	.L29
.L7:
	mov	#4,w0
.L29:
	rcall	_LoadsStateMachine
	bra	.L5
.L8:
	mov	#3,w0
	bra	.L29
.L9:
	mov	#5,w0
	bra	.L29
.L10:
	rcall	_ProtocolClose
	mov	#4608,w0
	mov	#122,w1
	rcall	___delay32
	rcall	_SysReset
	bra	.L5
.L11:
	rcall	_LoadsInit
	mov.b	#1,w0
	mov.b	w0,[w15-12]
	clr.b	w8
.L14:
	mov.b	w8,w0
	rcall	_LedBlink
	inc.b	w8,w8
	sub.b	w8,#9,[w15]
	.set ___BP___,88
	bra	nz,.L14
	bra	.L5
.L12:
	rcall	_LoadsInit
	clr.b	w0
	mov.b	w0,[w15-12]
	mov.b	w0,w8
.L15:
	mov.b	w8,w0
	rcall	_LedOff
	inc.b	w8,w8
	sub.b	w8,#9,[w15]
	.set ___BP___,88
	bra	nz,.L15
.L5:
	mov.b	[w15-12],w1
	cp0.b	w1
	.set ___BP___,91
	bra	nz,.L27
	mov	[w15-8],w0
	sub	w0,#2,[w15]
	.set ___BP___,86
	bra	nz,.L17
	mov.b	#8,w0
	rcall	_LedOff
	bra	.L30
.L17:
	mov	[w15-8],w8
	sub	w8,#1,[w15]
	.set ___BP___,86
	bra	nz,.L19
	mov.b	#8,w0
	rcall	_LedBlink
	mov	w8,w0
	bra	.L31
.L19:
	mov	[w15-8],w0
	sub	w0,#3,[w15]
	.set ___BP___,86
	bra	nz,.L18
	mov.b	#8,w0
	rcall	_LedOn
.L30:
	clr	w0
.L31:
	rcall	_LoadsStateMachine
.L18:
	rcall	_ButtonEventBuck
	mov.b	w0,[w15-11]
	mov.b	[w15-11],w0
	sub.b	w0,#1,[w15]
	.set ___BP___,86
	bra	nz,.L20
	mov	#2,w0
	bra	.L32
.L20:
	mov.b	[w15-11],w0
	sub.b	w0,#2,[w15]
	.set ___BP___,86
	bra	nz,.L21
	mov	#3,w0
.L32:
	rcall	_LoadsStateMachine
.L21:
	rcall	_ButtonEventBoost
	mov.b	w0,[w15-11]
	mov.b	[w15-11],w0
	sub.b	w0,#1,[w15]
	.set ___BP___,86
	bra	nz,.L22
	mov	#4,w0
	bra	.L28
.L22:
	mov.b	[w15-11],w0
	sub.b	w0,#2,[w15]
	.set ___BP___,72
	bra	nz,.L27
	mov	#5,w0
.L28:
	rcall	_LoadsStateMachine
	bra	.L27
	.size	_main, .-_main
	.align	2
	.global	_TMR1_CallBack	; export
	.type	_TMR1_CallBack,@function
_TMR1_CallBack:
	.set ___PA___,1
	mov.b	_nTick.4683,WREG
	ze	w0,w0
	clr	w1
	sub	w0,#4,[w15]
	subb	w1,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L34
	bra	w0
	.align	2
	.set	___PA___,0
.L40:
	bra	.L35
	bra	.L36
	bra	.L37
	bra	.L38
	bra	.L39
	.set	___PA___,1
.L35:
	rcall	_LedsMatrixTask
	bra	.L41
.L36:
	rcall	_ButtonsTask
	bra	.L41
.L37:
	rcall	_FaultTask
	bra	.L41
.L38:
	rcall	_LedsBlinkTask
	bra	.L41
.L39:
	rcall	_LoadsTask
	bra	.L41
.L34:
	clr.b	_nTick.4683
.L41:
	inc.b	_nTick.4683,WREG
	mov.b	WREG,_nTick.4683
	sub.b	w0,#4,[w15]
	.set ___BP___,39
	bra	leu,.L42
	clr.b	_nTick.4683
.L42:
	bra	_ProtocolTick
	.set ___PA___,0
	.size	_TMR1_CallBack, .-_TMR1_CallBack
	.section	.nbss,bss,near
	.type	_nTick.4683,@object
	.size	_nTick.4683, 1
_nTick.4683:
	.skip	1



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
