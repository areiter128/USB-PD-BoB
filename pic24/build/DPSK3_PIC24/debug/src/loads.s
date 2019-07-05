	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\loads.c"
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
	.type	__LoadSetBuck,@function
__LoadSetBuck:
.LFB3:
	.file 1 "src/loads.c"
	.loc 1 132 0
	.set ___PA___,1
	.loc 1 133 0
	ze	w0,w0
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L2
	.loc 1 134 0
	bset.b	_LATCbits,#0
	bra	.L3
.L2:
	.loc 1 136 0
	bclr.b	_LATCbits,#0
.L3:
	.loc 1 137 0
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L4
	.loc 1 138 0
	bset.b	_LATCbits,#1
	bra	.L5
.L4:
	.loc 1 140 0
	bclr.b	_LATCbits,#1
.L5:
	.loc 1 141 0
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L6
	.loc 1 142 0
	bset.b	_LATCbits,#2
	return	
.L6:
	.loc 1 144 0
	bclr.b	_LATCbits,#2
	return	
.LFE3:
	.size	__LoadSetBuck, .-__LoadSetBuck
	.align	2
	.type	__LoadSetBoost,@function
__LoadSetBoost:
.LFB4:
	.loc 1 149 0
	.set ___PA___,1
	.loc 1 150 0
	ze	w0,w0
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L9
	.loc 1 151 0
	bset.b	_LATAbits,#7
	bra	.L10
.L9:
	.loc 1 153 0
	bclr.b	_LATAbits,#7
.L10:
	.loc 1 154 0
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L11
	.loc 1 155 0
	bset.b	_LATBbits+1,#6
	bra	.L12
.L11:
	.loc 1 157 0
	bclr.b	_LATBbits+1,#6
.L12:
	.loc 1 158 0
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L13
	.loc 1 159 0
	bset.b	_LATBbits+1,#7
	return	
.L13:
	.loc 1 161 0
	bclr.b	_LATBbits+1,#7
	return	
.LFE4:
	.size	__LoadSetBoost, .-__LoadSetBoost
	.align	2
	.type	__fstate_S0,@function
__fstate_S0:
.LFB9:
	.loc 1 296 0
	.set ___PA___,1
	.loc 1 298 0
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
	.loc 1 301 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
	bra	.L21
.L19:
	.loc 1 303 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L21:
	mov	w0,[w1+2]
	return	
.L17:
	.loc 1 304 0
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0t),w0
	mov	w0,[w1+2]
.L15:
	return	
.LFE9:
	.size	__fstate_S0, .-__fstate_S0
	.align	2
	.type	__fstate_S1,@function
__fstate_S1:
.LFB10:
	.loc 1 310 0
	.set ___PA___,1
	.loc 1 312 0
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
	.loc 1 315 0
	mov.b	#3,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S2),w0
	bra	.L28
.L26:
	.loc 1 317 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L28:
	mov	w0,[w1+2]
	return	
.L24:
	.loc 1 318 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L22:
	return	
.LFE10:
	.size	__fstate_S1, .-__fstate_S1
	.align	2
	.type	__fstate_S2,@function
__fstate_S2:
.LFB11:
	.loc 1 324 0
	.set ___PA___,1
	.loc 1 326 0
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
	.loc 1 329 0
	mov.b	#7,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S3),w0
	bra	.L35
.L33:
	.loc 1 331 0
	mov.b	#3,w0
	mov.b	w0,[w1]
	mov.b	#4,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B2),w0
.L35:
	mov	w0,[w1+2]
	return	
.L31:
	.loc 1 332 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L29:
	return	
.LFE11:
	.size	__fstate_S2, .-__fstate_S2
	.align	2
	.type	__fstate_S3,@function
__fstate_S3:
.LFB12:
	.loc 1 338 0
	.set ___PA___,1
	.loc 1 340 0
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
	.loc 1 343 0
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0),w0
	bra	.L42
.L40:
	.loc 1 345 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#6,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B3),w0
.L42:
	mov	w0,[w1+2]
	return	
.L38:
	.loc 1 346 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	mov	w0,[w1+2]
.L36:
	return	
.LFE12:
	.size	__fstate_S3, .-__fstate_S3
	.align	2
	.type	__fstate_B1,@function
__fstate_B1:
.LFB13:
	.loc 1 352 0
	.set ___PA___,1
	.loc 1 354 0
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
	.loc 1 357 0
	mov.b	#3,w0
	mov.b	w0,[w1]
	mov.b	#4,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B2),w0
	bra	.L49
.L47:
	.loc 1 359 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
.L49:
	mov	w0,[w1+2]
	return	
