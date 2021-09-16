#pragma once

#include "FException.h"

namespace fedora {
    class ParserException : public FException {
    protected:
        std::u8string construct(std::u8string text) const {
            std::u8string buf;

            buf += u8"ParserException";
            buf += u8"\n\tError: ";
            buf += text;

            return buf;
        }

    public:
        ParserException(std::u8string text) :
                FException(construct(text)) {}
    };
}
