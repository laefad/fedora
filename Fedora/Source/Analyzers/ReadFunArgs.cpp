#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadFunArgs.h"

namespace fedora::analytic {
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
    std::shared_ptr<AnalyticBasic> ReadFunArgs::analyzeToken(
        parser::Token const& t,
        ContextBuilder& b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::FunctionContextDeclaration:
            return std::make_shared<ReadKeyWord>();

        case TokenType::FunctionReturnableDeclaration:
            b.notifyWeSetReturnable();
            return std::make_shared<ReadResult>();

        case TokenType::Name:
            b.addArgumentName(t);
            return shared_from_this();

        default:
            throwException(
                u8"Invalid argument name",
                this->getClassFileName()
            );
            return shared_from_this();
        }
    }

    std::u8string ReadFunArgs::getClassFileName() {
        return u8"ReadFunArgs.h";
    }
}
