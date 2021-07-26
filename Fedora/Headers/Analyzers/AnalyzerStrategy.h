//
// Created on 23.07.2021.
//
#pragma once
#include "Token.h"

namespace fedora{
    namespace analytic {
        /**
         * @brief Реализация паттерна "Стратегия" для анализа прочитаных токенов
         *
         * Предусмотрен ряд состояний, в которых мы можем находиться при чтении файлов
         * @see https://drive.google.com/file/d/1cfkN4fvaYokVqT0LpK5N6XwFGFjbHzKF/view?usp=sharing
        */
        // TODO Обеспечить доступ к последним прочитаным токенам для отображения ошибок
        // TODO Обеспечить проброс ссылки на сам экземпляр класса внутрь его класса
        class AnalyzerStrategy {

        };
    }
}