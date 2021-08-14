
#include "KeyWords.h"
#include "Exceptions/AnalyzerException.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadFunArgs.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {


        std::shared_ptr<AnalyticBasic> ReadFunArgs::analyzeToken(fedora::Token const &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            //addToken(token);  // Запомнить считаный токен


            // 3 пути:
            // 1. Мы прочитали [where] и начинается контекст функции
            // 2. Мы прочитали имя аргумента
            // 3. Мы прочитали равно, значит закончилось описание функции и начинается описание возвращаемого типа

            // Если получили знак равно
            if (t == returns) {
                return std::make_shared<ReadResult>();
            }

            // Читаем внутренний контекст функции, если встретили where
            if (t == where) {
                return std::make_shared<ReadKeyWord>();
            } else {
                // Читаем список аргументов
                if (AnalyticUtils::isTokenAName(t)) {
                    // Имя аргумента корректно
                    return shared_from_this();
                } else {
                    // Имя аргумента некорректно
                    throwException(L"Invalid argument name", "analyzeToken(Token&)");
                }

            }

            // TODO Будет ли хорошим тоном добавлять подобный Throw, чтобы исключить возможность логической ошибки при прохждении логики? Т.е. это проблема программы, а юзер мб сделал всё верно
            throwException(L"If-s didn't work", "analyzeToken(Token&)");
            return nullptr;
        }

        std::string ReadFunArgs::getClassFileName() {
            return "ReadFunArgs.h";
        }
    }
}
