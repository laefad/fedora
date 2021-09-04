
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"

namespace fedora {
    namespace types {

        BindedFunCall::BindedFunCall(
                std::shared_ptr<context::Function> function,
                BindedFunCall::FunCallArguments args
        ) :
                FunCall(args),
                function(std::move(function)) {};

        std::unique_ptr<UnbindedFunCall> BindedFunCall::unbind() {
            return std::make_unique<UnbindedFunCall>(function->getName(), args);
        }

        std::wstring BindedFunCall::eval() {
            std::wstring buf(function->getName());
            buf += L"(";

            for (std::shared_ptr<BasicType> bt : args) {
                buf += bt->eval();
                buf += L" ";
            }

            buf += L")";

            return buf;
        }
    }
}
