#pragma once

#include "Types/BasicType.h"
#include "Types/UnbindedFunCall.h"

namespace fedora
{
    namespace builder{
        class BuildableFunCall : public types::UnbindedFunCall{
        public:
            explicit BuildableFunCall():
                UnbindedFunCall(
                    L"",
                    types::UnbindedFunCall::FunCallArguments()
                )
            {}

            void setName(std::wstring newName) {
                functionName = std::move(newName);
            }

            void addArgument(const std::shared_ptr<fedora::types::BasicType>& b){
                args.push_back(b);
            }
        };
    }
}
