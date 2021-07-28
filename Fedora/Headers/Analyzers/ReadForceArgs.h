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
        // TODO Избавиться от этого лкасса в пользу readFunArgs
        /**
         * Класс чтения аргументов для force вызова функции
         * @see [Keywords.force]
         *
         * @example
         * force main(1 2 3)
         *
         * @example
         * let fun a = a
         * let main = [1 fun(2)] // Здесь данный класс выполняет функцию чтения аргумента функции fun внутри списка
         */
        class ReadForceArgs : public AnalyticBasic {
        public:
            explicit ReadForceArgs(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;
        };
    }
}