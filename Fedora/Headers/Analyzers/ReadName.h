#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать имя функции
         */
        class ReadName : public AnalyticBasic {
        public:
            explicit ReadName(std::vector<Token>);

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const&) override;

            std::string getFileName() override;

            /// Есть ли [force] среди ключевых слов функции
            bool areTokensIncludeForce();
        };
    }
}
