#pragma once

#include "FException.h"

namespace fedora {
    class ParserException : public FException {
    protected:
        std::wstring construct() const override {
            std::wstringstream buf;

            buf << L"ParserException"
                << L"\n\tError: " 
                << text;

            return buf.str();
        }
    public:
        ParserException(std::wstring text):
            FException(text)
        {}
    };
}
