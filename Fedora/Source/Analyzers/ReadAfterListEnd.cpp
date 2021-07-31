//
// Created on 31.07.2021.
//

#include <Analyzers/ReadKeyWord.h>
#include "Analyzers/ReadAfterListEnd.h"
#include "Analyzers/AnalyticUtils.h"

namespace fedora{
    namespace analytic{

        std::shared_ptr<AnalyticBasic> ReadAfterListEnd::analyzeToken(Token &t) {
            // Ожидаются:
            // 1. "]" Закрытие списка
            // 2. ")" Завершение функции
            // 3. Number. Следующий аргумент
            // 4. String. Следующий аргумент
            // 5. "[" Начало следующего списка
            // 6. = Начало returnable
            // 7. KeyWord. Начало объявления новой функции

            if (AnalyticUtils::isTokenARightSquareBracket(t.data)){
                return shared_from_this();
            }

            if (AnalyticUtils::isTokenARightCircleBracket(t.data)){
                return std::make_shared<ReadKeyWord>(std::vector<Token>());
            }

            throwException(L"Unimplemented","");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::string ReadAfterListEnd::getFileName() {
            return "ReadAfterListEnd.h";
        }
    }
}

