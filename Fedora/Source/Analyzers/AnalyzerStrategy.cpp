#include <regex>

#include "Analyzers/AnalyzerStrategy.h"

#include "Utils/Logger.h"

namespace fedora {
    bool AnalyzerStrategy::analyzeNext(parser::Token& t) {
        try {
            parser::Token t1 = makeAnalizableToken(t);
            analyticObj = analyticObj->analyzeToken(t1, contextBuilder);
            return true;
        } catch (FException& e) {
            // TODO Сделать вывод красного цвета (в консоли)
            Logger::logE(e.whatu8());
            return false;
        }
    }

    parser::Token AnalyzerStrategy::makeAnalizableToken(parser::Token& t) {
        if (t.getType() == parser::TokenType::String) {
            return parser::Token(
                t.getData().substr(1, t.getData().size() - 2), 
                t.getLine(), 
                t.getType()
            );
        } else {
            return t;
        }
    }
}
