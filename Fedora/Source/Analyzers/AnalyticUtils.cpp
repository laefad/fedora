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
        bool AnalyticUtils::isValidName(Token &t) {
            return
                    !isValueAKeyWord(t) &&
                    !isValueAString(t) &&
                    !isdigit(t.getData().at(0)) &&
                    !isBracket(t);
        }

        bool AnalyticUtils::isValueAKeyWord(Token &t) {
            std::wstring name = t.getData();
            for (auto &key : KeyWords::getAllKeyWords()) {
                if (key.getData() == name)
                    return true;
            }
            return false;
        }

        // Числом является [-+]?[0-9]+.?[0-9]+
        // Поддержки +/- раньше не было, поэтому могут возникать ошибки, если код на них не рассчитан
        bool AnalyticUtils::isValueANumber(Token &t) {
            std::wstring name = t.getData();
            bool hasDot = false;

            for (int i = 0, len = name.length(); i < len; ++i) {
                const wchar_t chr = name.at(i);

                if (isdigit(chr))
                    continue;

                if (chr != L'.') {
                    if (i != 0 || (chr != L'+' && chr != L'-'))
                        return false;
                } else if (hasDot || i == 0 || i == len - 1)
                    return false;
                else
                    hasDot = true;
            }
            return true;
        }

        bool AnalyticUtils::isValueAString(Token &t) {
            std::wstring name = t.getData();
            return name.at(0) == L'\"' && name.at(name.length() - 1) == L'\"';
        }

        bool AnalyticUtils::isTokenAPreFunKeyWord(Token &t) {
            std::wstring name = t.getData();
            bool res = false;
            for (auto &key : KeyWords::getPreFunKeyWords()) {
                if (key.getData() == name)
                    res = true;
            }
            return res;
        }

        bool AnalyticUtils::isBracket(Token &t) {
            std::wstring n = t.getData();
            return n.length() == 1 && (n.at(0) == L'(' || n.at(0) == L')' || n.at(0) == L'[' || n.at(0) == L']');
        }

        bool AnalyticUtils::isTokenALeftSquareBracket(Token &t) {
            std::wstring data = t.getData();
            return data.length() == 1 && data.at(0) == L'[';
        }

        bool AnalyticUtils::isTokenARightSquareBracket(Token &t) {
            std::wstring data = t.getData();
            return data.length() == 1 && data.at(0) == L']';
        }

        bool AnalyticUtils::isTokenALeftCircleBracket(Token &t) {
            std::wstring data = t.getData();
            return data.length() == 1 && data.at(0) == L'(';
        }

        bool AnalyticUtils::isTokenARightCircleBracket(Token &t) {
            std::wstring data = t.getData();
            return data.length() == 1 && data.at(0) == L')';
        }
    }
}