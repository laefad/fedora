#pragma once

#include <utility>
#include <vector>
#include "BasicType.h"

namespace fedora {
    namespace types {
        class FunCall : public types::BasicType {
        protected:
            // TODO добавить указатель на контекст
            // Имя функции, которая будет вызвана
            std::wstring nameToCall;
            // Массив аргументов функции, которая будет вызвана
            std::vector<std::shared_ptr<fedora::types::BasicType>> args = std::vector<std::shared_ptr<fedora::types::BasicType>>();
        public:
            FunCall() = default;

            Type type() override {
                return FUN_CALL;
            }

            std::wstring eval() override {
                return L"FunCall: " + nameToCall;
            }

            // Возвращает результат выполнения функции. Это либо простой тип, либо очередной funcall
            std::unique_ptr<fedora::types::BasicType> execute() {

            }
        };
    }

    namespace builder{
        class BuildableFunCall:public types::FunCall{
        public:
            void setName(std::wstring newName) {
                nameToCall = std::move(newName);
            }

            void addArgument(const std::shared_ptr<fedora::types::BasicType>& b){
                args.push_back(b);
            }
        };
    }

}
