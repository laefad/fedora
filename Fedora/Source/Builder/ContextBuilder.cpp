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
            // TODO Clion пишет "Pointer may be null", имея ввиду, что инстанс может быть нулёвым. Не понимаю, как это возможно?
            instance->addToCleaner();
        }
        return instance;
    }

    void ContextBuilder::addFunctionDeclarationToken(KeyWord &t) {
        if (functionDeclarator.isNull()) {
            // Need to declare new blank function

            createFunctionAndBuilder();
        } else {
            // Continue to build function
        }


        // If t == let -> we don't need anything special, cause function is already declared
        if (t != let) {
            functionDeclarator.addPreFunKeyWord(t);
        }
    }

    void ContextBuilder::notifyWeGotLetToken() {
        if (functionDeclarator.isNull()) {
            createFunctionAndBuilder();
        }
    }

    void ContextBuilder::setFunctionName(std::wstring &s) {
        functionDeclarator.setFunctionName(s);
    }

    void ContextBuilder::notifyWeSetReturnable() {
        functionDeclarator.setReturnableMode();
    }

    void ContextBuilder::addReturnableNumber() {

    }
}
