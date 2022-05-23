#include "Analyzers/ReadAfterReturnableFunName.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadName.h"

namespace fedora::analytic {
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
    std::shared_ptr<AnalyticBasic> ReadAfterReturnableFunName::analyzeToken(
        const parser::Token& t,
        ContextBuilder& b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::CallOpen:
            return std::make_shared<ReadCallArgs>();

        case TokenType::FunctionDeclaration:
            b.finishCurrentContext();
            b.notifyWeGotLetToken();
            return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);

        case TokenType::ForceCall:
            throw "Unimplemented ReadAfterReturnableFunName::analyzeToken";
            return std::make_shared<ReadName>(ReadName::ReadNameMode::FORCE_CALL);

        default:
            throwException(
                u8"Expected arguments or end of a returnable funCall declaration, but got "
                + t.getData(),
                this->getClassFileName()
            );
            return shared_from_this();
        }
    }

    std::u8string ReadAfterReturnableFunName::getClassFileName() {
        return u8"ReadAfterReturnableFunName.h";
    }
}
