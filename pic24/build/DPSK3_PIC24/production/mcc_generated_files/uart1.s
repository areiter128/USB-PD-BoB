	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\uart1.c"
	.section	.text,code
	.align	2
	.global	_UART1_Initialize	; export
	.type	_UART1_Initialize,@function
_UART1_Initialize:
	.set ___PA___,1
	mov	#8,w0
	mov	w0,_U1MODE
	clr	_U1STA
	mov	#16,w0
	mov	w0,_U1BRG
	bset.b	_IEC0bits+1,#3
	bset.b	_U1MODEbits+1,#7
	bset.b	_U1STAbits+1,#2
	mov	#_uart1_txByteQ,w0
	mov	w0,_uart1_obj+6
	mov	w0,_uart1_obj+4
	mov	#_uart1_rxByteQ,w0
	mov	w0,_uart1_obj+2
	mov	w0,_uart1_obj
	mov	#_uart1_obj+8,w1
	mov	[w1],w0
	ior	#514,w0
	mov	#-258,w2
	and	w0,w2,[w1]
	return	
	.set ___PA___,0
	.size	_UART1_Initialize, .-_UART1_Initialize
	.section	.isr.text,code,keep
	.align	2
	.global	__U1TXInterrupt	; export
	.type	__U1TXInterrupt,@function
__U1TXInterrupt:
	.set ___PA___,1
	mov.d	w0,[w15++]
	mov	w2,[w15++]
	mov	#512,w0
	mov	#_uart1_obj+8,w1
	and	w0,[w1],w0
	.set ___BP___,61
	bra	z,.L3
	bclr.b	_IEC0bits+1,#4
	bra	.L2
.L3:
	bclr.b	_IFS0bits+1,#4
	mov	_uart1_obj+4,w2
	mov	_uart1_obj+6,w0
	mov	_uart1_obj+8,w1
	lsr	w1,#8,w1
	and.b	w1,#1,w1
	bra	.L5
.L7:
	ze	[w0++],w1
	mov	w1,_U1TXREG
	mov	#_uart1_txByteQ+32,w1
	sub	w0,w1,[w15]
	.set ___BP___,85
	bra	nz,.L6
	mov	#-32,w0
	add	w0,w1,w0
.L6:
	sub	w0,w2,[w15]
	.set ___BP___,95
	bra	nz,.L8
	mov	w0,_uart1_obj+6
	mov	_uart1_obj+8,w0
	bclr	w0,#8
	bset	w0,#9
	bra	.L9
.L8:
	clr.b	w1
.L5:
	btst.b	_U1STAbits+9/8,#9%8
	.set ___BP___,95
	bra	z,.L7
	mov	w0,_uart1_obj+6
	and	w1,#1,w1
	sl	w1,#8,w1
	mov	_uart1_obj+8,w0
	bclr	w0,#8
	ior	w1,w0,w0
.L9:
	mov	w0,_uart1_obj+8
.L2:
	mov	[--w15],w2
	mov.d	[--w15],w0
	retfie	
	.set ___PA___,0
	.size	__U1TXInterrupt, .-__U1TXInterrupt
	.section	.isr.text,code,keep
	.align	2
	.global	__U1RXInterrupt	; export
	.type	__U1RXInterrupt,@function
__U1RXInterrupt:
	.set ___PA___,1
	mov.d	w0,[w15++]
	mov	w2,[w15++]
	mov	_uart1_obj+2,w2
	mov	_uart1_obj,w0
	mov	_uart1_obj+8,w1
	lsr	w1,w1
	and.b	w1,#1,w1
	bra	.L11
.L14:
	mov	_U1RXREG,w1
	mov.b	w1,[w0++]
	mov	#_uart1_rxByteQ+32,w1
	sub	w0,w1,[w15]
	.set ___BP___,85
	bra	nz,.L12
	mov	#-32,w0
	add	w0,w1,w0
.L12:
	sub	w0,w2,[w15]
	.set ___BP___,95
	bra	nz,.L15
	mov	w0,_uart1_obj
	mov	_uart1_obj+8,w0
	bclr	w0,#1
	bset	w0,#0
	bra	.L16
.L15:
	clr.b	w1
.L11:
	btst.b	_U1STAbits,#0
	.set ___BP___,95
	bra	nz,.L14
	mov	w0,_uart1_obj
	and	w1,#1,w0
	add	w0,w0,w1
	mov	_uart1_obj+8,w0
	bclr	w0,#1
	ior	w1,w0,w0
