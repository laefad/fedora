
#include "Analyzers/ReadList.h"
#include "Analyzers/AnalyticUtils.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora {
    namespace analytic {

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
         */
        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            //addToken(t); // Запомнить прочитаный токен

            // Мы можем получить:
            // 1. Число
            // 2. Строку
            // 3. Список
            // 4. Функцию (с аргументами или без)
            // 5. ] Закрытие списка

            if (t.getType() == TokenType::Name)
                return std::make_shared<ReadForceArgs>();

            // if number
            if (t.getType() == TokenType::Number) {
                return shared_from_this();
            }

            // if string
            if (t.getType() == TokenType::String) {
                return shared_from_this();
            }

            // "[" if list start
            if (t.getType() == TokenType::ListOpen) {
                return shared_from_this();
            }

            // "]" if list end
            if (t.getType() == TokenType::ListClose) {
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
