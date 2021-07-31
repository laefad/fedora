//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать возвращаемое значение функции
         */
        class ReadResult : public AnalyticBasic {
        public:
            explicit ReadResult(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;

        };
    }
}