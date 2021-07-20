#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {

        class Number : public BasicType {
        private:
            double value;
        public:
            std::wstring eval();
        };

    }
}

