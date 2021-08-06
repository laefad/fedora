//
// Created on 02.08.2021.
//

#pragma once

#include "ForceArgs.h"
#include "Function/Returnable/Returnable.h"

namespace fedora {
    namespace context {

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
            context::Returnable execute() {

            }
        };
    }
}
