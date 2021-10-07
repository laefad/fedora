
#include "Context/Function/FeFunction.h"

namespace fedora::context {
    FeFunction::FeFunction(
        std::shared_ptr<Function> parent, 
        std::u8string name
    ): 
        Function(std::move(parent), std::move(name)),
        children(Context()),
        returnable(nullptr),
        args(std::vector<std::u8string>())
    {}

    std::u8string FeFunction::logRet() const {
        return returnable->eval();
    }

    const std::shared_ptr<Function::Arguments> FeFunction::getArguments() const {
        return std::make_shared<Function::Arguments>(args);
    }

    const std::shared_ptr<Function::Context> FeFunction::getContext() const {
        return std::make_shared<Function::Context>(children);
    }

}
