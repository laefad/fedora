//
// Created on 23.07.2021.
//

#include <KeyWords.h>
#include <Analyzers/ReadKeyWord.h>
#include <Exceptions/AnalyzerException.h>
#include <Analyzers/ReadResult.h>
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadFunArgs::analyzeToken(fedora::Token &token) {
            addToken(token);  // Запомнить считаный токен

            // 3 пути:
            // 1. Мы прочитали [where] и начинается контекст функции
            // 2. Мы прочитали имя аргумента
            // 3. Мы прочитали равно, значит закончилось описание функции и начинается описание возвращаемого типа

            // Если получили знак равно
            if (token == returns){
                return std::make_shared<ReadResult>(std::vector<Token>());
            }

            // Читаем внутренний контекст функции, если встретили where
            if (token == where) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }else{
                // Читаем список аргументов
                if (AnalyticUtils::isValidName(token.data)){
                    // Имя аргумента корректно
                    return shared_from_this();
                }else{
                    // Имя аргумента некорректно
                    throwException(L"Invalid argument name", "analyzeToken(Token&)");
                }

            }

            // TODO Будет ли хорошим тоном добавлять подобный Throw, чтобы исключить возможность логической ошибки при прохждении логики?
            throwException(L"If-s didn't work", "analyzeToken(Token&)");
            return nullptr;
        }

        void ReadFunArgs::throwException(const std::wstring &msg, const std::string &funcName) {
            throw AnalyzerException(msg,"ReadFunArgs.h",funcName);
        }
    }
}
