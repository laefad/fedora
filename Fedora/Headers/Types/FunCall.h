#pragma once

#include <vector>

#include "Function.h"
#include "BasicType.h"

namespace fedora {

    class FunCall : public types::BasicType {
    private:
        std::wstring nameToCall;
        std::vector<fedora::types::BasicType> args = td::vector<fedora::types::BasicType>();
    public:
        FunCall() = default;

        /// Я Аянами Рей, а кто ты?
        std::unique_ptr<fedora::types::BasicType> execute() {

        }
    };

}
