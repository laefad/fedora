
#include "Types/BindedFunCall.h"
#include "Context/Function/Function.h"
#include "Stack/StackHolder.h"

namespace fedora {
    class Runtime {
    public:
        static void addSTDtoContext(std::shared_ptr<context::Function> context) {

        }

        static void execute(StackHolder sh, std::shared_ptr<context::Function> context) {
            using Call = StackHolder::Call;
            using BindedCall = std::shared_ptr<types::BindedFunCall>;

            for (const Call &call : sh.getData()) {
                BindedCall bcall = call->bind(context);
                bcall->execute();
            }
        }
    };
}
