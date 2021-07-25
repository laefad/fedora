//
// Created on 23.07.2021.
//
#pragma once
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Класс чтения аргументов для force вызова функции
         * @see Keywords.force
         */
        class ReadForceArgs:public AnalyticBasic{
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token&) override;
        };
    }
}