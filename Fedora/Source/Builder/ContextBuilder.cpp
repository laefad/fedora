#include <utility>

#include "Exceptions/BuilderException.h"

#include "Builder/ContextBuilder.h"

#include "Types/Number.h"
#include "Types/String.h"
#include "Types/Null.h"
#include "Types/List.h"

#include "Stack/StackHolder.h"

#include "StaticUtils.h"

namespace fedora
{
    void ContextBuilder::addFunctionDeclarationToken(parser::Token& t)
    {
        using fedora::parser::TokenType;

        if (functionDeclarator.isNull())
        {
            // Need to declare new blank function
            createFunctionAndBuilder();
        }

        // If t == let -> we don't need anything special, cause function is already declared
        if (t.getType() != TokenType::FunctionDeclaration)
        {
            functionDeclarator.addPreFunKeyWord(t);
        }

        if (t.getType() == TokenType::FunctionDeclaration)
            throw BuilderException(
                u8"A \"let\" token must not be pushed to the context. Use ContextBuilder::notifyWeGotLetToken() instead.",
                u8"ContextBuilder::addFunctionDeclarationToken"
            );
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
    void ContextBuilder::notifyWeGotLetToken()
    {
        currentFunCall = nullptr;
        currentList = nullptr;
        if (functionDeclarator.isNull()) {
            // cases 1 and 2
            createFunctionAndBuilder();
        } else {
            // case 3
            std::shared_ptr<builder::BuildableFunction> newFunction = std::make_shared<builder::BuildableFunction>(nullptr);
            newFunction->setParent(functionDeclarator.getFunction());
            functionDeclarator = builder::FunctionDeclarator(newFunction);
        }
    }

    void ContextBuilder::setFunctionName(parser::Token const& t)
    {
        functionDeclarator.setFunctionName(t.getData());

        if (functionDeclarator.isFunctionHasParent()) {
            functionDeclarator.getDowncastedParent()->setChildFunction(
                functionDeclarator.getFunction(),
                functionDeclarator.getFunctionName()
            );
        } else {
            context->operator[](functionDeclarator.getFunctionName()) = functionDeclarator.getFunction();
        }
    }

    void ContextBuilder::notifyWeSetReturnable() {
        functionDeclarator.setReturnableMode();
    }

    void ContextBuilder::addReturnableNumber(std::u8string const& s)
    {
        // TODO оно тут не нужно
        // exception::BuilderException e = exception::BuilderException(L"Couldn't convert \"" + s + L"\" to double",
        //                                                             L"ContextBuilder::addReturnableNumber(std::wstring const &s)");
        double newValue = StaticUtils::u8s2d(s);
        std::shared_ptr<types::Number> n = std::make_shared<types::Number>(newValue);
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
    }

    void ContextBuilder::setForceName(std::u8string const& u8s)
    {
        currentFunCall->setName(u8s);
    }

    void ContextBuilder::notifyWeStartForceCall()
    {
        std::shared_ptr<builder::BuildableFunCall> newForce = std::make_shared<builder::BuildableFunCall>();
        newForce->setForce();
        currentFunCall = newForce;
        stackHolder.addForceCall(newForce);
        // forceCallDeclarator = builder::ForceCallDeclarator(newForce);
    }

    void ContextBuilder::addReturnableFunCall(const std::u8string& name)
    {
        std::shared_ptr<builder::BuildableFunCall> n = std::make_shared<builder::BuildableFunCall>();
        n->setName(name);
        currentFunCall = n;
        functionDeclarator.setReturnable(n);
    }

    void ContextBuilder::addArgumentName(const parser::Token& t)
    {
        functionDeclarator.addArgumentName(t);
    }

    void ContextBuilder::addReturnableNull()
    {
        std::shared_ptr<types::Null> n = std::make_shared<types::Null>();
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
    }

    void ContextBuilder::addReturnableString(const std::u8string& s)
    {
        std::shared_ptr<types::String> n = std::make_shared<types::String>(s);
        functionDeclarator.setReturnable(n);
        finishFunctionDeclaration();
    }

    void ContextBuilder::addReturnableList()
    {
        std::shared_ptr<types::List> n = std::make_shared<types::List>();
        functionDeclarator.setReturnable(n);
        currentList = n;
        isBuildingList = true;
    }

    std::shared_ptr<types::BasicType> ContextBuilder::t2Bt(const parser::Token& t)
    {
        if (t.getType() == parser::TokenType::Number) {
            double newValue = StaticUtils::u8s2d(t.getData());
            return std::make_shared<types::Number>(newValue);

        } else if (t.getType() == parser::TokenType::String) {
            return std::make_shared<types::String>(t.getData());

        } else if (t.getType() == parser::TokenType::Null) {
            return std::make_shared<types::Null>();
            
        } else {
            throw BuilderException(
                u8"You're trying to convert token to BasicType, but token is not a primitive type instance.",
                u8"ContextBuilder::t2Bt(const parser::Token&)"
            );
        }
    }

    void ContextBuilder::addSimpleTypeInList(const parser::Token& t)
    {
        if (isBuildingList && currentList != nullptr) {
            //std::shared_ptr<builder::MutableList> newA = currentList;
            //currentList->addBasicToFirstFoundPlace(t2Bt(t),newA );
            addToList(t2Bt(t));
        } else { 
            // TODO Вынести тексты всех ошибок в один файл
            throw BuilderException(
                u8"You're trying to add a primitive type to the list, while the list is NOT being declared",
                u8"ContextBuilder::addSimpleTypeInList"
            );
        }
    }

    void ContextBuilder::addFunCallInList(const parser::Token& t)
    {
        if (isBuildingList && currentList != nullptr) {
            std::shared_ptr<builder::BuildableFunCall> n = std::make_shared<builder::BuildableFunCall>();
            n->setName(t.getData());
            currentFunCall = n;
            addToList(n);
            //currentList->addBasicToFirstFoundPlace(n, currentList);
        } else{ 
            // TODO Вынести тексты всех ошибок в один файл
            throw BuilderException(
                u8"You're trying to add a funCall to the list, while the list is NOT being declared",
                u8"ContextBuilder::addFunCallInList"
            );
        }
    }

    void ContextBuilder::endList()
    {
        functionDeclarator.setReturnable(currentList);
        Logger::logV(functionDeclarator.getFunction()->logRet());
        currentList = nullptr;
        isBuildingList = false;
    }

    void ContextBuilder::addToList(std::shared_ptr<types::BasicType> v)
    {
        if (currentList->getValue())
            currentList = types::List::addNewItemToTheEnd(std::move(v), currentList);
        else
            currentList = std::make_shared<types::List>(v);
    }

    void ContextBuilder::addPrimitiveAsCallArgument(const parser::Token& t)
    {
        using parser::TokenType;

        switch (t.getType())
        {
        case TokenType::String:
            addBasicToCallArguments(t2Bt(t));
            break;
        case TokenType::Number:
            addBasicToCallArguments(t2Bt(t));
            break;
        case TokenType::Null:
            addBasicToCallArguments(t2Bt(t));
            break;
        default:
            throw BuilderException(
                u8"addPrimitiveAsCallArgument(const parser::Token &t)", 
                u8"Analyzer was trying to add Non-Primitive-type token as a primitive call argument. Shit!"
            );
            break;
        }
    }

    void ContextBuilder::addBasicToCallArguments(std::shared_ptr<types::BasicType> basic) {
        if (currentFunCall) {
            currentFunCall->addArgument(basic);
        } else {
            throw BuilderException(
                u8"ContextBuilder::addBasicToCallArguments(std::shared_ptr<types::BasicType>)", 
                u8"currentFunCall is nullptr. Couldn't add an argument"
            );
        }
    }

    void ContextBuilder::finishCurrentContext() {
        if (functionDeclarator.isFunctionHasParent()) {
            functionDeclarator = builder::FunctionDeclarator(functionDeclarator.getDowncastedParent());
        } else {
            functionDeclarator = builder::FunctionDeclarator(nullptr);
        }
    }
}
