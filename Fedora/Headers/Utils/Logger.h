#pragma once

#include <iostream>

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

        /**
         * @overload log method, but for std::string
         * @param msg is a std::string
         */
        //static void log(const std::string &msg, fedora::settings::LogLevel logLevel);


        /// Log verbose
        static void logV(const std::u8string &msg);

        //static void logV(const std::string &msg);

        /// Log warnings
        static void logW(const std::u8string &msg);

        //static void logW(const std::string &msg);

        /// Log errors
        static void logE(const std::u8string &msg);

        //static void logE(const std::string &msg);
    };
}
