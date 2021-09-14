//
// Created on 09.08.2021.
//

#pragma once

#include "Stack/ForceCall/ForceCall.h"

namespace fedora {
    namespace builder {
        /**
         * BuildableForceCall is an extension for ForceCall to build it and make original ForceCall clear
         */
        class BuildableForceCall : public context::ForceCall {
        public:
            /// remember function name user want to call as raw string
            void setRawName(std::u8string s) {
                rawFunToCallName = std::move(s);
            }
        };
    }
}
