#include "Analyzers/ReadKeyWord.h"
#include "Analyzers/ReadList.h"
#include "Analyzers/ReadResult.h"
#include "Analyzers/ReadName.h"
#include "Analyzers/ReadAfterListEnd.h"

namespace fedora::analytic {
    /**
     * @brief TODO write brief
     *
     * @details
     * Ожидаются:
     *  2. ")" Завершение функции
     *  3. Number. Следующий аргумент
     *  4. String. Следующий аргумент
     *  5. "[" Начало следующего списка
     *  6. = Начало returnable
     *  7. KeyWord. Начало объявления новой функции
     *  8. Let Новая функция объявлена
     *
     */
    std::shared_ptr<AnalyticBasic> ReadAfterListEnd::analyzeToken(
        parser::Token const& t,
        ContextBuilder& b
    ) {
        using fedora::parser::TokenType;

        log(u8"Class: " + getClassFileName(), fedora::settings::LOG_VERBOSE);
        log(u8"Token: " + t.getData(), fedora::settings::LOG_VERBOSE);

        switch (t.getType())
        {
        // case TokenType::ListClose:
        //     return shared_from_this();

        case TokenType::CallClose:
            return std::make_shared<ReadKeyWord>();

        case TokenType::Number:
            /**
             * @example case 1: List and num inside list
             * let a = [ [1 2] 3 ]
             *
             * @example case 2: List and num in force args
             * force main ( [1 2] 3 )
             */
            // TODO Возвращать в чтение списка или в force args по необходимости
            return shared_from_this();

        case TokenType::String:
            // TODO Examples аналогичны Number
            return shared_from_this();

        case TokenType::ListOpen:
            return std::make_shared<ReadList>();

        case TokenType::FunctionReturnableDeclaration:
            return std::make_shared<ReadResult>();

        case TokenType::ForceCall:
            // TODO здесь был prefun keyword раньше (+ pure)
            return std::make_shared<ReadKeyWord>();

        case TokenType::FunctionDeclaration:
            b.finishCurrentContext();
            b.notifyWeGotLetToken();
            return std::make_shared<ReadName>(ReadName::FUNCTION_DECLARATION);

        default:
            throwException(
                u8"Got something unexpected. Token = " + t.getData(),
                this->getClassFileName()
            );
            // TODO remove plug
            return std::shared_ptr<AnalyticBasic>();
        }
    }

    std::u8string ReadAfterListEnd::getClassFileName() {
        return u8"ReadAfterListEnd.h";
    }
}
