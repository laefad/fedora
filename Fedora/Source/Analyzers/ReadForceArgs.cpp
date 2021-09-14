
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadForceArgs.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadForceArgs::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
            log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
            log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

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
            if (t.getType() == TokenType::CallOpen)
                return shared_from_this();

            // Число
            if (t.getType() == TokenType::Number)
                return shared_from_this();

            // Строка
            if (t.getType() == TokenType::String)
                return shared_from_this();

            // "[" A List
            if (t.getType() == TokenType::ListOpen)
                return std::make_shared<ReadList>();

            // Если функция
            if (t.getType() == TokenType::Name)
                // Начинаем новое чтение аргументов
                return std::make_shared<ReadForceArgs>();

            // "]"
            if (t.getType() == TokenType::ListClose)
                // TODO Либо мы читаем следующий аргумент функции (если список играет роль одного из аргументов),
                // либо переходим к чтению следующей функции
                return shared_from_this();

            // ")"
            if (t.getType() == TokenType::CallClose) {
                // Заканчиваем чтение аргументов
                // TODO Внедрить mode и начать здесь исполнение функции иначе переходим к чтению дальнейшего контекста
                return shared_from_this();
            }

            // Pure force Если идут ключевые слова для следующей функции, т.е. начинается её объявление
            // TODO опять вырезал pure 
            if (t.getType() == TokenType::ForceCall) {
                // TODO Понять, когда объявление функции валидно.
                // Оно валидно внутри контекста where ^ = или после завершения returnable (т.е. текущий токен должен корретно завершать рретурнабл, иначе оформлять вкид)
                return std::make_shared<ReadKeyWord>();
            }

            // TODO вырезал проверку, при обновлении токена и KeyWord ее надо будет восстановить
            // if (AnalyticUtils::isTokenAKeyWord(t)) {
            //     throwException(L"Got a keyword when a function argument expected", "analyzeToken(Token &)");
            // }

            // TODO Сюда мы вообще не должны попадать
            throwException(u8"ForceArgs got something undetectable o_0",
                           u8"analyzeToken(Token &)");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::u8string ReadForceArgs::getClassFileName() {
            return u8"ReadForceArgs.h";
        }
    }
}
