	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\loads.c"
	.section	.text,code
	.align	2
	.type	__LoadSetBuck,@function
__LoadSetBuck:
	.set ___PA___,1
	ze	w0,w0
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L2
	bset.b	_LATCbits,#0
	bra	.L3
.L2:
	bclr.b	_LATCbits,#0
.L3:
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L4
	bset.b	_LATCbits,#1
	bra	.L5
.L4:
	bclr.b	_LATCbits,#1
.L5:
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L6
	bset.b	_LATCbits,#2
	return	
.L6:
	bclr.b	_LATCbits,#2
	return	
	.size	__LoadSetBuck, .-__LoadSetBuck
	.align	2
	.type	__LoadSetBoost,@function
__LoadSetBoost:
	.set ___PA___,1
	ze	w0,w0
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L9
	bset.b	_LATAbits,#7
	bra	.L10
.L9:
	bclr.b	_LATAbits,#7
.L10:
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L11
	bset.b	_LATBbits+1,#6
	bra	.L12
.L11:
	bclr.b	_LATBbits+1,#6
.L12:
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L13
	bset.b	_LATBbits+1,#7
	return	
.L13:
	bclr.b	_LATBbits+1,#7
	return	
	.size	__LoadSetBoost, .-__LoadSetBoost
	.align	2
	.type	__fstate_S0,@function
__fstate_S0:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L15
	bra	w2
	.align	2
	.set	___PA___,0
.L20:
	bra	.L17
	bra	.L18
	bra	.L19
	bra	.L18
	bra	.L19
	.set	___PA___,1
.L18:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
	bra	.L21
.L19:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L21:
	mov	w0,[w1+2]
	return	
.L17:
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0t),w0
	mov	w0,[w1+2]
.L15:
	return	
	.size	__fstate_S0, .-__fstate_S0
	.align	2
	.type	__fstate_S1,@function
__fstate_S1:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L22
	bra	w2
	.align	2
	.set	___PA___,0
.L27:
	bra	.L24
	bra	.L25
	bra	.L26
	bra	.L25
	bra	.L26
	.set	___PA___,1
.L25:
	mov.b	#3,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S2),w0
	bra	.L28
.L26:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L28:
	mov	w0,[w1+2]
	return	
.L24:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L22:
	return	
	.size	__fstate_S1, .-__fstate_S1
	.align	2
	.type	__fstate_S2,@function
__fstate_S2:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L29
	bra	w2
	.align	2
	.set	___PA___,0
.L34:
	bra	.L31
	bra	.L32
	bra	.L33
	bra	.L32
	bra	.L33
	.set	___PA___,1
.L32:
	mov.b	#7,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S3),w0
	bra	.L35
.L33:
	mov.b	#3,w0
	mov.b	w0,[w1]
	mov.b	#4,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B2),w0
.L35:
	mov	w0,[w1+2]
	return	
.L31:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L29:
	return	
	.size	__fstate_S2, .-__fstate_S2
	.align	2
	.type	__fstate_S3,@function
__fstate_S3:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L36
	bra	w2
	.align	2
	.set	___PA___,0
.L41:
	bra	.L38
	bra	.L39
	bra	.L40
	bra	.L39
	bra	.L40
	.set	___PA___,1
.L39:
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0),w0
	bra	.L42
.L40:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#6,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B3),w0
.L42:
	mov	w0,[w1+2]
	return	
.L38:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L36:
	return	
	.size	__fstate_S3, .-__fstate_S3
	.align	2
	.type	__fstate_B1,@function
__fstate_B1:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L43
	bra	w2
	.align	2
	.set	___PA___,0
.L48:
	bra	.L45
	bra	.L46
	bra	.L47
	bra	.L46
	bra	.L47
	.set	___PA___,1
.L46:
	mov.b	#3,w0
	mov.b	w0,[w1]
	mov.b	#4,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B2),w0
	bra	.L49
.L47:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
.L49:
	mov	w0,[w1+2]
	return	
