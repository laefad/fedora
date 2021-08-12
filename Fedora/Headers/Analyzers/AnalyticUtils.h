//
// Created on 23.07.2021.
//
#pragma once

#include <string>
#include <Token.h>

namespace fedora {
    namespace analytic {
        class AnalyticUtils {
        public:
            /// Валидно ли имя функции или переменной
            static bool isValidName(Token &);

            /// Являеится ли строка ключевым словом
            static bool isValueAKeyWord(Token &);

            /// Являеится ли строка числом
            static bool isValueANumber(Token &);

            /// Являеится ли строка строкой
            static bool isValueAString(Token &);

            /// Является ли строка ключевым словом перед функцией
            static bool isTokenAPreFunKeyWord(Token &);

            /// Является ли строка ключевым словом перед функцией
            static bool isBracket(Token &);

            /// Является ли токен открытой квадратной скобкой ("[")
            static bool isTokenALeftSquareBracket(Token &);

            /// Является ли токен закрытой квадратной скобкой ("]")
            static bool isTokenARightSquareBracket(Token &);

            /// Is token an opening bracket ("(")
            static bool isTokenALeftCircleBracket(Token &);

            /// Is token a closing bracket (")")
            static bool isTokenARightCircleBracket(Token &);
        };
    }
}
