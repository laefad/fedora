#include "Analyzers/ReadList.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora::analytic {

    /**
     *
     * @example case 1: Add number in list
     * [ ... 1 ... ]
     *
     * @example case 2: Add string in list
     * [ ... "lol" ... ]
     *
     * @example case 3: Add list in list
     * [ ... [ ... ] ... ]
     *
     * @example case 4: Add function in list
     * [ ... main... ]
     *
     * @example case 5: Add forceCall in list
     * [ ... force main... ]
     *
     * @example case 6: List finish
     * ... ]
     */
    std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(
        parser::Token const& t,
        ContextBuilder& b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::Number:
            b.addSimpleTypeInList(t);
            return shared_from_this();

        case TokenType::String:
            b.addSimpleTypeInList(t);
            return shared_from_this();

        case TokenType::Null:
            b.addSimpleTypeInList(t);
            return shared_from_this();

        case TokenType::Name:
            b.addFunCallInList(t);
            return std::make_shared<ReadCallArgs>();

        case TokenType::ListOpen:
            return shared_from_this();

        case TokenType::ListClose:
            b.endList();
            return std::make_shared<ReadAfterListEnd>();

        default:
            throwException(
                u8"Expected a list member, but got token = "
                + t.getData(),
                this->getClassFileName()
            );

        }
    }

    std::u8string ReadList::getClassFileName() {
        return u8"ReadList.h";
    }
}
