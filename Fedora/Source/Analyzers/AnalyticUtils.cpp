
#include "KeyWords.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {

        bool AnalyticUtils::isTokenAName(Token const& t) {
            return 
                !isTokenAKeyWord(t) &&
                !isTokenAString(t) &&
                !isTokenANumber(t) &&
                !isTokenABracket(t);
        }

        bool AnalyticUtils::isTokenAKeyWord(Token const& t) {
            for (auto const& key : KeyWords::getAllKeyWords()) {
                if (key == t)
                    return true;
            }
            return false;
        }

        // Числом является [-+]?[0-9]+.?[0-9]+
        // Поддержки +/- раньше не было, поэтому могут возникать ошибки, если код на них не рассчитан
        bool AnalyticUtils::isTokenANumber(Token const& t) {
            auto data = t.getData();
            bool hasDot = false;

            for (int i = 0, len = data.length(); i < len; ++i) {
                auto chr = data.at(i);
                
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

        bool AnalyticUtils::isTokenAString(Token const& t) {
            auto data = t.getData();
            return data.at(0) == L'\"' && data.at(data.length() - 1) == L'\"';
        }

        bool AnalyticUtils::isTokenAPreFunKeyWord(Token const& t) {
            for (auto const& key : KeyWords::getPreFunKeyWords()) {
                if (key == t)
                    return true;
            }
            return false;
        }

        bool AnalyticUtils::isTokenABracket(Token const& t) {
            auto data = t.getData();
            return t.isChar() && (
                data.at(0) == L'(' ||
                data.at(0) == L')' ||
                data.at(0) == L'[' ||
                data.at(0) == L']'
            );
        }

        bool AnalyticUtils::isTokenALeftSquareBracket(Token const& t) {
            return t.isChar(L'[');
        }

        bool AnalyticUtils::isTokenARightSquareBracket(Token const& t) {
            return t.isChar(L']');
        }

        bool AnalyticUtils::isTokenALeftCircleBracket(Token const& t) {
            return t.isChar(L'(');
        }

        bool AnalyticUtils::isTokenARightCircleBracket(Token const& t) {
            return t.isChar(L')');
        }
    }
}
