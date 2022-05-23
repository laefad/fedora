#pragma once

#include "Types/BasicType.h"

namespace fedora::types {
    /**
     * NULL_ type. Means literally "nothing"
     *
     * @note Can be used as bool.
     * if arg != null -> true;
     * if arg == null -> false;
     */
    class Null : public BasicType {
    public:
        std::u8string eval() override;

        Type type() override {
            return types::NULL_;
        }
    };
}
