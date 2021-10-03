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
            log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() == parser::TokenType::CallOpen) {
                // case 1
                return std::make_shared<ReadCallArgs>();
            } else if (t.getType() == parser::TokenType::FunctionDeclaration) {
                // case 2
                b.finishCurrentContext();
                b.notifyWeGotLetToken();
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);
            } else if (t.getType() == parser::TokenType::ForceCall) {
                // case 3
                throw "Unimplemented ReadAfterReturnableFunName::analyzeToken";
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FORCE_CALL);
            } else {
                throwException(u8"Expected arguments or end of a returnable funCall declaration, but got " + t.getData(),
                               u8"ReadAfterReturnableFunName::analyzeToken");
            }
        }

        std::u8string ReadAfterReturnableFunName::getClassFileName() {
            return u8"ReadAfterReturnableFunName.h";
        }
    }
}
