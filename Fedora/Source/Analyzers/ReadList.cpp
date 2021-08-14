
#include "Analyzers/ReadList.h"
#include "Analyzers/AnalyticUtils.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token const &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            //addToken(t); // Запомнить прочитаный токен

            // Мы можем получить:
            // 1. Число
            // 2. Строку
            // 3. Список
            // 4. Функцию (с аргументами или без)
            // 5. ] Закрытие списка

            if (AnalyticUtils::isTokenAKeyWord(t))
                throwException(L"Expected a list value, but got a keyword.", "analyzeToken(Token&)");

            // Если функция, то перейдём на этап чтения аргументов
            if (AnalyticUtils::isTokenAName(t) && !AnalyticUtils::isTokenARightSquareBracket(t)) {
                return std::make_shared<ReadForceArgs>();
            }

            // if number
            if (AnalyticUtils::isTokenANumber(t)) {
                return shared_from_this();
            }

            // if string
            if (AnalyticUtils::isTokenAString(t)) {
                return shared_from_this();
            }

            // "[" if list start
            if (AnalyticUtils::isTokenALeftSquareBracket(t)) {
                return shared_from_this();
            }

            // "]" if list end
            if (AnalyticUtils::isTokenARightSquareBracket(t)) {
                return std::make_shared<ReadAfterListEnd>();
            } else {
                throwException(L"Expected a list member, but got token = " + t.getData(), "analyzeToken(Token&)");
                // TODO Вызывать сервис очистки синглтонов перед экстренным завершением программы
            }
            // Если строка, число, список или закрытая скобка
            //return chooseReturn(t);
        }

        std::string ReadList::getClassFileName() {
            return "ReadList.h";
        }

    }
}
