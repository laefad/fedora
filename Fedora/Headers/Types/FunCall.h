#pragma once

#include <vector>

#include "Function.h"
#include "BasicType.h"

namespace fedora {
    namespace types {
        class FunCall : public types::BasicType {
        private:
            std::wstring nameToCall;
            std::vector<fedora::types::BasicType> args = td::vector<fedora::types::BasicType>();
        public:
            FunCall() = default;

            Type type() override {
                return FUN_CALL;
            }

            /// Я Аянами Рей, а кто ты?
            std::unique_ptr<fedora::types::BasicType> execute() {

            }
        };
    }

}
