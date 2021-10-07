#pragma once

#include <utility>

#include "BasicType.h"
#include "Context/ContextualComplement.h"

namespace fedora::types {

    class List : public BasicType, public fedora::context::ContextualComplement {
    protected:
        std::shared_ptr<BasicType> value;
        std::shared_ptr<List> next;
    public:
        explicit List();
        explicit List(std::shared_ptr<BasicType> v);
        explicit List(std::shared_ptr<BasicType> v, std::shared_ptr<List> lst);
        explicit List(
            fedora::context::ContextualComplement::Context context,
            std::shared_ptr<BasicType> v,
            std::shared_ptr<List> lst
        );

        /**
         * Create new list and add newItem to the beginning
         * @param v - the new item
         * @param n - the old list (it won't be changed)
         * @return the new List
         */
        static std::shared_ptr<List> addNewItemToTheBeginning(
            std::shared_ptr<BasicType> v, 
            std::shared_ptr<List> lst
        );

        /**
         * Create new list and add newItem to the end
         * @param v - the new item
         * @param n - the old list (it won't be changed)
         * @return the new List
         * 
         * @details
         * Мы копируем указатели на данные, мы не создаем новые данные, но создаем список с нуля
         */
        static std::shared_ptr<List> addNewItemToTheEnd(
            std::shared_ptr<BasicType> v,
            std::shared_ptr<List> lst
        );

        std::u8string eval() override;

        virtual Type type() override;

        /// Возвращает значение элемента списка
        std::shared_ptr<BasicType> getValue();

        /// Возвращает следующий элемент списка
        std::shared_ptr<List> getNext();
    };

}
