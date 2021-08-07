//
// Created on 02.08.2021.
//

#pragma once

#include <memory>
#include <iostream>
#include <utility>
#include "ForceArgs.h"
#include "Context/Function/Returnable/Returnable.h"

namespace fedora {
    namespace context {

        /**
         *  Force function call
         *
         *  @example
         *  let a = ...
         *  force a
         */
        class ForceCall : public std::enable_shared_from_this<ForceCall> {
            ForceArgs forceArgs = ForceArgs();
            std::wstring rawFunToCallName;
        public:
            void setRawName(std::wstring s) {
                rawFunToCallName = std::move(s);
            }
        };
    }
}
