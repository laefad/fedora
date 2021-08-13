#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadKeyWord : public AnalyticBasic {
        public:
            explicit ReadKeyWord(std::vector<Token> t);

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token const&) override;

            std::string getFileName() override;
        };
    }
}
