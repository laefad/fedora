
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadKeyWord.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(L"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);


            if (t.getType() == TokenType::FunctionReturnableDeclaration) {
                // if we got an "equals"
                b.notifyWeSetReturnable();
                return std::make_shared<ReadResult>();

            } else if (t.getType() == TokenType::ForceCall) {

                // if is "force", read forceCall name
                b.notifyWeStartForceCall();
                return std::make_shared<ReadName>(ReadName::FORCE_CALL);

            } else if (t.getType() == TokenType::FunctionDeclaration) {

                // if is let, read fun name
                b.notifyWeGotLetToken();
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);

            } else {
                throwException(L"Expected a pre-function key word or \"=\", but got \"" + t.getData() + L"\"",
                               L"analyzeToken(Token &)");
                return shared_from_this();
            }
        }

        std::wstring ReadKeyWord::getClassFileName() {
            return L"ReadKeyWord.h";
        }
    }
}
