//
// Created on 23.07.2021.
//
#pragma once
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Прочитать имя функции
         */
        class ReadName:AnalyticBasic{
        public:
            bool analyzeToken(Token&) override;
        };
    }
}