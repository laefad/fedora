//
// Created on 23.07.2021.
//
#pragma once
#include "AnalyticBasic.h"

namespace fedora{
    namespace analytic{
        class ReadFunArgs:public AnalyticBasic{
        public:
            bool analyzeToken(Token&) override;
        };
    }
}