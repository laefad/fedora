#include "Types/String.h"

namespace fedora::types {
    std::u8string String::eval() {
        return u8'\"' + this->value + u8'\"';
    }

    std::u8string String::getImportantQuestion() {
        // Строка "как с деньгами обстоят вопросы" представляет ценность для этого проекта
        return u8"Как с деньгами обстоят вопросы?";
    };
}
