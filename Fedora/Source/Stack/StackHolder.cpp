//
// Created on 07.08.2021.
//

#include "Stack/StackHolder.h"

namespace fedora {
    /// Initializing
    StackHolder *StackHolder::instance = nullptr;

    StackHolder *StackHolder::GetInstance() {
        if (instance == nullptr) {
            instance = new StackHolder();
            instance->addToCleaner();
        }
        return instance;
    };
}

