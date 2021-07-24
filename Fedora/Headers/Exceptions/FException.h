//
// Created on 21.07.2021.
//

#pragma once
#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    protected:
        std::string text;
    public:
        explicit FException(const std::wstring& ss) noexcept(false){
            text = StaticUtils::ws2s(ss);
        }

        explicit FException(std::string ss) noexcept(false) : text(std::move(ss)){}

        ~FException() noexcept override = default;
        const char *what() const noexcept override { return text.c_str(); }
    };
}
