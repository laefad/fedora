#pragma once

#include <memory>
#include <vector>
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

        /// Возвращает контекст 
        Context getContext();

        /// Добавляет новый контекст к текущему, новые элементы могут перекрывать старые
        void addContext(std::shared_ptr<Context> context);

        /// Создает контекст из названий аргументов и их значений
        static std::shared_ptr<Context> createContext(std::vector<std::u8string> names, std::vector<Argument> values);

        /// Добавляем контекст к элементу, если он является контекстно-поддерживаемым типом
        static void addContextToElement(std::shared_ptr<types::BasicType> elem, std::shared_ptr<Context> context);
    };
}
