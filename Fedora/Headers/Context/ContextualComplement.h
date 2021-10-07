#pragma once

#include <memory>
#include <map>

#include "Types/BasicType.h"

namespace fedora::context {
    class ContextualComplement {
    public:
        using Argument = std::shared_ptr<fedora::types::BasicType>;
        using Context = std::map<std::u8string, Argument>;
    protected:
        Context context;
    public:
        explicit ContextualComplement();
        explicit ContextualComplement(Context context);

        /// Возващает аргумент, если аргумента нет с таким именем, то возвращает nullptr
        Argument get(std::u8string argumentName);

        /// Добавляет новый контекст к текущему, новые элементы могут перекрывать старые
        void addContext(Context context);
    };
}
