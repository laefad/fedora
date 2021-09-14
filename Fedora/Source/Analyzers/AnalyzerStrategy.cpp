#include "Analyzers/AnalyzerStrategy.h"
#include "Utils/Logger.h"

namespace fedora {
    bool AnalyzerStrategy::analyzeNext(parser::Token &t) {
        try {
            analyticObj = analyticObj->analyzeToken(t, contextBuilder);
            return true;
        } catch (FException &e) {
            // TODO Сделать вывод красного цвета (в консоли)
            Logger::logE(e.whatu8());
            return false;
        }
    }
}
