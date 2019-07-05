	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\pin_manager.c"
	.section	.text,code
	.align	2
	.global	_PIN_MANAGER_Initialize	; export
	.type	_PIN_MANAGER_Initialize,@function
_PIN_MANAGER_Initialize:
	.set ___PA___,1
	clr	_LATA
	mov	#96,w0
	mov	w0,_LATB
	clr	_LATC
	mov	#1823,w0
	mov	w0,_TRISA
	mov	#16319,w0
	mov	w0,_TRISB
	mov	#1016,w0
	mov	w0,_TRISC
	clr	_CNPU1
	mov	#26624,w0
	mov	w0,_CNPU2
	clr	_ODCA
	clr	_ODCB
	clr	_ODCC
	mov	#1996,w0
	mov	w0,_AD1PCFG
	mov	#191,w0
	and	_OSCCON,WREG
	mov	#70,w2
	mov	#87,w3
	mov	#_OSCCON,w1
	mov.b	w2,[w1]
	mov.b	w3,[w1]
	mov.b	w0,[w1]
	mov	#-32,w0
	mov	_RPINR18bits,w4
	and	w0,w4,w1
	ior	#5,w1
	mov	w1,_RPINR18bits
	and	_RPOR3bits,WREG
	ior	#3,w0
	mov	w0,_RPOR3bits
	mov	_OSCCON,w0
	bset	w0,#6
	mov	#_OSCCON,w1
	mov.b	w2,[w1]
	mov.b	w3,[w1]
	mov.b	w0,[w1]
	return	
	.set ___PA___,0
	.size	_PIN_MANAGER_Initialize, .-_PIN_MANAGER_Initialize



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
