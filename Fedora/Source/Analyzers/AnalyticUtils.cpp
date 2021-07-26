//
// Created on 23.07.2021.
//

#include <KeyWords.h>
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        bool AnalyticUtils::isValidName(std::wstring &name) {
            const int checksNeed = 3;
            int checks = 0;
            if (!isValueAKeyWord(name))
                ++checks;
            if (!isValueAString(name))
                ++checks;
            if (!isdigit(name.at(0)))
                ++checks;
            return checks == checksNeed;
        }

        bool AnalyticUtils::isValueAKeyWord(std::wstring &name) {
            bool isKey = false;
            for (auto& key :  KeyWords::getAllKeyWords()){
                if (key.data == name)
                    isKey = true;
            }
            return isKey;
        }

        bool AnalyticUtils::isValueANumber(std::wstring &name) {
            bool f = true;
            for (auto &chr :name) {
                if (!isdigit(chr))
                    f = false;
            }
            return f;
        }

        bool AnalyticUtils::isValueAString(std::wstring & name) {
            return name.at(0) == L'\"' && name.at(name.length() - 1) == L'\"';
        }

        bool AnalyticUtils::isTokenAPreFunKeyWord(std::wstring & data) {
            bool res = false;
            for (auto & key : KeyWords::getPreFunKeyWords()){
                if (key.data == data)
                    res = true;
            }
            return res;
        }
    }
}