#pragma once

#include <utility>

#include "BasicType.h"

namespace fedora {
    namespace types {

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


            std::wstring eval() override;

            Type type() override {
                return types::LIST;
            }

        };

    }
}
