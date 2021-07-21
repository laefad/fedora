//
// Created on 20.07.2021.
//

#include "Token.h"
#include "Context.h"
#include "FException.h"

namespace fedora {
    /// Состояние анализа. Описывает то, что ожидает получит анализатор от парсера
    enum ParsingState{
        // Начинаем читать функцию
        WAITING_FOR_FUNCTION,
        // Если нет force, значит мы описываем функцию
        READING_NAME,
        READING_ARGS_LIST,
        READING_FUNCTION_BODY,
        READING_FUNCTION_RESULT, // Возвращать функция может базовый тип или ленивый вызов другой функции


        // Если есть force, значит мы вызываем функцию
        READING_NAME_FORCE,
        READING_LEFT,
        READING_ARGS,
        READING_RIGHT,
    };

    class Analyzer {
    private:
        ParsingState state;
        std::shared_ptr<function::Context> context;
        std::vector<Token> tmpTokens = std::vector<Token>();

        bool waitingForFunction(Token &);
        bool readName(Token &);
        bool readArgs(Token&);
        bool readFunBody(Token&);
        bool readFunRes(Token&);
    public:
        /// Ключевые слова, которые мы ожидаем после завершения последней функции или при начале парсинга.
        /// Они должны начинать объявление новой функции или импорт
        std::vector<std::wstring> allKeyWords = {L"let", L"pure", L"using", L"import", L"force", L"where"};


        Analyzer();
        bool analyzeNext(Token&);
    };
}
