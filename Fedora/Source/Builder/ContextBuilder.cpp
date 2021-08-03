//
// Created on 01.08.2021.
//

#include <Builder/ContextBuilder.h>

namespace fedora {
    /// Initializing
    ContextBuilder *ContextBuilder::instance = nullptr;

    /// Simple instance getter
    ContextBuilder *fedora::ContextBuilder::GetInstance() {
        if (instance == nullptr) {
            instance = new ContextBuilder();
            instance->addToCleaner();
        }
        return instance;
    }

    void ContextBuilder::declareNewFunction(Token &t) {
        currentContext.
    }
}
