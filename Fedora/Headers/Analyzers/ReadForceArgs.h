//
// Created on 23.07.2021.
//
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        namespace readForce{
            enum mode{

            };
        }
        /**
         * Класс чтения аргументов для force вызова функции
         * @see [Keywords.force]
         *
         * @example
         * force main(1 2 3)
         *
         * @example
         * let fun a = a
         * let main = [1 fun(1 2 3)] // Здесь данный класс выполняет функцию чтения аргумента функции fun внутри списка
         *
         * @example
         * force main( fun1 fun2(1 2 3 )) // Nested function
         */
        class ReadForceArgs : public AnalyticBasic {
        public:
            // TODO Если токены не используются, можно в базовый конструктор посылать пустой массив, а в конструкторе класса убрать аргумент
            explicit ReadForceArgs(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;
        };
    }
}