#pragma once

#include <locale>
#include <codecvt>
#include <utility>

namespace fedora {
    class StaticUtils {
    public:
        /// wstring to string
        static std::string u8s2s(const std::u8string &);

        /// string to wstring
        static std::u8string s2u8s(const std::string &);

        /// wstring to double
        static double u8s2d(const std::u8string &);

        /// const string to double
        static double s2d(const std::string &);
    };
}
