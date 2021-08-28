#pragma once

#include <utility>
#include <sstream>

#include "FException.h"

namespace fedora {
    class SettingsException: public FException{
    protected:
        // TODO Конкретизировать ошибку
        std::wstring construct() const override {
            std::wstringstream buf;

            buf << L"SettingsException\n"
                << L"\tError: "
                << text;

            return buf.str();
        }
    public:
        explicit SettingsException(std::wstring text):
            FException(text) 
        {}
    };
}
