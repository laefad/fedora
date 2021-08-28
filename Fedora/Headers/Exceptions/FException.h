#pragma once

#include <exception>
#include <string>
#include <utility>

#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    protected:
        std::wstring text;

    protected:
        virtual std::wstring construct() const;
    public:

        explicit FException(std::wstring s) noexcept(false);

        ~FException() noexcept override;

        const char * what() const noexcept override;
    };
}
