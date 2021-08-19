#pragma once

#include <vector>

#include "Utils/SettingsSingleton.h"

namespace fedora {
    namespace Utils {
        /**
         * Clean singletons by their pointers
         *
         * @brief
         * Utility to save us from memory leak
         *
         * @note
         * We need to update [cleanThemAll] method every time we add new global singleton
         *
         */
        class SingletonsCleaner : public BasicSingleton {
        private:
            /// Classic private singleton constructor
            SingletonsCleaner() = default;

            /// Main instance
            static SingletonsCleaner *instance;

            std::vector<BasicSingleton *> singletons = std::vector<BasicSingleton *>();
        public:
            /// Singleton can't be copied
            SingletonsCleaner(SingletonsCleaner &other) = delete;

            /// Singletons should not be assignable.
            void operator=(const SingletonsCleaner &) = delete;

            /// Singleton instance getter
            static SingletonsCleaner *GetInstance();

            void cleanThemAll();

            void addToSingletons(BasicSingleton *);

            /// Does nothing
            void cleanFields() override {
                // Если я умру, меня заменят
            }
        };


    }
}
