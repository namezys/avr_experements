	.file	"main.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.rodata._Z5setupv.str1.1,"aMS",@progbits,1
.LC0:
	.string	"ABCDE0987654321\302\2471234567890"
	.section	.text._Z5setupv,"ax",@progbits
.global	_Z5setupv
	.type	_Z5setupv, @function
_Z5setupv:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	sts 197,__zero_reg__
	ldi r24,lo8(-49)
	sts 196,r24
	ldi r24,lo8(2)
	sts 192,r24
	ldi r24,lo8(24)
	sts 193,r24
	ldi r24,lo8(6)
	sts 194,r24
.L2:
	lds r24,192
	sbrs r24,5
	rjmp .L2
	ldi r24,lo8(12)
	sts 198,r24
.L3:
	rjmp .L3
	.size	_Z5setupv, .-_Z5setupv
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	call _Z5setupv
	.size	main, .-main
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
.global __do_copy_data
