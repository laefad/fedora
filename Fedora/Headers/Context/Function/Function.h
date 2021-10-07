#pragma once

#include <memory>
#include <map>

#include "Types/FunCall.h"

namespace fedora::context {
    class Function : public std::enable_shared_from_this<Function> {
    public:
        using Context = std::map<std::u8string, std::shared_ptr<Function>>;
    protected:
        std::shared_ptr<Function> parent;
        std::u8string name;
    public:
        explicit Function(std::shared_ptr<Function> parent, std::u8string name);

        /// Возвращает имя функции
        std::u8string getName() const;

        // По умолчанию возвращаем пустой контекст
        virtual const std::shared_ptr<Context> getContext() const;

        /**
         * @brief Возвращает результат вызова функции с аргументами
         *
         * @details
         * Возвращает результат выполнения функции, подставляя в него аргументы,
         * либо возвращает новый вызов текущей функции, если аргументов недостаточно
         */
        virtual std::shared_ptr<fedora::types::BasicType> getBindedReturnbale(
            fedora::types::FunCall::FunCallArguments arguments
        ) const;

        virtual std::shared_ptr<Function> find(std::u8string name) const;
    };
}
