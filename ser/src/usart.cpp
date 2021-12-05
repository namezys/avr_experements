//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "usart.h"
//
//namespace savr::usart {
//    ControlA ctrl_a;
//    ControlB ctrl_b;
//    ControlC ctrl_c;
//}
//
//using namespace savr::usart;
//using namespace details;
//
//namespace savr::usart::details {
//    /// buffer for usart data, every item must have same high address
//    uint8_t buffer[buffer_size] __attribute__(( aligned(buffer_size))) = {};
//    /// current buffer position which should be send to usart
//    uint8_t *current_buffer_position = buffer;
//}
//
////// Send data from usart buffer using interruption
//////
////// On empty tx data register write next character from buffer
//ISR(USART_UDRE_vect, ISR_NAKED) {
//    asm volatile(
//    "\n\t"
//    // save state
//    "push r16\n\t"
//    "in r16, __SREG__\n\t"
//    "push r16\n\t"
//    "push r30\n\t"
//    "push r31\n\t"
//    // load buffer pointer and value
//    // high address can be loaded as high address of buffer
//    "lds r30, %[CUR_BUFFER_POS]\n\t"
//    "ldi r31, hi8(%[BUFF])\n\t"
//    "ld r16, Z+\n\t"
//    // check value and jump if necessary
//    "cpi r16, 0\n\t"
//    "breq STOP_%=\n\t"
//    // send to tx register and save new current buffer
//    // because of alignment, hi8 of this buffer will not changed
//    "sts %[RXD], r16\n\t"
//    "sts %[CUR_BUFFER_POS], r30\n\t"
//    // restore state
//    "pop r31\n\t"
//    "pop r30\n\t"
//    "pop r16\n\t"
//    "out __SREG__, r16\n\t"
//    "pop r16\n\t"
//    "reti\n\t"
//    // stop send using interrupt
//    "STOP_%=:\n\t"
//    "lds r16, %[USART_B]\n\t"
//    "andi r16, %[USART_B_INT_MASK]\n\t"
//    "sts %[USART_B], r16\n\t"
//    // restore state
//    "pop r31\n\t"
//    "pop r30\n\t"
//    "pop r16\n\t"
//    "out __SREG__, r16\n\t"
//    "pop r16\n\t"
//    "reti\n\t"
//    :
//    :[USART_B]"M"(&UCSR0B), [USART_B_INT_MASK]"M"(0xFF ^ (1 << UDRIE0)),
//    [RXD]"M"(&UDR0), [CUR_BUFFER_POS]"m"(current_buffer_position),
//    [BUFF]"m"(buffer)
//    );
//}