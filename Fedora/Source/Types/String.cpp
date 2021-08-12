#include "Types/String.h"

namespace fedora {
    namespace types {
        // TODO убрать отсылку 
        std::wstring String::eval() {
            return L'\"' + this->value + L'\"';
        }

        std::wstring String::getImportantQuestion() {
            // Строка "как с деньгами обстоят вопросы" представляет ценность для этого проекта
            return L"Как с деньгами обстоят вопросы?";
        };
    }
}
