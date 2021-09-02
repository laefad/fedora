
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"

namespace fedora {
    namespace types { 
        UnbindedFunCall::UnbindedFunCall(
            std::wstring functionName, 
            UnbindedFunCall::FunCallArguments args
        ):
            FunCall(args),
            functionName(functionName)
        {}

        std::unique_ptr<BindedFunCall> UnbindedFunCall::bind(
            std::shared_ptr<context::Function> function
        ) {
            return std::make_unique<BindedFunCall>(function->find(functionName), args);
        }

        std::wstring UnbindedFunCall::eval() {
            std::wstring buf(functionName);
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
