//
// Created on 23.07.2021.
//
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать имя функции
         */
        class ReadName : public AnalyticBasic {
        public:
            explicit ReadName(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;

            /// Есть ли [force] среди ключевых слов функции
            bool areTokensIncludeForce();
        };
    }
}