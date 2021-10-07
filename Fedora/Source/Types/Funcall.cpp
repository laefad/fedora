
#include "Types/FunCall.h"

namespace fedora::types {

    FunCall::FunCall(
        fedora::context::ContextualComplement::Context context,
        FunCallArguments args,
        bool forced
    ):
        ContextualComplement(context),
        args(args),
        forced(forced)
    {}

    FunCall::FunCall(FunCallArguments args, bool forced):
        ContextualComplement(),
        args(args),
        forced(forced)
    {}

    Type FunCall::type() {
        return FUN_CALL;
    }

    bool FunCall::isForced() {
        return forced;
    }

    FunCall::FunCall():
        args(FunCall::FunCallArguments()),
        forced(false)
    {}
}
