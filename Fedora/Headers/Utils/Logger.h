//
// Created on 28.07.2021.
//

#pragma once

#include "Utils/SettingsSingleton.h"
#include <iostream>

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
        static void log(const std::string &msg, fedora::settings::LogLevel logLevel);
        static void log(const std::wstring &msg, fedora::settings::LogLevel logLevel);

        /// Log verbose
        static void logV(const std::wstring &msg);

        /// Log warnings
        static void logW(const std::wstring &msg);

        /// Log errors
        static void logE(const std::wstring &msg);
    };
}
