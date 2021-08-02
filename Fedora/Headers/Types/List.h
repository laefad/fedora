#pragma once

#include "BasicType.h"

namespace fedora {
    namespace types {

        class List : public BasicType {
        private:
            BasicType *value;
            // TODO Мб внутрянку списка сделать вектором? Это будет простое и хорошо оптимизированное решение
            List *next;
        public:
            std::wstring eval() override;
        };

    }
}