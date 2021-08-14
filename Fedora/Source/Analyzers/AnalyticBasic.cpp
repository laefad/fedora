
#include "Exceptions/AnalyzerException.h"
#include "Analyzers/AnalyticBasic.h"
#include "Utils/Logger.h"

namespace fedora {
    namespace analytic {

        void AnalyticBasic::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg, getClassFileName(), funcName);
        }

        void AnalyticBasic::throwException(const std::string &msg, const std::string &funcName) {
            throw AnalyzerException(msg, getClassFileName(), funcName);
        }

        void AnalyticBasic::log(const std::string &msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }

        void AnalyticBasic::log(const std::wstring &msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }
    }
}
