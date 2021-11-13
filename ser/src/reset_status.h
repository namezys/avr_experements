#include <avr/io.h>

#pragma once

namespace sarv {
    
    namespace details {
        extern uint8_t _mcusr_value;
    }
    
    /** Access to reset reason */
    class ResetReason {
        static inline
        bool _test_flag(uint8_t byte_position) {
            return details::_mcusr_value && static_cast<uint8_t>(1 << byte_position);
        }
        
    public:
        static bool is_watch_dog()
        {
            return _test_flag(WDRF);
        }
        
        static bool is_brown_out()
        {
            return _test_flag(BORF);
        }
        
        static bool is_external()
        {
            return _test_flag(EXTRF);
        }
        
        static bool is_power_on()
        {
            return _test_flag(PORF);
        }
    };
    
    
}