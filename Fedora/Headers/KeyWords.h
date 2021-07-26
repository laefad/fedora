//
// Created on 24.07.2021.
//

#pragma once
#include <utility>
#include <vector>
#include <string>
#include "Token.h"

namespace fedora{
    // TODO Объявить ключевое слово как Token и перегрузить оператор == у токена
    class KeyWord:public Token{
    public:
        explicit KeyWord(std::wstring value1): Token(std::move(value1)){}
    };

    static KeyWord pure = KeyWord(L"pure");
    static KeyWord force = KeyWord(L"force");
    static KeyWord let = KeyWord(L"let");
    static KeyWord where = KeyWord(L"where");
    static KeyWord returns = KeyWord(L"=");

    static KeyWord import = KeyWord(L"import"); // TODO Пока не используется
    static KeyWord using_ = KeyWord(L"using");  // TODO Пока не используется

    class KeyWords{
    public:
        static std::vector<KeyWord> getAllKeyWords();
        static std::vector<KeyWord> getPreFunKeyWords();
    };
}