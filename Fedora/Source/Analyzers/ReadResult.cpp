#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadName.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadAfterReturnableFunName.h"

namespace fedora::analytic {
    /**
     * @example case 1: Return null
     * let a = null
     *
     * @example case 2: Return number
     * let a = 1
     *
     * @example case 3: Return string
     * let a = "ok" # string should be put in context without " symbols #
     *
     * @example case 4: Return list
     * let a = [ ...
     *
     * @example case 5: Return function
     * let a = main
     */
    std::shared_ptr<AnalyticBasic> ReadResult::analyzeToken(
        parser::Token const &t, 
        ContextBuilder &b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::Null:
            b.addReturnableNull();
            return std::make_shared<ReadKeyWord>();

        case TokenType::Number:
            b.addReturnableNumber(t.getData());
            return std::make_shared<ReadKeyWord>();

        case TokenType::String:
            b.addReturnableString(t.getData());
            return std::make_shared<ReadKeyWord>();

        case TokenType::ListOpen:
            b.addReturnableList();
            return std::make_shared<ReadList>();

        case TokenType::Name:
            // TODO Внедрить режим чтения для force вызова и ретурна из функции
            b.addReturnableFunCall(t.getData());
            return std::make_shared<ReadAfterReturnableFunName>();

        case TokenType::ForceCall:
            return std::make_shared<ReadName>(ReadName::ReadNameMode::RETURNABLE_FORCE_CALL);

        default:
            // Пустая строка, которая нужна, чтобы конкатенировать константные строки. Забавно
            std::u8string text;
            // TODO Вынести тексты всех ошибок в единый файл и пронумеровать их
            throwException(
                u8"You have to return something from function, but nothing valid found.\n"
                + text
                + u8"Possible variants:\n"
                + text
                + u8"1. Number\n2. String\n3. List\n4. FunCall\n"
                + text
                + u8"Found: token = "
                + t.getData(),
                this->getClassFileName()
            );
            return shared_from_this();
        }
    }

    std::u8string ReadResult::getClassFileName() {
        return u8"ReadResult.h";
    }
}
