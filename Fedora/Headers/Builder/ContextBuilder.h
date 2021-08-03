//
// Created on 01.08.2021.
//

#pragma once

#include <memory>

#include "Utils/BasicSingleton.h"
#include "Function/Function.h"
#include "Utils/Logger.h"
#include "Token.h"
#include "FunctionDeclarator.h"

namespace fedora {
    /**
     * Context builder
     *
     * @brief Singleton pattern.
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
    class ContextBuilder : public BasicSingleton {
    private:
        /**
         * @static Singleton instance
         */
        static ContextBuilder *instance;

        /**
         * Constructor that initializes private stuff
         */
        ContextBuilder() {
            currentContext = std::make_shared<function::Context>(nullptr);
            // TODO Declare new function
        }

        ~ContextBuilder() {
            fedora::Logger::logW(L"ContextBuilder instance is destroyed");
        }

        /**
         * Pointer to current context
         *
         * @note redeclare utilities each time we get new context //TODO ВЫнести утилиты и контекст в приват абстрактного билдера и наследовать этот класс от него
         */
        std::shared_ptr<function::Context> currentContext;

        /// Function declaration utility
        builder::FunctionDeclarator functionDeclarator;//builder::FunctionDeclarator(nullptr);

    public:
        static ContextBuilder *GetInstance();

        /**
         * Add new function in context
         * @example
         * let a = ...
         * let b = ... <- Add new function next to previous
         *
         * @example
         * let a = ...
         * let b where
         *    let c = ... <- Add new function in sub-context
         * = ...
         *
         * @example
         * pure let a = 1 <- Declaration starts with a keyword
         *
         * @example
         * force
         */
        void declareNewFunction(Token &);

        void addKeyWordToCurrent();

        void addArgumentToCurrent();


        void setReturnable();

        void setListAsReturnable();

        void addArgumentToList();

        void addFunctionAsArgument();

        void setNumberAsReturnable();

        void setStringAsReturnable();
    };
}
