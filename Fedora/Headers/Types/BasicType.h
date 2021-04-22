    #pragma once
#include <string>
namespace fedora {
    namespace types {

        class BasicType
        {
        public:
            virtual std::wstring eval() = 0;
        };

    }
}