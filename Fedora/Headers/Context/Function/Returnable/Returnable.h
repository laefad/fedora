#pragma once

#include "Types/BasicType.h"

namespace fedora {
    namespace context {

        class Returnable {
        public:
            virtual std::unique_ptr<fedora::types::BasicType> &get() = 0;

        private:
            Returnable() {}
        };
    }
}