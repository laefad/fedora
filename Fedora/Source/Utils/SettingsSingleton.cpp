//
// Created on 28.07.2021.
//

#include "Utils/SettingsSingleton.h"

namespace fedora {
    /// Initializing
    Settings *Settings::instance = nullptr;

    /// Simple instance getter
    Settings *Settings::GetInstance() {
        if (instance == nullptr) {
            instance = new Settings();
            instance->addToCleaner();
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