.L45:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L43:
	return	
	.size	__fstate_B1, .-__fstate_B1
	.align	2
	.type	__fstate_B2,@function
__fstate_B2:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L50
	bra	w2
	.align	2
	.set	___PA___,0
.L55:
	bra	.L52
	bra	.L53
	bra	.L54
	bra	.L53
	bra	.L54
	.set	___PA___,1
.L53:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#6,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B3),w0
	bra	.L56
.L54:
	mov.b	#3,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S2),w0
.L56:
	mov	w0,[w1+2]
	return	
.L52:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L50:
	return	
	.size	__fstate_B2, .-__fstate_B2
	.align	2
	.type	__fstate_B3,@function
__fstate_B3:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#1,w2
	subb	w3,#0,w3
	sub	w2,#4,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L57
	bra	w2
	.align	2
	.set	___PA___,0
.L62:
	bra	.L59
	bra	.L60
	bra	.L61
	bra	.L60
	bra	.L61
	.set	___PA___,1
.L60:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
	bra	.L63
.L61:
	mov.b	#7,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S3),w0
.L63:
	mov	w0,[w1+2]
	return	
.L59:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L57:
	return	
	.size	__fstate_B3, .-__fstate_B3
	.align	2
	.type	__fstate_S0t,@function
__fstate_S0t:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#5,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L64
	bra	w2
	.align	2
	.set	___PA___,0
.L69:
	bra	.L66
	bra	.L64
	bra	.L67
	bra	.L68
	bra	.L67
	bra	.L68
	.set	___PA___,1
.L67:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	bra	.L70
.L68:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
.L70:
	mov	w0,[w1+2]
	return	
.L66:
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0),w0
	mov	w0,[w1+2]
.L64:
	return	
	.size	__fstate_S0t, .-__fstate_S0t
	.align	2
	.type	__fstate_S1t,@function
__fstate_S1t:
	.set ___PA___,1
	mul.uu	w0,#1,w2
	sub	w2,#5,[w15]
	subb	w3,#0,[w15]
	.set ___BP___,50
	bra	gtu,.L71
	bra	w2
	.align	2
	.set	___PA___,0
.L76:
	bra	.L73
	bra	.L71
	bra	.L74
	bra	.L75
	bra	.L74
	bra	.L75
	.set	___PA___,1
.L74:
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0t),w0
	bra	.L77
.L75:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
.L77:
	mov	w0,[w1+2]
	return	
.L73:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
	mov	w0,[w1+2]
.L71:
	return	
	.size	__fstate_S1t, .-__fstate_S1t
	.align	2
	.type	__fstate_B1t,@function
__fstate_B1t:
	.set ___PA___,1
	sub	w0,#3,[w15]
	.set ___BP___,29
	bra	z,.L81
	sub	w0,#5,[w15]
	.set ___BP___,29
	bra	z,.L81
	cp0	w0
	.set ___BP___,50
	bra	z,.L80
	return	
.L81:
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	bra	.L82
.L80:
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L82:
	mov	w0,[w1+2]
	return	
	.size	__fstate_B1t, .-__fstate_B1t
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
	.type	__LoadSignal,@function
__LoadSignal:
	.set ___PA___,1
	mov.b	_data_buck+1,WREG
	btst	w0,#0
	.set ___BP___,71
	bra	z,.L86
	clr.b	w0
	rcall	_LedBlink
	bra	.L87
.L86:
	mov.b	_data_buck,WREG
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L88
	clr.b	w0
	rcall	_LedOn
	bra	.L87
.L88:
	clr.b	w0
	rcall	_LedOff
.L87:
	mov.b	_data_buck+1,WREG
	btst	w0,#1
	.set ___BP___,71
	bra	z,.L89
	mov.b	#3,w0
	rcall	_LedBlink
	bra	.L90
.L89:
	mov.b	_data_buck,WREG
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L91
	mov.b	#3,w0
	rcall	_LedOn
	bra	.L90
