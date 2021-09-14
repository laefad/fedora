
#include "Types/List.h"

namespace fedora {
    namespace types {

        std::u8string List::eval() {
            std::shared_ptr<List> next = this->next;
            std::u8string buff;

            buff += u8'[';

            if (value)
                buff += value->eval();

            while (next) {
                buff += u8' ';
                buff += next->value->eval();
                next = next->next;
            }

            buff += u8']';

            return buff;
        };

    }
}
