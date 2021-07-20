#pragma once

#include <string>

namespace fedora {
    namespace types {

        class BasicType {
        public:
            // Преобразование в строку
            virtual std::wstring eval() = 0;
        };

    }
}