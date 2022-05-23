#include "Analyzers/ReadName.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadKeyWord.h"

namespace fedora::analytic {
    std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(parser::Token const& t, ContextBuilder& b) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::FunctionReturnableDeclaration:
            // if we got an "equals"
            b.notifyWeSetReturnable();
            return std::make_shared<ReadResult>();

        case TokenType::ForceCall:
            // if is "force", read forceCall name
            b.notifyWeStartForceCall();
            return std::make_shared<ReadName>(ReadName::FORCE_CALL);

        case TokenType::FunctionDeclaration:
            // if is let, read fun name
            b.notifyWeGotLetToken();
            return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);

        default:
            throwException(
                u8"Expected a pre-function key word or \"=\", but got \""
                + t.getData()
                + u8"\"",
                this->getClassFileName()
            );
            return shared_from_this();
        }
    }

    std::u8string ReadKeyWord::getClassFileName() {
        return u8"ReadKeyWord.h";
    }
}
