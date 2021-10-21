#pragma once

#include "BasicType.h"
#include "FunCall.h"
#include "Context/Function/Function.h"

namespace fedora::types {
    class BindedFunCall;

    class UnbindedFunCall : public types::FunCall {
    protected:
        // Имя функции, которая будет вызвана
        std::u8string functionName;
    public:
        explicit UnbindedFunCall(
                std::u8string functionName,
                FunCallArguments args,
                bool forced = false 
        );

        // TODO add error 
        std::shared_ptr<BindedFunCall> bind(
            std::shared_ptr<context::Function> function
        ) const ;

        virtual std::u8string getFunctionName() override;

        virtual std::u8string eval() override;
    };
}
