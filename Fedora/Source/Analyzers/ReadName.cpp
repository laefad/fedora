//
// Created on 23.07.2021.
//

#include <memory>
#include <KeyWords.h>
#include <Analyzers/ReadForceArgs.h>
#include <Analyzers/ReadFunArgs.h>
#include "Analyzers/ReadName.h"
#include "Analyzers/AnalyticUtils.h"
#include "Exceptions/AnalyzerException.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(fedora::Token &t, ContextBuilder &b) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (!AnalyticUtils::isValidName(t.getData()))
                throwException(L"Expected a function name, but founded name is invalid. Token = " + t.getData(),
                               "analyzeToken(Token&) <- AnalyticUtils::isValidName(std::wstring&)");

            // Если [force] есть среди ключевых слов, считать аргументы для вызова функции
            if (b.isCurrentFunctionForced()) {
                return std::make_shared<ReadForceArgs>();
            }
                // Иначе считать имена аргументов для объявления функции
            else {
                return std::make_shared<ReadFunArgs>();
            }
        }


//        bool ReadName::areTokensIncludeForce() {
//            bool hasForce = false;
//            for (auto &token:getTokens()) {
//                if (token == force)
//                    hasForce = true;
//            }
//            return hasForce;
//        }

        std::string ReadName::getFileName() {
            return "ReadName.h";
        }
    }
}
