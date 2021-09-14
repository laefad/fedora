#pragma once

#include <memory>
#include <utility>
#include <vector>
#include <map>

#include "Utils/Logger.h"
#include "Parser/Token.h"
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
            std::u8string name = u8"";
            std::vector<parser::Token> keyWords = std::vector<parser::Token>();

            std::map<std::u8string, std::shared_ptr<Function>> children = std::map<std::u8string, std::shared_ptr<Function>>();
        public:
            explicit Function(std::shared_ptr<Function> parent) : parent(std::move(parent)) {}

            std::shared_ptr<std::map<std::u8string, std::shared_ptr<Function>>> getContext(){
                return std::make_shared<std::map<std::u8string, std::shared_ptr<Function>>>(children);
            }

            std::u8string getName() const {
                return name;
            }

            std::shared_ptr<Function> find(std::u8string name) {

            }
        };
    }
}