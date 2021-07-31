//
// Created on 28.07.2021.
//

#pragma once

#include "Token.h"
#include <vector>
#include "Exceptions/SettingsException.h"
#include "BasicSingleton.h"

/**
 * Settings class
 *
 * @brief Singleton pattern implementation
 */
namespace fedora {
    namespace settings{
        enum LogLevel{
            LOG_VERBOSE,
            LOG_WARNING,
            LOG_ERROR,
        };
    }

    class Settings: public BasicSingleton{
    private:
        /// Classic private singleton constructor
        Settings() = default;

        /// Main instance
        static Settings *instance;

        /// How logs are detailed
        settings::LogLevel logLevel = settings::LOG_VERBOSE;
    public:

        /// Singleton can't be copied
        Settings(Settings &other) = delete;

        /// Singletons should not be assignable.
        void operator=(const Settings &) = delete;

        /// Singleton instance getter
        static Settings *GetInstance();

        /// Log level Setter
        void setLogLevel(settings::LogLevel l);
        /// Log level Getter
        settings::LogLevel getLogLevel();
    };
}
