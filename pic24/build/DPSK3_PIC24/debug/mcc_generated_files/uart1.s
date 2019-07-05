	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\uart1.c"
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
	.global	_UART1_Initialize	; export
	.type	_UART1_Initialize,@function
_UART1_Initialize:
.LFB0:
	.file 1 "mcc_generated_files/uart1.c"
	.loc 1 128 0
	.set ___PA___,1
	.loc 1 130 0
	mov	#8,w0
	mov	w0,_U1MODE
	.loc 1 132 0
	clr	_U1STA
	.loc 1 134 0
	mov	#16,w0
	mov	w0,_U1BRG
	.loc 1 136 0
	bset.b	_IEC0bits+1,#3
	.loc 1 139 0
	bset.b	_U1MODEbits+1,#7
	.loc 1 140 0
	bset.b	_U1STAbits+1,#2
	.loc 1 144 0
	mov	#_uart1_txByteQ,w0
	mov	w0,_uart1_obj+6
	.loc 1 145 0
	mov	w0,_uart1_obj+4
	.loc 1 146 0
	mov	#_uart1_rxByteQ,w0
	mov	w0,_uart1_obj+2
	.loc 1 147 0
	mov	w0,_uart1_obj
	.loc 1 148 0
	mov	#_uart1_obj+8,w1
	mov	[w1],w0
	.loc 1 149 0
	ior	#514,w0
	.loc 1 151 0
	mov	#-258,w2
	and	w0,w2,[w1]
	.loc 1 152 0
	return	
	.set ___PA___,0
.LFE0:
	.size	_UART1_Initialize, .-_UART1_Initialize
	.section	.isr.text,code,keep
	.align	2
	.global	__U1TXInterrupt	; export
	.type	__U1TXInterrupt,@function
__U1TXInterrupt:
	.section	.isr.text,code,keep
.LFB1:
	.section	.isr.text,code,keep
	.loc 1 161 0
	.set ___PA___,1
	mov.d	w0,[w15++]
.LCFI0:
	mov	w2,[w15++]
.LCFI1:
	.section	.isr.text,code,keep
	.loc 1 162 0
	mov	#512,w0
	mov	#_uart1_obj+8,w1
	and	w0,[w1],w0
	.set ___BP___,61
	bra	z,.L3
	.section	.isr.text,code,keep
	.loc 1 164 0
	bclr.b	_IEC0bits+1,#4
	.section	.isr.text,code,keep
	.loc 1 165 0
	bra	.L2
.L3:
	.section	.isr.text,code,keep
	.loc 1 168 0
	bclr.b	_IFS0bits+1,#4
	.section	.isr.text,code,keep
	.loc 1 184 0
	mov	_uart1_obj+4,w2
	mov	_uart1_obj+6,w0
	.section	.isr.text,code,keep
	.loc 1 182 0
	mov	_uart1_obj+8,w1
	lsr	w1,#8,w1
	and.b	w1,#1,w1
	.section	.isr.text,code,keep
	.loc 1 170 0
	bra	.L5
.L7:
	.section	.isr.text,code,keep
	.loc 1 173 0
	ze	[w0++],w1
	mov	w1,_U1TXREG
	.section	.isr.text,code,keep
	.loc 1 177 0
	mov	#_uart1_txByteQ+32,w1
	sub	w0,w1,[w15]
	.set ___BP___,85
	bra	nz,.L6
	.section	.isr.text,code,keep
	.loc 1 179 0
	mov	#-32,w0
	add	w0,w1,w0
.L6:
	.section	.isr.text,code,keep
	.loc 1 184 0
	sub	w0,w2,[w15]
	.set ___BP___,95
	bra	nz,.L8
	mov	w0,_uart1_obj+6
	mov	_uart1_obj+8,w0
	bclr	w0,#8
	.section	.isr.text,code,keep
	.loc 1 186 0
	bset	w0,#9
	bra	.L9
.L8:
	.section	.isr.text,code,keep
	.loc 1 182 0
	clr.b	w1
.L5:
	.section	.isr.text,code,keep
	.loc 1 170 0
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
	.section	.isr.text,code,keep
	.loc 1 190 0
	mov	[--w15],w2
	mov.d	[--w15],w0
	retfie	
	.set ___PA___,0
.LFE1:
	.size	__U1TXInterrupt, .-__U1TXInterrupt
	.section	.isr.text,code,keep
	.align	2
	.global	__U1RXInterrupt	; export
	.type	__U1RXInterrupt,@function
__U1RXInterrupt:
	.section	.isr.text,code,keep
.LFB2:
	.section	.isr.text,code,keep
	.loc 1 193 0
	.set ___PA___,1
	mov.d	w0,[w15++]
.LCFI2:
	mov	w2,[w15++]
.LCFI3:
	.section	.isr.text,code,keep
	.loc 1 210 0
	mov	_uart1_obj+2,w2
	mov	_uart1_obj,w0
	.section	.isr.text,code,keep
	.loc 1 208 0
	mov	_uart1_obj+8,w1
	lsr	w1,w1
	and.b	w1,#1,w1
	.section	.isr.text,code,keep
	.loc 1 196 0
	bra	.L11
.L14:
	.section	.isr.text,code,keep
	.loc 1 199 0
	mov	_U1RXREG,w1
	mov.b	w1,[w0++]
	.section	.isr.text,code,keep
	.loc 1 203 0
	mov	#_uart1_rxByteQ+32,w1
	sub	w0,w1,[w15]
	.set ___BP___,85
	bra	nz,.L12
	.section	.isr.text,code,keep
	.loc 1 205 0
	mov	#-32,w0
	add	w0,w1,w0
