
#include "Types/Number.h"

namespace fedora {
    namespace types {

        Number::Number(double v):
            value(v) 
        {}

        Type Number::type() {
            return types::NUMBER;
        }

        std::wstring Number::eval() {
            return std::to_wstring(value);
        }

        double Number::getValue() const {
            return value;
        }

    }
}
