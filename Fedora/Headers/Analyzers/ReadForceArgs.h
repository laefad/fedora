#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        namespace readForce {
            enum mode {

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
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;
        };
    }
}
