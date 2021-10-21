#pragma once

#include <memory>
#include <map>

#include "Types/FunCall.h"
#include "Context/Function/FunctionRelation.h"

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
        virtual std::shared_ptr<Function::Arguments> getArguments() const;

        /// Возвращает найденную функцию в контексте или nullptr, если ее нет 
        /// При этом FunctionRelation устанавливает соответственно приоритету
        virtual std::pair<std::shared_ptr<Function>, FunctionRelation> find(
            std::u8string name,
            FunctionRelation filteredType = FunctionRelation::Any
        );

        /// Вызывает функцию и возвращает простой тип или очередной вызов
        virtual std::shared_ptr<types::BasicType> call(
            std::shared_ptr<ContextualComplement::Context> context
        ) = 0;
    };
}
