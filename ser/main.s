	.file	"main.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.text.unlikely._Z5setupv,"ax",@progbits
.global	_Z5setupv
	.type	_Z5setupv, @function
_Z5setupv:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.size	_Z5setupv, .-_Z5setupv
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
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
	ldi r18,lo8(45)
.L7:
	ldi r30,lo8(_ZZ4mainE3__c)
	ldi r31,hi8(_ZZ4mainE3__c)
.L5:
/* #APP */
 ;  61 "./src/main.cpp" 1
	lpm r24, Z+
 ;  0 "" 2
/* #NOAPP */
	tst r24
	breq .L8
.L4:
	lds r25,192
	sbrs r25,5
	rjmp .L4
	sts 198,r24
	rjmp .L5
.L8:
	ldi r24,lo8(100)
	ldi r25,0
.L6:
	lds r19,192
	sbrs r19,5
	rjmp .L6
	sts 198,r18
	sbiw r24,1
	brne .L6
	rjmp .L7
	.size	main, .-main
	.section	.progmem.data._ZZ4mainE3__c,"a"
	.type	_ZZ4mainE3__c, @object
	.size	_ZZ4mainE3__c, 28
_ZZ4mainE3__c:
	.string	"ABCDE0987654321\302\2471234567890"
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
