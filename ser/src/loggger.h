#pragma once

#include "str.h"
#include "format.h"

/**
 * Logging system for output messages to USART.
 *
 * You should define Logger with name logger in current scope and use macros ERROR/INFO/DEBUG.
 *
 * Only one parameter in macros is supported right now.
 */
namespace savr::logging {
    
    /** Log level. Lower that defined will be removed from code */
    enum class Level {
        Error [[maybe_unused]],
        Info [[maybe_unused]],
        Debug [[maybe_unused]]
    };
    
    /**
     * Synchronize logger which will output data to usart until last symbol will be write to data buffer.
     *
     * Logger inherit usart interface.
     *
     * @tparam _level lower log level
     * @tparam Usart Usart class which is used for output
     */
    template<Level _level, class Usart>
    class [[maybe_unused]] SyncLogger: public Usart {
        
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
        
    public:
        SyncLogger() : Usart(true) {}
    
        [[maybe_unused]]
        void log(Level a_level, PmStr str) {
            if(is_enabled(a_level)) {
                Usart::sync_send(str);
                Usart::sync_send('\n');
            }
        }
        
        template<class T>
        [[maybe_unused]]
        void log(Level a_level, PmStr str, T v) {
            using namespace savr::format;
            if(is_enabled(a_level)) {
                Usart::sync_send(str);
                Usart::sync_send(Fmt<T>::format(v));
                Usart::sync_send('\n');
            }
        }
    };
    
    /**
     * Fake logger which will not output anything.
     *
     * Using just as replace class for SyncLogger.
     *
     * Provide fake Usart interface
     *
     * @tparam _level not used
     * @tparam Usart not used
     */
    template<Level _level, class Usart>
    class [[maybe_unused]] DummyLogger {
    public:
        // TODO: implement fakse USART
    
        [[maybe_unused]]
        static
        void log(Level, savr::PmStr) {
        }
        
        template<class T>
        [[maybe_unused]]
        void log(Level, savr::PmStr, const T &) {
        }
    };
}

/** Log message with log level. At least message must be provided. Message will be put into flash/ROM space. */
#define LOG(level, str, ...) logger.log(level, P(str), ## __VA_ARGS__)

/** Log error message. At least message must be provided. Message will be put into flash/ROM space. */
#define ERROR(str, ...) LOG(savr::logging::Level::Error, str, ##__VA_ARGS__)

/** Log info message. At least message must be provided. Message will be put into flash/ROM space. */
#define INFO(str, ...) LOG(savr::logging::Level::Info, str, ##__VA_ARGS__)

/** Log debug message. At least message must be provided. Message will be put into flash/ROM space. */
#define DEBUG(str, ...) LOG(savr::logging::Level::Debug, str, ##__VA_ARGS__)

