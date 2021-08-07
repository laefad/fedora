#include "Types/Number.h"

namespace fedora {
    namespace types {

        std::wstring Number::eval() {
            return std::to_wstring(this->value);
        };

    }
}
