//
// Created on 23.07.2021.
//
#pragma once
#include "Token.h"

namespace fedora{
    namespace analytic {
        /// Базовый класс анализатора токена
        class AnalyticBasic {
        public:
            virtual bool analyzeToken(Token&)=0;
        };
    }
}
