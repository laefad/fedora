//
// Created on 01.08.2021.
//

#pragma once

#include <memory>

#include "Utils/BasicSingleton.h"
#include "Context/Function/Function.h"
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
         *
         * @note
         * We have to explicitly initialize the member 'functionDeclarator' which does not have a default constructor.
         * That's why we init it with functionDeclarator(nullptr).
         * // TODO Стоит ли объявить пустой дефолтный конструктор, чтобы мы могли убрать functionDeclarator(nullptr) из конструктора? Текущее решение выглядит уродливо, зато работает явно. Скрытие плохого кода через дефолтный конструктор я считаю небезопасным. ИМХО пусть лучше будет некрасиво, но безопасно
         */
        ContextBuilder() : functionDeclarator(nullptr) {
            currentContext = std::make_shared<context::Function>(nullptr);
        }

        ~ContextBuilder() {
            fedora::Logger::logW(L"ContextBuilder instance is destroyed");
        }

        // TODO Переписать документацию
        /**
         * Pointer to current context
         *
         * @note redeclare utilities each time we get new context //TODO ВЫнести утилиты и контекст в приват абстрактного билдера и наследовать этот класс от него. Но мб это не нужно делать. Посмотрим, как будет выглядеть сборщик без этого
         */
        // TODO Заменить Function на Package?
        std::shared_ptr<context::Function> currentContext;

        /// Function declaration utility
        builder::FunctionDeclarator functionDeclarator;//builder::FunctionDeclarator(nullptr);

        // TODO Стоит ли разбить объявление функции и создание билдера на 2 функции? Или не стоит упоминать в имени 2 действия? Мне не нравится нарушение принципа единой ответственности
        void createFunctionAndBuilder() {
            std::shared_ptr<context::Function> newFunction = currentContext->addFunction();
            functionDeclarator = builder::FunctionDeclarator(newFunction);
        }

    public:
        static ContextBuilder *GetInstance();

        void addFunctionDeclarationToken(KeyWord &);

        void notifyWeGotLetToken();

        void setFunctionName(std::wstring &);

        void notifyWeSetReturnable();

        void addReturnableNumber(std::wstring &);
    };
}
