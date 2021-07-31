//
// Created on 31.07.2021.
//

#include "Utils/SingletonsCleaner.h"

namespace fedora {
    namespace Utils {
        /// Initializing
        SingletonsCleaner *SingletonsCleaner::instance = nullptr;

        /// Simple instance getter
        SingletonsCleaner *SingletonsCleaner::GetInstance() {
            if (instance == nullptr) {
                instance = new SingletonsCleaner();
                instance->addToCleaner();
            }
            return instance;
        }

        void SingletonsCleaner::addToSingletons(BasicSingleton * b) {
            singletons.push_back(b);
        }

        void SingletonsCleaner::cleanThemAll() {
            for(auto& a:singletons)
                delete a;
        }
    }
}

