//
// Created on 02.08.2021.
//

#include "Utils/Logger.h"
#include "StaticUtils.h"

namespace fedora {
    void Logger::log(const std::string &msg, fedora::settings::LogLevel logLevel) {
        // Convert string to wstring and use another method
        log(StaticUtils::s2ws(msg), logLevel);
    }

    void Logger::log(const std::wstring &msg, fedora::settings::LogLevel logLevel) {
        // Get settings
        fedora::Settings *settings = fedora::Settings::GetInstance();

        // Get logLevel from settings
        fedora::settings::LogLevel settingsLogLevel = settings->getLogLevel();

        // if message log levels allows it to be printed
        if (logLevel >= settingsLogLevel) {
            // print it
            std::wcout << msg << std::endl;
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

    void Logger::logV(const std::string &msg) {
        log(msg, fedora::settings::LOG_VERBOSE);
    }

    void Logger::logW(const std::string &msg) {
        log(msg, fedora::settings::LOG_WARNING);
    }

    void Logger::logE(const std::string &msg) {
        log(msg, fedora::settings::LOG_ERROR);
    }
}