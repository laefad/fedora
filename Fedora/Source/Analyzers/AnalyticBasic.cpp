#include <utility>

#include "Exceptions/AnalyzerException.h"

#include "Analyzers/AnalyticBasic.h"

#include "Utils/Logger.h"

namespace fedora::analytic {
    void AnalyticBasic::throwException(
        std::u8string msg, 
        std::u8string funcName
    ) {
        throw AnalyzerException(std::move(msg), getClassFileName(), std::move(funcName));
    }

    void AnalyticBasic::log(
        const std::u8string& msg, 
        fedora::settings::LogLevel level
    ) {
        Logger::log(msg, level);
    }
}
