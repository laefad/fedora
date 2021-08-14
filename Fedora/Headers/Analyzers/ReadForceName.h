//
// Created on 12.08.2021.
//
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Read forceCall name
         *
         * @example
         * force main() # "main" will be read via this class method [analyzeToken] #
         */
        class ReadForceName : public AnalyticBasic {
        public:
            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &, ContextBuilder &) override;

            std::string getClassFileName() override;

        };
    }
}