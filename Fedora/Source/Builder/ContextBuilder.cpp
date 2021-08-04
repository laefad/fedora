//
// Created on 01.08.2021.
//

#include <Builder/ContextBuilder.h>
#include <KeyWords.h>

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

    void ContextBuilder::addFunctionDeclarationToken(Token &t) {
        if (functionDeclarator.isNull()) {
            // Need to declare new blank function

            createFunctionAndBuilder();
        } else {
            // Continue to build function
        }

        // If t == let -> we don't need anything special, cause function is already declared
        if (t.data != let.data) {
            //functionDeclarator.
        }
    }
}
