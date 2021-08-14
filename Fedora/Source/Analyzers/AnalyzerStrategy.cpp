#include "Analyzers/AnalyzerStrategy.h"
#include "Utils/Logger.h"

bool fedora::AnalyzerStrategy::analyzeNext(fedora::Token &t) {
    try {
        analyticObj = analyticObj->analyzeToken(t, contextBuilder);
        return true;
    } catch (FException &e) {
        // TODO Сделать вывод красного цвета (в консоли)
        Logger::logE(e.what());
        return false;
    }
}
