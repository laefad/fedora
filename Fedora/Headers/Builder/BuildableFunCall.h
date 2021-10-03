#pragma once

#include "Types/BasicType.h"
#include "Types/UnbindedFunCall.h"

namespace fedora {
    namespace builder {
        class BuildableFunCall : public types::UnbindedFunCall {
        public:
            explicit BuildableFunCall() :
                    UnbindedFunCall(
                            u8"",
                            types::UnbindedFunCall::FunCallArguments()
                    ) {}

            void setName(std::u8string newName) {
                functionName = std::move(newName);
            }

            void setForce() {
                forced = true;
            };

            void addArgument(std::shared_ptr<fedora::types::BasicType> b) {
                args.push_back(b);
            }
        };
    }
}
