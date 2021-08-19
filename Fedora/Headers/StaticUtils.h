#pragma once

#include <locale>
#include <codecvt>
#include <utility>

namespace fedora {
    class StaticUtils {
    public:
        /// wstring to string
        static std::string ws2s(const std::wstring &wstr);

        /// string to wstring
        static std::wstring s2ws(const std::string &str);
    };
}
