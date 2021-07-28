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
        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(fedora::Token &t) {
            std::cout<<"Class: "<<getFileName()<<std::endl;
            std::wcout<<L"Token: "<<t.data<<std::endl;

            if (!AnalyticUtils::isValidName(t.data))
                throwException(L"Expected a function name, but founded name is invalid. Token = " + t.data,
                               "analyzeToken(Token&)");

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
