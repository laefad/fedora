//
// Created on 05.08.2021.
//

#pragma once

namespace fedora {
    namespace function {

        enum FunctionEntityType {
            DECLARATION_FUNCTION,
            CALL_FUNCTION,
        };

        class BasicFunction {
        public:
            virtual FunctionEntityType getType() = 0;
        };
    }
}