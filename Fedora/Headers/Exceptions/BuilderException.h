#pragma once

#include "FException.h"
#include "StaticUtils.h"

namespace fedora {
    class BuilderException : public FException {
    protected:
        std::wstring functionName;

    protected:
        std::wstring construct() const override {
            std::wstring buf;

            buf += L"ContextBuilder Exception\n";
            buf += L"\tFunction: ";
            buf += functionName;
            buf += L"\n";
            buf += L"\tError: ";
            buf += text;

            return buf;
        }

    public:
        explicit BuilderException(std::wstring text, std::wstring functionName) :
                FException(text),
                functionName(functionName) {}
    };
}
