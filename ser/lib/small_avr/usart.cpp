#include <avr/io.h>

extern "C"
void _low_level_send_p_string_from_z() {
    uint8_t *tmp;
    asm volatile(
    "\n"
    "LOAD_%=:\n\t"
    "lpm __zero_reg__, Z+\n\t"
    "tst __zero_reg__\n\t"
    "breq FINISH_%=\n"
    "CHECK_%=:\n\t"
    "lds __tmp_reg__, %[USART_A]\n\t"
    "sbrs __tmp_reg__, %[RXD_EM_FL]\n\t"
    "rjmp CHECK_%=\n\t"
    "sts %[RXD], __zero_reg__\n\t"
    "rjmp LOAD_%=\n"
    "FINISH_%=:\n"
    :"=z"(tmp)
    :[RXD_EM_FL]"I"(UDRE0), [USART_A]"M"(&UCSR0A), [RXD]"M"(&UDR0)
    );
}

extern "C"
void _low_level_send_string_from_z() {
    uint8_t *tmp;
    asm volatile(
    "\n"
    "LOAD_%=:\n\t"
    "ld __zero_reg__, Z+\n\t"
    "tst __zero_reg__\n\t"
    "breq FINISH_%=\n"
    "CHECK_%=:\n\t"
    "lds __tmp_reg__, %[USART_A]\n\t"
    "sbrs __tmp_reg__, %[RXD_EM_FL]\n\t"
    "rjmp CHECK_%=\n\t"
    "sts %[RXD], __zero_reg__\n\t"
    "rjmp LOAD_%=\n"
    "FINISH_%=:\n"
    :"=z"(tmp)
    :[RXD_EM_FL]"I"(UDRE0), [USART_A]"M"(&UCSR0A), [RXD]"M"(&UDR0)
    );
}

//
//   b4:	fc 01       	movw	r30, r24
//  b6:	91 91       	ld	r25, Z+
//  b8:	99 23       	and	r25, r25
//  ba:	39 f0       	breq	.+14     	; 0xca <_ZN5usart5UsartINS_18AsyncInternalClockILm9600ELb1EEENS_5FrameILh8ELh1ELNS_10ParityModeE0EEELb1ELb1ENS_10DummyStateEE11send_stringEPKc.isra.3+0x16>
//  bc:	80 91 c0 00 	lds	r24, 0x00C0	; 0x8000c0 <__TEXT_REGION_LENGTH__+0x7e00c0>
//  c0:	85 ff       	sbrs	r24, 5
//  c2:	fc cf       	rjmp	.-8      	; 0xbc <_ZN5usart5UsartINS_18AsyncInternalClockILm9600ELb1EEENS_5FrameILh8ELh1ELNS_10ParityModeE0EEELb1ELb1ENS_10DummyStateEE11send_stringEPKc.isra.3+0x8>
//  c4:	90 93 c6 00 	sts	0x00C6, r25	; 0x8000c6 <__TEXT_REGION_LENGTH__+0x7e00c6>
//  c8:	f6 cf       	rjmp	.-20     	; 0xb6 <_ZN5usart5UsartINS_18AsyncInternalClockILm9600ELb1EEENS_5FrameILh8ELh1ELNS_10ParityModeE0EEELb1ELb1ENS_10DummyStateEE11send_stringEPKc.isra.3+0x2>
//  ca:	08 95       	ret