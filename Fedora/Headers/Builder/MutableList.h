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
             * Get the actual first item of this list
             */
            std::shared_ptr<builder::MutableList> getTheVeryFirstItem(){
                std::shared_ptr<builder::MutableList> mParent = this->parent;
                std::shared_ptr<builder::MutableList> mList = std::static_pointer_cast<builder::MutableList>(this->shared_from_this());
                while(mParent != nullptr){
                    mList = mParent;
                    mParent = mList->parent;
                }
                return mList;
            }

            void setValue(std::shared_ptr<types::BasicType> v){
                value = std::move(v);
            }

            void setNext(std::shared_ptr<types::List> l){
                next = std::move(l);
            }
        };
    }
}