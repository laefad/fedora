
#include "Context/ContextualComplement.h"

namespace fedora::context {
    ContextualComplement::ContextualComplement():
        context(Context())
    {}

    ContextualComplement::ContextualComplement(Context context):
        context(context)
    {}

    ContextualComplement::Argument ContextualComplement::get(std::u8string argumentName) {
        try {
            return context.at(argumentName);
        } catch (std::out_of_range e) {
            return nullptr;
        }
    }
}
