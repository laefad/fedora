//
// Created on 23.07.2021.
//

#include <Analyzers/ReadKeyWord.h>
#include <Analyzers/ReadForceArgs.h>
#include "Analyzers/ReadResult.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora {
    namespace analytic {
        std::shared_ptr<AnalyticBasic> ReadResult::analyzeToken(Token &t) {
            addToken(t);    // Записать прочитаный токен

            // 4 Варианта, что можно вернуть из функции:
            // 1. Число
            // 2. Строка
            // 3. Список
            // 4. Функция

            // Если число
            if (AnalyticUtils::isValueANumber(t.data)) {
                // TODO Выделить во внешнюю константу пустой вектор токенов ( std::vector<Token>() )
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Если строка
            if (AnalyticUtils::isValueAString(t.data)) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Если Список
            if (isTokenALeftSquareBracket(t.data)) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Если функция
            if (AnalyticUtils::isValidName(t.data)) {
                // TODO Внедрить режим чтения для force вызова и ретурна из функции
                return std::make_shared<ReadForceArgs>(std::vector<Token>());
            }

            // Пустая строка, которая нужна, чтобы конкатенировать константные строки. Забавно
            std::wstring text = L"";
            // TODO Вынести тексты всех ошибок в единый файл и пронумеровать их
            throwException(L"You have to return something from function, but nothing valid found.\n" + text +
                           L"Possible variants:\n" + text + L"1. Number\n2. String\n3. List\n 4. Another function\n" +
                           text + L"Found: token = " + t.data, "analyzeToken(Token&)");
            return std::shared_ptr<AnalyticBasic>();
        }

        bool ReadResult::isTokenALeftSquareBracket(std::wstring &data) {
            return data.length() == 1 && data.at(0) == L'[';
        }

        void ReadResult::throwException(const std::wstring &msg, const std::string &funcName) {

        }
    }
}
