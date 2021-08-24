#include "Types/List.h"

namespace fedora {
    namespace types {

        std::wstring List::eval() {
            std::shared_ptr<List> next = this->next; // TODO Эта строчка бессмысленна
            std::wstring result = L"( ";
            while (next != nullptr) {
                result += next->value->eval() + L" ";
                next = next->next;
            }
            return result + L")";
        };

    }
}
