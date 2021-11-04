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
    
    inline
    void print_p2(const char* str) {
        uint8_t *tmp;
        asm volatile("\n"
                "LOAD_%=:\n\t"
                "lpm __zero_reg__, Z+\n\t"
                "tst __zero_reg__\n\t"
                "breq FINISH_%=\n"
                "CHECK_%=:\n\t"
                "lds __tmp_reg__, %[USART_A]\n\t"
                "sbrs __tmp_reg__, %[RXD_EM_FL]\n\t"
                "rjmp CHECK_%=\n\t"
                "sts %[RXD], __zero_reg__\n\t"
                "rjmp LOAD_%=\n"
                "FINISH_%=:\n"
                :"=z"(tmp)
                :"z"(str), [RXD_EM_FL]"I"(UDRE0), [USART_A]"M"(&UCSR0A), [RXD]"M"(&UDR0)
                :
                );
    }
    
    inline
    void ppp(const char* str) {
        asm volatile(
                "AAAA"
                :
                :"z"(str));
    }
};

extern "C"
void print_p2() {
    uint8_t *tmp;
    asm volatile("\n"
                 "LOAD_%=:\n\t"
                 "lpm __zero_reg__, Z+\n\t"
                 "tst __zero_reg__\n\t"
                 "breq FINISH_%=\n"
                 "CHECK_%=:\n\t"
                 "lds __tmp_reg__, %[USART_A]\n\t"
                 "sbrs __tmp_reg__, %[RXD_EM_FL]\n\t"
                 "rjmp CHECK_%=\n\t"
                 "sts %[RXD], __zero_reg__\n\t"
                 "rjmp LOAD_%=\n"
                 "FINISH_%=:\n"
    :"=z"(tmp)
    :[RXD_EM_FL]"I"(UDRE0), [USART_A]"M"(&UCSR0A), [RXD]"M"(&UDR0)
    :
    );
}

inline
void ppp(const char* str) {
    asm volatile("CALL print_p2"::"z"(str), "m"(print_p2));
}

int setup() {
    return 0;
}

enum class Level {
    Error,
    Info,
    Debug
};

template<Level _level, class LogStream>
class Logger: public LogStream {
private:
    static const Level level = _level;
    
    static
    bool is_error_enabled() {
        return is_info_enabled() || level == Level::Error;
    }
    
    static
    bool is_info_enabled() {
        return is_debug_enabled() || level == Level::Error;
    }
    
    static
    bool is_debug_enabled() {
        return level == Level::Debug;
    }
    
public:
    void log_info_p(const char* str) {
        if(!is_info_enabled()) {
            return;
        }
        LogStream::print_p("I: ");
        LogStream::print_p(str);
        LogStream::send('\n');
    }
};

#define LOG_I(data) logger.log_info_p(PSTR(data))

int main() {
    Logger<Level::Debug, Stream<usart::Usart<usart::AsyncInternalClock<9600, true>>>> logger;
    const char *p = PSTR("ABCDE");
//    logger.print_p2(p);
//    logger.print_p2(p);
//    logger.print_p2(PSTR("SDFGHJKL:"));
while(1) {
    ppp(PSTR("asdfghjkl"));
}
    
    //LOG_D("DDD");
    return 0x1122;
}