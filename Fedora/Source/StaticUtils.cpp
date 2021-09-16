
#include <StaticUtils.h>
#include <string>

namespace fedora {

    std::string StaticUtils::u8s2s(const std::u8string &u8str) {
        return std::string(u8str.begin(), u8str.end());
    }

    std::u8string StaticUtils::s2u8s(const std::string &str) {
        return std::u8string(str.begin(), str.end());
    }

    double StaticUtils::u8s2d(const std::u8string & u8str) {
        return s2d(u8s2s(u8str));
    }

    std::u8string StaticUtils::d2u8s(double value) {
        return s2u8s(std::to_string(value));
    }

    double StaticUtils::s2d(const std::string &str) {
        char * endPtr;
        const char * stPtr = str.c_str();
        double a = std::strtod(stPtr, &endPtr);
        return a;
    }

    int StaticUtils::u8s2i(const std::u8string &u8str) {
        return std::stoi(u8s2s(u8str));
    }

    std::u8string StaticUtils::i2u8s(int value) {
        return s2u8s(std::to_string(value));
    }
}
