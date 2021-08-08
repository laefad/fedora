//
// Created on 23.07.2021.
//

#include <KeyWords.h>
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {

        // TODO у нас вроде были запрещены скобочки посреди имени ?? 
        // имя f(x) пройдет же проверку 
        // или это где-то до обрабатывается?
        bool AnalyticUtils::isValidName(std::wstring &name) {
            return 
                !isValueAKeyWord(name) &&
                !isValueAString(name) &&
                !isdigit(name.at(0)) &&
                !isBracket(name);
        }

        bool AnalyticUtils::isValueAKeyWord(std::wstring &name) {
            for (auto &key : KeyWords::getAllKeyWords()) {
                if (key.getData() == name)
                    return true;
            }
            return false;
        }

        // Числом является [-+]?[0-9]+.?[0-9]+
        // Поддержки +/- раньше не было, поэтому могут возникать ошибки, если код на них не рассчитан
        bool AnalyticUtils::isValueANumber(std::wstring & name) {
            bool hasDot = false;

            for (int i = 0, len = name.length(); i < len; ++i) {
                const wchar_t chr = name.at(i);
                
                if (isdigit(chr)) 
                    continue;

                if (chr != L'.') {
                    if (i != 0 || (chr != L'+' && chr != L'-')) 
                    return false;
                } else 
                    if (hasDot || i == 0 || i == len - 1)
                        return false;
                    else 
                        hasDot = true;
            }
            return true;
        }

        bool AnalyticUtils::isValueAString(std::wstring &name) {
            return name.at(0) == L'\"' && name.at(name.length() - 1) == L'\"';
        }

        bool AnalyticUtils::isTokenAPreFunKeyWord(std::wstring &data) {
            bool res = false;
            for (auto &key : KeyWords::getPreFunKeyWords()) {
                if (key.getData() == data)
                    res = true;
            }
            return res;
        }

        bool AnalyticUtils::isBracket(std::wstring & n) {
            return n.length() == 1 && (n.at(0) == L'(' || n.at(0) == L')' || n.at(0) == L'['|| n.at(0) == L']');
        }

        bool AnalyticUtils::isTokenALeftSquareBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L'[';
        }

        bool AnalyticUtils::isTokenARightSquareBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L']';
        }

        bool AnalyticUtils::isTokenALeftCircleBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L'(';
        }

        bool AnalyticUtils::isTokenARightCircleBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L')';
        }
    }
}