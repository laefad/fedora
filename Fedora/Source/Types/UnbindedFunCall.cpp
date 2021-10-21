
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"
#include "Utils/Logger.h"

namespace fedora {
    namespace types {
        UnbindedFunCall::UnbindedFunCall(
            std::u8string functionName,
            UnbindedFunCall::FunCallArguments args,
            bool forced
        ):
            FunCall(args, forced),
            functionName(functionName) 
        {}

        std::shared_ptr<BindedFunCall> UnbindedFunCall::bind(
            std::shared_ptr<context::Function> function
        ) const {
            auto target = function->find(functionName);
            if (target.first)
                return std::make_shared<BindedFunCall>(target.first, args, forced);
            else {
                Logger::logE(u8"UnbindedFunCall::bind not found function [" +
                             functionName + 
                             u8"] in function [" +
                             function->getName() +
                             u8"]");
                // TODO throw RUNTIME ERROR
                throw std::exception();
            }
        }

        std::u8string UnbindedFunCall::eval() {
            std::u8string buf(functionName);
            buf += u8"(";

            for (std::shared_ptr<BasicType> bt : args) {
                buf += bt->eval();
                if (bt!=args.back())
                    buf += u8" ";
            }

            buf += u8")";

            return buf;
        }

        std::u8string UnbindedFunCall::getFunctionName() {
            return functionName;
        }
    }
}
