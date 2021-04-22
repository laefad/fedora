#pragma once
#include "Context.h"
#include "Returnable.h"
#include "Arguments.h"

namespace fedora {
namespace function {

    class Function {
    private:
        std::shared_ptr<Contex> context;
        std::shared_ptr<Contex> selfContext;
        std::unique_ptr<Returnable> returnable;
        std::unique_ptr<Arguments> args;
    };
}
}