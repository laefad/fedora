#include <stdexcept>

#include "Context/ContextualComplement.h"

namespace fedora::context {
    ContextualComplement::ContextualComplement() :
        context(Context())
    {}

    ContextualComplement::ContextualComplement(Context context) :
        context(context)
    {}

    ContextualComplement::Argument ContextualComplement::get(std::u8string argumentName) {
        try {
            return context.at(argumentName);
        } catch (std::out_of_range e) {
            return nullptr;
        }
    }

    ContextualComplement::Context ContextualComplement::getContext() {
        return context;
    }

    void ContextualComplement::addContext(std::shared_ptr<Context> context) {
        for (auto [key, value] : *context) {
            this->context[key] = value;
        }
    }

    std::shared_ptr<ContextualComplement::Context> ContextualComplement::createContext(
        std::vector<std::u8string> names,
        std::vector<Argument> values
    ) {
        auto c = std::make_shared<Context>();
        for (size_t i = 0; i < names.size(); ++i) {
            c->operator[](names[i]) = values[i];
        }
        return std::move(c);
    }

    void ContextualComplement::addContextToElement(
        std::shared_ptr<types::BasicType> elem,
        std::shared_ptr<Context> context
    ) {
        using fedora::types::Type;
        auto type = elem->type();

        if (type == Type::LIST || type == Type::FUN_CALL) {
            dynamic_cast<ContextualComplement*>(elem.get())->addContext(context);
        }
    }
}
