
#include "KeyWords.h"
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/AnalyticUtils.h"

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
         * @example case 3:
         * force main
         *
         * @example case 4:
         * ... = [main main2]
         *
         * @example case 5:
         * someFun(arg1 main arg3)
         */
        std::shared_ptr<AnalyticBasic> ReadName::analyzeToken(fedora::Token const &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (!AnalyticUtils::isTokenAName(t))
                throwException(L"Expected a function name, but founded name is invalid. Token = " + t.getData(),
                               "analyzeToken(Token&) <- AnalyticUtils::isValidName(std::wstring&)");

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
            }
        }

        std::string ReadName::getClassFileName() {
            return "ReadName.h";
        }


        std::shared_ptr<AnalyticBasic> ReadName::functionDeclaration(Token const &t, ContextBuilder &b) {
            b.setFunctionName(t);
            return std::shared_ptr<ReadFunArgs>();
        }

        std::shared_ptr<AnalyticBasic> ReadName::returnableFunCall(Token const &, ContextBuilder &) {
            return std::shared_ptr<AnalyticBasic>();
        }
    }
}
