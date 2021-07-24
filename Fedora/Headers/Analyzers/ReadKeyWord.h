//
// Created on 23.07.2021.
//
#pragma once
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Прочитать ключевые слова при объявлении функции
         */
        class ReadKeyWord:AnalyticBasic{
        public:
            bool analyzeToken(Token&) override;
        };
    }
}
