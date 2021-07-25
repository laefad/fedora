//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "Token.h"

namespace fedora{
    namespace analytic {
        /// Базовый класс анализатора токена
        class AnalyticBasic {
        public:
            virtual std::shared_ptr<AnalyticBasic> analyzeToken(Token&)=0;
            virtual void throwException(const std::wstring& msg, const std::string& funcName)=0;
        };
    }
}
