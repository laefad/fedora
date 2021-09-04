
#include "Exceptions/AnalyzerException.h"
#include "Analyzers/AnalyticBasic.h"

#include <utility>
#include "Utils/Logger.h"

namespace fedora {
    namespace analytic {

        void AnalyticBasic::throwException(std::wstring msg, std::wstring funcName) {
            throw AnalyzerException(std::move(msg), getClassFileName(), std::move(funcName));
        }

        void AnalyticBasic::log(const std::wstring& msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }
        
    }
}
