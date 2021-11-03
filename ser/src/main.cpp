#include "usart.h"
#include <avr/pgmspace.h>

// #include <Arduino.h>

class PStr {
public:
    const char* ptr;
public:
    explicit
    PStr(const char* a_ptr): ptr(a_ptr) {
    }
    
    PStr operator+(uint8_t a) {
        return PStr(ptr + a);
    }
  
    char load() const{
        return pgm_read_byte(ptr);
    }
    
};

template<class Output>
class Stream: public Output {
public:
    inline
    void print_string(const char* str) {
        while(*str != 0) {
            Output::send(*str);
            str++;
        }
    }
    
    inline
    void print_string_P(PStr str) {
//        for(auto c = str.load(); c != 0;) {
//            Output::send(c);
//            str = str + 1;
//            c = str.load();
//        }
        auto s = str.ptr;
        do {
            uint8_t value = 1;
            __asm__(
                "lpm %0, Z+"
                : "=r"(value), "=z"(s)
                : "z"(s)
            );
            if (value == 0) {
                return;
            }
            //Output::send(value);
        } while(true);
    }
    
    inline
    void print_p(const char* str) {
        do {
            uint8_t value;
            __asm__(
                    "lpm %0, Z+"
                    : "=r"(value), "=z"(str)
                    : "z"(str)
                    );
            if(value == 0) {
                return;
            }
            Output::send(value);
        } while(true);
    }
};



int setup() {

}

int main() {
    const char* p = PSTR("ABCDE0987654321§1234567890");
    
    Stream<usart::Usart<usart::AsyncInternalClock<9600, true>>> u;
    //u.send('A');
    while(1) {
        u.print_p(p);
        for(int i = 0; i < 100; ++i) {
            u.send('-');
        }
    }
    return 0x1122;
}