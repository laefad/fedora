//
// Created on 20.07.2021.
//
#include "string"

#ifndef FEDORA_TOKEN_H
#define FEDORA_TOKEN_H
namespace fedora {
    /// Токен, который мы прочитали и будем анализировать
    /// В классе можно сохранять контекст распрашеного токена для анализа
    class Token {
    public:
        Token(std::wstring &data);

        std::wstring data;
        bool isEmpty = false;
    };
}
#endif //FEDORA_TOKEN_H
