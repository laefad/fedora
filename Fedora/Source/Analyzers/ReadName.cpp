
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadName.h"

namespace fedora {
    namespace analytic {

        /**
         *
        * @param t - token we get
        * @param b - reference to context builder
        * @return next analyzer
         *
         * Examples for MAIN:
         * @example case 1: FUNCTION_DECLARATION
         * let main = null
         *
         * @example case 2: RETURNABLE_FUN_CALL
         * let a = main
         *
         * @example case 3: FORCE_CAL
         * force main
         *
         * @example case 4: LIST_VALUE
         * ... = [main main2]
         *
         * @example case 5:
         * someFun(arg1 main arg3)
         *
         * @brief actually a fabric method
         */
        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(L"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() != TokenType::Name)
                throwException(L"Expected a function name, but founded name is invalid. Token = " + t.getData(),
                               L"analyzeToken(Token&) <- AnalyticUtils::isValidName(std::wstring&)");

            switch (mode) {
                case FUNCTION_DECLARATION:
                    return functionDeclaration(t, b);
                case RETURNABLE_FUN_CALL:
                    return returnableFunCall(t, b);
                case FORCE_CALL:
                    return forceCall(t, b);
                case LIST_VALUE:
                    return listValue(t, b);
                case FUNCTION_ARGUMENT:
                    return functionArgument(t, b);
                case RETURNABLE_FORCE_CALL:
                    throwException(L"Unimplemented", L"ReadName::analyzeToken switch(mode)");
                    break;
            }

            //TODO no default exit
        }

        std::wstring ReadName::getClassFileName() {
            return L"ReadName.h";
        }


        std::shared_ptr<AnalyticBasic> ReadName::functionDeclaration(parser::Token const &t, ContextBuilder &b) {
            b.setFunctionName(t);
            return std::make_shared<ReadFunArgs>();
        }

        std::shared_ptr<AnalyticBasic> ReadName::returnableFunCall(parser::Token const &t, ContextBuilder &b) {
            b.addReturnableFunCall(t.getData());
            return std::make_shared<ReadForceArgs>();
        }

        std::shared_ptr<AnalyticBasic> ReadName::forceCall(parser::Token const &t, ContextBuilder &b) {
            b.setForceName(t.getData());
            return std::make_shared<ReadForceArgs>();
        }

        std::shared_ptr<AnalyticBasic> ReadName::listValue(const parser::Token &, ContextBuilder &) {
            throwException(L"unimplemented", L"ReadName::listValue");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::shared_ptr<AnalyticBasic> ReadName::functionArgument(const parser::Token &, ContextBuilder &) {
            throwException(L"unimplemented", L"ReadName::functionArgument");
            return std::shared_ptr<AnalyticBasic>();
        }
    }
}
