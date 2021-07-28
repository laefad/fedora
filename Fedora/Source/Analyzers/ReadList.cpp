//
// Created on 27.07.2021.
//

#include <memory>

#include <Analyzers/ReadList.h>
#include "Analyzers/AnalyticUtils.h"
#include <Analyzers/ReadFunArgs.h>
#include <Analyzers/ReadKeyWord.h>
#include <Analyzers/ReadForceArgs.h>

namespace fedora{
    namespace analytic{

        std::shared_ptr<AnalyticBasic> ReadList::analyzeToken(Token &t) {
            std::cout<<"Class: "<<getFileName()<<std::endl;
            std::wcout<<L"Token: "<<t.data<<std::endl;

            addToken(t); // Запомнить прочитаный токен

            // Мы можем получить:
            // 1. Число
            // 2. Строку
            // 3. Список
            // 4. Функцию (с аргументами или без)

            if(AnalyticUtils::isValueAKeyWord(t.data))
                throwException(L"Expected a list value, but got a keyword.", "analyzeToken(Token&)");

            // Если функция, то перейдём на этап чтения аргументов
            if (AnalyticUtils::isValidName(t.data) && !isTokenARightSquareBracket(t.data)){
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
            }

            // Если строка, число, список или закрытая скобка
            return chooseReturn(t);
        }

        std::string ReadList::getFileName() {
            return "ReadList.h";
        }

        bool ReadList::isTokenARightSquareBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L']';
        }

        std::shared_ptr<AnalyticBasic> ReadList::chooseReturn(Token& t) {
            // Если закончился ввод списка
            if (isTokenARightSquareBracket(t.data)){
                switch (mode) {
                    // Если мы читаем список внутри аргументов функции
                    case readList::READ_FUNCTION_ARG:
                        return std::make_shared<ReadFunArgs>(std::vector<Token>());

                    // Если мы читаем список как возвращаемое значение
                    case readList::READ_FUNCTION_RETURN:
                        return std::make_shared<ReadKeyWord>(std::vector<Token>());
                }
            }else {
                // Если список не закончился
                return shared_from_this();
            }
        }
    }
}


