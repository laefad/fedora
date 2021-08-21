//
// Created on 02.08.2021.
//

#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {
        /**
         * NULL_ type. Means literally "nothing"
         *
         * @note Can be used as bool.
         * if arg != null -> true;
         * if arg == null -> false;
         */
        class Null : public BasicType {
        public:
            std::wstring eval() override;

            Type type() override {
                return types::NULL_;
            }
        };
    }
}
