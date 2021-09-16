#pragma once

#include <exception>
#include <string>

#include "StaticUtils.h"

namespace fedora {
    class FException : public std::exception {
    protected:
        std::u8string u8strText;
        std::string strText;
        
    public:

        explicit FException(std::u8string s) noexcept;

        virtual ~FException() noexcept override;

        virtual const char *what() const noexcept override;

        std::u8string whatu8() const noexcept;
    };
}
