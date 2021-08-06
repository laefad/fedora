//
// Created on 05.08.2021.
//

#pragma once

#include <memory>
#include "Function.h"

namespace fedora {
    namespace context {
        class FunctionCall : public Function {
        public:
            static FunctionEntityType getType() {
                return CALL_FUNCTION;
            }
        };
    }
}
