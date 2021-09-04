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
            using fedora::parser::TokenType;
            log(L"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() == parser::TokenType::CallOpen) {
                // case 1
                return std::make_shared<ReadForceArgs>();
            } else if (t.getType() == parser::TokenType::FunctionDeclaration) {
                // case 2
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);
            } else if (t.getType() == parser::TokenType::ForceCall) {
                // case 3
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FORCE_CALL);
            } else {
                throwException(L"Expected arguments or end of a returnable funCall declaration, but got " + t.getData(),
                               L"ReadAfterReturnableFunName::analyzeToken");
            }
        }

        std::wstring ReadAfterReturnableFunName::getClassFileName() {
            return L"ReadAfterReturnableFunName.h";
        }
    }
}
