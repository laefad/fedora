//
// Created on 23.07.2021.
//

#include "Analyzers/ReadFunArgs.h"
namespace fedora {
    namespace analytic {
        std::shared_ptr<fedora::analytic::AnalyticBasic> fedora::analytic::ReadFunArgs::analyzeToken(fedora::Token &) {
            return std::shared_ptr<AnalyticBasic>();
        }

        void fedora::analytic::ReadFunArgs::throwException(const std::wstring &msg, const std::string &funcName) {

        }
    }
}
