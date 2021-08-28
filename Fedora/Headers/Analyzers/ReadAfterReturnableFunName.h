#include "Analyzers/AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        class ReadAfterReturnableFunName : public AnalyticBasic {
            std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const &, ContextBuilder &) override;

            std::wstring getClassFileName() override;
        };
    }
}
