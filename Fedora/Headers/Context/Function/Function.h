#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <Token.h>
#include <KeyWords.h>

#include "Context/Function/Returnable/Returnable.h"
#include "Context/Function/Returnable/ReturnableNumber.h"
#include "Types/BasicType.h"
#include "Arguments.h"


namespace fedora {
    namespace context {
        // TODO Использовать buildable context
        class Function : public std::enable_shared_from_this<Function> {
            // TODO Вынести в .cpp реализации И инициализации
        private:
            bool contextIsReady = false;

            std::shared_ptr<Function> parent;
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<NamesOfArguments> args = std::make_unique<NamesOfArguments>();
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

            void setReturnable(Returnable &r) {
                returnable = std::make_unique<Returnable>(r);
            }


            /**
             * Start context declaration
             */
            std::shared_ptr<context::Function> addFunction() {
                std::shared_ptr<context::Function> newFunction = std::make_shared<context::Function>(
                        shared_from_this());
                children.push_back(newFunction);
                return newFunction;
            }
        };
    }
}