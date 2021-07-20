//
// Created on 20.07.2021.
//

#include "Token.h"

namespace fedora {
    // Состояние анализа. Описывает то, что ожидает получит анализатор от парсера
    enum ParsingState{
        WAITING_FOR_KEYWORD,
        READING_NAME,
        READING_ARGS_LIST,
        READING_FUNCTION_BODY,
        READING_FUNCTION_RESULT,
    };

    class Analyzer {
    private:
        ParsingState state;
    public:
        void analyzeNext(Token&);
    };
}
