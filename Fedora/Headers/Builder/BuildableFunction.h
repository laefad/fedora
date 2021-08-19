#pragma once

#include "Context/Function/Function.h"
#include "Context/Function/Returnable/Returnable.h"
#include <utility>

namespace fedora {
    namespace builder {
        /**
         * BuildableFunction is an extension for Function to build it and make original Function clear
         */
        class BuildableFunction : public context::Function {
            /**
             * flag, that says function context is fully declared
             *
             * @example
             * let a where
             *                  # contextIsReady == false #
             *  let b = null
             *                  # contextIsReady == false #
             * = # contextIsReady == true # null
             */
            bool contextIsReady = false;
        public:
            explicit BuildableFunction(std::shared_ptr<Function> parent): 
                context::Function(std::move(parent))
            {}

            bool isNameDeclared() {
                return !name.empty();
            }

            bool isContextEmpty() {
                return children.empty();
            }

            /**
             * Add pre-fun keyword
             *
             * @example
             * pure let a = null    # <- "pure" has to be added via this method #
             */
            void addKeyWord(parser::Token &t) {
                keyWords.push_back(t);
            }

            /**
             * Remember raw function name
             */
            void setName(std::wstring const &s) {
                name = s;
            }

            /**
             * Notify that function context has finished
             *
             * @example
             * let a where
             *  let b = null
             * = # setContextFinished() is called after "=" is read #
             * null
             */
            void setContextFinished() {
                contextIsReady = true;
            }

            bool isContextFinished() const {
                return contextIsReady;
            }

            /**
             * Set returnable value to function
             */
            void setReturnable(context::Returnable &r) {
                returnable = std::make_unique<context::Returnable>(r);
            }

            void addArgName(const std::wstring& wstring){
                args->addStrToArgNames(wstring);
            }
        };
    }
}
