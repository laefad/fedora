#pragma once

#include <vector>

#include "Function.h"
#include "BasicType.h"

namespace fedora {
    namespace types {
        class FunCall : public types::BasicType {
        private:
            // TODO добавить указатель на контекст
            // Имя функции, которая будет вызвана
            std::wstring nameToCall;
            // Массив аргументов функции, которая будет вызвана
            std::vector<fedora::types::BasicType> args = std::vector<fedora::types::BasicType>();
        public:
            FunCall() = default;

            Type type() override {
                return FUN_CALL;
            }

            // Возвращает результат выполнения функции. Это либо простой тип, либо очередной funcall
            std::unique_ptr<fedora::types::BasicType> execute() {

            }
        };
    }

}
