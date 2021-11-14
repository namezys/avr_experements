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
    
        public:
            SyncLogger(): Usart(true) {}
        
            void log(Level a_level, const sarv::PmStr& str) {
                if (is_enabled(a_level)) {
                    Usart::sync_send(str);
                    Usart::sync_send('\n');
                }
            }
        };
    }
}

#define LOG(level, str) logger.log(level, P(str))
#define ERROR(str) LOG(sarv::logging::Level::Error, str)
#define INFO(str) LOG(sarv::logging::Level::Info, str)
#define DEBUG(str) LOG(sarv::logging::Level::Debug, str)
