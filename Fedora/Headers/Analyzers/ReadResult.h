#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать возвращаемое значение функции
         */
        class ReadResult : public AnalyticBasic {
        public:
            explicit ReadResult(std::vector<Token>);

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const&) override;

            std::string getFileName() override;

        };
    }
}
