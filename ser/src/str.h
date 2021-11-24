#pragma once

#include <avr/pgmspace.h>

namespace savr::details {
    class BaseStr {
    protected:
        const char *_ptr;
    
    public:
        BaseStr(const char *ptr) : _ptr(ptr) {}
    
        [[maybe_unused]]
        void incr() {
            _ptr++;
        }
    
        [[maybe_unused]] [[nodiscard]]
        const char *ptr() const {
            return _ptr;
        }
    
        [[maybe_unused]]
        void operator++() {
            incr();
        }
    
        [[maybe_unused]]
        void operator++(int) {
            incr();
        }
    };
}

namespace savr {
    
    /** Store string as address which is located in RAM space */
    class ConstStr: public details::BaseStr {
    public:
        using BaseStr::BaseStr;
        
        /** Get current value at address */
        [[maybe_unused]] [[nodiscard]]
        char get() const {
            return *_ptr;
        }
    
        [[maybe_unused]] [[nodiscard]]
        char operator*() const {
            return get();
        }
    };
    
    /** Store string as address which is located in flash (ROM) space */
    class PmStr: public details::BaseStr {
    public:
        using BaseStr::BaseStr;
        
        /** Get current value at address */
        [[maybe_unused]] [[nodiscard]]
        char get() const { // NOLINT
            return pgm_read_byte(_ptr);
        }
    
        [[maybe_unused]] [[nodiscard]]
        char operator*() const {
            return get();
        }
    };
    
}

/** Put string literal into flash/ROM and wrap it */
#define P(value) savr::PmStr(PSTR(value))
/** Put string literal into RAM and wrap it */
#define S(value) savr::ConstStr(value)

/** Put string literal into flash/ROM with new line at the end of string and wrap it */
#define PN(value) P(value "\n")
/** Put string literal into RAM with new line at the end of string and wrap it */
#define SN(value) P(value "\n")
