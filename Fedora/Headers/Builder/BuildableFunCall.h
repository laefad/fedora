#pragma once

#include "Types/BasicType.h"
#include "Types/FunCall.h"

namespace fedora
{
    namespace builder{
        class BuildableFunCall : public types::FunCall{
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
