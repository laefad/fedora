#pragma once

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "Function.h"

#include "Analyzers/ReadName.h"


namespace fedora {
    namespace function {
        /// Pre-declaration of function class //TODO Мб в единый внешний файл пре-декларации вынести?
        class Function;

        // Контекст, где хранятся функции и их контексты
        class Context : public std::enable_shared_from_this<Context> {
            // TODO Вынести в .cpp реализации И инициализации
        public:
            /**
             * Constructor with pointer to parent initialization
             */
            explicit Context(std::shared_ptr<Function> p) : parent(std::move(p)) {}

            std::shared_ptr<Function> parent;

            bool isEmpty() {
                return functions.empty();
            }

            /**
             * Start function declaration
             *
             */
            std::shared_ptr<function::Function> addFunction() {
                std::shared_ptr<analytic::ReadName> a = std::make_shared<analytic::ReadName>(std::vector<Token>());
                std::shared_ptr<function::Function> newFunction = std::make_shared<function::Function>(
                        shared_from_this());
//                functions.push_back(newFunction);
//                return newFunction;
            }

        private:
            std::vector<std::shared_ptr<Function>> functions = std::vector<std::shared_ptr<Function>>();
        };

    }
}
