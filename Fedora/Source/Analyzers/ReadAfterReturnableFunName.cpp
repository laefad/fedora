//
// Created on 26.08.2021.
//

#include "Analyzers/ReadAfterReturnableFunName.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadName.h"

namespace fedora {
    namespace analytic {

        /**
         * @example case 1: start args
         * let a = a(1 2)
         *
         * @example case 2: next function
         * let a = b # we get the "let" after the "b" #
         * let c = null
         *
         * @example case 3: force call
         * let a = b
         * force a
         */
        std::shared_ptr<AnalyticBasic>
        ReadAfterReturnableFunName::analyzeToken(const parser::Token &t, ContextBuilder &b) {
            if (t.getType() == parser::TokenType::CallOpen) {
                // case 1
                return std::make_shared<ReadForceArgs>();
            } else if (t.getType() == parser::TokenType::FunctionDeclaration) {
                // case 2
                return std::make_shared<ReadName>(ReadName::ReadNameMode::RETURNABLE_FUN_CALL);
            } else if (t.getType() == parser::TokenType::ForceCall) {
                // case 3
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FORCE_CALL);
            } else {
                throwException(L"Expected arguments or end of a returnable funCall declaration, but got " + t.getData(),
                               "ReadAfterReturnableFunName::analyzeToken");
            }
        }

        std::string ReadAfterReturnableFunName::getClassFileName() {
            return "ReadAfterReturnableFunName.h";
        }
    }
}