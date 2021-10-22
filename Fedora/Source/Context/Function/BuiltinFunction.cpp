
#include "Context/Function/BuiltinFunction.h"
#include "StaticUtils.h"

namespace fedora::context {

    BuiltinFunction::BuiltinFunction(
        std::u8string name,
        size_t argumentsAmount,
        std::function<std::shared_ptr<types::BasicType>(std::shared_ptr<ContextualComplement::Context>)> f
    ): 
        Function(nullptr, std::move(name)),
        argumentsAmount(argumentsAmount),
        f(f)
    {}

    std::shared_ptr<Function::Arguments> BuiltinFunction::getArguments() const {
        auto args = Function::Arguments();
        for (auto i = 0; i < argumentsAmount; ++i)
            args.push_back(u8"_" + StaticUtils::i2u8s(i));
        return std::make_shared<Function::Arguments>(args);
    };

    std::shared_ptr<types::BasicType> BuiltinFunction::call(
        std::shared_ptr<ContextualComplement::Context> context
    ) {
        return f(context);
    }

    std::pair<std::shared_ptr<Function>, FunctionRelation> BuiltinFunction::find(
        std::u8string name,
        FunctionRelation filteredType
    ) {
        if (this->name == name) {
            return std::make_pair(
                shared_from_this(), 
                FunctionRelation::Self
            );  
        } else {
            return std::make_pair(
                nullptr, 
                FunctionRelation::Any
            );   
        }
    }
}