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
            static List addNewItemToTheEnd(std::shared_ptr<BasicType> v, std::shared_ptr<List> n) {
                std::shared_ptr<List> nextList = n;

                while (nextList->next != nullptr) {
                    nextList = nextList->next;
                }
                
                nextList->next = std::make_shared<List>(v);
                return *n;
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
