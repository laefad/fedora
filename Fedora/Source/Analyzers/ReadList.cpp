
#include "Analyzers/ReadList.h"
#include "Analyzers/AnalyticUtils.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora {
    namespace analytic {

        ReadList::ReadList(std::vector<Token> vec, readList::readMode m):
            AnalyticBasic(std::move(vec)), mode(m)
        {}

        ReadList::ReadList(std::vector<Token> vec):
            AnalyticBasic(std::move(vec))
        {
            log(L"Нерабочий конструктор, убрать его, когда завезут моды для всех классов", 
                fedora::settings::LOG_ERROR);
        }

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token const& t) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            addToken(t); // Запомнить прочитаный токен

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
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
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
                return std::make_shared<ReadAfterListEnd>(std::vector<Token>());
            } else {
                throwException(L"Expected a list member, but got token = " + t.getData(), "analyzeToken(Token&)");
                // TODO Вызывать сервис очистки синглтонов перед экстренным завершением программы
            }
            // Если строка, число, список или закрытая скобка
            //return chooseReturn(t);
        }

        std::string ReadList::getFileName() {
            return "ReadList.h";
        }

        std::shared_ptr<AnalyticBasic> ReadList::chooseReturn(Token const& t) {
            // Если закончился ввод списка
            if (AnalyticUtils::isTokenARightSquareBracket(t)) {
                switch (mode) {
                    // Если мы читаем список внутри аргументов функции
                    case readList::READ_FUNCTION_ARG:
                        return std::make_shared<ReadFunArgs>(std::vector<Token>());

                        // Если мы читаем список как возвращаемое значение
                    case readList::READ_FUNCTION_RETURN:
                        return std::make_shared<ReadKeyWord>(std::vector<Token>());
                }
            } else {
                // Если список не закончился
                return shared_from_this();
            }
        }

        //TODO no return compiler warning
    }
}
