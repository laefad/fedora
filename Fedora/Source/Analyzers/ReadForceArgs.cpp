//
// Created by mi on 23.07.2021.
//

#include <memory>
#include "Analyzers/ReadForceArgs.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadForceArgs::analyzeToken(Token &) {
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadForceArgs::getFileName() {
            return "ReadForceArgs.h";
        }
    }
}
