//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        /**
         * Прочитать возвращаемое значение функции
         */
        class ReadResult:AnalyticBasic{
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token&) override;
        };
    }
}