.L16:
	mov	w0,_uart1_obj+8
	bclr.b	_IFS0bits+1,#3
	mov	[--w15],w2
	mov.d	[--w15],w0
	retfie	
	.set ___PA___,0
	.size	__U1RXInterrupt, .-__U1RXInterrupt
	.section	.isr.text,code,keep
	.align	2
	.global	__U1ErrInterrupt	; export
	.type	__U1ErrInterrupt,@function
__U1ErrInterrupt:
	.set ___PA___,1
	btst.b	_U1STAbits,#1
	.set ___BP___,39
	bra	z,.L18
	bclr.b	_U1STAbits,#1
.L18:
	bclr.b	_IFS4bits,#1
	retfie	
	.set ___PA___,0
	.size	__U1ErrInterrupt, .-__U1ErrInterrupt
	.section	.text,code
	.align	2
	.global	_UART1_Read	; export
	.type	_UART1_Read,@function
_UART1_Read:
	.set ___PA___,1
	mov	_uart1_obj+2,w1
	mov.b	[w1++],w0
	mov	w1,_uart1_obj+2
	mov	#_uart1_rxByteQ+32,w2
	sub	w1,w2,[w15]
	.set ___BP___,85
	bra	nz,.L20
	mov	#-32,w1
	add	w1,w2,w1
	mov	w1,_uart1_obj+2
.L20:
	mov	_uart1_obj+2,w2
	mov	#_uart1_obj,w1
	sub	w2,[w1],[w15]
	.set ___BP___,78
	bra	nz,.L21
	mov	_uart1_obj+8,w1
	bset	w1,#1
	mov	w1,_uart1_obj+8
.L21:
	mov	_uart1_obj+8,w1
	bclr	w1,#0
	mov	w1,_uart1_obj+8
	return	
	.set ___PA___,0
	.size	_UART1_Read, .-_UART1_Read
	.align	2
	.global	_UART1_ReadBuffer	; export
	.type	_UART1_ReadBuffer,@function
_UART1_ReadBuffer:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov	w10,[w15++]
	mov	w1,w10
	mov	w0,w9
	clr	w8
	bra	.L23
.L25:
	mov	#_uart1_obj+8,w0
	mov	[w0],w0
	and	w0,#2,w0
	.set ___BP___,4
	bra	nz,.L24
	rcall	_UART1_Read
	mov.b	w0,[w9++]
	inc	w8,w8
.L23:
	sub	w8,w10,[w15]
	.set ___BP___,95
	bra	ltu,.L25
.L24:
	mov	w8,w0
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
	.size	_UART1_ReadBuffer, .-_UART1_ReadBuffer
	.align	2
	.global	_UART1_Write	; export
	.type	_UART1_Write,@function
_UART1_Write:
	.set ___PA___,1
	bclr.b	_IEC0bits+1,#4
	mov	_uart1_obj+4,w1
	mov.b	w0,[w1++]
	mov	w1,_uart1_obj+4
	mov	#_uart1_txByteQ+32,w0
	sub	w1,w0,[w15]
	.set ___BP___,85
	bra	nz,.L27
	sub	#32,w0
	mov	w0,_uart1_obj+4
.L27:
	mov	_uart1_obj+8,w0
	bclr	w0,#9
	mov	w0,_uart1_obj+8
	mov	_uart1_obj+6,w2
	mov	#_uart1_obj+4,w1
	sub	w2,[w1],[w15]
	.set ___BP___,78
	bra	nz,.L28
	bset	w0,#8
	mov	w0,_uart1_obj+8
.L28:
	bset.b	_IEC0bits+1,#4
	return	
	.set ___PA___,0
	.size	_UART1_Write, .-_UART1_Write
	.align	2
	.global	_UART1_WriteBuffer	; export
	.type	_UART1_WriteBuffer,@function
_UART1_WriteBuffer:
	.set ___PA___,1
	mov.d	w8,[w15++]
	mov	w10,[w15++]
	mov	w1,w10
	mov	w0,w9
	clr	w8
	bra	.L30
.L32:
	mov	#256,w0
	mov	#_uart1_obj+8,w1
	and	w0,[w1],w0
	.set ___BP___,4
	bra	nz,.L31
	mov.b	[w9++],w0
	inc	w8,w8
	rcall	_UART1_Write
.L30:
	sub	w8,w10,[w15]
	.set ___BP___,95
	bra	ltu,.L32
.L31:
	mov	w8,w0
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
	.size	_UART1_WriteBuffer, .-_UART1_WriteBuffer
	.align	2
	.global	_UART1_TransferStatusGet	; export
	.type	_UART1_TransferStatusGet,@function
