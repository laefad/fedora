#pragma once

#include <utility>

#include "FException.h"

namespace fedora {
    class SettingsException : public FException {
    protected:
        // TODO Конкретизировать ошибку
        std::u8string construct() const override {
            std::u8string buf;

            buf += u8"SettingsException\n";
            buf += u8"\tError: ";
            buf += text;

            return buf;
        }

    public:
        explicit SettingsException(std::u8string text) :
                FException(std::move(text)) {}
    };
}
