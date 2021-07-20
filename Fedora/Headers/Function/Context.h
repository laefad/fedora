#pragma once
#include "Function.h"
#include <map>
#include <string>
#include <memory>
#include "vector"

namespace fedora {
namespace function {

    // Контекст, где хранятся функции и их контексты
    class Context {
    public:

    private:
        // Массив указателей на функции
        std::vector<std::shared_ptr<Function>> functions = std::vector<std::shared_ptr<Function>>();
    };

}
}
