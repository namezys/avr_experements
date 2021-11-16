#include <avr/pgmspace.h>
#include <util/delay.h>

#include "usart.h"
#include "reset_status.h"
#include "port.h"
#include "loggger.h"


#define IO(mnemonic, value) __attribute__((io(value + __SFR_OFFSET)))
#define MEM(mnemonic, value) __attribute__((address(value)))

namespace sarv {
    namespace timer_counter_0_A {
        enum class WaveformGenerationMode {
            // increment, 0x00 - 0xFF[signal and clear counter]
            normal,
            // increment, 0x00 - [signal and clear counter]
            compare_match,
            // increment, 0x00 - [signal] - 0xFF [clear counter]
            fast_pwm,
            // increment and decrement 0x00 - [signal] - 0xFF - [signal] - 0x00
            phase_correction_pwm,
            
        };
        
        namespace control {
            volatile uint8_t a IO(TCCR0A, 0x24);
            volatile uint8_t b IO(TCCR0B, 0x25);
            
            const uint8_t clock_mask = (1 << CS02) | (1 << CS01) | (1 << CS00);
            const uint8_t io_clock = (1 << CS00);
            const uint8_t io_clock_8 = (1 << CS01);
            const uint8_t io_clock_64 = (1 << CS01) | (1 << CS00);
            const uint8_t io_clock_256 = (1 << CS02);
            const uint8_t io_clock_1024 = (1 << CS02) | (1 << CS00);
            const uint8_t external_clock_falling_edge = (1 << CS02) | (1 << CS01);
            const uint8_t external_clock_rising_edge = (1 << CS02) | (1 << CS01) | (1 << CS00);
        }
        
        volatile uint8_t counter IO(TCNT0, 0x26);
        volatile uint8_t compare_a IO(OCR0A, 0x27);
        volatile uint8_t compare_b IO(OCR0B, 0x28);
        
        
        namespace interrupt_mask {
            const uint8_t match_b = 1 << OCIE0B;
            const uint8_t match_a = 1 << OCIE0A;
            const uint8_t overflow = 1 << TOIE0;
            
            volatile uint8_t value MEM(TIMSK0, 0x6E);
        }
        
        namespace interrupt_flags {
            const uint8_t match_b = 1 << OCF0B;
            const uint8_t match_a = 1 << OCF0A;
            const uint8_t overflow = 1 << TOV0;
            
            volatile uint8_t value IO(TIFR0, 0x15);
        }
        
        
        
        volatile uint8_t v __attribute__((io(0x24 + __SFR_OFFSET)));
        
        template<class Mode>
        class TC {
        
        };
    }
}

void test()
{

}

sarv::logging::SyncLogger<
        sarv::logging::Level::Debug,
        sarv::usart::Usart<sarv::usart::AsyncClock<9600, true>>
        > logger;

int main() {
    using namespace sarv;
    
    INFO("Start");
    port::Output<port::PortB, 2> output;
    port::Input<port::PortB, 0> input;
    _delay_ms(1000);
    
    DEBUG("Start cycle");
    bool current_state = input;
    
    uint8_t c8 = 0;
    uint8_t c16 = 0;
    while(true) {
        _delay_ms(1000);
        INFO("TEST8", c8);
        INFO("TEST16", c16);
        c8 += 3;
        c16 += c8;
        if (!current_state) {
            DEBUG("Send high");
        } else {
            DEBUG("Send low");
        }
        output = !current_state;
        
        if (current_state) {
            if (!input) {
                INFO("Go to lower current_state");
            }
        } else {
            if (input) {
                INFO("Go to high current_state");
            }
        }
        current_state = input;
    }
}