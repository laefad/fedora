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
        /// Номер строки, на которой был расположен токен
        uint32_t line;
    public:

        explicit Token(std::wstring data, uint32_t line);
        explicit Token(std::wstring data);

        // TODO Корректно ли возвращать референс, а не саму строку, чтобы получить буст производительности?
        // Но сделай тогда его неизменяемым(если я правильно const понимаю): std::wstring const & 
        // Иначе сейчас можно менять содержимое по ссылке 
        std::wstring & getData();

        // TODO Добавить в токен функцию, которая будет возвращать, что длина равна единице? 
        // Это нужно для красоты. Типа bool isChar(){return data.length()==1;}

        // TODO DEPRECATED
        bool isEmpty() const;

        friend bool operator==(Token &lhs, Token &rhs);
    };
}
