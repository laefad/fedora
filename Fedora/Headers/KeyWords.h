#pragma once

#include <vector>
#include <string>

#include "Token.h"

namespace fedora {
    class KeyWord : public Token {
    public:
        explicit KeyWord(std::wstring wstr, uint32_t line);

        explicit KeyWord(std::wstring wstr);

        explicit KeyWord(Token &t);

        explicit KeyWord(Token const &t);

        friend bool operator==(Token &lhs, KeyWord &rhs);

        //friend bool operator==(KeyWord &lhs, Token &rhs);
        friend bool operator==(KeyWord &lhs, KeyWord &rhs);

        friend bool operator!=(KeyWord &lhs, KeyWord &rhs);
    };

    static KeyWord pure = KeyWord(L"pure");
    static KeyWord force = KeyWord(L"force");
    static KeyWord let = KeyWord(L"let");
    static KeyWord where = KeyWord(L"where");
    static KeyWord returns = KeyWord(L"=");

    static KeyWord import = KeyWord(L"import"); // TODO Пока не используется
    static KeyWord using_ = KeyWord(L"using");  // TODO Пока не используется

    class KeyWords {
    public:
        static std::vector<KeyWord> getAllKeyWords();

        static std::vector<KeyWord> getPreFunKeyWords();
    };
}
