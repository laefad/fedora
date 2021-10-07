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

        virtual const std::shared_ptr<Function::Arguments> getArguments() const override;

        virtual const std::shared_ptr<Context> getContext() const override;

        // TODO only for testing? maybe create TestFeFunction? 
        std::u8string logRet() const;
    };
} 
