#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <Token.h>
#include <KeyWords.h>

#include "Context.h"
#include "Function/Returnable/Returnable.h"
#include "Arguments.h"


namespace fedora {
    namespace function {
        // TODO Использовать buildable function
        class Function : public std::enable_shared_from_this<Function> {
            // TODO Вынести в .cpp реализации И инициализации
        private:
            bool contextIsReady = false;

            std::shared_ptr<Function> parent;
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<Arguments> args = std::make_unique<Arguments>();
            std::wstring name = L"";
            std::vector<KeyWord> keyWords = std::vector<KeyWord>();

            std::vector<std::shared_ptr<Function>> children = std::vector<std::shared_ptr<Function>>();
        public:
            explicit Function(std::shared_ptr<Function> parent) : parent(std::move(parent)) {}

            bool isNameDeclared() {
                return !name.empty();
            }

            bool isContextEmpty() {
                return children.empty();
            }

            void addKeyWord(KeyWord &t) {
                keyWords.push_back(t);
            }

            void setName(std::wstring &s) {
                name = s;
            }

            void setContextFinished() {
                contextIsReady = true;
            }

            bool isContextFinished() const {
                return contextIsReady;
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