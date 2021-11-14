#include "port.h"

namespace sarv {
    
    namespace port {
        namespace B {
            volatile uint8_t pin __attribute__((io (0x03 + __SFR_OFFSET)));
            volatile uint8_t ddr __attribute__((io (0x04 + __SFR_OFFSET)));
            volatile uint8_t port __attribute__((io (0x05 + __SFR_OFFSET)));
        }
        
        namespace C {
            volatile uint8_t pin __attribute__((io (0x06 + __SFR_OFFSET)));
            volatile uint8_t ddr __attribute__((io (0x07 + __SFR_OFFSET)));
            volatile uint8_t port __attribute__((io (0x08 + __SFR_OFFSET)));
        }
        
        namespace D {
            volatile uint8_t pin __attribute__((io (0x09 + __SFR_OFFSET)));
            volatile uint8_t ddr __attribute__((io (0x0A + __SFR_OFFSET)));
            volatile uint8_t port __attribute__((io (0x0B + __SFR_OFFSET)));
        }
    }
}
