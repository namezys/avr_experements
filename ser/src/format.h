#pragma once
#include "str.h"

/**
 * Template classes to format different types to string.
 */
namespace savr::format {
    namespace details {
        extern char buffer[];
    }
    
    /** Format using common representation */
    template<typename T> struct [[maybe_unused]] StdFmt {};
    
    template<>
    struct [[maybe_unused]] StdFmt<bool> {
        [[maybe_unused]] [[nodiscard]]
        static PmStr format(int16_t value) {
            return value ? P("true") : P("false");
        }
    };
    
    /** Format using hex representation for integers with sign */
    template<typename T> struct [[maybe_unused]] HexFmt {};
    
    template<>
    struct [[maybe_unused]] HexFmt<uint8_t> {
        [[maybe_unused]] [[nodiscard]]
        static ConstStr format(uint8_t value) {
            using namespace savr::format::details;
            buffer[0] = '0';
            buffer[1] = 'x';
            buffer[2] = static_cast<char>('0' + value / 16);
            buffer[3] = static_cast<char>('0' + value % 16);
            buffer[4] = 0;
            return buffer;
        }
    };
    
    template<>
    struct [[maybe_unused]] HexFmt<int8_t> {
        [[maybe_unused]] [[nodiscard]]
        static ConstStr format(int8_t value) {
            using namespace savr::format::details;
            if (value < 0) {
                buffer[0] = '-';
                value = static_cast<int8_t>(-value);
            } else {
                buffer[0] = '+';
            }
            buffer[1] = '0';
            buffer[2] = 'x';
            buffer[3] = static_cast<char>('0' + value / 16);
            buffer[4] = static_cast<char>('0' + value % 16);
            buffer[5] = 0;
            return buffer;
        }
    };
    
    template<>
    struct [[maybe_unused]] HexFmt<uint16_t> {
        [[maybe_unused]] [[nodiscard]]
        static ConstStr format(uint16_t value) {
            using namespace savr::format::details;
            const uint8_t high = value >> 8;
            const uint8_t low = value;
            buffer[0] = '0';
            buffer[1] = 'x';
            buffer[2] = static_cast<char>('0' + high / 16);
            buffer[3] = static_cast<char>('0' + high % 16);
            buffer[4] = static_cast<char>('0' + low / 16);
            buffer[5] = static_cast<char>('0' + low % 16);
            buffer[6] = 0;
            return buffer;
        }
    };
    
    template<>
    struct [[maybe_unused]] HexFmt<int16_t> {
        [[maybe_unused]] [[nodiscard]]
        static ConstStr format(int16_t value) {
            using namespace savr::format::details;
            if (value < 0) {
                buffer[0] = '-';
                value = static_cast<int16_t>(-value);
            } else {
                buffer[0] = '+';
            }
            const uint8_t high = value >> 8;
            const uint8_t low = value;
            buffer[1] = '0';
            buffer[2] = 'x';
            buffer[3] = static_cast<char>('0' + high / 16);
            buffer[4] = static_cast<char>('0' + high % 16);
            buffer[5] = static_cast<char>('0' + low / 16);
            buffer[6] = static_cast<char>('0' + low % 16);
            buffer[7] = 0;
            return buffer;
        }
    };
    
    /**
     * Format value using static method format.
     * Type of return value of format can be ConstSyr or PrStr.
     *
     * @tparam T type of value
     */
    template<typename T> struct [[maybe_unused]] Fmt {
        // static ConstStr format(const T &t) {return nullptr;}
    };
    template<> struct [[maybe_unused]] Fmt<bool>: public StdFmt<bool> {};
    template<> struct [[maybe_unused]] Fmt<uint8_t>: public HexFmt<uint8_t> {};
    template<> struct [[maybe_unused]] Fmt<int8_t>: public HexFmt<int8_t> {};
    template<> struct [[maybe_unused]] Fmt<uint16_t>: public HexFmt<uint16_t> {};
    template<> struct [[maybe_unused]] Fmt<int16_t>: public HexFmt<int16_t> {};
}