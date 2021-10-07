
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

    void ContextualComplement::addContext(Context context) {
        for (auto [key, value] : context) {
            this->context[key] = value;
        }
    }

    ContextualComplement::Context ContextualComplement::createContext(
        std::vector<std::u8string> names, 
        std::vector<Argument> values
    ) {
        Context c = Context();
        for (size_t i = 0; i < names.size(); ++i) {
            c[names[i]] = values[i];
        }
        return c;
    }
}
