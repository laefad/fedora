//
// Created on 23.07.2021.
//

#include <memory>
#include "Analyzers/ReadForceArgs.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadForceArgs::analyzeToken(Token &t) {
            // TODO Сделать синглтон с настройками уровней дебаг вывода VERBOSE, WARNING, ERROR
            log("Class: "+getFileName(),fedora::settings::LOG_VERBOSE);
            log(L"Token: "+t.data,fedora::settings::LOG_VERBOSE);

            throwException(L"ForceArgs unimplemented", "");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadForceArgs::getFileName() {
            return "ReadForceArgs.h";
        }
    }
}
