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
            explicit ReadKeyWord(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            /// Определение родительского метода анализа токена
            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            /// Переопределение метода выброса ошибки
            void throwException(const std::wstring &msg, const std::string &funcName) override;
        };
    }
}
