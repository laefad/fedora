//
// Created on 23.07.2021.
//

#include <Analyzers/ReadName.h>
#include <Exceptions/AnalyzerException.h>
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(Token &t) {
            if (AnalyticUtils::isTokenAPreFunKeyWord(t.data))
                return std::make_shared<ReadName>();
            else
                throwException(L"Expected a pre-function key word, but got token.data = "+t.data, "analyzeToken(Token &)");
        }

        void ReadKeyWord::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg,"ReadKeyWord.h",funcName);
        }
    }
}
