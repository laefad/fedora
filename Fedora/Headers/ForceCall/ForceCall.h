//
// Created on 02.08.2021.
//

#pragma once

#include "ForceArgs.h"
#include "Function/Returnable.h"

namespace fedora {
    namespace function {

        /**
         *  Force function call
         *
         *  @example
         *  let a = ...
         *  force a
         */
        class ForceCall {
            ForceArgs forceArgs = ForceArgs();
        public:
            function::Returnable execute() {

            }
        };
    }
}
