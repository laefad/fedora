#include "Analyzers/AnalyzerStrategy.h"
#include <iostream>

bool fedora::AnalyzerStrategy::analyzeNext(fedora::Token &t) {
    try {
        analyticObj = analyticObj->analyzeToken(t);
        return true;
    }catch(FException& e){
        std::cout<<"Error:"<<std::endl<<e.what();
        return false;
    }
}
