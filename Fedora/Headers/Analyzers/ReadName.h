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
        class ReadName:public AnalyticBasic{
        public:
            std::shared_ptr<AnalyticBasic> analyzeToken(Token&) override;
            void throwException(const std::wstring& msg, const std::string& funcName) override;
        };
    }
}