.L91:
	mov.b	#3,w0
	rcall	_LedOff
.L90:
	mov.b	_data_buck+1,WREG
	btst	w0,#2
	.set ___BP___,71
	bra	z,.L92
	mov.b	#6,w0
	rcall	_LedBlink
	bra	.L93
.L92:
	mov.b	_data_buck,WREG
	btst	w0,#2
	.set ___BP___,50
	bra	z,.L94
	mov.b	#6,w0
	rcall	_LedOn
	bra	.L93
.L94:
	mov.b	#6,w0
	rcall	_LedOff
.L93:
	mov.b	_data_boost+1,WREG
	btst	w0,#0
	.set ___BP___,71
	bra	z,.L95
	mov.b	#1,w0
	rcall	_LedBlink
	bra	.L96
.L95:
	mov.b	_data_boost,WREG
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L97
	mov.b	#1,w0
	rcall	_LedOn
	bra	.L96
.L97:
	mov.b	#1,w0
	rcall	_LedOff
.L96:
	mov.b	_data_boost+1,WREG
	btst	w0,#1
	.set ___BP___,71
	bra	z,.L98
	mov.b	#4,w0
	rcall	_LedBlink
	bra	.L99
.L98:
	mov.b	_data_boost,WREG
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L100
	mov.b	#4,w0
	rcall	_LedOn
	bra	.L99
.L100:
	mov.b	#4,w0
	rcall	_LedOff
.L99:
	mov.b	_data_boost+1,WREG
	btst	w0,#2
	.set ___BP___,79
	bra	z,.L101
	mov.b	#7,w0
	bra	_LedBlink
.L101:
	mov.b	_data_boost,WREG
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L103
	mov.b	#7,w0
	bra	_LedOn
.L103:
	mov.b	#7,w0
	bra	_LedOff
	.size	__LoadSignal, .-__LoadSignal
	.align	2
	.global	_LoadsInit	; export
	.type	_LoadsInit,@function
_LoadsInit:
	.set ___PA___,1
	rcall	_INTERRUPT_GlobalDisable
	clr.b	_data_buck
	clr.b	_data_buck+1
	mov	#handle(__fstate_S0),w0
	mov	w0,_data_buck+2
	bclr.b	_LATCbits,#0
	bclr.b	_LATCbits,#1
	bclr.b	_LATCbits,#2
	clr.b	_data_boost
	clr.b	_data_boost+1
	mov	w0,_data_boost+2
	bclr.b	_LATAbits,#7
	bclr.b	_LATBbits+1,#6
	bclr.b	_LATBbits+1,#7
	rcall	_INTERRUPT_GlobalEnable
	bra	__LoadSignal
	.set ___PA___,0
	.size	_LoadsInit, .-_LoadsInit
	.align	2
	.global	_LoadsTask	; export
	.type	_LoadsTask,@function
_LoadsTask:
	.set ___PA___,1
	cp0.b	_toggle_bit.4316
	.set ___BP___,61
	bra	z,.L106
	mov.b	_data_buck,WREG
	mov	#_data_buck+1,w1
	mov.b	[w1],w1
	ior.b	w1,w0,w0
	rcall	__LoadSetBuck
	mov.b	_data_boost,WREG
	mov	#_data_boost+1,w1
	mov.b	[w1],w1
	ior.b	w1,w0,w0
	rcall	__LoadSetBoost
	clr.b	_toggle_bit.4316
	return	
.L106:
	mov	#_data_buck,w1
	mov.b	[w1],w1
	mov.b	_data_buck+1,WREG
	com.b	w0,w0
	and.b	w0,w1,w0
	rcall	__LoadSetBuck
	mov	#_data_boost,w1
	mov.b	[w1],w1
	mov.b	_data_boost+1,WREG
	com.b	w0,w0
	and.b	w0,w1,w0
	rcall	__LoadSetBoost
	mov.b	#1,w0
	mov.b	WREG,_toggle_bit.4316
	return	
	.size	_LoadsTask, .-_LoadsTask
	.align	2
	.global	_LoadsGetStatus	; export
	.type	_LoadsGetStatus,@function
