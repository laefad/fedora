#include "Analyzers/AnalyzerStrategy.h"
#include <iostream>

bool fedora::AnalyzerStrategy::analyzeNext(fedora::Token &t) {
    std::wcout<<t.data<<std::endl;

    //analyticObj = analyticObj->analyzeToken(t);
    try {
        analyticObj = analyticObj->analyzeToken(t);
        return true;
    }catch(FException& e){
        std::cout<<"Error:"<<std::endl<<e.what();
        return false;
    }
}
