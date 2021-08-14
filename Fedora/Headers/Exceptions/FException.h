#pragma once

#include "Utils/TokensHolder.h"
#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    private:;
    protected:
        std::string text;
    public:
        explicit FException(std::wstring const &ws) noexcept(false):
                text(StaticUtils::ws2s(ws)) {}

        explicit FException(std::string const &s) noexcept(false):
                text(std::move(s)) {}

        ~FException() noexcept override = default;

        // TODO Заменить text в этой переменной на функцию, которая будет переопределяться в child классах
        const char *what() const noexcept override { return text.c_str(); }
    };
}
