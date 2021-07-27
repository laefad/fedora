//
// Created on 23.07.2021.
//
#pragma once

#include <memory>
#include "Token.h"
#include "AnalyticBasic.h"
#include "ReadKeyWord.h"

namespace fedora {
    /**
     * Класс анализа токенов
     *
     * @brief Реализация паттерна "Стратегия" для анализа прочитаных токенов
     *
     * Предусмотрен ряд состояний, в которых мы можем находиться при чтении файлов
     * @see https://drive.google.com/file/d/1cfkN4fvaYokVqT0LpK5N6XwFGFjbHzKF/view?usp=sharing
    */
    // TODO Обеспечить доступ к последним прочитаным токенам для отображения ошибок
    class AnalyzerStrategy {
    private:
        std::shared_ptr<analytic::AnalyticBasic> analyticObj = std::make_shared<analytic::ReadKeyWord>(
                std::vector<Token>());
    public:
        bool analyzeNext(Token &);
    };

}