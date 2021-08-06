#pragma once

#include <utility>

#include "Types/BasicType.h"

namespace fedora {
    namespace context {

        class Returnable {
        private:
            std::shared_ptr<fedora::types::BasicType> n;
        public:
            /// Get actual returnable data
            /// TODO Раньше здесь был unique_ptr, но я поставил shared, потому что не только ретурнабл должен иметь дело с данными внутри. Это разуменое решение?
            std::shared_ptr<fedora::types::BasicType> get() {
                return n;
            }

            explicit Returnable(std::shared_ptr<fedora::types::BasicType> t) : n(std::move(t)) {};
        };
    }
}