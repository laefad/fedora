
#include "Types/List.h"

namespace fedora {
    namespace types {

        std::wstring List::eval() {
            std::shared_ptr<List> next = this->next;
            std::wstring buff;

            buff += L'[';

            if (value)
                buff += value->eval();

            while (next) {
                buff += L' ';
                buff += next->value->eval();
                next = next->next;
            }

            buff += L']';

            return buff;
        };

    }
}
