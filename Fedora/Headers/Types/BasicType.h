#pragma once

#include <string>
#include <memory>

#include "Types/Type.h"

namespace fedora {
    namespace types {
        /**
         * Base class for data type
         */
        class BasicType : public std::enable_shared_from_this<BasicType> {
        public:
            /// ToString() stuff
            virtual std::u8string eval() = 0;

            /// Get type of basic function-object
            virtual Type type() = 0;
        };

    }
}
