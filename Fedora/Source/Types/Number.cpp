#include "Types/Number.h"

#include "StaticUtils.h"

namespace fedora::types {
    Number::Number(double v) :
            value(v) {}

    Type Number::type() {
        return types::NUMBER;
    }

    std::u8string Number::eval() {
        return StaticUtils::d2u8s(value);
    }

    double Number::getValue() const {
        return value;
    }
}
