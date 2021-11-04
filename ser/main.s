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
/* prologue: naked */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  113 "./src/main.cpp" 1
	
	push r16
	in r16, __SREG__
	push r16
	push r30
	push r31
	lds r30, current_buffer
	lds r31, current_buffer + 1
	ld r16, Z+
	cpi r16, 0
	breq STOP_5
	sts 198, r16
	pop r31
	pop r30
	pop r16
	out __SREG__, r16
	pop r16
	reti
	STOP_5:
	lds r16, 193
	andi r16, 223
	sts 193, r16
	pop r31
	pop r30
	pop r16
	out __SREG__, r16
	pop r16
	reti
	
 ;  0 "" 2
/* #NOAPP */
/* epilogue start */
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
	std Z+15,__zero_reg__
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
 ;  201 "./src/main.cpp" 1
	cli
 ;  0 "" 2
/* #NOAPP */
	movw r30,r24
	ldi r26,lo8(buffer)
	ldi r27,hi8(buffer)
.L4:
	ld r24,Z+
	cpse r24,__zero_reg__
	rjmp .L5
	st X,__zero_reg__
	ldi r24,lo8(buffer)
	ldi r25,hi8(buffer)
	sts current_buffer+1,r25
	sts current_buffer,r24
	lds r24,193
	ori r24,lo8(32)
	sts 193,r24
/* #APP */
 ;  209 "./src/main.cpp" 1
	sei
 ;  0 "" 2
/* #NOAPP */
/* epilogue start */
	ret
.L5:
	st X+,r24
	rjmp .L4
	.size	_Z4savePKc, .-_Z4savePKc
	.section	.rodata.main.str1.1,"aMS",@progbits,1
.LC0:
	.string	"sdfghjkl"
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r24,lo8(.LC0)
	ldi r25,hi8(.LC0)
	call _Z4savePKc
	ldi r25,0
	ldi r24,0
/* epilogue start */
	ret
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
	.word	buffer+15
.global	buffer
	.section	.bss.buffer,"aw",@nobits
	.p2align	4
	.type	buffer, @object
	.size	buffer, 16
buffer:
	.zero	16
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
.global __do_copy_data
.global __do_clear_bss
