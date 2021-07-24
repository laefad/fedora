//
// Created on 20.07.2021.
//

#include "Token.h"
#include "Context.h"
#include "Exceptions/FException.h"
#include "Analyzers/AnalyticBasic.h"
#include "Analyzers/ReadForceArgs.h"
#include "Analyzers/ReadFunArgs.h"

namespace fedora {
    /// Состояние анализа. Описывает то, что ожидает получит анализатор от парсера
    namespace analytic {
        enum ParsingState {
            // Начинаем читать функцию
            WAITING_FOR_FUNCTION,
            // Если нет force, значит мы описываем функцию
            READING_NAME,
            READING_ARGS_LIST,
            READING_FUNCTION_BODY,
            READING_FUNCTION_RESULT, // Возвращать функция может базовый тип или ленивый вызов другой функции
            READING_FUNCTION_RESULT_LIST,
            READING_FUNCTION_RESULT_FUNCALL,


            // Если есть force, значит мы вызываем функцию
            READING_NAME_FORCE,
            READING_LEFT,
            READING_ARGS,
            READING_RIGHT,
        };


        /// Полный алгоритм парсинга
        /// 1. Читаем ключевые слова функции
        /// 2.
        class Analyzer {
        private:
            ParsingState state;
            std::shared_ptr<function::Context> context;
            std::vector<Token> tmpTokens = std::vector<Token>();
            std::shared_ptr<AnalyticBasic> analyticObj = std::make_shared<ReadForceArgs>();

            // TODO Все функции зарефакторить как отдельные классы с наследованием от базового
            // TODO Проверять валидность имён переменных!!!!!!!!
            bool waitingForFunction(Token &);

            bool readName(Token &);

            bool readArgs(Token &);

            bool readFunBody(Token &);

            bool readFunRes(Token &);

            bool checkIfNum(Token &);

            bool checkIfString(Token &);

            bool checkIfList(Token &);

        public:
            /// Ключевые слова, которые мы ожидаем после завершения последней функции или при начале парсинга.
            /// Они должны начинать объявление новой функции или импорт
            // TODO Разбить список ключевых слов на подсписки по смыслу
            std::vector<std::wstring> allKeyWords = {L"let", L"pure", L"using", L"import", L"force", L"where"};


            Analyzer();

            bool analyzeNext(Token &);
        };
    }
}
