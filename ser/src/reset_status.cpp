#include "reset_status.h"

namespace sarv {
    namespace details {
        static
        uint8_t _mcusr_value_init() {
            const uint8_t value = MCUSR;
            MCUSR = 0;
            return value;
        }
    
        uint8_t _mcusr_value = _mcusr_value_init();
    
        static
        uint8_t _mcusr_value_init2() {
            const uint8_t value = MCUCR;
            MCUSR = 0;
            return value;
        }
    
        uint8_t _mcusr_value2 = _mcusr_value_init2();
    }
}