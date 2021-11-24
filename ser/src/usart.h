#pragma once

#include <assert.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "str.h"
#include "savr_io.h"

extern "C" {
// these functions include asm code which should not been inlined
// also, these functions can brok ABI
extern uint8_t _usart_0_buffer[];
extern uint8_t *_usart_0_current_buffer_position;
}

namespace savr::usart {
    
    class ControlA: public savr::details::ControlRegister<regs::control_a> {
    public:
        /// Flag: data register is empty
        static constexpr Value data_register_empty = (1 << UDRE0);
        /// Double speed
        static constexpr Value double_speed = (1 << U2X0);
        
        using ControlRegister::operator=;
    };
    
    class ControlB: public savr::details::ControlRegister<regs::control_b> {
    public:
        /// Interrupt mask: tx data register is empty
        static constexpr Value data_register_empty_interrupt = (1 << UDRIE0);
        static constexpr Value receiver_enabled = (1 << RXEN0);
        static constexpr Value transmitter_enabled = (1 << TXEN0);
        static constexpr Value char_size_9b = (1 << UCSZ02);
        
        using ControlRegister::operator=;
    };
    
    class ControlC: public savr::details::ControlRegister<regs::control_c> {
    public:
        static constexpr Value transmission_on_falling_edge = (1 << UCPOL0);
        static constexpr Value parity_mode_nothing = 0;
        static constexpr Value parity_mode_even = (1 << UPM01) | (0 << UPM00);
        static constexpr Value parity_mode_odd = (1 << UPM01) | (1 << UPM00);
        static constexpr Value sync_mode = (1 << UMSEL00);
        static constexpr Value stop_bit_number_1 = 0;
        static constexpr Value stop_bit_number_2 = (1 << USBS0);
        
        static constexpr Value char_size_5b = 0;
        static constexpr Value char_size_6b = (1 << UCSZ00);
        static constexpr Value char_size_7b = (1 << UCSZ01);
        static constexpr Value char_size_8b = (1 << UCSZ00) | (1 << UCSZ01);
        static constexpr Value char_size_9b = (1 << UCSZ00) | (1 << UCSZ01);
        
        template<uint8_t bits>
        static constexpr Value char_size_mask() {
            static_assert(5 <= bits && bits <= 9);
            static_assert(char_size_9b._value == char_size_8b._value);
            return bits == 5 ? char_size_5b : (bits == 6 ? char_size_6b : (bits == 7 ? char_size_7b : char_size_8b));
        }
        
        using ControlRegister::operator=;
    };
    
    extern ControlA ctrl_a;
    extern ControlB ctrl_b;
    extern ControlC ctrl_c;
    
    enum class SyncClockSendEdge {
        Raising, Falling
    };
    
    /** Parity mode for frame */
    enum class ParityMode {
        Disabled, Even, Odd
    };
    
    /** Internal namespace, an user should not use it */
    namespace details {
        
        /// size of usart buffer include last zero
        const uint8_t buffer_size = 4;
        /// buffer for usart transmission
        extern uint8_t buffer[];
        /// current buffer position which should be send to usart
        extern uint8_t *current_buffer_position;
        
        // constrains
        static_assert(buffer_size <= 128, "maximum 255 buffer size is supported because of optimization");
        
        
        /** Base class for clock setting s*/
        template<uint32_t _baud, bool _double_speed, uint8_t _divisor, bool _sync, bool _falling_trx>
        class InternalClock {
        public:
            // assume that it can be 250kbps
            static const uint32_t baud = _baud;
            // using uint16_t can cause false negative static assert because integer conversion
            static const uint32_t ubrr = F_CPU / _divisor / baud - 1;
            // real baud after conversion
            static const uint32_t real_baud = F_CPU / _divisor / (ubrr + 1);
            static const bool double_speed = _double_speed;
            static const bool sync = _sync;
            static const bool falling_trx = false;
            
            static_assert(0 < ubrr && ubrr < 4096, "invalid baud setting for async mode");
            static_assert((real_baud > baud ? real_baud - baud : baud - real_baud) < 3 * baud / 100,
                          "baud is out of possible 3% tolerance");
        };
        
        const uint8_t ASYNC_DIVISOR = 16;
        const uint8_t ASYNC_DIVISOR_DOUBLE_SPEED = 8;
        const uint8_t SYNC_DIVISOR = 2;
    
        // if compiler decided to not inline this function, it will use too many registers without saving significant
        // space
        inline void empty_data_register_spin_lock()  __attribute__((always_inline));
        
        inline void empty_data_register_spin_lock()  {
            while(ctrl_a.is_unset(ControlA::data_register_empty)) {
            }
        }
    }
    
    template<uint32_t _baud, bool _double_speed = false>
    class AsyncClock: public details::InternalClock<_baud, _double_speed,
            _double_speed ? details::ASYNC_DIVISOR_DOUBLE_SPEED : details::ASYNC_DIVISOR,
            false, false> {
    };
    
    template<uint32_t _baud, SyncClockSendEdge _edge = SyncClockSendEdge::Raising>
    class SyncMasterClock: public details::InternalClock<_baud, false, details::SYNC_DIVISOR,
            true, _edge == SyncClockSendEdge::Falling> {
    };
    
    template<uint8_t _character_size = 8, uint8_t _stop_bits = 1, ParityMode _parity_mode = ParityMode::Disabled>
    class Frame {
    public:
        static const uint8_t character_size = _character_size;
        static const uint8_t stop_bits = _stop_bits;
        static const ParityMode parity_mode = _parity_mode;
        
