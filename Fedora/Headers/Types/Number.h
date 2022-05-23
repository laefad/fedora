#pragma once

#include "Types/BasicType.h"

namespace fedora::types {
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
