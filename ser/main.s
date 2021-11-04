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
	.section	.text._ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc,"axG",@progbits,_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc,comdat
	.weak	_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc
	.type	_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc, @function
_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	movw r30,r22
/* #APP */
 ;  54 "./src/main.cpp" 1
	
LOAD_27:
	lpm __zero_reg__, Z+
	tst __zero_reg__
	breq FINISH_27
CHECK_27:
	lds __tmp_reg__, 192
	sbrs __tmp_reg__, 5
	rjmp CHECK_27
	sts 198, __zero_reg__
	rjmp LOAD_27
FINISH_27:

 ;  0 "" 2
/* #NOAPP */
/* epilogue start */
	ret
	.size	_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc, .-_ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc
	.section	.text.startup.main,"ax",@progbits
.global	main
	.type	main, @function
main:
	push __tmp_reg__
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 1 */
/* stack size = 1 */
.L__stack_usage = 1
	sts 197,__zero_reg__
	ldi r24,lo8(-49)
	sts 196,r24
	ldi r24,lo8(2)
	sts 192,r24
	ldi r24,lo8(24)
	sts 193,r24
	ldi r24,lo8(6)
	sts 194,r24
	ldi r22,lo8(_ZZ4mainE3__c)
	ldi r23,hi8(_ZZ4mainE3__c)
	movw r24,r28
	adiw r24,1
	call _ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc
	ldi r22,lo8(_ZZ4mainE3__c)
	ldi r23,hi8(_ZZ4mainE3__c)
	movw r24,r28
	adiw r24,1
	call _ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc
	ldi r22,lo8(_ZZ4mainE3__c_0)
	ldi r23,hi8(_ZZ4mainE3__c_0)
	movw r24,r28
	adiw r24,1
	call _ZN6StreamIN5usart5UsartINS0_18AsyncInternalClockILm9600ELb1EEENS0_5FrameILh8ELh1ELNS0_10ParityModeE0EEELb1ELb1ENS0_10DummyStateEEEE8print_p2EPKc
	ldi r30,lo8(_ZZ4mainE3__c_1)
	ldi r31,hi8(_ZZ4mainE3__c_1)
/* #APP */
 ;  104 "./src/main.cpp" 1
	CALL print_p2
 ;  0 "" 2
/* #NOAPP */
	ldi r24,lo8(34)
	ldi r25,lo8(17)
/* epilogue start */
	pop __tmp_reg__
	ret
	.size	main, .-main
	.section	.progmem.data._ZZ4mainE3__c_1,"a"
	.type	_ZZ4mainE3__c_1, @object
	.size	_ZZ4mainE3__c_1, 10
_ZZ4mainE3__c_1:
	.string	"asdfghjkl"
	.section	.progmem.data._ZZ4mainE3__c_0,"a"
	.type	_ZZ4mainE3__c_0, @object
	.size	_ZZ4mainE3__c_0, 10
_ZZ4mainE3__c_0:
	.string	"SDFGHJKL:"
	.section	.progmem.data._ZZ4mainE3__c,"a"
	.type	_ZZ4mainE3__c, @object
	.size	_ZZ4mainE3__c, 6
_ZZ4mainE3__c:
	.string	"ABCDE"
	.ident	"GCC: (Homebrew AVR GCC 11.1.0_1) 11.1.0"
