#pragma once

#include "BasicType.h"
#include "FunCall.h"
#include "Context/Function/Function.h"

namespace fedora {
    namespace types {
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

            std::unique_ptr<UnbindedFunCall> unbind();

            virtual std::u8string eval() override;

            // Возвращает результат выполнения функции. 
            // Это либо простой тип, либо очередной funcall
            std::unique_ptr<fedora::types::BasicType> execute() {

            }
        };
    }
}
