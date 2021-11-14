#include <avr/pgmspace.h>
#include <util/delay.h>

#include "usart.h"
#include "reset_status.h"
#include "port.h"

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

template<uint8_t _stack_size = 64>
class Task {
private:
    uint8_t _r2;
    uint8_t _r3;
    uint8_t _sreg;
    uint8_t _stack[_stack_size];

public:
    
    void give() {
        asm volatile(
                "sts %[S_R2], r2\n\t"
                "sts %[S_R3], r3\n\t"
                :
                [S_R2]"=m"(_r2),
                [S_R3]"=m"(_r3)
                :
                :
                    "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
                    "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20",
                    "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
                );
    }
};

void schedule() {}

void resume()
{
}

void suspend()
{
}

/// Disable pull up for all I/O ports
///
/// Nested scope instanced is not allowed
class PullDisable {
protected:
    static const uint8_t PUD_MASK = 1 << PUD;
    
public:
    explicit
    PullDisable(bool turn_on = true, bool ignore_initial_state = true) {
        if (turn_on) {
            PullDisable::turn_on(ignore_initial_state);
        }
    }
    ~PullDisable() {
        turn_off();
    }
    
    static
    void turn_on(bool ignore_initial_state = true) {
        assert(ignore_initial_state || !(MCUCR & PUD_MASK));
        MCUCR |= PUD_MASK;
    }
    
    static
    void turn_off() {
        MCUSR = MCUCR & ~PUD_MASK;
    }
};

namespace B {
    volatile uint8_t pin __attribute__((io (0x03 + __SFR_OFFSET)));
    volatile uint8_t ddr __attribute__((io (0x04 + __SFR_OFFSET)));
    volatile uint8_t port __attribute__((io (0x05 + __SFR_OFFSET)));
}






template<uint8_t bit>
class PortBit {
public:
    static_assert(0 <= bit && bit < 8, "Invalid port bit");
    
    static const uint8_t mask = (1 << bit);
    static const uint8_t inv_mask = ~mask;
};



//
//class PortC: public Port {
//
//public:
//    PortC(): Port(DDRC, PORTC, PINC) {}
//};
//
//class PortD: public Port {
//
//public:
//    PortD(): Port(DDRD, PORTD, PIND) {}
//};
//
//PortC portC;
//PortD portD;


//class BaseTask {
//private:
//    uint16_t _stack_pointer;
//
//public:
//
//
//
//    void yield() {
//        uint8_t stack_high;
//        uint8_t stack_low;
//        asm volatile(
//                "CALL AAAA"
//        :
//        :"m"(suspend)
//        :
//        "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
//                "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20",
//                "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
//        );
//    }
//};

//
//Task<128> task_test;
//
//

volatile uint8_t porta __attribute__((io (0x05 + __SFR_OFFSET)));

constexpr
volatile uint8_t* io_register(int offset)
{
    return static_cast<volatile uint8_t*>(0x0) + offset;
}

template<volatile uint8_t& v>
class P {
public:
    static
    void a() {
        v |= 0x08;
    }
};

volatile uint8_t& d = DDRB;


int main() {
    using namespace sarv;
    
    usart::Usart<usart::AsyncClock<9600, true>> uart;
    uart.sync_send(PN("Start"));
    port::Output<port::PortB, 2> output;
    port::Input<port::PortB, 0> input;
    _delay_ms(1000);
    uart.sync_send(PN("Start cycle"));
    bool state = input;
    while(true) {
//        _delay_ms(1000);
//        uart.sync_send(PN("Send high"));
//        output.set_high();
//        _delay_ms(1000);
//        uart.sync_send(PN("Send low"));
//        output.set_low();
        if (state) {
            if (!input) {
                uart.sync_send(PN("Go to lower state"));
                state = false;
            }
        } else {
            if (input) {
                uart.sync_send(PN("Go to high state"));
                state = true;
            }
        }
    }
    
//
//    u.sync_send(PS("Output set"));
    
//    while(1) {
//        _delay_ms(1000);
//
        //output.set_high();
//        _delay_ms(500);
//
        //portB.set_output_value<0>(false);
//    }
    return 0x1A;
    
//    PullDisable ddis;
//    BaseTask bt;
//
//    bt.yield();
//
//    usart::Usart<usart::AsyncClock<9600, true>> u;
//    init();
//    while(1) {
//        save("sdfghjkl");
//
//        for(volatile uint32_t i = 0; i < F_CPU / 30;) {
//            i = i + 1;
//        }
//        u.send('+');
//    }
//    init();
//    send();
//    using namespace sarv;
//    usart::Usart<usart::AsyncClock<9600>> usart1;
//    for(int i = 100; i > 0; i--) {
//        usart1.save_string(P("qwertyuiop;lkjhgfdsazxcvbnm,."));
//        usart1.save_string(S("><MNBVCXZASDFGHJKL:POIUYTREWQ"));
//        usart1.save_string(P("qwertyuiop;lkjhgfdsazxcvdsfsdsbnm,."));
//        usart1.save_string(S("><MNBVCXZASDFGHJKL:POIUYTREWsdfsfQ"));
//    }
//    return 0;
    
//    usart1.save("ASDFGHJKL:OIUYTREWSDFGHJK");
    
//    const char *p = PSTR("ABCDE1");
//    const char *s = "qwertyuiop";
//    const char *ss = "qdkljdwdjkldertdkjljdyuiop";
//
//    logger.send_string(s);
//    logger.send_string(ss);
//    logger.send_pm_string(p);
//
    //LOG_D("DDD");

    return 0;
}