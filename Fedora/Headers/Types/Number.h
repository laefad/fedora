#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {

        class Number : public BasicType {
        private:
            double value;
        public:
            std::wstring eval() override;

            Number() : value(0.0) {}

            explicit Number(double v) : value(v) {}

            double getValue() const {
                return value;
            };
        };

    }
}

