//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora {
    namespace analytic {
        /**
         * Класс чтения аргументов при объявлении функции
         */
        class ReadFunArgs : public AnalyticBasic {
        public:
            explicit ReadFunArgs(std::vector<Token> t) : AnalyticBasic(std::move(t)) {}

            std::shared_ptr<AnalyticBasic> analyzeToken(Token &) override;

            std::string getFileName() override;
        };
    }
}