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

            /// Переопределение метода выброса ошибки
            void throwException(const std::wstring &msg, const std::string &funcName) override;

            /// Является ли токен открытой квадратной скобкой ("[")
            static bool isTokenALeftSquareBracket(std::wstring&);
        };
    }
}