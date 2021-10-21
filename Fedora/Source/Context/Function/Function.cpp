
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

    std::shared_ptr<Function::Arguments> Function::getArguments() const {
        return nullptr;
    }

    std::pair<std::shared_ptr<Function>, FunctionRelation> Function::find(
        std::u8string name,
        FunctionRelation filteredType
    ) {
        return std::make_pair(
            nullptr, 
            FunctionRelation::Any
        );
    }
}
