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
            bool forced;
        protected:
            explicit FunCall(FunCallArguments args, bool forced) :
                    args(args),
                    forced(forced)
            {}

        public:
            virtual Type type() override {
                return FUN_CALL;
            }

            virtual std::u8string eval() = 0;

            bool isForced() {
                return forced;
            }

        private:
            explicit FunCall();
        };
    }
}
