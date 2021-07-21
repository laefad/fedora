//
// Created on 21.07.2021.
//

#include <StaticUtils.h>
#include <iostream>

bool fedora::StaticUtils::isDelimiter(wchar_t & tmp) {
    // Символы, которые мы считаем разделителями на токены
    const std::wstring ignoredSymbols = L"()[]#";
    return ignoredSymbols.find(tmp) != std::wstring::npos;
}
