#pragma once

#include "savr_io.h"
#include "registers.h"
#include "port.h"

namespace savr::timer_0 {

    class ClockSource {
        // CS02:0
        // TCCR0B
    };

    class Mode {
        // normal
        // clear on match
        // * togle mode
        //
    };
    
    namespace details {
        using namespace savr::details;
        
        constexpr
        uint8_t _source_mask(uint8_t cs02, uint8_t cs01, uint8_t cs00) {
            return (cs02 << CS02) | (cs01 << CS01) | (cs00 << CS00);
        }
    }
    
    class ControlA: public details::ControlRegister<regs::control_a> {
    public:
        /** These bits control the output compare pin (OC0A) behavior */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_a_mask = (1 << COM0A1) | (1 << COM0A0);
        /** Normal port operation, OC0A disconnected. */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_a_disabled = (0 << COM0A1) | (0 << COM0A0);
        /**
         * non-PWM Mode:
         * * Toggle pin on compare match.
         *
         * PWM modes:
         * * WGM02 = 0: Normal pin operation, OC0A disconnected.
         * * WGM02 = 1: Toggle pin on compare match.
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_a_toggle = (0 << COM0A1) | (1 << COM0A0);
        /**
         * Clear pin on compare match when up-counting.
         *
         * Fast PWM Mode: set at bottom.
         * Phase Correct PWM Mode: set when down-counting
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_a_clear_on_match = (1 << COM0A1) | (0 << COM0A0);
        /**
         * Set OC0A on compare match when up-counting.
         *
         * Fast PWM Mode: clear at bottom.
         * Phase Correct PWM Mode: clear when down-counting
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_a_set_on_match = (1 << COM0A1) | (1 << COM0A0);
    
        /** These bits control the output compare pin (OC0B) behavior */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_b_mask = (1 << COM0B1) | (1 << COM0B0);
        
        /** Normal port operation, OC0B disconnected. */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_b_disabled = (0 << COM0B1) | (0 << COM0B0);
        
        /**
         * non-PWM Mode:
         * * Toggle pin on compare match.
         *
         * PWM modes: undefined
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_b_toggle = (0 << COM0B1) | (1 << COM0B0);
        
        /**
         * Clear pin on compare match when up-counting.
         *
         * Fast PWM Mode: set at bottom.
         * Phase Correct PWM Mode: set when down-counting
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_b_clear_on_match = (1 << COM0B1) | (0 << COM0B0);
        
        /**
         * Set OC0A on compare match when up-counting.
         *
         * Fast PWM Mode: clear at bottom.
         * Phase Correct PWM Mode: clear when down-counting
         */
        [[maybe_unused]]
        static constexpr Value compare_output_mode_b_set_on_match = (1 << COM0B1) | (1 << COM0B0);
    
        /** Mask of control the counting sequence of the counter */
        [[maybe_unused]]
        static constexpr Value mode_mask = (1 << WGM01) | (1 << WGM00);
        
        /** Normal operation mode (counter) */
        [[maybe_unused]]
        static constexpr Value mode_normal = (0 << WGM01) | (0 << WGM00);
        
        /** phase correct pwm mode */
        [[maybe_unused]]
        static constexpr Value mode_phase_correction_pwm = (0 << WGM01) | (1 << WGM00);
        
        /** clear timer on compare match (CTC) mode */
        [[maybe_unused]]
        static constexpr Value mode_clear_on_match = (1 << WGM01) | (1 << WGM00);
    
        /** fast pwm mode */
        [[maybe_unused]]
        static constexpr Value mode_fast_pwm = (1 << WGM01) | (1 << WGM00);
    
        using ControlRegister::operator=;
    };
    
    class ControlB: public details::ControlRegister<regs::control_b> {
    public:
        /** Force Output Compare A in a non-PWM mode */
        [[maybe_unused]]
        static constexpr Value force_output_a = (1 << FOC0A);
        
        /** Force Output Compare B in a non-PWM mode */
        [[maybe_unused]]
        static constexpr Value force_output_b = (1 << FOC0B);
        
        /** No clock source (Timer/Counter stopped) */
        [[maybe_unused]]
        static constexpr Value source_mask = details::_source_mask(1, 1, 1);
    
        /** clkIO (no prescaling) */
        [[maybe_unused]]
        static constexpr Value source_prescaler_no = details::_source_mask(0, 0, 1);
    
