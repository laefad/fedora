//
// Created on 28.07.2021.
//

#pragma once
#include "Utils/SettingsSingleton.h"

namespace fedora{
    /**
     * Logging class
     */
    class Logger{
    public:
        /**
         * Log message
         * @param msg - text you want to log
         * @param logLevel - message logLevel that compares to settings logLevel
         */
        static void log(const std::string& msg, fedora::settings::LogLevel logLevel);
        static void log(const std::wstring& msg, fedora::settings::LogLevel logLevel);

        /// Log verbose
        static void logV(const std::wstring& msg);
        /// Log warnings
        static void logW(const std::wstring& msg);
        /// Log errors
        static void logE(const std::wstring& msg);
    };

    void Logger::log(const std::string& msg, fedora::settings::LogLevel logLevel) {
        // Convert string to wstring and use another method
        log(StaticUtils::s2ws(msg), logLevel);
    }

    void Logger::log(const std::wstring &msg, fedora::settings::LogLevel logLevel) {
        // Get settings
        fedora::Settings * settings = fedora::Settings::GetInstance();

        // Get logLevel from settings
        fedora::settings::LogLevel settingsLogLevel = settings->getLogLevel();

        // if message log levels allows it to be printed
        if (logLevel >= settingsLogLevel){
            // print it
            std::wcout<<msg<<std::endl;
        }
    }

    void Logger::logV(const std::wstring &msg) {
        log(msg, fedora::settings::LOG_VERBOSE);
    }

    void Logger::logW(const std::wstring &msg) {
        log(msg, fedora::settings::LOG_WARNING);
    }

    void Logger::logE(const std::wstring &msg) {
        log(msg, fedora::settings::LOG_ERROR);
    }
}
