//
// Created on 23.07.2021.
//

#include "Analyzers/ReadResult.h"
namespace fedora{
    namespace analytic{
        std::shared_ptr<AnalyticBasic> ReadResult::analyzeToken(Token &) {
            return std::shared_ptr<AnalyticBasic>();
        }

        void ReadResult::throwException(const std::wstring &msg, const std::string &funcName) {

        }
    }
}
