//
// Created on 02.08.2021.
//

#pragma once

#include "Types/BasicType.h"

namespace fedora {
    namespace types {
        /**
         * Null type. Means literally "nothing"
         *
         * @note Can be used as bool.
         * if arg != null -> true;
         * if arg == null -> false;
         */
        class Null : public BasicType {
            std::wstring eval() override;
        };
    }
}