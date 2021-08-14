
#include <StaticUtils.h>

namespace fedora {

    const std::wstring StaticUtils::ignoredSymbols = L"\n\t\r \377";
    const std::wstring StaticUtils::delimiterSymbols = L"()[]=";

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

    bool StaticUtils::isDelimiter(wchar_t tmp) {
        //const std::wstring delimiters = L"()[]#\n";
        return StaticUtils::delimiterSymbols.find(tmp) != std::wstring::npos;
    }

    bool StaticUtils::isNewLine(wchar_t tmp) {
        return tmp == L'\n';
    }

    bool StaticUtils::isQuote(wchar_t tmp) {
        return tmp == L'\"';
    }

    bool StaticUtils::isComment(wchar_t tmp) {
        return tmp == L'#';
    }

    bool StaticUtils::isIgnored(wchar_t tmp) {
        //const std::wstring ignoredSymbols = L"\n\t\r \377"; // Возможно, \377 - это символ окончания файла 
        return StaticUtils::ignoredSymbols.find(tmp) != std::wstring::npos;
    }

}
