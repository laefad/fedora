
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadFunArgs.h"

namespace fedora {
    namespace analytic {

        /**
         * Reading arg names for function
         *
         * @example case 1: read WHERE
         * let a where      # means that function does not have args and we read context declaration #
         * ...
         *
         * @example case 2: read '='
         * let a = ...     # means that function does not have args and we read returnable value #
         *
         * @example case 3: actual argument
         * let main arg1 ... # means that arg1 is the name of an argument of the main function #
         */
        std::shared_ptr<AnalyticBasic> ReadFunArgs::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() == TokenType::FunctionContextDeclaration) {
                // case 1
                return std::make_shared<ReadKeyWord>();
            } else if (t.getType() == TokenType::FunctionReturnableDeclaration) {
                // case 2
                b.notifyWeSetReturnable();
                return std::make_shared<ReadResult>();
            } else if (t.getType() == TokenType::Name) {
                //case 3
                b.addArgumentName(t);
                return shared_from_this();
            } else {
                // error
                throwException(u8"Invalid argument name",
                               u8"analyzeToken(Token&)");
                return shared_from_this();
            }
        }

        std::u8string ReadFunArgs::getClassFileName() {
            return u8"ReadFunArgs.h";
        }
    }
}
