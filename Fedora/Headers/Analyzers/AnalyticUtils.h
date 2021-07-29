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
            static bool isValidName(std::wstring &);

            /// Являеится ли строка ключевым словом
            static bool isValueAKeyWord(std::wstring &);

            /// Являеится ли строка числом
            static bool isValueANumber(std::wstring &);

            /// Являеится ли строка строкой
            static bool isValueAString(std::wstring &);

            /// Является ли строка ключевым словом перед функцией
            static bool isTokenAPreFunKeyWord(std::wstring &);

            /// Является ли строка ключевым словом перед функцией
            static bool isBracket(std::wstring &);

            /// Является ли токен открытой квадратной скобкой ("[")
            static bool isTokenALeftSquareBracket(std::wstring&);

            /// Является ли токен закрытой квадратной скобкой ("]")
            static bool isTokenARightSquareBracket(std::wstring&);

            /// Is token an opening bracket ("(")
            static bool isTokenALeftCircleBracket(std::wstring &);

            /// Is token a closing bracket (")")
            static bool isTokenARightCircleBracket(std::wstring &);
        };
    }
}
