//
// Created on 31.07.2021.
//

#include "Analyzers/ReadAfterListEnd.h"

namespace fedora{
    namespace analytic{

        std::shared_ptr<AnalyticBasic> ReadAfterListEnd::analyzeToken(Token &) {
            throwException(L"Unimplemented","");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadAfterListEnd::getFileName() {
            return "ReadAfterListEnd.h";
        }
    }
}

