
#include "KeyWords.h"

#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadAfterListEnd.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora{
    namespace analytic{

        ReadAfterListEnd::ReadAfterListEnd(std::vector<Token> vec):
            AnalyticBasic(std::move(vec))
        {}

        std::shared_ptr<AnalyticBasic> ReadAfterListEnd::analyzeToken(Token const& t) {
            // Ожидаются:
            // 1. "]" Закрытие списка
            // 2. ")" Завершение функции
            // 3. Number. Следующий аргумент
            // 4. String. Следующий аргумент
            // 5. "[" Начало следующего списка
            // 6. = Начало returnable
            // 7. KeyWord. Начало объявления новой функции
            // 8. Let Новая функция объявлена

            // "]"
            if (AnalyticUtils::isTokenARightSquareBracket(t)) {
                return shared_from_this();
            }

            // ")"
            if (AnalyticUtils::isTokenARightCircleBracket(t)) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            // Number
            /**
             * @example case 1: List and num inside list
             * let a = [ [1 2] 3 ]
             *
             * @example case 2: List and num in force args
             * force main ( [1 2] 3 )
             */
            if (AnalyticUtils::isTokenANumber(t)) {
                // TODO Возвращать в чтегие списка или в force args по необходимости
                return shared_from_this();
            }

            // TODO Examples аналогичны Number
            if (AnalyticUtils::isTokenAString(t)) {
                return shared_from_this();
            }

            // "["
            if (AnalyticUtils::isTokenALeftSquareBracket(t)) {
                return std::make_shared<ReadList>(std::vector<Token>());
            }

            if (t == returns) {
                return std::make_shared<ReadResult>(std::vector<Token>());
            }

            if (AnalyticUtils::isTokenAPreFunKeyWord(t)) {
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            if (t == let){
                return std::make_shared<ReadName>(std::vector<Token>());
            }

            throwException(L"Got something unexpected. Token = " + t.getData(), "ReadAfterListEnd");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadAfterListEnd::getFileName() {
            return "ReadAfterListEnd.h";
        }
    }
}

