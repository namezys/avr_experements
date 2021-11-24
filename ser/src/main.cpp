#include <avr/pgmspace.h>
#include <util/delay.h>

#include "usart.h"
#include "reset_status.h"
#include "port.h"
#include "loggger.h"
#include "format.h"

//
//namespace savr {
//    namespace timer_counter_0_A {
//        enum class WaveformGenerationMode {
//            // increment, 0x00 - 0xFF[signal and clear counter]
//            normal,
//            // increment, 0x00 - [signal and clear counter]
//            compare_match,
//            // increment, 0x00 - [signal] - 0xFF [clear counter]
//            fast_pwm,
//            // increment and decrement 0x00 - [signal] - 0xFF - [signal] - 0x00
//            phase_correction_pwm,
//
//        };
//
//        namespace control {
//            volatile uint8_t a IO(TCCR0A, 0x24);
//            volatile uint8_t b IO(TCCR0B, 0x25);
//
//            const uint8_t clock_mask = (1 << CS02) | (1 << CS01) | (1 << CS00);
//            const uint8_t io_clock = (1 << CS00);
//            const uint8_t io_clock_8 = (1 << CS01);
//            const uint8_t io_clock_64 = (1 << CS01) | (1 << CS00);
//            const uint8_t io_clock_256 = (1 << CS02);
//            const uint8_t io_clock_1024 = (1 << CS02) | (1 << CS00);
//            const uint8_t external_clock_falling_edge = (1 << CS02) | (1 << CS01);
//            const uint8_t external_clock_rising_edge = (1 << CS02) | (1 << CS01) | (1 << CS00);
//        }
//
//        volatile uint8_t counter IO(TCNT0, 0x26);
//        volatile uint8_t compare_a IO(OCR0A, 0x27);
//        volatile uint8_t compare_b IO(OCR0B, 0x28);
//
//
//        namespace interrupt_mask {
//            const uint8_t match_b = 1 << OCIE0B;
//            const uint8_t match_a = 1 << OCIE0A;
//            const uint8_t overflow = 1 << TOIE0;
//
//            volatile uint8_t value MEM(TIMSK0, 0x6E);
//        }
//
//        namespace interrupt_flags {
//            const uint8_t match_b = 1 << OCF0B;
//            const uint8_t match_a = 1 << OCF0A;
//            const uint8_t overflow = 1 << TOV0;
//
//            volatile uint8_t value IO(TIFR0, 0x15);
//        }
//
//
//
//        volatile uint8_t v __attribute__((io(0x24 + __SFR_OFFSET)));
//
//        template<class Mode>
//        class TC {
//
//        };
//    }
//}
//
//void test()
//{
//
//}



// usart test
//int main() {
//    using namespace savr::usart;
//    Usart<savr::usart::AsyncClock<9600, true>> uart(false);
//    uart.sync_send('A');
//    uart.sync_send(S("AB-AB"));
//    uart.sync_send(P("BA-BA"));

//    uart.sync_send('B');
//    uart.sync_send(S("BB-BB"));
//    uart.sync_send(P("BC-BC"));
//
//    uart.sync_send('C');
//}

// usart test + fmt
//volatile int8_t i_8 MEM(0, 0x800);
//volatile uint8_t u_8 MEM(0, 0x800);
//volatile int16_t i_16 MEM(0, 0x800);
//volatile uint16_t u_16 MEM(0, 0x800);
//
//int main() {
//    using namespace savr::usart;
//    using namespace savr::format;
//    Usart<savr::usart::AsyncClock<9600, true>> uart(false);
//    uart.sync_send(Fmt<int8_t>::format(0xA0));
//    uart.sync_send(Fmt<uint8_t>::format(0xA0));
//    uart.sync_send(Fmt<int16_t>::format(0xA0));
//    uart.sync_send(Fmt<uint16_t>::format(0xA0));
//
//    uart.sync_send(Fmt<int8_t>::format(i_8));
//    uart.sync_send(Fmt<uint8_t>::format(u_8));
//    uart.sync_send(Fmt<int16_t>::format(i_16));
//    uart.sync_send(Fmt<uint16_t>::format(u_16));
//
//    uart.sync_send(Fmt<bool>::format(u_8 == 0xF0));
//}


// logger test
//savr::logging::SyncLogger<
//        savr::logging::Level::Debug,
//        savr::usart::Usart<savr::usart::AsyncClock<9600, true>>
//> logger;
//volatile uint8_t u_8 MEM(0, 0x800);
//volatile uint8_t u_88 MEM(0, 0x400);
//int main() {
//
//    ERROR("Error msg");
//    INFO("Info message");
//    DEBUG("Details");
//
//    uint8_t t = u_8;
//    ERROR("Details with", t);
//    DEBUG("Details with", t);
//    uint8_t tt = u_88;
//    INFO("Info to", tt);
//
//    {
//        ERROR("A");
//        INFO("B");
//        DEBUG("C");
//
//        uint8_t tl = u_8;
//        ERROR("D", tl);
//        DEBUG("E", tl);
//        uint8_t ttl = u_88;
//        INFO("F", ttl);
//    }
//}

// reset status
//int main() {
//    using namespace savr;
//    cli();
//    watch_dog.reset();
//    watch_dog |= WatchDog::change_enabled | WatchDog::system_reset_enabled;
//    watch_dog = WatchDog::prescalar_64k;
//    sei();
//
//    usart::Usart<savr::usart::AsyncClock<9600, true>> uart;
//    uart.sync_send(P("Start"));
//    while(true) {}
//    return 0;
//}