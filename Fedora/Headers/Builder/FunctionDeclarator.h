#pragma once

#include <utility>
#include "Types/Number.h"
#include "Context/Function/Returnable/Returnable.h"
#include "Builder/BuildableFunction.h"

namespace fedora {
    namespace builder {

        /**
         * Steps of context declaration
         */
        enum FunctionDeclarationMode {
            /// Declare function keywords, name and arg names
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
            std::shared_ptr<builder::BuildableFunction> function;

//            /**
//             * Step of building process we are on
//             */
//            FunctionDeclarationMode funMode;
//
//            /**
//             * let a where
//             *  let b = 1
//             *              <- Here we set SET_CONTEXT mode
//             * = # <- Here we set SET_RETURNABLE # 2
//             * @return
//             */
//            FunctionDeclarationMode setFunMode() const {
//                FunctionDeclarationMode result = SET_INITIAL;
//                if (function != nullptr) {
//                    if (!function->isContextEmpty()) {
//                        result = SET_CONTEXT;
//                    }
//
//                    if (function->isContextFinished())
//                        result = SET_RETURNABLE;
//                }
//
//                return result;
//            };
        public:
            explicit FunctionDeclarator(std::shared_ptr<builder::BuildableFunction> f):
                function(std::move(f))
            {}

            // TODO Стоит ли внедрять в каждую функцию проверку на Nullptr?
            bool isNull() {
                return function == nullptr;
            }

            /**
             * Add function keyword
             * @example
             * pure let a = null <- "pure" keyword should be added via this method
             */
            void addPreFunKeyWord(parser::Token &t) {
                function->addKeyWord(t);
            }

            bool isFunctionHasParent(){
                return function->isHasParent();
            }

            std::shared_ptr<builder::BuildableFunction> getUpcastedParent(){
                return std::static_pointer_cast<builder::BuildableFunction>(function->getParent());
            }

            /**
             * @return pointer to function
             */
            std::shared_ptr<builder::BuildableFunction> getFunction(){
                return function;
            }

            /**
             * Add function keyword
             * @example
             * pure let main = 1 <- name "name" should be set via this method
             */
            void setFunctionName(std::wstring const &s) {
                function->setName(s);
            }

            /**
             * Add function keyword
             * @example
             * pure let main arg1 = 1 <- after you added "arg1",
             *                              you should notify builder that context declaration has finished
             */
            void setReturnableMode() {
                function->setContextFinished();
            }

            /**
             * Add function keyword
             * @example
             * pure let main arg1 = 1 <- set "1" as returnable
             */
            void setReturnable(const std::shared_ptr<types::BasicType> &n) {
                context::Returnable r = context::Returnable(n);
                function->setReturnable(r);
            }

            void addArgumentName(const parser::Token &t){
                function->addArgName(t.getData());
            }
        };

    }
}