.L12:
	.section	.isr.text,code,keep
	.loc 1 210 0
	sub	w0,w2,[w15]
	.set ___BP___,95
	bra	nz,.L15
	mov	w0,_uart1_obj
	mov	_uart1_obj+8,w0
	bclr	w0,#1
	.section	.isr.text,code,keep
	.loc 1 213 0
	bset	w0,#0
	bra	.L16
.L15:
	.section	.isr.text,code,keep
	.loc 1 208 0
	clr.b	w1
.L11:
	.section	.isr.text,code,keep
	.loc 1 196 0
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
	.section	.isr.text,code,keep
	.loc 1 219 0
	bclr.b	_IFS0bits+1,#3
	.section	.isr.text,code,keep
	.loc 1 221 0
	mov	[--w15],w2
	mov.d	[--w15],w0
	retfie	
	.set ___PA___,0
.LFE2:
	.size	__U1RXInterrupt, .-__U1RXInterrupt
	.section	.isr.text,code,keep
	.align	2
	.global	__U1ErrInterrupt	; export
	.type	__U1ErrInterrupt,@function
__U1ErrInterrupt:
	.section	.isr.text,code,keep
.LFB3:
	.section	.isr.text,code,keep
	.loc 1 225 0
	.set ___PA___,1
	.section	.isr.text,code,keep
	.loc 1 226 0
	btst.b	_U1STAbits,#1
	.set ___BP___,39
	bra	z,.L18
	.section	.isr.text,code,keep
	.loc 1 228 0
	bclr.b	_U1STAbits,#1
.L18:
	.section	.isr.text,code,keep
	.loc 1 231 0
	bclr.b	_IFS4bits,#1
	.section	.isr.text,code,keep
	.loc 1 232 0
	retfie	
	.set ___PA___,0
.LFE3:
	.size	__U1ErrInterrupt, .-__U1ErrInterrupt
	.section	.text,code
	.align	2
	.global	_UART1_Read	; export
	.type	_UART1_Read,@function
_UART1_Read:
.LFB4:
	.loc 1 239 0
	.set ___PA___,1
	.loc 1 242 0
	mov	_uart1_obj+2,w1
	mov.b	[w1++],w0
	.loc 1 244 0
	mov	w1,_uart1_obj+2
	.loc 1 246 0
	mov	#_uart1_rxByteQ+32,w2
	sub	w1,w2,[w15]
	.set ___BP___,85
	bra	nz,.L20
	.loc 1 248 0
	mov	#-32,w1
	add	w1,w2,w1
	mov	w1,_uart1_obj+2
.L20:
	.loc 1 251 0
	mov	_uart1_obj+2,w2
	mov	#_uart1_obj,w1
	sub	w2,[w1],[w15]
	.set ___BP___,78
	bra	nz,.L21
	.loc 1 253 0
	mov	_uart1_obj+8,w1
	bset	w1,#1
	mov	w1,_uart1_obj+8
.L21:
	.loc 1 256 0
	mov	_uart1_obj+8,w1
	bclr	w1,#0
	mov	w1,_uart1_obj+8
	.loc 1 259 0
	return	
	.set ___PA___,0
.LFE4:
	.size	_UART1_Read, .-_UART1_Read
	.align	2
	.global	_UART1_ReadBuffer	; export
	.type	_UART1_ReadBuffer,@function
_UART1_ReadBuffer:
.LFB5:
	.loc 1 263 0
	.set ___PA___,1
	mov.d	w8,[w15++]
.LCFI4:
	mov	w10,[w15++]
.LCFI5:
	mov	w1,w10
	.loc 1 264 0
	mov	w0,w9
	clr	w8
	.loc 1 265 0
	bra	.L23
.L25:
	.loc 1 267 0
	mov	#_uart1_obj+8,w0
	mov	[w0],w0
	and	w0,#2,w0
	.set ___BP___,4
	bra	nz,.L24
	.loc 1 273 0
	rcall	_UART1_Read
	mov.b	w0,[w9++]
	inc	w8,w8
.L23:
	.loc 1 265 0
	sub	w8,w10,[w15]
	.set ___BP___,95
	bra	ltu,.L25
.L24:
	.loc 1 278 0
	mov	w8,w0
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE5:
	.size	_UART1_ReadBuffer, .-_UART1_ReadBuffer
	.align	2
	.global	_UART1_Write	; export
	.type	_UART1_Write,@function
_UART1_Write:
.LFB6:
	.loc 1 283 0
	.set ___PA___,1
	.loc 1 284 0
	bclr.b	_IEC0bits+1,#4
	.loc 1 286 0
	mov	_uart1_obj+4,w1
	mov.b	w0,[w1++]
	.loc 1 288 0
	mov	w1,_uart1_obj+4
	.loc 1 290 0
	mov	#_uart1_txByteQ+32,w0
	sub	w1,w0,[w15]
	.set ___BP___,85
	bra	nz,.L27
	.loc 1 292 0
	sub	#32,w0
	mov	w0,_uart1_obj+4
.L27:
	.loc 1 295 0
	mov	_uart1_obj+8,w0
	bclr	w0,#9
	mov	w0,_uart1_obj+8
	.loc 1 297 0
	mov	_uart1_obj+6,w2
	mov	#_uart1_obj+4,w1
	sub	w2,[w1],[w15]
	.set ___BP___,78
	bra	nz,.L28
	.loc 1 299 0
	bset	w0,#8
	mov	w0,_uart1_obj+8
