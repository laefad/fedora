//
// Created on 21.07.2021.
//
#pragma once

#include <locale>
#include <codecvt>
#include <utility>

namespace fedora {
    class StaticUtils {
    public:
        static const std::wstring ignoredSymbols;
        static const std::wstring delimiterSymbols;

        /// wstring to string
        static std::string ws2s(const std::wstring &wstr);

        /// string to wstring
        static std::wstring s2ws(const std::string &str);

        /// Является ли символ разделителем между токенами
        static bool isDelimiter(wchar_t wchr);

        /// Является ли символ пробельным
        static bool isIgnored(wchar_t wchr);

        /// Является ли символ -- символом перевода строки?
        static bool isNewLine(wchar_t wchr);

        /// Является ли символ -- кавычкой "?
        static bool isQuote(wchar_t wchr);

        /// Является ли символ -- символом комментария[#]?
        static bool isComment(wchar_t wchr);
    };
}
