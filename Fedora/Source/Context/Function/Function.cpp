
#include "Context/Function/Function.h"

namespace fedora::context {
    
    Function::Function(std::shared_ptr<Function> parent, std::u8string name):
        parent(std::move(parent)),
        name(std::move(name))
    {}

    std::u8string Function::getName() const {
        return name;
    }

    const std::shared_ptr<Function::Context> Function::getContext() const {
        return nullptr;
    }

    std::shared_ptr<fedora::types::BasicType> Function::getBindedReturnbale(
        fedora::types::FunCall::FunCallArguments arguments
    ) const {
        // TODO add realization or maybe delete this on basic class
        return nullptr;
    }

    std::shared_ptr<Function> Function::find(std::u8string name) const {
        // TODO add realization
        return nullptr;
    }
}
