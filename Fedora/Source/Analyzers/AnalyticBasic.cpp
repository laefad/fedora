
#include "Exceptions/AnalyzerException.h"
#include "Analyzers/AnalyticBasic.h"
#include "Utils/Logger.h"

namespace fedora{
    namespace analytic{

        AnalyticBasic::AnalyticBasic(std::vector<Token> tokens): 
            tokens(std::move(tokens)) 
        {};

        std::vector<Token> &AnalyticBasic::getTokens()  {
            return tokens;
        }

        void AnalyticBasic::addToken(Token const& token) {
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
