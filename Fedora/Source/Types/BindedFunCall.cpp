
#include "Types/UnbindedFunCall.h"
#include "Types/BindedFunCall.h"

namespace fedora {
    namespace types {

        BindedFunCall::BindedFunCall(
                std::shared_ptr<context::Function> function,
                BindedFunCall::FunCallArguments args,
                bool forced
        ) :
                FunCall(args, forced),
                function(std::move(function)) {};

        std::shared_ptr<UnbindedFunCall> BindedFunCall::unbind() {
            return std::make_shared<UnbindedFunCall>(function->getName(), args);
        }

        std::shared_ptr<fedora::types::BasicType> BindedFunCall::execute() {
            auto argumentsNames = function->getArguments();

            if (argumentsNames->size() <= args.size()) {
                addContext(ContextualComplement::createContext(
                    *argumentsNames,
                    args
                ));

                return function->call(
                    std::make_shared<ContextualComplement::Context>(context)
                );
            } else {
                return shared_from_this();
            }
        }

        std::u8string BindedFunCall::getFunctionName() {
            return function->getName();
        }

        std::u8string BindedFunCall::eval() {
            std::u8string buf(function->getName());
            buf += u8"(";

            for (std::shared_ptr<BasicType> bt : args) {
                buf += bt->eval();
                if (bt!=args.back())
                    buf += u8" ";
            }

            buf += u8")";

            return buf;
        }
    }
}
