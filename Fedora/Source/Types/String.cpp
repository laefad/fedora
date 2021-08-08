#include "Types/String.h"

namespace fedora {
    namespace types {
        // TODO убрать отсылку 
        std::wstring String::eval() {
            return L'\"' + this->value + L'\"' + L" Как с деньгами обстоят вопросы?";
        };
    }
}