.L28:
	.loc 1 302 0
	bset.b	_IEC0bits+1,#4
	.loc 1 304 0
	return	
	.set ___PA___,0
.LFE6:
	.size	_UART1_Write, .-_UART1_Write
	.align	2
	.global	_UART1_WriteBuffer	; export
	.type	_UART1_WriteBuffer,@function
_UART1_WriteBuffer:
.LFB7:
	.loc 1 308 0
	.set ___PA___,1
	mov.d	w8,[w15++]
.LCFI6:
	mov	w10,[w15++]
.LCFI7:
	mov	w1,w10
	.loc 1 309 0
	mov	w0,w9
	clr	w8
	.loc 1 311 0
	bra	.L30
.L32:
	.loc 1 313 0
	mov	#256,w0
	mov	#_uart1_obj+8,w1
	and	w0,[w1],w0
	.set ___BP___,4
	bra	nz,.L31
	.loc 1 319 0
	mov.b	[w9++],w0
	inc	w8,w8
	rcall	_UART1_Write
.L30:
	.loc 1 311 0
	sub	w8,w10,[w15]
	.set ___BP___,95
	bra	ltu,.L32
.L31:
	.loc 1 325 0
	mov	w8,w0
	mov	[--w15],w10
	mov.d	[--w15],w8
	return	
	.set ___PA___,0
.LFE7:
	.size	_UART1_WriteBuffer, .-_UART1_WriteBuffer
	.align	2
	.global	_UART1_TransferStatusGet	; export
	.type	_UART1_TransferStatusGet,@function
_UART1_TransferStatusGet:
.LFB8:
	.loc 1 329 0
	.set ___PA___,1
	.loc 1 332 0
	mov	_uart1_obj+8,w1
	.loc 1 330 0
	clr	w0
	.loc 1 332 0
	btst	w1,#8
	.set ___BP___,50
	bra	z,.L34
	.loc 1 334 0
	mov	#8,w0
.L34:
	.loc 1 337 0
	btst	w1,#9
	.set ___BP___,50
	bra	z,.L35
	.loc 1 339 0
	bset	w0,#4
.L35:
	.loc 1 342 0
	btst	w1,#0
	.set ___BP___,50
	bra	z,.L36
	.loc 1 344 0
	bset	w0,#0
.L36:
	.loc 1 347 0
	btst	w1,#1
	.set ___BP___,61
	bra	z,.L37
	.loc 1 349 0
	bset	w0,#2
	return	
.L37:
	.loc 1 353 0
	bset	w0,#1
	.loc 1 356 0
	return	
.LFE8:
	.size	_UART1_TransferStatusGet, .-_UART1_TransferStatusGet
	.align	2
	.global	_UART1_Peek	; export
	.type	_UART1_Peek,@function
_UART1_Peek:
.LFB9:
	.loc 1 360 0
	.set ___PA___,1
	.loc 1 361 0
	mov	_uart1_obj+2,w2
	add	w2,w0,w1
	mov	#_uart1_rxByteQ+32,w3
	sub	w1,w3,[w15]
	.set ___BP___,61
	bra	leu,.L41
	.loc 1 363 0
	sub	w0,w3,w3
	add	w2,w3,w2
	mov	#_uart1_rxByteQ,w0
	mov.b	[w0+w2],w0
	return	
.L41:
	.loc 1 367 0
	mov.b	[w1],w0
	.loc 1 369 0
	return	
.LFE9:
	.size	_UART1_Peek, .-_UART1_Peek
	.align	2
	.global	_UART1_ReceiveBufferSizeGet	; export
	.type	_UART1_ReceiveBufferSizeGet,@function
_UART1_ReceiveBufferSizeGet:
.LFB10:
	.loc 1 373 0
	.set ___PA___,1
	.loc 1 374 0
	mov	#_uart1_obj+8,w0
	mov	[w0],w0
	and	w0,#1,w1
	.loc 1 385 0
	clr	w0
	.loc 1 374 0
	.set ___BP___,39
	bra	nz,.L44
	.loc 1 376 0
	mov	_uart1_obj+2,w0
	mov	_uart1_obj,w1
	sub	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L45
	.loc 1 378 0
	sub	w0,w1,w0
	return	
.L45:
	.loc 1 382 0
	add	#32,w0
	sub	w0,w1,w0
.L44:
	.loc 1 386 0
	return	
.LFE10:
	.size	_UART1_ReceiveBufferSizeGet, .-_UART1_ReceiveBufferSizeGet
	.align	2
	.global	_UART1_TransmitBufferSizeGet	; export
	.type	_UART1_TransmitBufferSizeGet,@function
_UART1_TransmitBufferSizeGet:
.LFB11:
	.loc 1 390 0
	.set ___PA___,1
	.loc 1 391 0
	mov	#256,w1
	mov	#_uart1_obj+8,w0
	and	w1,[w0],w1
	.loc 1 402 0
	clr	w0
	.loc 1 391 0
	.set ___BP___,39
	bra	nz,.L48
	.loc 1 393 0
	mov	_uart1_obj+6,w0
	mov	_uart1_obj+4,w1
	sub	w0,w1,[w15]
	.set ___BP___,61
	bra	leu,.L49
	.loc 1 395 0
	sub	w0,w1,w0
	return	
.L49:
	.loc 1 399 0
	add	#32,w0
	sub	w0,w1,w0
.L48:
	.loc 1 403 0
	return	
.LFE11:
	.size	_UART1_TransmitBufferSizeGet, .-_UART1_TransmitBufferSizeGet
	.align	2
	.global	_UART1_ReceiveBufferIsEmpty	; export
	.type	_UART1_ReceiveBufferIsEmpty,@function
