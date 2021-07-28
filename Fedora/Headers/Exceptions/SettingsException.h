//
// Created on 28.07.2021.
//

#pragma once

#include <utility>

#include "FException.h"

namespace fedora {

    class SettingsException: public FException{

    public:
        explicit SettingsException(std::string s):FException(std::move(s)){
            // TODO Изменить text на SettingsException...
        }

        //const char *what() const noexcept override { return text.c_str(); }
    };
}
