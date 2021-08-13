
#include "KeyWords.h"
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {

        ReadName::ReadName(std::vector<Token> vec): 
            AnalyticBasic(std::move(vec))
        {}

        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(Token const& t) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (!AnalyticUtils::isTokenAName(t))
                throwException(L"Expected a function name, but founded name is invalid. Token = " + t.getData(),
                               "analyzeToken(Token&) <- AnalyticUtils::isValidName(std::wstring&)");

            // Если [force] есть среди ключевых слов, считать аргументы для вызова функции
            if (areTokensIncludeForce()) {
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
            }
                // Иначе считать имена аргументов для объявления функции
            else {
                return std::make_shared<ReadFunArgs>(std::vector<Token>());
            }
        }


        bool ReadName::areTokensIncludeForce() {
            bool hasForce = false;
            for (auto &token:getTokens()) {
                if (token == force)
                    hasForce = true;
            }
            return hasForce;
        }

        std::string ReadName::getFileName() {
            return "ReadName.h";
        }
    }
}
