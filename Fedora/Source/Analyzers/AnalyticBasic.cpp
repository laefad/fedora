
#include "Exceptions/AnalyzerException.h"
#include "Analyzers/AnalyticBasic.h"
#include "Utils/Logger.h"

namespace fedora {
    namespace analytic {

        void AnalyticBasic::throwException(std::wstring msg, std::wstring funcName) {
            throw AnalyzerException(msg, getClassFileName(), funcName);
        }

        void AnalyticBasic::log(std::wstring msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }
        
    }
}
