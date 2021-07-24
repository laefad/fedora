//
// Created on 23.07.2021.
//
#pragma once
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Прочитать возвращаемое значение функции
         */
        class ReadResult:AnalyticBasic{
        public:
            bool analyzeToken(Token&) override;
        };
    }
}