#pragma once

#include <sstream>

#include "FException.h"

namespace fedora {

    class AnalyzerException : public FException {
    protected:
        const std::wstring file;
        const std::wstring func;
    protected:
        std::wstring construct() const override {
            std::wstringstream buf;

            buf << L"AnalyzerException"
                << L"\n\tFile: " 
                << file 
                << L"\n\tFunc: " 
                << func
                << L"\n\tError: " 
                << text;

            return buf.str();
        }

        // TODO Мы можем показывать кол-во последних токенов в сообщении об ошибке
        // parser::ParserUtils::format(tokensHolder.getLines(3,1))

    public:
        AnalyzerException(std::wstring text, std::wstring file, std::wstring func):
            FException(text),
            file(file),
            func(func)
        {}
    };
}
