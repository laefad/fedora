#pragma once

#include "Function.h"

#include "Context/Function/Returnable/Returnable.h"
#include "Types/BasicType.h"
#include "Arguments.h"

namespace fedora::context
{
    class FeFunction : public Function {
    protected:
        std::unique_ptr<Returnable> returnable = nullptr;
        std::unique_ptr<NamesOfArguments> args = std::make_unique<NamesOfArguments>();
        std::map<std::u8string, std::shared_ptr<Function>> children = std::map<std::u8string, std::shared_ptr<Function>>();
    public:
        explicit FeFunction(std::shared_ptr<Function> parent, std::u8string name): 
            Function(std::move(parent), std::move(name))
        {}

        virtual const std::shared_ptr<Context> getContext() const override {
            return std::make_shared<Function::Context>(children);
        }
        
    };
} 
