#pragma once

#include <utility>
#include <vector>
#include "BasicType.h"

namespace fedora {
    namespace types {
        class FunCall : public types::BasicType {
        public:
            using FunCallArguments = std::vector<std::shared_ptr<fedora::types::BasicType>>;
        protected:
            // Массив аргументов функции, которая будет вызвана
            FunCallArguments args;
        protected:
            explicit FunCall(FunCallArguments args) :
                    args(args) {}

        public:
            virtual Type type() override {
                return FUN_CALL;
            }

            virtual std::wstring eval() = 0;

        private:
            explicit FunCall();
        };
    }
}
