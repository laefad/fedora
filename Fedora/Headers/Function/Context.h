#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include "Function.h"

namespace fedora {
namespace function {

    // Контекст, где хранятся функции и их контексты
    class Context {
    public:
        std::shared_ptr<Context> parent;
    private:
        // Массив указателей на функции
        std::vector<std::shared_ptr<Function>> functions = std::vector<std::shared_ptr<Function>>();
    };

}
}
