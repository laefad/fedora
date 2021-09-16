#pragma once

#include "FException.h"

namespace fedora {
    class SettingsException : public FException {
    protected:
        // TODO Конкретизировать ошибку
        std::u8string construct(std::u8string text) const {
            std::u8string buf;

            buf += u8"SettingsException\n";
            buf += u8"\tError: ";
            buf += text;

            return buf;
        }

    public:
        explicit SettingsException(std::u8string text) :
                FException(std::move(construct(text))) {}
    };
}
