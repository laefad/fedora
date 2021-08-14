
#include "KeyWords.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadForceArgs::analyzeToken(Token const &t, ContextBuilder &b) {
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
            if (AnalyticUtils::isTokenALeftCircleBracket(t)) {
                return shared_from_this();
            }

            // Число
            if (AnalyticUtils::isTokenANumber(t)) {
                return shared_from_this();
            }

            // Строка
            if (AnalyticUtils::isTokenAString(t)) {
                return shared_from_this();
            }

            // "[" A List
            if (AnalyticUtils::isTokenALeftSquareBracket(t)) {
                return std::make_shared<ReadList>();
            }

            // Если функция
            if (AnalyticUtils::isTokenAName(t)) {
                // Начинаем новое чтение аргументов
                return std::make_shared<ReadForceArgs>();
            }

            // "]"
            if (AnalyticUtils::isTokenARightSquareBracket(t)) {
                // TODO Либо мы читаем следующий аргумент функции (если список играет роль одного из аргументов), либо переходим к чтению следующей функции
                return shared_from_this();
            }

            // ")"
            if (AnalyticUtils::isTokenARightCircleBracket(t)) {
                // Заканчиваем чтение аргументов
                // TODO Внедрить mode и начать здесь исполнение функции иначе переходим к чтению дальнейшего контекста
                return shared_from_this();
            }

            // Pure force Если идут ключевые слова для следующей функции, т.е. начинается её объявление
            if (AnalyticUtils::isTokenAPreFunKeyWord(t)) {
                // TODO Понять, когда объявление функции валидно.
                // Оно валидно внутри контекста where ^ = или после завершения returnable (т.е. текущий токен должен корретно завершать рретурнабл, иначе оформлять вкид)
                return std::make_shared<ReadKeyWord>();
            }

            if (AnalyticUtils::isTokenAKeyWord(t)) {
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