        static_assert(5 <= character_size && character_size <= 9, "allowed only character from 5 up to 9 bits");
        static_assert(character_size != 9, "9-bit mode isn't implemented");
        static_assert(stop_bits == 1 || stop_bits == 2, "allowed only 1- or 2-stop bits");
    };
    
    /**
     * State which doesn't save actual state.
     *
     * Can be used if you don't care about current initiation state.
     * An user should care about setting up USART because there will not any error message
     */
    class DummyState {
    public:
        static const bool is_inited = true;
        
        inline
        void set_inited(bool) {}
    };
    
    /**
     * State which store current initiation state.
     */
    class SavedState {
    public:
        bool is_inited = false;
        
        inline
        void set_inited(bool state) {
            is_inited = state;
        }
    };
    
    /**
     * @tparam Clock
     * @tparam FrameFormat
     * @tparam receiver_enabled
     * @tparam transmitter_enabled
     */
    template<class Clock, class FrameFormat = Frame<>, bool receiver_enabled = true, bool transmitter_enabled = true,
            class State = DummyState>
    class Usart: public State, private Clock, private FrameFormat {
    private:
        void _init_ubrr() {
            // we know that ubrr must fit into 4 + 8 bits
            regs::baud_rate_high = static_cast<uint8_t>(Clock::ubrr >> 8u) & 0x0Fu;
            regs::baud_rate_low = static_cast<uint8_t>(Clock::ubrr);
        }
        
        void _init_ucsr() {
            ctrl_a =
                    ControlA::double_speed.only_if(Clock::double_speed);
            ctrl_b =
                    ControlB::receiver_enabled.only_if(receiver_enabled) |
                    ControlB::transmitter_enabled.only_if(transmitter_enabled) |
                    ControlB::char_size_9b.only_if(FrameFormat::character_size == 9);
            ctrl_c =
                    ControlC::char_size_mask<FrameFormat::character_size>() |
                    ControlC::parity_mode_even.only_if(FrameFormat::parity_mode == ParityMode::Even) |
                    ControlC::parity_mode_odd.only_if(FrameFormat::parity_mode == ParityMode::Odd) |
                    ControlC::sync_mode.only_if(Clock::sync) |
                    ControlC::stop_bit_number_2.only_if(FrameFormat::stop_bits == 2) |
                    ControlC::transmission_on_falling_edge.only_if(Clock::falling_trx);
        }
    
    public:
        
        explicit
        Usart(bool init = true) {
            if(init) {
                Usart::init();
            }
        }
        
        /** Init device with provided parameters */
        void init() {
            _init_ubrr();
            _init_ucsr();
            State::set_inited(true);
        }

        void sync_send(PmStr str) {
            sync_send_pm_string(str.ptr());
        }

        void sync_send(ConstStr str) {
            sync_send_string(str.ptr());
        }

        /**
         * Synchronize transmit 8-bit. Wait until data send to register.
         *
         * @param data
         */
        inline
        void sync_send(uint8_t data) {
            assert(State::is_inited);
            details::empty_data_register_spin_lock();
            regs::data = data;
        }
        
        /**
         * Synchronize transmit null-terminated string from data space
         *
         * @param str
         */
        inline
        void sync_send_string(const char *str) {
            assert(State::is_inited);
            while(*str != 0) {
                details::empty_data_register_spin_lock();
                regs::data = *str;
                ++str;
            }
        }
        
        /**
         * Synchonize transmit null-terminated string from program space
         *
         * @param str
         */
        inline
        void sync_send_pm_string(const char *pm_str) {
            assert(State::is_inited);
            uint8_t value;
            while(true) {
                asm("LPM %[V], Z+":[V]"=a"(value), "+z"(pm_str));
                if(value == 0) {
                    return;
                }
                details::empty_data_register_spin_lock();
                regs::data = value;
            }
        }
        
        /**
         * Async transmit null-terminated string from data space.
         *
         * Wait until buffer will be ready
         * @param str
         */
        void save_string(const char *str) {
            while(*str != 0) {
                auto s_reg = regs::status;
                cli();
                if(*_usart_0_current_buffer_position != 0) {
                    // we have data in buffer and this data was not send to usart
                    // restore state and wait
                    regs::status = s_reg;
                    continue;
                }
                // now we have space and no interruption is possible. copy data
                uint8_t *dst = _usart_0_buffer;
                for(uint8_t buf_size = usart::details::buffer_size;
                    *str != 0 && buf_size >= 0; ++str, ++dst, --buf_size) {
                    *dst = *str;
                }
                *dst = 0;
                _usart_0_current_buffer_position = _usart_0_buffer;
                ctrl_b.set_flag(ControlB::data_register_empty_interrupt);
                // finish and restore state
                regs::status = s_reg;
            }
        }
        
        /**
         * Async transmit null-terminated string from data space.
         *
         * Wait until buffer will be ready
         * @param str
         */
        template<class Str>
        void save_string(Str str) {
            while(*str != 0) {
                auto s_reg = regs::status;
                cli();
                if(*details::current_buffer_position != 0) {
                    // we have data in buffer and this data was not send to usart
                    // restore state and wait
                    regs::status = s_reg;
                    continue;
                }
                // now we have space and no interruption is possible. copy data
                uint8_t *dst = details::buffer;
                uint8_t buf_size = details::buffer_size - 1;
                while(*str != 0 && buf_size != 0) {
                    *dst = *str;
                    str.incr();
                    ++dst;
                    --buf_size;
                }
                *dst = 0;
                details::current_buffer_position = details::buffer;
                ctrl_b.set_flag(ControlB::data_register_empty_interrupt);
                // finish and restore state
                regs::status = s_reg;
            }
        }
    };
    
}