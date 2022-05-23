#include <iostream>

#include "Utils/Logger.h"

#include "StaticUtils.h"

namespace fedora {

    void Logger::log(const std::u8string& msg, fedora::settings::LogLevel logLevel) {
        // Get settings
        fedora::Settings* settings = fedora::Settings::GetInstance();

        // Get logLevel from settings
        fedora::settings::LogLevel settingsLogLevel = settings->getLogLevel();

        // if message log levels allows it to be printed
        if (logLevel >= settingsLogLevel) {
            // print it
            // TODO Мы не можем определить поток для u8string, поэтому 
            // вынуждены конверсировать u8string -> string для каждого вывода 
            std::cout << StaticUtils::u8s2s(msg) << std::endl;
        }
    }

    void Logger::logV(const std::u8string& msg) {
        log(msg, fedora::settings::LOG_VERBOSE);
    }

    void Logger::logW(const std::u8string& msg) {
        log(msg, fedora::settings::LOG_WARNING);
    }

    void Logger::logE(const std::u8string& msg) {
        log(msg, fedora::settings::LOG_ERROR);
    }

}
