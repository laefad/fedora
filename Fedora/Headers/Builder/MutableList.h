//
// Created on 24.08.2021.
//

#include "Types/List.h"

#include <utility>

namespace fedora {
    namespace builder {
        /**
         * A list, that can change itself
         */
        class MutableList : public types::List {
        public:
            /**
             * if this list is dead inside, it'll have the parent
             */
            std::shared_ptr<MutableList> parent = nullptr;

            /**
             * Add new value to the list
             * @param t - a value to add
             */
            void addBasicToFirstFoundPlace(std::shared_ptr<types::BasicType> t) {
                // if list is empty
                if (value == nullptr) {
                    value = std::move(t);
                } else {
                    next = std::make_shared<types::List>();
                }
            }
        };
    }
}