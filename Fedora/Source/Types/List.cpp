#include "Types/List.h"

namespace fedora {
    namespace types {

        std::wstring List::eval() {
            fedora::types::List *next = this->next;
            std::wstring result = L"( ";
            while (next != nullptr) {
                result += next->value->eval() + L" ";
                next = next->next;
            }
            return result + L")";
        };

    }
}
