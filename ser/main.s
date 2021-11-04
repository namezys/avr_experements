	.file	"main.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
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
	ldi r18,lo8(43)
.L5:
	std Y+1,__zero_reg__
	std Y+2,__zero_reg__
	std Y+3,__zero_reg__
	std Y+4,__zero_reg__
.L2:
	ldd r24,Y+1
	ldd r25,Y+2
	ldd r26,Y+3
	ldd r27,Y+4
	cp r24,__zero_reg__
	sbci r25,106
	sbci r26,24
	cpc r27,__zero_reg__
	brlo .L3
.L4:
	lds r24,192
	sbrs r24,5
	rjmp .L4
	sts 198,r18
	rjmp .L5
.L3:
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
	rjmp .L2
	.size	main, .-main
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
