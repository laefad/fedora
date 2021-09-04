
#include "Builder/ContextBuilder.h"
#include "Types/Number.h"
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
            throw BuilderException(
                    L"A \"let\" token must not be pushed to the context. Use ContextBuilder::notifyWeGotLetToken() instead.",
                    L"ContextBuilder::addFunctionDeclarationToken");
    }

    /**
     * @example case 1: First top-level function declaration
     * let a = 1
     *
     * @example case 2: Another top-level function
     * let a = 1
     * let b = null
     *
     * @example case 3: sub-level function
     * let a where
     *  let b = null
     *  ...
     */
    void ContextBuilder::notifyWeGotLetToken() {
        if (functionDeclarator.isNull()) {
            // cases 1 and 2
            createFunctionAndBuilder();
        } else {
            // case 3
            std::shared_ptr<builder::BuildableFunction> newFunction = std::make_shared<builder::BuildableFunction>(
                    nullptr);
            newFunction->setParent(functionDeclarator.getFunction());
            functionDeclarator = builder::FunctionDeclarator(newFunction);
        }
    }

    void ContextBuilder::setFunctionName(parser::Token const &t) {
        functionDeclarator.setFunctionName(t.getData());
        if (functionDeclarator.isFunctionHasParent()) {
            functionDeclarator.getUpcastedParent()->setChildFunction(functionDeclarator.getFunction(),
                                                                     functionDeclarator.getFunctionName());
        } else {
            package->setChildFunction(functionDeclarator.getFunction(), functionDeclarator.getFunctionName());
        }
    }

    void ContextBuilder::notifyWeSetReturnable() {
        functionDeclarator.setReturnableMode();
    }

    void ContextBuilder::addReturnableNumber(std::wstring const &s) {
        // TODO оно тут не нужно 
        // exception::BuilderException e = exception::BuilderException(L"Couldn't convert \"" + s + L"\" to double",
        //                                                             L"ContextBuilder::addReturnableNumber(std::wstring const &s)");
        double newValue = StaticUtils::ws2d(s);
        std::shared_ptr<types::Number> n = std::make_shared<types::Number>(newValue);
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
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
        std::shared_ptr<builder::BuildableFunCall> n = std::make_shared<builder::BuildableFunCall>();
        n->setName(name);
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::addArgumentName(const parser::Token &t) {
        functionDeclarator.addArgumentName(t);
    }

    void ContextBuilder::addReturnableNull() {
        std::shared_ptr<types::Null> n = std::make_shared<types::Null>();
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
    }

    void ContextBuilder::addReturnableString(const std::wstring &s) {
        std::shared_ptr<types::String> n = std::make_shared<types::String>(s);
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
    }

    void ContextBuilder::addReturnableList() {
        std::shared_ptr<builder::MutableList> n = std::make_shared<builder::MutableList>();
        functionDeclarator.setReturnable(n);
        currentList = n;
        isBuildingList = true;
    }

    std::shared_ptr<types::BasicType> ContextBuilder::t2Bt(const parser::Token &t) {
        if (t.getType() == parser::TokenType::Number) {
            // TODO оно тут не нужно 
            // exception::BuilderException e = exception::BuilderException(
            //         L"Couldn't convert \"" + t.getData() + L"\" to double",
            //         L"ContextBuilder::t2Bt(const parser::Token&)");
            double newValue = StaticUtils::ws2d(t.getData());
            return std::make_shared<types::Number>(newValue);
        } else if (t.getType() == parser::TokenType::String) {
            return std::make_shared<types::String>(t.getData());
        } else if (t.getType() == parser::TokenType::Null) {
            return std::make_shared<types::Null>();
        } else {
            throw BuilderException(
                    L"You're trying to convert token to BasicType, but token is not a primitive type instance.",
                    L"ContextBuilder::t2Bt(const parser::Token&)");
        }
    }

    void ContextBuilder::addSimpleTypeInList(const parser::Token &t) {
        if (isBuildingList && currentList != nullptr) {
            currentList->addBasicToFirstFoundPlace(t2Bt(t));
        } else { // TODO Вынести тексты всех ошибок в один файл
            throw BuilderException(
                    L"You're trying to add a primitive type to the list, while the list is NOT being declared",
                    L"ContextBuilder::addSimpleTypeInList");
        }
    }

    void ContextBuilder::addFunCallInList(const parser::Token &t) {
        if (isBuildingList && currentList != nullptr) {
            std::shared_ptr<builder::BuildableFunCall> n = std::make_shared<builder::BuildableFunCall>();
            n->setName(t.getData());
            currentFunCall = n;
            currentList->addBasicToFirstFoundPlace(n);
        } else { // TODO Вынести тексты всех ошибок в один файл
            throw BuilderException(
                    L"You're trying to add a funCall to the list, while the list is NOT being declared",
                    L"ContextBuilder::addFunCallInList");
        }
    }

    void ContextBuilder::endList() {
        currentList = nullptr;
        isBuildingList = false;
    }
}
