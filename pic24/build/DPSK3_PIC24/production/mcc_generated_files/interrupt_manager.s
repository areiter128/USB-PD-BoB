	.file "C:\\_dsmps\\DPSK3\\Troubleshooting\\__src__\\dpsk3-firmware\\pic24\\mcc_generated_files\\interrupt_manager.c"
	.section	.text,code
	.align	2
	.global	_INTERRUPT_Initialize	; export
	.type	_INTERRUPT_Initialize,@function
_INTERRUPT_Initialize:
	.set ___PA___,1
	mov	#-28673,w0
	mov	_IPC0bits,w1
	and	w0,w1,w2
	mov	#12288,w1
	ior	w1,w2,w1
	mov	w1,_IPC0bits
	mov	#-113,w1
	mov	_IPC3bits,w3
	and	w1,w3,w2
	bset	w2,#6
	mov	w2,_IPC3bits
	mov	_IPC16bits,w2
	and	w1,w2,w1
	bset	w1,#4
	mov	w1,_IPC16bits
	mov	#-8,w1
	mov	_IPC3bits,w3
	and	w1,w3,w1
	bset	w1,#0
	mov	w1,_IPC3bits
	and	_IPC2bits,WREG
	bset	w0,#13
	mov	w0,_IPC2bits
	return	
	.set ___PA___,0
	.size	_INTERRUPT_Initialize, .-_INTERRUPT_Initialize



	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
