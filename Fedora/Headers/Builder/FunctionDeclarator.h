//
// Created on 03.08.2021.
//

#pragma once

#include <utility>
#include "Types/Number.h"
#include "Context/Function/Returnable/Returnable.h"

namespace fedora {
    namespace builder {

        /**
         * Steps of context declaration
         */
        enum FunctionDeclarationMode {
//            /**
//             * @example
//             * pure, force
//             *
//             * pure let a = 1
//             */
//            SET_KEYWORDS,
//
//            /**
//             * Must be a valid not-keyword name
//             *
//             * @example
//             * main
//             *
//             * let main = 1
//             */
//            SET_NAME,
//
//            /**
//             * Must be a valid not-keyword name
//             *
//             * @example
//             * a b c
//             *
//             * let main a = +(a 1) # Adds 1 to a and returns result #
//             */
//            SET_ARGS,

            SET_INITIAL,

            /**
             * "Where" part declaration. Function context is a sub-functions container
             *
             * @example
             * let main where
             *      let a = 1
             * = a
             *
             * force main   # main returns 1, because "a = 1" #
             */
            SET_CONTEXT,

            /**
             * Stuff context returns
             * @see ReadResult.h analyzeToken(Token&) context docs
             *
             * @example
             * let a = 1    <- "= 1" is returnable part. "1" is a value to be returned
             */
            SET_RETURNABLE,
        };

        /**
         * Function declaration class
         * takes @param context and manages Function building process
         */
        class FunctionDeclarator {
            // TODO У нас есть контекст, в который добавляются функции, а манипулирует функцией этот класс. Это паттерн Посетитель?
            // TODO Вынести в .cpp
        private:
            /**
             * Function we are building
             */
            std::shared_ptr<context::Function> function;

            /**
             * Step of building process we are on
             */
            FunctionDeclarationMode funMode;

            /**
             * let a where
             *  let b = 1
             *              <- Here we set SET_CONTEXT mode
             * = # <- Here we set SET_RETURNABLE # 2
             * @return
             */
            FunctionDeclarationMode setFunMode() const {
                FunctionDeclarationMode result = SET_INITIAL;
                if (function != nullptr) {
                    if (!function->isContextEmpty()) {
                        result = SET_CONTEXT;
                    }

                    if (function->isContextFinished())
                        result = SET_RETURNABLE;
                }

                return result;
            };
        public:
            explicit FunctionDeclarator(std::shared_ptr<context::Function> f) : function(std::move(f)),
                                                                                funMode(setFunMode()) {}

            // TODO Стоит ли внедрять в каждую функцию проверку на Nullptr?
            bool isNull() {
                return function == nullptr;
            }

            void addPreFunKeyWord(KeyWord &t) {
                function->addKeyWord(t);
            }

            void setFunctionName(std::wstring &s) {
                function->setName(s);
            }

            void setReturnableMode() {
                function->setContextFinished();
            }

            void setNumberAsReturnable(const std::shared_ptr<types::Number> &n) {
                context::Returnable r = context::Returnable(n);
                function->setReturnable(r);
            }
        };

    }
}