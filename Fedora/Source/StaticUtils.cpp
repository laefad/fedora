
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

    /// Символы, которые мы считаем разделителями на токены
    bool StaticUtils::isDelimiter(wchar_t & tmp) {
        // Раньше \n не было в разделителях. Он был в игнорируемых символах.
        // Однако, я перенёс его сюда, чтобы он не игнорировался, а читался и заносился в tokensHolder как пустой.
        // В сборке контекста он не участвует.
        const std::wstring delimiters = L"()[]#\n";
        return delimiters.find(tmp) != std::wstring::npos;
    }

}
