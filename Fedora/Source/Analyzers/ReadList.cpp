//
// Created on 27.07.2021.
//

#include <memory>

#include <Analyzers/ReadList.h>
#include "Analyzers/AnalyticUtils.h"
#include <Analyzers/ReadFunArgs.h>
#include <Analyzers/ReadKeyWord.h>
#include <Analyzers/ReadForceArgs.h>
#include <Analyzers/ReadAfterListEnd.h>

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token &t) {
            log("Class: " + getFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.data, fedora::settings::LOG_VERBOSE);

            addToken(t); // Запомнить прочитаный токен

            // Мы можем получить:
            // 1. Число
            // 2. Строку
            // 3. Список
            // 4. Функцию (с аргументами или без)
            // 5. ] Закрытие списка

            if (AnalyticUtils::isValueAKeyWord(t.data))
                throwException(L"Expected a list value, but got a keyword.", "analyzeToken(Token&)");

            // Если функция, то перейдём на этап чтения аргументов
            if (AnalyticUtils::isValidName(t.data) && !AnalyticUtils::isTokenARightSquareBracket(t.data)) {
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
            }

            // if number
            if (AnalyticUtils::isValueANumber(t.data)){
                return shared_from_this();
            }

            // if string
            if (AnalyticUtils::isValueAString(t.data)){
                return shared_from_this();
            }

            // "[" if list start
            if (AnalyticUtils::isTokenALeftSquareBracket(t.data)){
                return shared_from_this();
            }

            // "]" if list end
            if (AnalyticUtils::isTokenARightSquareBracket(t.data)){
                return std::make_shared<ReadAfterListEnd>(std::vector<Token>());
            }else{
                throwException(L"Expected a list member, but got token = "+t.data,"analyzeToken(Token&)");
                // TODO Вызывать сервис очистки синглтонов перед экстренным завершением программы
            }
            // Если строка, число, список или закрытая скобка
            //return chooseReturn(t);
        }

        std::string ReadList::getFileName() {
            return "ReadList.h";
        }

        std::shared_ptr<AnalyticBasic> ReadList::chooseReturn(Token &t) {
            // Если закончился ввод списка
            if (AnalyticUtils::isTokenARightSquareBracket(t.data)) {
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
    }
}


