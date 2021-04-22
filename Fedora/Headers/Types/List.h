#pragma once
#include "BasicType.h"
namespace fedora {
    namespace types {

        class List : public BasicType 
        {
        private:
            BasicType* value;
            List* next;
        public:
            std::wstring eval();
        };

    }
}