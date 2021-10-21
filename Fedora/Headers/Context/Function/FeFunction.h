#pragma once

#include "Function.h"

#include "Types/BasicType.h"

namespace fedora::context
{
    class FeFunction : public Function {
    protected:
        std::shared_ptr<fedora::types::BasicType> returnable;
        Function::Arguments args;
        Context children;
    public:
        explicit FeFunction(
            std::shared_ptr<Function> parent, 
            std::u8string name
        );

        virtual std::shared_ptr<Function::Arguments> getArguments() const override;

        virtual const std::shared_ptr<Context> getContext() const override;

        virtual std::pair<std::shared_ptr<Function>, FunctionRelation> find(
            std::u8string name,
            FunctionRelation filteredType = FunctionRelation::Any
        ) override;

        // TODO only for testing? maybe create TestFeFunction? 
        std::u8string logRet() const;

        virtual std::shared_ptr<types::BasicType> call(
            std::shared_ptr<ContextualComplement::Context> context
        );
    };
} 
