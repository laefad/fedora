#pragma once

#include "Function.h"

#include "Types/BasicType.h"
#include "Arguments.h"

namespace fedora::context
{
    class FeFunction : public Function {
    protected:
        std::shared_ptr<fedora::types::BasicType> returnable;
        std::unique_ptr<NamesOfArguments> args;
        Context children;
    public:
        explicit FeFunction(std::shared_ptr<Function> parent, std::u8string name): 
            Function(std::move(parent), std::move(name)),
            children(Context()),
            returnable(nullptr),
            args(std::make_unique<NamesOfArguments>())
        {}

        // TODO only for testing? maybe create TestFeFunction? 
        std::u8string logRet() const {
            return returnable->eval();
        }

        virtual const std::shared_ptr<Context> getContext() const override {
            return std::make_shared<Function::Context>(children);
        }
        
    };
} 
