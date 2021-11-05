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

extern "C" {
const uint8_t _usart_0_buffer_size = 256 - 1;
uint8_t _usart_0_buffer[_usart_0_buffer_size + 1] __attribute__(( aligned(256)));
const uint8_t *buffer_end = _usart_0_buffer + _usart_0_buffer_size;
uint8_t *_usart_0_current_buffer_position;

const uint8_t USART_TX_EMPTY_INT_MASK = (1 << UDRIE0);
const uint8_t USART_TX_EMPTY_INT_INV_MASK = static_cast<uint8_t>(~USART_TX_EMPTY_INT_MASK);

ISR(USART_UDRE_vect, ISR_NAKED) {
    asm volatile(
            "\n\t"
            // save state
            "push r16\n\t"
            "in r16, __SREG__\n\t"
            "push r16\n\t"
            "push r30\n\t"
            "push r31\n\t"
            // load buffer pointer and value
            // high address can be loaded as high address of buffer
            "lds r30, current_buffer\n\t"
            "ldi r31, hi8(buffer)\n\t"
            "ld r16, Z+\n\t"
            // check value and jump if necessary
            "cpi r16, 0\n\t"
            "breq STOP_%=\n\t"
            // send to tx register and save new current buffer
            // because of alignment, hi8 of this buffer will not changed
            "sts %[RXD], r16\n\t"
            "sts current_buffer, r30\n\t"
            // restore state
            "pop r31\n\t"
            "pop r30\n\t"
            "pop r16\n\t"
            "out __SREG__, r16\n\t"
            "pop r16\n\t"
            "reti\n\t"
            // stop send using interrupt
            "STOP_%=:\n\t"
            "lds r16, %[USART_B]\n\t"
            "andi r16, %[USART_B_INT_MASK]\n\t"
            "sts %[USART_B], r16\n\t"
            // restore state
            "pop r31\n\t"
            "pop r30\n\t"
            "pop r16\n\t"
            "out __SREG__, r16\n\t"
            "pop r16\n\t"
            "reti\n\t"
            :
            :[USART_B]"M"(&UCSR0B),
             [USART_B_INT_MASK]"M"(0xFF ^ USART_TX_EMPTY_INT_MASK),
             [RXD]"M"(&UDR0),
             "m"(_usart_0_current_buffer_position),
             "m"(_usart_0_buffer)
    );
}

}

void init()
{
    _usart_0_buffer[0] = 0;
    _usart_0_buffer[_usart_0_buffer_size] = 0;
}

void save(const char* str)
{

    //  a6:	1f 92       	push	r1
    //  a8:	0f 92       	push	r0
    //  aa:	0f b6       	in	r0, 0x3f	; 63
    //  ac:	0f 92       	push	r0
    //  ae:	11 24       	eor	r1, r1
    //  b0:	8f 93       	push	r24
    //  b2:	9f 93       	push	r25
    //  b4:	ef 93       	push	r30
    //  b6:	ff 93       	push	r31
    //  b8:	e0 91 20 01 	lds	r30, 0x0120	; 0x800120 <current_buffer>
    //  bc:	f0 91 21 01 	lds	r31, 0x0121	; 0x800121 <current_buffer+0x1>
    //  c0:	80 81       	ld	r24, Z
    //  c2:	81 11       	cpse	r24, r1
    //  c4:	0e c0       	rjmp	.+28     	; 0xe2 <__vector_19+0x3c>
    //  c6:	80 91 c1 00 	lds	r24, 0x00C1	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
    //  ca:	8f 7d       	andi	r24, 0xDF	; 223
    //  cc:	80 93 c1 00 	sts	0x00C1, r24	; 0x8000c1 <__TEXT_REGION_LENGTH__+0x7e00c1>
    //  d0:	ff 91       	pop	r31
    //  d2:	ef 91       	pop	r30
    //  d4:	9f 91       	pop	r25
    //  d6:	8f 91       	pop	r24
    //  d8:	0f 90       	pop	r0
    //  da:	0f be       	out	0x3f, r0	; 63
    //  dc:	0f 90       	pop	r0
    //  de:	1f 90       	pop	r1
    //  e0:	18 95       	reti
    //  e2:	80 93 c6 00 	sts	0x00C6, r24	; 0x8000c6 <__TEXT_REGION_LENGTH__+0x7e00c6>
    //  e6:	80 91 20 01 	lds	r24, 0x0120	; 0x800120 <current_buffer>
    //  ea:	90 91 21 01 	lds	r25, 0x0121	; 0x800121 <current_buffer+0x1>
    //  ee:	01 96       	adiw	r24, 0x01	; 1
    //  f0:	90 93 21 01 	sts	0x0121, r25	; 0x800121 <current_buffer+0x1>
    //  f4:	80 93 20 01 	sts	0x0120, r24	; 0x800120 <current_buffer>
    //  f8:	eb cf       	rjmp	.-42     	; 0xd0 <__vector_19+0x2a>
    cli();
    uint8_t* b = _usart_0_buffer;
    for(;*str != 0; ++str, ++b) {
        *b = *str;
    }
    *b = 0;
    _usart_0_current_buffer_position = _usart_0_buffer;
    UCSR0B = UCSR0B | (1 << UDRIE0);
    sei();
}

int main() {
    usart::Usart<usart::AsyncInternalClock<9600, true>> u;
    init();
    while(1) {
        save("sdfghjkl");
        
        for(volatile uint32_t i = 0; i < F_CPU / 30;) {
            i = i + 1;
        }
        u.send('+');
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

    return 0;
}