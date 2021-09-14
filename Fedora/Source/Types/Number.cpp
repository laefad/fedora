
#include "Types/Number.h"

namespace fedora {
    namespace types {

        Number::Number(double v) :
                value(v) {}

        Type Number::type() {
            return types::NUMBER;
        }

        std::u8string Number::eval() {
            //TODO !important add conversion
            return u8"";//std::to_string(value);
        }

        double Number::getValue() const {
            return value;
        }

    }
}
