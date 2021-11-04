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
    uint8_t *tmp;
    asm volatile("CALL print_p2": "=z"(tmp): "z"(str), "m"(print_p2));
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
    const char *p = PSTR("ABCDE1");
    const char *p1 = PSTR("ABCDE2");
    const char *p2 = PSTR("ABCDE3");
    const char *p3 = PSTR("ABCDE4");
    const char *p4 = PSTR("ABCDE5");
    const char *p5 = PSTR("ABCD6");
    const char *p6 = PSTR("ABCDE7");
    const char *p7 = PSTR("ABCDE8");
    const char *p8 = PSTR("ABCDE9");
    const char *p9 = PSTR("ABCDEA");
    const char *p0 = PSTR("ABCDEB");
    const char *pa = PSTR("ABCDEC");
    const char *p00 = PSTR("0ABCDE1");
    const char *p10 = PSTR("0ABCDE2");
    const char *p20 = PSTR("0ABCDE3");
    const char *p30 = PSTR("0ABCDE4");
    const char *p40 = PSTR("0ABCDE5");
    const char *p50 = PSTR("0ABCD6");
    const char *p60 = PSTR("0ABCDE7");
    const char *p70 = PSTR("0ABCDE8");
    const char *p80 = PSTR("0ABCDE9");
    const char *p90 = PSTR("0ABCDEA");
    const char *pa0 = PSTR("0ABCDEC");
    
    
    
//    logger.print_p2(p);
//    logger.print_p2(p);
//    logger.print_p2(PSTR("SDFGHJKL:"));
while(1) {
    ppp(p);
    ppp(p1);
    ppp(p2);
    ppp(p3);
    ppp(p4);
    ppp(p5);
    ppp(p6);
    ppp(p7);
    ppp(p8);
    ppp(p9);
    ppp(p0);
    ppp(pa);
    ppp(p00);
    ppp(p10);
    ppp(p20);
    ppp(p30);
    ppp(p40);
    ppp(p50);
    ppp(p60);
    ppp(p70);
    ppp(p80);
    ppp(p90);
    ppp(pa0);
}
    
    //LOG_D("DDD");
    return 0x1122;
}