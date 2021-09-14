#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать возвращаемое значение функции
         */
        class ReadResult : public AnalyticBasic {
        public:
            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(parser::Token const &, ContextBuilder &) override;

            std::u8string getClassFileName() override;
        };
    }
}
