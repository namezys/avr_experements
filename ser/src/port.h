#pragma once

#include <avr/io.h>
#include "savr_io.h"

/**
 * Helper classes to work with GPIO ports.
 */
namespace savr::port {

    /**
     * Assign bit on port
     *
     * @tparam bit bit number
     */
    template<uint8_t bit>
    class PortBit {
    public:
        static_assert(0 <= bit && bit < 8, "Invalid port bit");

        static constexpr uint8_t mask = (1 << bit);
        static constexpr uint8_t inv_mask = ~mask;
    };

    /**
     * Aggregate port register together to store access together.
     *
     * This class can't be used directly.
     *
     * @tparam pin reference to input register (PINx)
     * @tparam ddr reference to direction register (DDRx)
     * @tparam port reference to output/pull-up register (PORTx)
     */
    template<volatile uint8_t &pin, volatile uint8_t &ddr, volatile uint8_t &port>
    class Port {

    protected:
        Port() = default;

    public:

        /**
         * Check direction of the pin
         *
         * @tparam bit pin number
         * @return true if pin is output
         */
        template<uint8_t bit>
        [[nodiscard]]
        bool is_output() const {
            return ddr & PortBit<bit>::mask;
        }
        
        /**
         * Set output on pin
         *
         * @tparam bit pin number
         */
        template<uint8_t bit>
        [[maybe_unused]]
        void set_output() {
            ddr |= PortBit<bit>::mask;
        }

        /**
         * Check direction of the pin
         *
         * @tparam bit pin number
         * @return true if pin is input
         */
        template<uint8_t bit>
        [[maybe_unused]] [[nodiscard]]
        bool is_input() const {
            return !is_output<bit>();
        }

        /**
         * Set output on pin
         *
         * @tparam bit pin  number
         * @param pull_up set or reset up pull-up mode for the pin
         */
        template<uint8_t bit>
        [[maybe_unused]]
        void set_input(bool pull_up) {
            using Bit = PortBit<bit>;
            // TODO: check order of port changed, it can be important
            if(pull_up) {
                port |= Bit::mask;
            }
            else {
                port &= Bit::mask;
            }
            ddr &= Bit::inv_mask;
        }

        /**
         * Get value on pin (even pin is output)
         *
         * @tparam bit pin number
         * @return true if high and false if low
         */
        template<uint8_t bit>
        [[maybe_unused]] [[nodiscard]]
        bool get_input_value() const {
            return pin & PortBit<bit>::mask;
        }

        /**
         * Set output value. In case of input mode will affect pull-up mode
         *
         * @tparam bit pin number
         * @param is_high true to set high and false to set low
         */
        template<uint8_t bit>
        [[maybe_unused]]
        void set_output_value(bool is_high) {
            using Bit = PortBit<bit>;
            if(is_high) {
                port |= Bit::mask;
            }
            else {
                port &= Bit::inv_mask;
            }
        }
    };

    
    class PortB: public Port<B::pin, B::ddr, B::port> {
    public:
        PortB() = default;
    };
    
    class PortC: public Port<C::pin, C::ddr, C::port> {
    public:
        PortC() = default;
    };
    
    class PortD: public Port<D::pin, D::ddr, D::port> {
    public:
        PortD() = default;
    };

    /**
     * Assign bit on port as output and its value
     *
     * @tparam Port Port class
     * @tparam bit pin number
     */
    template<class Port, uint8_t bit>
    class [[maybe_unused]] Output: public Port, protected PortBit<bit> { // NOLINT
    public:
        explicit
        Output(bool a_init = true) {
            if(a_init) {
                init();
            }
        }

        /**
         * Init or re-init initial state of port and direction
         *
         * Current output value will not be affected
         */
        void init() {
            Port::template set_output<bit>();
        }

        /** Set high or low level on pin */
        [[maybe_unused]]
        void set(bool is_high) {
            Port::template set_output_value<bit>(is_high);
        }

        /** Set high on pin */
        [[maybe_unused]]
        void set_high() {
            set(true);
        }

        /** Set low on pin */
        [[maybe_unused]]
        void set_low() {
            set(false);
        }

        /** Set high or low on pin using assign operator */
        [[maybe_unused]]
        void operator=(bool is_high) {
            set(is_high);
        }
    };

    /**
     * Assign pin os input and get it value
     * @tparam Port Port class
     * @tparam bit pin number
     * @tparam pull_up set pull up on init
     */
    template<class Port, uint8_t bit, bool pull_up = true>
    class [[maybe_unused]] Input: public Port, protected PortBit<bit> {
    public:
        explicit Input(bool a_init = true) {
            if(a_init) {
                init();
            }
        }
    
        /**
         * Init or re-init initial state of port and direction.
         * Pull up will be set according type definition
         */
        void init() {
            Port::template set_input<bit>(pull_up);
        }
    
        /** Current value on pin, true if high and false if low */
        [[maybe_unused]] [[nodiscard]]
        bool value() const {
            return Port::template get_input_value<bit>();
        }
    
        [[maybe_unused]]
        operator bool() const { // NOLINT
            return value();
        }
    };
    
    [[maybe_unused]] static PortB port_b;
    [[maybe_unused]] static PortC port_c;
    [[maybe_unused]] static PortD port_d;
}