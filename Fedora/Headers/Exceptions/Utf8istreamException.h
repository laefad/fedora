#pragma once

#include "FException.h"

namespace fedora {
    class Utf8istreamException : public FException {
    protected:
        std::u8string construct(
            std::u8string text
        ) const {
            std::u8string buf;

            buf += u8"Utf8istreamError\n";
            buf += u8"\tError: ";
            buf += text;

            return buf;
        }

    public:
        explicit Utf8istreamException(std::u8string text) :
            FException(std::move(construct(text))) {}
    };
}
