#pragma once

#include <memory>
#include "Context.h"
#include "Returnable.h"
#include "Arguments.h"

namespace fedora {
namespace function {

    class Function {
    private:
//        std::shared_ptr<fedora::function::Context> context;
//        std::shared_ptr<Context> selfContext;
        std::unique_ptr<Returnable> returnable;
        std::unique_ptr<Arguments> args;
    };
}
}