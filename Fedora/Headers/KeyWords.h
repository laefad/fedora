//
// Created on 24.07.2021.
//

#pragma once

namespace fedora{

    class KeyWord{
        std::wstring value;
    public:
        explicit KeyWord(std::wstring value1):value(value1){}
        std::wstring getValue(){
            return value;
        }
    };

    class KeyWords{
    private:

    public:
        static KeyWord pure = KeyWord(L"pure");
        static KeyWord force = KeyWord(L"force");
        static KeyWord let = KeyWord(L"let");
        static KeyWord where = KeyWord(L"where");
        static KeyWord returns = KeyWord(L"=");
        static KeyWord import = KeyWord(L"import");
        static KeyWord using_ = KeyWord(L"using");
    };
}