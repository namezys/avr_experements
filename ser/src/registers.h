#pragma once

namespace savr::details {
    
    /**
     * Control or status register which include possible values or mask
     *
     * Subclass should define possible masks/values/bit-masks using class Value as constexpr
     *
     * @tparam reg reference to 8-bit register
     */
    template<volatile uint8_t &reg>
    class ControlRegister {
    public:
        
        /**
         * Value which can be assigned and used for this control register
         *
         * This class variables should be passed by instance instead of const reference because
         * it will be better for optimization
         */
        class Value {
        public:
            /// Actual value
            const uint8_t _value;
            
            [[maybe_unused]]
            constexpr Value(uint8_t value) : _value(value) {}
    
            [[nodiscard]]
            constexpr Value operator|(const Value &other) const {
                return _value | other._value;
            }
    
            [[nodiscard]]
            constexpr Value operator&(const Value &other) const {
                return _value & other._value;
            }
    
            [[nodiscard]]
            Value operator~() const {
                return ~_value;
            }
            
            /** Check if value is flag which contains only one bit */
            [[maybe_unused]] [[nodiscard]]
            constexpr bool is_flag() const {
                return _value == 0x01 || _value == 0x02 || _value == 0x04 || _value == 0x08
                       || _value == 0x10 || _value == 0x20 || _value == 0x40 || _value == 0x80;
            }
            
            /**
             * Use value only condition is true and 0x00 otherwise
             *
             * @param condition boolean condition
             * @return value of 0x00
             */
            [[maybe_unused]] [[nodiscard]]
            Value only_if(bool condition) const {
                return condition ? *this : 0;
            }
        };
        
        /**
         * Set bit according value mask
         * @param value mask
         */
        [[maybe_unused]]
        void set_flag(const Value &value) {
            reg = reg | value._value;
        }
    
        /**
         * Reset bit according value mask
         * @param value mask
         */
        [[maybe_unused]]
        void unset_flag(const Value &value) {
            reg = reg | (~value._value);
        }
    
        /**
         * Check if all bit in mask is set (value 1)
         *
         * In case of empty mask behaviour is undefined.
         * @param value mask
         * @return true if all bits are set
         */
        [[maybe_unused]] [[nodiscard]]
        bool is_set(Value value) const {
            return static_cast<uint8_t>(*this) & value._value;
        }
    
        /**
         * Check if all bit in mask is unset (value 0)
         *
         * In case of empty mask behaviour is undefined.
         * @param value mask
         * @return true if all bits are set
         */
        [[maybe_unused]] [[nodiscard]]
        bool is_unset(Value value) const {
            return !is_set(value);
        }
        
        /**
         * Assign all bit according value
         *
         * @param value actual value
         */
        void operator=(Value value) {
            reg = value._value;
        }
        
        void operator|=(Value value) {
            reg |= value._value;
        }
    
        [[nodiscard]]
        bool operator&(Value value) const {
            return reg & value._value;
        }
    
        [[nodiscard]]
        bool operator|(Value value) const {
            return reg | value._value;
        }
    
        [[nodiscard]]
        operator uint8_t() const {
            return reg;
        }
    
        [[nodiscard]]
        uint8_t operator~() const {
            return ~reg;
        }
    };
}