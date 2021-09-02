#pragma once

#include "FException.h"

namespace fedora {
    class SettingsException: public FException{
    protected:
        // TODO Конкретизировать ошибку
        std::wstring construct() const override {
            std::wstring buf;

            buf += L"SettingsException\n";
            buf += L"\tError: ";
            buf += text;

            return buf;
        }
    public:
        explicit SettingsException(std::wstring text):
            FException(text) 
        {}
    };
}
