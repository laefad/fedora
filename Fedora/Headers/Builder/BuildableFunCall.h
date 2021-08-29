//
// Created on 29.08.2021.
//

#pragma once
#include "Types/FunCall.h"

namespace fedora {
    namespace builder {
        class BuildableFunCall: public types::FunCall{
        public:
            /**
             * Set funCall name
             *
             * @brief
             * This function should be used in 2 cases:
             * 1. When we create new funCall and set name of the function we call
             * 2. When we replace context
             */
            void setName(std::wstring newName) {
                nameToCall = std::move(newName);
            }

            void addArgument(fedora::types::BasicType b){
                args.push_back(b);
            }
        };
    }
}
