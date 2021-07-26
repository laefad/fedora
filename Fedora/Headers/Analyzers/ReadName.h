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
            // Этот класс отработает 1 раз, ему не нужна ссылка на себя
            explicit ReadName(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            /// Переопределение метода выброса ошибки
            void throwException(const std::wstring &msg, const std::string &funcName) override;

            /// Есть ли [force] среди ключевых слов функции
            bool areTokensIncludeForce();
        };
    }
}