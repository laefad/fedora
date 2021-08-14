
#include "Exceptions/AnalyzerException.h"
#include "KeyWords.h"

#include "Analyzers/ReadName.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/AnalyticUtils.h"
#include "Analyzers/ReadForceName.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadKeyWord::analyzeToken(Token const &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);


            if (t == returns) {
                // if we got an "equals"
                b.notifyWeSetReturnable();
                return std::make_shared<ReadResult>();

            } else if (t == pure) {
                // if is "pure", set keyword in context and read fun name
                KeyWord casted = KeyWord(t);
                b.addFunctionDeclarationToken(casted);
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);

            } else if (t == force) {
                // if is "force", read forceCall name
                b.notifyWeStartForceCall();
                return std::make_shared<ReadName>(ReadName::FORCE_CALL);

            } else if (t == let) {
                // if is let, read fun name
                b.notifyWeGotLetToken();
                return std::make_shared<ReadName>(ReadName::ReadNameMode::FUNCTION_DECLARATION);

            } else {
                throwException(L"Expected a pre-function key word or \"=\", but got \"" + t.getData() + L"\"",
                               "analyzeToken(Token &)");
                return std::shared_ptr<AnalyticBasic>();
            }

        }

        std::string ReadKeyWord::getClassFileName() {
            return "ReadKeyWord.h";
        }
    }
}
