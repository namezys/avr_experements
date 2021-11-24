#pragma once

#include "attrs.h"
#include "registers.h"

namespace savr {
    
    /** Global registers */
    namespace regs {
        extern volatile uint8_t status EXTERN_IO(SREG, 0x3F);
        extern volatile uint8_t mcu_status EXTERN_IO(MCUSR, 0x34);
        extern volatile uint8_t watch_dog EXTERN_MEM(WDTCSR, 0x60);
    }
    
    /** Register for USART */
    namespace usart::regs {
        using namespace savr::regs;
        
        extern volatile uint8_t baud_rate_low EXTERN_MEM(UBRR0L, 0xc4);
        extern volatile uint8_t baud_rate_high EXTERN_MEM(UBRR0H, 0xc5);
        extern volatile uint8_t data EXTERN_MEM(UDR0, 0xC6);
        extern volatile uint8_t control_a EXTERN_MEM(UCSR0A, 0xC0);
        extern volatile uint8_t control_b EXTERN_MEM(UCSR0B, 0xC1);
        extern volatile uint8_t control_c EXTERN_MEM(UCSR0C, 0xC2);
    }
    
    /** Registers for GPIO ports */
    namespace port {
        namespace B {
            extern volatile uint8_t pin EXTERN_IO(PINB, 0x03);
            extern volatile uint8_t ddr EXTERN_IO(DDRB, 0x04);
            extern volatile uint8_t port EXTERN_IO(PORTB, 0x05);
        }
        
        namespace C {
            extern volatile uint8_t pin EXTERN_IO(PINC, 0x06);
            extern volatile uint8_t ddr EXTERN_IO(DDRC, 0x07);
            extern volatile uint8_t port EXTERN_IO(PORTC, 0x08);
        }
        
        namespace D {
            extern volatile uint8_t pin EXTERN_IO(PIND, 0x09);
            extern volatile uint8_t ddr EXTERN_IO(DDRD, 0x0A);
            extern volatile uint8_t port EXTERN_IO(PORTD, 0x0B);
        }
    }
    
    namespace timer_0::regs {
        extern volatile uint8_t control_a EXTERN_IO(TCCR0A, 0x24);
        extern volatile uint8_t control_b EXTERN_IO(TCCR0B, 0x25);
        extern volatile uint8_t counter EXTERN_IO(TCNT0, 0x26);
        extern volatile uint8_t output_compare_a EXTERN_IO(OCR0A, 0x27);
        extern volatile uint8_t output_compare_b EXTERN_IO(OCR0B, 0x28);
        extern volatile uint8_t interrupt_mask EXTERN_MEM(TIMSK0, 0x6E);
        extern volatile uint8_t interrupt_flag EXTERN_IO(TIFR0, 0x15);
    }
};
