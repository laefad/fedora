//
// Created on 20.07.2021.
//
#pragma once

#include <string>

namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
    private:
        std::wstring data;
    public:

        explicit Token(std::wstring data);

        // TODO Корректно ли возвращать референс, а не саму строку, чтобы получить буст производительности?
        // Но сделай тогда его неизменяемым(если я правильно const понимаю): std::wstring const & 
        // Иначе сейчас можно менять содержимое по ссылке 
        std::wstring & getData();

        bool isEmpty() const;

        friend bool operator==(Token &lhs, Token &rhs);
    };
}
