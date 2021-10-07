#pragma once

#include "Function.h"

#include "Types/BasicType.h"

namespace fedora::context
{
    class FeFunction : public Function {
    protected:
        std::shared_ptr<fedora::types::BasicType> returnable;
        std::vector<std::u8string> args;
        Context children;
    public:
        explicit FeFunction(
            std::shared_ptr<Function> parent, 
            std::u8string name
        );

        // TODO only for testing? maybe create TestFeFunction? 
        std::u8string logRet() const;

        //TODO подумать над возвратом частично решенных функций
        virtual std::shared_ptr<fedora::types::BasicType> getBindedReturnbale(
            fedora::types::FunCall::FunCallArguments arguments
        ) const override;

        virtual const std::shared_ptr<Context> getContext() const override;
    };
} 
