//
// Created on 20.07.2021.
//

#include "Token.h"
#include "Context.h"
#include "FException.h"

namespace fedora {
    // Состояние анализа. Описывает то, что ожидает получит анализатор от парсера
    enum ParsingState{
        WAITING_FOR_FUNCTION,
        READING_NAME,
        READING_ARGS_LIST,
        READING_FUNCTION_BODY,
        READING_FUNCTION_RESULT,
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
        std::vector<std::wstring> allKeyWords = {L"let"};


        Analyzer();
        bool analyzeNext(Token&);
    };
}
