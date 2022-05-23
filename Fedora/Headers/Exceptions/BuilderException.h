#pragma once

#include "FException.h"

namespace fedora {
    class BuilderException : public FException {
    protected:
        std::u8string construct(
            std::u8string functionName,
            std::u8string text
        ) const {
            std::u8string buf;

            buf += u8"ContextBuilder Exception\n";
            buf += u8"\tFunction: ";
            buf += functionName;
            buf += u8"\n";
            buf += u8"\tError: ";
            buf += text;

            return buf;
        }

    public:
        explicit BuilderException(std::u8string text, std::u8string functionName) :
            FException(construct(functionName, text))
        {}
    };
}
