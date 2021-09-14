
#include <Analyzers/ReadName.h>
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadAfterReturnableFunName.h"

namespace fedora {
    namespace analytic {

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
        std::shared_ptr<AnalyticBasic> ReadResult::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            if (t.getType() == TokenType::Null) {
                // if "null" returns
                b.addReturnableNull();
                return std::make_shared<ReadKeyWord>();
            } else if (t.getType() == TokenType::Number) {
                // if number returns
                b.addReturnableNumber(t.getData());
                return std::make_shared<ReadKeyWord>();
            } else if (t.getType() == TokenType::String) {
                // if string returns
                b.addReturnableString(t.getData());
                return std::make_shared<ReadKeyWord>();
            } else if (t.getType() == TokenType::ListOpen) {
                // if list returns
                b.addReturnableList();
                return std::make_shared<ReadList>();
            } else if (t.getType() == TokenType::Name) {
                // if funCall returns
                // TODO Внедрить режим чтения для force вызова и ретурна из функции
                b.addReturnableFunCall(t.getData());
                return std::make_shared<ReadAfterReturnableFunName>();
            } else if (t.getType() == TokenType::ForceCall) {
                // if force call returns
                return std::make_shared<ReadName>(ReadName::ReadNameMode::RETURNABLE_FORCE_CALL);
            } else {
                // Пустая строка, которая нужна, чтобы конкатенировать константные строки. Забавно
                std::u8string text;
                // TODO Вынести тексты всех ошибок в единый файл и пронумеровать их
                throwException(u8"You have to return something from function, but nothing valid found.\n"
                               + text
                               + u8"Possible variants:\n"
                               + text
                               + u8"1. Number\n2. String\n3. List\n4. FunCall\n"
                               + text
                               + u8"Found: token = "
                               + t.getData(),
                               u8"analyzeToken(Token&)");
                return shared_from_this();
            }
        }

        std::u8string ReadResult::getClassFileName() {
            return u8"ReadResult.h";
        }
    }
}
