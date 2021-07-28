//
// Created on 28.07.2021.
//

#pragma once

#include "Token.h"
#include <vector>
#include "Exceptions/SettingsException.h"

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

    class Settings {
    private:
        /// Classic private singleton constructor
        Settings() {}

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

        /// Set log level
        void setLogLevel(settings::LogLevel l);
        /// Get log level
        settings::LogLevel getLogLevel();
    };

    Settings *Settings::instance = nullptr;

    /// Simple instance getter
    Settings *Settings::GetInstance() {
        if (instance == nullptr) {
            instance = new Settings();
        }
        return instance;
    }

    void Settings::setLogLevel(settings::LogLevel l) {
        logLevel = l;
    }

    settings::LogLevel Settings::getLogLevel() {
        return logLevel;
    }
}
