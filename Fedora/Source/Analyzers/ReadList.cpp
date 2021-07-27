//
// Created on 27.07.2021.
//

#include <Analyzers/ReadList.h>
#include <memory>

namespace fedora{
    namespace analytic{

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token &) {
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadList::getFileName() {
            return "ReadList.h";
        }
    }
}