_UART1_TransferStatusGet:
	.set ___PA___,1
	mov	_uart1_obj+8,w1
	clr	w0
	btst	w1,#8
	.set ___BP___,50
	bra	z,.L34
	mov	#8,w0
.L34:
	btst	w1,#9
	.set ___BP___,50
	bra	z,.L35
	bset	w0,#4
.L35:
	btst	w1,#0
	.set ___BP___,50
	bra	z,.L36
	bset	w0,#0
.L36:
	btst	w1,#1
	.set ___BP___,61
	bra	z,.L37
	bset	w0,#2
	return	
.L37:
	bset	w0,#1
	return	
	.size	_UART1_TransferStatusGet, .-_UART1_TransferStatusGet
	.align	2
	.global	_UART1_Peek	; export
	.type	_UART1_Peek,@function
_UART1_Peek:
	.set ___PA___,1
	mov	_uart1_obj+2,w2
	add	w2,w0,w1
	mov	#_uart1_rxByteQ+32,w3
	sub	w1,w3,[w15]
	.set ___BP___,61
	bra	leu,.L41
	sub	w0,w3,w3
	add	w2,w3,w2
	mov	#_uart1_rxByteQ,w0
	mov.b	[w0+w2],w0
	return	
.L41:
	mov.b	[w1],w0
	return	
	.size	_UART1_Peek, .-_UART1_Peek
	.align	2
	.global	_UART1_ReceiveBufferSizeGet	; export
	.type	_UART1_ReceiveBufferSizeGet,@function
_UART1_ReceiveBufferSizeGet:
	.set ___PA___,1
	mov	#_uart1_obj+8,w0
	mov	[w0],w0
	and	w0,#1,w1
	clr	w0
	.set ___BP___,39
	bra	nz,.L44
	mov	_uart1_obj+2,w0
	mov	_uart1_obj,w1
	sub	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L45
	sub	w0,w1,w0
	return	
.L45:
	add	#32,w0
	sub	w0,w1,w0
.L44:
	return	
	.size	_UART1_ReceiveBufferSizeGet, .-_UART1_ReceiveBufferSizeGet
	.align	2
	.global	_UART1_TransmitBufferSizeGet	; export
	.type	_UART1_TransmitBufferSizeGet,@function
_UART1_TransmitBufferSizeGet:
	.set ___PA___,1
	mov	#256,w1
	mov	#_uart1_obj+8,w0
	and	w1,[w0],w1
	clr	w0
	.set ___BP___,39
	bra	nz,.L48
	mov	_uart1_obj+6,w0
	mov	_uart1_obj+4,w1
	sub	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L49
	sub	w0,w1,w0
	return	
.L49:
	add	#32,w0
	sub	w0,w1,w0
.L48:
	return	
	.size	_UART1_TransmitBufferSizeGet, .-_UART1_TransmitBufferSizeGet
	.align	2
	.global	_UART1_ReceiveBufferIsEmpty	; export
	.type	_UART1_ReceiveBufferIsEmpty,@function
_UART1_ReceiveBufferIsEmpty:
	.set ___PA___,1
	mov	_uart1_obj+8,w0
	lsr	w0,w0
	and.b	w0,#1,w0
	return	
	.set ___PA___,0
	.size	_UART1_ReceiveBufferIsEmpty, .-_UART1_ReceiveBufferIsEmpty
	.align	2
	.global	_UART1_TransmitBufferIsFull	; export
	.type	_UART1_TransmitBufferIsFull,@function
_UART1_TransmitBufferIsFull:
	.set ___PA___,1
	mov	_uart1_obj+8,w0
	lsr	w0,#8,w0
	and.b	w0,#1,w0
	return	
	.set ___PA___,0
	.size	_UART1_TransmitBufferIsFull, .-_UART1_TransmitBufferIsFull
	.align	2
	.global	_UART1_StatusGet	; export
	.type	_UART1_StatusGet,@function
_UART1_StatusGet:
	.set ___PA___,1
	mov	_U1STA,w0
	return	
	.set ___PA___,0
	.size	_UART1_StatusGet, .-_UART1_StatusGet
	.section	.bss,bss
	.align	2
	.type	_uart1_obj,@object
	.size	_uart1_obj, 10
_uart1_obj:
	.skip	10
	.type	_uart1_rxByteQ,@object
	.size	_uart1_rxByteQ, 32
_uart1_rxByteQ:
	.skip	32
	.type	_uart1_txByteQ,@object
	.size	_uart1_txByteQ, 32
_uart1_txByteQ:
	.skip	32



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
