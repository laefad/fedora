
#include "Exceptions/FException.h"

#include "Utils/Logger.h"

namespace fedora {
    std::u8string FException::construct() const {
        return text;
    }

    FException::FException(std::u8string s) noexcept(false):
        text(std::move(s))
    {}

    FException::~FException() noexcept = default;

    const char * FException::what() const noexcept {
        std::u8string wstr(construct());
        Logger::logE(wstr);
        return StaticUtils::u8s2s(wstr).c_str();
    }
}