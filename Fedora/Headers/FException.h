//
// Created on 21.07.2021.
//

#pragma once
#include <locale>
#include <codecvt>
#include <utility>

namespace fedora {
    struct FException : public std::exception {
    private:
        static std::string ws2s(const std::wstring& wstr){
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.to_bytes(wstr);
        }
    public:
        std::string s;

        explicit FException(const std::wstring& ss) {
            s = ws2s(ss);
        }

        explicit FException(std::string ss):s(std::move(ss)){}

        ~FException() noexcept override = default;
        const char *what() const noexcept override { return s.c_str(); }
    };
}
