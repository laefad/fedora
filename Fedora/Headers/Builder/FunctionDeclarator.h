//
// Created on 03.08.2021.
//

#pragma once

#include <utility>

#include "Function/Context.h"

namespace fedora {
    namespace builder {

        /**
         * Steps of function declaration
         */
        enum FunctionDeclarationMode {
            /**
             * @example
             * pure, force
             *
             * pure let a = 1
             */
            SET_KEYWORDS,

            /**
             * Must be a valid not-keyword name
             *
             * @example
             * main
             *
             * let main = 1
             */
            SET_NAME,

            /**
             * Must be a valid not-keyword name
             *
             * @example
             * a b c
             *
             * let main a = +(a 1) # Adds 1 to a and returns result #
             */
            SET_ARGS,

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
             * Stuff function returns
             * @see ReadResult.h analyzeToken(Token&) function docs
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
        private:
            /**
             * Function we are building
             */
            std::shared_ptr<function::Function> function;

            /**
             * Step of building process we are on
             */
            FunctionDeclarationMode funMode;
        public:
            explicit FunctionDeclarator(std::shared_ptr<function::Function> f) : function(std::move(f)) {
            }
        };
    }
}