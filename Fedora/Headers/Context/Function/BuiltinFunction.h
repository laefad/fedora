#pragma once

#include "Function.h"

#include <functional>

namespace fedora::context {
    class BuiltinFunction : public Function {
    protected:
        size_t argumentsAmount;
        std::function<std::shared_ptr<types::BasicType>(std::shared_ptr<ContextualComplement::Context>)> f;
    public:
        explicit BuiltinFunction(
            std::u8string name,
            size_t argumentsAmount,
            std::function<std::shared_ptr<types::BasicType>(std::shared_ptr<ContextualComplement::Context>)> f
        );

        /// Возвращает аргументы функции
        virtual std::shared_ptr<Function::Arguments> getArguments() const;

        virtual std::pair<std::shared_ptr<Function>, FunctionRelation> find(
            std::u8string name,
            FunctionRelation filteredType
        ) override;

        virtual std::shared_ptr<types::BasicType> call(
            std::shared_ptr<ContextualComplement::Context> context
        );
    };
}
