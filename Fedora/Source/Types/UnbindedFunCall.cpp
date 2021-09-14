
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"

namespace fedora {
    namespace types {
        UnbindedFunCall::UnbindedFunCall(
                std::u8string functionName,
                UnbindedFunCall::FunCallArguments args
        ) :
                FunCall(args),
                functionName(functionName) {}

        std::unique_ptr<BindedFunCall> UnbindedFunCall::bind(
                std::shared_ptr<context::Function> function
        ) {
            return std::make_unique<BindedFunCall>(function->find(functionName), args);
        }

        std::u8string UnbindedFunCall::eval() {
            std::u8string buf(functionName);
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
