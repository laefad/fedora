#pragma once

#include <utility>

#include "BasicType.h"

namespace fedora::types {

        class List : public BasicType {
        protected:
            std::shared_ptr<BasicType> value;
            std::shared_ptr<List> next;
        public:
            explicit List(): 
                value(nullptr), 
                next(nullptr) 
            {}

            explicit List(std::shared_ptr<BasicType> v):
                value(std::move(v)),
                next(nullptr)
            {}

            explicit List(std::shared_ptr<BasicType> v, std::shared_ptr<List> lst):
                value(std::move(v)),
                next(lst)
            {}

            /**
             * Create new list and add newItem to the beginning
             * @param v - the new item
             * @param n - the old list (it won't be changed)
             * @return the new List
             */
            static std::shared_ptr<List> addNewItemToTheBeginning(
                std::shared_ptr<BasicType> v, 
                std::shared_ptr<List> lst
            ) {
                return std::make_shared<List>(std::move(v), std::move(lst));
            }

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
            ) {
                auto head = std::make_shared<List>(lst->value);
                auto new_lst = head;
                auto next = lst->next;

                while(next) {
                    new_lst->next = std::make_shared<List>(next->value);
                    new_lst = new_lst->next;
                    next = next->next;
                }

                new_lst->next = std::make_shared<List>(v);

                return head;
            }

            std::u8string eval() override;

            Type type() override {
                return types::LIST;
            }

            std::shared_ptr<BasicType> getValue() {
                return value;
            }

            std::shared_ptr<List> getNext() {
                return next;
            }

        };

    }
