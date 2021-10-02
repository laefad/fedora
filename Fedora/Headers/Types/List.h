#pragma once

#include <utility>

#include "BasicType.h"

namespace fedora::types {

        class List : public BasicType {
        protected:
            std::shared_ptr<BasicType> value;

            std::shared_ptr<List> next;
        public:
            List() : value(nullptr), next(nullptr) {}

            explicit List(std::shared_ptr<BasicType> v) : value(std::move(v)), next(nullptr) {}

            /**
             * Create new list and add newItem to the beginning
             * @param v - the new item
             * @param n - the old list (it won't be changed)
             * @return the new List
             */
            static List addNewItemToTheBeginning(std::shared_ptr<BasicType> v, std::shared_ptr<List> n) {
                List a = List();
                a.value = std::move(v);
                a.next = std::move(n);
                return a;
            }

            /**
             * Create new list and add newItem to the end
             * @param v - the new item
             * @param n - the old list (it won't be changed)
             * @return the new List
             */
             // TODO Тут у нас создаётся новый список при добавлении в конец таким образом, что все элементы страого копируются. Мб можно просто в новом списке оставить указатель на первый элемент старого?
            static List addNewItemToTheEnd(std::shared_ptr<BasicType> v, const std::shared_ptr<List> &n) {
                std::shared_ptr<List> a = std::make_shared<List>(n->value);

                std::shared_ptr<List> nextList = n->next;
                std::shared_ptr<List> nextA = a;
                while (nextList != nullptr) {
                    nextA->next = std::make_shared<List>(nextList->value);
                    nextA = nextA->next;
                    nextList = nextList->next;
                }
                nextA->next = std::make_shared<List>(v);
                return *a;
            }


            std::u8string eval() override;

            Type type() override {
                return types::LIST;
            }

            std::shared_ptr<BasicType> getValue(){
                return value;
            }

            std::shared_ptr<List> getNext(){
                throw "UNIMPLEMENTED List::getNext";
            }

        };

    }
