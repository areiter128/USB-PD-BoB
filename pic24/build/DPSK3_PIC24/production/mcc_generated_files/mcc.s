	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\mcc.c"
	.section	.text,code
	.align	2
	.global	_OSCILLATOR_Initialize	; export
	.type	_OSCILLATOR_Initialize,@function
_OSCILLATOR_Initialize:
	.set ___PA___,1
	mov	#12288,w0
	mov	w0,_CLKDIV
	clr	_OSCTUN
	mov	#1,w0
	mov	#154,w2
	mov	#120,w1
	mov	#_OSCCON+1,w3
	mov.b	w1,[w3]
	mov.b	w2,[w3]
	mov.b	w0,[w3]
	mov	#87,w2
	mov	#70,w1
	mov	#_OSCCON,w3
	mov.b	w1,[w3]
	mov.b	w2,[w3]
	mov.b	w0,[w3]
.L2:
	btst.b	_OSCCONbits,#0
	.set ___BP___,91
	bra	nz,.L2
	return	
	.set ___PA___,0
	.size	_OSCILLATOR_Initialize, .-_OSCILLATOR_Initialize
	.align	2
	.global	_SYSTEM_Initialize	; export
	.type	_SYSTEM_Initialize,@function
_SYSTEM_Initialize:
	.set ___PA___,1
	rcall	_PIN_MANAGER_Initialize
	rcall	_OSCILLATOR_Initialize
	rcall	_INTERRUPT_Initialize
	rcall	_ADC1_Initialize
	rcall	_UART1_Initialize
	bra	_TMR1_Initialize
	.set ___PA___,0
	.size	_SYSTEM_Initialize, .-_SYSTEM_Initialize



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words
; Configuration word @ 0x0000abfe
	.section	.config_JTAGEN, code, address(0xabfe), keep
__config_JTAGEN:
	.pword	16255
; Configuration word @ 0x0000abfc
	.section	.config_IESO, code, address(0xabfc), keep
__config_IESO:
	.pword	63583

	.set ___PA___,0
	.end