.L45:
	.loc 1 360 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L43:
	return	
.LFE13:
	.size	__fstate_B1, .-__fstate_B1
	.align	2
	.type	__fstate_B2,@function
__fstate_B2:
.LFB14:
	.loc 1 366 0
	.set ___PA___,1
	.loc 1 368 0
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
	.loc 1 371 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#6,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B3),w0
	bra	.L56
.L54:
	.loc 1 373 0
	mov.b	#3,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S2),w0
.L56:
	mov	w0,[w1+2]
	return	
.L52:
	.loc 1 374 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L50:
	return	
.LFE14:
	.size	__fstate_B2, .-__fstate_B2
	.align	2
	.type	__fstate_B3,@function
__fstate_B3:
.LFB15:
	.loc 1 380 0
	.set ___PA___,1
	.loc 1 382 0
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
	.loc 1 385 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
	bra	.L63
.L61:
	.loc 1 387 0
	mov.b	#7,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S3),w0
.L63:
	mov	w0,[w1+2]
	return	
.L59:
	.loc 1 388 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
	mov	w0,[w1+2]
.L57:
	return	
.LFE15:
	.size	__fstate_B3, .-__fstate_B3
	.align	2
	.type	__fstate_S0t,@function
__fstate_S0t:
.LFB16:
	.loc 1 394 0
	.set ___PA___,1
	.loc 1 396 0
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
	.loc 1 399 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	bra	.L70
.L68:
	.loc 1 401 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
.L70:
	mov	w0,[w1+2]
	return	
.L66:
	.loc 1 402 0
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0),w0
	mov	w0,[w1+2]
.L64:
	return	
.LFE16:
	.size	__fstate_S0t, .-__fstate_S0t
	.align	2
	.type	__fstate_S1t,@function
__fstate_S1t:
.LFB17:
	.loc 1 408 0
	.set ___PA___,1
	.loc 1 410 0
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
	.loc 1 413 0
	clr.b	[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S0t),w0
	bra	.L77
.L75:
	.loc 1 415 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1t),w0
.L77:
	mov	w0,[w1+2]
	return	
.L73:
	.loc 1 416 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1),w0
	mov	w0,[w1+2]
.L71:
	return	
.LFE17:
	.size	__fstate_S1t, .-__fstate_S1t
	.align	2
	.type	__fstate_B1t,@function
__fstate_B1t:
.LFB18:
	.loc 1 422 0
	.set ___PA___,1
	.loc 1 424 0
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
	.loc 1 427 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	clr.b	w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_S1t),w0
	bra	.L82
.L80:
	.loc 1 428 0
	mov.b	#1,w0
	mov.b	w0,[w1]
	mov.b	#2,w0
	mov.b	w0,[w1+1]
	mov	#handle(__fstate_B1),w0
.L82:
	mov	w0,[w1+2]
	return	
.LFE18:
	.size	__fstate_B1t, .-__fstate_B1t
	.align	2
	.type	_INTERRUPT_GlobalDisable,@function
_INTERRUPT_GlobalDisable:
.LFB1:
	.file 2 "mcc_generated_files/interrupt_manager.h"
	.loc 2 136 0
	.set ___PA___,1
	.loc 2 137 0
	disi	#16383
	.loc 2 138 0
	return	
	.set ___PA___,0
.LFE1:
	.size	_INTERRUPT_GlobalDisable, .-_INTERRUPT_GlobalDisable
	.align	2
	.type	_INTERRUPT_GlobalEnable,@function
_INTERRUPT_GlobalEnable:
.LFB0:
	.loc 2 105 0
	.set ___PA___,1
	.loc 2 106 0
	disi	#0
	.loc 2 107 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_INTERRUPT_GlobalEnable, .-_INTERRUPT_GlobalEnable
	.align	2
	.type	__LoadSignal,@function
__LoadSignal:
.LFB5:
	.loc 1 166 0
	.set ___PA___,1
	.loc 1 167 0
	mov.b	_data_buck+1,WREG
	btst	w0,#0
	.set ___BP___,71
	bra	z,.L86
	.loc 1 168 0
	clr.b	w0
	rcall	_LedBlink
	bra	.L87
.L86:
	.loc 1 169 0
	mov.b	_data_buck,WREG
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L88
	.loc 1 170 0
	clr.b	w0
	rcall	_LedOn
	bra	.L87
.L88:
	.loc 1 172 0
	clr.b	w0
	rcall	_LedOff
.L87:
	.loc 1 174 0
	mov.b	_data_buck+1,WREG
	btst	w0,#1
	.set ___BP___,71
	bra	z,.L89
	.loc 1 175 0
	mov.b	#3,w0
	rcall	_LedBlink
	bra	.L90
