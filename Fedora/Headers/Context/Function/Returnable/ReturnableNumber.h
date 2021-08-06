//
// Created on 05.08.2021.
//

#pragma once

#include "Returnable.h"
#include "Types/Number.h"

namespace fedora {
    class ReturnableNumber : public context::Returnable, public types::Number {
    public:
        explicit ReturnableNumber(double v) : types::Number(v) {}

        std::unique_ptr<fedora::types::BasicType> &get() override {
            return this;
        }
    };
}

