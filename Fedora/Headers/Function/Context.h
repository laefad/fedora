#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "Function.h"


namespace fedora {
    namespace function {
        /// Pre-declaration of function class //TODO Мб в единый внешний файл пре-декларации вынести?
        class Function;

        // Контекст, где хранятся функции и их контексты
        class Context {
        public:
            std::shared_ptr<Function> parent;
        private:
            std::vector<std::shared_ptr<Function>> functions = std::vector<std::shared_ptr<Function>>();
        };

    }
}