.L89:
	.loc 1 176 0
	mov.b	_data_buck,WREG
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L91
	.loc 1 177 0
	mov.b	#3,w0
	rcall	_LedOn
	bra	.L90
.L91:
	.loc 1 179 0
	mov.b	#3,w0
	rcall	_LedOff
.L90:
	.loc 1 181 0
	mov.b	_data_buck+1,WREG
	btst	w0,#2
	.set ___BP___,71
	bra	z,.L92
	.loc 1 182 0
	mov.b	#6,w0
	rcall	_LedBlink
	bra	.L93
.L92:
	.loc 1 183 0
	mov.b	_data_buck,WREG
	btst	w0,#2
	.set ___BP___,50
	bra	z,.L94
	.loc 1 184 0
	mov.b	#6,w0
	rcall	_LedOn
	bra	.L93
.L94:
	.loc 1 186 0
	mov.b	#6,w0
	rcall	_LedOff
.L93:
	.loc 1 188 0
	mov.b	_data_boost+1,WREG
	btst	w0,#0
	.set ___BP___,71
	bra	z,.L95
	.loc 1 189 0
	mov.b	#1,w0
	rcall	_LedBlink
	bra	.L96
.L95:
	.loc 1 190 0
	mov.b	_data_boost,WREG
	btst	w0,#0
	.set ___BP___,50
	bra	z,.L97
	.loc 1 191 0
	mov.b	#1,w0
	rcall	_LedOn
	bra	.L96
.L97:
	.loc 1 193 0
	mov.b	#1,w0
	rcall	_LedOff
.L96:
	.loc 1 195 0
	mov.b	_data_boost+1,WREG
	btst	w0,#1
	.set ___BP___,71
	bra	z,.L98
	.loc 1 196 0
	mov.b	#4,w0
	rcall	_LedBlink
	bra	.L99
.L98:
	.loc 1 197 0
	mov.b	_data_boost,WREG
	btst	w0,#1
	.set ___BP___,50
	bra	z,.L100
	.loc 1 198 0
	mov.b	#4,w0
	rcall	_LedOn
	bra	.L99
.L100:
	.loc 1 200 0
	mov.b	#4,w0
	rcall	_LedOff
.L99:
	.loc 1 202 0
	mov.b	_data_boost+1,WREG
	btst	w0,#2
	.set ___BP___,79
	bra	z,.L101
	.loc 1 203 0
	mov.b	#7,w0
	bra	_LedBlink
.L101:
	.loc 1 204 0
	mov.b	_data_boost,WREG
	btst	w0,#2
	.set ___BP___,61
	bra	z,.L103
	.loc 1 205 0
	mov.b	#7,w0
	bra	_LedOn
.L103:
	.loc 1 207 0
	mov.b	#7,w0
	bra	_LedOff
.LFE5:
	.size	__LoadSignal, .-__LoadSignal
	.align	2
	.global	_LoadsInit	; export
	.type	_LoadsInit,@function
_LoadsInit:
.LFB2:
	.loc 1 109 0
	.set ___PA___,1
	.loc 1 111 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 114 0
	clr.b	_data_buck
	clr.b	_data_buck+1
	mov	#handle(__fstate_S0),w0
	mov	w0,_data_buck+2
	.loc 1 115 0
	bclr.b	_LATCbits,#0
	.loc 1 116 0
	bclr.b	_LATCbits,#1
	.loc 1 117 0
	bclr.b	_LATCbits,#2
	.loc 1 121 0
	clr.b	_data_boost
	clr.b	_data_boost+1
	mov	w0,_data_boost+2
	.loc 1 122 0
	bclr.b	_LATAbits,#7
	.loc 1 123 0
	bclr.b	_LATBbits+1,#6
	.loc 1 124 0
	bclr.b	_LATBbits+1,#7
	.loc 1 125 0
	rcall	_INTERRUPT_GlobalEnable
	.loc 1 127 0
	bra	__LoadSignal
	.loc 1 128 0
	.set ___PA___,0
.LFE2:
	.size	_LoadsInit, .-_LoadsInit
	.align	2
	.global	_LoadsTask	; export
	.type	_LoadsTask,@function
