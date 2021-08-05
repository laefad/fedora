#pragma once

#include "BasicType.h"

namespace fedora {
    namespace function {

        class Returnable {
        public:
            virtual std::unique_ptr<fedora::types::BasicType> &get() = 0;

        private:
            Returnable() {}
        };
    }
}