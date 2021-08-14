//
// Created on 23.07.2021.
//

#include <memory>
#include <Analyzers/ReadKeyWord.h>
#include <Analyzers/ReadList.h>
#include <KeyWords.h>
#include <Analyzers/ReadName.h>
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        // TODO !!!!!!!!! Мне не нравится, что мы приходим в этот класс и во время начала чтения аргументов, и в середине. Это нормально из-за того, что функции с аргументами могут выступать как аргументы для других функций с аргументами. Возможно, следует внедрить дополнительные переменные состояния, чтобы адекватно оценивать контекст
        std::shared_ptr<AnalyticBasic> ReadForceArgs::analyzeToken(Token &t, ContextBuilder &b) {
            log("Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(L"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

            // TODO if-ы размансить

            // Что ожидается:
            // 0. Открывающая круглая скобка (начало чтения аргументов)
            // 1. Число
            // 2. Строка
            // 3. Список
            // 4. Имя функции
            // 5. Закрывающая круглая скобка
            // 6. Закрывающая квадратная скобка
            // Если функция вызывается без скобок и без аргументов и заканчивается чтение списка
            // @example                    -> | <-
            // let my_list = [ 1 2 "3" my_str ]

            // "(" Открвающая скобка. Начало чтения аргументов
            if (AnalyticUtils::isTokenALeftCircleBracket(t.getData())) {
                return shared_from_this();
            }

            // Число
            if (AnalyticUtils::isValueANumber(t.getData())) {
                return shared_from_this();
            }

            // Строка
            if (AnalyticUtils::isValueANumber(t.getData())) {
                return shared_from_this();
            }

            // "[" A List
            if (AnalyticUtils::isTokenALeftSquareBracket(t.getData())) {
                return std::make_shared<ReadList>();
            }

            // Если функция
            if (AnalyticUtils::isValidName(t.getData())) {
                // Начинаем новое чтение аргументов
                return std::make_shared<ReadForceArgs>();
            }

            // let
            if (t == let) {
                // Произошло обьявление новой функции? Нужно прочитать название
                // TODO Понять, когда объявление функции валидно.
                // Оно валидно внутри контекста where ^ = или после завершения returnable (т.е. текущий токен должен корретно завершать рретурнабл, иначе оформлять вкид)
                return std::make_shared<ReadName>();
            }

            // "]"
            if (AnalyticUtils::isTokenARightSquareBracket(t.getData())) {
                // TODO Либо мы читаем следующий аргумент функции (если список играет роль одного из аргументов), либо переходим к чтению следующей функции
                return shared_from_this();
            }

            // ")"
            if (AnalyticUtils::isTokenARightCircleBracket(t.getData())) {
                // Заканчиваем чтение аргументов
                // TODO Внедрить mode и начать здесь исполнение функции иначе переходим к чтению дальнейшего контекста
                return shared_from_this();
            }

            // Pure force Если идут ключевые слова для следующей функции, т.е. начинается её объявление
            if (AnalyticUtils::isTokenAPreFunKeyWord(t.getData())) {
                // TODO Понять, когда объявление функции валидно.
                // Оно валидно внутри контекста where ^ = или после завершения returnable (т.е. текущий токен должен корретно завершать рретурнабл, иначе оформлять вкид)
                return std::make_shared<ReadKeyWord>();
            }

            if (AnalyticUtils::isValueAKeyWord(t.getData())) {
                throwException(L"Got a keyword when a function argument expected", "analyzeToken(Token &)");
            }

            // TODO Сюда мы вообще не должны попадать
            throwException(L"ForceArgs got something undetectable o_0", "analyzeToken(Token &)");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadForceArgs::getClassFileName() {
            return "ReadForceArgs.h";
        }
    }
}
