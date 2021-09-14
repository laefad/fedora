
#include <StaticUtils.h>
#include <string>

namespace fedora {

    std::string StaticUtils::u8s2s(const std::u8string &u8str) {
        return std::string(u8str.begin(), u8str.end());
    }

    std::u8string StaticUtils::s2u8s(const std::string &str) {
        //TODO !important test conversion 
        return std::u8string(str.begin(), str.end());
    }

    double StaticUtils::u8s2d(const std::u8string & ws) {
        return s2d(u8s2s(ws));
    }

    double StaticUtils::s2d(const std::string &str) {
        char * endPtr;
        const char * stPtr = str.c_str();
        double a = std::strtod(stPtr, &endPtr);
        return a;
    }
}