_LoadsGetStatus:
	.set ___PA___,1
	mov	w8,[w15++]
	rcall	_INTERRUPT_GlobalDisable
	mov	#_data_buck,w8
	mov.b	[w8],w8
	mov.b	_data_buck+1,WREG
	and	w0,#7,w0
	sl	w0,#4,w0
	and	w8,#7,w8
	mov	#_data_boost,w1
	mov.b	[w1],w1
	and	w1,#7,w1
	sl	w1,#8,w1
	ior	w0,w8,w8
	mov.b	_data_boost+1,WREG
	and	w0,#7,w0
	sl	w0,#12,w0
	ior	w1,w8,w8
	ior	w0,w8,w8
	rcall	_INTERRUPT_GlobalEnable
	mov	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_LoadsGetStatus, .-_LoadsGetStatus
	.align	2
	.global	_LoadsStateMachine	; export
	.type	_LoadsStateMachine,@function
_LoadsStateMachine:
	.set ___PA___,1
	mov	w8,[w15++]
	mov	w0,w8
	sub	w8,#5,[w15]
	.set ___BP___,50
	bra	gtu,.L110
	mov	#1,w0
	sl	w0,w8,w0
	mov	w0,w1
	and	#48,w1
	.set ___BP___,50
	bra	nz,.L113
	and	w0,#12,w1
	.set ___BP___,50
	bra	nz,.L112
	and	w0,#3,w0
	.set ___BP___,50
	bra	z,.L110
	rcall	_INTERRUPT_GlobalDisable
	mov	#_data_buck,w1
	mov	w8,w0
	mov	_data_buck+2,w2
	call	w2
	rcall	_INTERRUPT_GlobalEnable
	bra	.L113
.L112:
	rcall	_INTERRUPT_GlobalDisable
	mov	#_data_buck,w1
	mov	w8,w0
	mov	_data_buck+2,w2
	bra	.L114
.L113:
	rcall	_INTERRUPT_GlobalDisable
	mov	#_data_boost,w1
	mov	w8,w0
	mov	_data_boost+2,w2
.L114:
	call	w2
	rcall	_INTERRUPT_GlobalEnable
.L110:
	rcall	__LoadSignal
	mov	[--w15],w8
	return	
	.set ___PA___,0
	.size	_LoadsStateMachine, .-_LoadsStateMachine
	.global	_fstates	; export
	.section	.const,psv,page
	.align	2
	.type	_fstates,@object
	.size	_fstates, 20
_fstates:
	.word	handle(__fstate_S0)
	.word	handle(__fstate_S1)
	.word	handle(__fstate_S2)
	.word	handle(__fstate_S3)
	.word	handle(__fstate_B1)
	.word	handle(__fstate_B2)
	.word	handle(__fstate_B3)
	.word	handle(__fstate_S0t)
	.word	handle(__fstate_S1t)
	.word	handle(__fstate_B1t)
	.global	_stills	; export
	.type	_stills,@object
	.size	_stills, 10
_stills:
	.byte 0
	.byte 1
	.byte 3
	.byte 7
	.byte 1
	.byte 3
	.byte 1
	.byte 0
	.byte 1
	.byte 1
	.global	_blinks	; export
	.type	_blinks,@object
	.size	_blinks, 10
_blinks:
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 2
	.byte 4
	.byte 6
	.byte 0
	.byte 0
	.byte 2
	.section	.nbss,bss,near
	.type	_data_buck,@object
	.global	_data_buck
	.align	2
_data_buck:	.space	4
	.type	_data_boost,@object
	.global	_data_boost
	.align	2
_data_boost:	.space	4
	.type	_toggle_bit.4316,@object
	.size	_toggle_bit.4316, 1
_toggle_bit.4316:
	.skip	1



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
