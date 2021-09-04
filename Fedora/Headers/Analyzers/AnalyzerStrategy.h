#pragma once

#include <memory>
#include "Parser/Token.h"
#include "AnalyticBasic.h"
#include "ReadKeyWord.h"
#include "Builder/ContextBuilder.h"

namespace fedora {
    /**
     * Класс анализа токенов
     *
     * @brief Реализация паттерна "Стратегия" для анализа прочитаных токенов
     *
     * Предусмотрен ряд состояний, в которых мы можем находиться при чтении файлов
     * @see https://drive.google.com/file/d/1cfkN4fvaYokVqT0LpK5N6XwFGFjbHzKF/view?usp=sharing
     *
    */
    class AnalyzerStrategy {
    private:
        std::shared_ptr<analytic::AnalyticBasic> analyticObj = std::make_shared<analytic::ReadKeyWord>();
        ContextBuilder &contextBuilder;
    public:
        explicit AnalyzerStrategy(ContextBuilder &contextBuilder1) :
                contextBuilder(contextBuilder1) {}

        bool analyzeNext(parser::Token &);
    };

}