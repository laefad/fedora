//
// Created on 05.08.2021.
//

#pragma once

#include <memory>
#include "Function/Function.h"

namespace fedora {
    namespace function {
        class FunctionCall : public Function {
        public:
            static FunctionEntityType getType() {
                return CALL_FUNCTION;
            }
        };
    }
}