        /** clkIO/8 (from prescaler) */
        [[maybe_unused]]
        static constexpr Value source_prescaler_8 = details::_source_mask(0, 1, 0);
    
        /** clkIO/64 (from prescaler) */
        [[maybe_unused]]
        static constexpr Value source_prescaler_64 = details::_source_mask(0, 1, 1);
    
        /** clkIO/256 (from prescaler) */
        [[maybe_unused]]
        static constexpr Value source_prescaler_256 = details::_source_mask(1, 0, 0);
    
        /** clkIO/1024 (from prescaler) */
        [[maybe_unused]]
        static constexpr Value source_prescaler_1024 = details::_source_mask(1, 0, 1);
    
        /** External clock source on T0 pin. Clock on falling edge. */
        [[maybe_unused]]
        static constexpr Value source_external_falling_edge = details::_source_mask(1, 1, 0);
    
        /** External clock source on T0 pin. Clock on rising edge. */
        [[maybe_unused]]
        static constexpr Value source_external_rising_edge = details::_source_mask(1, 1, 1);
    
        /** Bit the source for maximum (TOP) counter value */
        [[maybe_unused]]
        static constexpr Value mode_source_of_top_mask = (1 << WGM02);
        
        /** Top value is maximum (0xFF) */
        [[maybe_unused]]
        static constexpr Value mode_source_of_top_max = (0 << WGM02);
        
        /**
         * Top value is comparator a.
         *
         * Normal and clear timer on compare match modes are not supported.
         */
        [[maybe_unused]]
        static constexpr Value mode_source_of_top_a = (1 << WGM02);
    
        using ControlRegister::operator=;
    };
    
    /**
     * Interrupt Mask Register.
     *
     * When the flag bit is written to one, and the I-bit in the status register is set,
     * the corresponding interrupt is enabled.
     */
    class InterruptMask: public details::ControlRegister<regs::interrupt_mask> {
    public:
        /** The corresponding interrupt is executed if a compare match in Timer/Counter occurs */
        [[maybe_unused]]
        static constexpr Value compare_match_enabled_b = (1 << OCIE0B);
    
        /** The corresponding interrupt is executed if a compare match in Timer/Counter occurs */
        [[maybe_unused]]
        static constexpr Value compare_match_enabled_a = (1 << OCIE0A);
    
        /** The corresponding interrupt is executed if an overflow in Timer/Counter occurs */
        [[maybe_unused]]
        static constexpr Value overflow_enabled = (1 << TOIE0);
        
        using ControlRegister::operator=;
    };

    /**
     * Interrupt Flag Register.
     *
     * Direct record to this register is prohibited.
     * Flag is cleared by hardware when executing the corresponding interrupt handling vector.
     * Alternatively, flag is cleared by writing a logic one to the flag.
     */
    class InterruptFlag: private details::ControlRegister<regs::interrupt_flag> {
    public:
        using ControlRegister::ControlRegister;
        
        /** The compare_match_b bit is set when a compare match occurs */
        [[maybe_unused]]
        static constexpr Value compare_match_b = (1 << OCF0B);
        
        /** The compare_match_a bit is set when a compare match occurs */
        [[maybe_unused]]
        static constexpr Value compare_match_a = (1 << OCF0A);
    
        /** The bit counter_overflow is set when an overflow occurs */
        [[maybe_unused]]
        static constexpr Value counter_overflow = (1 << TOV0);
        
        /** Clear the flag by writing a logic one */
        [[maybe_unused]]
        void unset_flag(Value flag) {
            ControlRegister::set_flag(flag);
        }
    
        using ControlRegister::is_set;
        using ControlRegister::is_unset;
        using ControlRegister::operator&;
    };
    
    [[maybe_unused]] static ControlA control_a;
    [[maybe_unused]] static ControlB control_b;
    [[maybe_unused]] static InterruptMask interrupt_mask;
    [[maybe_unused]] static InterruptFlag interrupt_flag;
    [[maybe_unused]] static port::Output<port::PortD, 4> clock_output(false);
    [[maybe_unused]] static port::Input<port::PortD, 4> clock_input(false);
    [[maybe_unused]] static port::Output<port::PortD, 6> compare_output_a(false);
    [[maybe_unused]] static port::Output<port::PortD, 5> compare_output_b(false);
}