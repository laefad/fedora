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

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            //addToken(t); // Запомнить прочитаный токен

            // Мы можем получить:
            // 1. Число
            // 2. Строку
            // 3. Список
            // 4. Функцию (с аргументами или без)
            // 5. ] Закрытие списка

            if (AnalyticUtils::isValueAKeyWord(t.getData()))
                throwException(L"Expected a list value, but got a keyword.", "analyzeToken(Token&)");

            // Если функция, то перейдём на этап чтения аргументов
            if (AnalyticUtils::isValidName(t.getData()) && !AnalyticUtils::isTokenARightSquareBracket(t.getData())) {
                return std::make_shared<ReadForceArgs>();
            }

            // if number
            if (AnalyticUtils::isValueANumber(t.getData())) {
                return shared_from_this();
            }

            // if string
            if (AnalyticUtils::isValueAString(t.getData())) {
                return shared_from_this();
            }

            // "[" if list start
            if (AnalyticUtils::isTokenALeftSquareBracket(t.getData())) {
                return shared_from_this();
            }

            // "]" if list end
            if (AnalyticUtils::isTokenARightSquareBracket(t.getData())) {
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

        std::shared_ptr<AnalyticBasic> ReadList::chooseReturn(Token &t) {
            // Если закончился ввод списка
            if (AnalyticUtils::isTokenARightSquareBracket(t.getData())) {
                switch (mode) {
                    // Если мы читаем список внутри аргументов функции
                    case readList::READ_FUNCTION_ARG:
                        return std::make_shared<ReadFunArgs>();

                        // Если мы читаем список как возвращаемое значение
                    case readList::READ_FUNCTION_RETURN:
                        return std::make_shared<ReadKeyWord>();
                }
            } else {
                // Если список не закончился
                return shared_from_this();
            }
        }
    }
}