_UART1_ReceiveBufferIsEmpty:
.LFB12:
	.loc 1 407 0
	.set ___PA___,1
	.loc 1 408 0
	mov	_uart1_obj+8,w0
	lsr	w0,w0
	and.b	w0,#1,w0
	.loc 1 409 0
	return	
	.set ___PA___,0
.LFE12:
	.size	_UART1_ReceiveBufferIsEmpty, .-_UART1_ReceiveBufferIsEmpty
	.align	2
	.global	_UART1_TransmitBufferIsFull	; export
	.type	_UART1_TransmitBufferIsFull,@function
_UART1_TransmitBufferIsFull:
.LFB13:
	.loc 1 413 0
	.set ___PA___,1
	.loc 1 414 0
	mov	_uart1_obj+8,w0
	lsr	w0,#8,w0
	and.b	w0,#1,w0
	.loc 1 415 0
	return	
	.set ___PA___,0
.LFE13:
	.size	_UART1_TransmitBufferIsFull, .-_UART1_TransmitBufferIsFull
	.align	2
	.global	_UART1_StatusGet	; export
	.type	_UART1_StatusGet,@function
_UART1_StatusGet:
.LFB14:
	.loc 1 419 0
	.set ___PA___,1
	.loc 1 420 0
	mov	_U1STA,w0
	.loc 1 421 0
	return	
	.set ___PA___,0
.LFE14:
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI0-.LFB1
	.byte	0x13
	.sleb128 -4
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x13
	.sleb128 -5
	.byte	0x82
	.uleb128 0x4
	.byte	0x80
	.uleb128 0x2
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI2-.LFB2
	.byte	0x13
	.sleb128 -4
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0x13
	.sleb128 -5
	.byte	0x82
	.uleb128 0x4
	.byte	0x80
	.uleb128 0x2
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.byte	0x4
	.4byte	.LCFI4-.LFB5
	.byte	0x13
	.sleb128 -4
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0x13
	.sleb128 -5
	.byte	0x8a
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.byte	0x4
	.4byte	.LCFI6-.LFB7
	.byte	0x13
	.sleb128 -4
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0x13
	.sleb128 -5
	.byte	0x8a
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x2
	.align	4
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.align	4
.LEFDE20:
.LSFDE22:
	.4byte	.LEFDE22-.LASFDE22
.LASFDE22:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	4
.LEFDE22:
.LSFDE24:
	.4byte	.LEFDE24-.LASFDE24
.LASFDE24:
	.4byte	.Lframe0
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.align	4
.LEFDE24:
.LSFDE26:
	.4byte	.LEFDE26-.LASFDE26
.LASFDE26:
	.4byte	.Lframe0
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.align	4
.LEFDE26:
.LSFDE28:
	.4byte	.LEFDE28-.LASFDE28
.LASFDE28:
	.4byte	.Lframe0
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.align	4
.LEFDE28:
	.section	.text,code
