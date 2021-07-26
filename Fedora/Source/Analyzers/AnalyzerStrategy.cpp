#include "Analyzers/AnalyzerStrategy.h"
#include <iostream>

bool fedora::AnalyzerStrategy::analyzeNext(fedora::Token &t) {
    std::wcout<<t.data<<std::endl;

    analyticObj = analyticObj->analyzeToken(t);
}
