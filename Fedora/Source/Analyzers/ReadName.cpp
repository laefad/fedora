//
// Created on 23.07.2021.
//

#include <memory>
#include "Analyzers/ReadName.h"
#include "Analyzers/AnalyticUtils.h"
#include "Exceptions/AnalyzerException.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(fedora::Token &t) {
            if (!AnalyticUtils::isValidName(t.data))
                throwException(L"Expected a function name, but got a key word", "analyzeToken(Token&)");

            return std::shared_ptr<AnalyticBasic>();
        }

        void ReadName::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg,"ReadName.h",funcName);
        }
    }
}
