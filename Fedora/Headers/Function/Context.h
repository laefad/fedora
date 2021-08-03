#pragma once

#include <map>
#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "Function.h"


namespace fedora {
    namespace function {
        /// Pre-declaration of function class //TODO Мб в единый внешний файл пре-декларации вынести?
        class Function;

        // Контекст, где хранятся функции и их контексты
        class Context : public std::enable_shared_from_this<Context> {
            // TODO Вынести в .cpp реализации И инициализации
        public:
            /**
             * Constructor with pointer to parent initialization
             */
            explicit Context(std::shared_ptr<Function> p) : parent(std::move(p)) {}

            std::shared_ptr<Function> parent;

            bool isEmpty() {
                return functions.empty();
            }

            /**
             * Start function declaration
             * // TODO Класс объявления функции. Этапы: ключевые слова, имя, аргументы, контекст, ретурн. Если проиходит несвоевременное изменение, бросаем ошибку
             */
            void addFunction() {

            }

        private:
            std::vector<std::shared_ptr<Function>> functions = std::vector<std::shared_ptr<Function>>();
        };

    }
}
