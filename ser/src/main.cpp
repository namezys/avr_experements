#include <usart.h>
#include <avr/pgmspace.h>

// #include <Arduino.h>

//class PStr {
//public:
//    const char* ptr;
//public:
//    explicit
//    PStr(const char* a_ptr): ptr(a_ptr) {
//    }
//
//    PStr operator+(uint8_t a) {
//        return PStr(ptr + a);
//    }
//
//    char load() const{
//        return pgm_read_byte(ptr);
//    }
//
//};
//
//template<class Output>
//class Stream: public Output {
//public:
//    inline
//    void print_string(const char* str) {
//        while(*str != 0) {
//            Output::send(*str);
//            str++;
//        }
//    }
//};
//
//
//int setup() {
//    return 0;
//}
//
//enum class Level {
//    Error,
//    Info,
//    Debug
//};
//
//template<Level _level, class LogStream>
//class Logger: public LogStream {
//private:
//    static const Level level = _level;
//
//    static
//    bool is_error_enabled() {
//        return is_info_enabled() || level == Level::Error;
//    }
//
//    static
//    bool is_info_enabled() {
//        return is_debug_enabled() || level == Level::Error;
//    }
//
//    static
//    bool is_debug_enabled() {
//        return level == Level::Debug;
//    }
//
//public:
//    void log_info_p(const char* str) {
//        if(!is_info_enabled()) {
//            return;
//        }
//        LogStream::print_p("I: ");
//        LogStream::print_p(str);
//        LogStream::send('\n');
//    }
//};
//
//
//
//#define LOG_I(data) logger.log_info_p(PSTR(data))

#include <avr/interrupt.h>



//void init()
//{
//    buffer[size] = 0;
//    current_buffer = buffer;
//}
//
//void send()
//{
//    current_buffer++;
//    uint8_t value = *current_buffer;
//    if (value) {
//        asm volatile("AAAA");
//    } else {
//        asm volatile("HJKHK"::"r"(value));
//    }
//}

const uint8_t size = 32;
uint8_t buffer[size + 1] __attribute__(( aligned(32) ));
const uint8_t* buffer_end = buffer + size;
uint8_t* current_buffer;


ISR(USART_UDRE_vect)
{
    if (*current_buffer == 0) {
        UCSR0B = UCSR0B & ~(1 << UDRIE0);
    } else {
        UDR0 = *current_buffer;
        current_buffer++;
    }
}

void init()
{
    buffer[0] = 0;
    buffer[size] = 0;
}

void save(const char* str)
{
    cli();
    uint8_t* b = buffer;
    for(;*str != 0; ++str, ++b) {
        *b = *str;
    }
    *b = 0;
    current_buffer = buffer;
    UCSR0B = UCSR0B | (1 << UDRIE0);
    sei();
}

int main() {
    usart::Usart<usart::AsyncInternalClock<9600, true>> u; u.init();
    init();
    while(1) {
        save("sdfghjkl");
        
        for(volatile uint32_t i = 0; i < F_CPU / 30;) {
            i = i + 1;
        }
        //u.send('+');
    }
//    init();
//    send();
    
//    Logger<Level::Debug, Stream<usart::Usart<usart::AsyncInternalClock<9600, true>>>> logger;
//    const char *p = PSTR("ABCDE1");
//    const char *s = "qwertyuiop";
//    const char *ss = "qdkljdwdjkldertdkjljdyuiop";
//
//    logger.send_string(s);
//    logger.send_string(ss);
//    logger.send_pm_string(p);
//
    //LOG_D("DDD");

    return 0x1122;
}