#pragma once

#include "BasicType.h"
#include "FunCall.h"
#include "Context/Function/Function.h"

namespace fedora {
    namespace types {
        class BindedFunCall;

        class UnbindedFunCall : public types::FunCall {
        protected:
            // Имя функции, которая будет вызвана
            std::wstring functionName;
        public:
            explicit UnbindedFunCall(
                    std::wstring functionName,
                    FunCallArguments args
            );

            // TODO add error 
            std::unique_ptr<BindedFunCall> bind(
                    std::shared_ptr<context::Function> function
            );

            virtual std::wstring eval() override;
        };
    }
}
