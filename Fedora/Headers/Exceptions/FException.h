#pragma once

#include <exception>
#include <string>
#include <utility>

#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    protected:
        std::u8string text;

    protected:
        virtual std::u8string construct() const;

    public:

        explicit FException(std::u8string s) noexcept(false);

        ~FException() noexcept override;

        const char *what() const noexcept override;

        // TODO to .cpp
        std::u8string whatu8() const {
            return text;
        }
    };
}
