	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\src\\protocol.c"
	.section	.text,code
	.align	2
	.global	_ProtocolInit	; export
	.type	_ProtocolInit,@function
_ProtocolInit:
	.set ___PA___,1
	clr.b	_tx_flag
	return	
	.set ___PA___,0
	.size	_ProtocolInit, .-_ProtocolInit
	.align	2
	.global	_ProtocolCheck	; export
	.type	_ProtocolCheck,@function
_ProtocolCheck:
	.set ___PA___,1
	lnk	#2
	mov	w8,[w15++]
	mov	w0,w8
	clr.b	w0
	mov.b	w0,[w15-3]
	cp0.b	_WSOF.4685
	.set ___BP___,50
	bra	z,.L3
	rcall	_UART1_ReceiveBufferIsEmpty
	cp0.b	w0
	.set ___BP___,71
	bra	nz,.L4
	rcall	_UART1_Read
	mov.b	#85,w1
	sub.b	w0,w1,[w15]
	.set ___BP___,72
	bra	nz,.L4
	clr.b	_WSOF.4685
	inc.b	_timeout_counter
	bra	.L4
.L3:
	rcall	_UART1_ReceiveBufferSizeGet
	mov.b	#32,w1
	sub.b	w1,w0,w1
	mov.b	w1,[w15-4]
	mov.b	[w15-4],w0
	cp0.b	w0
	.set ___BP___,71
	bra	z,.L4
	mov	#1,w1
	sub	w15,#3,w0
	rcall	_UART1_ReadBuffer
	mov.b	#1,w0
	mov.b	WREG,_WSOF.4685
.L4:
	cp0.b	_timeout_flag
	.set ___BP___,50
	bra	z,.L5
	mov.b	#1,w0
	mov.b	WREG,_WSOF.4685
	clr.b	_timeout_flag
.L5:
	cp0.b	_tx_flag
	.set ___BP___,61
	bra	z,.L6
	clr.b	_tx_flag
	mov.b	#85,w0
	rcall	_UART1_Write
	mov	#4,w1
	mov	w8,w0
	rcall	_UART1_WriteBuffer
.L6:
	mov.b	[w15-3],w0
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
	.size	_ProtocolCheck, .-_ProtocolCheck
	.align	2
	.global	_ProtocolClose	; export
	.type	_ProtocolClose,@function
_ProtocolClose:
	.set ___PA___,1
	clr.b	_tx_flag
.L8:
	rcall	_UART1_TransferStatusGet
	btst	w0,#4
	.set ___BP___,91
	bra	z,.L8
	mov	#13568,w0
	mov	#12,w1
	rcall	___delay32
	bclr.b	_U1STAbits+1,#2
	bclr.b	_U1MODEbits+1,#7
	return	
	.set ___PA___,0
	.size	_ProtocolClose, .-_ProtocolClose
	.align	2
	.global	_ProtocolTick	; export
	.type	_ProtocolTick,@function
_ProtocolTick:
	.set ___PA___,1
	mov.b	_timeout_counter,WREG
	.set ___BP___,50
	bra	z,.L10
	mov.b	#99,w1
	sub.b	w0,w1,[w15]
	.set ___BP___,50
	bra	leu,.L11
	mov.b	#1,w0
	mov.b	WREG,_timeout_flag
	clr.b	_timeout_counter
	bra	.L10
.L11:
	inc.b	w0,w0
	mov.b	WREG,_timeout_counter
.L10:
	inc	_count.4696,WREG
	mov	w0,_count.4696
	mov	#999,w1
	sub	w0,w1,[w15]
	.set ___BP___,39
	bra	leu,.L9
	clr	_count.4696
	mov.b	#1,w0
	mov.b	WREG,_tx_flag
.L9:
	return	
	.size	_ProtocolTick, .-_ProtocolTick
	.section	.nbss,bss,near
	.type	_timeout_counter,@object
	.size	_timeout_counter, 1
_timeout_counter:
	.skip	1
	.type	_timeout_flag,@object
	.size	_timeout_flag, 1
_timeout_flag:
	.skip	1
	.type	_tx_flag,@object
	.size	_tx_flag, 1
_tx_flag:
	.skip	1
	.align	2
	.type	_count.4696,@object
	.size	_count.4696, 2
_count.4696:
	.skip	2
	.section	.ndata,data,near
	.type	_WSOF.4685,@object
	.size	_WSOF.4685, 1
_WSOF.4685:
	.byte 1



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
