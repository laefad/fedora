
#include <StaticUtils.h>

namespace fedora {

     std::string StaticUtils::ws2s(const std::wstring &wstr) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.to_bytes(wstr);
    }

    std::wstring StaticUtils::s2ws(const std::string &str) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.from_bytes(str);
    }

    double StaticUtils::ws2d(const std::wstring & ws, const FException &e) {
        return s2d(ws2s(ws), e);
    }


    double StaticUtils::s2d(const std::string &str, const FException &e) {
         char * endPtr;
         const char * stPtr = str.c_str();
         double a = std::strtod(stPtr, &endPtr);
         if (stPtr != endPtr){
             // everything is okay
         }else{
             throw e;
         }
        return a;
    }
}
