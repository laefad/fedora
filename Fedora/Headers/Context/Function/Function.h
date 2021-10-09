#pragma once

#include <memory>
#include <map>

#include "Types/FunCall.h"

namespace fedora::context {
    class Function : public std::enable_shared_from_this<Function> {
    public:
        using Context = std::map<std::u8string, std::shared_ptr<Function>>;
        using Arguments = std::vector<std::u8string>;
    protected:
        std::shared_ptr<Function> parent;
        std::u8string name;
    public:
        explicit Function(std::shared_ptr<Function> parent, std::u8string name);

        /// Возвращает имя функции
        std::u8string getName() const;

        /// Возвращает контекст функции
        virtual const std::shared_ptr<Context> getContext() const;

        /// Возвращает аргументы функции
        virtual const std::shared_ptr<Function::Arguments> getArguments() const;

        virtual std::shared_ptr<Function> find(std::u8string name) const;

        virtual std::shared_ptr<types::BasicType> call(
            std::shared_ptr<ContextualComplement::Context> context
        ) const = 0;
    };
}
