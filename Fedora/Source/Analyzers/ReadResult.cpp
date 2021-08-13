
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {

        ReadResult::ReadResult(std::vector<Token> vec):
            AnalyticBasic(std::move(vec))
        {}

        std::shared_ptr<AnalyticBasic> ReadResult::analyzeToken(Token const& t) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            addToken(t);    // Записать прочитаный токен

            // 4 Варианта, что можно вернуть из функции:
            // 1. Число
            // 2. Строка
            // 3. Список
            // 4. Функция

            // Если число
            if (AnalyticUtils::isTokenANumber(t)) {
                // TODO Выделить во внешнюю константу пустой вектор токенов ( std::vector<Token>() )
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Если строка
            if (AnalyticUtils::isTokenAString(t)) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Если Список
            if (AnalyticUtils::isTokenALeftSquareBracket(t)) {
                return std::make_shared<ReadList>(std::vector<Token>(), readList::READ_FUNCTION_RETURN);
            }

            // Если функция
            if (AnalyticUtils::isTokenAName(t)) {
                // TODO Внедрить режим чтения для force вызова и ретурна из функции
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
            }

            // Пустая строка, которая нужна, чтобы конкатенировать константные строки. Забавно
            std::wstring text = L"";
            // TODO Вынести тексты всех ошибок в единый файл и пронумеровать их
            throwException(L"You have to return something from function, but nothing valid found.\n" + text +
                           L"Possible variants:\n" + text + L"1. Number\n2. String\n3. List\n4. FunCall\n" +
                           text + L"Found: token = " + t.getData(), "analyzeToken(Token&)");

            // TODO Я не хочу здесь return. Программа должна остановить выполнение
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadResult::getFileName() {
            return "ReadResult.h";
        }
    }
}
