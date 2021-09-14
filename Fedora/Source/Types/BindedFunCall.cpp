
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

        std::u8string BindedFunCall::eval() {
            std::u8string buf(function->getName());
            buf += u8"(";

            for (std::shared_ptr<BasicType> bt : args) {
                buf += bt->eval();
                buf += u8" ";
            }

            buf += u8")";

            return buf;
        }
    }
}
