//
// Created on 02.08.2021.
//

#pragma once

#include <vector>
#include "Types/BasicType.h"

namespace fedora {
    namespace context {
        /**
         * Arguments for force function call
         *
         * @brief Actually, it's a list of BasicTypes
         * @see BasicType
         *
         * @example of all possible argument options:
         * 1. A number
         * 2. A string
         * 3. A list
         * 4. A FunCall
         * force main( 1 "a string" ["a" "list" ["nested" "list"] ] function function(1 2 3))
         *
         */
        class ForceArgs {
            std::vector<types::BasicType> args = std::vector<types::BasicType>();
        };
    }
}
