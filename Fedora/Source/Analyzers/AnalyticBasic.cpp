//
// Created on 27.07.2021.
//

#include <Exceptions/AnalyzerException.h>
#include "Analyzers/AnalyticBasic.h"
#include "Utils/Logger.h"

namespace fedora{
    namespace analytic{

        std::vector<Token> &AnalyticBasic::getTokens()  {
            return tokens;
        }

        void AnalyticBasic::addToken(const Token &token) {
            tokens.push_back(token);
        }

        void AnalyticBasic::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg, getFileName(), funcName);
        }

        void AnalyticBasic::log(const std::string& msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }

        void AnalyticBasic::log(const std::wstring &msg, fedora::settings::LogLevel level) {
            Logger::log(msg, level);
        }
    }
}
