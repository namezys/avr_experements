#pragma once

#include "str.h"

namespace sarv {
    namespace logging {
        enum class Level {
            Error,
            Info,
            Debug
        };
    
        template<Level _level, class Usart>
        class SyncLogger: protected Usart {
        
            static
            bool is_enabled(Level a_level) {
                switch(_level) {
                    case Level::Error:
                        return a_level == Level::Error;
                    case Level::Info:
                        return a_level == Level::Error || a_level == Level::Info;
                    default:
                        return true;
                }
            }
        
            void _log(const sarv::PmStr& str) {
                Usart::sync_send(str);
            }
            
            void _log_hex(uint8_t value) {
                char buffer[] = " 0x00";
                buffer[4] = '0' + value % 16;
                buffer[3] = '0' + value / 16;
                Usart::sync_send_string(buffer);
            }
    
            void _log_hex(uint16_t value) {
                char buffer[] = " 0x0000";
                buffer[6] = '0' + value % 16;
                value /= 16;
                buffer[5] = '0' + value % 16;
                value / 16;
                buffer[4] = '0' + value % 16;
                value /= 16;
                buffer[3] = '0' + value;
                Usart::sync_send_string(buffer);
            }
    
        public:
            SyncLogger(): Usart(true) {}
        
            void log(Level a_level, const sarv::PmStr& str) {
                if (is_enabled(a_level)) {
                    Usart::sync_send(str);
                    Usart::sync_send('\n');
                }
            }
    
            template<class T>
            void log(Level a_level, const sarv::PmStr& str, const T& v) {
                if (is_enabled(a_level)) {
                    Usart::sync_send(str);
                    _log_hex(v);
                    Usart::sync_send('\n');
                }
            }
        };
    
        template<Level _level, class Usart>
        class DummyLogger {
        public:
            static
            void log(Level a_level, const sarv::PmStr& str) {
            }
            
            template<class T>
            void log(Level a_level, const sarv::PmStr& str, const T& v) {
            }
        };
    }
}

#define LOG(level, str, ...) logger.log(level, P(str), ## __VA_ARGS__)
#define ERROR(str, ...) LOG(sarv::logging::Level::Error, str, ##__VA_ARGS__)
#define INFO(str, ...) LOG(sarv::logging::Level::Info, str, ##__VA_ARGS__)
#define DEBUG(str, ...) LOG(sarv::logging::Level::Debug, str, ##__VA_ARGS__)
