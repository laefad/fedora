#pragma once

#include <utility>

#include "FException.h"

namespace fedora {

    class AnalyzerException : public FException {
    protected:
        const std::wstring file;
        const std::wstring func;
    protected:
        std::wstring construct() const override {
            std::wstring buf;

            buf += L"AnalyzerException";
            buf += L"\n\tFile: ";
            buf += file;
            buf += L"\n\tFunc: ";
            buf += func;
            buf += L"\n\tError: ";
            buf += text;

            return buf;
        }

        // TODO Мы можем показывать кол-во последних токенов в сообщении об ошибке
        // parser::ParserUtils::format(tokensHolder.getLines(3,1))

    public:
        AnalyzerException(std::wstring text, std::wstring file, std::wstring func):
            FException(std::move(text)),
            file(std::move(file)),
            func(std::move(func))
        {}
    };
}
