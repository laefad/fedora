#pragma once

#include <string>

#include "Parser/TokenType.h"

namespace fedora::parser {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
    private:

        /// Содержимое токена
        std::u8string data;
        /// Номер строки, на которой был расположен токен
        size_t line;
        /// Тип токена, по умолчанию равен TokenType::None
        TokenType tokenType;

    public:
        explicit Token(std::u8string data, size_t line, TokenType tokenType);

        explicit Token(std::u8string data, TokenType tokenType);

        explicit Token(std::u8string data, size_t line);

        explicit Token(std::u8string data);

        /// @return строковое представление токена
        std::u8string const& getData() const;

        /// @return номер строки, на которой был расположн токен
        size_t getLine() const;

        /// @return тип токена
        TokenType getType() const;

        /// @param type новый тип токена
        void setType(TokenType type);

        friend bool operator==(Token const& lhs, Token const& rhs);
    };
}
