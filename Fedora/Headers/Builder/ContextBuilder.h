#pragma once

#include <memory>

#include "Utils/BasicSingleton.h"
#include "Context/Function/Function.h"
#include "Context/Package.h"
#include "Utils/Logger.h"
#include "Parser/Token.h"
#include "FunctionDeclarator.h"
#include "ForceCallDeclarator.h"
#include "Builder/BuildableFunction.h"
#include "Types/List.h"

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
        std::shared_ptr<context::Function> currentFunction;
        std::shared_ptr<context::Package> package;

        /// Function declaration utility
        builder::FunctionDeclarator functionDeclarator;

        builder::ForceCallDeclarator forceCallDeclarator;

        /**
         * @example case 1: Top-level function declaration
         * let example = 1
         *
         * @example case 2: Sub-level function declaration
         * let main where
         *   let example = 1
         * ...
         */
        void createFunctionAndBuilder() {
            std::shared_ptr<builder::BuildableFunction> newFunction = std::make_shared<builder::BuildableFunction>(
                    nullptr);
            if (currentFunction == nullptr){
                // case 1: First Top-level function declaration
                currentFunction = newFunction;
                package->addChildFunction(currentFunction);
            }else{
                // case 2: Sub-level function declaration
                currentFunction->addChildFunction(newFunction);
            }
            functionDeclarator = builder::FunctionDeclarator(newFunction);
        }

        bool isBuildingList = false;
        std::shared_ptr<types::List> currentList;

    public:
        ContextBuilder():
            functionDeclarator(nullptr),
            forceCallDeclarator(nullptr),
            currentFunction(nullptr),
            package(std::make_shared<context::Package>())
        {
            
        }

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

        void addReturnableNumber(std::wstring const &);

        void addReturnableString(std::wstring const &);

        void addReturnableFunCall(std::wstring const &);

        void addReturnableList();

        void notifyWeStartForceCall();

        void addArgumentName(parser::Token const &);

        void setForceName(std::wstring const &);
        // TODO Добавить режим заполнения: функция, фанколл и проверять, своевременно ли вызван метод

        bool isCurrentFunctionForced(parser::Token &) {
            return true;
        }
    };
}
