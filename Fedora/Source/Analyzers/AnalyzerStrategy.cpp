#include "Analyzers/AnalyzerStrategy.h"
#include <iostream>

bool fedora::AnalyzerStrategy::analyzeNext(fedora::Token &t) {
    try {
        analyticObj = analyticObj->analyzeToken(t);
        return true;
    }catch(FException& e){
        // TODO Сделать вывод красного цвета (в консоли)
        // TODO У НАС ЛОГГЕР ЕСТЬ
        std::cout<<"Error:"<<std::endl<<e.what();
        return false;
    }
}
