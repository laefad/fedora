#pragma once

#include <memory>

#include "Types/FunCall.h"
#include "Utils/BasicSingleton.h"
#include "Context/Function/Function.h"
#include "Context/Package.h"
#include "Utils/Logger.h"
#include "Parser/Token.h"
#include "FunctionDeclarator.h"
#include "ForceCallDeclarator.h"
#include "Builder/BuildableFunction.h"
#include "Builder/BuildableFunCall.h"
#include "Stack/StackHolder.h"

namespace fedora {
    /**
     * Context builder
     *
     * @brief
     * Does 2 things:
     * 1. Declares function
     * 2. Declares funCall
     *
     * You need funCalls in 2 cases:
     * 1. force call
     * @example
     * force main()             <- "main" is a funCall
     *
     * 2. returnable funCall
     * @example
     * let a = main(1 2 3)      <- "main" is a funCall
     *
     * @note FunCall declaration is possible inside Function. But Function declaration inside FunCall is NOT possible
     */
    class ContextBuilder {
    private:

        // TODO Переписать документацию
        /**
         * Pointer to current context
         *
         * @note redeclare utilities each time we get new context //TODO ВЫнести утилиты и контекст в приват абстрактного билдера и наследовать этот класс от него. Но мб это не нужно делать. Посмотрим, как будет выглядеть сборщик без этого
         */
        // TODO Заменить Function на Package с unique_ptr
        //std::shared_ptr<context::Function> currentContext;
        //std::shared_ptr<context::Function> currentFunction;
        std::shared_ptr<context::Package> package;

        /// Function declaration utility
        builder::FunctionDeclarator functionDeclarator;

        builder::ForceCallDeclarator forceCallDeclarator;

        StackHolder stackHolder;

        /**
         * @example case 1: Top-level function declaration
         * let example = 1
         */
        void createFunctionAndBuilder() {
            std::shared_ptr<builder::BuildableFunction> newFunction = std::make_shared<builder::BuildableFunction>(
                    nullptr);
            functionDeclarator = builder::FunctionDeclarator(newFunction);
        }

        /**
         * @example case 1:
         * let a where
         *  let b = null
         *  # function b has a parent #
         *
         * @example case 2:
         * let a = null
         * let b = null
         * # function b has no parent #
         */
        void finishFunctionDeclaration() {
            if (functionDeclarator.isFunctionHasParent()) {
                // case 1
                functionDeclarator = builder::FunctionDeclarator(functionDeclarator.getUpcastedParent());
            } else {
                // case 2
                functionDeclarator = builder::FunctionDeclarator(nullptr);
            }
        }

        bool isBuildingList = false;
        std::shared_ptr<types::List> currentList = nullptr;

        void addToList(std::shared_ptr<types::BasicType>);

        std::shared_ptr<builder::BuildableFunCall> currentFunCall = nullptr;
    public:
        ContextBuilder() :
                functionDeclarator(nullptr),
                forceCallDeclarator(nullptr),
                package(std::make_shared<context::Package>()),
                stackHolder(StackHolder())
        {}

        ~ContextBuilder() = default;

        /**
         * Add keyword to function
         *
         * @example
         * pure let a = 1 <- "pure" will be added via this method
         *
         */
        void addFunctionDeclarationToken(parser::Token &);

        void notifyWeGotLetToken();

        void setFunctionName(parser::Token const &);

        void notifyWeSetReturnable();

        /// set NULL_ as returnable
        void addReturnableNull();

        void addReturnableNumber(std::u8string const &);

        void addReturnableString(std::u8string const &);

        void addReturnableFunCall(std::u8string const &);

        void addReturnableList();

        void endList();

        static std::shared_ptr<types::BasicType> t2Bt(const parser::Token &);

        void addSimpleTypeInList(const parser::Token &t);

        void addFunCallInList(const parser::Token &);

        void notifyWeStartForceCall();

        void addArgumentName(parser::Token const &);

        void setForceName(std::u8string const &);
        // TODO Добавить режим заполнения: функция, фанколл и проверять, своевременно ли вызван метод

        bool isCurrentFunctionForced(parser::Token &) {
            return true;
        }

        std::shared_ptr<context::Package> getPackage() {
            return package;
        }
    };
}
