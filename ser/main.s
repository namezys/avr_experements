	.file	"main.cpp"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
	.section	.text.print_p2,"ax",@progbits
.global	print_p2
	.type	print_p2, @function
print_p2:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
/* #APP */
 ;  84 "./src/main.cpp" 1
	
LOAD_5:
	lpm __zero_reg__, Z+
	tst __zero_reg__
	breq FINISH_5
CHECK_5:
	lds __tmp_reg__, 192
	sbrs __tmp_reg__, 5
	rjmp CHECK_5
	sts 198, __zero_reg__
	rjmp LOAD_5
FINISH_5:

 ;  0 "" 2
/* #NOAPP */
/* epilogue start */
	ret
	.size	print_p2, .-print_p2
	.section	.text._Z5setupv,"ax",@progbits
.global	_Z5setupv
	.type	_Z5setupv, @function
_Z5setupv:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	ldi r25,0
	ldi r24,0
/* epilogue start */
	ret
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
	ldi r24,lo8(_ZZ4mainE3__c)
	ldi r25,hi8(_ZZ4mainE3__c)
.L4:
	movw r30,r24
/* #APP */
 ;  105 "./src/main.cpp" 1
	CALL print_p2
 ;  0 "" 2
/* #NOAPP */
	movw r30,r24
/* #APP */
 ;  105 "./src/main.cpp" 1
	CALL print_p2
 ;  0 "" 2
/* #NOAPP */
	rjmp .L4
	.size	main, .-main
	.section	.progmem.data._ZZ4mainE3__c,"a"
	.type	_ZZ4mainE3__c, @object
	.size	_ZZ4mainE3__c, 6
_ZZ4mainE3__c:
	.string	"ABCDE"
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
