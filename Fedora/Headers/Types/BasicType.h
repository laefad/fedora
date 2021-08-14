#pragma once

#include <string>
#include <memory>

namespace fedora {
    namespace types {

        enum Type {
            NUMBER,
            STRING,
            LIST,
            FUN_CALL,
            NULL_,
        };

        /**
         * Base class for data type
         */
        class BasicType : public std::enable_shared_from_this<BasicType> {
        public:
            /// ToString() stuff
            virtual std::wstring eval() = 0;

            /// Get type of basic function-object
            virtual Type type() = 0;
        };

    }
}
