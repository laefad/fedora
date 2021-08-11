//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include <utility>
#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadKeyWord : public AnalyticBasic {
        public:
            ReadKeyWord() = default;

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &, ContextBuilder &) override;

            std::string getFileName() override;
        };
    }
}
