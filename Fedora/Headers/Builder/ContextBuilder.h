//
// Created on 01.08.2021.
//

#pragma once

#include <memory>

#include "Utils/BasicSingleton.h"
#include "Function/Function.h"
#include "Utils/Logger.h"

namespace fedora {
    /**
     * Context builder
     *
     * @brief Singleton pattern
     */
    class ContextBuilder : public BasicSingleton {
    private:
        static ContextBuilder *instance;

        ContextBuilder() {
            currentFun = std::make_shared<function::Function>(nullptr);
        }

        ~ContextBuilder() {
            fedora::Logger::logW(L"ContextBuilder instance is destroyed");
        }

        std::shared_ptr<function::Function> currentFun;
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
        void declareNewFunction();

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
