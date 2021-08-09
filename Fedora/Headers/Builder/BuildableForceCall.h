//
// Created on 09.08.2021.
//

#pragma once

#include "Stack/ForceCall/ForceCall.h"

namespace fedora {
    namespace builder {
        class BuildableForceCall : public context::ForceCall {
        public:
            void setRawName(std::wstring s) {
                rawFunToCallName = std::move(s);
            }
        };
    }
}
