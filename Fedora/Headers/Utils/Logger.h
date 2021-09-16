#pragma once

#include <string>

#include "Utils/SettingsSingleton.h"

namespace fedora {
    /**
     * Logging class
     */
    class Logger {
    public:
        /**
        * Log message
        * @param msg - text you want to log
        * @param logLevel - message logLevel that compares to settings logLevel
        */
        static void log(const std::u8string &msg, fedora::settings::LogLevel logLevel);

        /// Log verbose
        static void logV(const std::u8string &msg);

        /// Log warnings
        static void logW(const std::u8string &msg);

        /// Log errors
        static void logE(const std::u8string &msg);

    };
}