_LoadsTask:
.LFB6:
	.loc 1 212 0
	.set ___PA___,1
	.loc 1 215 0
	cp0.b	_toggle_bit.4316
	.set ___BP___,61
	bra	z,.L106
	.loc 1 217 0
	mov.b	_data_buck,WREG
	mov	#_data_buck+1,w1
	mov.b	[w1],w1
	ior.b	w1,w0,w0
	rcall	__LoadSetBuck
	.loc 1 218 0
	mov.b	_data_boost,WREG
	mov	#_data_boost+1,w1
	mov.b	[w1],w1
	ior.b	w1,w0,w0
	rcall	__LoadSetBoost
	.loc 1 219 0
	clr.b	_toggle_bit.4316
	return	
.L106:
	.loc 1 223 0
	mov	#_data_buck,w1
	mov.b	[w1],w1
	mov.b	_data_buck+1,WREG
	com.b	w0,w0
	and.b	w0,w1,w0
	rcall	__LoadSetBuck
	.loc 1 224 0
	mov	#_data_boost,w1
	mov.b	[w1],w1
	mov.b	_data_boost+1,WREG
	com.b	w0,w0
	and.b	w0,w1,w0
	rcall	__LoadSetBoost
	.loc 1 225 0
	mov.b	#1,w0
	mov.b	WREG,_toggle_bit.4316
	return	
.LFE6:
	.size	_LoadsTask, .-_LoadsTask
	.align	2
	.global	_LoadsGetStatus	; export
	.type	_LoadsGetStatus,@function
_LoadsGetStatus:
.LFB7:
	.loc 1 230 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI0:
	.loc 1 232 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 233 0
	mov	#_data_buck,w8
	mov.b	[w8],w8
	.loc 1 234 0
	mov.b	_data_buck+1,WREG
	and	w0,#7,w0
	sl	w0,#4,w0
	and	w8,#7,w8
	.loc 1 235 0
	mov	#_data_boost,w1
	mov.b	[w1],w1
	and	w1,#7,w1
	sl	w1,#8,w1
	ior	w0,w8,w8
	.loc 1 236 0
	mov.b	_data_boost+1,WREG
	and	w0,#7,w0
	sl	w0,#12,w0
	ior	w1,w8,w8
	ior	w0,w8,w8
	.loc 1 237 0
	rcall	_INTERRUPT_GlobalEnable
	.loc 1 239 0
	mov	w8,w0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE7:
	.size	_LoadsGetStatus, .-_LoadsGetStatus
	.align	2
	.global	_LoadsStateMachine	; export
	.type	_LoadsStateMachine,@function
_LoadsStateMachine:
.LFB8:
	.loc 1 242 0
	.set ___PA___,1
	mov	w8,[w15++]
.LCFI1:
	mov	w0,w8
	.loc 1 243 0
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
	.loc 1 247 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 248 0
	mov	#_data_buck,w1
	mov	w8,w0
	mov	_data_buck+2,w2
	call	w2
	.loc 1 249 0
	rcall	_INTERRUPT_GlobalEnable
	bra	.L113
.L112:
	.loc 1 256 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 257 0
	mov	#_data_buck,w1
	mov	w8,w0
	mov	_data_buck+2,w2
	bra	.L114
.L113:
	.loc 1 262 0
	rcall	_INTERRUPT_GlobalDisable
	.loc 1 263 0
	mov	#_data_boost,w1
	mov	w8,w0
	mov	_data_boost+2,w2
.L114:
	call	w2
	.loc 1 264 0
	rcall	_INTERRUPT_GlobalEnable
.L110:
	.loc 1 268 0
	rcall	__LoadSignal
	.loc 1 269 0
	mov	[--w15],w8
	return	
	.set ___PA___,0
.LFE8:
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
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.align	4
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.align	4
.LEFDE20:
.LSFDE22:
	.4byte	.LEFDE22-.LASFDE22
.LASFDE22:
	.4byte	.Lframe0
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.align	4
.LEFDE22:
.LSFDE24:
	.4byte	.LEFDE24-.LASFDE24
.LASFDE24:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.align	4
.LEFDE24:
.LSFDE26:
	.4byte	.LEFDE26-.LASFDE26
.LASFDE26:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE26:
.LSFDE28:
	.4byte	.LEFDE28-.LASFDE28
.LASFDE28:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE28:
.LSFDE30:
	.4byte	.LEFDE30-.LASFDE30
.LASFDE30:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.align	4
.LEFDE30:
.LSFDE32:
	.4byte	.LEFDE32-.LASFDE32
.LASFDE32:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE32:
.LSFDE34:
	.4byte	.LEFDE34-.LASFDE34
.LASFDE34:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.byte	0x4
	.4byte	.LCFI0-.LFB7
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE34:
.LSFDE36:
	.4byte	.LEFDE36-.LASFDE36
.LASFDE36:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.byte	0x4
	.4byte	.LCFI1-.LFB8
	.byte	0x13
	.sleb128 -3
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE36:
	.section	.text,code
