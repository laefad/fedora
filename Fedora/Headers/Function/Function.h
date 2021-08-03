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
        class Context;

        class Function : public std::enable_shared_from_this<Function> {
            // TODO Вынести в .cpp реализации И инициализации
        private:
            std::shared_ptr<Context> outsideContext;
            std::shared_ptr<Context> insideContext = std::make_shared<Context>(shared_from_this());
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<Arguments> args = std::make_unique<Arguments>();
            std::wstring name = L"";
            std::vector<Token> keyWords = std::vector<Token>();
        public:
            explicit Function(std::shared_ptr<Context> parent) : outsideContext(std::move(parent)) {}

            bool isNameDeclared() {
                return !name.empty();
            }

        };
    }
}