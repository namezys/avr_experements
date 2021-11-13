#pragma once

#include <avr/pgmspace.h>

namespace sarv {
    
    
    class BaseStr {
    protected:
        const char* _ptr;
        
    public:
        explicit BaseStr(const char* ptr): _ptr(ptr)
        {}
        
        void incr() {
            _ptr++;
        }
    };
    
    class ConstStr: public BaseStr {
    public:
        using BaseStr::BaseStr;
        
        char get() const {
            return *_ptr;
        }
        
        char operator*() const {
            return get();
        }
    };
    
    class PmStr: public BaseStr {
    public:
        using BaseStr::BaseStr;
    
        char get() const {
            return pgm_read_byte(_ptr);
        }
    
        char operator*() const {
            return get();
        }
    };
    
}

#define P(x) sarv::PmStr(PSTR(x))
#define S(x) sarv::ConstStr(x)