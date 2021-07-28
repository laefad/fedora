//
// Created on 23.07.2021.
//

#include <KeyWords.h>
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        bool AnalyticUtils::isValidName(std::wstring &name) {
            const int checksNeed = 4;
            int checks = 0;
            if (!isValueAKeyWord(name))
                ++checks;
            if (!isValueAString(name))
                ++checks;
            if (!isdigit(name.at(0)))
                ++checks;
            if (!isBracket(name))
                ++checks;
            return checks == checksNeed;
        }

        bool AnalyticUtils::isValueAKeyWord(std::wstring &name) {
            bool isKey = false;
            for (auto &key :  KeyWords::getAllKeyWords()) {
                if (key.data == name)
                    isKey = true;
            }
            return isKey;
        }

        bool AnalyticUtils::isValueANumber(std::wstring &name) {
            bool hasDot = false; // Имеет ли число точку в записи (если число дробное)
            bool f = true; // Все ли символы токена корректны

            // TODO Оптимизировать if-ы
            // Пройдёмся по всем символам и проверим, все ли онц цифры.
            // Также позволено поставить точку в середине числа, чтобы сделать дробь
            for (int i=0;i<name.length();++i) {
                wchar_t chr = name.at(i);
                if (!isdigit(chr) && !(chr == L'.' && i!=0 && i!=name.length()-1 && !hasDot))
                    f = false;
                if (chr == L'.' && i!=0 && i!=name.length()-1 && !hasDot)
                    hasDot = true;
            }
            return f;
        }

        bool AnalyticUtils::isValueAString(std::wstring &name) {
            return name.at(0) == L'\"' && name.at(name.length() - 1) == L'\"';
        }

        bool AnalyticUtils::isTokenAPreFunKeyWord(std::wstring &data) {
            bool res = false;
            for (auto &key : KeyWords::getPreFunKeyWords()) {
                if (key.data == data)
                    res = true;
            }
            return res;
        }

        bool AnalyticUtils::isBracket(std::wstring & n) {
            return n.length() == 1 && (n.at(0) == L'(' || n.at(0) == L')' || n.at(0) == L'['|| n.at(0) == L']');
        }
    }
}