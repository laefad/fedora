#include "List.h"
namespace fedora {
    namespace types {

        std::wstring List::eval() {
            List* next = this->next;
            std::wstring result = L"( ";
            while (next != nullptr)
            {
                result += next->value->eval() + L" ";
                next = next->next;
            }
            return result + L")";
        };

    }
}