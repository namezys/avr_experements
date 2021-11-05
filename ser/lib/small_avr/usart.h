#pragma once

#include <assert.h>
#include <avr/io.h>

extern "C" {
// these functions include asm code which should not been inlined
// also, these functions can brok ABI

void _low_level_send_p_string_from_z();
void _low_level_send_string_from_z();
}

namespace usart {
    enum class SyncClockSendEdge {
        Raising, Falling
    };
    
    /** Parity mode for frame */
    enum class ParityMode {
        Disabled, Even, Odd
    };
    
    /** Internal namespace, an user should not use it */
    namespace details {
        /// size of usart buffer
        const uint8_t _usart_0_buffer_size = 32 - 1;
        
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
    }
    
    template<uint32_t _baud, bool _double_speed = false>
    class AsyncInternalClock: public details::InternalClock<_baud, _double_speed,
            _double_speed ? details::ASYNC_DIVISOR_DOUBLE_SPEED : details::ASYNC_DIVISOR,
            false, false> {
    };
    
    template<uint32_t _baud>
    class DoubleSpeedAsyncClock: public AsyncInternalClock<_baud, true> {
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
        static const uint8_t SYNC_MODE_MASK = (1 << UMSEL00);
        static const uint8_t SYNC_FALL_TRX = (1 << UCPOL0);
        static const uint8_t STOP_1B = 0x0u;
        static const uint8_t STOP_2B = (1 << USBS0);
        static const uint8_t CH_SIZE_9B = (1 << UCSZ02);
        
        void _init_ubrr() {
            // we know that ubrr must fit into 4 + 8 bits
            UBRR0H = static_cast<uint8_t>(Clock::ubrr >> 8u) & 0x0Fu;
            UBRR0L = static_cast<uint8_t>(Clock::ubrr);
        }
        
        static
        uint8_t _parity_mask() {
            if(FrameFormat::parity_mode == ParityMode::Even) {
                return (1 << UPM01) | (0 << UPM00);
            }
            if(FrameFormat::parity_mode == ParityMode::Odd) {
                return (1 << UPM01) | (1 << UPM00);
            }
            return 0u;
        }
        
        static
        uint8_t _char_size_mask_ucsr_b() {
            //we now that size can be only from 5 to 9
            switch(FrameFormat::character_size) {
                case 5:
                    return 0u;
                case 6:
                    return (1 << UCSZ00);
                case 7:
                    return (1 << UCSZ01);
                case 8:
                case 9:
                    return (1 << UCSZ00) | (1 << UCSZ01);
                default:
                    return 0u;
            }
        }
        
        void _init_ucsr() {
            const uint8_t ucsr = _parity_mask() | _char_size_mask_ucsr_b() |
                                 (Clock::sync ? SYNC_MODE_MASK : 0u) |
                                 (Clock::falling_trx ? SYNC_FALL_TRX : 0u) |
                                 (FrameFormat::stop_bits == 2 ? STOP_2B : STOP_1B);
            UCSR0A = Clock::double_speed ? (1 << U2X0) : 0u;
            UCSR0B =
                    (receiver_enabled ? (1 << RXEN0) : 0u) |
                    (transmitter_enabled ? (1 << TXEN0) : 0u) |
                    (FrameFormat::character_size == 9 ? CH_SIZE_9B : 0u);
            UCSR0C = ucsr;
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
        
        /**
         * Synchronize transmit 8-bit. Wait until data register will be writen.
         * @param data
         */
        inline
        void sync_send(uint8_t data) {
            assert(State::is_inited);
            while(!(UCSR0A & (1 << UDRE0))) {
            }
            UDR0 = data;
        }
        
        /**
         * Synchronize transmit null-terminated string from data space
         * @param str
         */
        inline
        void sync_send_string(const char *str) {
            assert(State::is_inited);
            uint8_t *tmp;
            asm volatile("CALL _low_level_send_string_from_z"
            : "=z"(tmp)
            : "z"(str), "m"(_low_level_send_string_from_z));
        }
        
        /**
         * Synchonize transmit null-terminated string from program space
         * @param str
         */
        inline
        void sync_send_pm_string(const char *pm_str) {
            uint8_t *tmp;
            asm volatile("CALL _low_level_send_p_string_from_z"
            : "=z"(tmp)
            : "z"(pm_str), "m"(_low_level_send_p_string_from_z));
        }
    };
}
