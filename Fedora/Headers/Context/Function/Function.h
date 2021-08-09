#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <Token.h>
#include <KeyWords.h>
#include <Utils/Logger.h>

#include "Context/Function/Returnable/Returnable.h"
#include "Context/Function/Returnable/ReturnableNumber.h"
#include "Types/BasicType.h"
#include "Arguments.h"



namespace fedora {
    namespace context {
        // TODO Использовать buildable context
        class Function : public std::enable_shared_from_this<Function> {
            // TODO Вынести в .cpp реализации И инициализации
        protected:
            std::shared_ptr<Function> parent;
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<NamesOfArguments> args = std::make_unique<NamesOfArguments>();
            std::wstring name = L"";
            std::vector<KeyWord> keyWords = std::vector<KeyWord>();

            std::vector<std::shared_ptr<Function>> children = std::vector<std::shared_ptr<Function>>();
        public:
            explicit Function(std::shared_ptr<Function> parent) : parent(std::move(parent)) {}

            /**
            * Start context declaration
            */
            std::shared_ptr<context::Function> addChildFunction(std::shared_ptr<context::Function> newFunction) {
                children.push_back(newFunction);
                return newFunction;
            }
        };
    }
}