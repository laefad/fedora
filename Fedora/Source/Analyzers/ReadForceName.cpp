//
// Created on 12.08.2021.
//

#include "Analyzers/ReadForceName.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadForceName::analyzeToken(Token &, ContextBuilder &) {
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadForceName::getFileName() {
            return "ReadForceName.h";
        }
    }
}


