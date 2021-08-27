#pragma once

#include <string>

#include "Token.h"
#include "Parser/TokenType.h"

namespace fedora {
    namespace parser {
        /// Токен, который мы прочитали и будем анализировать
        /// В классе можно сохранять контекст распрашеного токена для анализа
        class Token {
        private:

            /// Содержимое токена
            std::wstring data;
            /// Номер строки, на которой был расположен токен
            size_t line;
            /// Тип токена, по умолчанию равен TokenType::None
            TokenType tokenType;

        public:
            explicit Token(std::wstring data, size_t line, TokenType tokenType);
            explicit Token(std::wstring data, TokenType tokenType);
            explicit Token(std::wstring data, size_t line);
            explicit Token(std::wstring data);

            /// @return строковое представление токена
            std::wstring const &getData() const;

            /// @return номер строки, на которой был расположн токен
            size_t getLine() const;

            /// @return тип токена
            TokenType getType() const;

            /// @param type новый тип токена
            void setType(TokenType type);

            /// TODO некорректно для wchar
            /// Cимвол может состоять из нескольки wchar, в случае, если sizeof(wchar) != 4
            /// Если токен состоит из 1 символа, то возвращает true
            bool isChar() const;

            /// TODO некорректно для wchar
            /// Cимвол может состоять из нескольки wchar, в случае, если sizeof(wchar) != 4
            /// Если токен состоит из 1 символа и этот символ равен wchar, то возвращает true
            bool isChar(wchar_t wchr) const;

            friend bool operator==(Token const &lhs, Token const &rhs);
        };
    }
}
