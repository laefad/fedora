#pragma once

#include "FException.h"

namespace fedora {
    class ParserException : public FException {
    protected:
        std::wstring construct() const override {
            std::wstring buf;

            buf += L"ParserException";
            buf += L"\n\tError: ";
            buf += text;

            return buf;
        }
    public:
        ParserException(std::wstring text):
            FException(text)
        {}
    };
}
