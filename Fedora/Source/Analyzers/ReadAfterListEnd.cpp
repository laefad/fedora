
#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora {
    namespace analytic {

        std::shared_ptr<AnalyticBasic> ReadAfterListEnd::analyzeToken(parser::Token const &t, ContextBuilder &b) {
            using fedora::parser::TokenType;
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
            if (t.getType() == TokenType::ListClose) 
                return shared_from_this();

            // ")"
            if (t.getType() == TokenType::CallClose)
                return std::make_shared<ReadKeyWord>();

            // Number
            /**
             * @example case 1: List and num inside list
             * let a = [ [1 2] 3 ]
             *
             * @example case 2: List and num in force args
             * force main ( [1 2] 3 )
             */
            if (t.getType() == TokenType::Number)
                // TODO Возвращать в чтение списка или в force args по необходимости
                return shared_from_this();

            // TODO Examples аналогичны Number
            if (t.getType() == TokenType::String)
                return shared_from_this();

            // "["
            if (t.getType() == TokenType::ListOpen)
                return std::make_shared<ReadList>();

            if (t.getType() == TokenType::FunctionReturnableDeclaration) {
                return std::make_shared<ReadResult>();
            }

            // TODO здесь был prefun keyword раньше (+ pure)
            if (t.getType() == TokenType::ForceCall)  {
                return std::make_shared<ReadKeyWord>();
            }

            if (t.getType() == TokenType::FunctionDeclaration) {
                return std::make_shared<ReadName>(ReadName::FUNCTION_DECLARATION);
            }

            throwException(L"Got something unexpected. Token = " + t.getData(), L"ReadAfterListEnd");
            return std::shared_ptr<AnalyticBasic>();
        }

        std::wstring ReadAfterListEnd::getClassFileName() {
            return L"ReadAfterListEnd.h";
        }
    }
}

