#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {

        /**
         * Read function arg names
         *
         * @example case 1: Has args
         * let fun arg1 arg2 = ...
         *
         * @example case 2: Does not has args
         * let fun = ...
         */
        class ReadFunArgs : public AnalyticBasic {
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const &, ContextBuilder &) override;

            std::string getClassFileName() override;
        };
    }
}
