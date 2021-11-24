#pragma once
#include <avr/wdt.h>
#include "savr_io.h"
#include "registers.h"

namespace savr {
    
    namespace details {
        [[nodiscard]]
        static constexpr uint8_t watch_dog_prescalar_value(uint8_t wdp3, uint8_t  wdp2, uint8_t  wdp1, uint8_t  wdp0) {
            return (wdp3 << WDP3) | (wdp2 << WDP2) | (wdp1 << WDP1) | (wdp0 << WDP0);
        }
    }
    
    /**
     * The MCU status register provides information on which reset source caused an MCU reset.
     *
     * Any bit can be reset by  writing a logic zero to the flag.
     */
    class McuStatus: public details::ControlRegister<regs::mcu_status> {
    public:
        /** This bit is set if a watchdog system reset occurs. */
        [[maybe_unused]]
        static constexpr Value watch_dog_system_reset = (1 << WDRF);
        
        /** This bit is set if a brown-out reset occurs. */
        [[maybe_unused]]
        static constexpr Value brown_out_reset = (1 << BORF);
        
        /** This bit is set if an external reset occurs. */
        [[maybe_unused]]
        static constexpr Value external_reset = (1 << EXTRF);
        
        /** This bit is set if a power-on reset occurs. */
        [[maybe_unused]]
        static constexpr Value power_on_reset = (1 << PORF);
        
        /** Reset mcu status. To determinate reset reason it should be called as early as possible */
        [[maybe_unused]]
        void clear() {
            (*this) = 0x0;
        }
    
        using ControlRegister::operator=;
    };
    
    /**
     * Enhanced watchdog timer (WDT).
     *
     * The WDT is a timer counting cycles of a separate on-chip 128kHz oscillator.
     *
     * If the system doesn't restart the counter, an interrupt or system reset will be issued.
     *
     * The watchdog always on (WDTON) fuse, if programmed, will force the watchdog timer to system reset mode.
     */
    class WatchDog: public details::ControlRegister<regs::watch_dog> {
    private:
    
    public:
        /**
         * This bit is set when a time-out occurs in the watchdog timer and the watchdog timer is configured for interrupt.
         *
         * Cleared by:
         * * hardware when executing the corresponding interrupt handling vector.
         * * cleared by writing a logic one to the flag.
         */
        [[maybe_unused]]
        static constexpr Value interrupt_flag = (1 << WDIF);
        
        /**
         * When this bit is written to one and the I-bit in the status register is set, the watchdog interrupt is enabled.
         *
         * Executing the corresponding interrupt vector will clear interrupt_enabled and interrupt_flag
         * automatically by hardware and the watchdog goes to system reset mode.
         */
        [[maybe_unused]]
        static constexpr Value interrupt_enabled = (1 << WDIE);
        
        /**
         * This bit is used in timed sequences for changing system_reset_enabled and prescaler.
         *
         * Once written to one, hardware will clear change_enabled after four clock cycles.
         */
        [[maybe_unused]]
        static constexpr Value change_enabled = (1 << WDCE);
        
        /**
         * Watchdog System Reset Enable.
         *
         * The flag system_reset_enabled WDE is always set when McuStatus::watch_dog_system_reset is set
         */
        [[maybe_unused]]
         static constexpr Value system_reset_enabled = (1 << WDE);
        
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 2K (2048) cycles; Typical Time-out at VCC = 5.0V is 16ms
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_2k = details::watch_dog_prescalar_value(0, 0, 0, 0);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 4K (2048) cycles; Typical Time-out at VCC = 5.0V is 32ms
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_4k = details::watch_dog_prescalar_value(0, 0, 0, 1);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 8K (2048) cycles; Typical Time-out at VCC = 5.0V is 64ms
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_8k = details::watch_dog_prescalar_value(0, 0, 1, 0);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 16K (2048) cycles; Typical Time-out at VCC = 5.0V is 0.125s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_16k = details::watch_dog_prescalar_value(0, 0, 1, 1);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 32K (2048) cycles; Typical Time-out at VCC = 5.0V is 0.25s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_32k = details::watch_dog_prescalar_value(0, 1, 0, 0);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 64K (2048) cycles; Typical Time-out at VCC = 5.0V is 0.5s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_64k = details::watch_dog_prescalar_value(0, 1, 0, 1);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 128K (2048) cycles; Typical Time-out at VCC = 5.0V is 1s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_128k = details::watch_dog_prescalar_value(0, 1, 1, 0);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 256K (2048) cycles; Typical Time-out at VCC = 5.0V is 2s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_256k = details::watch_dog_prescalar_value(0, 1, 1, 1);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 512K (2048) cycles; Typical Time-out at VCC = 5.0V is 4s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_512k = details::watch_dog_prescalar_value(1, 0, 0, 0);
    
        /**
         * The watchdog timer prescalar when the watchdog timer is running.
         *
         * 1024K (2048) cycles; Typical Time-out at VCC = 5.0V is 8s
         * */
        [[maybe_unused]]
        static constexpr Value prescalar_1024k = details::watch_dog_prescalar_value(1, 0, 0, 1);
    
        /** Reset Watchdog Timer */
        [[maybe_unused]]
        void reset() {
            (void)this; // to avoid hint what this method can be static
            wdt_reset();
        }
    
    
        using ControlRegister::operator=;
        
    };
    
    [[maybe_unused]] static WatchDog watch_dog;
    [[maybe_unused]] static McuStatus mcu_status;
}
