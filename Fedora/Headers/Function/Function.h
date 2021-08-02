#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "Context.h"
#include "Returnable.h"
#include "Arguments.h"


namespace fedora {
    namespace function {
        class Context;

        class Function {
        private:
            std::shared_ptr<Context> outsideContext;
            std::shared_ptr<Context> insideContext = std::make_shared<Context>();
            std::unique_ptr<Returnable> returnable = nullptr;
            std::unique_ptr<Arguments> args = std::make_unique<Arguments>();

        public:
            explicit Function(std::shared_ptr<Context> parent) : outsideContext(std::move(parent)) {}
        };
    }
}