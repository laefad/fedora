//
// Created on 23.07.2021.
//
#pragma once

#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Класс чтения аргументов для force вызова функции
         * @see Keywords.force
         */
        class ReadForceArgs : public AnalyticBasic {
        public:
            explicit ReadForceArgs(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;
        };
    }
}