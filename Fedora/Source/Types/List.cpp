
#include "Types/List.h"

#include <sstream>

namespace fedora {
    namespace types {

        std::wstring List::eval() {
            std::shared_ptr<List> next = this->next;
            std::wstringstream buff;

            buff << L'[';

            if (value)
                buff << value->eval();

            while (next) {
                buff << L' ' << next->value->eval();
                next = next->next;
            } 

            buff << L']';

            return buff.str();
        };

    }
}
