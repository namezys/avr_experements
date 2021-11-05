#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

extern "C" {
static_assert(usart::details::_usart_0_buffer_size < 255,
        "maximum 255 buffer size is supported because of optimization");
/// buffer for usart data, every item must have same high address
uint8_t _usart_0_buffer[usart::details::_usart_0_buffer_size + 1] __attribute__(( aligned(128)));
/// current buffer position which should be send to usart
uint8_t *_usart_0_current_buffer_position;
/// Transmission data register empty interrupt mask
const uint8_t USART_TX_EMPTY_INT_MASK = (1 << UDRIE0);

extern "C"
void _low_level_send_p_string_from_z() {
    uint8_t *tmp;
    asm volatile(
    "\n"
    // expect that address was put into register pair Z
    // repeat until we found zero character
    "LOAD_%=:\n\t"
    "lpm __zero_reg__, Z+\n\t"
    "tst __zero_reg__\n\t"
    // jump to end if found zero symbol
    "breq FINISH_%=\n"
    // check if register is empty
    "CHECK_%=:\n\t"
    "lds __tmp_reg__, %[USART_A]\n\t"
    "sbrs __tmp_reg__, %[RXD_EM_FL]\n\t"
    "rjmp CHECK_%=\n\t"
    // save register and repeat for next symbol
    "sts %[RXD], __zero_reg__\n\t"
    "rjmp LOAD_%=\n"
    "FINISH_%=:\n"
    // at the end we have zero in __zero_reg__
    :"=z"(tmp)
    :[RXD_EM_FL]"I"(UDRE0), [USART_A]"M"(&UCSR0A), [RXD]"M"(&UDR0)
    );
}

void _low_level_send_string_from_z() {
    uint8_t *tmp;
    asm volatile(
    "\n"
    // similar to _low_level_send_p_string_from_z
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

ISR(USART_UDRE_vect, ISR_NAKED) {
    asm volatile(
    "\n\t"
    // save state
    "push r16\n\t"
    "in r16, __SREG__\n\t"
    "push r16\n\t"
    "push r30\n\t"
    "push r31\n\t"
    // load buffer pointer and value
    // high address can be loaded as high address of buffer
    "lds r30, _usart_0_current_buffer_position\n\t"
    "ldi r31, hi8(_usart_0_buffer)\n\t"
    "ld r16, Z+\n\t"
    // check value and jump if necessary
    "cpi r16, 0\n\t"
    "breq STOP_%=\n\t"
    // send to tx register and save new current buffer
    // because of alignment, hi8 of this buffer will not changed
    "sts %[RXD], r16\n\t"
    "sts _usart_0_current_buffer_position, r30\n\t"
    // restore state
    "pop r31\n\t"
    "pop r30\n\t"
    "pop r16\n\t"
    "out __SREG__, r16\n\t"
    "pop r16\n\t"
    "reti\n\t"
    // stop send using interrupt
    "STOP_%=:\n\t"
    "lds r16, %[USART_B]\n\t"
    "andi r16, %[USART_B_INT_MASK]\n\t"
    "sts %[USART_B], r16\n\t"
    // restore state
    "pop r31\n\t"
    "pop r30\n\t"
    "pop r16\n\t"
    "out __SREG__, r16\n\t"
    "pop r16\n\t"
    "reti\n\t"
    :
    :[USART_B]"M"(&UCSR0B), [USART_B_INT_MASK]"M"(0xFF ^ USART_TX_EMPTY_INT_MASK),
    [RXD]"M"(&UDR0), "m"(_usart_0_current_buffer_position), "m"(_usart_0_buffer)
    );
}

}