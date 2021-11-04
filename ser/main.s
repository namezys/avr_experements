	.file	"main.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.text.__vector_19,"ax",@progbits
.global	__vector_19
	.type	__vector_19, @function
__vector_19:
	__gcc_isr 1
	push r25
	push r30
	push r31
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 3...7 */
.L__stack_usage = 3 + __gcc_isr.n_pushed
	lds r30,current_buffer
	lds r31,current_buffer+1
	ld r24,Z
	cpse r24,__zero_reg__
	rjmp .L2
	lds r24,193
	andi r24,lo8(-33)
	sts 193,r24
.L1:
/* epilogue start */
	pop r31
	pop r30
	pop r25
	__gcc_isr 2
	reti
.L2:
	sts 198,r24
	lds r24,current_buffer
	lds r25,current_buffer+1
	adiw r24,1
	sts current_buffer+1,r25
	sts current_buffer,r24
	rjmp .L1
	__gcc_isr 0,r24
	.size	__vector_19, .-__vector_19
	.section	.text._Z4initv,"ax",@progbits
.global	_Z4initv
	.type	_Z4initv, @function
_Z4initv:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r30,lo8(buffer)
	ldi r31,hi8(buffer)
	st Z,__zero_reg__
	std Z+32,__zero_reg__
/* epilogue start */
	ret
	.size	_Z4initv, .-_Z4initv
	.section	.text._Z4savePKc,"ax",@progbits
.global	_Z4savePKc
	.type	_Z4savePKc, @function
_Z4savePKc:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  127 "./src/main.cpp" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	movw r30,r24
	ldi r26,lo8(buffer)
	ldi r27,hi8(buffer)
.L6:
	ld r24,Z+
	cpse r24,__zero_reg__
	rjmp .L7
	st X,__zero_reg__
	ldi r24,lo8(buffer)
	ldi r25,hi8(buffer)
	sts current_buffer+1,r25
	sts current_buffer,r24
	lds r24,193
	ori r24,lo8(32)
	sts 193,r24
/* #APP */
 ;  135 "./src/main.cpp" 1
	sei
 ;  0 "" 2
/* #NOAPP */
/* epilogue start */
	ret
.L7:
	st X+,r24
	rjmp .L6
	.size	_Z4savePKc, .-_Z4savePKc
	.section	.rodata.main.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sdfghjkl"
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
/* stack size = 4 */
.L__stack_usage = 4
	sts 197,__zero_reg__
	ldi r19,lo8(-49)
	sts 196,r19
	ldi r18,lo8(2)
	sts 192,r18
	ldi r25,lo8(24)
	sts 193,r25
	ldi r24,lo8(6)
	sts 194,r24
	sts 197,__zero_reg__
	sts 196,r19
	sts 192,r18
	sts 193,r25
	sts 194,r24
	call _Z4initv
.L11:
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call _Z4savePKc
	std Y+1,__zero_reg__
	std Y+2,__zero_reg__
	std Y+3,__zero_reg__
	std Y+4,__zero_reg__
.L9:
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	cpi r24,85
	sbci r25,35
	sbci r26,8
	cpc r27,__zero_reg__
	brsh .L11
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	adiw r24,1
	adc r26,__zero_reg__
	adc r27,__zero_reg__
	std Y+1,r24
	std Y+2,r25
	std Y+3,r26
	std Y+4,r27
	rjmp .L9
	.size	main, .-main
.global	current_buffer
	.section	.bss.current_buffer,"aw",@nobits
	.type	current_buffer, @object
	.size	current_buffer, 2
current_buffer:
	.zero	2
.global	buffer_end
	.section	.data.buffer_end,"aw"
	.type	buffer_end, @object
	.size	buffer_end, 2
buffer_end:
	.word	buffer+32
.global	buffer
	.section	.bss.buffer,"aw",@nobits
	.p2align	5
	.type	buffer, @object
	.size	buffer, 33
buffer:
	.zero	33
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
.global __do_copy_data
.global __do_clear_bss
