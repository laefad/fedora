//
// Created by mi on 21.07.2021.
//

#ifndef FEDORA_FEXCEPTION_H
#define FEDORA_FEXCEPTION_H

#include <locale>
#include <codecvt>

namespace fedora {
    struct FException : public std::exception {
    private:
        std::string ws2s(const std::wstring& wstr){
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.to_bytes(wstr);
        }
    public:
        std::string s;

        FException(std::wstring ss) {
            s = ws2s(ss);
        }

        FException(std::string ss):s(ss){}

        ~FException() throw() {} // Updated
        const char *what() const throw() { return s.c_str(); }
    };
}
#endif //FEDORA_FEXCEPTION_H
