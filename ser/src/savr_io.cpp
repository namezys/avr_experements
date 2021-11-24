#include "savr_io.h"

namespace savr {
    namespace regs {
        volatile uint8_t status IO(SREG, 0x3F);
        volatile uint8_t mcu_status IO(MCUSR, 0x34);
        volatile uint8_t watch_dog MEM(WDTCSR, 0x60);
    }
    
    namespace usart::regs {
        volatile uint8_t baud_rate_low MEM(UBRR0L, 0xc4);
        volatile uint8_t baud_rate_high MEM(UBRR0H, 0xc5);
        volatile uint8_t data MEM(UDR0, 0xC6);
        volatile uint8_t control_a MEM(UCSR0A, 0xC0);
        volatile uint8_t control_b MEM(UCSR0B, 0xC1);
        volatile uint8_t control_c MEM(UCSR0C, 0xC2);
    }

    namespace port {
        namespace B {
            volatile uint8_t pin IO(PINB, 0x03);
            volatile uint8_t ddr IO(DDRB, 0x04);
            volatile uint8_t port IO(PORTB, 0x05);
        }

        namespace C {
            volatile uint8_t pin IO(PINC, 0x06);
            volatile uint8_t ddr IO(DDRC, 0x07);
            volatile uint8_t port IO(PORTC, 0x08);
        }

        namespace D {
            volatile uint8_t pin IO(PIND, 0x09);
            volatile uint8_t ddr IO(DDRD, 0x0A);
            volatile uint8_t port IO(PORTD, 0x0B);
        }
    }
    
    namespace timer_0::regs {
        volatile uint8_t control_a IO(TCCR0A, 0x24);
        volatile uint8_t control_b IO(TCCR0B, 0x25);
        volatile uint8_t counter IO(TCNT0, 0x26);
        volatile uint8_t output_compare_a IO(OCR0A, 0x27);
        volatile uint8_t output_compare_b IO(OCR0B, 0x28);
        volatile uint8_t interrupt_mask MEM(TIMSK0, 0x6E);
        volatile uint8_t interrupt_flag IO(TIFR0, 0x15);
    }
};
