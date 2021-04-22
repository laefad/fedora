#pragma once
#include "BasicType.h"
namespace fedora {
    namespace types {

        class String : public BasicType 
        {
        private:
            std::wstring value;
        public:
            std::wstring eval();
        };

    }
}