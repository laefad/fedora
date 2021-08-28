
#include "Exceptions/FException.h"

#include "Utils/Logger.h"

namespace fedora {
    std::wstring FException::construct() const {
        return text;
    }

    FException::FException(std::wstring s) noexcept(false):
        text(std::move(s))
    {}

    FException::~FException() noexcept = default;

    const char * FException::what() const noexcept {
        std::wstring wstr(construct());
        Logger::logE(wstr);
        return StaticUtils::ws2s(wstr).c_str();
    }
}