#pragma once

#include "BasicType.h"
#include "FunCall.h"
#include "Context/Function/Function.h"

namespace fedora::types {
    class UnbindedFunCall;

    class BindedFunCall : public types::FunCall {
    protected:
        // Имя функции, которая будет вызвана
        std::shared_ptr<context::Function> function;
    public:
        explicit BindedFunCall(
            std::shared_ptr<context::Function> function,
            FunCallArguments args,
            bool forced = false
        );

        std::shared_ptr<UnbindedFunCall> unbind();

        virtual std::u8string eval() override;

        virtual std::u8string getFunctionName() override;

        // Возвращает результат выполнения функции. 
        // Это либо простой тип, либо очередной funcall
        std::shared_ptr<fedora::types::BasicType> execute();
    };
}
