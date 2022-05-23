#include "Exceptions/FException.h"

#include "Utils/Logger.h"

namespace fedora {

    FException::FException(std::u8string s) noexcept :
        u8strText(std::move(s)),
        strText(StaticUtils::u8s2s(u8strText))
    {}

    FException::~FException() noexcept = default;

    const char* FException::what() const noexcept {
        return strText.c_str();
    }

    std::u8string FException::whatu8() const noexcept {
        return u8strText;
    }
}
