#pragma once

#include <exception>
#include <string>
#include <utility>

namespace fedora {
    class FException : public std::exception {
    private:;
    protected:
        std::string text;
    public:

        explicit FException(std::string s) noexcept(false):
                text(std::move(s)) {}

        ~FException() noexcept override = default;

        // TODO Заменить text в этой переменной на функцию, которая будет переопределяться в child классах
        const char *what() const noexcept override { return text.c_str(); }
    };
}
