#pragma once

#include <string>

namespace fedora {
    class StaticUtils {
    public:
        /// u8string to string
        static std::string u8s2s(const std::u8string&);

        /// string to u8string
        static std::u8string s2u8s(const std::string&);

        /// u8string to double
        static double u8s2d(const std::u8string&);

        /// double to u8string 
        static std::u8string d2u8s(double);

        /// string to double
        static double s2d(const std::string&);

        /// u8sring to int
        static int u8s2i(const std::u8string&);

        /// int to u8string
        static std::u8string i2u8s(int);
    };
}
