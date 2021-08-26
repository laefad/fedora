//
// Created on 26.08.2021.
//

#include "Analyzers/AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        class ReadAfterReturnableFunName : public AnalyticBasic {
            std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;
        }
    }
}