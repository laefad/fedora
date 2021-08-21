#pragma once

#include <locale>
#include <codecvt>
#include <utility>

#include "Exceptions/FException.h"

namespace fedora {
    class StaticUtils {
    public:
        /// wstring to string
        static std::string ws2s(const std::wstring &);

        /// string to wstring
        static std::wstring s2ws(const std::string &);

        /// wstring to double
        static double ws2d(const std::wstring &, const FException&);

        /// const string to double
        static double s2d(const std::string &, const FException&);
    };
}
