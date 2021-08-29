#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <Parser/Token.h>
#include <KeyWords.h>
#include <Utils/Logger.h>

#include "Context/Function/Returnable/Returnable.h"
#include "Context/Function/Returnable/ReturnableNumber.h"
#include "Types/BasicType.h"
#include "Arguments.h"
#include <map>


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
            std::vector<parser::Token> keyWords = std::vector<parser::Token>();

            std::map<std::wstring, std::shared_ptr<Function>> children = std::map<std::wstring, std::shared_ptr<Function>>();
        public:
            explicit Function(std::shared_ptr<Function> parent) : parent(std::move(parent)) {}

            std::shared_ptr<std::map<std::wstring, std::shared_ptr<Function>>> getContext(){
                return std::make_shared<std::map<std::wstring, std::shared_ptr<Function>>>(children);
            }
        };
    }
}