//
// Created on 21.07.2021.
//
#pragma once

#include <locale>
#include <codecvt>
#include <utility>

namespace fedora{
    class StaticUtils{
    public:
        /// wstring to string
        static std::string ws2s(const std::wstring& wstr){
            using convert_typeX = std::codecvt_utf8<wchar_t>;
            std::wstring_convert<convert_typeX, wchar_t> converterX;

            return converterX.to_bytes(wstr);
        }
        /// Является ли символ разделителем между докенами
        static bool isDelimiter(wchar_t &);
    };
}
