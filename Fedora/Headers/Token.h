//
// Created on 20.07.2021.
//
#pragma once

#include <string>

namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
        bool empty = false;
        std::wstring data;
    public:
        explicit Token(std::wstring data);

        // TODO Корректно ли возвращать референс, а не саму строку, чтобы получить буст производительности?
        std::wstring &getData() {
            return data;
        }

        bool isEmpty() const {
            return empty;
        }

        void setEmpty(bool b) {
            empty = b;
        }

        friend bool operator==(Token &lhs, Token &rhs);
    };
}
