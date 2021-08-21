
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/AnalyticUtils.h"

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
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);


            // Если число
            if (t.getType() == TokenType::Number) {
                b.addReturnableNumber(t.getData());
                return std::make_shared<ReadKeyWord>();
            }

            // Если строка
            if (t.getType() == TokenType::String) {
                return std::make_shared<ReadKeyWord>();
            }

            // Если Список
            if (t.getType() == TokenType::ListOpen) {
                return std::make_shared<ReadList>();
            }

            // Если функция
            if (t.getType() == TokenType::Name) {
                // TODO Внедрить режим чтения для force вызова и ретурна из функции
                return std::make_shared<ReadForceArgs>();
            }

            // Пустая строка, которая нужна, чтобы конкатенировать константные строки. Забавно
            std::wstring text;
            // TODO Вынести тексты всех ошибок в единый файл и пронумеровать их
            throwException(L"You have to return something from function, but nothing valid found.\n" + text +
                           L"Possible variants:\n" + text + L"1. Number\n2. String\n3. List\n4. FunCall\n" +
                           text + L"Found: token = " + t.getData(), "analyzeToken(Token&)");

            // TODO Я не хочу здесь return. Программа должна остановить выполнение
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadResult::getClassFileName() {
            return "ReadResult.h";
        }
    }
}