.Letext0:
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 4 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.file 5 "h/loads.h"
	.file 6 "../common/h/proto_data.h"
	.section	.debug_info,info
	.4byte	0xc77
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"src/loads.c"
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
	.byte	0x3
	.byte	0x2b
	.4byte	0xea
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
	.asciz	"tagLATABITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x6df
	.4byte	0x215
	.uleb128 0x5
	.asciz	"LATA0"
	.byte	0x4
	.2byte	0x6e0
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA1"
	.byte	0x4
	.2byte	0x6e1
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA2"
	.byte	0x4
	.2byte	0x6e2
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA3"
	.byte	0x4
	.2byte	0x6e3
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA4"
	.byte	0x4
	.2byte	0x6e4
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA7"
	.byte	0x4
	.2byte	0x6e6
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA8"
	.byte	0x4
	.2byte	0x6e7
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA9"
	.byte	0x4
	.2byte	0x6e8
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATA10"
	.byte	0x4
	.2byte	0x6e9
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"LATABITS"
	.byte	0x4
	.2byte	0x6ea
	.4byte	0x14a
	.uleb128 0x4
	.asciz	"tagLATBBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x72b
	.4byte	0x382
	.uleb128 0x5
	.asciz	"LATB0"
	.byte	0x4
	.2byte	0x72c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB1"
	.byte	0x4
	.2byte	0x72d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB2"
	.byte	0x4
	.2byte	0x72e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB3"
	.byte	0x4
	.2byte	0x72f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB4"
	.byte	0x4
	.2byte	0x730
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB5"
	.byte	0x4
	.2byte	0x731
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB6"
	.byte	0x4
	.2byte	0x732
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB7"
	.byte	0x4
	.2byte	0x733
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB8"
	.byte	0x4
	.2byte	0x734
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB9"
	.byte	0x4
	.2byte	0x735
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB10"
	.byte	0x4
	.2byte	0x736
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB11"
	.byte	0x4
	.2byte	0x737
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB12"
	.byte	0x4
	.2byte	0x738
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB13"
	.byte	0x4
	.2byte	0x739
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB14"
	.byte	0x4
	.2byte	0x73a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATB15"
	.byte	0x4
	.2byte	0x73b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"LATBBITS"
	.byte	0x4
	.2byte	0x73c
	.4byte	0x226
	.uleb128 0x4
	.asciz	"tagLATCBITS"
	.byte	0x2
	.byte	0x4
	.2byte	0x777
	.4byte	0x471
	.uleb128 0x5
	.asciz	"LATC0"
	.byte	0x4
	.2byte	0x778
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC1"
	.byte	0x4
	.2byte	0x779
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC2"
	.byte	0x4
	.2byte	0x77a
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC3"
	.byte	0x4
	.2byte	0x77b
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC4"
	.byte	0x4
	.2byte	0x77c
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC5"
	.byte	0x4
	.2byte	0x77d
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC6"
	.byte	0x4
	.2byte	0x77e
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC7"
	.byte	0x4
	.2byte	0x77f
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC8"
	.byte	0x4
	.2byte	0x780
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"LATC9"
	.byte	0x4
	.2byte	0x781
	.4byte	0xfb
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x6
	.asciz	"LATCBITS"
	.byte	0x4
	.2byte	0x782
	.4byte	0x393
	.uleb128 0x7
	.byte	0x2
	.byte	0x5
	.byte	0x68
	.4byte	0x508
	.uleb128 0x8
	.asciz	"LOADS_THERM_SAFE"
	.sleb128 0
	.uleb128 0x8
	.asciz	"LOADS_THERM_ALERT"
	.sleb128 1
	.uleb128 0x8
	.asciz	"LOADS_SBUTTON_BUCK"
	.sleb128 2
	.uleb128 0x8
	.asciz	"LOADS_LBUTTON_BUCK"
	.sleb128 3
	.uleb128 0x8
	.asciz	"LOADS_SBUTTON_BOOST"
	.sleb128 4
	.uleb128 0x8
	.asciz	"LOADS_LBUTTON_BOOST"
	.sleb128 5
	.byte	0x0
	.uleb128 0x3
	.asciz	"loads_event_t"
	.byte	0x5
	.byte	0x6f
	.4byte	0x482
	.uleb128 0x9
	.byte	0x2
	.byte	0x6
	.byte	0x23
	.4byte	0x588
	.uleb128 0xa
	.asciz	"buck_still"
	.byte	0x6
	.byte	0x24
	.4byte	0xdb
	.byte	0x1
	.byte	0x3
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xa
	.asciz	"buck_blink"
	.byte	0x6
	.byte	0x26
	.4byte	0xdb
	.byte	0x1
	.byte	0x3
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xa
	.asciz	"boost_still"
	.byte	0x6
	.byte	0x28
	.4byte	0xdb
	.byte	0x1
	.byte	0x3
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0xa
	.asciz	"boost_blink"
	.byte	0x6
	.byte	0x2a
	.4byte	0xdb
	.byte	0x1
	.byte	0x3
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.byte	0x0
	.uleb128 0xb
	.byte	0x2
	.byte	0x6
	.byte	0x22
	.4byte	0x5a1
	.uleb128 0xc
	.4byte	0x51d
	.uleb128 0xd
	.asciz	"u16"
	.byte	0x6
	.byte	0x2d
	.4byte	0xfb
	.byte	0x0
	.uleb128 0x3
	.asciz	"proto_ldst_t"
	.byte	0x6
	.byte	0x2e
	.4byte	0x588
	.uleb128 0x3
	.asciz	"sm_state_t"
	.byte	0x1
	.byte	0x1f
	.4byte	0x5c7
	.uleb128 0xe
	.byte	0x2
	.4byte	0x5cd
	.uleb128 0xf
	.byte	0x1
	.4byte	0x5de
	.uleb128 0x10
	.4byte	0x508
	.uleb128 0x10
	.4byte	0x5de
	.byte	0x0
	.uleb128 0x11
	.byte	0x2
	.uleb128 0x9
	.byte	0x4
	.byte	0x1
	.byte	0x21
	.4byte	0x621
	.uleb128 0x12
	.asciz	"set_still"
	.byte	0x1
	.byte	0x22
	.4byte	0x621
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x12
	.asciz	"set_blink"
	.byte	0x1
	.byte	0x23
	.4byte	0x621
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x12
	.asciz	"state"
	.byte	0x1
	.byte	0x24
	.4byte	0x5b5
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0x0
	.uleb128 0x13
	.4byte	0xdb
	.uleb128 0x3
	.asciz	"sm_data_t"
	.byte	0x1
	.byte	0x25
	.4byte	0x5e0
	.uleb128 0x7
	.byte	0x2
	.byte	0x1
	.byte	0x5b
	.4byte	0x6b1
	.uleb128 0x8
	.asciz	"state_S0"
	.sleb128 0
	.uleb128 0x8
	.asciz	"state_S1"
	.sleb128 1
	.uleb128 0x8
	.asciz	"state_S2"
	.sleb128 2
	.uleb128 0x8
	.asciz	"state_S3"
	.sleb128 3
	.uleb128 0x8
	.asciz	"state_B1"
	.sleb128 4
	.uleb128 0x8
	.asciz	"state_B2"
	.sleb128 5
	.uleb128 0x8
	.asciz	"state_B3"
	.sleb128 6
	.uleb128 0x8
	.asciz	"state_S0t"
	.sleb128 7
	.uleb128 0x8
	.asciz	"state_S1t"
	.sleb128 8
	.uleb128 0x8
	.asciz	"state_B1t"
	.sleb128 9
	.byte	0x0
	.uleb128 0x14
	.asciz	"_LoadSetBuck"
	.byte	0x1
	.byte	0x83
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.4byte	0x6e2
	.uleb128 0x15
	.asciz	"setting"
	.byte	0x1
	.byte	0x83
	.4byte	0xdb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x14
	.asciz	"_LoadSetBoost"
	.byte	0x1
	.byte	0x94
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0x714
	.uleb128 0x15
	.asciz	"setting"
	.byte	0x1
	.byte	0x94
	.4byte	0xdb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_S0"
	.byte	0x1
	.2byte	0x127
	.byte	0x1
	.4byte	.LFB9
	.4byte	.LFE9
	.byte	0x1
	.byte	0x5f
	.4byte	0x75d
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x127
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x127
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x129
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0xe
	.byte	0x2
	.4byte	0x626
	.uleb128 0x16
	.asciz	"_fstate_S1"
	.byte	0x1
	.2byte	0x135
	.byte	0x1
	.4byte	.LFB10
	.4byte	.LFE10
	.byte	0x1
	.byte	0x5f
	.4byte	0x7ac
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x135
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x135
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x137
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_S2"
	.byte	0x1
	.2byte	0x143
	.byte	0x1
	.4byte	.LFB11
	.4byte	.LFE11
	.byte	0x1
	.byte	0x5f
	.4byte	0x7f5
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x143
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x143
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x145
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_S3"
	.byte	0x1
	.2byte	0x151
	.byte	0x1
	.4byte	.LFB12
	.4byte	.LFE12
	.byte	0x1
	.byte	0x5f
	.4byte	0x83e
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x151
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x151
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x153
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_B1"
	.byte	0x1
	.2byte	0x15f
	.byte	0x1
	.4byte	.LFB13
	.4byte	.LFE13
	.byte	0x1
	.byte	0x5f
	.4byte	0x887
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x15f
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x15f
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x161
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_B2"
	.byte	0x1
	.2byte	0x16d
	.byte	0x1
	.4byte	.LFB14
	.4byte	.LFE14
	.byte	0x1
	.byte	0x5f
	.4byte	0x8d0
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x16d
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x16d
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x16f
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_B3"
	.byte	0x1
	.2byte	0x17b
	.byte	0x1
	.4byte	.LFB15
	.4byte	.LFE15
	.byte	0x1
	.byte	0x5f
	.4byte	0x919
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x17b
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x17b
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x17d
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_S0t"
	.byte	0x1
	.2byte	0x189
	.byte	0x1
	.4byte	.LFB16
	.4byte	.LFE16
	.byte	0x1
	.byte	0x5f
	.4byte	0x963
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x189
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x189
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x18b
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_S1t"
	.byte	0x1
	.2byte	0x197
	.byte	0x1
	.4byte	.LFB17
	.4byte	.LFE17
	.byte	0x1
	.byte	0x5f
	.4byte	0x9ad
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x197
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x197
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x19
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x199
	.4byte	0x75d
	.byte	0x1
	.byte	0x51
	.byte	0x0
	.uleb128 0x16
	.asciz	"_fstate_B1t"
	.byte	0x1
	.2byte	0x1a5
	.byte	0x1
	.4byte	.LFB18
	.4byte	.LFE18
	.byte	0x1
	.byte	0x5f
	.4byte	0x9f5
	.uleb128 0x17
	.4byte	.LASF0
	.byte	0x1
	.2byte	0x1a5
	.4byte	0x508
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"ptr"
	.byte	0x1
	.2byte	0x1a5
	.4byte	0x5de
	.byte	0x1
	.byte	0x51
	.uleb128 0x1a
	.4byte	.LASF1
	.byte	0x1
	.2byte	0x1a7
	.4byte	0x75d
	.byte	0x0
	.uleb128 0x1b
	.asciz	"INTERRUPT_GlobalDisable"
	.byte	0x2
	.byte	0x87
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1b
	.asciz	"INTERRUPT_GlobalEnable"
	.byte	0x2
	.byte	0x68
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1b
	.asciz	"_LoadSignal"
	.byte	0x1
	.byte	0xa5
	.byte	0x1
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1c
	.byte	0x1
	.asciz	"LoadsInit"
	.byte	0x1
	.byte	0x6c
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.4byte	0xa83
	.uleb128 0x1d
	.4byte	.LASF1
	.byte	0x1
	.byte	0x6e
	.4byte	0x75d
	.byte	0x0
	.uleb128 0x1c
	.byte	0x1
	.asciz	"LoadsTask"
	.byte	0x1
	.byte	0xd3
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0xab9
	.uleb128 0x1e
	.asciz	"toggle_bit"
	.byte	0x1
	.byte	0xd6
	.4byte	0xab9
	.byte	0x5
	.byte	0x3
	.4byte	_toggle_bit.4316
	.byte	0x0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x1f
	.byte	0x1
	.asciz	"LoadsGetStatus"
	.byte	0x1
	.byte	0xe5
	.byte	0x1
	.4byte	0xfb
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0xaf7
	.uleb128 0x20
	.asciz	"temp16"
	.byte	0x1
	.byte	0xe7
	.4byte	0x5a1
	.byte	0x0
	.uleb128 0x1c
	.byte	0x1
	.asciz	"LoadsStateMachine"
	.byte	0x1
	.byte	0xf1
	.byte	0x1
	.4byte	.LFB8
	.4byte	.LFE8
	.byte	0x1
	.byte	0x5f
	.4byte	0xb2a
	.uleb128 0x21
	.4byte	.LASF0
	.byte	0x1
	.byte	0xf1
	.4byte	0x508
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x22
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x6eb
	.4byte	0xb38
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.4byte	0x215
	.uleb128 0x22
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x73d
	.4byte	0xb4b
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.4byte	0x382
	.uleb128 0x22
	.4byte	.LASF4
	.byte	0x4
	.2byte	0x783
	.4byte	0xb5e
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.4byte	0x471
	.uleb128 0x23
	.4byte	0x5b5
	.4byte	0xb73
	.uleb128 0x24
	.4byte	0x10b
	.byte	0x9
	.byte	0x0
	.uleb128 0x25
	.asciz	"fstates"
	.byte	0x1
	.byte	0x32
	.4byte	0xb84
	.byte	0x1
	.byte	0x1
	.uleb128 0x26
	.4byte	0xb63
	.uleb128 0x23
	.4byte	0xdb
	.4byte	0xb99
	.uleb128 0x24
	.4byte	0x10b
	.byte	0x9
	.byte	0x0
	.uleb128 0x25
	.asciz	"stills"
	.byte	0x1
	.byte	0x3f
	.4byte	0xba9
	.byte	0x1
	.byte	0x1
	.uleb128 0x26
	.4byte	0xb89
	.uleb128 0x25
	.asciz	"blinks"
	.byte	0x1
	.byte	0x4c
	.4byte	0xbbe
	.byte	0x1
	.byte	0x1
	.uleb128 0x26
	.4byte	0xb89
	.uleb128 0x27
	.4byte	.LASF5
	.byte	0x1
	.byte	0x68
	.4byte	0x626
	.byte	0x1
	.byte	0x1
	.uleb128 0x27
	.4byte	.LASF6
	.byte	0x1
	.byte	0x68
	.4byte	0x626
	.byte	0x1
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF2
	.byte	0x4
	.2byte	0x6eb
	.4byte	0xb38
	.byte	0x1
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF3
	.byte	0x4
	.2byte	0x73d
	.4byte	0xb4b
	.byte	0x1
	.byte	0x1
	.uleb128 0x22
	.4byte	.LASF4
	.byte	0x4
	.2byte	0x783
	.4byte	0xb5e
	.byte	0x1
	.byte	0x1
	.uleb128 0x28
	.asciz	"fstates"
	.byte	0x1
	.byte	0x32
	.4byte	0xc1d
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_fstates
	.uleb128 0x26
	.4byte	0xb63
	.uleb128 0x28
	.asciz	"stills"
	.byte	0x1
	.byte	0x3f
	.4byte	0xc37
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_stills
	.uleb128 0x26
	.4byte	0xb89
	.uleb128 0x28
	.asciz	"blinks"
	.byte	0x1
	.byte	0x4c
	.4byte	0xc51
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_blinks
	.uleb128 0x26
	.4byte	0xb89
	.uleb128 0x29
	.4byte	.LASF5
	.byte	0x1
	.byte	0x68
	.4byte	0x626
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_data_buck
	.uleb128 0x29
	.4byte	.LASF6
	.byte	0x1
	.byte	0x68
	.4byte	0x626
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	_data_boost
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
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
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x17
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
	.uleb128 0xc
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
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
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x15
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
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x17
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x19
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x1a
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x0
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
	.uleb128 0x1c
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
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x21
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x24
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x25
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x26
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x28
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x29
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x92
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0xc7b
	.4byte	0xa5a
	.asciz	"LoadsInit"
	.4byte	0xa83
	.asciz	"LoadsTask"
	.4byte	0xac2
	.asciz	"LoadsGetStatus"
	.4byte	0xaf7
	.asciz	"LoadsStateMachine"
	.4byte	0xc07
	.asciz	"fstates"
	.4byte	0xc22
	.asciz	"stills"
	.4byte	0xc3c
	.asciz	"blinks"
	.4byte	0xc56
	.asciz	"data_buck"
	.4byte	0xc68
	.asciz	"data_boost"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0xbe
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0xc7b
	.4byte	0xdb
	.asciz	"uint8_t"
	.4byte	0xfb
	.asciz	"uint16_t"
	.4byte	0x14a
	.asciz	"tagLATABITS"
	.4byte	0x215
	.asciz	"LATABITS"
	.4byte	0x226
	.asciz	"tagLATBBITS"
	.4byte	0x382
	.asciz	"LATBBITS"
	.4byte	0x393
	.asciz	"tagLATCBITS"
	.4byte	0x471
	.asciz	"LATCBITS"
	.4byte	0x508
	.asciz	"loads_event_t"
	.4byte	0x5a1
	.asciz	"proto_ldst_t"
	.4byte	0x5b5
	.asciz	"sm_state_t"
	.4byte	0x626
	.asciz	"sm_data_t"
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
	.asciz	"LATAbits"
.LASF6:
	.asciz	"data_boost"
.LASF0:
	.asciz	"event"
.LASF5:
	.asciz	"data_buck"
.LASF1:
	.asciz	"pdata"
.LASF3:
	.asciz	"LATBbits"
.LASF4:
	.asciz	"LATCbits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
