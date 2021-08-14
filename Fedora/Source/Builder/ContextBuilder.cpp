//
// Created on 01.08.2021.
//

#include <Builder/ContextBuilder.h>
#include <KeyWords.h>
#include "Types/Number.h"
#include "Exceptions/BuilderException.h"
#include "Stack/StackHolder.h"

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
        }


        // If t == let -> we don't need anything special, cause function is already declared
        if (t != let) {
            functionDeclarator.addPreFunKeyWord(t);
        }


        if (t == let)
            throw exception::BuilderException(
                    "A \"let\" token must not be pushed to the context. Use ContextBuilder::notifyWeGotLetToken() instead.",
                    "ContextBuilder::addFunctionDeclarationToken");
    }

    void ContextBuilder::notifyWeGotLetToken() {
        if (functionDeclarator.isNull()) {
            createFunctionAndBuilder();
        }
    }

    void ContextBuilder::setFunctionName(Token const &t) {
        functionDeclarator.setFunctionName(t.getData());
    }

    void ContextBuilder::notifyWeSetReturnable() {
        functionDeclarator.setReturnableMode();
    }

    void ContextBuilder::addReturnableNumber(std::wstring &s) {
        // TODO Перегнать wstring в double в конструкторе Number
        std::shared_ptr<types::Number> n = std::make_shared<types::Number>();
        functionDeclarator.setNumberAsReturnable(n);
    }

    void ContextBuilder::setForceName(std::wstring &s) {
        forceCallDeclarator.setName(s);
    }

    void ContextBuilder::notifyWeStartForceCall() {
        StackHolder *stackHolder = StackHolder::GetInstance();
        std::shared_ptr<builder::BuildableForceCall> newForce = std::make_shared<builder::BuildableForceCall>();
        stackHolder->addForceCall(newForce);
        forceCallDeclarator = builder::ForceCallDeclarator(newForce);
    }
}
