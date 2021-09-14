#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {

        class Number : public BasicType {
        private:
            double value;
        public:
            std::u8string eval() override;

            Type type() override;

            explicit Number(double v);

            double getValue() const;
        };

    }
}
