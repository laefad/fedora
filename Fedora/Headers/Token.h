//
// Created on 20.07.2021.
//
#pragma once

#include <string>

namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
    public:
        Token(std::wstring data);

        std::wstring data;
        bool isEmpty = false;

        friend bool operator== (Token &lhs, Token &rhs);
    };
}
