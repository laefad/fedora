//
// Created on 21.07.2021.
//

#include <StaticUtils.h>
#include <iostream>

/// Символы, которые мы считаем разделителями на токены
bool fedora::StaticUtils::isDelimiter(wchar_t & tmp) {

    // Раньше \n не было в разделителях. Он был в игнорируемых символах.
    // Однако, я перенёс его сюда, чтобы он не игнорировался, а читался и заносился в tokensHolder как пустой.
    // В сборке контекста он не участвует.
    const std::wstring delimiters = L"()[]#\n";
    return delimiters.find(tmp) != std::wstring::npos;
}
