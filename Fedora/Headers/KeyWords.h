//
// Created on 24.07.2021.
//

#pragma once
#include <utility>
#include <vector>
#include <string>

namespace fedora{

    class KeyWord{
        std::wstring value;
    public:
        explicit KeyWord(std::wstring value1):value(std::move(value1)){}
        std::wstring& getValue(){
            return value;
        }
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