#include "Analyzers/AnalyticBasic.h"

namespace fedora::analytic {
    class ReadAfterReturnableFunName : public AnalyticBasic {
        std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const&, ContextBuilder&) override;

        std::u8string getClassFileName() override;
    };
}
