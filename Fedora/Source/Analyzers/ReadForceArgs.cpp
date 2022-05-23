#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadForceArgs.h"

namespace fedora::analytic {
    /**
     * @brief TODO write brief
     *
     * @details
     * Что ожидается:
     *  0. Открывающая круглая скобка (начало чтения аргументов)
     *  1. Число
     *  2. Строка
     *  3. Список
     *  4. Имя функции
     *  5. Закрывающая круглая скобка
     *  6. Закрывающая квадратная скобка
     *  7. null
     *  Если функция вызывается без скобок и без аргументов и заканчивается чтение списка
     *  @example                    -> | <-
     *  let my_list = [ 1 2 "3" my_str ]
     */
    std::shared_ptr<AnalyticBasic> ReadCallArgs::analyzeToken(
        parser::Token const& t,
        ContextBuilder& b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        case TokenType::CallOpen:
            // "(" Открывающая скобка. Начало чтения аргументов
            return shared_from_this();

        case TokenType::Number:
            b.addPrimitiveAsCallArgument(t);
            return shared_from_this();

        case TokenType::String:
            b.addPrimitiveAsCallArgument(t);
            return shared_from_this();

        case TokenType::Null:
            b.addPrimitiveAsCallArgument(t);
            return shared_from_this();

        case TokenType::ListOpen:
            return std::make_shared<ReadList>();

        case TokenType::Name:
            // Если функция
            // Начинаем новое чтение аргументов
            return std::make_shared<ReadCallArgs>();

        case TokenType::ListClose:
            // TODO Либо мы читаем следующий аргумент функции (если список играет роль одного из аргументов),
            // либо переходим к чтению следующей функции
            return shared_from_this();

        case TokenType::CallClose:
            // Заканчиваем чтение аргументов
            // TODO Внедрить mode и начать здесь исполнение функции иначе переходим к чтению дальнейшего контекста
            return shared_from_this();

        case TokenType::ForceCall:
            // Pure force Если идут ключевые слова для следующей функции, т.е. начинается её объявление
            // TODO опять вырезал pure 
            // TODO Понять, когда объявление функции валидно.
            // Оно валидно внутри контекста where ^ = или после завершения returnable 
            // (т.е. текущий токен должен корретно завершать рретурнабл, иначе оформлять вкид)
            return std::make_shared<ReadKeyWord>();

        default:
            // TODO вырезал проверку, при обновлении токена и KeyWord ее надо будет восстановить
            // if (AnalyticUtils::isTokenAKeyWord(t)) {
            //     throwException(L"Got a keyword when a function argument expected", "analyzeToken(Token &)");
            // }

            throwException(
                u8"ForceArgs got something undetectable o_0",
                this->getClassFileName()
            );
            // TODO remove plug
            return std::shared_ptr<AnalyticBasic>();
        }
    }

    std::u8string ReadCallArgs::getClassFileName() {
        return u8"ReadCallArgs.h";
    }
}