.Letext0:
	.file 2 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\include\\lega-c/stdint.h"
	.file 3 "c:\\program files (x86)\\microchip\\xc16\\v1.36\\bin\\bin\\../..\\support\\PIC24F\\h/p24FJ64GA004.h"
	.file 4 "mcc_generated_files/uart1.h"
	.section	.debug_info,info
	.4byte	0xec9
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1.36) (B) Build date: Jan 25 2019"
	.byte	0x1
	.asciz	"mcc_generated_files/uart1.c"
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
	.byte	0x2
	.byte	0x2b
	.4byte	0xfa
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.asciz	"unsigned char"
	.uleb128 0x3
	.asciz	"uint16_t"
	.byte	0x2
	.byte	0x31
	.4byte	0x11b
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
	.asciz	"tagIFS0BITS"
	.byte	0x2
	.byte	0x3
	.byte	0xf5
	.4byte	0x26c
	.uleb128 0x5
	.asciz	"INT0IF"
	.byte	0x3
	.byte	0xf6
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"IC1IF"
	.byte	0x3
	.byte	0xf7
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"OC1IF"
	.byte	0x3
	.byte	0xf8
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T1IF"
	.byte	0x3
	.byte	0xf9
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"IC2IF"
	.byte	0x3
	.byte	0xfb
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"OC2IF"
	.byte	0x3
	.byte	0xfc
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T2IF"
	.byte	0x3
	.byte	0xfd
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"T3IF"
	.byte	0x3
	.byte	0xfe
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"SPF1IF"
	.byte	0x3
	.byte	0xff
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPI1IF"
	.byte	0x3
	.2byte	0x100
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1RXIF"
	.byte	0x3
	.2byte	0x101
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1TXIF"
	.byte	0x3
	.2byte	0x102
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"AD1IF"
	.byte	0x3
	.2byte	0x103
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"IFS0BITS"
	.byte	0x3
	.2byte	0x104
	.4byte	0x15a
	.uleb128 0x8
	.asciz	"tagIFS4BITS"
	.byte	0x2
	.byte	0x3
	.2byte	0x137
	.4byte	0x2e5
	.uleb128 0x6
	.asciz	"U1ERIF"
	.byte	0x3
	.2byte	0x139
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U2ERIF"
	.byte	0x3
	.2byte	0x13a
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"CRCIF"
	.byte	0x3
	.2byte	0x13b
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"LVDIF"
	.byte	0x3
	.2byte	0x13d
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"IFS4BITS"
	.byte	0x3
	.2byte	0x13e
	.4byte	0x27d
	.uleb128 0x8
	.asciz	"tagIEC0BITS"
	.byte	0x2
	.byte	0x3
	.2byte	0x143
	.4byte	0x412
	.uleb128 0x6
	.asciz	"INT0IE"
	.byte	0x3
	.2byte	0x144
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"IC1IE"
	.byte	0x3
	.2byte	0x145
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"OC1IE"
	.byte	0x3
	.2byte	0x146
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T1IE"
	.byte	0x3
	.2byte	0x147
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"IC2IE"
	.byte	0x3
	.2byte	0x149
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"OC2IE"
	.byte	0x3
	.2byte	0x14a
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T2IE"
	.byte	0x3
	.2byte	0x14b
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"T3IE"
	.byte	0x3
	.2byte	0x14c
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPF1IE"
	.byte	0x3
	.2byte	0x14d
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"SPI1IE"
	.byte	0x3
	.2byte	0x14e
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1RXIE"
	.byte	0x3
	.2byte	0x14f
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"U1TXIE"
	.byte	0x3
	.2byte	0x150
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"AD1IE"
	.byte	0x3
	.2byte	0x151
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"IEC0BITS"
	.byte	0x3
	.2byte	0x152
	.4byte	0x2f6
	.uleb128 0x9
	.byte	0x2
	.byte	0x3
	.2byte	0x596
	.4byte	0x51a
	.uleb128 0x6
	.asciz	"STSEL"
	.byte	0x3
	.2byte	0x597
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"PDSEL"
	.byte	0x3
	.2byte	0x598
	.4byte	0x10b
	.byte	0x2
	.byte	0x2
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"BRGH"
	.byte	0x3
	.2byte	0x599
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"RXINV"
	.byte	0x3
	.2byte	0x59a
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"ABAUD"
	.byte	0x3
	.2byte	0x59b
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"LPBACK"
	.byte	0x3
	.2byte	0x59c
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"WAKE"
	.byte	0x3
	.2byte	0x59d
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UEN"
	.byte	0x3
	.2byte	0x59e
	.4byte	0x10b
	.byte	0x2
	.byte	0x2
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"RTSMD"
	.byte	0x3
	.2byte	0x5a0
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"IREN"
	.byte	0x3
	.2byte	0x5a1
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x3
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"USIDL"
	.byte	0x3
	.2byte	0x5a2
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UARTEN"
	.byte	0x3
	.2byte	0x5a4
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.byte	0x2
	.byte	0x3
	.2byte	0x5a6
	.4byte	0x574
	.uleb128 0x6
	.asciz	"PDSEL0"
	.byte	0x3
	.2byte	0x5a8
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"PDSEL1"
	.byte	0x3
	.2byte	0x5a9
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UEN0"
	.byte	0x3
	.2byte	0x5ab
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UEN1"
	.byte	0x3
	.2byte	0x5ac
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.byte	0x3
	.2byte	0x595
	.4byte	0x588
	.uleb128 0xb
	.4byte	0x423
	.uleb128 0xb
	.4byte	0x51a
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagU1MODEBITS"
	.byte	0x2
	.byte	0x3
	.2byte	0x594
	.4byte	0x5a8
	.uleb128 0xc
	.4byte	0x574
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"U1MODEBITS"
	.byte	0x3
	.2byte	0x5af
	.4byte	0x588
	.uleb128 0x9
	.byte	0x2
	.byte	0x3
	.2byte	0x5b6
	.4byte	0x6e3
	.uleb128 0x6
	.asciz	"URXDA"
	.byte	0x3
	.2byte	0x5b7
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xf
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"OERR"
	.byte	0x3
	.2byte	0x5b8
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xe
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"FERR"
	.byte	0x3
	.2byte	0x5b9
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xd
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"PERR"
	.byte	0x3
	.2byte	0x5ba
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xc
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"RIDLE"
	.byte	0x3
	.2byte	0x5bb
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xb
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"ADDEN"
	.byte	0x3
	.2byte	0x5bc
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0xa
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"URXISEL"
	.byte	0x3
	.2byte	0x5bd
	.4byte	0x10b
	.byte	0x2
	.byte	0x2
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"TRMT"
	.byte	0x3
	.2byte	0x5be
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXBF"
	.byte	0x3
	.2byte	0x5bf
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXEN"
	.byte	0x3
	.2byte	0x5c0
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x5
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXBRK"
	.byte	0x3
	.2byte	0x5c1
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x4
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXISEL0"
	.byte	0x3
	.2byte	0x5c3
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXINV"
	.byte	0x3
	.2byte	0x5c4
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x1
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"UTXISEL1"
	.byte	0x3
	.2byte	0x5c5
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x10
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x9
	.byte	0x2
	.byte	0x3
	.2byte	0x5c7
	.4byte	0x71b
	.uleb128 0x6
	.asciz	"URXISEL0"
	.byte	0x3
	.2byte	0x5c9
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x9
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x6
	.asciz	"URXISEL1"
	.byte	0x3
	.2byte	0x5ca
	.4byte	0x10b
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0xa
	.byte	0x2
	.byte	0x3
	.2byte	0x5b5
	.4byte	0x72f
	.uleb128 0xb
	.4byte	0x5bb
	.uleb128 0xb
	.4byte	0x6e3
	.byte	0x0
	.uleb128 0x8
	.asciz	"tagU1STABITS"
	.byte	0x2
	.byte	0x3
	.2byte	0x5b4
	.4byte	0x74e
	.uleb128 0xc
	.4byte	0x71b
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x7
	.asciz	"U1STABITS"
	.byte	0x3
	.2byte	0x5cd
	.4byte	0x72f
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.asciz	"short unsigned int"
	.uleb128 0xd
	.byte	0x2
	.byte	0x4
	.byte	0x4e
	.4byte	0x819
	.uleb128 0xe
	.asciz	"UART1_RX_DATA_AVAILABLE"
	.sleb128 1
	.uleb128 0xe
	.asciz	"UART1_RX_OVERRUN_ERROR"
	.sleb128 2
	.uleb128 0xe
	.asciz	"UART1_FRAMING_ERROR"
	.sleb128 4
	.uleb128 0xe
	.asciz	"UART1_PARITY_ERROR"
	.sleb128 8
	.uleb128 0xe
	.asciz	"UART1_RECEIVER_IDLE"
	.sleb128 16
	.uleb128 0xe
	.asciz	"UART1_TX_COMPLETE"
	.sleb128 256
	.uleb128 0xe
	.asciz	"UART1_TX_FULL"
	.sleb128 512
	.byte	0x0
	.uleb128 0x3
	.asciz	"UART1_STATUS"
	.byte	0x4
	.byte	0x6b
	.4byte	0x776
	.uleb128 0xd
	.byte	0x2
	.byte	0x4
	.byte	0x7c
	.4byte	0x8e0
	.uleb128 0xe
	.asciz	"UART1_TRANSFER_STATUS_RX_FULL"
	.sleb128 1
	.uleb128 0xe
	.asciz	"UART1_TRANSFER_STATUS_RX_DATA_PRESENT"
	.sleb128 2
	.uleb128 0xe
	.asciz	"UART1_TRANSFER_STATUS_RX_EMPTY"
	.sleb128 4
	.uleb128 0xe
	.asciz	"UART1_TRANSFER_STATUS_TX_FULL"
	.sleb128 8
	.uleb128 0xe
	.asciz	"UART1_TRANSFER_STATUS_TX_EMPTY"
	.sleb128 16
	.byte	0x0
	.uleb128 0x3
	.asciz	"UART1_TRANSFER_STATUS"
	.byte	0x4
	.byte	0x91
	.4byte	0x82d
	.uleb128 0xf
	.byte	0x1
	.byte	0x1
	.byte	0x3f
	.4byte	0x941
	.uleb128 0x5
	.asciz	"full"
	.byte	0x1
	.byte	0x41
	.4byte	0xeb
	.byte	0x1
	.byte	0x1
	.byte	0x7
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"empty"
	.byte	0x1
	.byte	0x42
	.4byte	0xeb
	.byte	0x1
	.byte	0x1
	.byte	0x6
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x5
	.asciz	"reserved"
	.byte	0x1
	.byte	0x43
	.4byte	0xeb
	.byte	0x1
	.byte	0x6
	.byte	0x8
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.byte	0x0
	.uleb128 0x10
	.byte	0x1
	.byte	0x1
	.byte	0x3d
	.4byte	0x961
	.uleb128 0x11
	.asciz	"s"
	.byte	0x1
	.byte	0x44
	.4byte	0x8fd
	.uleb128 0x11
	.asciz	"status"
	.byte	0x1
	.byte	0x45
	.4byte	0xeb
	.byte	0x0
	.uleb128 0x3
	.asciz	"UART_BYTEQ_STATUS"
	.byte	0x1
	.byte	0x48
	.4byte	0x941
	.uleb128 0xf
	.byte	0xa
	.byte	0x1
	.byte	0x50
	.4byte	0x9ed
	.uleb128 0x12
	.asciz	"rxTail"
	.byte	0x1
	.byte	0x53
	.4byte	0x9ed
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x12
	.asciz	"rxHead"
	.byte	0x1
	.byte	0x55
	.4byte	0x9ed
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x12
	.asciz	"txTail"
	.byte	0x1
	.byte	0x58
	.4byte	0x9ed
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x12
	.asciz	"txHead"
	.byte	0x1
	.byte	0x5a
	.4byte	0x9ed
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x12
	.asciz	"rxStatus"
	.byte	0x1
	.byte	0x5c
	.4byte	0x961
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x12
	.asciz	"txStatus"
	.byte	0x1
	.byte	0x5e
	.4byte	0x961
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.byte	0x0
	.uleb128 0x13
	.byte	0x2
	.4byte	0xeb
	.uleb128 0x3
	.asciz	"UART_OBJECT"
	.byte	0x1
	.byte	0x60
	.4byte	0x97a
	.uleb128 0x14
	.byte	0x1
	.asciz	"UART1_Initialize"
	.byte	0x1
	.byte	0x7f
	.byte	0x1
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5f
	.uleb128 0x14
	.byte	0x1
	.asciz	"_U1TXInterrupt"
	.byte	0x1
	.byte	0xa0
	.byte	0x1
	.4byte	.LFB1
	.4byte	.LFE1
	.byte	0x1
	.byte	0x5f
	.uleb128 0x14
	.byte	0x1
	.asciz	"_U1RXInterrupt"
	.byte	0x1
	.byte	0xc0
	.byte	0x1
	.4byte	.LFB2
	.4byte	.LFE2
	.byte	0x1
	.byte	0x5f
	.uleb128 0x14
	.byte	0x1
	.asciz	"_U1ErrInterrupt"
	.byte	0x1
	.byte	0xe0
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.byte	0x1
	.byte	0x5f
	.uleb128 0x15
	.byte	0x1
	.asciz	"UART1_Read"
	.byte	0x1
	.byte	0xee
	.byte	0x1
	.4byte	0xeb
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x1
	.byte	0x5f
	.4byte	0xab2
	.uleb128 0x16
	.asciz	"data"
	.byte	0x1
	.byte	0xf0
	.4byte	0xeb
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x17
	.byte	0x1
	.asciz	"UART1_ReadBuffer"
	.byte	0x1
	.2byte	0x106
	.byte	0x1
	.4byte	0x11b
	.4byte	.LFB5
	.4byte	.LFE5
	.byte	0x1
	.byte	0x5f
	.4byte	0xb15
	.uleb128 0x18
	.asciz	"buffer"
	.byte	0x1
	.2byte	0x106
	.4byte	0x9ed
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"bufLen"
	.byte	0x1
	.2byte	0x106
	.4byte	0xb15
	.byte	0x1
	.byte	0x5a
	.uleb128 0x19
	.asciz	"numBytesRead"
	.byte	0x1
	.2byte	0x108
	.4byte	0x11b
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x1a
	.4byte	0x11b
	.uleb128 0x1b
	.byte	0x1
	.asciz	"UART1_Write"
	.byte	0x1
	.2byte	0x11a
	.byte	0x1
	.4byte	.LFB6
	.4byte	.LFE6
	.byte	0x1
	.byte	0x5f
	.4byte	0xb4a
	.uleb128 0x18
	.asciz	"byte"
	.byte	0x1
	.2byte	0x11a
	.4byte	0xb4a
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x1a
	.4byte	0xeb
	.uleb128 0x17
	.byte	0x1
	.asciz	"UART1_WriteBuffer"
	.byte	0x1
	.2byte	0x133
	.byte	0x1
	.4byte	0x11b
	.4byte	.LFB7
	.4byte	.LFE7
	.byte	0x1
	.byte	0x5f
	.4byte	0xbb6
	.uleb128 0x18
	.asciz	"buffer"
	.byte	0x1
	.2byte	0x133
	.4byte	0xbb6
	.byte	0x1
	.byte	0x50
	.uleb128 0x18
	.asciz	"bufLen"
	.byte	0x1
	.2byte	0x133
	.4byte	0xb15
	.byte	0x1
	.byte	0x5a
	.uleb128 0x19
	.asciz	"numBytesWritten"
	.byte	0x1
	.2byte	0x135
	.4byte	0x11b
	.byte	0x1
	.byte	0x58
	.byte	0x0
	.uleb128 0x13
	.byte	0x2
	.4byte	0xb4a
	.uleb128 0x17
	.byte	0x1
	.asciz	"UART1_TransferStatusGet"
	.byte	0x1
	.2byte	0x148
	.byte	0x1
	.4byte	0x8e0
	.4byte	.LFB8
	.4byte	.LFE8
	.byte	0x1
	.byte	0x5f
	.4byte	0xbfc
	.uleb128 0x1c
	.asciz	"status"
	.byte	0x1
	.2byte	0x14a
	.4byte	0x8e0
	.byte	0x0
	.uleb128 0x17
	.byte	0x1
	.asciz	"UART1_Peek"
	.byte	0x1
	.2byte	0x167
	.byte	0x1
	.4byte	0xeb
	.4byte	.LFB9
	.4byte	.LFE9
	.byte	0x1
	.byte	0x5f
	.4byte	0xc31
	.uleb128 0x18
	.asciz	"offset"
	.byte	0x1
	.2byte	0x167
	.4byte	0x10b
	.byte	0x1
	.byte	0x50
	.byte	0x0
	.uleb128 0x1d
	.byte	0x1
	.asciz	"UART1_ReceiveBufferSizeGet"
	.byte	0x1
	.2byte	0x174
	.byte	0x1
	.4byte	0x11b
	.4byte	.LFB10
	.4byte	.LFE10
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1d
	.byte	0x1
	.asciz	"UART1_TransmitBufferSizeGet"
	.byte	0x1
	.2byte	0x185
	.byte	0x1
	.4byte	0x11b
	.4byte	.LFB11
	.4byte	.LFE11
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1d
	.byte	0x1
	.asciz	"UART1_ReceiveBufferIsEmpty"
	.byte	0x1
	.2byte	0x196
	.byte	0x1
	.4byte	0xcbf
	.4byte	.LFB12
	.4byte	.LFE12
	.byte	0x1
	.byte	0x5f
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.asciz	"_Bool"
	.uleb128 0x1d
	.byte	0x1
	.asciz	"UART1_TransmitBufferIsFull"
	.byte	0x1
	.2byte	0x19c
	.byte	0x1
	.4byte	0xcbf
	.4byte	.LFB13
	.4byte	.LFE13
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1d
	.byte	0x1
	.asciz	"UART1_StatusGet"
	.byte	0x1
	.2byte	0x1a2
	.byte	0x1
	.4byte	0x819
	.4byte	.LFB14
	.4byte	.LFE14
	.byte	0x1
	.byte	0x5f
	.uleb128 0x1e
	.4byte	.LASF0
	.byte	0x3
	.2byte	0x105
	.4byte	0xd29
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x26c
	.uleb128 0x1e
	.4byte	.LASF1
	.byte	0x3
	.2byte	0x13f
	.4byte	0xd3c
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x2e5
	.uleb128 0x1e
	.4byte	.LASF2
	.byte	0x3
	.2byte	0x153
	.4byte	0xd4f
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x412
	.uleb128 0x20
	.asciz	"U1MODE"
	.byte	0x3
	.2byte	0x593
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x10b
	.uleb128 0x1e
	.4byte	.LASF3
	.byte	0x3
	.2byte	0x5b0
	.4byte	0xd78
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x5a8
	.uleb128 0x20
	.asciz	"U1STA"
	.byte	0x3
	.2byte	0x5b3
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF4
	.byte	0x3
	.2byte	0x5ce
	.4byte	0xd9b
	.byte	0x1
	.byte	0x1
	.uleb128 0x1f
	.4byte	0x74e
	.uleb128 0x20
	.asciz	"U1TXREG"
	.byte	0x3
	.2byte	0x5d1
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1RXREG"
	.byte	0x3
	.2byte	0x5d3
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1BRG"
	.byte	0x3
	.2byte	0x5d5
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x16
	.asciz	"uart1_obj"
	.byte	0x1
	.byte	0x62
	.4byte	0x9f3
	.byte	0x5
	.byte	0x3
	.4byte	_uart1_obj
	.uleb128 0x21
	.4byte	0xeb
	.4byte	0xdfb
	.uleb128 0x22
	.4byte	0x11b
	.byte	0x1f
	.byte	0x0
	.uleb128 0x16
	.asciz	"uart1_txByteQ"
	.byte	0x1
	.byte	0x76
	.4byte	0xdeb
	.byte	0x5
	.byte	0x3
	.4byte	_uart1_txByteQ
	.uleb128 0x16
	.asciz	"uart1_rxByteQ"
	.byte	0x1
	.byte	0x77
	.4byte	0xdeb
	.byte	0x5
	.byte	0x3
	.4byte	_uart1_rxByteQ
	.uleb128 0x1e
	.4byte	.LASF0
	.byte	0x3
	.2byte	0x105
	.4byte	0xd29
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF1
	.byte	0x3
	.2byte	0x13f
	.4byte	0xd3c
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF2
	.byte	0x3
	.2byte	0x153
	.4byte	0xd4f
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1MODE"
	.byte	0x3
	.2byte	0x593
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF3
	.byte	0x3
	.2byte	0x5b0
	.4byte	0xd78
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1STA"
	.byte	0x3
	.2byte	0x5b3
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF4
	.byte	0x3
	.2byte	0x5ce
	.4byte	0xd9b
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1TXREG"
	.byte	0x3
	.2byte	0x5d1
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1RXREG"
	.byte	0x3
	.2byte	0x5d3
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
	.uleb128 0x20
	.asciz	"U1BRG"
	.byte	0x3
	.2byte	0x5d5
	.4byte	0xd65
	.byte	0x1
	.byte	0x1
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
	.uleb128 0xb
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
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
	.uleb128 0xa
	.uleb128 0x17
	.byte	0x1
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
	.uleb128 0xb
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
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
	.uleb128 0xe
	.uleb128 0x28
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x0
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x1a
	.uleb128 0x26
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
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
	.uleb128 0x1c
	.uleb128 0x34
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
	.uleb128 0x1d
	.uleb128 0x2e
	.byte	0x0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.byte	0x0
	.byte	0x0
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x22
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x163
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0xecd
	.4byte	0xa06
	.asciz	"UART1_Initialize"
	.4byte	0xa26
	.asciz	"_U1TXInterrupt"
	.4byte	0xa44
	.asciz	"_U1RXInterrupt"
	.4byte	0xa62
	.asciz	"_U1ErrInterrupt"
	.4byte	0xa81
	.asciz	"UART1_Read"
	.4byte	0xab2
	.asciz	"UART1_ReadBuffer"
	.4byte	0xb1a
	.asciz	"UART1_Write"
	.4byte	0xb4f
	.asciz	"UART1_WriteBuffer"
	.4byte	0xbbc
	.asciz	"UART1_TransferStatusGet"
	.4byte	0xbfc
	.asciz	"UART1_Peek"
	.4byte	0xc31
	.asciz	"UART1_ReceiveBufferSizeGet"
	.4byte	0xc60
	.asciz	"UART1_TransmitBufferSizeGet"
	.4byte	0xc90
	.asciz	"UART1_ReceiveBufferIsEmpty"
	.4byte	0xcc8
	.asciz	"UART1_TransmitBufferIsFull"
	.4byte	0xcf7
	.asciz	"UART1_StatusGet"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0x10f
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0xecd
	.4byte	0xeb
	.asciz	"uint8_t"
	.4byte	0x10b
	.asciz	"uint16_t"
	.4byte	0x15a
	.asciz	"tagIFS0BITS"
	.4byte	0x26c
	.asciz	"IFS0BITS"
	.4byte	0x27d
	.asciz	"tagIFS4BITS"
	.4byte	0x2e5
	.asciz	"IFS4BITS"
	.4byte	0x2f6
	.asciz	"tagIEC0BITS"
	.4byte	0x412
	.asciz	"IEC0BITS"
	.4byte	0x588
	.asciz	"tagU1MODEBITS"
	.4byte	0x5a8
	.asciz	"U1MODEBITS"
	.4byte	0x72f
	.asciz	"tagU1STABITS"
	.4byte	0x74e
	.asciz	"U1STABITS"
	.4byte	0x819
	.asciz	"UART1_STATUS"
	.4byte	0x8e0
	.asciz	"UART1_TRANSFER_STATUS"
	.4byte	0x961
	.asciz	"UART_BYTEQ_STATUS"
	.4byte	0x9f3
	.asciz	"UART_OBJECT"
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
.LASF3:
	.asciz	"U1MODEbits"
.LASF1:
	.asciz	"IFS4bits"
.LASF4:
	.asciz	"U1STAbits"
.LASF0:
	.asciz	"IFS0bits"
.LASF2:
	.asciz	"IEC0bits"
	.section	.text,code



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
