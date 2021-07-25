//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Класс чтения аргументов при объявлении функции
         */
        class ReadFunArgs:public AnalyticBasic{
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token&) override;
        };
    }
}