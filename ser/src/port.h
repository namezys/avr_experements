#pragma once

#include <avr/io.h>


namespace sarv {
    
    namespace port {
        namespace B {
            extern volatile uint8_t pin __attribute__((io (0x03 + __SFR_OFFSET)));
            extern volatile uint8_t ddr __attribute__((io (0x04 + __SFR_OFFSET)));
            extern volatile uint8_t port __attribute__((io (0x05 + __SFR_OFFSET)));
        }
    
        namespace C {
            extern volatile uint8_t pin __attribute__((io (0x06 + __SFR_OFFSET)));
            extern volatile uint8_t ddr __attribute__((io (0x07 + __SFR_OFFSET)));
            extern volatile uint8_t port __attribute__((io (0x08 + __SFR_OFFSET)));
        }
    
        namespace D {
            extern volatile uint8_t pin __attribute__((io (0x09 + __SFR_OFFSET)));
            extern volatile uint8_t ddr __attribute__((io (0x0A + __SFR_OFFSET)));
            extern volatile uint8_t port __attribute__((io (0x0B + __SFR_OFFSET)));
        }
    
        template<uint8_t bit>
        class PortBit {
        public:
            static_assert(0 <= bit && bit < 8, "Invalid port bit");
        
            static const uint8_t mask = (1 << bit);
            static const uint8_t inv_mask = ~mask;
        };
    
        template<volatile uint8_t& pin, volatile uint8_t& ddr, volatile uint8_t& port>
        class Port {
    
        protected:
            Port() = default;
    
        public:
        
            template<uint8_t bit>
            bool is_output() const {
                return ddr & PortBit<bit>::mask;
            }
        
            template<uint8_t bit>
            void set_output() {
                ddr |= PortBit<bit>::mask;
            }
        
            template<uint8_t bit>
            bool is_input() const {
                return !is_output<bit>();
            }
        
            template<uint8_t bit>
            void set_input(bool pull_up) {
                using Bit = PortBit<bit>;
                if (pull_up) {
                    port |= Bit::mask;
                } else {
                    port &= Bit::mask;
                }
                ddr &= Bit::inv_mask;
            }
        
            template<uint8_t bit>
            bool get_input_value() const {
                return  pin & PortBit<bit>::mask;
            }
        
            template<uint8_t bit>
            void set_output_value(bool is_high) {
                using Bit = PortBit<bit>;
                if (is_high) {
                    port |= Bit::mask;
                } else {
                    port &= Bit::inv_mask;
                }
            }
        };
    
        class PortB: public Port<B::pin, B::ddr, B::port> {
        public:
            PortB() = default;
        };
    
        template<class Port, uint8_t bit>
        class Output: public Port, protected PortBit<bit> {
        public:
            explicit Output(bool a_init = true) {
                if(a_init) {
                    init();
                }
            }
        
            void init() {
                Port::template set_output<bit>();
            }
        
            void set(bool is_high) {
                Port::template set_output_value<bit>(is_high);
            }
        
            void set_high() {
                set(true);
            }
        
            void set_low() {
                set(false);
            }
        };
    }
}