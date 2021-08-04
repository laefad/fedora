#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <Token.h>

#include "Context.h"
#include "Returnable.h"
#include "Arguments.h"


namespace fedora {
    namespace function {
        class Function : public std::enable_shared_from_this<Function> {
            // TODO Вынести в .cpp реализации И инициализации
        private:
            std::shared_ptr<Function> parent;
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<Arguments> args = std::make_unique<Arguments>();
            std::wstring name = L"";
            std::vector<Token> keyWords = std::vector<Token>();

            std::vector<std::shared_ptr<Function>> children = std::vector<std::shared_ptr<Function>>();
        public:
            explicit Function(std::shared_ptr<Function> parent) : parent(std::move(parent)) {}

            bool isNameDeclared() {
                return !name.empty();
            }

            bool isContextEmpty() {
                return children.empty();
            }

            /**
             * Start function declaration
             */
            std::shared_ptr<function::Function> addFunction() {
                std::shared_ptr<function::Function> newFunction = std::make_shared<function::Function>(
                        shared_from_this());
                children.push_back(newFunction);
                return newFunction;
            }

        };
    }
}