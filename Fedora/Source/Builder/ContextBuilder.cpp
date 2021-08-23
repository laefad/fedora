//
// Created on 01.08.2021.
//

#include <Builder/ContextBuilder.h>
#include <KeyWords.h>
#include "Types/Number.h"
#include "Types/FunCall.h"
#include "Types/String.h"
#include "Types/Null.h"
#include "Exceptions/BuilderException.h"
#include "Stack/StackHolder.h"
#include "StaticUtils.h"

namespace fedora {
    void ContextBuilder::addFunctionDeclarationToken(parser::Token &t) {
        using fedora::parser::TokenType;
        if (functionDeclarator.isNull()) {
            // Need to declare new blank function
            createFunctionAndBuilder();
        }


        // If t == let -> we don't need anything special, cause function is already declared
        if (t.getType() != TokenType::FunctionDeclaration) {
            functionDeclarator.addPreFunKeyWord(t);
        }


        if (t.getType() == TokenType::FunctionDeclaration)
            throw exception::BuilderException(
                    "A \"let\" token must not be pushed to the context. Use ContextBuilder::notifyWeGotLetToken() instead.",
                    "ContextBuilder::addFunctionDeclarationToken");
    }

    void ContextBuilder::notifyWeGotLetToken() {
        if (functionDeclarator.isNull()) {
            createFunctionAndBuilder();
        }
    }

    void ContextBuilder::setFunctionName(parser::Token const &t) {
        functionDeclarator.setFunctionName(t.getData());
    }

    void ContextBuilder::notifyWeSetReturnable() {
        functionDeclarator.setReturnableMode();
    }

    void ContextBuilder::addReturnableNumber(std::wstring const &s) {
        exception::BuilderException e = exception::BuilderException(L"Couldn't convert \"" + s + L"\" to double",
                                                                    "ContextBuilder::addReturnableNumber(std::wstring const &s)");
        double newValue = StaticUtils::ws2d(s, e);
        std::shared_ptr<types::Number> n = std::make_shared<types::Number>(newValue);
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::setForceName(std::wstring const &s) {
        forceCallDeclarator.setName(s);
    }

    void ContextBuilder::notifyWeStartForceCall() {
        StackHolder *stackHolder = StackHolder::GetInstance();
        std::shared_ptr<builder::BuildableForceCall> newForce = std::make_shared<builder::BuildableForceCall>();
        stackHolder->addForceCall(newForce);
        forceCallDeclarator = builder::ForceCallDeclarator(newForce);
    }

    void ContextBuilder::addReturnableFunCall(const std::wstring &name) {
        std::shared_ptr<types::FunCall> n = std::make_shared<types::FunCall>();
        n->setName(name);
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::addArgumentName(const parser::Token &t) {
        functionDeclarator.addArgumentName(t);
    }

    void ContextBuilder::addReturnableNull() {
        std::shared_ptr<types::Null> n = std::make_shared<types::Null>();
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::addReturnableString(const std::wstring &s) {
        std::shared_ptr<types::String> n = std::make_shared<types::String>(s);
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::addReturnableList() {
        std::shared_ptr<types::List> n = std::make_shared<types::List>();
        functionDeclarator.setReturnable(n);
        currentList = n;
        isBuildingList = true;
    }
}
